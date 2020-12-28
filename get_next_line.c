#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

static char *add_check_cache(char **cache, char **line, char *point)
{
	char *temp;

	*point = '\0';
	point++;
	temp = *line;
	*line = ft_strjoin(*line, *cache);
	*cache = NULL;
	if (*point != '\0')
		*cache = ft_strdup(point);
	free(temp);
	free(point);
	return (*line);
}

static int add_check(char *buffer, char **line, char **cache)
{
	char *point;
	char *temp;
	
	if ((point = ft_strchr(buffer, '\n')))
	{
		*point = '\0';
		if ((*(++point)) != '\0')
			*cache = ft_strdup(point);
		temp = *line;
		*line = ft_strjoin(*line, buffer);
		free(buffer);
		free(temp);
		return (1);
	}
	temp = *line;
	*line = ft_strjoin(*line, buffer);
	free(temp);
	free(buffer);
	return (0);
}

int get_next_line(int fd, char **line)
{
	char buffer[BUFFER_SIZE + 1];
	int add;
	static char *cache;
	char *point;
	char *temp;

	if ((fd < 0) || (line == NULL) || (BUFFER_SIZE < 1) || !(*line = (char *)malloc(1)))
		return (-1);
	**line = '\0';
	if (cache)
	{
		if ((point = ft_strchr(cache, '\n')))
		{
			*line = add_check_cache(&cache, line, point);
			return (1);
		}
		temp = *line;
		*line = ft_strjoin(*line, cache);
		cache = NULL;
		free(temp);
	}
	while ((add = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[add] = '\0';
		add = add_check(buffer, line, &cache);
			if (add == 1 || add == -1)
				break;
	}
	return ((add == 0) ? 0 : 1);
}