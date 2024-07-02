#ifndef CUB3D_H
#define CUB3D_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# include <unistd.h>
# include <fcntl.h>

typedef struct s_map
{
	int	fd;
	int	linecount;

	char	**mapsave;
	mlx_t	*mlx;
}	t_map;

#endif