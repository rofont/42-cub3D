#include "../cube.h"

void raycast(t_data *data)
{
    for (data->ray->i = 0; data->ray->i < WIDTH; data->ray->i++)
    {

      //init all raycast value
        ray_init(data);

        // Calculate step and initial sideDist
       get_side_dist(data);

        // Perform DDA
        dda(data);

       //compute wall
       get_wall(data);

        //TODO replace with WALL TEXTURE
       wall_color(data);

        // Draw the pixels of the stripe as a vertical line
        verLine(data->ray->i, data->ray->drawStart, data->ray->drawEnd, data->ray->color);
    }
}


//TODO need to set up the value of pos dir and plane values to fit the N,E,W,S
void ray_init (t_data *data)
{

      // Calculate ray position and direction
        data->ray->cameraX = 2 * data->ray->i / (double)WIDTH - 1; // x-coordinate in camera space
        data->ray->rayDirX = data->ray->dirX + data->ray->planeX * data->ray->cameraX;
        data->ray->rayDirY = data->ray->dirY + data->ray->planeY * data->ray->cameraX;

        // Map grid position
        data->ray->mapX = (int)data->ray->posX;
        data->ray->mapY = (int)data->ray->posY;

        // Length of ray from one x or y-side to next x or y-side
         data->ray->deltaDistX = fabs(1 / data->ray->rayDirX);
         data->ray->deltaDistY = fabs(1 / data->ray->rayDirY);

}

// Calculate step and initial sideDist
void get_side_dist (t_data *data)
{
 if (data->ray->rayDirX < 0)
        {
            data->ray->stepX = -1;
            data->ray->sideDistX = (data->ray->posX - data->ray->mapX) * data->ray->deltaDistX;
        }
        else
        {
            data->ray->stepX = 1;
            data->ray->sideDistX = (data->ray->mapX + 1.0 - data->ray->posX) * data->ray->deltaDistX;
        }
        if (data->ray->rayDirY < 0)
        {
            data->ray->stepY = -1;
            data->ray->sideDistY = (data->ray->posY - data->ray->mapY) * data->ray->deltaDistY;
        }
        else
        {
            data->ray->stepY = 1;
            data->ray->sideDistY = (data->ray->mapY + 1.0 - data->ray->posY) * data->ray->deltaDistY;
        }
}

void dda (t_data *data)
{
    data->ray->hit = 0; // Reset hit flag
        while (!data->ray->hit)
        {
            // Jump to next map square, either in x-direction, or in y-direction
            if (data->ray->sideDistX < data->ray->sideDistY)
            {
                data->ray->sideDistX += data->ray->deltaDistX;
               data->ray->mapX += data->ray->stepX;
                data->ray->side = 0;
            }
            else
            {
                data->ray->sideDistY += data->ray->deltaDistY;
                data->ray->mapY += data->ray->stepY;
                data->ray->side = 1;
            }

            //TODO change for the actual map parsing
            // Check if ray has hit a wall
            if (data->map->map[data->ray->mapX][data->ray->mapY] == '1')
                data->ray->hit = 1;

     // Calculate distance projected on camera direction
        if (data->ray->side == 0)
            data->ray->perpWallDist = (data->ray->mapX - data->ray->posX + (1 - data->ray->stepX) / 2) / data->ray->rayDirX;
        else
            data->ray->perpWallDist = (data->ray->mapY - data->ray->posY + (1 - data->ray->stepY) / 2) / data->ray->rayDirY;
        }
}

void get_wall (t_data *data)
{
       // Calculate height of line to draw on screen
        data->ray->lineHeight = (int)(HEIGHT / data->ray->perpWallDist);

        // Calculate lowest and highest pixel to fill in current stripe
        data->ray->drawStart = -data->ray->lineHeight / 2 + HEIGHT / 2;
        if (data->ray->drawStart < 0)
            data->ray->drawStart = 0;
        data->ray->drawEnd = data->ray->lineHeight / 2 + HEIGHT / 2;
        if (data->ray->drawEnd >= HEIGHT)
            data->ray->drawEnd = HEIGHT - 1;
}
