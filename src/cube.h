/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmartin <bmartin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:31:36 by bmartin           #+#    #+#             */
/*   Updated: 2023/05/04 17:09:58 by bmartin          ###   ########.fr       */
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
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
 #include <math.h>

//Variable 
#define IMG_PIXEL_SIZE 16
#define WIDTH 800
#define HEIGHT 600

//message erreur
# define E_CHAR_INVALID "Error\n Found Invalid Character\n"
# define E_MAP_TOO_WIDTH "Error\n Map Too Wide (Max 40)\n"
# define E_MAP_TOO_HEIGTH "Error\n Map Too High (max 21)\n"
# define E_MAP_BORDER "Error\n Map Border Missing\n"
# define E_FILE_NAME "Error\n File Name Is Invalid\n"
# define E_FLOODFILL "Error\n Floodfill Is Invalid\n"
# define E_ARGS_NUM "Error\n Argument Number is wrong\n"

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
	int				radius;

}				t_player;

//function

#endif
