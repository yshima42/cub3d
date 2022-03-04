/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:56:20 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/04 00:58:39 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../includes/cub3d.h"

void	set_wall_hit(t_ray *ray, t_xy_d horz_wall_hit,
	t_xy_d vert_wall_hit, double horz_distance, double vert_distance)
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

void	set_each_ray(t_conf *conf, t_ray *ray, const t_player player)
{
	t_xy_d	horz_wall_hit;
	t_xy_d	vert_wall_hit;
	double	horz_distance;
	double	vert_distance;

	//initialize
	ray->was_hit_vertical = false;
	horz_wall_hit = find_horz_wall(conf, ray, player);
	vert_wall_hit = find_vert_wall(conf, ray, player);
	horz_distance = calc_horz_distance(ray, player, horz_wall_hit);
	vert_distance = calc_vert_distance(ray, player, vert_wall_hit);
	set_wall_hit(ray, horz_wall_hit, vert_wall_hit,
		horz_distance, vert_distance);
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

	mini_pos.x = player.pos.x;
	mini_pos.y = player.pos.y;	
	strip_id = 0;
	while (strip_id < NUM_RAYS)
	{
		mini_hit_pos.x = rays[strip_id].wall_hit_pos.x;
		mini_hit_pos.y = rays[strip_id].wall_hit_pos.y;
		line_pixel_put_2(screen, mini_pos, mini_hit_pos, 0x00FFFF00);
		strip_id++;
	}
}
