/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peters <peters@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:02:24 by peters            #+#    #+#             */
/*   Updated: 2023/08/16 14:16:43 by peters           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE];
	char		*next_line;
	static char	*extras;
	int			bytes_read;
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 1;
	k = 0;
	next_line = NULL;
	bytes_read = BUFFER_SIZE;
	while (bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		next_line = realloc(next_line, ((sizeof(char) * BUFFER_SIZE * j) + 1));
		while (buff[i] != '\n' && buff[i] != EOF && i < bytes_read)
			next_line[k++] = buff[i++];
		if (buff[i] == '\n' || buff[i] == EOF)
		{
			next_line[k] = '\n';
			next_line[k + 1] = '\0';
			if (extras)
				next_line = ft_strjoin(extras, next_line);
			extras = ft_substr(buff, (i + 1), (BUFFER_SIZE - i - 1));
			break ;
		}
		i = 0;
		j++;
	}
	return (next_line);
}

int	main(void)
{
	int	fd;

	fd = open("teste.txt", O_RDONLY);
	printf("gnl 1: %s", get_next_line(fd));
	printf("gnl 2: %s", get_next_line(fd));
	printf("gnl 3: %s", get_next_line(fd));
	printf("gnl 4: %s", get_next_line(fd));
	printf("gnl 5: %s", get_next_line(fd));
	printf("gnl 6: %s", get_next_line(fd));
	printf("gnl 7: %s", get_next_line(fd));
}
// substr, inicio até strchr('\n')