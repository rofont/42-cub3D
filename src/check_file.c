#include "cube.h"

void	f_print_tab(char **cou) //TODO a supprimer
{
	int i;

	i = 0;
	while (cou[i])
	{
		printf("%s", cou[i]);
		i++;
	}
}

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

char **f_extract_data(char *file)
{
	char **data;
	char *str;
	int fd;
	int i;
	int j;

	j = 0;
	i = 0;
	fd = open(file, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		i++;
		f_freenull(str);
		str = get_next_line(fd);
	}
	f_freenull(str);
	close(fd);
	data = ft_calloc(sizeof(char *), i + 1);
	fd = open(file, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		data[j++] = ft_strdup(str);
		f_freenull(str);
		str = get_next_line(fd);
	}
	f_freenull(str);
	close(fd);
	return (data);
}

/*A travailler*/
// t_dm *f_get_good_map(char **dat)
// {
// 	t_dm	*data_map;
// 	int i;
// 	int j;

// 	i = 0;
// 	data_map = f_calloc(sizeof(t_dm), 1);
// 	ft_bzero(data_map, sizeof(t_dm));

// 	while (dat[i])
// 	{
// 		if data commance par no
// 			copie dans no
// 		if data commance par so
// 			copie dans so
// 		if data commance par we
// 			copie dans we
// 		if data commance par ea
// 			copie dans ea
// 		if data commance par f
// 			copie dans floor
// 		if data commance par c
// 			copie dans ceilling
// 		if data dif de \n
// 			copie dans map;
// 	}
// 	return (data_map);
// }