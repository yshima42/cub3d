#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, size_t x, size_t y, size_t color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

bool has_wall_at(t_map map, double x, double y)
{
	if (x < 0 || x > ((int)map.width * TILE_SIZE) || y < 0 || y > ((int)map.height * TILE_SIZE)) 
        return true;
	size_t mapIndexX = floor(x / TILE_SIZE);
	size_t mapIndexY = floor(y / TILE_SIZE);
	return map.map[mapIndexY][mapIndexX] != '0';
}

void squre_pixel_put(t_data *screen, size_t px, size_t py, size_t size, size_t color)
{
	size_t i;
	size_t j;
	size_t c_color;

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

void circle_pixel_put(t_data *screen, t_xy pos, size_t radius, size_t color)
{
	size_t x;
	size_t y;
	size_t dx;
	size_t dy;

	y = pos.y - radius;
	while(y < pos.y + radius)
	{
		x = pos.x - radius;
		while (x < pos.x + radius)
		{
			dx = x - pos.x;
			dy = y - pos.y;
			if ((dx * dx) + (dy * dy) <= radius * radius)
			{
				my_mlx_pixel_put(screen, x, y, color);
			}
			x++;
		}
		y++;
	}
}

void line_pixel_put(t_data *screen, t_xy pos, double angle, double len, size_t color)
{
	size_t x;
	size_t y;
	double i;
	for (i = 0; i < len; i++)
	{
		x = pos.x * MINIMAP_SCALE + i * cos(angle);
		y = pos.y * MINIMAP_SCALE + i * sin(angle);
		my_mlx_pixel_put(screen, x, y, color);
	}
}

void line_pixel_put_2(t_data *screen, t_player player, t_xy start, t_xy end, size_t color)
{
	t_xy	line;
	t_xy	dist;
	size_t	len;
	double	rad;
	size_t	i;

	dist.x = end.x - start.x;
	dist.y = end.y - start.y;
	len = sqrt(dist.x * dist.x + dist.y * dist.y);
	rad = atan2(dist.y, dist.x);
	i = 0;
	while (i < len)
	{
		line.x = player.pos.x * MINIMAP_SCALE + i * cos(rad);
		line.y = player.pos.y * MINIMAP_SCALE + i * sin(rad);
		my_mlx_pixel_put(screen, line.x, line.y, color);
		i++;
	}
}

void render_player(t_data *screen, const t_player player)
{
	circle_pixel_put(screen, player.pos, PLAYER_SIZE / 2, 0x00FF0000);
	line_pixel_put(screen, player.pos, player.angle, 30, 0x00FF0000);
}

void render_map(t_data *screen, char **map)
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
				squre_pixel_put(screen, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, 0xFFFFFF);
			else if (map[y][x] == '0')
				squre_pixel_put(screen, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, 0x000000);
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

double distance_between_points(t_xy start, t_xy end)
{
	return sqrt((end.x - start.x) * (end.x - start.x) + (end.y - start.y) * (end.y - start.y));
}

void clear_color_buffer(t_conf *conf, size_t color)
{
	size_t x;
	size_t y;

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
	size_t x;
	size_t y;

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

t_xy calc_horz_intercept(t_ray *ray, const t_player player)
{
	t_xy intercept;

	intercept.y = floor(player.pos.y / TILE_SIZE) * TILE_SIZE;
	if (ray->facing_to & DOWN)
		intercept.y += TILE_SIZE;
	intercept.x = player.pos.x + (intercept.y - player.pos.y) / tan(ray->angle);
	return (intercept);
}

t_xy calc_horz_step(t_ray *ray)
{
	t_xy	step;

	step.y = TILE_SIZE;
	if (ray->facing_to & UP)
		step.y *= -1;

	step.x = TILE_SIZE / tan(ray->angle);
	if ((ray->facing_to & LEFT) && step.x > 0)
		step.x *= -1;
	if ((ray->facing_to & RIGHT) && step.x < 0)
		step.x *= -1;
	return (step);
}

t_xy calc_horz_wall_hit(const t_map map, t_ray *ray, t_xy step, t_xy intercept)
{
	t_xy horz_wall_hit;
	t_xy to_check;

	horz_wall_hit.x = 0;
	horz_wall_hit.y = 0;
	while (intercept.x >= 0 && intercept.x <= WINDOW_WIDTH && intercept.y >= 0 && intercept.y <= WINDOW_HEIGHT)
	{
		to_check.x = intercept.x;
		to_check.y = intercept.y;
		if (ray->facing_to & UP)
			to_check.y--;
		if (has_wall_at(map, to_check.x, to_check.y))
		{
			ray->found_horz_wall_hit = true;
			horz_wall_hit.x = intercept.x;
			horz_wall_hit.y = intercept.y;
			break;
		}
		else
		{
			intercept.x += step.x;
			intercept.y += step.y;
		}
	}
	return (horz_wall_hit);
}

t_xy find_horz_wall(t_conf *conf, t_ray *ray, const t_player player)
{
	//initialize
	ray->found_horz_wall_hit = 0;
	t_xy	horz_wall_hit;	
	t_xy	step;
	t_xy	intercept;

	set_facing_to(ray);
	intercept = calc_horz_intercept(ray, player);
	step = calc_horz_step(ray);
	horz_wall_hit = calc_horz_wall_hit(conf->map, ray, step, intercept);
	return (horz_wall_hit);
}

t_xy calc_vert_intercept(t_ray *ray, const t_player player)
{
	t_xy	intercept;

	intercept.x = floor(player.pos.x / TILE_SIZE) * TILE_SIZE;
	if (ray->facing_to & RIGHT)
		intercept.x += TILE_SIZE;
	intercept.y = player.pos.y + (intercept.x - player.pos.x) * tan(ray->angle);
	return(intercept);
}

t_xy calc_vert_step(t_ray *ray)
{
	t_xy	step;

	step.x = TILE_SIZE;
	if (ray->facing_to & LEFT)
		step.x *= -1;
	step.y = TILE_SIZE * tan(ray->angle);
	if ((ray->facing_to & UP) && step.y > 0)
		step.y *= -1;
	if ((ray->facing_to & DOWN) && step.y < 0)
		step.y *= -1;
	return (step);
}

t_xy calc_vert_wall_hit(const t_map map, t_ray *ray, t_xy step, t_xy intercept)
{
	t_xy	to_check;
	t_xy	vert_wall_hit;

	vert_wall_hit.x = 0;
	vert_wall_hit.y = 0;
	while (intercept.x >= 0 && intercept.x <= WINDOW_WIDTH && intercept.y >= 0 && intercept.y <= WINDOW_HEIGHT)
	{
		to_check.x = intercept.x;
		to_check.y = intercept.y;
		if (ray->facing_to & LEFT)
			to_check.x--;
		if (has_wall_at(map, to_check.x, to_check.y))
		{
			ray->found_vert_wall_hit = true;
			vert_wall_hit.x = intercept.x;
			vert_wall_hit.y = intercept.y;
			break;
		}
		else
		{
			intercept.x += step.x;
			intercept.y += step.y;
		}
	}
	return (vert_wall_hit);
}

t_xy find_vert_wall(t_conf *conf, t_ray *ray, const t_player player)
{
	t_xy	vert_wall_hit;
	t_xy	step;
	t_xy	intercept;

	ray->found_vert_wall_hit = 0;
	set_facing_to(ray);
	intercept = calc_vert_intercept(ray, player);
	step = calc_vert_step(ray);
	vert_wall_hit = calc_vert_wall_hit(conf->map, ray, step, intercept);
	return (vert_wall_hit);
}

double calc_horz_distance(t_ray *ray, const t_player player, t_xy horz_wall_hit)
{
	double	horz_distance;

	if (ray->found_horz_wall_hit)	
		horz_distance = distance_between_points(player.pos, horz_wall_hit);
	else
		horz_distance = INT_MAX;
	return (horz_distance);
}

double calc_vert_distance(t_ray *ray, const t_player player, t_xy vert_wall_hit)
{
	double	vert_distance;

	if (ray->found_vert_wall_hit)
		vert_distance = distance_between_points(player.pos, vert_wall_hit);
	else
		vert_distance = INT_MAX;
	return (vert_distance);
}

void set_wall_hit(t_ray *ray, t_xy horz_wall_hit, t_xy vert_wall_hit, double horz_distance, double vert_distance)
{
	if (vert_distance < horz_distance)
	{
		ray->wall_hit_pos = vert_wall_hit;
		ray->distance = vert_distance;
		ray->was_hit_vertical = true;	
	}
	else
	{
		ray->wall_hit_pos = horz_wall_hit;
		ray->distance = horz_distance;
	}	
}

void set_each_ray(t_conf *conf, t_ray *ray, const t_player player)
{
	t_xy	horz_wall_hit;
	t_xy	vert_wall_hit;
	double	horz_distance;
	double	vert_distance;
	
	//initialize
	ray->was_hit_vertical = false;
	horz_wall_hit = find_horz_wall(conf, ray, player);
	vert_wall_hit = find_vert_wall(conf, ray, player); 
	horz_distance = calc_horz_distance(ray, player, horz_wall_hit);
	vert_distance = calc_vert_distance(ray, player, vert_wall_hit);
	set_wall_hit(ray, horz_wall_hit, vert_wall_hit, horz_distance, vert_distance);
}

void set_rays(t_conf *conf) {
	double ray_angle;
	size_t strip_id;

	ray_angle = normalize_angle(conf->player.angle - (FOV_ANGLE / 2));
	strip_id = 0;
	while (strip_id < NUM_RAYS)
	{
		conf->rays[strip_id].angle = ray_angle;
		set_each_ray(conf, &(conf->rays[strip_id]), conf->player);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		ray_angle = normalize_angle(ray_angle);
		strip_id++;
	}
}

void render_rays(t_data *screen, t_player player, t_ray *rays)
{
	double ray_angle;
	size_t strip_id;

	ray_angle = normalize_angle(player.angle - (FOV_ANGLE / 2));
	strip_id = 0;
	while (strip_id < NUM_RAYS)
	{
		rays[strip_id].angle = ray_angle;
		line_pixel_put_2(screen, player, player.pos, rays[strip_id].wall_hit_pos, 0x00FFFF00);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		ray_angle = normalize_angle(ray_angle);
		strip_id++;
	}
}

void rect_pixel_put(t_data *screen, t_xy start, double width, double height, size_t color)
{
	size_t i;
	size_t j;

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

void set_ceiling_color(t_conf *conf, const t_3d info_3d, size_t *i)
{
	size_t y;

	y = 0;
	while (y < info_3d.wall_top)
	{
		conf->color_buffer[(WINDOW_WIDTH * y) + *i] = 0xFF333333;
		y++;
	}
}

void set_wall_color(t_conf *conf, const t_3d info_3d, size_t *i)
{
	size_t y;
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

void set_floor_color(t_conf *conf, const t_3d info_3d, size_t *i)
{
	size_t y;

	y = info_3d.wall_bottom;
	while (y < WINDOW_HEIGHT)
	{
		conf->color_buffer[(WINDOW_WIDTH * y) + *i] = 0xFF777777;
		y++;
	}

}

void render_3d_walls(t_conf *conf)
{
	size_t i;	
	double prep_distance;
	t_3d info_3d;

	i = 0;
	while (i < NUM_RAYS)
	{
		prep_distance = conf->rays[i].distance * cos(conf->rays[i].angle - conf->player.angle);
		info_3d.wall_strip_height = (TILE_SIZE / prep_distance) * DIST_TO_PROJECTION;
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
	render_map(&conf->screen, conf->map.map);
	render_rays(&conf->screen, conf->player, conf->rays);
	render_player(&conf->screen, conf->player);	
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
	conf->color_buffer = (size_t *)malloc(sizeof(size_t) * WINDOW_WIDTH * WINDOW_HEIGHT);
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
