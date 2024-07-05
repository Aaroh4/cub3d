#ifndef CUB3D_H
#define CUB3D_H

#define WALL "textures/wall.png"
#define GROUND "textures/ground.png"
#define PI 3.1415926535

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# include <unistd.h>
# include <fcntl.h>

typedef struct s_map
{
	int	fd;
	int	linecount;
	int	plocation[2];

	int	py;
	int	px;

	double diry;
	double dirx;

	char	**mapsave;
	char	**mapcopy;
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

#endif