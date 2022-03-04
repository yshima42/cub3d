/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:56:20 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/04 14:46:12 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"

void	set_wall_hit(t_ray *ray, t_xy_d horz_wall_hit,
	t_xy_d vert_wall_hit, t_xy_d dist)
{
	if (dist.y < dist.x)
	{
		ray->wall_hit_pos = vert_wall_hit;
		ray->distance = dist.y;
		ray->was_hit_vertical = true;
	}
	else
	{
		ray->wall_hit_pos = horz_wall_hit;
		ray->distance = dist.x;
	}	
}

void	set_each_ray(t_conf *conf, t_ray *ray, const t_player player)
{
	t_xy_d	horz_wall_hit;
	t_xy_d	vert_wall_hit;
	t_xy_d	dist;

	ray->was_hit_vertical = false;
	horz_wall_hit = find_horz_wall(conf, ray, player);
	vert_wall_hit = find_vert_wall(conf, ray, player);
	dist.x = calc_horz_distance(ray, player, horz_wall_hit);
	dist.y = calc_vert_distance(ray, player, vert_wall_hit);
	set_wall_hit(ray, horz_wall_hit, vert_wall_hit, dist);
}

void	set_rays(t_conf *conf)
{
	double	ray_angle;
	size_t	strip_id;

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

void	render_rays(t_data *screen, t_player player, t_ray *rays)
{
	size_t	strip_id;
	t_xy_d	mini_pos;
	t_xy_d	mini_hit_pos;

	mini_pos.x = player.pos.x * MINIMAP_SCALE;
	mini_pos.y = player.pos.y * MINIMAP_SCALE;
	strip_id = 0;
	while (strip_id < NUM_RAYS)
	{
		mini_hit_pos.x = rays[strip_id].wall_hit_pos.x * MINIMAP_SCALE;
		mini_hit_pos.y = rays[strip_id].wall_hit_pos.y * MINIMAP_SCALE;
		line_pixel_put_2(screen, mini_pos, mini_hit_pos, 0x00FFFF00);
		strip_id++;
	}
}
