/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peters <peters@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:02:24 by peters            #+#    #+#             */
/*   Updated: 2023/08/15 15:12:01 by peters           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE];
	char		*next_line;
	static char	extras;
	int			bytes_read;
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 1;
	k = 0;
	next_line = malloc(1);
	bytes_read = BUFFER_SIZE;
	while (bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (NULL);
		next_line = realloc(next_line, ((sizeof(char) * BUFFER_SIZE * j) + 1));
		while (buff[i] != '\n' && i < bytes_read)
			next_line[k++] = buff[i++];
		if (buff[i] == '\n')
		{
			next_line[k] = '\n';
			break ;
		}
		i = 0;
		j++;
	}
	//extras = ft_substr(next_line, ft_strrchr('\n', next_line,))
	// como guardar para a proxima chamada
	// concat com a chamada anterior
	return (next_line);
}

#include <stdio.h>

int	main(void)
{
	int	fd;

	fd = open("teste.txt", O_RDONLY);
	printf("1: %s", get_next_line(fd));
	printf("2: %s", get_next_line(fd));
	printf("3: %s", get_next_line(fd));
	printf("4: %s", get_next_line(fd));
	printf("5: %s", get_next_line(fd));
	printf("6: %s", get_next_line(fd));
	printf("7: %s", get_next_line(fd));
}
// substr, inicio até strchr('\n')