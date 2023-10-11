#include "../cube.h"

t_data *get_data(void)

{
    static t_data *var = NULL;

    if (!var)
    {
        var = ft_calloc(1, sizeof(t_data));
        var->ray = ft_calloc(1, sizeof(t_ray));       // Allocate and initialize the ray structure
        var->player = ft_calloc(1, sizeof(t_player)); // Allocate and initialize the player structure
        var->map = ft_calloc(1, sizeof(t_map));
        var->tex = ft_calloc(1, sizeof(t_tex));
        return (var);
    }
    return (var);
}


void init_mlx(t_data *data)
{
    if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true)))
    {
        puts(mlx_strerror(mlx_errno));
        // TODO add a protection to free our value if mlx fail
        return;
    }
    data->canvas = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    mlx_image_to_window(data->mlx, data->canvas, 0, 0);
}

void	init_dir(t_data *data)
{
     data->ray->posX = data->player->x, data->ray->posY = data->player->y;
	if (data->player->orientation == 'N')
	{
		data->ray->dirX = -1;
		data->ray->planeY = 0.66;
	}
	if (data->player->orientation == 'S')
	{
		data->ray->dirX = 1;
		data->ray->planeY = -0.66;
	}
	if (data->player->orientation == 'E')
	{
		data->ray->dirY = 1; 
		data->ray->planeX = 0.66;
	}
	if (data->player->orientation == 'W')
	{
		data->ray->dirY = -1; 
		data->ray->planeX = -0.66;
	}
}

void get_texture (t_data *data)
{
    data->tex->no_tex = mlx_load_xpm42(data->map->no);
    data->tex->so_tex = mlx_load_xpm42(data->map->so);
    data->tex->ea_tex = mlx_load_xpm42(data->map->ea);
    data->tex->we_tex = mlx_load_xpm42(data->map->we);
	data->tex->no = fill_texture(data->tex->no_tex);
    data->tex->so = fill_texture(data->tex->so_tex);
	data->tex->we = fill_texture(data->tex->we_tex);
	data->tex->ea = fill_texture(data->tex->ea_tex);
}