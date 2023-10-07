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
        return (var);
    }
    return (var);
}

void player_view_init(t_data *data)
{
    data->ray->posX = data->player->x, data->ray->posY = data->player->y; // x and y start position   (player x and y)
    data->ray->dirX = -1, data->ray->dirY = 0;                            // initial direction vector
    data->ray->planeX = 0, data->ray->planeY = 0.66;                       // the 2d raycaster version of camera plane
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