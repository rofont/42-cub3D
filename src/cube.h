#ifndef CUBE_H
# define CUBE_H

//////Libraries
# include "../MLX42/include/GLFW/glfw3.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/gnl/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Variable
# define WIDTH 1080
# define HEIGHT 1080

// message erreur
# define E_CHAR_INVALID "Error\nFound Invalid Character\n"
# define E_MAP_TOO_WIDTH "Error\nMap Too Wide (Max 40)\n"
# define E_MAP_TOO_HEIGTH "Error\nMap Too High (max 21)\n"
# define E_MAP_BORDER "Error\nMap Border Missing\n"
# define E_FILE_NAME "Error\nFile Is Invalid\n"
# define E_FLOODFILL "Error\nFloodfill Is Invalid\n"
# define E_ARGS_NUM "Error\nArgument Number Is Wrong\n"
# define E_COLORS "Error\nColors Is Invalid\n"

// colors
# define BCK "\x1B[30m"
# define GRE "\x1B[32m"
# define YEL "\x1B[33m"
# define BLE "\x1B[34m"
# define MAG "\x1B[35m"
# define CYA "\x1B[36m"
# define WHT "\x1B[37m"

// debug
# define DEBUG 1

typedef struct s_ray
{
	// iterator
	int			i;
	// init cam values
	double		posX;   // x and y start position   (player x and y)
	double		posY;   // x and y start position   (player x and y)
	double		dirX;   // initial direction vector
	double		dirY;   // initial direction vector
	double		planeX; // raycaster of camera plane
	double		planeY; // raycaster of camera plane

	// Calculate ray position and direction
	double		cameraX; // x-coordinate in camera space
	double		rayDirX;
	double		rayDirY;

	// Map grid position
	int			mapX;
	int			mapY;
	// Length of ray from current position to next x or y-side
	double		sideDistX;
	double		sideDistY;
	// Length of ray from one x or y-side to next x or y-side
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	// Direction to step in x or y-direction (either +1 or -1)
	int			stepX;
	int			stepY;
	int			hit;        // Was there a wall hit?
	int			side;       // Was a NS or EW wall hit?
	int			lineHeight; // wall height
	int			drawStart;  // position to start drawing wall
	int			drawEnd;    // position to end drawing wall
	uint32_t	color; /// TODO pick wall color (replace when texture update)
}				t_ray;

typedef struct s_map
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		**map;
	int			floor;
	int			ceiling;
	int			map_width;
	int			map_height;
}				t_map;

typedef struct s_player
{
	int			x;
	int			y;
	char		orientation;
	float		angle;
	double		moveSpeed; // the constant value is in squares/second
	double		rotSpeed;  // the constant value is in radians/second
}				t_player;

typedef struct s_data
{
	mlx_t		*mlx;
	int			height;
	int			width;
	int			height_pixel;
	int			width_pixel;
	t_map		*map;
	t_player	*player;
	t_ray		*ray;
	mlx_image_t	*canvas;
}				t_data;

// function

// PARSING
// a_supp
void			f_print_tab(char **cou);
void			f_print_map(t_map *data_map);
void			f_pri_map(char **map);

// check_arg
void			f_error(char *msg, t_map *data);
int				f_check_cub(char *str);
void			f_check_arg(int argc, char **argv);
void			f_print_player(t_player *play);
void			f_pars_file(int ac, char **av, t_data *data);

// utils
void			*f_freenull(void *str);
char			*f_join_and_free(char *src, char *add);
t_map			*f_init_map(void);
char			*f_pars_direction(char *line, char *dir);
bool			f_its_here(char *src, char *search);

// utils2
int				f_number(char *str);
int				f_return_colors(char *line, char *dir);
int				*f_tab_color(char *line);
char			*f_pars_colors(char *line, char *dir);
bool			f_is_good_data(t_map *map);

// utils1
t_player		*f_init_player(void);
bool			f_is_position(char c);
char			**f_copy_tab(char **src);
void			*f_free_tmap(t_map *data);
void			*f_free_player(t_player *play);

// extract_data
char			**f_extract_data(char *file);
void			f_get_data(t_map *map, char **dat);
void			f_while_pars(int *i, char **dat, t_map *map);

// pars_map
int				get_rgba(int r, int g, int b, int a);
bool			f_is_digit(char *str);
int				f_search_player(t_map *data, t_player *player);
void			f_size_maps(t_map *cub);
void			f_flood_fill(char **temp, t_map *cub, int x, int y);

// EXECUTE
// init
t_data			*get_data(void);
void			player_view_init(t_data *data);
void			init_mlx(t_data *data);

// raycast
void			raycast(t_data *data);
void			ray_init(t_data *data);
void			get_side_dist(t_data *data);
void			dda(t_data *data);
void			get_wall(t_data *data);
// TODO delete when texture are in
void			wall_color(t_data *data);

// tools
void			reset_window(t_data *data);
uint32_t		ft_color(int32_t r, int32_t g, int32_t b, int32_t a);
void			draw_filled_circle(mlx_image_t *image, int centerX, int centerY,
					int radius, uint32_t color);
void			verLine(int x, int startY, int drawEnd, uint32_t color);
int 			is_player (char c);

// player control
void			player_control(t_data *data);
void			move_player(t_data *data, char key);
void			strafe_player(t_data *data, char direction);
void			rotate_player(t_data *data, char direction);


#endif
