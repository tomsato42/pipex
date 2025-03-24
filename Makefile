NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src
GNL_DIR = get_next_line
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(GNL_DIR)/*.c)
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
INCLUDES = -I include -I $(LIBFT_DIR) -I $(FT_PRINTF_DIR) -I $(GNL_DIR)
RM = rm -f
all: $(NAME)
$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF) -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)
clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
