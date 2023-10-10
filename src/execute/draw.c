#include "../cube.h"

void draw_filled_circle(mlx_image_t *image, int centerX, int centerY, int radius, uint32_t color)
{
    int x = centerX - radius;
    while (x <= centerX + radius && x <= WIDTH- radius)
    {
        int y = centerY - radius;
        while (y <= centerY + radius && y<=HEIGHT -radius)
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
            // data->map->ceiling++;
            // data->map->floor++;
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

// draw minimap------
void draw_minimap(t_data *data)
{
    int scale_factor = 5;
    int i = 0;
    while (i < data->map->map_height) // Use map_height for rows
    {
        int j = 0;
        while (j < data->map->map_width) // Use map_width for columns
        {
            uint32_t color;
            if (data->map->map[i][j] == '0')
                color = ft_color(255, 255, 255, 255);
            else if (data->map->map[i][j] == '1')
                color = ft_color(0, 0, 0, 255);
            else
                color = ft_color(0, 0, 0, 100);

            // Calculate the pixel coordinates for the current square
            int startX = j * scale_factor;
            int startY = i * scale_factor;
            int x = startX;
            while (x < startX + scale_factor)
            {
                int y = startY;
                while (y < startY + scale_factor)
                {
                    mlx_put_pixel(data->canvas, x, y, color);
                    y++;
                }
                x++;
            }
            j++;
        }
        i++;
    }
}
