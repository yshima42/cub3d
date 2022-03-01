#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

bool has_wall_at(t_map map, double x, double y)
{
	if (x < 0 || x >= ((int)map.width * TILE_SIZE) || y < 0 || y >= ((int)map.height * TILE_SIZE)) 
        return true;
	size_t mapIndexX = floor(x / TILE_SIZE);
	size_t mapIndexY = floor(y / TILE_SIZE);
	return map.map[mapIndexY][mapIndexX] != '0';
}

void squre_pixel_put(t_data *screen, int px, int py, int size, int color)
{
	int i;
	int j;
	int c_color;

	i = px;
	while (i < px + size)
	{
		j = py;
		while(j < py + size)
		{
			if (i == px || j == py)
				c_color = 0x808080;
			else
				c_color = color;
			my_mlx_pixel_put(screen, i, j, c_color);
			j++;
		}
		i++;
	}
}

double normalize_angle(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

void circle_pixel_put(t_data *screen, unsigned int px, unsigned int py, int radius, int color)
{
	unsigned int x;
	unsigned int y;
	int dx;
	int dy;

	y = py - radius;
	while(y < py + radius)
	{
		x = px - radius;
		while (x < px + radius)
		{
			dx = (int)x - (int)px;
			dy = (int)y - (int)py;
			if ((dx * dx) + (dy * dy) <= radius * radius)
			{
				my_mlx_pixel_put(screen, x, y, color);
			}
			x++;
		}
		y++;
	}
}

void line_pixel_put(t_data *screen, t_player *player, double angle, double len, int color)
{
	int x;
	int y;
	double i;
	for (i = 0; i < len; i++)
	{
		x = player->pos.x * MINIMAP_SCALE + i * cos(angle);
		y = player->pos.y * MINIMAP_SCALE + i * sin(angle);
		my_mlx_pixel_put(screen, x, y, color);
	}
}

void line_pixel_put_2(t_data *screen, t_player player, t_point start, t_point end, int color)
{
	unsigned int x;
	unsigned int y;
	int dx;
	int dy;
	unsigned int len;
	double rad;
	unsigned int i;

	dx = end.x - start.x;
	dy = end.y - start.y;
	len = sqrt(dx * dx + dy * dy);
	rad = atan2(dy, dx);

	for (i = 0; i < len; i++)
	{
		x = player.pos.x * MINIMAP_SCALE + i * cos(rad);
		y = player.pos.y * MINIMAP_SCALE + i * sin(rad);
		my_mlx_pixel_put(screen, x, y, color);
	}
}

void render_player(t_conf *conf)
{
	circle_pixel_put(&conf->screen, conf->player.pos.x * MINIMAP_SCALE, conf->player.pos.y * MINIMAP_SCALE, PLAYER_SIZE / 2, 0x00FF0000);
	line_pixel_put(&conf->screen, &conf->player, conf->player.angle, 30, 0x00FF0000);

}

void render_map(char **map, t_conf *conf)
{
	size_t	y;
	size_t	x;
	
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				squre_pixel_put(&conf->screen, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, 0xFFFFFF);
			else if (map[y][x] == '0')
				squre_pixel_put(&conf->screen, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, 0x000000);
			x++;
		}
		y++;
	}
}

void set_facing_to(t_ray *ray)
{
	if (ray->angle > 0 && ray->angle <= M_PI / 2)
		ray->facing_to = DOWN | RIGHT;
	if (ray->angle > M_PI / 2 && ray->angle <= M_PI)
		ray->facing_to = DOWN | LEFT;
	if (ray->angle > M_PI && ray->angle <= M_PI * 3 / 2)
		ray->facing_to = UP | LEFT;
	if (ray->angle >= M_PI * 3 / 2 && ray->angle <= M_PI * 2)
		ray->facing_to = UP | RIGHT;	
}

double distance_between_points(t_point start, t_point end)
{
	return sqrt((end.x - start.x) * (end.x - start.x) + (end.y - start.y) * (end.y - start.y));
}

void clear_color_buffer(t_conf *conf, uint32_t color)
{
	int x;
	int y;

	x = 0;
	while(x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			conf->color_buffer[(WINDOW_WIDTH * y) + x] = color;
			y++;
		}
		x++;
	}
}

void render_color_buffer(t_conf *conf)
{
	int x;
	int y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while(y < WINDOW_HEIGHT)
		{
			my_mlx_pixel_put(&conf->screen, x, y, conf->color_buffer[(WINDOW_WIDTH * y) + x]);
			y++;
		}
		x++;
	}
}

void set_horz_intercepts(t_ray *ray, const t_player player)
{
	ray->intercept.y = floor(player.pos.y / TILE_SIZE) * TILE_SIZE;
	if (ray->facing_to & DOWN)
		ray->intercept.y += TILE_SIZE;
	ray->intercept.x = player.pos.x + (ray->intercept.y - player.pos.y) / tan(ray->angle);
}

void set_horz_steps(t_ray *ray)
{
	ray->ystep = TILE_SIZE;
	if (ray->facing_to & UP)
		ray->ystep *= -1;

	ray->xstep = TILE_SIZE / tan(ray->angle);
	if ((ray->facing_to & LEFT) && ray->xstep > 0)
		ray->xstep *= -1;
	if ((ray->facing_to & RIGHT) && ray->xstep < 0)
		ray->xstep *= -1;
}

void set_horz_wall_hit(const t_map map, t_ray *ray)
{
	t_point next;
	t_point to_check;

	next.x = ray->intercept.x;
	next.y = ray->intercept.y;
	while (next.x >= 0 && next.x <= WINDOW_WIDTH && next.y >= 0 && next.y <= WINDOW_HEIGHT)
	{
		to_check.x = next.x;
		to_check.y = next.y;
		if (ray->facing_to & UP)
			to_check.y--;
		if (has_wall_at(map, to_check.x, to_check.y))
		{
			ray->found_horz_wall_hit = true;
			ray->horz_wall_hit.x = next.x;
			ray->horz_wall_hit.y = next.y;
			break;
		}
		else
		{
			next.x += ray->xstep;
			next.y += ray->ystep;
		}
	}
}

t_point find_horz_wall(t_conf *conf, t_ray *ray, const t_player player)
{
	ray->found_horz_wall_hit = 0;
	ray->horz_wall_hit.x = 0;
	ray->horz_wall_hit.y = 0;
	set_facing_to(ray);
	set_horz_intercepts(ray, player);
	set_horz_steps(ray);
	set_horz_wall_hit(conf->map, ray);
	return (ray->horz_wall_hit);
}

void set_vert_intercepts(t_ray *ray, const t_player player)
{
	ray->intercept.x = floor(player.pos.x / TILE_SIZE) * TILE_SIZE;
	if (ray->facing_to & RIGHT)
		ray->intercept.x += TILE_SIZE;
	ray->intercept.y = player.pos.y + (ray->intercept.x - player.pos.x) * tan(ray->angle);
}

void set_vert_steps(t_ray *ray)
{
	ray->xstep = TILE_SIZE;
	if (ray->facing_to & LEFT)
		ray->xstep *= -1;

	ray->ystep = TILE_SIZE * tan(ray->angle);
	if ((ray->facing_to & UP) && ray->ystep > 0)
		ray->ystep *= -1;
	if ((ray->facing_to & DOWN) && ray->ystep < 0)
		ray->ystep *= -1;
}

void set_vert_wall_hit(const t_map map, t_ray *ray)
{
	t_point next;
	t_point to_check;

	next.x = ray->intercept.x;
	next.y = ray->intercept.y;
	while (next.x >= 0 && next.x <= WINDOW_WIDTH && next.y >= 0 && next.y <= WINDOW_HEIGHT)
	{
		to_check.x = next.x;
		to_check.y = next.y;
		if (ray->facing_to & LEFT)
			to_check.x--;
		if (has_wall_at(map, to_check.x, to_check.y))
		{
			ray->found_vert_wall_hit = true;
			ray->vert_wall_hit.x = next.x;
			ray->vert_wall_hit.y = next.y;
			break;
		}
		else
		{
			next.x += ray->xstep;
			next.y += ray->ystep;
		}
	}
}

t_point find_vert_wall(t_conf *conf, t_ray *ray, const t_player player)
{
	ray->found_vert_wall_hit = 0;
	ray->vert_wall_hit.x = 0;
	ray->vert_wall_hit.y = 0;
	set_facing_to(ray);
	set_vert_intercepts(ray, player);
	set_vert_steps(ray);
	set_vert_wall_hit(conf->map, ray);
	return (ray->vert_wall_hit);
}

void set_horz_distance(t_ray *ray, const t_player player)
{
	if (ray->found_horz_wall_hit)	
		ray->horz_distance = distance_between_points(player.pos, ray->horz_wall_hit);
	else
		ray->horz_distance = INT_MAX;
}

void set_vert_distance(t_ray *ray, const t_player player)
{
	if (ray->found_vert_wall_hit)
		ray->vert_distance = distance_between_points(player.pos, ray->vert_wall_hit);
	else
		ray->vert_distance = INT_MAX;
}

void set_wall_hit(t_ray *ray)
{
	if (ray->vert_distance < ray->horz_distance)
	{
		ray->wall_hit = ray->vert_wall_hit;
		ray->distance = ray->vert_distance;
		ray->was_hit_vertical = true;	
	}
	else
	{
		ray->wall_hit = ray->horz_wall_hit;
		ray->distance = ray->horz_distance;
	}	
}

void set_each_ray(t_conf *conf, t_ray *ray, const t_player player)
{
	ray->horz_wall_hit = find_horz_wall(conf, ray, player);
	ray->vert_wall_hit = find_vert_wall(conf, ray, player); 
	//initialize
	ray->was_hit_vertical = false;

	set_horz_distance(ray, player);
	set_vert_distance(ray, player);
	set_wall_hit(ray);
}

void set_rays(t_conf *conf) {
	double rayAngle = conf->player.angle - (FOV_ANGLE / 2);
	rayAngle = normalize_angle(rayAngle);

	int strip_id = 0;
	while (strip_id < NUM_RAYS)
	{
		conf->rays[strip_id].angle = rayAngle;
		set_each_ray(conf, &(conf->rays[strip_id]), conf->player);
		rayAngle += FOV_ANGLE / NUM_RAYS;
		rayAngle = normalize_angle(rayAngle);
		strip_id++;
	}
}

void render_rays(t_conf *conf)
{
	double rayAngle = conf->player.angle - (FOV_ANGLE / 2);
	rayAngle = normalize_angle(rayAngle);

	int strip_id = 0;
	while (strip_id < NUM_RAYS)
	{
		conf->rays[strip_id].angle = rayAngle;
		line_pixel_put_2(&conf->screen, conf->player, conf->player.pos, conf->rays[strip_id].wall_hit, 0x00FFFF00);
		rayAngle += FOV_ANGLE / NUM_RAYS;
		rayAngle = normalize_angle(rayAngle);
		strip_id++;
	}
}

void rect_pixel_put(t_data *screen, t_point start, double width, double height, int color)
{
	int i;
	int j;

	i = start.y;
	while (i < start.y + height)
	{
		j = start.x;
		while(j < start.x + width)
		{
			my_mlx_pixel_put(screen, j, i, color);
			j++;
		}
		i++;
	}
}

void set_ceiling_color(t_conf *conf, const t_3d info_3d, int *i)
{
	int y;

	y = 0;
	while (y < info_3d.wall_top)
	{
		conf->color_buffer[(WINDOW_WIDTH * y) + *i] = 0xFF333333;
		y++;
	}
}

void set_wall_color(t_conf *conf, const t_3d info_3d, int *i)
{
	int y;
	y = info_3d.wall_top;
	while (y < info_3d.wall_bottom)
	{
		if (conf->rays[*i].was_hit_vertical)
           	conf->color_buffer[(WINDOW_WIDTH * y) + *i] = 0xFFFFFFFF;
		else
           	conf->color_buffer[(WINDOW_WIDTH * y) + *i] = 0xFFCCCCCC;
		y++;
	}
}

void set_floor_color(t_conf *conf, const t_3d info_3d, int *i)
{
	int y;

	y = info_3d.wall_bottom;
	while (y < WINDOW_HEIGHT)
	{
		conf->color_buffer[(WINDOW_WIDTH * y) + *i] = 0xFF777777;
		y++;
	}

}

void render_3d_walls(t_conf *conf)
{
	int i;	
	t_3d info_3d;

	//initialize	
	info_3d.distance_to_projection = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		info_3d.prep_distance = conf->rays[i].distance * cos(conf->rays[i].angle - conf->player.angle);
		info_3d.wall_strip_height = (TILE_SIZE / info_3d.prep_distance) * info_3d.distance_to_projection;
		info_3d.wall_top = (WINDOW_HEIGHT / 2) - (info_3d.wall_strip_height / 2);
		if (info_3d.wall_top < 0)
			info_3d.wall_top = 0;
		info_3d.wall_bottom = (WINDOW_HEIGHT / 2) + (info_3d.wall_strip_height / 2);
		if (info_3d.wall_bottom > WINDOW_HEIGHT)
			info_3d.wall_bottom = WINDOW_HEIGHT;
		set_ceiling_color(conf, info_3d, &i);
		set_wall_color(conf, info_3d, &i);
		set_floor_color(conf, info_3d, &i);	
		i++;
	}
	render_color_buffer(conf);
}

void render(t_conf *conf)
{
	conf->screen.img = mlx_new_image(conf->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	conf->screen.addr = mlx_get_data_addr(conf->screen.img, &conf->screen.bits_per_pixel, &conf->screen.line_length,
								&conf->screen.endian);

	render_3d_walls(conf);
	render_map(conf->map.map, conf);
	render_rays(conf);
	render_player(conf);	
	mlx_put_image_to_window(conf->mlx_ptr, conf->win_ptr, conf->screen.img, 0, 0);
}



void move_player(const t_map map, t_player *player, double newDestX, double newDestY)
{
	if (!has_wall_at(map, newDestX, newDestY))
	{
		player->pos.x = newDestX;
		player->pos.y = newDestY;
	}
}

int deal_key(int key, t_conf *conf)
{
	if (key == A_KEY)
		move_player(conf->map, &conf->player, conf->player.pos.x + PLAYER_SIZE * cos(normalize_angle(conf->player.angle - M_PI / 2)), conf->player.pos.y + PLAYER_SIZE * sin(normalize_angle(conf->player.angle - M_PI / 2)));
	else if (key == D_KEY)
		move_player(conf->map, &conf->player, conf->player.pos.x + PLAYER_SIZE * cos(normalize_angle(conf->player.angle + M_PI / 2)), conf->player.pos.y + PLAYER_SIZE * sin(normalize_angle(conf->player.angle + M_PI / 2)));
	else if (key == W_KEY)
		move_player(conf->map, &conf->player, conf->player.pos.x + PLAYER_SIZE * cos(conf->player.angle), conf->player.pos.y + PLAYER_SIZE * sin(conf->player.angle));
	else if (key == S_KEY)
		move_player(conf->map, &conf->player, conf->player.pos.x - PLAYER_SIZE * cos(conf->player.angle), conf->player.pos.y - PLAYER_SIZE * sin(conf->player.angle));
	else if (key == LEFT_KEY)
	{
		conf->player.angle -= M_PI * ROTATE_SPEED;
		conf->player.angle = normalize_angle(conf->player.angle);	
		conf->player.pdx = cos(conf->player.angle);
		conf->player.pdy = sin(conf->player.angle);
	}
	else if (key == RIGHT_KEY)
	{
		conf->player.angle += M_PI * ROTATE_SPEED;
		conf->player.angle = normalize_angle(conf->player.angle);		
		conf->player.pdx = cos(conf->player.angle);
		conf->player.pdy = sin(conf->player.angle);
	}
	set_rays(conf);
	render(conf);
    return (0);
}

void init_conf(t_conf *conf)
{
	*conf = (t_conf){};
	conf->player.pos.x = 80;
	conf->player.pos.y = 80;
	conf->color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * WINDOW_WIDTH * WINDOW_HEIGHT);
}


void	map_check(char **map, t_conf *conf)
{
	rectangular_check(map, conf);
	wall_check(map, conf);
	array_loop(map, conf, invalid_char_check);
	array_loop(map, conf, inmap_char_count);
	//n_char_check(map, conf);
}


char	**map_set(char *mapfile, t_conf *conf)
{
	int		fd;
	t_list	*buf;

	buf = NULL;
	fd = ft_open_readfile(mapfile);
	conf->map.height = fd_to_lst(fd, &buf);
	size_check(conf);
	return (lst_to_array(buf, conf->map.height));
}

void exit_tmp(t_conf *conf)
{
	(void)conf;
	free(conf->color_buffer);
	exit(0);
}


int main(int ac, char *av[])
{
	t_conf conf; 

	args_check(ac, av);
	init_conf(&conf);
    conf.mlx_ptr = mlx_init();
    conf.win_ptr = mlx_new_window(conf.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	conf.map.map = map_set(av[1], &conf);
	map_check(conf.map.map, &conf);
	set_rays(&conf);
	render(&conf);
    mlx_hook(conf.win_ptr, 2, 1L << 0, deal_key, &conf);
    mlx_loop(conf.mlx_ptr);
}
