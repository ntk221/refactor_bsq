/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:59:31 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 22:52:56 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static int			g_word_index = 0;
static int			g_start = 0;
static int			g_end = 0;

enum				e_state
{
	WORD_OUT,
	WORD_IN
};

static enum e_state	g_state;

/**
 * @brief charsetで区切られた単語の数を返す
 * g_stateを適切に切り替えることによって、区切り文字の連続を一つの区切り文字として扱っている
 * 
 * @param str 
 * @param charset 
 * @return int 
 */
static int	ft_get_wc(char *str, char *charset)
{
	int	wc;

	wc = 0;
	g_state = WORD_OUT;
	while (*str)
	{
		if (ft_is_in_charset(*str, charset))
			g_state = WORD_OUT;
		else if (g_state == WORD_OUT)
		{
			g_state = WORD_IN;
			++wc;
		}
		++str;
	}
	return (wc);
}

/**
 * @brief g_stateによって、word pointerのstartとendを更新する
 * g_stateが入力状態の場合、単語の終端位置を進める
 * 
 * @param i 
 */
static void	ft_update_in_word(int i)
{
	if (g_state == WORD_OUT)
	{
		g_state = WORD_IN;
		g_start = i;
		g_end = i;
	}
	else
		g_end = i;
}

/**
 * @brief strからwordを読み込んで、resに追加する
 * 
 * @param res 
 * @param str 
 */
static void	ft_add_word_to_result(char **res, char *str)
{
	int	j;

	j = -1;
	res[g_word_index] = malloc(sizeof(char) * ((g_end - g_start) + 1));
	if (!res[g_word_index])
		exit(EXIT_FAILURE);
	while (g_start <= g_end)
		res[g_word_index][++j] = str[g_start++];
	res[g_word_index][++j] = '\0';
	g_word_index++;
}

static void	ft_add_last_word(char **res, char *str, int i)
{
	int	j;

	if (g_state == WORD_IN)
	{
		res[g_word_index] = malloc(sizeof(char) * ((i - g_start) + 1));
		j = -1;
		while (g_start <= i)
			res[g_word_index][++j] = str[g_start++];
		res[g_word_index][++j] = '\0';
		g_word_index++;
	}
	res[g_word_index] = 0;
}

char	**ft_split(char *str, char *charset)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (ft_get_wc(str, charset) + 1));
	if (!res)
		exit(EXIT_FAILURE);
	i = -1;
	while (str[++i])
	{
		if (ft_is_in_charset(str[i], charset))
		{
			if (g_state == WORD_OUT)
				continue ;
			g_state = WORD_OUT;
			ft_add_word_to_result(res, str);
		}
		else
			ft_update_in_word(i);
	}
	ft_add_last_word(res, str, i);
	g_word_index = 0;
	g_start = 0;
	g_end = 0;
	return (res);
}

/*int main() {
    char *str = "abc def ghi";
    char *charset = " ";
    char **res = ft_split(str, charset);
    int i = 0;
    while (res[i]) {
        printf("%s\n", res[i]);
        i++;
    }

    i = 0;
    while (res[i]) {
        free(res[i]);
        i++;
    }
    free(res);

    char *str2 = "def ghi jkl";
    char *charset2 = " ";
    char **res2 = ft_split(str2, charset2);
    int i2 = 0;
    while (res2[i2]) {
        printf("%s\n", res2[i2]);
        i2++;
    }
 
    i2 = 0;
    while (res2[i2]) {
        free(res2[i2]);
        i2++;
    }
    free(res2);

    return (0);
}
*/