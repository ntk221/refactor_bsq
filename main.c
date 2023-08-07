/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:58:38 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 20:08:52 by kazuki           ###   ########.fr       */
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

/**
 * @brief 入力内容が改行で終わっているか確認する
 * 
 * @param content 
 * @return int 
 */
int		validate_content_end(char *content)
{
	int		i;

	i = 0;
	while (content[i] != '\0')
		i++;
	if (content[i - 1] != '\n')
		return (FAIL);
	return (SUCCESS);
}

int		process_stdin(void)
{
	char	*content;
	char	**map;
	t_info	*info;

	content = ft_read(STDIN_FILENO);
	if (validate_content_end(content) == FAIL)
		return (FAIL);
	map = ft_split(content, "\n");
	free(content);
	// map の validation
	if (validate_map_header(map) == FAIL)
		return (FAIL);
	// map の parse
	if (!(info = ft_parse(map)))
		return (FAIL);
	if (ft_validate(map, info) == FAIL)
		return (FAIL);
	ft_make_map(map, info);
	ft_free(&map);
	free(info);
	return (SUCCESS);
}

/**
 * @brief fileを読み込んでmapを作成する
 * 
 * @param argc 
 * @param argv 
 * @param i 
 * @return int 
 */
int		process_file(int argc, char *argv[], int i)
{
	int		ifd;
	char	*content;
	char	**map;
	t_info	*info;

	if ((ifd = open(argv[i], O_RDONLY)) == -1)
		return (FAIL);
	content = ft_read(ifd);
	if (validate_content_end(content) == FAIL)
		return (FAIL);
	close(ifd);
	map = ft_split(content, "\n");
	free(content);
	if (validate_map_header(map) == FAIL)
		return (FAIL);
	if (!(info = ft_parse(map)))
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
		if (process_stdin() == FAIL)
			ft_puterror(FT_ERR_MAP);
	}
	else
	{
		i = 0;
		while (++i < argc)
		{
			if (process_file(argc, argv, i) == FAIL)
				ft_puterror(FT_ERR_MAP);
		}
	}
	return (0);
}
