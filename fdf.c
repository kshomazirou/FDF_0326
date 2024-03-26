/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshoma <kshoma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 09:45:36 by kshoma            #+#    #+#             */
/*   Updated: 2024/03/26 08:09:28 by kshoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_default(t_fdf *data)
{
	data->scale = 10;
	data->z_scale = 1;
	data->is_isometric = 1;
	data->angle = 0.523599;
	data->win_x = 1000;
	data->win_y = 500;
	data->shift_x = data->win_x / 3;
	data->shift_y = data->win_y / 3;
	data->mlx_ptr = mlx_init();
	data->win_ptr = \
	mlx_new_window(data->mlx_ptr, data->win_x, data->win_y, "FDF");
}

int	close_window(void *param)
{
	t_fdf	**data;
	int		i;

	data = (t_fdf **)param;
	mlx_destroy_window(data[0][0].mlx_ptr, data[0][0].win_ptr);
	i = 0;
	while (data[i] != NULL)
		free(data[i++]);
	free(data);
	*data = NULL;
	exit(0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_fdf	**data;

	if (argc == 2)
	{
		data = read_file(argv[1]);
		set_default(&data[0][0]);
		draw(data);
		mlx_hook(data[0][0].win_ptr, 2, 0, deal_key, data);
		mlx_hook(data[0][0].win_ptr, 17, 0, close_window, data);
		mlx_loop(data[0][0].mlx_ptr);
		free(data);
		*data = NULL;
	}
	else
		ft_error("Error: usage{ ./fdf map.fdf}");
	return (0);
}
