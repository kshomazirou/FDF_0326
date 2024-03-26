/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshoma <kshoma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:09:33 by kshoma            #+#    #+#             */
/*   Updated: 2024/03/26 07:47:46 by kshoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw2(t_fdf **data, int *img_data)
{
	int	x;
	int	y;

		y = 0;
	while (data[y])
	{
		x = 0;
		while (1)
		{
			if (data[y + 1])
				bresenham(data[y][x], data[y + 1][x], &data[0][0], img_data);
			if (!data[y][x].is_last)
				bresenham(data[y][x], data[y][x + 1], &data[0][0], img_data);
			if (data[y][x].is_last)
				break ;
			x++;
		}
		y++;
	}
}

void	*image_create(t_fdf **data, char **img_data)
{
	int		bpp;
	int		endian;
	int		size_line;
	void	*img_ptr;

	bpp = 32;
	endian = 0;
	img_ptr = mlx_new_image(data[0][0].mlx_ptr, \
			data[0][0].win_x, data[0][0].win_y);
	size_line = data[0][0].win_x * (bpp / 8);
	*img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	return (img_ptr);
}

void	draw(t_fdf **data)
{
	void	*img_ptr;
	char	*img_data;

	img_data = 0;
	img_ptr = image_create(data, &img_data);
	draw2(data, (int *)img_data);
	mlx_put_image_to_window(data[0][0].mlx_ptr, \
			data[0][0].win_ptr, img_ptr, 0, 0);
	print_data(data[0][0]);
}
