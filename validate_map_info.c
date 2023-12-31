/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:48:35 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/09 01:45:33 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
static int	validate_map_has_info(char **map, t_info *info);
static int	validate_map_cells(char **map, t_info *info);
static int	validate_map_rows_length(char **map, t_info *info);

/**
 * @bried infoを参照して,map に関するvalidationを行う
 */
int	validate_map_info(char **map, t_info *info)
{
	if (validate_map_has_info(map, info) == FAIL)
		return (FAIL);
	if (validate_map_cells(map, info) == FAIL)
		return (FAIL);
	if (validate_map_rows_length(map, info) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

static int	validate_map_has_info(char **map, t_info *info)
{
	if (!(map[0] && map[1]))
		return (FAIL);
	if (!(map[1][0] == info->empty || \
			map[1][0] == info->obstacle || \
			map[1][0] == info->full))
		return (FAIL);
	return (SUCCESS);
}

/**
 * @brief infoに記載されている空白、障害物、の文字がmapに含まれているかを確認する
 */
static int	validate_map_cells(char **map, t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!(map[i][j] == info->empty || map[i][j] == info->obstacle))
				return (FAIL);
		}
	}
	return (SUCCESS);
}

static int	validate_map_rows_length(char **map, t_info *info)
{
	int	i;
	int	len;

	i = 1;
	len = ft_strlen(map[i]);
	while (map[i])
	{
		if (len != ft_strlen(map[i]))
			return (FAIL);
		i++;
	}
	if (i - 1 != info->num_rows)
		return (FAIL);
	return (SUCCESS);
}

