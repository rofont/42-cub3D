# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmartin <bmartin@student.42quebec.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 11:31:23 by bmartin           #+#    #+#              #
#    Updated: 2023/02/08 13:09:49 by bmartin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#                 \ \ / /_\ | _ |_ _| /_\ | _ | |  | __/ __|                   
#                  \ V / _ \|   /| | / _ \| _ | |__| _|\__ \                    
#                   \_/_/ \_|_|_|___/_/ \_|___|____|___|___/                   



######################_____________VARIABLES______________######################

# add colors
G = \033[0;32m
RT = \033[0m

# NAME_OF_THE_PROGRAM (exemple:   a.out    )
NAME	= cube

# COMPILER
CC		= gcc

# COMPILER FLAGS
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LFLAGS  = -fsanitize=address

# LIBRARY
LIBMLX	= MLX42
LIBFT	= libft
LIBS	= lib/libmlx42.a lib/libglfw3.a libft/libft.a

# DIRECTORY FOR HEADER FILE
HEADERS	= -I ./include -I $(LIBMLX)/include


SRCS	=	src/main.c \
		

OBJDIR	=	bin/

SRCDIR	=	src/

OBJS	=	$(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))



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


$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c $(INC) | $(OBJDIR)
	@$(CC)  $(CFLAGS)$(LFLAGS) -c $< -o $@ $(HEADERS)


$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) -framework Cocoa -framework OpenGL -framework IOKit

	@echo "$(G)\n ║ MAKE COMPLETE 🥳 ║$(RT)"
	@echo "\nMAKE PLAY  \ RUN...$(RT)"
	@echo "MAKE LEAKS   \\ RUN + LEAKS CHECK $(RT)"

clean:
	@echo "\n$(R)Cleaning...$(RT)"
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBMLX) clean
	@echo "$(G)MLX42 Cleaned$(RT)"
	@$(MAKE) -C $(LIBFT) clean
	@echo "$(G)Libft Cleaned$(RT)\n"

#The target "fclean" removes the final program and cleans the libraries.
fclean: clean rm_bin
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBMLX) fclean
	@echo "$(G)MLX42  Cleaned$(RT)"
	@$(MAKE) -C $(LIBFT) fclean
	@echo "$(G)Libft Cleaned$(RT)"

#The new target "rm_bin" removes the "bin" directory.
rm_bin:
	@rm -rf $(OBJDIR)

#The target "re" is a shortcut for "fclean" followed by "all".
re: fclean all

#The target "leaks" runs the program with the "leaks" tool to check for memory leaks.
leaks: all
	leaks -atExit -- ./cube 

#The target "play" builds the program and runs it with a specific map file.
play: all
	./cube 

