NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src
GNL_DIR = get_next_line
MAIN_SRC = $(SRC_DIR)/main.c
BONUS_MAIN_SRC = $(SRC_DIR)/main_bonus.c
COMMON_SRCS = $(filter-out $(MAIN_SRC) $(BONUS_MAIN_SRC), $(wildcard $(SRC_DIR)/*.c)) $(wildcard $(GNL_DIR)/*.c)
SRCS = $(COMMON_SRCS) $(MAIN_SRC)
BONUS_SRCS = $(COMMON_SRCS) $(BONUS_MAIN_SRC)
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
INCLUDES = -I include -I $(LIBFT_DIR) -I $(FT_PRINTF_DIR) -I $(GNL_DIR)
RM = rm -f

all: $(NAME)

$(NAME): .normal

.normal: $(OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF) -o $(NAME)
	@touch .normal
	@rm -f .bonus

bonus: .bonus

.bonus: $(BONUS_OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) $(FT_PRINTF) -o $(NAME)
	@touch .bonus
	@rm -f .normal

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean

fclean: clean
	$(RM) $(NAME) .normal .bonus
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus