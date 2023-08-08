/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_header.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:36:38 by kazuki            #+#    #+#             */
/*   Updated: 2023/08/07 17:47:14 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

/**
 * @brief mapの最初の行(ヘッダー行)が正しいか確認する
 * 
 * @param map 
 * @return int 
 */
int	validate_map_header(char **map)
{
	const int	header_length = 4;
	int			len;
	char		*header;
	int			i;

	if (!map[0])
		return (FAIL);
	header = map[0];
	len = ft_strlen(header);
	if (len < header_length)
		return (FAIL);
	i = -1;
	while (++i < len - 3)
		if (!(header[i] >= '0' && header[i] <= '9'))
			return (FAIL);
	if (!(ft_is_printable(header[len - 1]) && \
			ft_is_printable(header[len - 2]) && \
			ft_is_printable(header[len - 3])))
		return (FAIL);
	if (header[len - 1] == header[len - 2] || \
		header[len - 2] == header[len - 3] || \
		header[len - 3] == header[len - 1])
		return (FAIL);
	return (SUCCESS);
}
