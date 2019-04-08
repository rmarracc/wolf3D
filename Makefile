#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/11 09:56:48 by rmarracc          #+#    #+#              #
#    Updated: 2019/01/02 16:45:04 by rmarracc         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = wolf3d
GNAME = generator
SRC = main.c parse_map.c parse_map2.c parse_map_check.c display_init.c display_hook.c display_move.c parse_texture.c display_rays.c display_minimap.c rays_helper.c rays_helper2.c
GSRC = generator.c
OBJ = $(SRC:.c=.o)
GOBJ = $(GSRC:.c=.o)
CC = @gcc
CFLAGS = -Wall -Wextra -Werror -I. -O2
SANITIZE = -fsanitize=address
HDR = wolf3d.h
GHDR = generator.h

all : $(NAME) $(GNAME)

$(NAME) : $(OBJ)
	@make -C libft/
	@make -C minilibx/
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L libft/ -lft -L minilibx/ -lmlx -framework OpenGL -framework AppKit

$(GNAME) : $(GOBJ)
	@$(CC) $(CFLAGS) -o $(GNAME) $(GOBJ) -L libft/ -lft

$(OBJ) : $(SRC) $(HDR)

$(GOBJ) : $(GSRC) $(GHDR)

clean :
	@make -C libft/ clean
	@make -C minilibx/ clean
	@rm -f $(OBJ)
	@rm -f $(GOBJ)

fclean : clean
	@make -C libft/ fclean
	@make -C minilibx/ clean
	@rm -f $(NAME)
	@rm -f $(GNAME)

re : fclean all

.PHONY : all clean fclean re
