/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:25:29 by pehenri2          #+#    #+#             */
/*   Updated: 2023/08/23 14:37:47 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int		fd;
	int		i;
	char	*line;

	fd = open("teste.txt", O_RDONLY);
	i = 0;
	while (i < 5)
	{
		line = get_next_line(fd);
		printf("line %i >>> %s", i, line);
		free (line);
		i++;
	}
}
