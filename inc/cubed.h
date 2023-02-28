/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alondot <alondot@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:52:04 by alondot           #+#    #+#             */
/*   Updated: 2023/02/28 15:13:20 by alondot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "../lib/libft/includes/libft.h"
# include "../lib/libft/includes/ft_printf.h"
# include "../lib/libft/includes/get_next_line.h"
# include "../lib/mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

typedef struct s_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_texture {
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		floor;
	int		ceilling;
}	t_texture;

typedef struct s_move {
	int	move_up;
	int	move_down;
	int	move_left;
	int	move_right;
	int	cam_left;
	int	cam_right;
}	t_move;

typedef struct s_raycasting {
	double	ray_x;
	double	ray_y;
	double	camera_x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	double	wall_distance;
}	t_raycasting;

typedef struct s_player{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_game {
	char			**map;
	t_data			mlx_img;
	int				fd;
	int				orientation;
	void			*mlx;
	void			*mlx_win;
	t_move			move;
	t_texture		texture;
	t_player		player;
	t_raycasting	raycast;
	t_data			t_north;
	t_data			t_south;
	t_data			t_east;
	t_data			t_west;
}	t_game;

# define NORTH 1
# define SOUTH 2
# define EAST 3
# define WEST 4

# define FOV 0.9
# define MOVE_SPEED 0.04
# define ROT_SPEED 0.04

# define ESC 53
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define CAM_LEFT 123
# define CAM_RIGHT 124

# define WIN_WIDTH 1366
# define WIN_HEIGHT 768
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define NO_PL 101
# define TOO_MUCH_PL 102
# define WRONG_FILL 103
# define WRONG_LAYOUT 104

//main
void			get_file(char **argv, t_game *game);
void			checking_arg(int argc, char **argv, t_game *game);
void			init_player(t_game *game);
void			init_struct(t_game *game);

//map
char			**get_map(int fd, char *line);
void			check_nswe(t_game *game);
int				nswe(t_game *game, int i, int j);
void			get_player(t_game *game);
void			check_layout(t_game *game);

//raycasting
int				raycasting(t_game *game);
void			calculate_text_x(t_game *game, t_raycasting *ray,
					double *wall_x, int *text_x);
void			dist_wall(t_game *game, t_raycasting *ray);
void			init_side_dist(t_game *game, t_raycasting *ray);
void			init_value(t_game *game, t_raycasting *ray, int i);

//draw
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			draw_ceilling(t_game *game, int i,
					int draw_start, int draw_end);
void			draw_floor(t_game *game, int i, int draw_start, int draw_end);
void			draw_line(t_game *game, t_raycasting *ray, int i);
void			draw_texture(t_game *game,
					t_raycasting *ray, int text_x, int i);

//texture
unsigned int	my_mlx_get_color(t_data *data, int x, int y);
void			check_texture(t_game *game, char *line);
t_data			texture_load(char *path, t_game *game);
void			init_texture(t_game *game);
char			*get_texture(t_game *game);

//texture_bis
int				is_texture(t_game *game, char *line);
int				strcmp_texture(t_game *game, char **tab, char *line);
void			stock_texture(t_game *game,
					char **tab, char **texture, char *line);
int				ft_strisdigit(char *str);

//rgb
int				line_not_empty(char *str);
int				create_trgb(int t, int r, int g, int b);
int				get_rgb(char **tab);
void			stock_rgb(t_game *game, char **tab, int *rgb, char *line);
void			check_nb_arg(t_game *game, char **new_tab,
					char *line, char **tab);

//utils
void			free_tab(char **tab);
void			free_texture(t_game *game);
void			free_struct(t_game *game);
double			ft_abs(double x);
int				close_window(t_game *game);

//error
void			free_close(char *str, char **tab);
void			ft_error(char *str, t_game *game);
void			ft_error_code(int code, t_game *game);
void			check_error_map(t_game *game, int i, int j);
char			*code_erreur(int code);

//keyboard
int				key_events(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
void			move_y_player(t_game *game);
void			move_x_player(t_game *game);
void			move_cam(t_game *game);

#endif
