/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 02:58:38 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/08 16:53:17 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"
#include <string.h>

int		process_stdin(void);
int		process_file(int argc, char *argv[], int i);
char	*get_content_from(char *arg);
int		check_precondition(char *arg, char ***map, t_info **info);

/**
 * @brief コマンドライン引数の有無によって、標準入力から読み込むか、ファイルから読み込むかを判断する
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int	main(int argc, char *argv[])
{
	int	file_num;

	if (argc < 2)
	{
		if (process_stdin() == FAIL)
			ft_puterror(FT_ERR_MAP);
	}
	else
	{
		file_num = 0;
		while (++file_num < argc)
		{
			if (process_file(argc, argv, file_num) == FAIL)
				ft_puterror(FT_ERR_MAP);
		}
	}
	return (0);
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
	char *stdin = "STDIN";
	
	
	if (check_precondition(stdin, &map, &info) == FAIL)
		return (FAIL);
	solve_bsq(map, info);
	ft_free(&map);
	free(info);
	return (SUCCESS);
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
int	process_file(int argc, char *argv[], int file_num)
{
	char	**map;
	t_info	*info;

	if(check_precondition(argv[file_num], &map, &info) == FAIL)
		return (FAIL);
	solve_bsq(map, info);
	if (!(file_num + 1 == argc))
		ft_putstr("\n");
	ft_free(&map);
	free(info);
	return (SUCCESS);
}

/**
 * @brief solverに渡す前に、mapの内容が正しいか確認する
 * 
 * @param arg 
 * @param map 
 * @param info 
 * @return int 
 */
int check_precondition(char *arg, char ***map, t_info **info)
{
	char	*content;

	content = get_content_from(arg);
	if (!content)
		return (FAIL);
	if (validate_content_end_with_newline(content) == FAIL)
		return (FAIL);
	*map = ft_split(content, "\n");
	free(content);
	if (validate_map_header(*map) == FAIL)
		return (FAIL);
	*info = ft_parse(*map);
	if (!info)
		return (FAIL);
	if (validate_map_info(*map, *info) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

/**
 * @brief 引数が標準入力を表すときは、標準入力から読み込む
 * それ以外のときは引数はファイルを表すのでファイルから読み込む
 * 
 * @param arg 
 * @return char* 
 */
char	*get_content_from(char *arg)
{
	int		ifd;
	char	*content;
	char	*stdin = "STDIN";

	if (ft_strncmp(arg, stdin, ft_strlen(arg)) == 0)
	{
		content = ft_read(0);
		return (content);
	}
	ifd = open(arg, O_RDONLY);
	if (ifd == -1)
		return (NULL);
	content = ft_read(ifd);
	close(ifd);
	return (content);
}
