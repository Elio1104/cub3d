#include "../inc/cubed.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

unsigned int	my_mlx_get_color(t_data *data, int x, int y)
{
	char			*dst;
	unsigned int	color;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void draw_verline(t_game *game, int i, int draw_start, int draw_end, int color)
{
    while(draw_start <= draw_end)
    {
        my_mlx_pixel_put(&game->mlx_img, i, draw_start, color);
        draw_start++;
    }
}

void init_value(t_game *game, t_raycasting *ray, int i)
{
    ray->camera_x = 2 * i / (double)WIN_WIDTH - 1;
    ray->ray_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
    ray->ray_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
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
}

void init_side_dist(t_game *game, t_raycasting *ray)
{
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
}

void dist_wall(t_game *game, t_raycasting *ray)
{
    ray->hit = 0;
    while (ray->hit == 0)
    {
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
        if (game->map[ray->map_y][ray->map_x] == '1') 
        {
            ray->hit = 1;
        }
    }
    if(ray->side == 0)
        ray->wall_distance = (ray->sideDistX - ray->deltaDistX);
    else          
        ray->wall_distance = (ray->sideDistY - ray->deltaDistY);
}

void draw_line(t_game *game, t_raycasting *ray, int i)
{
    int lineHeight;
    int drawStart;
    int drawEnd;
    int color;


    double wallX; //where exactly the wall was hit
    if (ray->side == 0)
        wallX = game->player.y + ray->wall_distance * ray->ray_y;
    else           
        wallX = game->player.x + ray->wall_distance * ray->ray_x;
    wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double)(texWidth));
      if (ray->side == 0 && ray->ray_x > 0)
        texX = texWidth - texX - 1;
      if (ray->side == 1 && ray->ray_y < 0)
        texX = texWidth - texX - 1;


    lineHeight = (int)(WIN_HEIGHT / ray->wall_distance);
    drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
    if(drawStart < 0)
        drawStart = 0;
    drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
    if(drawEnd >= WIN_HEIGHT)
        drawEnd = WIN_HEIGHT - 1;
    if(ray->side == 0)
        color /= 2;
    if (drawStart != 0)
        draw_verline(game, i, 0, drawStart, game->texture.ceilling);
    if (drawEnd != WIN_HEIGHT - 1)
        draw_verline(game, i, drawEnd , WIN_HEIGHT - 1, game->texture.floor);
    int j;
    double step;
    double pos;
    j = 0;
    step = 1.0 * texHeight / lineHeight;
    pos = (drawStart - WIN_HEIGHT / 2 + lineHeight / 2) * step;
    while (j + drawStart < drawEnd)
    {
        if(ray->side == 1 && ray->ray_y < 0)
            color = my_mlx_get_color(&game->t_north, texX, (int)pos);
        else if(ray->side == 1 && ray->ray_y > 0)
            color = my_mlx_get_color(&game->t_south, texX, (int)pos);
        else if(ray->side == 0 && ray->ray_x < 0)
            color = my_mlx_get_color(&game->t_west, texX, (int)pos);
        else
            color = my_mlx_get_color(&game->t_east, texX, (int)pos);
        my_mlx_pixel_put(&game->mlx_img, i, j + drawStart, color);
        pos += step;
        j++;
    }
}

int raycasting(t_game *game)
{
    int i;
    t_raycasting *ray;

    game->mlx_img.img = mlx_new_image(game->mlx, (int)WIN_WIDTH, (int)WIN_HEIGHT);
    game->mlx_img.addr = mlx_get_data_addr(game->mlx_img.img,
			&game->mlx_img.bits_per_pixel, &game->mlx_img.line_length,
			&game->mlx_img.endian);
    ray = &game->raycast;
    move_y_player(game);
    move_x_player(game);
    move_cam(game);
    i = 0;
    while(i < WIN_WIDTH)
    {
        init_value(game, ray, i);
        init_side_dist(game, ray);
        dist_wall(game, ray);
        draw_line(game, ray ,i);
        i++;
    }
    mlx_put_image_to_window(game->mlx, game->mlx_win, game->mlx_img.img, 0, 0);
    mlx_destroy_image(game->mlx, game->mlx_img.img);
    return (0);
}
