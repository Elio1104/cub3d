#include "../inc/cubed.h"

void raycasting(t_game *game)
{
    int i;

    i = 0;
    while(i < WIN_WIDTH)
    {
        game->raycast.camera_x = 2 * i / (double)WIN_WIDTH - 1; //x-coordinate in camera space
        game->raycast.ray_x = game->player.dir_x + game->player.plane_x * game->raycast.camera_x;
        game->raycast.ray_y = game->player.dir_y + game->player.plane_y * game->raycast.camera_x;
        // printf("%f %f\n", ray_x, ray_y);
        game->raycast.map_x = (int)game->player.x;
        game->raycast.map_y = (int)game->player.y;
        if(game->raycast.ray_x == 0)
            game->raycast.deltaDistX = 1e30;
        else
            game->raycast.deltaDistX = ft_abs(1/game->raycast.ray_x);
        if(game->raycast.ray_y == 0)
            game->raycast.deltaDistY = 1e30;
        else
            game->raycast.deltaDistY = ft_abs(1/game->raycast.ray_y);
        if (game->raycast.ray_x < 0)
        {
            game->raycast.step_x = -1;
            game->raycast.sideDistX = (game->player.x - game->raycast.map_x) * game->raycast.deltaDistX;
        }
        else
        {
            game->raycast.step_x = 1;
            game->raycast.sideDistX = (game->raycast.map_x + 1.0 - game->player.x) * game->raycast.deltaDistX;
        }
        if (game->raycast.ray_y < 0)
        {
            game->raycast.step_y = -1;
            game->raycast.sideDistY = (game->player.y - game->raycast.map_y) * game->raycast.deltaDistY;
        }
        else
        {
            game->raycast.step_y = 1;
            game->raycast.sideDistY = (game->raycast.map_y + 1.0 - game->player.y) * game->raycast.deltaDistY;
        }


        i++;
    }
}