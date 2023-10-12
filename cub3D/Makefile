# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmartin <bmartin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 11:31:23 by bmartin           #+#    #+#              #
#    Updated: 2023/10/12 16:18:47 by bmartin          ###   ########.fr        #
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
NAME_BONUS = cub3D_bonus

# COMPILER
CC		= gcc -g #-fsanitize=address

# COMPILER FLAGS
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -Ofast

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
			parsing/pars_map.c \
			execute/texture.c \


OBJDIR	=	bin/

SRCDIR	=	src/

SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJ		= $(SRC:%.c=%.o)
OBJS	= $(addprefix $(OBJDIR), $(OBJ))


# BONUS
SRC_BONUS		=	main_bonus.c \
					execute_bonus/control_bonus.c \
					execute_bonus/init_bonus.c \
					execute_bonus/raycast_bonus.c \
					execute_bonus/tools_bonus.c \
					execute_bonus/draw_bonus.c \
					parsing_bonus/check_arg_bonus.c \
					parsing_bonus/utils_bonus.c \
					parsing_bonus/utils1_bonus.c \
					parsing_bonus/utils2_bonus.c \
					parsing_bonus/extract_data_bonus.c \
					parsing_bonus/pars_map_bonus.c \
					execute_bonus/texture_bonus.c \
					execute_bonus/animation_bonus.c \

SRCDIR_BONUS	=	src_bonus/

#OBJDIR_BONUS	=	bin_bonus/

SRCS_BONUS		= $(addprefix $(SRCDIR_BONUS), $(SRC_BONUS))
OBJ_BONUS		= $(SRC_BONUS:%.c=%.o)
OBJS_BONUS		= $(addprefix $(OBJDIR), $(OBJ_BONUS))


#                        _____ _   ___  ___ ___ _____
#                       |_   _/_\ | _ \/ __| __|_   _|
#                         | |/ _ \|   | (_ | _|  | |
#                         |_/_/ \_|_|_\\___|___| |_|

######################______________TARGET______________######################


all: mk_bin libs_make $(NAME)
bonus: mk_bin_bonus libs_make $(NAME_BONUS)

# The target "mk_bin" creates the "bin" directory if it doesn't exist already
mk_bin:
	@mkdir -p $(OBJDIR)
mk_bin_bonus:
	@mkdir -p $(OBJDIR)

libs_make:
	@$(MAKE) -C $(LIBMLX)
	@$(MAKE) -C $(LIBFT)

$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	@$(CC)  $(CFLAGS) -c $< -o $@ $(HEADERS)
$(OBJDIR)%.o : $(SRCDIR_BONUS)%.c
	@mkdir -p $(dir $@)
	@$(CC)  $(CFLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) -framework Cocoa -framework OpenGL -framework IOKit

	@echo "$(G)\n ║ MAKE COMPLETE 🥳 ║$(RT)"
	@echo "\nMAKE run  \ RUN...$(RT)"
	@echo "MAKE leaks   \\ RUN + LEAKS CHECK $(RT)"

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(LIBS) $(HEADERS) -o $(NAME_BONUS) -framework Cocoa -framework OpenGL -framework IOKit

	@echo "$(G)\n ║ MAKE_BONUS COMPLETE 🥳 ║$(RT)"
	@echo "\nMAKE run_bonus  \ RUN...$(RT)"
	@echo "MAKE leaks_bonus   \\ RUN + LEAKS CHECK $(RT)"


clean:
	@echo "\n$(R)Cleaning...$(RT)"
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBMLX) clean
	@echo "$(G)MLX42 Cleaned$(RT)"
	@$(MAKE) -C $(LIBFT) clean
	@echo "$(G)Libft Cleaned$(RT)\n"

clean_bonus:
	@echo "\n$(R)Cleaning...$(RT)"
	@rm -f $(OBJS_BONUS)
	@$(MAKE) -C $(LIBMLX) clean
	@echo "$(G)MLX42 Cleaned Bonus$(RT)"
	@$(MAKE) -C $(LIBFT) clean
	@echo "$(G)Libft Cleaned Bonus$(RT)\n"

fclean: clean rm_bin
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBMLX) fclean
	@echo "$(G)MLX42 	Cleaned$(RT)"
	@$(MAKE) -C $(LIBFT) fclean
	@echo "$(G)Libft	Cleaned$(RT)"

fclean_bonus: clean_bonus rm_bin_bonus
	@rm -f $(NAME_BONUS)
	@$(MAKE) -C $(LIBMLX) fclean
	@echo "$(G)MLX42 	Cleaned Bonus$(RT)"
	@$(MAKE) -C $(LIBFT) fclean
	@echo "$(G)Libft	Cleaned Bonus$(RT)"

# "rm_bin" removes the "bin" directory.
rm_bin:
	@rm -rf $(OBJDIR)
rm_bin_bonus:
	@rm -rf $(OBJDIR)

# "re" is a shortcut for "fclean" followed by "all".
re: fclean all
re_bonus: fclean_bonus bonus

# "leaks" runs the program with the "leaks" tool to check for memory leaks.
leaks: all
	leaks -atExit -- ./$(NAME) $(word 2, $(MAKECMDGOALS))
leaks_bonus: bonus
	leaks -atExit -- ./$(NAME_BONUS) $(word 2, $(MAKECMDGOALS))
	

#"play" builds the program and runs it with a specific map file.
run: all
	@./$(NAME) $(word 2, $(MAKECMDGOALS))
run_bonus: bonus
	say -v karen "3D CUBE party launching"
	@./$(NAME_BONUS) $(word 2, $(MAKECMDGOALS))
	say -v karen "party over"
%:
	@true

.PHONY: all bonus mk_bin mk_bin_bonus libs_make clean clean_bonus fclean fclean_bonus rm_bin rm_bin_bonus re re_bonus run run_bonus
