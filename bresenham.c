/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshoma <kshoma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:21:27 by kshoma            #+#    #+#             */
/*   Updated: 2024/03/25 21:37:47 by kshoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	mod(float i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}

float	max_judge(float a, float b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void	color_judge(int *color, t_fdf a, t_fdf b)
{
	if (b.z || a.z)
		*color = 0xfc0345;
	else
		*color = 0xBBFAFF;
	if (b.z != a.z)
		*color = 0xfc031c;
}

void	bresenham(t_fdf a, t_fdf b, t_fdf *data, int *img_data)
{
	float	x_step;
	float	y_step;
	float	max;
	int		color;

	set_param(&a, &b, data);
	x_step = b.x - a.x;
	y_step = b.y - a.y;
	max = max_judge(mod(x_step), mod(y_step));
	x_step /= max;
	y_step /= max;
	color_judge(&color, a, b);
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		if ((int)a.x >= 0 && (int)a.x < data->win_x && \
				(int)a.y >= 0 && (int)a.y < data->win_y)
				img_data[(int)a.y * data->win_x + (int)a.x] = color;
		a.x += x_step;
		a.y += y_step;
		if (a.x > data->win_x || a.y > data->win_y \
				|| a.y < 0 || a.x < 0)
			continue ;
	}
}
