#include "cube.h"

static mlx_image_t* image;

// -----------------------------------------------------------------------------


t_data	*get_data(void)

{
	static t_data	*var = NULL;

	if (!var)
	{
		var = ft_calloc(1, sizeof(t_data));

		return (var);
	}
	return (var);
}


//donne la couleur selon le niveau de rgba
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_render(void* param)
{
    (void)param;
    int32_t i = 0;
    int32_t y = 0;
  
    while (i < (int32_t)image->width)
    {
        y = 0;
        while (y < (int32_t)image->height)
        {
            mlx_put_pixel(image, i, y, 243);
            y++;
        }
        i++;
    }
}

void ft_hook(void* param)
{
    mlx_t* mlx = param;
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
        "   111    111111111 111111111    1  "
    };

    // Store the previous position of the image instance (center)
    int prevCenterX = image->instances[0].x + 32;  // Center X coordinate (64x64 image)
    int prevCenterY = image->instances[0].y + 32;  // Center Y coordinate (64x64 image)

    // Calculate the new position based on user input
    int newCenterX = prevCenterX;
    int newCenterY = prevCenterY;

    if (mlx_is_key_down(mlx, MLX_KEY_UP))
        newCenterY -= 10;
    if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
        newCenterY += 10;
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
        newCenterX -= 10;
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
        newCenterX += 10;

    // Define the collider dimensions around the center
    int colliderWidth = 30;
    int colliderHeight = 30;

    // Calculate the top-left and bottom-right corners of the collider box
    int topLeftX = newCenterX - colliderWidth / 2;
    int topLeftY = newCenterY - colliderHeight / 2;
    int bottomRightX = newCenterX + colliderWidth / 2;
    int bottomRightY = newCenterY + colliderHeight / 2;

    // Convert coordinates to grid cells
    int gridTopLeftX = topLeftX / 64;
    int gridTopLeftY = topLeftY / 64;
    int gridBottomRightX = bottomRightX / 64;
    int gridBottomRightY = bottomRightY / 64;

    // Check for collisions within the collider box
    int hasCollision = 0;

    for (int x = gridTopLeftX; x <= gridBottomRightX; x++) {
        for (int y = gridTopLeftY; y <= gridBottomRightY; y++) {
            if (map[y][x] == '1') {
                hasCollision = 1;
                break;
            }
        }
    }

    // If there's a collision, reset the position to the previous valid position
    if (hasCollision) {
        newCenterX = prevCenterX;
        newCenterY = prevCenterY;
    }

    // Update the instance's position
    image->instances[0].x = newCenterX - 32;
    image->instances[0].y = newCenterY - 32;

    // Handle other key presses
    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx);
}


void	png_to_texture(void)
{
	t_data	*var;

	var = get_data();

	var->wall = mlx_load_png("./asset/wall.png");
	var->grass = mlx_load_png("./asset/grass.png");
	var->penguin = mlx_load_png("./asset/penguin.png");
}

void	texture_to_image(void)
{
	t_data	*var;

	var = get_data();
	
	var->wall_img = mlx_texture_to_image(var->mlx, var->wall);
	var->grass_img = mlx_texture_to_image(var->mlx, var->grass);
	var->penguin_img = mlx_texture_to_image(var->mlx, var->penguin);

}


void	render_asset(int x, int y)
{
	t_data	*var;

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
		"   111    111111111 111111111    1  "
    };
	if (map[x][y] == '1')
		mlx_image_to_window(var->mlx, var->wall_img, y * 64, x * 64);
	else if (map[x][y] == 'N')
	{
		mlx_image_to_window(var->mlx, var->penguin_img, y * 64, x * 64);
	}
	else if (map[x][y] == '0')
		mlx_image_to_window(var->mlx, var->grass_img, y * 64, x * 64);
}

void	render(void)
{
	t_data		*var;
	int			x;
	int			y;


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






int main(int ac, const char* av[])
{
	t_data *data;

    (void)ac;
    (void)av;
	data = get_data();

	// Gotta error check this stuff
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

//create basic map
	png_to_texture();
	texture_to_image();
	render();

//create player  instance
	if (!(image = mlx_new_image(data->mlx, 64, 64)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
//create window + player
	if (mlx_image_to_window(data->mlx, image, 1700, 760) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	mlx_loop_hook(data->mlx, ft_render, data->mlx);
	mlx_loop_hook(data->mlx, ft_hook, data->mlx);

	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}