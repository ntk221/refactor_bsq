# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/28 13:12:23 by louisnop          #+#    #+#              #
#    Updated: 2023/08/07 22:31:37 by kazuki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = bsq
SRCS = main.c ft_read.c ft_free.c ft_strlen.c ft_puts.c ft_printable.c ft_strdup.c ft_strjoin.c ft_split.c ft_atoi.c ft_info.c ft_validate_map_info.c bsq_solver.c bsq_helper.c ft_validate_header.c ft_split_helper.c
OBJS = main.o ft_read.o ft_free.o ft_strlen.o ft_puts.o ft_printable.o ft_strdup.o ft_strjoin.o ft_split.o ft_atoi.o ft_info.o ft_validate_map_info.o bsq_solver.o bsq_helper.o ft_validate_header.o ft_split_helper.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.c%.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: all clean re
clean:
	-rm -f $(OBJS)

fclean:
	-rm -f $(TARGET) $(OBJS)

re: fclean all
