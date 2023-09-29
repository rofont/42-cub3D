#include "cube.h"

t_player player;
mlx_image_t *map;
  // Scale factor for each square
    int Minimap_scale_factor = 16;


double posX = 6, posY = 6;  //x and y start position   (player x and y)
  double dirX = -1, dirY = 0; //initial direction vector
  double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

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

double getTicks()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0);
}



void draw_3d()
{
    for (int x = 0; x < WIDTH; x++)
    {
        // Calculate ray position and direction
        double cameraX = 2 * x / (double)WIDTH - 1; // x-coordinate in camera space
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        // Map grid position
        int mapX = (int)posX;
        int mapY = (int)posY;

        // Length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        // Length of ray from one x or y-side to next x or y-side
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        // Direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; // Was there a wall hit?
        int side;    // Was a NS or EW wall hit?

        // Calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        // Perform DDA
        while (!hit)
        {
            // Jump to next map square, either in x-direction, or in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            // Check if ray has hit a wall
            if (map1[mapX][mapY] == '1')
                hit = 1;
        }

        // Calculate distance projected on camera direction
        if (side == 0)
            perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

        // Calculate height of line to draw on screen
        int lineHeight = (int)(HEIGHT / perpWallDist);

        // Calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT)
            drawEnd = HEIGHT - 1;

        // Choose wall color (update this according to your map)
        uint32_t color;
        switch (map1[mapX][mapY])
        {
            case '1':
                color = ft_color(255, 0, 0, 255); // Red
                break;
            case '2':
                color = ft_color(0, 255, 0, 255); // Green
                break;
            case '3':
                color = ft_color(0, 0, 255, 255); // Blue
                break;
            default:
                color = ft_color(255, 255, 255, 255); // White
                break;
        }

        // Give x and y sides different brightness
        if (side == 1)
        {
            color = color / 2;
        }

        // Draw the pixels of the stripe as a vertical line
        verLine(x, drawStart, drawEnd, color);
    }
}




void ft_hook(void *param)
{
    mlx_t *mlx = param;
    t_data *data;

    data = get_data();

    //reset_pixel
   reset_window(map);

//draw 3d view

draw_3d();


///-----player_move
       //speed modifiers
    double moveSpeed = 0.1 ; //the constant value is in squares/second
    double rotSpeed = 0.1; //the constant value is in radians/second

      //move forward if no wall in front of you
     if (mlx_is_key_down(mlx, MLX_KEY_W))
    {
      if(map1[(int)(posX + dirX * moveSpeed)][(int)(posY)] == '0')
       posX += dirX * moveSpeed;
      if(map1[(int)(posX)][(int)(posY + dirY * moveSpeed)] == '0')
       posY += dirY * moveSpeed;
    }
    //move backwards if no wall behind you
     if (mlx_is_key_down(mlx, MLX_KEY_S))
    {
      if(map1[(int)(posX - dirX * moveSpeed)][(int)(posY)] == '0') 
      posX -= dirX * moveSpeed;
      if(map1[(int)(posX)][(int)(posY - dirY * moveSpeed)] == '0') 
      posY -= dirY * moveSpeed;
    }
    // Move to the left (A)
if (mlx_is_key_down(mlx, MLX_KEY_A))
{
   // Calculate the leftward direction perpendicular to the current direction
  double leftDirX = -dirY;
  double leftDirY = dirX;

  // Update the position based on the leftward direction
  if (map1[(int)(posX - leftDirX * moveSpeed)][(int)(posY)] == '0') 
    posX += leftDirX * moveSpeed;
  if (map1[(int)(posX)][(int)(posY - leftDirY * moveSpeed)] == '0') 
    posY += leftDirY * moveSpeed;
}

// Move to the right (D)
if (mlx_is_key_down(mlx, MLX_KEY_D))
{
   // Calculate the leftward direction perpendicular to the current direction
  double leftDirX = -dirY;
  double leftDirY = dirX;

  // Update the position based on the leftward direction
  if (map1[(int)(posX - leftDirX * moveSpeed)][(int)(posY)] == '0') 
    posX -= leftDirX * moveSpeed;
  if (map1[(int)(posX)][(int)(posY - leftDirY * moveSpeed)] == '0') 
    posY -= leftDirY * moveSpeed;
}
    //rotate to the right
     if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
      dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
      planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    //rotate to the left
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
      dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
      planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
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

 

    map = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    mlx_image_to_window(data->mlx, map, 0, 0);


    mlx_loop_hook(data->mlx, ft_hook, data->mlx);

    mlx_loop(data->mlx);
    mlx_terminate(data->mlx);
    return (EXIT_SUCCESS);
}