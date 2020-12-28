/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:33:06 by cyuuki            #+#    #+#             */
/*   Updated: 2020/12/26 19:52:47 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

static int add_check(char **line, char *buffer, char **cache)
{
	char *point;
	char *temp;

	if (!buffer)
		return (0);
	if ((point = ft_strchr(buffer, '\n')))
	{
		*point = '\0';
		if(*(++point) != '\0')
			*cache = ft_strdup(point);
		temp = *line;
		*line = ft_strjoin(*line, buffer);
		free(*temp);
		return (1);
	}
		*line = ft_strjoin(*line, buffer);
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
			*point = '\0';
			temp = *line;
			*line = ft_strjoin(*line, cache);
			free(temp);
			if(*(++point) != '\0')
				cache = ft_strdup(point);
			else
				cache = NULL;
			return (1);
		}
		else
		{
			temp = *line;
			*line = ft_strjoin(*line, cache);
			cache = NULL;
			free(temp);
		}
	}
	while ((add = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[add] = '\0';
		add = add_check(line, buffer, &cache);
		if(add == 1 || add == -1)
			break;
	}
	if (add == -1)
		return (-1);
	if (add == 1)
		return (1);
	else
		return (0);
}

/*int main(void)
{
	char *string;
	int fd;

	fd = open("tnt.txt", O_RDONLY);
	get_next_line(fd, &string);
	printf("%s\n", string);
	get_next_line(fd, &string);
	printf("%s\n", string);
	return (0);
}*/

