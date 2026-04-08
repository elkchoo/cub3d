# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Elkan Choo <echoo@42mail.sutd.edu.sg>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/12 21:52:11 by elkan             #+#    #+#              #
#    Updated: 2026/04/08 13:25:14 by Elkan Choo       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = $(wildcard *.c)

BONUS_SOURCES = check_path.c mlx_utils_2.c mlx_utlis.c open_window.c \
player_movement.c player_rotation.c search_path.c so_long.c so_long_utils.c \
config_steps_bonus.c

OBJECTS = $(SOURCES:%.c=%.o)

BONUS_OBJECTS = $(BONUS_SOURCES:%.c=%.o)

NAME = so_long

BONUS = so_long_bonus

LIBFT = libft/libft.a

MLX = minilibx-linux/libmlx.a

CFLAGS = -Wall -Wextra -Werror -Ilibft -Iminilibx-linux -g

all: $(NAME)

$(NAME): $(MLX) $(OBJECTS) $(LIBFT)
	cc $(OBJECTS) $(CFLAGS) $(LIBFT) $(MLX) -lXext -lX11 -o $(NAME)

bonus: $(BONUS)

$(BONUS): $(MLX) $(BONUS_OBJECTS) $(LIBFT)
	cc $(BONUS_OBJECTS) $(CFLAGS) $(LIBFT) $(MLX) -lXext -lX11 -o $(BONUS)

$(LIBFT):
	make -C libft

$(MLX): minilibx-linux
	make -C minilibx-linux

minilibx-linux:
	wget https://cdn.intra.42.fr/document/document/46415/minilibx-linux.tgz
	tar -xzf minilibx-linux.tgz
	rm -f minilibx-linux.tgz

%.o: %.c cub3d.h
	cc $(CFLAGS) -c $< -o $@

-include $(SRC:%.c=%.d)

clean:
	rm -f $(OBJECTS)
	rm -f $(BONUS_OBJECTS)
	make clean -C libft

fclean: clean
	rm -f $(NAME) $(BONUS)
	make fclean -C libft
	make clean -C minilibx-linux

re: fclean all

.PHONY: all clean fclean re bonus
