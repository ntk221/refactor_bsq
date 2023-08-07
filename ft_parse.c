/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_info.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:47:47 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 17:35:17 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

/**
 * @brief mapの最初の行から、行数、空白、障害物、fullの情報を取得する
 * 
 * @param map 
 * @return t_info* 
 */
t_info	*ft_parse(char **map)
{
	t_info	*info;
	char	*line;
	int		len;
	int		i;
	char	*num_row;

	line = map[0];
	len = ft_strlen(line);
	info = malloc(sizeof(t_info *));
	if (info == NULL)
		exit(EXIT_FAILURE);
	num_row = malloc(sizeof(char) * (len - 3) + 1);
	if (num_row == NULL)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < len - 3)
		num_row[i] = line[i];
	num_row[i] = '\0';
	i = -1;
	info->num_rows = ft_atoi(num_row);
	info->empty = line[len - 3];
	info->obstacle = line[len - 2];
	info->full = line[len - 1];
	free(num_row);
	return (info);
}
