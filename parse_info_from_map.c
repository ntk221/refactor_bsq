/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info_from_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:47:47 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/09 01:20:36 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

/**
 * @brief mapの最初の行から、行数、空白、障害物、fullの情報を取得する
 * 前提知識: mapの1行目はheader行になっていて次のような形式に従っている
 *          例: 9.ox (9は行数、.は空白、oは障害物、xはfull)
 *          ゆえに len("9.ox") - 3 は常に 空白文字 のインデックス(後ろから３番目)になるように期待される
 * 
 * @param map 
 * @return t_info* 
 */
t_info	*parse_info_from_map(char **map)
{
	t_info	*info;
	char	*header;
	int		len;
	int		i;
	char	*num_row;

	header = map[0];
	len = ft_strlen(header);
	info = malloc(sizeof(t_info *));
	if (info == NULL)
		exit(EXIT_FAILURE);
	num_row = malloc(sizeof(char) * (len - 3) + 1);
	if (num_row == NULL)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < len - 3)
		num_row[i] = header[i];
	num_row[i] = '\0';
	i = -1;
	info->num_rows = ft_atoi(num_row);
	info->empty = header[len - 3];
	info->obstacle = header[len - 2];
	info->full = header[len - 1];
	free(num_row);
	return (info);
}
