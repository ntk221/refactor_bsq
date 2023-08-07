/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makesquare2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 17:22:31 by kazuki           ###   ########.fr       */
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

void	ft_change_map(char **map, t_info *p_info)
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

void	ft_make_map(char **map, t_info *p_info)
{
	t_tempcrs *p_tempcrs;

	g_max = 0;
	g_col = 0;
	g_row = 0;
	p_tempcrs = malloc(sizeof(t_tempcrs));
	set_tempcrs(p_tempcrs);
	while (p_tempcrs->row <= p_info->num_rows)
	{
		p_tempcrs->col = 0;
		while (p_tempcrs->col < ft_map_colsize(map))
		{
			if (ft_check_1(map, p_tempcrs->col,
			p_tempcrs->row, p_info) == 1)
			{
				ft_check_3(map, p_tempcrs, p_info);
			}
			p_tempcrs->col++;
		}
		p_tempcrs->row++;
	}
	ft_change_map(map, p_info);
	free(p_tempcrs);
	return ;
}
