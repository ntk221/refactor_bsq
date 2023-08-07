/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:44:48 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 20:43:37 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * @brief 0x20(space)から0x7e(~)までの文字かどうかを判定する
 * ASCIIコード表を参照
 * 
 * @param c 
 * @return int 
 */
int		ft_is_printable(char c)
{
	if (c < 0x20 || c == 0x7f)
		return (0);
	return (1);
}
