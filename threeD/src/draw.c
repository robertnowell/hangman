#include "wireframe.h"

//draws pixels from 2d array of vectors points to output display
void draw_points(t_view v)
{
	int row;
	int col;

	for (row = 0; row < v.rowcount - 1; row++)
	{
		for (col = 0; col <= v.columncount - 1; col++)
			mlx_pixel_put(v.mlx, v.win, v.points[row][col].x, v.points[row][col].y, COLOR);
	}
	draw_edges(v);
}




//draws edges draws horizontal and vertical lines between adjacent points
void draw_edges(t_view v)
{
	int row;
	int col;
	t_vec2 **points;

	points = v.points;
	for (row = 0; row < v.rowcount-2; row++)
	{
		for (col = 0; col < v.columncount - 1; col++)
		{
			draw_line_bresenham(points[row][col], points[row][col+1], v);
			draw_line_bresenham(points[row][col], points[row+1][col], v);
		}
		draw_line_bresenham(points[row][col], points[row+1][col], v);
	}
	for (col = 0; col < v.columncount - 1; col++)
		draw_line_bresenham(points[row][col], points[row][col+1], v);
}




int ft_abs(int a)
{
	return a < 0 ? -a : a;
}




//implements Bresenham's line algorithm
void draw_line_bresenham(t_vec2 vec1, t_vec2 vec2, t_view v)
{
	float x1, x2, y1, y2;
	x1 = vec1.x;
	y1 = vec1.y;
	x2 = vec2.x;
	y2 = vec2.y;
	double x = x1;
	double y = y1;
	double delta_x = ft_abs(x2 - x1);
	double delta_y = ft_abs(y2 - y1);
	double sign_x = sign(x2 - x1);
	double sign_y = sign(y2 - y1);
	double swap = 0;
	double temp;

	if (delta_y > delta_x) 
	{ 
		temp = delta_x;
		delta_x = delta_y;
		delta_y = temp;
		swap = 1;
	}
	float delta_err = 2 * delta_y - delta_x;
	int i = 0;
	while (i < delta_x)
	{
		mlx_pixel_put(v.mlx, v.win, x, y, COLOR);
		while (delta_err >= 0)
		{ 
			delta_err = delta_err - 2 * delta_x; 
			if (swap) 
				x += sign_x; 
			else 
				y += sign_y; 
		}
		delta_err = delta_err + 2 * delta_y;
		if (swap)
			y += sign_y;
		else 
			x += sign_x;
		i++;
	}
}
