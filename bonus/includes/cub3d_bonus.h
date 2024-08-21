/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:03:33 by plang             #+#    #+#             */
/*   Updated: 2024/08/20 17:32:20 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WALL "textures/wall.png"
# define GROUND "textures/ground.png"

# define INVTXTMAP "Error\nTextures or map invalid\n"
# define INVRGB "Error\nRGB not valid\n"
# define INVFILE "Error\nCan not open file\n"
# define INVCUB "Error\nWe need a .cub file\n"
# define INVWALLS "Error\nBuilding blocks are invalid\n"
# define INVPCOUNT "Error\nNot the right amount of players\n"
# define MALLOCFAIL "Error\nMalloc failed\n"
# define MLXLPFAIL "Error\nMLX load png failed\n"
# define MLXTXTFAIL "Error\nMLX texture to img failed\n"

# define PI 3.14159265358979323846
# define FOV 60
# define DEGREE 0.01745329
# define STEPSIZE 1
# define DOORTXT "./textures/DOOR_1A.PNG"

# define SCREENWIDTH  1200// HIGHER VALUES WILL CAUSE LAG
# define SCREENLENGTH 800 // HIGHER VALUES WILL CAUSE LAG

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

typedef struct s_fcheck
{
	double		cameraposy;
	double		cameraposx;
	char		playerstartpos;

	int			map_size;
	int			linecount;
	int			count;
	int			map_start;
	int			info;
	int			error;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*sky;
	char		*ground;
	uint32_t	top;
	uint32_t	bottom;
	char		**mapcpy;
	char		**file;
}	t_fcheck;

typedef struct s_wall
{
	mlx_texture_t	*door;
	mlx_texture_t	*txt[4];
	int				side;
	double			x;
	double			y;
	double			ty_off;
	double			ty_step;
}	t_wall;

typedef struct s_map
{
    bool waiting;
    double elapsed_time;
	int wait_stage;
	
	int				fd;
	int				linecount;
	int				wallcount;
	int				lenght;
	int				info_set;
	int				map_start;
	int				map_size;
	int				size;

	uint32_t		floor;
	uint32_t		ceiling;

	double			pa;

	int				side;

	double			diry;
	double			dirx;

	double			raydirx;
	double			raydiry;
	double			raypa;

	double			rayposy;
	double			rayposx;

	double			cameraposy;
	double			cameraposx;

	double			wallx;

	int				stepy;
	int				stepx;

	t_wall			wall;
	
	int				is_door;

	double			deltadisty;
	double			deltadistx;

	int				mapy;
	int				mapx;

	int				lastx;
	int				lasty;

	int				mouse_enabled;
	int32_t			mx;
	int32_t			my;

	int				rayamount;

	double			firstray[2]; // 0 for x // 1 for y

	char			playerstartpos;
	char			**mapsave;
	char			**mapcopy;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*surface;
	char			*sky;
	mlx_t			*mlx;

	mlx_image_t		*background;
	mlx_texture_t	*background_txt;

	mlx_image_t		*gun1;
	mlx_texture_t	*gun1_txt;
	
	mlx_image_t		*gun2;
	mlx_texture_t	*gun2_txt;
	
	mlx_image_t		*gun3;
	mlx_texture_t	*gun3_txt;
	
	mlx_image_t		*gun4;
	mlx_texture_t	*gun4_txt;

	int				gunpos;
	int				gunway;
}	t_map;

//parsing files

/* ************************************************************************** */
/*                              file_reader.c                                 */
/* ************************************************************************** */
int			count_file_lines(char *map_name, int count);
void		read_file(char *map_name, int count, t_map *map);
void		get_map_information(t_fcheck *check);
int			check_rest(t_fcheck *check, int i);
void		argument_check(char *argv);

/* ************************************************************************** */
/*                           file_reader_utils.c                              */
/* ************************************************************************** */
void		data_transfer(t_map *map, t_fcheck *check);
void		data_reading(t_fcheck *check);

/* ************************************************************************** */
/*                             map_validation.c                               */
/* ************************************************************************** */
void		looptrough(t_fcheck *check, char *str, int count);
void		direction_check(t_fcheck *check, int *invalid, int *i, int *j);
int			check_char(char c);
void		map_boarder_check(t_fcheck *check);
void		check_player_and_boarder(t_fcheck *check);

/* ************************************************************************** */
/*                             rgb_validation.c                               */
/* ************************************************************************** */
void		rgb_free(char **strings);
uint32_t	bitshift_rgba(int r, int g, int b, int a);
int			check_int_of_rgb(t_fcheck *check, char **surface);
void		check_rgb_floor(t_fcheck *check);
void		check_rgb_ceiling(t_fcheck *check);

/* ************************************************************************** */
/*                            input_extractor.c                               */
/* ************************************************************************** */
int			extract_and_set_info1(char *str, int info_set, t_fcheck *check);
int			extract_and_set_info2(char *str, int info_set, t_fcheck *check);
char		*check_and_set_info(char *str, char *info, t_fcheck *check);
void		check_info_flag(t_fcheck *check, int i);
void		check_failed_info_flag(t_fcheck *check);

/* ************************************************************************** */
/*                             input_cleaner.c                                */
/* ************************************************************************** */
void		clean_from_space_nl(char **str);
void		clean_from_nl(char **str);
void		clean_cardinal_directions(char **str);
void		clean_input_strings(t_fcheck *check);

/* ************************************************************************** */
/*                              input_error.c                                 */
/* ************************************************************************** */
void		ft_loadpng_fail(t_fcheck *check, t_map *map, int index);
void		ft_loadpng_fail2(t_map *map, int index, int imagef);
void		invalid_input(char *str);
void		error_inside_file(t_fcheck *check, char *str);

/* ************************************************************************** */
/*                              free_memory.c                                 */
/* ************************************************************************** */
void		free_check_struct(t_fcheck *check);
void		ft_strfree(char *str);
void		ft_arrfree(char **arr);
void		successful_exit(t_map *map, int index);

/* ************************************************************************** */
/*                              movement.c                                    */
/* ************************************************************************** */
void		playermovement(t_map *map);
void		playerrotation(t_map *map);
void		playerstrafe(t_map *map);
void		mouse_movement(t_map *map);

/* ************************************************************************** */
/*                              raycasting.c                                  */
/* ************************************************************************** */
void		makethelines(t_map *map);

/* ************************************************************************** */
/*                              rendering.c                                   */
/* ************************************************************************** */
void		makethewalls(t_map *map);

#endif