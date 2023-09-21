#include "cube.h"

void	*f_freenull(void *str)
{
	if (str)
		free(str);
	return (NULL);
}


void	f_print_file(char *file)
{
	char *str;
	int fd;
	int i = 0;

	fd = open(file, O_RDONLY);

	str = get_next_line(fd);
	while (str)
	{
		if (ft_strlen(str) > 1 && str[ft_strlen(str)] != '\n')
		{
			printf("%s", str);
			i++;
		}
		f_freenull(str);
		str = get_next_line(fd);
	}
	f_freenull(str);
	close(fd);
	printf ("nb line %d\n", i);
}
/*A travailler*/
char **f_extract_data(char *file)
{
	char **data = NULL;
	char *str;
	int fd;
	int i;

	i = 0;
	fd = open(file, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		if (ft_strlen(str) > 1 && str[ft_strlen(str)] != '\n')
			i++;
		f_freenull(str);
		str = get_next_line(fd);
	}
	f_freenull(str);
	close(fd);

	return (data);
}