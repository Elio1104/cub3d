#include "../inc/cubed.h"

void move_y_player(int keycode, t_game *game)
{
    if (keycode == UP)
    {
        if(game->map[(int)(game->player.y)][(int)(game->player.x + game->player.dir_x * MOVE_SPEED)] == '0')
            game->player.x += game->player.dir_x * MOVE_SPEED;
        if(game->map[(int)(game->player.y + game->player.dir_y * MOVE_SPEED)][(int)(game->player.x)] == '0')
            game->player.y += game->player.dir_y * MOVE_SPEED;
    }
    if (keycode == DOWN)
    {
        if(game->map[(int)(game->player.y)][(int)(game->player.x - game->player.dir_x * MOVE_SPEED)] == '0')
            game->player.x -= game->player.dir_x * MOVE_SPEED;
        if(game->map[(int)(game->player.y - game->player.dir_y * MOVE_SPEED)][(int)(game->player.x)] == '0')
            game->player.y -= game->player.dir_y * MOVE_SPEED;
    }
}

void move_x_player(int keycode, t_game *game)
{
    if (keycode == LEFT)
    {
        if(game->map[(int)(game->player.y)][(int)(game->player.x + game->player.dir_y * MOVE_SPEED)] == '0')
            game->player.x += game->player.dir_y * MOVE_SPEED;
        if(game->map[(int)(game->player.y - game->player.dir_x * MOVE_SPEED)][(int)(game->player.x)] == '0')
            game->player.y -= game->player.dir_x * MOVE_SPEED;
    }
    if (keycode == RIGHT)
    {
        if(game->map[(int)(game->player.y)][(int)(game->player.x - game->player.dir_y * MOVE_SPEED)] == '0')
            game->player.x -= game->player.dir_y * MOVE_SPEED;
        if(game->map[(int)(game->player.y + game->player.dir_x * MOVE_SPEED)][(int)(game->player.x)] == '0')
            game->player.y += game->player.dir_x * MOVE_SPEED;
    }
}

void move_cam(int keycode, t_game *game)
{
    if (keycode == CAM_LEFT)
    {
        double oldDirX = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED) - game->player.dir_y * sin(-ROT_SPEED);
        game->player.dir_y = oldDirX * sin(-ROT_SPEED) + game->player.dir_y * cos(-ROT_SPEED);
        double oldPlaneX = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED) - game->player.plane_y * sin(-ROT_SPEED);
        game->player.plane_y = oldPlaneX * sin(-ROT_SPEED) + game->player.plane_y * cos(-ROT_SPEED);
    }
    if (keycode == CAM_RIGHT)
    {
        double oldDirX = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(ROT_SPEED) - game->player.dir_y * sin(ROT_SPEED);
        game->player.dir_y = oldDirX * sin(ROT_SPEED) + game->player.dir_y * cos(ROT_SPEED);
        double oldPlaneX = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(ROT_SPEED) - game->player.plane_y * sin(ROT_SPEED);
        game->player.plane_y = oldPlaneX * sin(ROT_SPEED) + game->player.plane_y * cos(ROT_SPEED);
    }
}

int key_events(int keycode, t_game *game)
{
    if (keycode == ESC)
		close_window(game);
    move_y_player(keycode, game);
    move_x_player(keycode, game);
    move_cam(keycode, game);
    return (0);
}