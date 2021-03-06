/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: naplouvi <naplouvi@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/20 16:02:23 by naplouvi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/20 16:02:26 by naplouvi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fillit.h"

int		main(int argc, char **argv)
{
	int			fd;
	int			id;
	char		*tetros[26 + 1];
	t_info		*info;
	char		**map;

	id = 0;
	ft_usage(argc);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_error();
	id = read_tetros(fd, id, tetros);
	if ((info = malloc(sizeof(t_info))) == NULL || close(fd) == -1)
		ft_error();
	initialize(info, id);
	if ((map = (char **)malloc(sizeof(char *) * (info->size + 1))) == NULL)
		ft_error();
	ft_putsstr((map = resolve_tetro(tetros, info, map)), info->size);
	free_content(map);
	id = -1;
	while (tetros[++id] != NULL)
		free(tetros[id]);
	return (0);
}
