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

	i = px;
	while (i < px + size)
	{
		j = py;
		while(j < py + size)
		{
			my_mlx_pixel_put(screen, i, j, color);
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

void line_pixel_put(t_data *screen, t_ppos *ppos, int color)
{
	int x;
	int y;
	int len;

	for (len = 0; len < 30; len++)
	{
		x = ppos->px + len * cos(ppos->pa);
		y = ppos->py + len * sin(ppos->pa);

		my_mlx_pixel_put(screen, x, y, color);
	}
}

void putPlayer(t_conf *conf)
{
	circle_pixel_put(&conf->screen, conf->ppos.px, conf->ppos.py, 3, 0x00FF0000);
	line_pixel_put(&conf->screen, &conf->ppos, 0x00FF0000);

}

void putMap(char **map, t_conf *conf)
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
				squre_pixel_put(&conf->screen, x * CHIP_SIZE, y * CHIP_SIZE, CHIP_SIZE, 0xFFFFFF);
			else if (map[y][x] == '0')
				squre_pixel_put(&conf->screen, x * CHIP_SIZE, y * CHIP_SIZE, CHIP_SIZE, 0x000000);
			x++;
		}
		y++;
	}

}


void drawMinimap(t_conf *conf)
{
	conf->screen.img = mlx_new_image(conf->mlx_ptr, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	conf->screen.addr = mlx_get_data_addr(conf->screen.img, &conf->screen.bits_per_pixel, &conf->screen.line_length,
								&conf->screen.endian);
	putMap(conf->map.map, conf);
	putPlayer(conf);

	mlx_put_image_to_window(conf->mlx_ptr, conf->win_ptr, conf->screen.img, 0, 0);
}

bool hasWallAt(char **map, int x, int y)
{
	int mapIndexX = x / CHIP_SIZE;
	int mapIndexY = y / CHIP_SIZE;

	return map[mapIndexY][mapIndexX] != '0';
}

int deal_key(int key, t_conf *conf)
{
	if (key == A_KEY)
	{
		if (!hasWallAt(conf->map.map, conf->ppos.px - PLAYER_SIZE, conf->ppos.py))
			conf->ppos.px -= PLAYER_SIZE;
	}
	else if (key == D_KEY)
	{
		if (!hasWallAt(conf->map.map, conf->ppos.px + PLAYER_SIZE, conf->ppos.py))
			conf->ppos.px += PLAYER_SIZE;
	}
	else if (key == W_KEY)
	{
		if (!hasWallAt(conf->map.map, conf->ppos.px, conf->ppos.py - PLAYER_SIZE))
			conf->ppos.py -= PLAYER_SIZE;
	}
	else if (key == S_KEY)
	{
		if (!hasWallAt(conf->map.map, conf->ppos.px, conf->ppos.py + PLAYER_SIZE))
			conf->ppos.py += PLAYER_SIZE;
	}
	else if (key == LEFT_KEY)
	{
		conf->ppos.pa -= 0.1;
		if (conf->ppos.pa < 0)
		{
			conf->ppos.pa += 2 * PI;
		}
		conf->ppos.pdx = cos(conf->ppos.pa) * 5;
		conf->ppos.pdy = sin(conf->ppos.pa) * 5;
		printf("pa: %f\n", conf->ppos.pa);
		printf("pdx: %f\n", conf->ppos.pdx);
		printf("pdy: %f\n", conf->ppos.pdy);
	}
	else if (key == RIGHT_KEY)
	{
		conf->ppos.pa += 0.1;
		if (conf->ppos.pa > 2 * PI)
		{
			conf->ppos.pa -= 2 * PI;
		}
		conf->ppos.pdx = cos(conf->ppos.pa) * 5;
		conf->ppos.pdy = sin(conf->ppos.pa) * 5;
		printf("pa: %f\n", conf->ppos.pa);
		printf("pdx: %f\n", conf->ppos.pdx);
		printf("pdy: %f\n", conf->ppos.pdy);
	}
	drawMinimap(conf);
    return (0);
}

void init_conf(t_conf *conf)
{
	*conf = (t_conf){};
	conf->ppos.px = 160;
	conf->ppos.py = 160;
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

int main(int ac, char *av[])
{
	t_conf conf; 

	args_check(ac, av);
	init_conf(&conf);
    conf.mlx_ptr = mlx_init();
    conf.win_ptr = mlx_new_window(conf.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	conf.map.map = map_set(av[1], &conf);
	map_check(conf.map.map, &conf);
	drawMinimap(&conf);
    mlx_hook(conf.win_ptr, 2, 1L << 0, deal_key, &conf);
    mlx_loop(conf.mlx_ptr);
}
