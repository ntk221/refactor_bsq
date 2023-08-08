/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 22:31:17 by kazuki            #+#    #+#             */
/*   Updated: 2023/08/09 01:43:46 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define FT_BUFSIZ 4096

char	*ft_read(int ifd)
{
	char	*content;
	char	buf[FT_BUFSIZ + 1];
	int		n;

	content = NULL;
	n = read(ifd, buf, FT_BUFSIZ); 
	while (n > 0)
	{
		buf[n] = '\0';
		if (content == NULL)
			content = ft_strdup(buf);
		else
		{
			char *tmp = ft_strjoin(content, buf);
			free(content);
			content = tmp;
		}
		n = read(ifd, buf, FT_BUFSIZ);
	}
	return (content);
}
