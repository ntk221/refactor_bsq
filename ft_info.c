/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_info.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 22:47:47 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 16:16:18 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int		ft_validate_5(char **map)
{
	int		len;
	char	*line;
	int		i;

	if (!map[0])
		return (FAIL);
	line = map[0];
	len = ft_strlen(line);
	if (len < 4)
		return (FAIL);
	i = -1;
	while (++i < len - 3)
		if (!(line[i] >= '0' && line[i] <= '9'))
			return (FAIL);
	if (!(ft_is_printable(line[len - 1]) &&
				ft_is_printable(line[len - 2]) &&
				ft_is_printable(line[len - 3])))
		return (FAIL);
	if (line[len - 1] == line[len - 2] ||
			line[len - 2] == line[len - 3] ||
			line[len - 3] == line[len - 1])
		return (FAIL);
	return (SUCCESS);
}

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
	char	*info_chunk;

	line = map[0];
	len = ft_strlen(line);
	info = malloc(sizeof(t_info *));
	if (info == NULL)
		exit(EXIT_FAILURE);
	info_chunk = malloc(sizeof(char) * (len - 3) + 1);
	if (info_chunk == NULL)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < len - 3)
		info_chunk[i] = line[i];
	info_chunk[i] = '\0';
	info->num_rows = ft_atoi(info_chunk);
	info->empty = line[len - 3];
	info->obstacle = line[len - 2];
	info->full = line[len - 1];
	free(info_chunk);
	return (info);
}
