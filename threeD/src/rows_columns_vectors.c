#include "wireframe.h"

//initializes 2d vector struct
t_vec2	vec2(float x, float y)
{
	t_vec2 v;

	v.x = x;
	v.y = y;
	return (v);
}





//initializes 3d vector struct
t_vec3	vec3(float x, float y, float z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}





//counts number of rows (lines) in the input file
int count_rows(int fd)
{
	int ret;
	char *buf;
	int count = 0;
	int i;

	if ((ret = read(fd, buf, 1) > 0))
	{
		count++;
		if (*buf == '\n')
			count++;
	}
	while ((ret = read(fd, buf, 1)))
	{
		for (i = 0; buf[i]; i++)
		{
			if (buf[i] == '\n')
				count++;
		}
	}
	return (count);
}





//counts number of columns in the input file
int count_columns(int fd)
{
	int ret;
	char buf = 0;
	char line[1000];
	int count = 0;
	int i = 0;

	if (!fd)
		return 0;
	while ((ret = read(fd, &buf, 1)))
	{
		if (buf == '\n')
			break;
		line[i] = buf;
		i++;
	}
	for (i = 0; line[i]; i++)
	{
		if (line[i] > ' ' && line[i - 1] <= ' ')
			count++;		
	}
	return (count);
}