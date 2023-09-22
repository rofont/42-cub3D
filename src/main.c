#include "cube.h"

t_player player;
mlx_image_t *map;
  // Scale factor for each square
    int scaleFactor = 40;
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

int is_collision(int playerX, int playerY, int playerRadius)
{


    // Convert player's pixel coordinates to grid coordinates
    int gridX = playerX / scaleFactor;
    int gridY = playerY / scaleFactor;

    // Calculate the grid cell that the player's center falls into
    char cell = map1[gridY][gridX];

    // Check if the player's grid cell contains a wall ('1')
    if (cell == '1')
    {
        // Calculate the distance from the player's center to the center of the cell
        int cellCenterX = gridX * scaleFactor + scaleFactor / 2;
        int cellCenterY = gridY * scaleFactor + scaleFactor / 2;
        int dx = playerX - cellCenterX;
        int dy = playerY - cellCenterY;

        // Check if the distance is less than the sum of player's radius and half cell size
        if (dx * dx + dy * dy <= (playerRadius + scaleFactor / 2) * (playerRadius + scaleFactor / 2))
        {
            // Collision detected
            return 1;
        }
    }
    // No collision
    return 0;
}

// void draw_line(mlx_image_t *image, int x1, int y1, int x2, int y2, uint32_t color)
// {
//     int dx = abs(x2 - x1);
//     int dy = abs(y2 - y1);
//     int sx, sy;

//     if (x1 < x2)
//         sx = 1;
//     else
//         sx = -1;

//     if (y1 < y2)
//         sy = 1;
//     else
//         sy = -1;

//     int err = dx - dy;

//     while (x1 != x2 || y1 != y2)
//     {
//         mlx_put_pixel(image, x1, y1, color);
//         int e2 = 2 * err;

//         if (e2 > -dy)
//         {
//             err -= dy;
//             x1 += sx;
//         }

//         if (e2 < dx)
//         {
//             err += dx;
//             y1 += sy;
//         }
//     }
// }

//void draw_line_from_angle(mlx_image_t *image, int playerX, int playerY, float playerAngle, int lineLength, uint32_t color)
// {
//     // Convert playerAngle from degrees to radians
//     float angleRad = playerAngle * M_PI / 180.0;

//     // Calculate the endpoint coordinates
//     int lineEndX = playerX + (int)(lineLength * cos(angleRad));
//     int lineEndY = playerY + (int)(lineLength * sin(angleRad));

//     // Use the draw_line function to draw the line
//     draw_line(image, playerX, playerY, lineEndX, lineEndY, color);
// }


void draw_wall(mlx_image_t *image, float distance, float playerAngle, int wallX)
{
    // Define FOV and other constants
    float fov = 60.0; // Field of view angle in degrees
    int numRays = WIDTH; // Number of rays (one per pixel)
    float rayAngleIncrement = fov / numRays;

    // Calculate the angle for the current ray
    float rayAngle = playerAngle - (fov / 2) + wallX * rayAngleIncrement;
    rayAngle = fmod(rayAngle, 360.0); // Ensure the angle is within [0, 360)

    // Calculate the height of the wall based on its distance for perspective
    int wallHeight = (int)(HEIGHT / distance);

    // Calculate the Y-coordinates for the top and bottom of the wall segment
    int wallTop = (HEIGHT - wallHeight) / 2;
    int wallBottom = wallTop + wallHeight;

    // Draw the wall segment on the screen as a vertical line
    for (int y = wallTop; y < wallBottom; y++)
    {
        mlx_put_pixel(image, wallX, y, ft_color(0, 255, 0, 255)); // Set color for the wall
    }
}




// int line_length_before_collision ()
void draw_line_from_angle_stop_on_collision(mlx_image_t *image, int playerX, int playerY, float playerAngle, uint32_t color)
{

    player.radius =1;
    int lineLength = 5000;
    
    // Convert playerAngle from degrees to radians
    float angleRad = playerAngle * M_PI / 180.0;

    // Calculate the endpoint coordinates
    int lineEndX = playerX + (int)(lineLength * cos(angleRad));
    int lineEndY = playerY + (int)(lineLength * sin(angleRad));


printf("lineendx = %i\n", lineEndX);
printf("lineendy = %i\n", lineEndY);
 
    // Step size for drawing the line
    int step = 1;

    // Determine the direction of the line (positive or negative step)
    if (lineEndX < playerX)
        step = -1;

    // Calculate the slope of the line
    float slope = (float)(lineEndY - playerY) / (float)(lineEndX - playerX);

    int x = playerX;
    int y = playerY;

    while ((step ==  1 && x <= lineEndX) || (step == -1 && x >= lineEndX))
    {
        // Check for collision at the current position
        if (is_collision(x, y, player.radius)) // Assuming playerRadius is 10 for collision check
        {
            break; // Stop drawing if a collision is detected
        }

        // Check if the current position is outside the environment boundaries
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        {
            break; // Stop drawing if outside boundaries
        }

        // Draw the pixel at the current position
       mlx_put_pixel(image, x, y, color);

        // Calculate the next position
        x += step;
        y = playerY + (int)(slope * (x - playerX));
    }
  // Calculate the distance to the current position
        int dx = x - playerX;
        int dy = y - playerY;
        int distance = sqrt(dx * dx + dy * dy);
        printf("Distance to endpoint: %i\n", distance);
          // Check if the current position is outside the environment boundaries

      draw_wall(image,distance, player.angle, lineEndX);
   
        


}


double deg_to_rad(double degree)
{
    // Convert playerAngle from degrees to radians
    return (degree * M_PI / 180.0);
}

// 

float calculate_wall_distance(int playerX, int playerY, float rayAngle)
{
    // Constants
    float maxDistance = 1000.0; // Maximum distance to check
    float rayStepSize = 1.0;   // Step size for ray casting
    float distance = 0.0;      // Current distance from the player

    // Convert rayAngle from degrees to radians
    float angleRad = rayAngle * M_PI / 180.0;

    // Start ray casting
    float rayX = playerX;
    float rayY = playerY;

    while (distance < maxDistance)
    {
        // Calculate the next position along the ray
        rayX += rayStepSize * cos(angleRad);
        rayY += rayStepSize * sin(angleRad);

        // Convert the ray position to grid coordinates
        int gridX = (int)(rayX / scaleFactor);
        int gridY = (int)(rayY / scaleFactor);

        // Check if the grid coordinates are within the map bounds
        if (gridX >= 0 && gridX < 16 && gridY >= 0 && gridY < 39)
        {
            // Check if the current cell is a wall ('1')
            if (map1[gridY][gridX] == '1')
            {
                // Calculate the distance to the wall using the Pythagorean theorem
                float dx = rayX - playerX;
                float dy = rayY - playerY;
                return sqrt(dx * dx + dy * dy);
            }
        }

        // Increment the distance
        distance += rayStepSize;
    }

    // If no wall is hit within the maximum distance, return the maximum distance
    return maxDistance;
}




void draw_field_of_view(mlx_image_t *image, int playerX, int playerY)
{
    // Define FOV and other constants
    float fov = 60.0; // Field of view angle in degrees
    int numRays = WIDTH; // Number of rays (one per pixel)
    float rayAngleIncrement = fov / numRays;

    // Calculate the starting angle for the FOV
    float startAngle = player.angle - (fov / 2);

    // Iterate over the entire FOV and draw rays
    for (int wallX = 0; wallX < WIDTH; wallX++)
    {
        // Calculate the angle for the current ray
        float rayAngle = startAngle + wallX * rayAngleIncrement;
        rayAngle = fmod(rayAngle, 360.0); // Ensure the angle is within [0, 360)

        // Use rayAngle to calculate the distance to the wall (you need to implement this)
        float distance = calculate_wall_distance(playerX, playerY, rayAngle);

        // Draw the wall segment
        draw_wall(image, distance, player.angle, wallX);
    }
}

void draw_line_from_angle_stop_on_collision2(mlx_image_t *image, int playerX, int playerY, float playerAngle, uint32_t color)
{

    player.radius =10;
    int lineLength = 5000;
    
    // Convert playerAngle from degrees to radians
    float angleRad = playerAngle * M_PI / 180.0;

    // Calculate the endpoint coordinates
    int lineEndX = playerX + (int)(lineLength * cos(angleRad));
    int lineEndY = playerY + (int)(lineLength * sin(angleRad));


printf("lineendx = %i\n", lineEndX);
printf("lineendy = %i\n", lineEndY);
 
    // Step size for drawing the line
    int step = 1;

    // Determine the direction of the line (positive or negative step)
    if (lineEndX < playerX)
        step = -1;

    // Calculate the slope of the line
    float slope = (float)(lineEndY - playerY) / (float)(lineEndX - playerX);

    int x = playerX;
    int y = playerY;

    while ((step ==  1 && x <= lineEndX) || (step == -1 && x >= lineEndX))
    {
        // Check for collision at the current position
        if (is_collision(x, y, player.radius)) // Assuming playerRadius is 10 for collision check
        {
            break; // Stop drawing if a collision is detected
        }

        // Check if the current position is outside the environment boundaries
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        {
            break; // Stop drawing if outside boundaries
        }

        // Draw the pixel at the current position
       mlx_put_pixel(image, x, y, color);

        // Calculate the next position
        x += step;
        y = playerY + (int)(slope * (x - playerX));
    }
  // Calculate the distance to the current position
        int dx = x - playerX;
        int dy = y - playerY;
        int distance = sqrt(dx * dx + dy * dy);
        printf("Distance to endpoint: %i\n", distance);
          // Check if the current position is outside the environment boundaries

   
   
        


}

void draw_field_of_view2(mlx_image_t *image, int playerX, int playerY)
{
      // Draw the field of view with rays
    int numRays = 4000; // Adjust the number of rays as needed
    int fovAngle =60; // Adjust the field of view angle as needed
    
    
    // Calculate the angle increment between rays
    float angleIncrement = (float)fovAngle / (float)(numRays - 1);

    // Start angle for the first ray
    float startAngle = player.angle - (float)(fovAngle / 2);

    // Iterate over the number of rays
    for (int i = 0; i < numRays; i+=20)
    {
        // Calculate the angle for the current ray
        float currentAngle = startAngle + i * angleIncrement;

        // Call draw_line_from_angle_stop_on_collision for the current ray
        draw_line_from_angle_stop_on_collision2(image, playerX, playerY, currentAngle,ft_color(255,0,0,255));
    }
}





void ft_hook(void *param)
{
    mlx_t *mlx = param;
    t_data *data;

    data = get_data();

    //reset_pixel
    reset_window(map);

// draw minimap------

    // Original map dimensions (15x39)
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
            int startX = j * scaleFactor;
            int startY = i * scaleFactor;
            int x = startX;
            while (x < startX + scaleFactor)
            {
                int y = startY;
                while (y < startY + scaleFactor)
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
    int playerRadius = 10; // Adjust the radius as needed
    draw_filled_circle(map, player.x, player.y, playerRadius, ft_color(255, 0, 0, 255));


//draw raycast


draw_field_of_view(map, player.x, player.y);
draw_field_of_view2(map, player.x, player.y);








///-----player_move
    // Handle key presses to update position
    float moveSpeed = 4.0; // Adjust the movement speed as needed

    if (mlx_is_key_down(mlx, MLX_KEY_W))
    {
        // Calculate the new position based on the player's angle
        float angleRad = deg_to_rad(player.angle);
        int newX = player.x + (int)(moveSpeed * cos(angleRad));
        int newY = player.y + (int)(moveSpeed * sin(angleRad));

        // Check for collision before updating the position
        if (!is_collision(newX, newY, playerRadius))
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
        if (!is_collision(newX, newY, playerRadius))
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
        if (!is_collision(newX, newY, playerRadius))
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
        if (!is_collision(newX, newY, playerRadius))
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

    player.x = 100;
    player.y = 80;
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