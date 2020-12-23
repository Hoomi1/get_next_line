/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:33:06 by cyuuki            #+#    #+#             */
/*   Updated: 2020/12/23 21:11:54 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

static int add_check(char **line, char *buffer, char **cache)
{
	char *tmp;
	char *point;
	int i;

	i = 0;
	if (!buffer)
		return (0);
	if((point = ft_strchr(buffer, '\n')))
	{
		*point = '\0';
		point++;
		if(*point != '\0')
		*cache = ft_strdup(point);
	}
	tmp = ft_strjoin(*line, buffer);
	free(*line);
	*line = tmp;
	if(point)
		return (1);
	else
		return (0);
}

int get_next_line(int fd, char **line)
{
	char buffer[BUFFER_SIZE + 1];
	int add;
	static char *cache;
	int i;

	i = 2;
	if ((fd < 0) || (line == NULL) || (BUFFER_SIZE < 1) || !(*line = (char *)malloc(1)))
		return (-1);
	**line = '\0';
	while ((add = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[add] = '\0';
		add = add_check(line, buffer, &cache);
		if(add == 1 || add == -1)
			break;
	}
	if(add == -1)
		return (-1);
	if(add == 1)
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

