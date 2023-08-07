/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makesquare2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 19:06:24 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	ft_put_map(char **map, t_info *p_info)
{
	int i;
	int j;

	i = 1;
	while (i <= p_info->num_rows)
	{
		j = 0;
		while (j < ft_map_colsize(map))
		{
			write(1, &map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	draw_square(char **map, t_info *p_info)
{
	int		i;
	int		j;
	t_bsq	*p_bsq;

	i = 0;
	p_bsq = malloc(sizeof(t_bsq));
	set_bsq(p_bsq);
	while (i < g_max)
	{
		j = 0;
		while (j < g_max)
		{
			map[g_row + i][g_col + j] = p_info->full;
			j++;
		}
		i++;
	}
	ft_put_map(map, p_info);
	free(p_bsq);
	return ;
}

void	set_tempcrs(t_tempcrs *p_tempcrs)
{
	p_tempcrs->row = 1;
	p_tempcrs->col = 0;
	p_tempcrs->size = 0;
}

/**
 * @brief mapとその情報を受け取り、最大の正方形を探して、その正方形の部分をfullに変える 
 * 
 * @param map 
 * @param p_info 
 */
void	ft_make_map(char **map, t_info *info)
{
	t_tempcrs *p_tempcrs;

	g_max = 0;
	g_col = 0;
	g_row = 0;
	p_tempcrs = malloc(sizeof(t_tempcrs));
	set_tempcrs(p_tempcrs);
	while (p_tempcrs->row <= info->num_rows)
	{
		p_tempcrs->col = 0;
		while (p_tempcrs->col < ft_map_colsize(map))
		{
			if (is_valid_position(map, p_tempcrs->col,
			p_tempcrs->row, info) == 1)
			{
				find_largest_square(map, p_tempcrs, info);
			}
			p_tempcrs->col++;
		}
		p_tempcrs->row++;
	}
	draw_square(map, info);
	free(p_tempcrs);
	return ;
}
