/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpmakesquare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 17:23:01 by kazuki           ###   ########.fr       */
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

void	set_tempcrs(t_tempcrs *p_tempcrs)
{
	p_tempcrs->row = 1;
	p_tempcrs->col = 0;
	p_tempcrs->size = 0;
}

int		ft_check_1(char **map, int col, int row, t_info *p_info)
{
	if (col == ft_map_colsize(map))
	{
		return (0);
	}
	if (row == p_info->num_rows + 1)
	{
		return (0);
	}
	if (map[row][col] == p_info->obstacle || map[row][col] == '\0')
	{
		return (0);
	}
	return (1);
}

int		ft_check_2(char **map, t_tempcrs *p_tempcrs, t_info *p_info)
{
	int i;

	i = 0;
	while (i <= p_tempcrs->size)
	{
		if (ft_check_1(map, p_tempcrs->col + i,
		p_tempcrs->row + p_tempcrs->size, p_info) == 0)
		{
			return (0);
		}
		i++;
	}
	i = 0;
	while (i <= p_tempcrs->size)
	{
		if (ft_check_1(map, p_tempcrs->col + p_tempcrs->size,
		p_tempcrs->row + i, p_info) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_check_3(char **map, t_tempcrs *p_tempcrs, t_info *p_info)
{
	p_tempcrs->size = 0;
	while (ft_check_2(map, p_tempcrs, p_info) == 1)
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
