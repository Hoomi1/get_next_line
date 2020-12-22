/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuuki <cyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:33:06 by cyuuki            #+#    #+#             */
/*   Updated: 2020/12/22 20:27:39 by cyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

static int add_check(char **line, char *buffer, char *poin, char **cache)
{
	char *tmp;

	if(!buffer)
		return (0);
	tmp = NULL;
		if ((poin = ft_strchr(buffer, '\n')))
		{
			*poin = '\0';
			poin++;
			tmp = ft_strdup(poin);
		}
	free(*cache);
	*cache = tmp;
	tmp = *line;
	*line = ft_strjoin(*line, buffer);
	free(tmp);
	//free(*line);
	// *line = ft_strjoin(*line, *cache);
	// free(*cache);
	if(*line == '\0')
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
	int flag;

	flag = 1;
	if ((fd < 0) || (line == NULL) || (BUFFER_SIZE < 1) || !(*line = (char *)malloc(1)))
		return (-1);
	**line = '\0';
	while ((add = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[add] = '\0';
		add = add_check(line, buffer, poin, &cache);
		/*if ((poin = ft_strchr(buffer, '\n')))
		{
			*poin = '\0';
			poin++;
			flag = 0;
		}
		*line = ft_strjoin(*line, buffer);*/
		//free(*line);
	}
	if(add == -1)
	return (-1);

	return (0);
}
/*
int main(void)
{
	char *string;
	int fd;

	fd = open("tnt.txt", O_RDONLY);
	get_next_line(fd, &string);
	printf("%s\n", string);
	return (0);
}
*/
