#ifndef WIREFRAME_H
# define WIREFRAME_H

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include "libft.h"
#include "mlx.h"




#define GREEN 0x0000FF00
#define LIME_GREEN 0x0032CD32
#define SPRING_GREEN 0x0000FA9A
#define DARK_GREEN 0x00008400
#define LILAC 0x00B2B2FF
#define INDIGO 0x004C4CFF
#define BURNT_ORANGE 0x0CC6600
#define PALE_GOLDEN_ROD 0x00EEE8AA
#define BLUE 0x001010AA
#define DARK_BLUE 0x000000088

#define COLOR INDIGO


#define SIZE 600

#define Y mesh[row][col].y
#define X mesh[row][col].x
#define Z mesh[row][col].z

#define sign(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))





typedef struct
{
	float x;
	float y;
	float z;
}		t_vec3;

t_vec3		vec3(float x, float y, float z);

typedef	struct
{
	float	x;
	float	y;
}			t_vec2;
t_vec2		vec2(float x, float y);

typedef struct	s_view
{
	void *mlx;
	void *win;
	int rowcount;
	int columncount;
	int		distance;
	int size;
	float proportionality;
	t_vec3 **mesh;
	t_vec2 **points;
	float x_angle;
	float y_angle;
	float z_angle;
}				t_view;




int count_rows(int fd);
int count_columns(int fd);
void rot_x(t_vec3 **mesh, t_view v, float angle);
void rot_y(t_vec3 **mesh, t_view v, float angle);
void rot_z(t_vec3 **mesh, t_view v, float angle);
int ft_abs(int a);
void draw_line_bresenham(t_vec2 vec1, t_vec2 vec2, t_view v);
void draw_edges(t_view v);
void draw_points(t_view v);
t_vec2	vec2(float x, float y);
t_vec3	vec3(float x, float y, float z);
t_vec2 **ft_create_points(t_view v, t_vec3 **mesh);
t_vec3 **create_mesh_copy(t_vec3 **mesh, t_view v);
t_vec3 **create_mesh(int rowcount, int columncount, char *line, int fd, int size);
void create_image(t_view v);
int keyboard_event(int keycode, t_view *v);
t_view initialize_view(int rowcount, int columncount, char *line, int fd);

#endif