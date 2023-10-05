#include "../cube.h"

void player_control (t_data *data)
{
///-----player_move
       //speed modifiers
    data->player->moveSpeed = 0.1;
    data->player->rotSpeed = 0.1;

      //4 direction move
     if (mlx_is_key_down(data->mlx, MLX_KEY_W))
         move_player(data,'w');
     if (mlx_is_key_down(data->mlx, MLX_KEY_S))
         move_player(data,'s');
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
        strafe_player(data, 'a');
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
        strafe_player(data, 'd');

    //rotate to the right
     if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
    rotate_player(data,'r');
    //rotate to the left
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
    rotate_player(data,'l');
    if(mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(0);
}


void move_player(t_data *data, char key)
{
    double newX = data->ray->posX;
    double newY = data->ray->posY;

    if (key == 'w')
    {
        newX += data->ray->dirX * data->player->moveSpeed;
        newY += data->ray->dirY * data->player->moveSpeed;
    }
    else if (key == 's')
    {
        newX -= data->ray->dirX * data->player->moveSpeed;
        newY -= data->ray->dirY * data->player->moveSpeed;
    }

    // Check if the new position is valid (not a wall)
      if (data->map->map[(int)newX][(int)newY] == '0' || is_player(data->map->map[(int)newX][(int)newY]))
    {
        data->ray->posX = newX;
        data->ray->posY = newY;
    }
}

void strafe_player(t_data *data, char direction)
{
    double leftDirX = -data->ray->dirY;
    double leftDirY = data->ray->dirX;
    double newX = data->ray->posX;
    double newY = data->ray->posY;

    if (direction == 'a')
    {
        newX += leftDirX * data->player->moveSpeed;
        newY += leftDirY * data->player->moveSpeed;
    }
    else if (direction == 'd')
    {
        newX -= leftDirX * data->player->moveSpeed;
        newY -= leftDirY * data->player->moveSpeed;
    }

    // Check if the new position is valid (not a wall)
    if (data->map->map[(int)newX][(int)newY] == '0' || is_player(data->map->map[(int)newX][(int)newY]))
    {
        data->ray->posX = newX;
        data->ray->posY = newY;
    }
}

void rotate_player(t_data *data, char direction)
{
    double oldDirX = data->ray->dirX;
    double oldPlaneX = data->ray->planeX;

    if (direction == 'r')
    {
        data->ray->dirX = data->ray->dirX * cos(-data->player->rotSpeed) - data->ray->dirY * sin(-data->player->rotSpeed);
        data->ray->dirY = oldDirX * sin(-data->player->rotSpeed) + data->ray->dirY * cos(-data->player->rotSpeed);
        data->ray->planeX = data->ray->planeX * cos(-data->player->rotSpeed) - data->ray->planeY * sin(-data->player->rotSpeed);
        data->ray->planeY = oldPlaneX * sin(-data->player->rotSpeed) + data->ray->planeY * cos(-data->player->rotSpeed);
    }
    else if (direction == 'l')
    {
        data->ray->dirX = data->ray->dirX * cos(data->player->rotSpeed) - data->ray->dirY * sin(data->player->rotSpeed);
        data->ray->dirY = oldDirX * sin(data->player->rotSpeed) + data->ray->dirY * cos(data->player->rotSpeed);
        data->ray->planeX = data->ray->planeX * cos(data->player->rotSpeed) - data->ray->planeY * sin(data->player->rotSpeed);
        data->ray->planeY = oldPlaneX * sin(data->player->rotSpeed) + data->ray->planeY * cos(data->player->rotSpeed);
    }
}
