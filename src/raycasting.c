#include "../inc/cubed.h"

void draw_verline(t_game *game, int i, int draw_start, int draw_end, int color)
{
    while(draw_start <= draw_end)
    {
        mlx_pixel_put(game->mlx, game->mlx_win, i, draw_start, color);
        draw_start++;
    }
}


void raycasting(t_game *game)
{
    int i;
    t_raycasting *ray;

    ray = &game->raycast;
    i = 0;
    while(i < WIN_WIDTH)
    {
        ray->camera_x = 2 * i / (double)WIN_WIDTH - 1; //x-coordinate in camera space
        ray->ray_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
        ray->ray_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
        // printf("%f %f\n", ray_x, ray_y);
        ray->map_x = (int)game->player.x;
        ray->map_y = (int)game->player.y;
        if(ray->ray_x == 0)
            ray->deltaDistX = 1e30;
        else
            ray->deltaDistX = ft_abs(1/ray->ray_x);
        if(ray->ray_y == 0)
            ray->deltaDistY = 1e30;
        else
            ray->deltaDistY = ft_abs(1/ray->ray_y);
        if (ray->ray_x < 0)
        {
            ray->step_x = -1;
            ray->sideDistX = (game->player.x - ray->map_x) * ray->deltaDistX;
        }
        else
        {
            ray->step_x = 1;
            ray->sideDistX = (ray->map_x + 1.0 - game->player.x) * ray->deltaDistX;
        }
        if (ray->ray_y < 0)
        {
            ray->step_y = -1;
            ray->sideDistY = (game->player.y - ray->map_y) * ray->deltaDistY;
        }
        else
        {
            ray->step_y = 1;
            ray->sideDistY = (ray->map_y + 1.0 - game->player.y) * ray->deltaDistY;
        }
        ray->hit = 0;
        while (ray->hit == 0)
        {
            //jump to next map square, either in x-direction, or in y-direction
            if (ray->sideDistX < ray->sideDistY)
            {
                ray->sideDistX += ray->deltaDistX;
                ray->map_x += ray->step_x;
                ray->side = 0;
            }
            else
            {
                ray->sideDistY += ray->deltaDistY;
                ray->map_y += ray->step_y;
                ray->side = 1;
            }
            //Check if ray has hit a wall
            if (game->map[ray->map_y][ray->map_x] == '1') 
            {
                ray->hit = 1;
            }
        }
        if(ray->side == 0)
            ray->wall_distance = (ray->sideDistX - ray->deltaDistX);
        else          
            ray->wall_distance= (ray->sideDistY - ray->deltaDistY);
        printf("%d :%f\n", i, ray->wall_distance);

        int lineHeight = (int)(WIN_HEIGHT / ray->wall_distance);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
        if(drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
        if(drawEnd >= WIN_HEIGHT)
            drawEnd = WIN_HEIGHT - 1;
        int color = 16711680;
        if(ray->side == 0)
            color /= 2;
        draw_verline(game, i, drawStart, drawEnd, color);
        i++;
    }
    
}