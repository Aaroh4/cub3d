/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:25:31 by ahamalai          #+#    #+#             */
/*   Updated: 2024/08/19 15:07:51 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3dbonus.h"

static void	getting_index(t_map *map, double length)
{
	if (map->side == 1)
	{
		if (map->raydiry > 0)
			map->wall.side = 0;
		else
			map->wall.side = 1;
	}
	else
	{
		if (map->raydirx > 0)
			map->wall.side = 2;
		else
			map->wall.side = 3;
	}
	if (map->side == 0)
		map->wallx = map->cameraposy + length * map->raydiry;
	else
		map->wallx = map->cameraposx + length * map->raydirx;
}

static int	calculate_wall(t_map *map)
{
	double	length;
	double	height;
	double	correct;

	if (map->side == 0)
		length = (map->rayposx - map->deltadistx);
	else
		length = (map->rayposy - map->deltadisty);
	correct = (map->pa - map->raypa);
	getting_index(map, length);
	map->wallx -= floor((map->wallx));
	length *= cos(correct);
	height = (STEPSIZE * SCREENLENGTH) / length;
	map->wall.ty_off = 0;
	map->wall.ty_step = map->wall.txt[map->wall.side]->height / height;
	if (height > SCREENLENGTH)
	{
		map->wall.ty_off = (height - SCREENLENGTH) / 2;
		height = SCREENLENGTH;
	}
	map->wall.y = map->wall.ty_off * map->wall.ty_step;
	return (height);
}

static void	draw_line(int x, int y, t_map *map)
{
	mlx_texture_t	*wall;
	int				offset;
	uint32_t		pixel;

	offset = 0;
	pixel = 0;
	if (!map->is_door)
		wall = map->wall.txt[map->wall.side];
	else
		wall = map->wall.door;
	if (map->wall.side == 0 || map->wall.side == 3)
	{
		if (map->wallx < 0.015)
			offset = (((int)(map->wall.y) * wall->height + (int)(map->wallx
							* (wall->width + 1) * -1))) * sizeof(uint32_t);
		else
			offset = (((int)(map->wall.y + 1) * wall->height + (int)(map->wallx
							* (wall->width + 1) * -1))) * sizeof(uint32_t);
	}
	else
		offset = (((int)map->wall.y * wall->height
					+ (int)(map->wallx * wall->width))) * sizeof(uint32_t);
	if (offset < (int)(wall->width * wall->height * sizeof(uint32_t)))
		pixel = (wall->pixels[offset] << 24) | (wall->pixels[offset + 1] << 16)
			| (wall->pixels[offset + 2] << 8) | wall->pixels[offset + 3];
	mlx_put_pixel(map->background, x, y, pixel);
	map->wall.y += map->wall.ty_step;
}

void	makethewalls(t_map *map)
{
	int	wall_height;
	int	i;
	int	untily;
	int	drawstart;
	int	drawend;

	wall_height = calculate_wall(map);
	i = 0;
	drawstart = -wall_height / 2 + SCREENLENGTH / 2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = wall_height / 2 + SCREENLENGTH / 2;
	untily = 0;
	while (i < SCREENLENGTH)
	{
		if (i < drawstart)
			mlx_put_pixel(map->background, map->rayamount, i, map->ceiling);
		else if (i >= drawstart && i <= drawend)
			draw_line(map->rayamount, i, map);
		else if (i > drawend)
			mlx_put_pixel(map->background, map->rayamount, i, map->floor);
		i++;
	}
}
