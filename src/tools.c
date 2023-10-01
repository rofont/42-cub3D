#include "cube.h"

///TODO remove temp map
char map3[9][9] = {
    "111111111",
    "110010011",
    "100000001",
    "100000001",
    "110010011",
    "100000001",
    "100000001",
    "110010011",
    "111111111"};

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
    t_data *data;

    data = get_data();
    int y;
    for (y = startY; y <= drawEnd; y++)
    {
        mlx_put_pixel(data->canvas, x, y, color);
    }
}