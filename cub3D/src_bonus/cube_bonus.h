/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:21:00 by bmartin           #+#    #+#             */
/*   Updated: 2023/10/12 14:38:32 by rofontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_BONUS_H
# define CUBE_BONUS_H

//////Libraries
# include "../MLX42/include/GLFW/glfw3.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/gnl/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Variable
# define WIDTH 2040
# define HEIGHT 1400

// message erreur
# define E_CHAR_INVALID "Error\nFound Invalid Character\n"
# define E_MAP_TOO_WIDTH "Error\nMap Too Wide \n"
# define E_MAP_TOO_HEIGTH "Error\nMap Too High )\n"
# define E_MAP_BORDER "Error\nMap Border Missing\n"
# define E_MAP_TOO_BIG "Error\nMap Dimension Too BIG )\n"
# define E_FLOODFILL "Error\nFloodfill Is Invalid\n"
# define E_ARGS_NUM "Error\nArgument Number Is Wrong\n"
# define E_TEX_PATH "Error\nTexture Path is INVALID\n"
# define E_ARG "Error\nGood Usage = ./cub3d map/path/here\n"
# define E_ASSET "Error\nAsset Is Invalid Or Missing\n"
# define E_FILE_NAME "Error\nFile Is Invalid or Is Empty\n"
# define E_COLORS "Error\nColors Is Invalid Or Missing\n"
# define E_PLAYER "Error\nNumber Of Palyers Is Wrong\n"

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

typedef struct s_tex
{
	int			**no;
	int			**so;
	int			**ea;
	int			**we;
	xpm_t		*no_tex;
	xpm_t		*so_tex;
	xpm_t		*ea_tex;
	xpm_t		*we_tex;
}				t_tex;

typedef struct s_ray
{
	int			i;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		raydir_x;
	double		raydir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	uint32_t	color;
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
	double		move_speed;
	double		rot_speed;
}				t_player;

typedef struct s_data
{
	mlx_t		*mlx;
	int			height;
	int			width;
	int			height_pixel;
	int			width_pixel;
	int			anim_f;
	int			scale_factor;
	int			i;
	int			j;
	int			start_x;
	int			start_y;
	int			x;
	int			y;
	uint32_t	color;
	t_map		*map;
	t_player	*player;
	t_ray		*ray;
	mlx_image_t	*canvas;
	t_tex		*tex;
}				t_data;

// function

// PARSING

// check_arg
void			f_error(char *msg, t_map *data);
int				f_check_cub(char *str);
void			f_check_arg(int argc, char **argv);
void			f_pars_file(int ac, char **av, t_data *data);

// utils
void			*f_freenull(void *str);
char			*f_join_and_free(char *src, char *add);
t_map			*f_init_map(void);
char			*f_pars_direction(char *line, char *dir);
bool			f_its_here(char *src, char *search);

// utils2
int				f_number(char *str);
int				f_return_colors(char *line, char *dir, t_map *data);
int				*f_tab_color(char *line, t_map *data);
char			*f_pars_colors(char *line, char *dir);
int 			f_is_good_data(t_map *map);

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
void			init_mlx(t_data *data);
void			get_texture(t_data *data);
void			init_dir(t_data *data);
void	mouse_view_rotation(double xpos, double ypos, void *param);

// raycast
void			raycast(t_data *data);
void			ray_init(t_data *data);
void			get_side_dist(t_data *data);
void			dda(t_data *data);
void			get_wall(t_data *data);

// tools
void			reset_window(t_data *data);
uint32_t		ft_color(int32_t r, int32_t g, int32_t b, int32_t a);
int				is_player(char c);

// player control
void			player_control(t_data *data);
void			move_player(t_data *data, char key);
void			strafe_player(t_data *data, char direction);
void			rotate_player_l(t_data *data);
void			rotate_player_r(t_data *data);

// draw
void			draw_floor(t_data *data);
void			draw_sky(t_data *data);
void			draw_filled_circle(mlx_image_t *image, int centerX, int centerY,
					int radius);
void			draw_minimap(t_data *data);

//texture
void			choose_texture(t_data *data, int x);
void			draw_texture(t_data *data, int x, xpm_t *wall_tex, int **array);
int				**fill_texture(xpm_t *texture);
void			find_texture(t_data *data, xpm_t *texture);

//animation
void			load_dancer(t_data *data);
void			load_no(t_data *data);
void			load_so(t_data *data);
void			load_ea(t_data *data);
void			load_we(t_data *data);
#endif
