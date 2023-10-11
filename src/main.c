#include "cube.h"

//TODO will become wall texture
void    wall_color (t_data *data)
{
     // Choose wall color (update this according to your map)
      
        
        if (data->ray->side == 0)
            data->ray->color = ft_color(0, 255, 0, 255); ///side wall are purples
        if (data->ray->side == 1)
            data->ray->color = ft_color(128, 0, 128, 255); ///side wall are purples
        if (data->ray->side == 2)
            data->ray->color = ft_color(0, 0, 255, 255); ///side wall are blue
        if (data->ray->side == 3)
            data->ray->color = ft_color(255, 0, 0, 255); ///side wall are red
}


//PLAY audio

void *play_audio(void *arg)
{
  
    system("afplay russian.wav");
    return(arg);
}



void ft_hook(void *param)
{
    (void)param;
    t_data *data;

    data = get_data();

    //player_move
    player_control(data);

    //reset_pixel or commment it to see something beautifull hahahah
   reset_window(data);

   draw_floor_sky(data);

    //draw "3d" view with raycast
    raycast(data);

    draw_minimap(data);
      //draw_filled_circle(data->canvas, data->ray->posX, data->ray->posY, 5, ft_color(255, 0, 0, 255));

}



int	main(int ac, char **av)
{
  	t_data *data;


    if(ac != 2)
    {
        //TODO add free here and clean exit
        printf("ERROR good usage = ./cub3d map/path/here\n");
        return(0);
    }
    //--mlx init
    data = get_data();
    init_mlx(data);
	f_pars_file(ac, av, data);
	//f_print_map(data->map);


    //TODO modify the values according to the letter we have for the player (N-S-E-W)
    //modify the function player_view_init
    init_dir(data);

    ///texture load
    get_texture(data);

    ////MUSIC
    // pthread_t thread;
    // int result;

    // result = pthread_create(&thread, NULL, play_audio, NULL);
    /////////

    mlx_loop_hook(data->mlx, ft_hook, data->mlx);
    mlx_loop(data->mlx);
    mlx_terminate(data->mlx);
  
	// f_free_player(play);
	// f_free_tmap(map);
	return (EXIT_SUCCESS);
}
