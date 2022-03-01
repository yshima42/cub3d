#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"

void print_pos(t_player player)
{
	printf("x: %f\n", player.pos.x);
	printf("y: %f\n", player.pos.y);
}

void print_angle(t_conf *conf)
{
	printf("angle: %f\n", conf->player.angle);
	printf("pdx: %f\n", conf->player.pdx);
	printf("pdy: %f\n", conf->player.pdy);
}