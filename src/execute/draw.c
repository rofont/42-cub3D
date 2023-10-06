#include "../cube.h"

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


/// @brief /TODO FIX the color gradient / transparency 4 param instead of 3 rgb ......
/// @param data 
void draw_floor_sky (t_data *data)
{
    int x;
    int y;
    x=0;
    y=0;
    while(y < HEIGHT/2)
    {
        while (x < WIDTH)
        {
             mlx_put_pixel(data->canvas, x, y, data->map->ceiling);
             ////TODO ANIMATION BS
            data->map->ceiling--;
            ////////
             x++;
        }
        x=0;
        y++;
    }
     while(y < HEIGHT)
     {
           while (x < WIDTH)
        {
            //TODO rig with the floor color 
             mlx_put_pixel(data->canvas, x, y, data->map->floor);
             x++;
        }
        x=0;
        y++;
     }
}