/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmakesquare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 19:10:42 by kazuki           ###   ########.fr       */
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
 * @param p_tempcrs 
 * @param info 
 * @return true 
 * @return false 
 */
bool	can_expand_horizontally_vertically(char **map, t_tempcrs *p_tempcrs, t_info *info)
{
	int i;

	i = 0;
	while (i <= p_tempcrs->size)
	{
		if (!is_valid_position(map, p_tempcrs->col + i,
		p_tempcrs->row + p_tempcrs->size, info))
		{
			return (false);
		}
		i++;
	}
	i = 0;
	while (i <= p_tempcrs->size)
	{
		if (!is_valid_position(map, p_tempcrs->col + p_tempcrs->size,
		p_tempcrs->row + i, info))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief map内の指定された位置から、一片がsize分の長さの正方形を描けるかを判定する
 * 
 * @param map 
 * @param p_tempcrs 
 * @param p_info 
 */
void	find_largest_square(char **map, t_tempcrs *p_tempcrs, t_info *p_info)
{
	p_tempcrs->size = 0;
	while (can_expand_horizontally_vertically(map, p_tempcrs, p_info))
	{
		p_tempcrs->size++;
	}
	if (g_max < p_tempcrs->size)
	{
		g_max = p_tempcrs->size;
		g_col = p_tempcrs->col;
		g_row = p_tempcrs->row;
	}
}

void	set_bsq(t_bsq *p_bsq)
{
	p_bsq->x = g_col;
	p_bsq->y = g_row;
	p_bsq->size = g_max;
}
