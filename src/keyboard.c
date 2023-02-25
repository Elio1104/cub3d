#include "../inc/cubed.h"

void move_y_player(t_game *game)
{
    if (game->move.move_up == 1)
    {
        if(game->map[(int)(game->player.y)][(int)(game->player.x + game->player.dir_x * MOVE_SPEED)] == '0')
            game->player.x += game->player.dir_x * MOVE_SPEED;
        if(game->map[(int)(game->player.y + game->player.dir_y * MOVE_SPEED)][(int)(game->player.x)] == '0')
            game->player.y += game->player.dir_y * MOVE_SPEED;
    }
    if (game->move.move_down == 1)
    {
        if(game->map[(int)(game->player.y)][(int)(game->player.x - game->player.dir_x * MOVE_SPEED)] == '0')
            game->player.x -= game->player.dir_x * MOVE_SPEED;
        if(game->map[(int)(game->player.y - game->player.dir_y * MOVE_SPEED)][(int)(game->player.x)] == '0')
            game->player.y -= game->player.dir_y * MOVE_SPEED;
    }
}

void move_x_player(t_game *game)
{
    if (game->move.move_left == 1)
    {
        if(game->map[(int)(game->player.y)][(int)(game->player.x + game->player.dir_y * MOVE_SPEED)] == '0')
            game->player.x += game->player.dir_y * MOVE_SPEED;
        if(game->map[(int)(game->player.y - game->player.dir_x * MOVE_SPEED)][(int)(game->player.x)] == '0')
            game->player.y -= game->player.dir_x * MOVE_SPEED;
    }
    if (game->move.move_right == 1)
    {
        if(game->map[(int)(game->player.y)][(int)(game->player.x - game->player.dir_y * MOVE_SPEED)] == '0')
            game->player.x -= game->player.dir_y * MOVE_SPEED;
        if(game->map[(int)(game->player.y + game->player.dir_x * MOVE_SPEED)][(int)(game->player.x)] == '0')
            game->player.y += game->player.dir_x * MOVE_SPEED;
    }
}

void move_cam(t_game *game)
{
    if (game->move.cam_left == 1)
    {
        double oldDirX = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED) - game->player.dir_y * sin(-ROT_SPEED);
        game->player.dir_y = oldDirX * sin(-ROT_SPEED) + game->player.dir_y * cos(-ROT_SPEED);
        double oldPlaneX = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED) - game->player.plane_y * sin(-ROT_SPEED);
        game->player.plane_y = oldPlaneX * sin(-ROT_SPEED) + game->player.plane_y * cos(-ROT_SPEED);
    }
    if (game->move.cam_right == 1)
    {
        double oldDirX = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(ROT_SPEED) - game->player.dir_y * sin(ROT_SPEED);
        game->player.dir_y = oldDirX * sin(ROT_SPEED) + game->player.dir_y * cos(ROT_SPEED);
        double oldPlaneX = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(ROT_SPEED) - game->player.plane_y * sin(ROT_SPEED);
        game->player.plane_y = oldPlaneX * sin(ROT_SPEED) + game->player.plane_y * cos(ROT_SPEED);
    }
}


int key_release(int keycode, t_game *game)
{
    if (keycode == UP)
        game->move.move_up = 0;
    else if (keycode == DOWN)
        game->move.move_down = 0;
    else if (keycode == LEFT)
        game->move.move_left = 0;
    else if (keycode == RIGHT)
        game->move.move_right = 0;
    else if (keycode == CAM_LEFT)
        game->move.cam_left = 0;
    else if (keycode == CAM_RIGHT)
        game->move.cam_right = 0;
    return (0);
}


int key_events(int keycode, t_game *game)
{
     if (keycode == ESC)
		close_window(game);
    else if (keycode == UP)
        game->move.move_up = 1;
    else if (keycode == DOWN)
        game->move.move_down = 1;
    else if (keycode == LEFT)
        game->move.move_left = 1;
    else if (keycode == RIGHT)
        game->move.move_right = 1;
    else if (keycode == CAM_LEFT)
        game->move.cam_left = 1;
    else if (keycode == CAM_RIGHT)
        game->move.cam_right = 1;
    return (0);
}