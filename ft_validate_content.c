/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:36:58 by kazuki            #+#    #+#             */
/*   Updated: 2023/08/08 16:29:27 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief 入力内容が改行で終わっているか確認する
 * 
 * @param content 
 * @return int 
 */
int	validate_content_end_with_newline(char *content)
{
	int		i;

	i = 0;
	while (content[i] != '\0')
		i++;
	if (content[i - 1] != '\n')
		return (FAIL);
	return (SUCCESS);
}
