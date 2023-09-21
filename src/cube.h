/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:31:36 by bmartin           #+#    #+#             */
/*   Updated: 2023/09/21 16:10:33 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE
# define CUBE

//////Libraries
# include "../MLX42/include/GLFW/glfw3.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/gnl/get_next_line.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>

//Variable
#define IMG_PIXEL_SIZE 64
#define WIDTH 2048
#define HEIGHT 2048

//message erreur
# define E_CHAR_INVALID "Error\nFound Invalid Character\n"
# define E_MAP_TOO_WIDTH "Error\nMap Too Wide (Max 40)\n"
# define E_MAP_TOO_HEIGTH "Error\nMap Too High (max 21)\n"
# define E_MAP_BORDER "Error\nMap Border Missing\n"
# define E_FILE_NAME "Error\nFile Is Invalid\n"
# define E_FLOODFILL "Error\nFloodfill Is Invalid\n"
# define E_ARGS_NUM "Error\nArgument Number is wrong\n"

typedef struct s_data
{
	mlx_t			*mlx;
	int				height;
	int				width;
	int				height_pixel;
	int				width_pixel;
	char			**map;

	mlx_texture_t *wall;
	mlx_texture_t *grass;
	mlx_texture_t *penguin;

	mlx_image_t *wall_img;
	mlx_image_t *grass_img;
	mlx_image_t *penguin_img;
}					t_data;

typedef struct s_map
{
	char		**map;
	int			map_height;
	int			map_width;

}					t_map;

typedef struct s_player
{
	int				x;
	int				y;
	float			angle;

}				t_player;

//function

// PARSING

//check_arg
void	f_error(char *msg);
int		f_check_fdf(char *str);
void	f_check_arg(int argc, char **argv);

//check_file
void	*f_freenull(void *str);
void	f_print_file(char *file);

#endif
