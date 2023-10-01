#include "cube.h"

t_player player;
mlx_image_t *map;
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

// donne la couleur selon le niveau de rgba
uint32_t ft_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

double deg_to_rad(double degree)
{
    // Convert playerAngle from degrees to radians
    return (degree * M_PI / 180.0);
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


void draw_filled_circle(mlx_image_t *image, int centerX, int centerY, int radius, uint32_t color)
{
    int x = centerX - radius;
    while (x <= centerX + radius)
    {
        int y = centerY - radius;
        while (y <= centerY + radius)
        {
            int dx = x - centerX;
            int dy = y - centerY;
            if (dx * dx + dy * dy <= radius * radius)
            {
                mlx_put_pixel(image, x, y, color);
            }
            y++;
        }
        x++;
    }
}


void verLine(int x, int startY, int drawEnd, uint32_t color)
{
    int y;
    for (y = startY; y <= drawEnd; y++)
    {
        mlx_put_pixel(map, x, y, color);
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
    mlx_t *mlx = param;
    t_data *data;

    data = get_data();

    //reset_pixel
   reset_window(map);

//draw "3d" view with raycast
raycast(data);


///-----player_move
       //speed modifiers
    double moveSpeed = 0.1 ; //the constant value is in squares/second
    double rotSpeed = 0.1; //the constant value is in radians/second

      //move forward if no wall in front of you
     if (mlx_is_key_down(mlx, MLX_KEY_W))
    {
      if(map1[(int)(data->ray->posX + data->ray->dirX * moveSpeed)][(int)(data->ray->posY)] == '0')
       data->ray->posX += data->ray->dirX * moveSpeed;
      if(map1[(int)(data->ray->posX)][(int)(data->ray->posY + data->ray->dirY * moveSpeed)] == '0')
       data->ray->posY += data->ray->dirY * moveSpeed;
    }
    //move backwards if no wall behind you
     if (mlx_is_key_down(mlx, MLX_KEY_S))
    {
      if(map1[(int)(data->ray->posX - data->ray->dirX * moveSpeed)][(int)(data->ray->posY)] == '0') 
      data->ray->posX -= data->ray->dirX * moveSpeed;
      if(map1[(int)(data->ray->posX)][(int)(data->ray->posY - data->ray->dirY * moveSpeed)] == '0') 
      data->ray->posY -= data->ray->dirY * moveSpeed;
    }
    // Move to the left (A)
if (mlx_is_key_down(mlx, MLX_KEY_A))
{
   // Calculate the leftward direction perpendicular to the current direction
  double leftDirX = -data->ray->dirY;
  double leftDirY = data->ray->dirX;

  // Update the position based on the leftward direction
  
  if (map1[(int)(data->ray->posX - leftDirX * moveSpeed)][(int)(data->ray->posY)] == '0') 
  
    data->ray->posX += leftDirX * moveSpeed;
  if (map1[(int)(data->ray->posX)][(int)(data->ray->posY - leftDirY * moveSpeed)] == '0') 
    data->ray->posY += leftDirY * moveSpeed;
}

// Move to the right (D)
if (mlx_is_key_down(mlx, MLX_KEY_D))
{
   // Calculate the leftward direction perpendicular to the current direction
  double leftDirX = -data->ray->dirY;
  double leftDirY = data->ray->dirX;

  // Update the position based on the leftward direction
  if (map1[(int)(data->ray->posX - leftDirX * moveSpeed)][(int)(data->ray->posY)] == '0') 
    data->ray->posX -= leftDirX * moveSpeed;
  if (map1[(int)(data->ray->posX)][(int)(data->ray->posY - leftDirY * moveSpeed)] == '0') 
    data->ray->posY -= leftDirY * moveSpeed;
}
    //rotate to the right
     if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
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
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = data->ray->dirX;
      data->ray->dirX = data->ray->dirX * cos(rotSpeed) - data->ray->dirY * sin(rotSpeed);
      data->ray->dirY = oldDirX * sin(rotSpeed) + data->ray->dirY * cos(rotSpeed);
      double oldPlaneX = data->ray->planeX;
      data->ray->planeX = data->ray->planeX * cos(rotSpeed) - data->ray->planeY * sin(rotSpeed);
      data->ray->planeY = oldPlaneX * sin(rotSpeed) + data->ray->planeY * cos(rotSpeed);
    }
    if(mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		exit(0);
    

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

    // error check
    if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true)))
    {
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }

 
    data->ray->posX = 6, data->ray->posY = 6;  //x and y start position   (player x and y)
    data->ray->dirX = -1, data->ray->dirY = 0; //initial direction vector
    data->ray->planeX = 0, data->ray->planeY = 0.66; //the 2d raycaster version of camera plane 

    map = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    mlx_image_to_window(data->mlx, map, 0, 0);


    mlx_loop_hook(data->mlx, ft_hook, data->mlx);

    mlx_loop(data->mlx);
    mlx_terminate(data->mlx);
    return (EXIT_SUCCESS);
}