# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/16 13:58:06 by plang             #+#    #+#              #
#    Updated: 2024/08/19 14:01:34 by ahamalai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
BONUS = .bonus
LIBFTDIR = ./libft
MAKE = make
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
LIBMLX = ./MLX42
SRCS = srcs/main.c \
			srcs/input_extractor.c \
			srcs/file_reader.c \
			srcs/file_reader_utils.c \
			srcs/map_validation.c \
			srcs/rgb_validation.c \
			srcs/input_cleaner.c \
			srcs/input_error.c \
			srcs/free_memory.c \
			srcs/rendering.c \
			srcs/raycasting.c \
			srcs/movement.c

SRCS_B = srcsbonus/main.c \
			srcsbonus/input_extractor.c \
			srcsbonus/file_reader.c \
			srcsbonus/file_reader_utils.c \
			srcsbonus/map_validation.c \
			srcsbonus/rgb_validation.c \
			srcsbonus/input_cleaner.c \
			srcsbonus/input_error.c \
			srcsbonus/free_memory.c \
			srcsbonus/rendering.c \
			srcsbonus/raycasting.c \
			srcsbonus/movement.c

OBJS = $(SRCS:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
		@$(MAKE) -C $(LIBFTDIR)
		@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
		@$(CC) $(CFLAGS) $(OBJS) $(LIBMLX)/build/libmlx42.a -lm -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" ./libft/libft.a -o $(NAME) 

bonus: $(BONUS)

$(BONUS):	$(OBJS_B)
		@touch .bonus
		@$(MAKE) -C $(LIBFTDIR)
		@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
		@$(CC) $(CFLAGS) $(OBJS_B) $(LIBMLX)/build/libmlx42.a -lm -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" ./libft/libft.a -o $(NAME) 

clean:
		@rm -f .bonus
		@rm -f $(OBJS) $(OBJS_B)
		@$(MAKE) clean -C $(LIBFTDIR)
		@rm -rf $(LIBMLX)/build

fclean: clean
		@rm -f $(NAME)
		@rm -f libft.a
		@$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re