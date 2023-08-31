# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}			t_list;
char	*get_next_line(int fd);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);

char	*get_next_line(int fd)
{
	char			*next_line;
	static t_list	*head;
	char			*buff;
	int				bytes_read;
	t_list			*current;
	t_list			*new;
	t_list			*temp;
	char			*rest;
	int				i;
	int				line_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = BUFFER_SIZE;
	if (!head)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free (buff);
			return NULL;
		}
		buff[bytes_read] = '\0';
		if (bytes_read > 0)
		{
			new = ft_lstnew(ft_strdup(buff));
			ft_lstadd_back(&head, new);
		}
	}
	current = head;
	while (!ft_strchr(current->content, '\n') && bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free (buff);
			return NULL;
		}
		buff[bytes_read] = '\0';
		new = ft_lstnew(ft_strdup(buff));
		ft_lstadd_back(&head, new);
		current = current->next;
	}
	free (buff);
	if (bytes_read == 0 && head->content[0] == '\0')
	{
		ft_lstclear(&head, free);
		return (NULL);
	}
	current = head;
	i = 0;
	line_len = 0;
	while(current->content[i] != '\n')
	{
		if (current->content[i] == '\0')
		{
			current = current->next;
			i = 0;
		}
		else
		{
			line_len++;
			i++;
		}
		if(current->content[i] == '\n')
			line_len++;
	}
	next_line = malloc(sizeof(char) * (line_len + 1));
	current = head;
	line_len = 0;
	while(current)
	{
		i = 0;
		while(i < BUFFER_SIZE)
		{
			if (current->content[i] != '\n' && current->content[i] != '\0')
			{
				next_line[line_len] = current->content[i];
				i++;
				line_len++;
			}
			else
			{
				if (current->content[i] == '\n')
					next_line[line_len++] = '\n';
				next_line[line_len] = '\0';
				rest = ft_strdup(current->content + i);
				new = ft_lstnew(rest);
				break ;
			}
		}
		current = current->next;
	}
	ft_lstclear(&head, free);
	head = new;
	return (next_line);
}
///////////////////////////////////////////////////////////////


char	*get_next_line(int fd)
{
	char			*next_line;
	static t_list	*head;
	char			*buff;
	int				bytes_read;
	t_list			*current;
	t_list			*new;
	t_list			*temp;
	char			*rest;
	int				i;
	int				line_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = BUFFER_SIZE;
	if (!head)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free (buff);
			return NULL;
		}
		buff[bytes_read] = '\0';
		if (bytes_read > 0)
		{
			new = ft_lstnew(ft_strdup(buff));
			ft_lstadd_back(&head, new);
		}
	}
	current = head;
	while (!ft_strchr(current->content, '\n') && bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free (buff);
			return NULL;
		}
		buff[bytes_read] = '\0';
		new = ft_lstnew(ft_strdup(buff));
		ft_lstadd_back(&head, new);
		current = current->next;
	}
	free (buff);
	if (bytes_read == 0 && head->content[0] == '\0')
	{
		ft_lstclear(&head, free);
		return (NULL);
	}
	current = head;
	i = 0;
	line_len = 0;
	while(current->content[i] != '\n')
	{
		if (current->content[i] == '\0')
		{
			current = current->next;
			i = 0;
		}
		else
		{
			line_len++;
			i++;
		}
		if(current->content[i] == '\n')
			line_len++;
	}
	next_line = malloc(sizeof(char) * (line_len + 1));
	current = head;
	line_len = 0;
	while(current)
	{
		i = 0;
		while(i < BUFFER_SIZE)
		{
			if (current->content[i] != '\n' && current->content[i] != '\0')
			{
				next_line[line_len] = current->content[i];
				i++;
				line_len++;
			}
			else
			{
				if (current->content[i] == '\n')
					next_line[line_len++] = '\n';
				next_line[line_len] = '\0';
				rest = ft_strdup(current->content + i);
				new = ft_lstnew(rest);
				break ;
			}
		}
		current = current->next;
	}
	ft_lstclear(&head, free);
	head = new;
	return (next_line);
}

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	char	*line;
	int	i;
	int	fd;

	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("Line [%02i] %s\n", i, line);
		free(line);
		i++;
	}
}
