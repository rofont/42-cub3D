#include "cube.h"

t_player player;
mlx_image_t *map;
  // Scale factor for each square
    int Minimap_scale_factor = 12;
char map1[16][39] = {
    "11111111111111111111111111111111111",
    "11111111111111111111111111111111111",
    "10000000001100000000000010000000001",
    "10110000011100000000000010000000001",
    "10010000000000000000000010000000001",
    "11111111101100000111000000000000001",
    "10000000001100000111011110011111111",
    "11110111111111011100000010001       ",
    "11110111111111011101010010001       ",
    "11000000110101011100000010001       ",
    "10000000000000001100000010001       ",
    "10000000000000001101010010001       ",
    "11000001110101011111011110N0111     ",
    "111101111110101101111010001111111111",
    "   111    111111111 111111111    1  "};
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



int is_collision_minimap(int playerX, int playerY, int playerRadius)
{
    // Convert player's pixel coordinates to grid coordinates
    int gridX = playerX / Minimap_scale_factor;
    int gridY = playerY / Minimap_scale_factor;

    // Check if the player's grid cell contains a wall ('1')
    if (map1[gridY][gridX] == '1')
    {
        // Calculate the squared distance from the player's center to the cell center
        int dx = playerX - (gridX * Minimap_scale_factor + Minimap_scale_factor / 2);
        int dy = playerY - (gridY * Minimap_scale_factor + Minimap_scale_factor / 2);
        int squaredDist = dx * dx + dy * dy;

        // Calculate the maximum squared distance allowed for collision
        int maxSquaredDist = (playerRadius + Minimap_scale_factor / 2) * (playerRadius + Minimap_scale_factor / 2);

        // Collision detected if the squared distance is less than or equal to the allowed maximum
        return squaredDist <= maxSquaredDist;
    }

    // No collision
    return 0;
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




void draw_3d(void *param)
{

     mlx_t *mlx = param;

    double posX = 22, posY = 12;  //x and y start position   (player x and y)
  double dirX = -1, dirY = 0; //initial direction vector
  double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

  double time = 0; //time of current frame
  double oldTime = 0; //time of previous frame

  for(int x = 0; x < WIDTH; x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;

      //which box of the map we're in
      int mapX = (int)posX;
      int mapY = (int)posY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

       //length of ray from one x or y-side to next x or y-side
      double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
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

       //perform DDA
      while (hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
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
        //Check if ray has hit a wall
        if (map1[mapX][mapY] > 0) hit = 1;
      } 

         //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
      if(side == 0) perpWallDist = (sideDistX - deltaDistX);
      else          perpWallDist = (sideDistY - deltaDistY);

       //Calculate height of line to draw on screen
      int lineHeight = (int)(HEIGHT / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + HEIGHT / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + HEIGHT / 2;
      if(drawEnd >= HEIGHT)drawEnd = HEIGHT - 1;

    //choose wall color
      uint32_t color;
      switch(map1[mapX][mapY])
      {
        case 1:  color = ft_color(255,0,0,255);  break; //red
        case 2:  color = ft_color(0,255,0,255);  break; //green
        case 3:  color = ft_color(255,0,0,255);   break; //blue
        case 4:  color = ft_color(255,255,255,255);  break; //white
        default: color = ft_color(255,255,0,255); break; //yellow
      }

      //give x and y sides different brightness
      if (side == 1) {color = color / 2;}

      //draw the pixels of the stripe as a vertical line
      verLine(x, drawStart, drawEnd, color);
    }
     //timing for input and FPS counter
    oldTime = time;
    time = getTicks();
    double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    printf("FPS:%f\n",1.0 / frameTime); //FPS counter
    
    //////
   ///redraw here ??????
    ///////
 

    //speed modifiers
    double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

      //move forward if no wall in front of you
     if (mlx_is_key_down(mlx, MLX_KEY_W))
    {
      if(map1[(int)(posX + dirX * moveSpeed)][(int)(posY)] == false) posX += dirX * moveSpeed;
      if(map1[(int)(posX)][(int)(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    }
    //move backwards if no wall behind you
     if (mlx_is_key_down(mlx, MLX_KEY_S))
    {
      if(map1[(int)(posX - dirX * moveSpeed)][(int)(posY)] == false) posX -= dirX * moveSpeed;
      if(map1[(int)(posX)][(int)(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    }
    //rotate to the right
     if (mlx_is_key_down(mlx, MLX_KEY_R))
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
    if (mlx_is_key_down(mlx, MLX_KEY_L))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
      dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
      planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
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

draw_3d(mlx);



// draw minimap------

    // Original map dimensions (16x39)
    int originalWidth = 16;
    int originalHeight = 39;

  printf("%f\n", player.angle);

    int i = 0;
    while (i < originalWidth)
    {
        int j = 0;
        while (j < originalHeight)
        {
            uint32_t color;
            if (map1[i][j] == '0')
                color = ft_color(255, 255, 255, 255);
            else if (map1[i][j] == '1')
                color = ft_color(0, 0, 0, 255);
            else
                color = ft_color(0, 0, 0, 100);

// Calculate the pixel coordinates for the current square
            int startX = j * Minimap_scale_factor;
            int startY = i * Minimap_scale_factor;
            int x = startX;
            while (x < startX + Minimap_scale_factor)
            {
                int y = startY;
                while (y < startY + Minimap_scale_factor)
                {
                    mlx_put_pixel(map, x, y, color);
                    y++;
                }
                x++;
            }
            j++;
        }
        i++;
    }

// draw player
    int playerRadius = 5; // Adjust the radius as needed
    draw_filled_circle(map, player.x, player.y, playerRadius, ft_color(255, 0, 0, 255));

///-----player_move
    // Handle key presses to update position
    float moveSpeed = 3.0; // Adjust the movement speed as needed

    if (mlx_is_key_down(mlx, MLX_KEY_W))
    {
        // Calculate the new position based on the player's angle
        float angleRad = deg_to_rad(player.angle);
        int newX = player.x + (int)(moveSpeed * cos(angleRad));
        int newY = player.y + (int)(moveSpeed * sin(angleRad));

        // Check for collision before updating the position
        if (!is_collision_minimap(newX, newY, playerRadius))
        {
            player.x = newX;
            player.y = newY;
        }
    }
    if (mlx_is_key_down(mlx, MLX_KEY_S))
    {
        // Calculate the new position based on the player's angle
        float angleRad = deg_to_rad(player.angle);
        int newX = player.x - (int)(moveSpeed * cos(angleRad));
        int newY = player.y - (int)(moveSpeed * sin(angleRad));

        // Check for collision before updating the position
        if (!is_collision_minimap(newX, newY, playerRadius))
        {
            player.x = newX;
            player.y = newY;
        }
    }
    if (mlx_is_key_down(mlx, MLX_KEY_A))
    {
        // Calculate the new position based on the player's angle - 90 degrees
        float angleRad = deg_to_rad(player.angle - 90.0);
        int newX = player.x + (int)(moveSpeed * cos(angleRad));
        int newY = player.y + (int)(moveSpeed * sin(angleRad));

        // Check for collision before updating the position
        if (!is_collision_minimap(newX, newY, playerRadius))
        {
            player.x = newX;
            player.y = newY;
        }
    }

    if (mlx_is_key_down(mlx, MLX_KEY_D))
    {
        // Calculate the new position based on the player's angle + 90 degrees
        float angleRad = deg_to_rad(player.angle + 90.0);
        int newX = player.x + (int)(moveSpeed * cos(angleRad));
        int newY = player.y + (int)(moveSpeed * sin(angleRad));

        // Check for collision before updating the position
        if (!is_collision_minimap(newX, newY, playerRadius))
        {
            player.x = newX;
            player.y = newY;
        }
    }

    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
        player.angle -= 5;
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
        player.angle += 5;
    if (player.angle >= 360)
        player.angle = 0;
    if (player.angle < 0)
        player.angle = 360;
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

    player.x = 13 ;
    player.y = 32 ;
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