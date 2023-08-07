/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:30:46 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/07 17:57:10 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <libgen.h>

# define FT_BUFSIZ 320000
# define IN 1
# define OUT 0
# define SUCCESS 1
# define FAIL 0
# define FT_ERR_MAP "map error\n"

typedef	struct	s_bsq
{
	int			x;
	int			y;
	int			size;
}				t_bsq;

typedef	struct	s_info
{
	int		num_rows;
	char	empty;
	char	obstacle;
	char	full;
}				t_info;

typedef	struct	s_tempcrs
{
	int	col;
	int	row;
	int	size;
}				t_tempcrs;

extern int				g_max;
extern int				g_col;
extern int				g_row;
void			ft_putchar(char c);
void			ft_putstr(char *str);
void			ft_puterror(char *str);
int				ft_strlen(char *str);
int				ft_is_in_charset(char c, char *charset);
char			**ft_split(char *str, char *charset);
int				ft_is_printable(char c);
char			*ft_strdup(char *src);
char			*ft_strjoin(char *s1, char *s2);
int				ft_atoi(char *str);
int				validate_map_header(char **map);
t_info			*ft_parse(char **map);
int				ft_validate(char **map, t_info *info);
int				validate_content_end(char *content);
void			set_tempcrs(t_tempcrs *p_tempcrs);
int				ft_check_1(char **map, int col, int row, t_info *p_info);
int				ft_check_2(char **map, t_tempcrs *p_tempcrs, t_info *p_info);
void			ft_check_3(char **map, t_tempcrs *p_tempcrs, t_info *p_info);
void			ft_make_map(char **map, t_info *p_info);
void			set_bsq(t_bsq *p_bsq);
int				ft_map_colsize(char **map);

#endif
