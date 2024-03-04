/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:38:54 by siroulea          #+#    #+#             */
/*   Updated: 2024/03/04 16:04:23 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosofers.h"

t_data	*get_data(void)
{
	static t_data	*data = NULL;

	if (!data)
	{
		data = ft_calloc(1, sizeof(t_data));
		return (data);
	}
	return (data);
}

void	*thread_routine(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 0;
	while (i < data->nbr_philo)
	{
		if (i == data->nbr_philo)
			data->philo[i].other_fork = &data->philo[0].own_fork;
		else
			data->philo[i].other_fork = &data->philo[i + 1].own_fork;
		i++;
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_create(&data->philo[i].tid, NULL, &routine,
				&data->philo[i]) != 0)
			return (0);
		i++;
	}
	return (0);
}

int	ft_stop(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->display);
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->philo[i].own_fork);
		i++;
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_join(data->philo[i].tid, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc == 5 || argc == 6)
	{
		if (ft_check_if_its_nbr(argv) == 0)
		{
			write(2, "wrong argv\n", 11);
			return (0);
		}
		data = get_data();
		init_data(argv);
		init_philo();
		thread_routine();
		ft_stop(data);
		return (0);
	}
	write(2, "wrong argc\n", 12);
	return (0);
}
