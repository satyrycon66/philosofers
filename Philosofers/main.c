/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:38:54 by siroulea          #+#    #+#             */
/*   Updated: 2024/03/01 13:46:48 by siroulea         ###   ########.fr       */
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
	int		i;

	data = get_data();
	if (argc == 5 || argc == 6)
	{
		init_data(argv);
		init_philo();
		thread_routine();
		ft_stop(data);
	}
	return (0);
}
