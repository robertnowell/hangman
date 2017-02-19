#include "wireframe.h"

//alters y and z value of each vector in the mesh based on specified rotation angle (mesh values accessed through X, Y, and Z macros for readability)
void rot_x(t_vec3 **mesh, t_view v, float angle)
{
	float y_prime;
	float z_prime;
	int row;
	int col;

	for (row = 0; row < v.rowcount - 1; row++)
	{
		for (col = 0; col <= v.columncount - 1; col++)
		{
			y_prime = Y * cos(angle) - Z * sin(angle);
			z_prime = Z * cos(angle) + Y * sin(angle);
			Y = y_prime;
			Z = z_prime;
		}
	}
}





//alters x and z value of each vector in the mesh based on specified rotation angle
void rot_y(t_vec3 **mesh, t_view v, float angle)
{
	float x_prime;
	float z_prime;
	int row;
	int col;

	for (row = 0; row < v.rowcount - 1; row++)
	{
		for (col = 0; col <= v.columncount - 1; col++)
		{
			x_prime = X * cos(angle) - Z * sin(angle);
			z_prime = Z * cos(angle) + X * sin(angle);
			Z = z_prime;
			X = x_prime;
		}
	}
}





//alters x and y value of each vector in the mesh based on specified rotation angle
void rot_z(t_vec3 **mesh, t_view v, float angle)
{
	float x_prime;
	float y_prime;
	int row;
	int col;

	for (row = 0; row < v.rowcount - 1; row++)
	{
		for (col = 0; col <= v.columncount - 1; col++)
		{
			x_prime = X * cos(angle) - Y * sin(angle);
			y_prime = X * sin(angle) + Y * cos(angle);
			X = x_prime;
			Y = y_prime;
		}
	}
}