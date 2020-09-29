#include "cub3d.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}		t_data;

typedef struct s_vars {
	void	*mlx;
	void	*window;
}		t_vars;

int	close(int keycode, t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->window);

	return (keycode);
}


// porque essa funcao funciona???
void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char 	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
       *(unsigned int*)dst = color;       
}

void	put_rect(t_data *data, int x, int y, int size_x, int size_y, int color)
{
	int init_x;

	init_x = x;
	while (y <= size_y)
	{
		x = init_x;
		while (x <= size_x)
		{
			my_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	put_circle(t_data *data, int a, int b, int size, int color)
{
	int x;
	int y;

	x = 0;
	while (x <= (a + size) )
	{
		y = 0;
		while (y <= (b + size) )
		{
			if ((x - a) * (x - a) + (y - b) * (y - b) <= size * size)
				my_pixel_put(data, x, y, color);
			y++;

		}
		x++;
	}
	// (x -a)2 + (y - b)2 = size 2
}

void	print_str(t_vars *vars,  int x, int y, int color, char *str)
{
	mlx_string_put(vars->mlx, vars->window, x, y, color, str);
}

int	main(void)
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	vars.window = mlx_new_window(vars.mlx, NUM_ROWS, NUM_COLS, "TESTE PRIMEIRO");

	img.img = mlx_new_image(vars.mlx, NUM_ROWS, NUM_COLS);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	my_pixel_put(&img, 250, 250, 0x0000FF00);
	//put_rect(&img, 0, 0, 500, 500, 0x00FF0000);
	put_circle(&img, 249, 249, 249, 0x0000FF00);
	mlx_put_image_to_window(vars.mlx, vars.window, img.img, 0, 0);
	mlx_string_put(vars.mlx, vars.window, 20, 20 , 0x000000FF, "Hi, I am mlx_string_put");
	
	print_str(&vars, 40, 40, 0x00FF0000, "hello from print_str! Im I red?");
//	mlx_key_hook(vars.window, close, &vars);
	mlx_hook(vars.window, 2, 1L<<0, close, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
