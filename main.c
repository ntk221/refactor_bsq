/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:58:38 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 22:32:49 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

/**
 * @brief 入力内容が改行で終わっているか確認する
 * 
 * @param content 
 * @return int 
 */
int	validate_content_end(char *content)
{
	int	i;

	i = 0;
	while (content[i] != '\0')
		i++;
	if (content[i - 1] != '\n')
		return (FAIL);
	return (SUCCESS);
}

/**
 * @brief コマンドライン引数にファイルを指定されない場合は標準入力から読み込む
 * 
 * @return int 
 */
int	process_stdin(void)
{
	char	**map;
	t_info	*info;
	char	*content;

	content = ft_read(STDIN_FILENO);
	if (validate_content_end(content) == FAIL)
		return (FAIL);
	map = ft_split(content, "\n");
	free(content);
	if (validate_map_header(map) == FAIL)
		return (FAIL);
	info = ft_parse(map);
	if (!info)
		return (FAIL);
	if (validate_map_info(map, info) == FAIL)
		return (FAIL);
	solve_bsq(map, info);
	ft_free(&map);
	free(info);
	return (SUCCESS);
}

static char	*get_content_from_file(char *filename)
{
	int		ifd;
	char	*content;

	ifd = open(filename, O_RDONLY);
	if (ifd == -1)
		return (NULL);
	content = ft_read(ifd);
	close(ifd);
	return (content);
}

/**
 * @brief fileを読み込んでmapを作成し、solve_bsqに渡す
 * return値は、成功か失敗かを表す
 * 
 * @param argc 
 * @param argv 
 * @param i 
 * @return int 
 */
int	process_file(int argc, char *argv[], int i)
{
	char	*content;
	char	**map;
	t_info	*info;

	content = get_content_from_file(argv[i]);
	if (!content)
		return (FAIL);
	if (validate_content_end(content) == FAIL)
		return (FAIL);
	map = ft_split(content, "\n");
	free(content);
	if (validate_map_header(map) == FAIL)
		return (FAIL);
	info = ft_parse(map);
	if (!info)
		return (FAIL);
	if (validate_map_info(map, info) == FAIL)
		return (FAIL);
	solve_bsq(map, info);
	if (!(i + 1 == argc))
		ft_putstr("\n");
	ft_free(&map);
	free(info);
	return (SUCCESS);
}

int	main(int argc, char *argv[])
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
