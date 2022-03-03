/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:39:55 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/03 18:34:52 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"

double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

void	set_facing_to(t_ray *ray)
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

double	distance_between_points(t_xy_double start, t_xy_double end)
{
	double	dist;

	dist = sqrt((end.x - start.x) * (end.x - start.x)
			+ (end.y - start.y) * (end.y - start.y));
	return (dist);
}
