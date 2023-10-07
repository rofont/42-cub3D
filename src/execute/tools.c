#include "../cube.h"

//put black pixel everywhere
void reset_window(t_data *data)
{
    int x = 0;
    while (x < WIDTH)
    {
        int y = 0;
        while (y < HEIGHT)
        {
            mlx_put_pixel(data->canvas, x, y, ft_color(0, 0, 0, 255)); // Set pixel to black
            y++;
        }
        x++;
    }
}

// donne la couleur selon le niveau de rgba
uint32_t ft_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void verLine(int x, int startY, int drawEnd, uint32_t color)
{
    t_data *data;

    data = get_data();
    int y;
    for (y = startY; y <= drawEnd; y++)
    {
        mlx_put_pixel(data->canvas, x, y, color);
    }
}

int is_player (char c)
{
    if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
        return (1);
    else
        return(0);
}

