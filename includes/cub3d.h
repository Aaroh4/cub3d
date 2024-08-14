#ifndef CUB3D_H
#define CUB3D_H

#define WALL "textures/wall.png"
#define GROUND "textures/ground.png"
#define PI 3.1415926535

#define screenwidth 1200
#define screenlength 600

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h> //remove;

typedef struct s_fcheck
{
	int		plocation[2];
	int		cameraposy;
	int		cameraposx;
	char	playerstartpos;

	int		map_size;
	int		linecount;
	int		count;
	int		map_start;
	int		info;
	int		error;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*ground;
	char	*sky;
	char	**mapcpy;
	char	**file;
}	t_fcheck;


typedef struct s_ray
{
	int x;
	int	y;
	int lenght;
} t_ray;

typedef struct s_map
{
	t_ray rays[90];
	int	fd;
	int	linecount;
	int wallcount;
	int	lenght;
	int	plocation[2]; // 0 for x // 1 for y
	int	info_set;
	int	map_start;

	int	py;
	int	px;

	double pa;

	double diry;
	double dirx;

	int	rayposy;
	int	rayposx;

	int	cameraposy;
	int	cameraposx;

	int lastx;
	int	lasty;

	int rayamount;

	double firstray[2]; // 0 for x // 1 for y

	char	playerstartpos;
	char	**mapsave;
	char	**mapcopy;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*surface;
	char	*sky;
	mlx_t	*mlx;

	mlx_image_t		*background;
	mlx_image_t		*wall;
	mlx_image_t		*floor;
	mlx_image_t		*player;

	mlx_texture_t	*background_txt;
	mlx_texture_t	*wall_txt;
	mlx_texture_t	*floor_txt;
	mlx_texture_t	*player_txt;

}	t_map;


void	ft_init_textu(t_map *map);
void	ft_init_img(mlx_t *mlx, t_map *map);
void	ft_create_wall(t_map *img);


void	 read_map(t_map *map, char *map_name);
void	save_map(t_map *map, char *map_name);
int		wallfloodfill(t_map *map, int posy, int posx);
int		check_num(char c);
void	loop_trough(t_map *map, char *str, int count);


//parsing files

void	check_int_of_rgb(t_fcheck *check, char **ceiling);
void	check_rgb_floor(t_fcheck *check);
void	check_rgb_ceiling(t_fcheck *check);
void	looptrough(t_fcheck *check, char *str, int count);
void	direction_check(t_fcheck *check, int *invalid, int *i, int *j);
int 	check_char(char c);
void	map_boarder_check(t_fcheck *check);
void	check_player_and_boarder(t_fcheck *check);
int		extract_and_set_info1(char *str, int info_set, t_fcheck *check);
int		extract_and_set_info2(char *str, int info_set, t_fcheck *check);
char	*check_and_set_info(char *str, char *info, t_fcheck *check);
void	check_info_flag(t_fcheck *check, int i);
void	check_failed_info_flag(t_fcheck *check);
void	invalid_input(char *str);
void	error_inside_file(t_fcheck *check);
void	clean_from_space_nl(char **str);
void	clean_from_nl(char **str);
void	clean_cardinal_directions(char **str);
void	clean_input_strings(t_fcheck *check);
int		count_file_lines(char *map_name, int count);
void	read_file(char *map_name, int count);
void	get_map_information(t_fcheck *check);
int		check_rest(t_fcheck *check, int	i);
void	argument_check(char *argv);
// remove;
void	print_check_struct(t_fcheck *check);

#endif