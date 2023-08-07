/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmakesquare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 20:40:09 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft.h"

int		ft_map_colsize(char **map)
{
	int count;

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
	if (col == ft_map_colsize(map))
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

/**
 * @brief 指定された位置から、水平方向、垂直方向にsize分だけ拡張できるかを判定する
 * 途中で障害物にぶつかったらfalseを返す
 * 
 * @param map 
 * @param map_cursor
 * @param info 
 * @return true 
 * @return false 
 */
bool	can_expand_horizontally_vertically(char **map, t_map_cursor *map_cursor, t_info *info)
{
	int i;

	i = 0;
	while (i <= map_cursor->size)
	{
		if (!is_valid_position(map, map_cursor->col + i,
		map_cursor->row + map_cursor->size, info))
		{
			return (false);
		}
		i++;
	}
	i = 0;
	while (i <= map_cursor->size)
	{
		if (!is_valid_position(map, map_cursor->col + map_cursor->size,
		map_cursor->row + i, info))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief map内の指定された位置から、一片がsize分の長さの正方形を描けるかを判定する
 * 
 * @param map 
 * @param map_cursor
 * @param info 
 */
void	find_largest_square(char **map, t_map_cursor *map_cursor, t_info *p_info)
{
	map_cursor->size = 0;
	while (can_expand_horizontally_vertically(map, map_cursor, p_info))
	{
		map_cursor->size++;
	}
}

void	set_bsq(t_bsq *p_bsq, int max, int col, int row)
{
	p_bsq->x = col;
	p_bsq->y = row;
	p_bsq->size = max;
}
