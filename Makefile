# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 11:31:23 by bmartin           #+#    #+#              #
#    Updated: 2023/10/05 10:59:54 by rofontai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#                 \ \ / /_\ | _ |_ _| /_\ | _ | |  | __/ __|
#                  \ V / _ \|   /| | / _ \| _ | |__| _|\__ \
#                  \_/_/ \_|_|_|___/_/ \_|___|____|___|___/



######################_____________VARIABLES______________######################

# add colors
G = \033[0;32m
RT = \033[0m

# NAME_OF_THE_PROGRAM (exemple:   a.out    )
NAME	= cub3D

# COMPILER
CC		= gcc -g

# COMPILER FLAGS
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LFLAGS  = -fsanitize=address

# LIBRARY
LIBMLX	= MLX42
LIBFT	= libft
LIBS	= MLX42/lib2/libmlx42.a MLX42/lib2/libglfw3.a libft/libft.a

# DIRECTORY FOR HEADER FILE
HEADERS	= -I ./include -I $(LIBMLX)/include


SRC	=		main.c \
			execute/control.c \
			execute/init.c \
			execute/raycast.c \
			execute/tools.c \
			execute/draw.c \
			parsing/check_arg.c \
			parsing/utils.c \
			parsing/utils1.c \
			parsing/utils2.c \
			parsing/extract_data.c \
			parsing/a_supp.c \
			parsing/pars_map.c \


OBJDIR	=	bin/

SRCDIR	=	src/

SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJ		= $(SRC:%.c=%.o)
OBJS	= $(addprefix $(OBJDIR), $(OBJ))


#                        _____ _   ___  ___ ___ _____
#                       |_   _/_\ | _ \/ __| __|_   _|
#                         | |/ _ \|   | (_ | _|  | |
#                         |_/_/ \_|_|_\\___|___| |_|

######################______________TARGET______________######################


all: mk_bin libs_make $(NAME)


# The target "mk_bin" creates the "bin" directory if it doesn't exist already
mk_bin:
	@mkdir -p $(OBJDIR)

libs_make:
	@$(MAKE) -C $(LIBMLX)
	@$(MAKE) -C $(LIBFT)

$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	@$(CC)  $(CFLAGS)$(LFLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) -framework Cocoa -framework OpenGL -framework IOKit

	@echo "$(G)\n ║ MAKE COMPLETE 🥳 ║$(RT)"
	@echo "\nMAKE run  \ RUN...$(RT)"
	@echo "MAKE leaks   \\ RUN + LEAKS CHECK $(RT)"

clean:
	@echo "\n$(R)Cleaning...$(RT)"
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBMLX) clean
	@echo "$(G)MLX42 Cleaned$(RT)"
	@$(MAKE) -C $(LIBFT) clean
	@echo "$(G)Libft Cleaned$(RT)\n"

fclean: clean rm_bin
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBMLX) fclean
	@echo "$(G)MLX42 	Cleaned$(RT)"
	@$(MAKE) -C $(LIBFT) fclean
	@echo "$(G)Libft	Cleaned$(RT)"

# "rm_bin" removes the "bin" directory.
rm_bin:
	@rm -rf $(OBJDIR)

# "re" is a shortcut for "fclean" followed by "all".
re: fclean all

# "leaks" runs the program with the "leaks" tool to check for memory leaks.
leaks: all
	leaks -atExit -- ./$(NAME) $(word 2, $(MAKECMDGOALS)) 


#"play" builds the program and runs it with a specific map file.
run: all
	@./$(NAME) $(word 2, $(MAKECMDGOALS)) 
	

%:
	@true

.PHONY: all mk_bin libs_make clean fclean rm_bin re run
