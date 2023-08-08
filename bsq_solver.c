/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 21:46:00 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/09 01:32:12 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static void	put_map(char **map, t_info *p_info);
static void	draw_square_to_map(char **map, t_info *info, t_bsq *p_bsq);
static t_bsq	*get_bsq(char **map, t_info *info);
void	solve_bsq(char **map, t_info *info);
bool	can_expand_square(char **map, t_map_cursor *map_cursor, t_info *info);

/**
 * @brief マップの最大の正方形を検索し、その座標をdraw_squareに渡す
 * 
 * @param map 
 * @param p_info 
 */
void	solve_bsq(char **map, t_info *info)
{
	t_bsq			*p_bsq;

	p_bsq = get_bsq(map, info);
	draw_square_to_map(map, info, p_bsq);
	free(p_bsq);
	return ;
}

/**
 * @brief 最大の正方形の座標を検索し、t_bsqのポインタ型で返す
 * init_bsqでmallocしているので、呼び出し側はfoundをfreeする必要がある
 * 
 * @param map 
 * @param info 
 * @param found
 */
static t_bsq	*get_bsq(char **map, t_info *info)
{
	t_bsq			*found;
	t_map_cursor	map_cursor;

	// map上を探索するカーソルを初期化する
 	// 探索する行の最初はヘッダーを飛ばした行から始めるので row = 1になる 
	map_cursor.row = 1;
	map_cursor.col = 0;
	map_cursor.size = 0;
	found = init_bsq();
	while (map_cursor.row <= info->num_rows)
	{
		map_cursor.col = 0;
		while (map_cursor.col < get_map_colsize(map))
		{
			if (is_valid_position(map, map_cursor.col, map_cursor.row,
					info) == 1)
			{
				int searched_size = search_largest_square(map, &map_cursor, info);
				if (found->size < searched_size)
				{
					found->size = map_cursor.size;
					found->y = map_cursor.col;
					found->x = map_cursor.row;
				}
			}
			map_cursor.col++;
		}
		map_cursor.row++;
	}
	return (found);
}

/**
 * @brief map内の指定された位置から、可能な最大の正方形のサイズを探索して、それを返す
 *
 * 
 * @param map 
 * @param map_cursor
 * @param info 
 *
 * @return size
 */
int	search_largest_square(char **map, t_map_cursor *map_cursor,
		t_info *p_info)
{
	map_cursor->size = 0;
	while (can_expand_square(map, map_cursor, p_info))
	{
		map_cursor->size++;
	}
	return map_cursor->size;
}

/**
 * @brief 指定された位置から、一辺の長さがsize分の正方形が広げられるかどうかを判定する
 * 途中で障害物にぶつかるから、map外に収まらない場合はfalseを返す
 * 
 * @param map 
 * @param map_cursor
 * @param info 
 * @return true 
 * @return false 
 */
bool	can_expand_square(char **map, t_map_cursor *map_cursor, t_info *info)
{
	int side_length = map_cursor->size;

	int i = 0;
	while (i <=  side_length)
	{
		if (!is_valid_position(map, map_cursor->col + i, map_cursor->row
				+ side_length, info))
		{
			return (false);
		}
		i++;
	}
	i = 0;
	while (i <= side_length)
	{
		if (!is_valid_position(map, map_cursor->col + side_length,
				map_cursor->row + i, info))
			return (false);
		i++;
	}
	return (true);
}

static void	draw_square_to_map(char **map, t_info *info, t_bsq *p_bsq)
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
	put_map(map, info);
	return ;
}

static void	put_map(char **map, t_info *p_info)
{
	int	i;
	int	j;

	i = 1;
	while (i <= p_info->num_rows)
	{
		j = 0;
		while (j < get_map_colsize(map))
		{
			write(1, &map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

/**
 * @brief mallocしているので、呼び出し側はfreeする必要がある
 * 
 * @return t_bsq* 
 */
t_bsq	*init_bsq(void)
{
	t_bsq	*p_bsq;

	p_bsq = (t_bsq *)malloc(sizeof(t_bsq));
	if (p_bsq == NULL)
		exit(EXIT_FAILURE);
	p_bsq->x = 0;
	p_bsq->y = 0;
	p_bsq->size = 0;
	return (p_bsq);
}
