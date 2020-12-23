/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:33:06 by cyuuki            #+#    #+#             */
/*   Updated: 2020/12/23 20:56:52 by cyuuki           ###   ########.fr       */
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
		//printf("123");
	}
	tmp = ft_strjoin(*line, buffer);
	//printf("111");
	free(*line);
	*line = tmp;
	//free(tmp);

	/*tmp = NULL;
		if ((point = ft_strchr(buffer, '\n')))
		{
			*point = '\0';
		}*/
//	free(*cache);
	//*cache = tmp;
	//tmp = *line;
//	*line = ft_strjoin(*line, buffer);
	//free(tmp);
	//free(*line);
	// *line = ft_strjoin(*line, *cache);
	// free(*cache);
	if(point)
		return (1);
	else
		return (0);
}

int get_next_line(int fd, char **line)
{
	char buffer[BUFFER_SIZE + 1];
	int add;
	char *poin;
	static char *cache;
	char *tmp;
	int i;

	i = 2;
	if ((fd < 0) || (line == NULL) || (BUFFER_SIZE < 1) || !(*line = (char *)malloc(1)))
		return (-1);
	**line = '\0';
	while ((add = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[add] = '\0';
		//printf("line\n%s\n", *line);
		//printf("buffer\n%s\n", buffer);
		add = add_check(line, buffer, &cache);
		if(add == 1)
			break;
	}
	//printf("111");
	//printf("%s\n", tmp);
	/*if(add == -1)
	return (-1);

	return (0);*/
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

