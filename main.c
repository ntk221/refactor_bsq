/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:58:38 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 11:56:35 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	ft_free(char ***map)
{
	long int i;

	i = 0;
	while ((*map)[i])
	{
		free((*map)[i]);
		i++;
	}
	free(*map);
	*map = NULL;
}

char	*ft_read(int ifd)
{
	char	*content;
	char	buf[FT_BUFSIZ + 1];
	int		n;

	content = NULL;
	while ((n = read(ifd, buf, FT_BUFSIZ)) > 0)
	{
		buf[n] = '\0';
		if (content == NULL)
			content = ft_strdup(buf);
		else
			content = ft_strjoin(content, buf);
	}
	return (content);
}

int		ft_main_1(void)
{
	char	*content;
	char	**map;
	t_info	*info;

	content = ft_read(STDIN_FILENO); // mapを標準入力から読み込む
	if (ft_validate_4(content) == FAIL)
		return (FAIL);
	map = ft_split(content, "\n");
	free(content);
	if (ft_validate_5(map) == FAIL)
		return (FAIL);
	if (!(info = ft_prse(map)))
		return (FAIL);
	if (ft_validate(map, info) == FAIL)
		return (FAIL);
	ft_make_map(map, info);
	ft_free(&map);
	free(info);
	return (SUCCESS);
}

int		ft_main_2(int argc, char *argv[], int i)
{
	int		ifd;
	char	*content;
	char	**map;
	t_info	*info;

	if ((ifd = open(argv[i], O_RDONLY)) == -1)
		return (FAIL);
	content = ft_read(ifd);
	if (ft_validate_4(content) == FAIL)
		return (FAIL);
	close(ifd);
	map = ft_split(content, "\n");
	free(content);
	if (ft_validate_5(map) == FAIL)
		return (FAIL);
	if (!(info = ft_prse(map)))
		return (FAIL);
	if (ft_validate(map, info) == FAIL)
		return (FAIL);
	ft_make_map(map, info);
	if (!(i + 1 == argc))
		ft_putstr("\n");
	ft_free(&map);
	free(info);
	return (SUCCESS);
}

int		main(int argc, char *argv[])
{
	int	i;

	if (argc < 2)
	{
		if (ft_main_1() == FAIL)
			ft_puterror(FT_ERR_MAP);
	}
	else
	{
		i = 0;
		while (++i < argc)
		{
			if (ft_main_2(argc, argv, i) == FAIL)
				ft_puterror(FT_ERR_MAP);
		}
	}
	return (0);
}
