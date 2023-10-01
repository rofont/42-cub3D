#include "cube.h"

void player_view_init (t_data *data)
{
      data->ray->posX = 6, data->ray->posY = 6;  //x and y start position   (player x and y)
    data->ray->dirX = -1, data->ray->dirY = 0; //initial direction vector
    data->ray->planeX = 0, data->ray->planeY = 0.66; //the 2d raycaster version of camera plane 
}