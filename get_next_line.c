#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int get_next_line(int fd, char **line)
{
	char buffer[BUFFER_SIZE + 1];
	//static char *cache = NULL;
	int add;
	char *poin;

	*line = '\0';
	if (!(*line = (char *)malloc(1)) || line )
		return (-1);
	while ((add = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[add] = '\0';
		if ((poin = ft_strchr(buffer, '\n')))
		{
			*poin = '\0';
		}
		*line = ft_strjoin(*line, buffer);
	}
	return (0);
}

int main(void)
{
	char *line;
	int fd;

	fd = open("tnt.txt", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n", line);
	return (0);
}