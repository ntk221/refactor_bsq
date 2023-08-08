CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = libft.a
SRCS = ft_read.c ft_atoi.c ft_printable.c ft_puts.c ft_split.c ft_split_helper.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $@ $(OBJS)

%.c%.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: all clean fclean re
clean:
	-rm -f $(OBJS)

fclean: clean
	-rm -f $(TARGET)

re: fclean all