/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:36:38 by kazuki            #+#    #+#             */
/*   Updated: 2023/08/09 01:20:10 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

/**
 * @brief mapの最初の行(ヘッダー行)が正しいか確認する
 * 前提知識: mapの1行目はheader行になっていて次のような形式に従っている
 *          例: 9.ox (9は行数、.は空白、oは障害物、xはfull)
 *          ゆえに len("9.ox") - 3 は常に 空白文字 のインデックス(後ろから３番目)になるように期待される
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
			
	char	empty = header[len - 3];
	char	obstacle = header[len - 2];
	char	full = header[len - 1];
	if (!(ft_is_printable(empty) && \
			ft_is_printable(obstacle) && \
			ft_is_printable(full)))
		return (FAIL);
	if (empty == obstacle || \
		obstacle == full || full == obstacle)
		return (FAIL);
	return (SUCCESS);
}
