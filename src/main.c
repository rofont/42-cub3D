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
            data->ray->color = ft_color(128, 0, 128, 255); ///side wall are purples
}


void ft_hook(void *param)
{
    (void)param;
    t_data *data;

    data = get_data();

    //reset_pixel or commment it to see something beautifull hahahah
   reset_window(data);

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

    ///////TODO replace map1 with actual map
    data->map = map1;

    /////INSERT PARSING HERE

    //--mlx init
    init_mlx(data);

    //TODO modify the values according to the letter we have for the player (N-S-E-W)
    player_view_init(data);

    mlx_loop_hook(data->mlx, ft_hook, data->mlx);
    mlx_loop(data->mlx);
    mlx_terminate(data->mlx);
    return (EXIT_SUCCESS);
}