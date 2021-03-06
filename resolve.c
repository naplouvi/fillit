/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   resolve.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: naplouvi <naplouvi@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/20 16:01:51 by naplouvi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/20 16:01:52 by naplouvi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fillit.h"

int		resolve(char **map, char **tetros, t_info *info)
{
	t_tetro	*tetro;

	while (++info->id < info->nb_tetros)
	{
		if ((tetro = malloc(sizeof(t_tetro))) == NULL)
			ft_error();
		coord(tetro, tetros, info->id);
		serialize_tetro(tetro);
		if (check_free(map, tetros, tetro, info) == 0)
			free(tetro);
		else
		{
			info->id = -1;
			info->x = 0;
			info->y = 0;
			free(tetro);
			return (1);
		}
	}
	return (0);
}

int		check_free(char **map, char **tetros, t_tetro *tetro, t_info *info)
{
	if (info->x >= info->size)
		increase_line(info);
	while (map[info->y])
	{
		while (map[info->y][info->x])
		{
			if ((is_free(map, tetro, info->x, info->y) == 0))
			{
				info->x = 0;
				info->y = 0;
				return (0);
			}
			if (info->y == info->size - 1 && info->x == info->size - 1)
			{
				return (tetro->letter != 'A' ?
				backtracking(map, tetros, tetro, info) : 1);
			}
			info->x++;
			if (map[info->y][info->x] == '\0')
				increase_line(info);
		}
	}
	return (1);
}

int		backtracking(char **map, char **tetros, t_tetro *tetro, t_info *info)
{
	t_tetro *before;

	if ((before = (t_tetro*)malloc(sizeof(t_tetro))) == NULL)
		return (1);
	coord(before, tetros, info->id - 1);
	serialize_tetro(before);
	remove_tetro(map, tetro, info);
	info->found = 0;
	info->id--;
	if (check_free(map, tetros, before, info) == 0)
	{
		free(before);
		return (0);
	}
	free(before);
	return (1);
}

int		is_free(char **map, t_tetro *tetro, int x, int y)
{
	int size;

	size = ft_strlen(map[0]);
	if ((y + tetro->y1 < size) && (y + tetro->y2 < size)
	&& (y + tetro->y3 < size) && (y + tetro->y4 < size)
	&& (x + tetro->x1 < size) && (x + tetro->x2 < size)
	&& (x + tetro->x3 < size) && (x + tetro->x4 < size))
	{
		if (map[y + tetro->y1][x + tetro->x1] == '.'
		&& map[y + tetro->y2][x + tetro->x2] == '.'
		&& map[y + tetro->y3][x + tetro->x3] == '.'
		&& map[y + tetro->y4][x + tetro->x4] == '.')
		{
			map[y + tetro->y1][x + tetro->x1] = tetro->letter;
			map[y + tetro->y2][x + tetro->x2] = tetro->letter;
			map[y + tetro->y3][x + tetro->x3] = tetro->letter;
			map[y + tetro->y4][x + tetro->x4] = tetro->letter;
			return (0);
		}
	}
	return (1);
}

int		remove_tetro(char **map, t_tetro *tetro, t_info *info)
{
	int		x;
	int		y;

	y = -1;
	while (map[++y] && (x = -1))
	{
		while (map[y][++x])
		{
			if (map[y][x] == tetro->letter - 1)
			{
				map[y][x] = '.';
				if (info->found == 0)
				{
					info->y = y;
					info->x = x + 1;
				}
				if (info->x > x)
					info->x = x + 1;
				info->found++;
			}
		}
	}
	return (info->found == 4);
}
