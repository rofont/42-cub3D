#include "cube.h"

t_player player;

  // Scale factor for each square
  //  int Minimap_scale_factor = 16;



char map1[9][9] = {
    "111111111",
    "110010011",
    "100000001",
    "100000001",
    "110010011",
    "100000001",
    "100000001",
    "110010011",
    "111111111"};
// -----------------------------------------------------------------------------


t_data *get_data(void)

{
    static t_data *var = NULL;

    if (!var)
    {
        var = ft_calloc(1, sizeof(t_data));
        var->ray = ft_calloc(1, sizeof(t_ray)); // Allocate and initialize the ray structure
        return (var);
    }
    return (var);
}

//put black pixel everywhere
void reset_window(mlx_image_t *image)
{
    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            mlx_put_pixel(image, x, y, ft_color(0, 0, 0, 255)); // Set pixel to black
        }
    }
}

void verLine(int x, int startY, int drawEnd, uint32_t color)
{
    t_data *data;

    data = get_data();
    int y;
    for (y = startY; y <= drawEnd; y++)
    {
        mlx_put_pixel(data->canvas, x, y, color);
    }
}

//TODO will become wall texture
void    wall_color (t_data *data)
{
     // Choose wall color (update this according to your map)
        switch (map1[data->ray->mapX][data->ray->mapY])
        {
            case '1':
                data->ray->color = ft_color(0, 255, 0, 255); // GREEN
                break;
            default:
                data->ray->color = ft_color(255, 255, 255, 255); // White if error wall
                break;
        }

        // Give x and y sides different brightness
        if (data->ray->side == 1)
        {
            data->ray->color = ft_color(128, 0, 128, 255); ///side wall are purples
        }
}


void ft_hook(void *param)
{
    (void)param;
    t_data *data;

    data = get_data();

    //reset_pixel
   reset_window(data->canvas);

//draw "3d" view with raycast
raycast(data);


//player_move
    player_control(data);

}

// -----------------------------------------------------------------------------

int main(int ac, const char *av[])
{
    t_data *data;

    (void)ac;
    (void)av;
    data = get_data();

    player.x = 6 ;
    player.y = 6 ;
    player.angle = 0;
    ///////TODO replace map1 with actual map
    data->map = map1;


//------------mlx init
    // error check
    if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true)))
    {
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
    data->canvas = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    mlx_image_to_window(data->mlx, data->canvas, 0, 0);
///////-------


    player_view_init(data);




    mlx_loop_hook(data->mlx, ft_hook, data->mlx);
    mlx_loop(data->mlx);

    mlx_terminate(data->mlx);
    return (EXIT_SUCCESS);
}