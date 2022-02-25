#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

void circle_pixel_put(t_data *screen, unsigned int px, unsigned int py, int radius, int color)
{
	unsigned int x;
	unsigned int y;
	int dx;
	int dy;

	y = 0;
	while(y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
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

void line_pixel_put(t_data *screen, t_player *player, double angle, int color)
{
	int x;
	int y;
	int len;

	//need to change this len max 
	//if you rotate a lot, segmentation fault
	for (len = 0; len < 50; len++)
	{
		x = player->pos.x * MINIMAP_SCALE + len * cos(angle);
		y = player->pos.y * MINIMAP_SCALE + len * sin(angle);
		my_mlx_pixel_put(screen, x, y, color);
	}
}

void renderPlayer(t_conf *conf)
{
	circle_pixel_put(&conf->screen, conf->player.pos.x * MINIMAP_SCALE, conf->player.pos.y * MINIMAP_SCALE, PLAYER_SIZE / 2, 0x00FF0000);
	line_pixel_put(&conf->screen, &conf->player, conf->player.angle, 0x00FF0000);

}

void renderMap(char **map, t_conf *conf)
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

void castRay(t_conf *conf, double angle)
{

	line_pixel_put(&conf->screen, &conf->player, angle, 0x00FFFF00);

}


void castAllRays(t_conf *conf) {
	double rayAngle = conf->player.angle - (FOV_ANGLE / 2);
	t_ray rays[NUM_RAYS];

	int stripId = 0;
	while (stripId < NUM_RAYS)
	{
		rayAngle += FOV_ANGLE / NUM_RAYS;
		rays[stripId]->rayAngle = rayAngle;
		castRay(conf, rays[stripId]->rayAngle);
		stripId++;
	}
}


void render(t_conf *conf)
{
	conf->screen.img = mlx_new_image(conf->mlx_ptr, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	conf->screen.addr = mlx_get_data_addr(conf->screen.img, &conf->screen.bits_per_pixel, &conf->screen.line_length,
								&conf->screen.endian);

	renderMap(conf->map.map, conf);
	renderPlayer(conf);
	castAllRays(conf);

	mlx_put_image_to_window(conf->mlx_ptr, conf->win_ptr, conf->screen.img, 0, 0);
}

bool hasWallAt(char **map, int x, int y)
{
	int mapIndexX = x / TILE_SIZE;
	int mapIndexY = y / TILE_SIZE;

	return map[mapIndexY][mapIndexX] != '0';
}

int deal_key(int key, t_conf *conf)
{
	if (key == A_KEY)
	{
		//I don't understand why it works with 2 multiple
		if (!hasWallAt(conf->map.map, conf->player.pos.x - PLAYER_SIZE * 2, conf->player.pos.y))
			conf->player.pos.x -= PLAYER_SIZE;
	}
	else if (key == D_KEY)
	{
		if (!hasWallAt(conf->map.map, conf->player.pos.x + PLAYER_SIZE, conf->player.pos.y))
			conf->player.pos.x += PLAYER_SIZE;
	}
	else if (key == W_KEY)
	{
		//I don't understand why it works with 2 multiple
		if (!hasWallAt(conf->map.map, conf->player.pos.x, conf->player.pos.y - PLAYER_SIZE * 2))
			conf->player.pos.y -= PLAYER_SIZE;
	}
	else if (key == S_KEY)
	{
		if (!hasWallAt(conf->map.map, conf->player.pos.x, conf->player.pos.y + PLAYER_SIZE))
			conf->player.pos.y += PLAYER_SIZE;
	}
	else if (key == LEFT_KEY)
	{
		conf->player.angle -= 0.1;
		if (conf->player.angle < 0)
		{
			conf->player.angle += 2 * M_PI;
		}
		conf->player.pdx = cos(conf->player.angle) * 5;
		conf->player.pdy = sin(conf->player.angle) * 5;
		printf("angle: %f\n", conf->player.angle);
		printf("pdx: %f\n", conf->player.pdx);
		printf("pdy: %f\n", conf->player.pdy);
	}
	else if (key == RIGHT_KEY)
	{
		conf->player.angle += 0.1;
		if (conf->player.angle > 2 * M_PI)
		{
			conf->player.angle -= 2 * M_PI;
		}
		conf->player.pdx = cos(conf->player.angle) * 5;
		conf->player.pdy = sin(conf->player.angle) * 5;
		printf("angle: %f\n", conf->player.angle);
		printf("pdx: %f\n", conf->player.pdx);
		printf("pdy: %f\n", conf->player.pdy);
	}
	render(conf);
    return (0);
}

void init_conf(t_conf *conf)
{
	*conf = (t_conf){};
	conf->player.pos.x = 80;
	conf->player.pos.y = 80;
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
	render(&conf);
    mlx_hook(conf.win_ptr, 2, 1L << 0, deal_key, &conf);
    mlx_loop(conf.mlx_ptr);
}
