/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/09 01:45:10 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	get_map_colsize(char **map)
{
	int	count;

	count = 0;
	while (map[1][count])
	{
		count++;
	}
	return (count);
}

/**
 * @brief col, rowで指定された位置が、map内であるか、また障害物でないかを判定する。
 * 
 * @param map 
 * @param col 
 * @param row 
 * @param info 
 * @return bool
 */
bool	is_valid_position(char **map, int col, int row, t_info *info)
{
	if (col == get_map_colsize(map))
	{
		return (false);
	}
	if (row == info->num_rows + 1)
	{
		return (false);
	}
	if (map[row][col] == info->obstacle || map[row][col] == '\0')
	{
		return (false);
	}
	return (true);
}
