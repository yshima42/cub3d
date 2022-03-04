/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:13:50 by yshimazu          #+#    #+#             */
/*   Updated: 2022/03/04 14:17:09 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	size_check(t_conf *conf)
{
	if (conf->map.width > INT32_MAX || conf->map.height > INT32_MAX)
		map_error_output(conf->map.map, "Map size is too big\n");
}
