#include "fdf.h"

int	esc_watcher(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

int	main()
{
	void		*ctx;
	void		*win;
	void		*img;
	int			bpp;
	int			sl;
	int			endianess;
	char		*img_data;
	unsigned	white;

	ASSERT(ctx = mlx_init());
	ASSERT(win = mlx_new_window(ctx, 1024, 1024, "Indeed a window."));
	ASSERT(img = mlx_new_image(ctx, 1024, 1024));
	img_data = mlx_get_data_addr(img, &bpp, &sl, &endianess);
	ft_putnbr(bpp);
	white = mlx_get_color_value(ctx, 0xFFFFFF);

	mlx_put_image_to_window(ctx, win, img, 0, 0);
	mlx_key_hook(win, esc_watcher, NULL);
	mlx_loop(ctx);
	return (0);
}
