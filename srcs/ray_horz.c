/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_horz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:09:02 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/04 13:03:30 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"

t_xy_d	calc_horz_intercept(t_ray *ray, const t_player player)
{
	t_xy_d	intercept;

	intercept.y = floor(player.pos.y / TILE_SIZE) * TILE_SIZE;
	if (ray->facing_to & DOWN)
		intercept.y += TILE_SIZE;
	intercept.x = player.pos.x + (intercept.y - player.pos.y) / tan(ray->angle);
	return (intercept);
}

t_xy_d	calc_horz_step(t_ray *ray)
{
	t_xy_d	step;

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

t_xy_d	calc_horz_wall_hit(const t_map map, t_ray *ray,
	t_xy_d step, t_xy_d intercept)
{
	t_xy_d	horz_wall_hit;
	t_xy_d	to_check;

	horz_wall_hit.x = 0;
	horz_wall_hit.y = 0;
	while (intercept.x >= 0 && intercept.x <= WINDOW_WIDTH
		&& intercept.y >= 0 && intercept.y <= WINDOW_HEIGHT)
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
			break ;
		}
		else
		{
			intercept.x += step.x;
			intercept.y += step.y;
		}
	}
	return (horz_wall_hit);
}

t_xy_d	find_horz_wall(t_conf *conf, t_ray *ray, const t_player player)
{
	t_xy_d	horz_wall_hit;	
	t_xy_d	step;
	t_xy_d	intercept;

	ray->found_horz_wall_hit = 0;
	set_facing_to(ray);
	intercept = calc_horz_intercept(ray, player);
	step = calc_horz_step(ray);
	horz_wall_hit = calc_horz_wall_hit(conf->map, ray, step, intercept);
	return (horz_wall_hit);
}

double	calc_horz_distance(t_ray *ray, const t_player player,
	t_xy_d horz_wall_hit)
{
	double	horz_distance;

	if (ray->found_horz_wall_hit)
		horz_distance = distance_between_points(player.pos, horz_wall_hit);
	else
		horz_distance = INT_MAX;
	return (horz_distance);
}
