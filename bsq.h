/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:30:46 by louisnop          #+#    #+#             */
/*   Updated: 2023/08/09 01:44:48 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <libgen.h>
# include <stdbool.h>

# define FT_BUFSIZ 320000
# define IN 1
# define OUT 0
# define SUCCESS 1
# define FAIL 0
# define FT_ERR_MAP "map error\n"

typedef struct s_bsq
{
	int			x;
	int			y;
	int			size;
}				t_bsq;

typedef struct s_info
{
	int		num_rows;
	char	empty;
	char	obstacle;
	char	full;
}				t_info;

/**
 * @brief map上を探索するカーソル
 * 
 */
typedef struct s_map_cursor
{
	int	col;
	int	row;
	int	size;
}				t_map_cursor;

void			free_map(char ***map);
char			*ft_read(int ifd);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
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
t_info			*parse_info_from_map(char **map);
int				validate_map_info(char **map, t_info *info);
int				validate_content_end_with_newline(char *content);
bool			is_valid_position(char **map, int col, int row, t_info *info);
bool			can_expand_square(char **map, t_map_cursor \
													*p_tempcrs, t_info *info);
int				search_largest_square(char **map, t_map_cursor *p_tempcrs, \
																t_info *p_info);
void			solve_bsq(char **map, t_info *p_info);
t_bsq			*init_bsq(void);
int				get_map_colsize(char **map);

#endif
