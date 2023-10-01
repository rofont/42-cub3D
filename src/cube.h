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
 #include <sys/time.h>

//Variable 


#define WIDTH 1080
#define HEIGHT 1080

//message erreur
# define E_CHAR_INVALID "Error\n Found Invalid Character\n"
# define E_MAP_TOO_WIDTH "Error\n Map Too Wide (Max 40)\n"
# define E_MAP_TOO_HEIGTH "Error\n Map Too High (max 21)\n"
# define E_MAP_BORDER "Error\n Map Border Missing\n"
# define E_FILE_NAME "Error\n File Name Is Invalid\n"
# define E_FLOODFILL "Error\n Floodfill Is Invalid\n"
# define E_ARGS_NUM "Error\n Argument Number is wrong\n"



typedef struct s_ray
{
	//iterator
		int i; 
	//init cam values
		 double posX;//x and y start position   (player x and y)
		 double posY;//x and y start position   (player x and y)
		 double dirX;//initial direction vector
		 double dirY;//initial direction vector
		 double planeX;//raycaster of camera plane 
		 double planeY;//raycaster of camera plane 

	 // Calculate ray position and direction
        double cameraX; // x-coordinate in camera space
        double rayDirX;
        double rayDirY;

        // Map grid position
        int mapX;
        int mapY;
        // Length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;
        // Length of ray from one x or y-side to next x or y-side
        double deltaDistX;
        double deltaDistY;
        double perpWallDist;
        // Direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;
        int hit; // Was there a wall hit?
        int side;    // Was a NS or EW wall hit?
		int lineHeight;	//wall height
		int	drawStart;	//position to start drawing wall
		int	drawEnd;	//position to end drawing wall

		uint32_t	color;   ///TODO pick wall color (replace when texture update)
}	t_ray;

typedef struct s_player
{
    int x;
    int y;
	char orientation; 
    float angle;
	double moveSpeed; //the constant value is in squares/second
    double rotSpeed; //the constant value is in radians/second
} t_player;

typedef struct s_map
{
	char		**map;
	int			map_height;	
	int			map_width;	

}					t_map;

typedef struct s_data
{
	mlx_t			*mlx;
	int				height;
	int				width;
	int				height_pixel;
	int				width_pixel;
	//TODO replace with actual map parsing
	char (*map)[9];
	t_player		*player;
	t_ray			*ray;
	mlx_image_t *canvas;

}					t_data;




//----------------------function
//init
	t_data *get_data(void);
	void player_view_init (t_data *data);
	void init_mlx (t_data *data);

//raycast
	void raycast(t_data *data);
	void ray_init (t_data *data);
	void get_side_dist (t_data *data);
	void dda (t_data *data);
	void get_wall (t_data *data);
		//TODO delete when texture are in
		void    wall_color (t_data *data);


//tools
	void reset_window(t_data *data);
	uint32_t ft_color(int32_t r, int32_t g, int32_t b, int32_t a);
	void draw_filled_circle(mlx_image_t *image, int centerX, int centerY, int radius, uint32_t color);
		void verLine(int x, int startY, int drawEnd, uint32_t color);


//player control
	void player_control (t_data *data);
	void move_player(t_data *data, char key);
	void strafe_player(t_data *data, char direction);
	void rotate_player(t_data *data, char direction);
#endif
