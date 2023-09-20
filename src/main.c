#include "cube.h"

t_player player;
 mlx_image_t *map;

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
uint32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_hook(void *param)
{
    mlx_t *mlx = param;
    // char map[15][39] = {
    //     "            11111111111111111111111",
    //     "11111111111111111111111111111111111",
    //     "10000000001100000000000010000000001",
    //     "10110000011100000000000010000000001",
    //     "10010000000000000000000010000000001",
    //     "11111111101100000111000000000000001",
    //     "10000000001100000111011110011111111",
    //     "11110111111111011100000010001       ",
    //     "11110111111111011101010010001       ",
    //     "11000000110101011100000010001       ",
    //     "10000000000000001100000010001       ",
    //     "10000000000000001101010010001       ",
    //     "11000001110101011111011110N0111     ",
    //     "111101111110101101111010001111111111",
    //     "   111    111111111 111111111    1  "
    // };

    mlx_put_pixel(map, player.x, player.y, ft_pixel(255,0,0,255));
    printf("marche tu tbk \n");
    // Handle key presses to update position
    if (mlx_is_key_down(mlx, MLX_KEY_UP))
       player.y -= 10;
    if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
        player.y += 10;
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
        player.x -= 10;
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
       player.x += 10;
}

void png_to_texture(void)
{
    t_data *var;

    var = get_data();

    var->wall = mlx_load_png("./asset/wall.png");
    var->grass = mlx_load_png("./asset/grass.png");
    var->penguin = mlx_load_png("./asset/penguin.png");
}

void texture_to_image(void)
{
    t_data *var;

    var = get_data();

    var->wall_img = mlx_texture_to_image(var->mlx, var->wall);
    var->grass_img = mlx_texture_to_image(var->mlx, var->grass);
    var->penguin_img = mlx_texture_to_image(var->mlx, var->penguin);
}

void render_asset(int x, int y)
{
    t_data *var;

    var = get_data();
    char map[15][39] = {
        "            11111111111111111111111",
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
    if (map[x][y] == '1')
        mlx_image_to_window(var->mlx, var->wall_img, y * 64, x * 64);
    else if (map[x][y] == 'N')
    {
        mlx_image_to_window(var->mlx, var->penguin_img, y * 64, x * 64);
    }
    else if (map[x][y] == '0')
        mlx_image_to_window(var->mlx, var->grass_img, y * 64, x * 64);
}

void render(void)
{
    t_data *var;
    int x;
    int y;

    var = get_data();

    var->height = 15;
    var->width = 39;

    y = 0;
    while (y < var->width)
    {
        x = 0;
        while (x < var->height)
        {
            render_asset(x, y);
            x++;
        }
        y++;
    }
}

// -----------------------------------------------------------------------------

int main(int ac, const char *av[])
{
    t_data *data;
   

    (void)ac;
    (void)av;
    data = get_data();

    player.x=0;
    player.y=0;
    
    // Gotta error check this stuff
    if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true)))
    {
        puts(mlx_strerror(mlx_errno));
        return (EXIT_FAILURE);
    }
   map = mlx_new_image(data->mlx,WIDTH, HEIGHT );
   mlx_image_to_window(data->mlx, map, 0, 0);

    // create basic map
    png_to_texture();
    texture_to_image();
    //render map
    //render();

    mlx_loop_hook(data->mlx, ft_hook, data->mlx);

    mlx_loop(data->mlx);
    mlx_terminate(data->mlx);
    return (EXIT_SUCCESS);
}