/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_vert.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:08:58 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/03 18:28:10 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"

t_xy_double	calc_vert_intercept(t_ray *ray, const t_player player)
{
	t_xy_double	intercept;

	intercept.x = floor(player.pos.x / TILE_SIZE) * TILE_SIZE;
	if (ray->facing_to & RIGHT)
		intercept.x += TILE_SIZE;
	intercept.y = player.pos.y + (intercept.x - player.pos.x) * tan(ray->angle);
	return (intercept);
}

t_xy_double	calc_vert_step(t_ray *ray)
{
	t_xy_double	step;

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

t_xy_double	calc_vert_wall_hit(const t_map map, t_ray *ray, t_xy_double step, t_xy_double intercept)
{
	t_xy_double	to_check;
	t_xy_double	vert_wall_hit;

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
			break ;
		}
		else
		{
			intercept.x += step.x;
			intercept.y += step.y;
		}
	}
	return (vert_wall_hit);
}

t_xy_double	find_vert_wall(t_conf *conf, t_ray *ray, const t_player player)
{
	t_xy_double	vert_wall_hit;
	t_xy_double	step;
	t_xy_double	intercept;

	ray->found_vert_wall_hit = 0;
	set_facing_to(ray);
	intercept = calc_vert_intercept(ray, player);
	step = calc_vert_step(ray);
	vert_wall_hit = calc_vert_wall_hit(conf->map, ray, step, intercept);
	return (vert_wall_hit);
}

double	calc_vert_distance(t_ray *ray, const t_player player, t_xy_double vert_wall_hit)
{
	double	vert_distance;

	if (ray->found_vert_wall_hit)
		vert_distance = distance_between_points(player.pos, vert_wall_hit);
	else
		vert_distance = INT_MAX;
	return (vert_distance);
}
