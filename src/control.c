#include "cube.h"

void player_control (t_data *data)
{
///-----player_move
       //speed modifiers
    double moveSpeed = 0.1 ; //the constant value is in squares/second
    double rotSpeed = 0.1; //the constant value is in radians/second

      //move forward if no wall in front of you
     if (mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
      if(data->map[(int)(data->ray->posX + data->ray->dirX * moveSpeed)][(int)(data->ray->posY)] == '0')
       data->ray->posX += data->ray->dirX * moveSpeed;
      if(data->map[(int)(data->ray->posX)][(int)(data->ray->posY + data->ray->dirY * moveSpeed)] == '0')
       data->ray->posY += data->ray->dirY * moveSpeed;
    }
    //move backwards if no wall behind you
     if (mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
      if(data->map[(int)(data->ray->posX - data->ray->dirX * moveSpeed)][(int)(data->ray->posY)] == '0') 
      data->ray->posX -= data->ray->dirX * moveSpeed;
      if(data->map[(int)(data->ray->posX)][(int)(data->ray->posY - data->ray->dirY * moveSpeed)] == '0') 
      data->ray->posY -= data->ray->dirY * moveSpeed;
    }
    // Move to the left (A)
if (mlx_is_key_down(data->mlx, MLX_KEY_A))
{
   // Calculate the leftward direction perpendicular to the current direction
  double leftDirX = -data->ray->dirY;
  double leftDirY = data->ray->dirX;

  // Update the position based on the leftward direction
  
  if (data->map[(int)(data->ray->posX - leftDirX * moveSpeed)][(int)(data->ray->posY)] == '0') 
  
    data->ray->posX += leftDirX * moveSpeed;
  if (data->map[(int)(data->ray->posX)][(int)(data->ray->posY - leftDirY * moveSpeed)] == '0') 
    data->ray->posY += leftDirY * moveSpeed;
}

// Move to the right (D)
if (mlx_is_key_down(data->mlx, MLX_KEY_D))
{
   // Calculate the leftward direction perpendicular to the current direction
  double leftDirX = -data->ray->dirY;
  double leftDirY = data->ray->dirX;

  // Update the position based on the leftward direction
  if (data->map[(int)(data->ray->posX - leftDirX * moveSpeed)][(int)(data->ray->posY)] == '0') 
    data->ray->posX -= leftDirX * moveSpeed;
  if (data->map[(int)(data->ray->posX)][(int)(data->ray->posY - leftDirY * moveSpeed)] == '0') 
    data->ray->posY -= leftDirY * moveSpeed;
}
    //rotate to the right
     if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = data->ray->dirX;
      data->ray->dirX = data->ray->dirX * cos(-rotSpeed) - data->ray->dirY * sin(-rotSpeed);
      data->ray->dirY = oldDirX * sin(-rotSpeed) + data->ray->dirY * cos(-rotSpeed);
      double oldPlaneX = data->ray->planeX;
      data->ray->planeX = data->ray->planeX * cos(-rotSpeed) - data->ray->planeY * sin(-rotSpeed);
      data->ray->planeY = oldPlaneX * sin(-rotSpeed) + data->ray->planeY * cos(-rotSpeed);
    }
    //rotate to the left
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = data->ray->dirX;
      data->ray->dirX = data->ray->dirX * cos(rotSpeed) - data->ray->dirY * sin(rotSpeed);
      data->ray->dirY = oldDirX * sin(rotSpeed) + data->ray->dirY * cos(rotSpeed);
      double oldPlaneX = data->ray->planeX;
      data->ray->planeX = data->ray->planeX * cos(rotSpeed) - data->ray->planeY * sin(rotSpeed);
      data->ray->planeY = oldPlaneX * sin(rotSpeed) + data->ray->planeY * cos(rotSpeed);
    }
    if(mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(0);
}