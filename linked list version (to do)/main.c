/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:44:54 by pehenri2          #+#    #+#             */
/*   Updated: 2023/08/30 20:06:55 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	char	*line;
	int	i;
	int	fd;

	fd = open("test.txt", O_RDONLY);
	while (i < 5)
	{
		line = get_next_line(fd);
		printf("Line [%i] %s\n", i, line);
		free(line);
		i++;
	}
}