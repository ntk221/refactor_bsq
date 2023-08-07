/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 22:48:35 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static void	ft_put_map(char **map, t_info *p_info)
{
	int	i;
	int	j;

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

static void	draw_square(char **map, t_info *info, t_bsq *p_bsq)
{
	int	i;
	int	j;

	i = 0;
	while (i < p_bsq->size)
	{
		j = 0;
		while (j < p_bsq->size)
		{
			map[p_bsq->x + i][p_bsq->y + j] = info->full;
			j++;
		}
		i++;
	}
	ft_put_map(map, info);
	return ;
}

/**
 * @brief map上を探索するカーソルを初期化する
 * 探索する行の最初はヘッダーを飛ばした行から始めるので row = 1になる
 * 
 * @param map_cursor 
 */
static void	set_map_cursor(t_map_cursor *map_cursor)
{
	map_cursor->row = 1;
	map_cursor->col = 0;
	map_cursor->size = 0;
}

/**
 * @brief 最大の正方形の座標を検索し、t_bsqのポインタ型で返す
 * 
 * @param map 
 * @param info 
 * @param map_cursor 
 * @param find
 */
static t_bsq	*find_largest_square_coordinates(char **map, t_info *info,
		t_map_cursor *map_cursor)
{
	t_bsq	*found;

	found = init_bsq();
	while (map_cursor->row <= info->num_rows)
	{
		map_cursor->col = 0;
		while (map_cursor->col < ft_map_colsize(map))
		{
			if (is_valid_position(map, map_cursor->col, map_cursor->row,
					info) == 1)
			{
				find_largest_square(map, map_cursor, info);
				if (found->size < map_cursor->size)
				{
					found->size = map_cursor->size;
					found->y = map_cursor->col;
					found->x = map_cursor->row;
				}
			}
			map_cursor->col++;
		}
		map_cursor->row++;
	}
	return (found);
}

/**
 * @brief マップの最大の正方形を検索し、その座標をdraw_squareに渡す
 * 
 * @param map 
 * @param p_info 
 */
void	solve_bsq(char **map, t_info *info)
{
	t_map_cursor	*map_cursor;
	t_bsq			*p_bsq;

	map_cursor = malloc(sizeof(t_map_cursor));
	if (map_cursor == NULL)
		exit(EXIT_FAILURE);
	set_map_cursor(map_cursor);
	p_bsq = find_largest_square_coordinates(map, info, map_cursor);
	draw_square(map, info, p_bsq);
	free(p_bsq);
	free(map_cursor);
	return ;
}
