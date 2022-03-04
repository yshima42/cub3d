/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:08:48 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/04 13:11:01 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# define MINIMAP_SCALE 1
# define TILE_SIZE 			32
# define SCREEN_SIZE 		20
# define PLAYER_SIZE 		8

# define FOV_ANGLE (60 * (M_PI / 180))
# define TWO_PI M_PI * 2
# define WALL_STRIP_WIDTH 1
# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define ROTATE_SPEED 1/60
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 890
# define MINIMAP_WIDTH 1280
# define MINIMAP_HEIGHT 890
# define DIST_TO_PROJECTION (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2)
# define RIGHT 1 << 0
# define LEFT 1 << 1
# define UP 1 << 2
# define DOWN 1 << 3
#define NUM_RAYS WINDOW_WIDTH / WALL_STRIP_WIDTH
typedef uint32_t t_color;

#endif /* DEFS */
