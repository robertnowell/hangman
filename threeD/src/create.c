#include "wireframe.h"

//creates 2d array of 2d vectors called points which holds the two-d representation of three-d mesh.
t_vec2 **ft_create_points(t_view v, t_vec3 **mesh)
{
	t_vec2 **points;
	int row;
	int col;

	points = (t_vec2**)malloc(sizeof(t_vec2 *) * v.rowcount);
	row = 0;
	for (row = 0; row < v.rowcount; row++)
		points[row] = (t_vec2 *)malloc(sizeof(t_vec2) * v.columncount);
	for (row = 0; row < v.rowcount - 1; row++)
	{
		for (col = 0; col <= v.columncount - 1; col++)
			points[row][col] = vec2(X + v.size/2 + v.proportionality*X*Z, Y + v.size/2 + v.proportionality*Y*Z);
	}
	return points;
}





//copies 2d array of 3d vectors called mesh
t_vec3 **create_mesh_copy(t_vec3 **mesh, t_view v)
{
	int row;
	int col;
	t_vec3 **tmp_mesh;

	tmp_mesh = (t_vec3 **)malloc(sizeof(t_vec3*) * v.rowcount + 1);
	for (row = 0; row < v.rowcount; row++)
		tmp_mesh[row] = (t_vec3*)malloc(sizeof(t_vec3) * v.columncount + 1);
	row = 0;
	for (row = 0; row < v.rowcount - 1; row++)
	{
		for (col = 0; col < v.columncount; col++)
			tmp_mesh[row][col] = mesh[row][col];
	}
	return tmp_mesh;
}





t_vec3 **create_mesh(int rowcount, int columncount, char *line, int fd, int size)
{	
	int i;
	int j;
	int linei = 0;
	int mod = size/(columncount+rowcount);

	t_vec3 **mesh;
	mesh = (t_vec3 **)malloc(sizeof(t_vec3*) * rowcount + 1);
	for (i = 0;i < rowcount - 1; i++)
	{
		if (!line)
			get_next_line(fd, &line);
		linei = 0;
		mesh[i] = (t_vec3*)malloc(sizeof(t_vec3) * columncount + 1);
		for (j = 0; j < columncount; j++)
		{
			mesh[i][j] = vec3(mod*(j-columncount/2), mod*(i-rowcount/2), (mod/2.5)*ft_atoi(&line[linei]));
			while (line[linei] > ' ')
				linei++;
			while (line[linei] == ' ')
				linei++;
		}
		line = NULL;
	}
	return mesh;
}
