CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = bsq
SRCS = main.c ft_read.c ft_free.c ft_validate_map_info.c bsq_helper.c ft_parse.c ft_validate_content.c bsq_solver.c ft_validate_header.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_NAME = libft.a
LIBFT_PATH = $(LIBFT_DIR)/$(LIBFT_NAME)
INC = -I$(LIBFT_DIR)

all: $(TARGET)

$(TARGET): $(OBJS) $(LIBFT_PATH)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT_PATH) $(INC)

$(LIBFT_PATH):
	make -C $(LIBFT_DIR)

%.c%.o:
	$(CC) $(CFLAGS) -c $< $(INC)

.PHONY: all clean fclean re
clean:
	-rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	-rm -f $(TARGET)
	make -C $(LIBFT_DIR) fclean

re: fclean all

