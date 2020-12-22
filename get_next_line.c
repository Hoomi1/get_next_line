#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int get_next_line(int fd, char **line)
{
	char buffer[BUFFER_SIZE + 1];
	static char *cache;
	int add;
	char *poin;

	*line = '\0';
	if (!(*line = (char *)malloc(1)) || line )
		return (-1);
	while (cache[poin] != '\n' || (add = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[add] = '\0';
		//add = add_check(line, buffer, &cache);
		if ((poin = ft_strchr(buffer, '\n')))
		{
			*poin = '\0';
			poin++;
			while (poin != '\0')
				cache[poin++];
		}
		*line = ft_strjoin(*line, buffer);
	}
	*line = ft_strjoin(*line, cache);
	free(*cache);
	return ((line) ? 1 : 0);
}

int main(void)
{
	char *string;
	int fd;

	fd = open("tnt.txt", O_RDONLY);
	get_next_line(fd, &string);
	printf("%s\n", string);
	return (0);
}