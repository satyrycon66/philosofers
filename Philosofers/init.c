/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:11:28 by siroulea          #+#    #+#             */
/*   Updated: 2024/03/01 13:55:37 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosofers.h"

void	init_data(char **argv)
{
	t_data	*data;

	data = get_data();
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->start_time = get_time();
	data->stop = false;
	data->philo = malloc(sizeof(t_philo *) * data->nbr_philo);
	if (pthread_mutex_init(&data->display, NULL) != 0)
		return ;
	if (argv[5])
		data->nbr_of_time_each_philo_must_eat = ft_atoi(argv[5]);
}

int	*init_philo(void)
{
	t_data		*data;
	long long	time;
	int			i;

	data = get_data();
	i = 0;
	time = get_time();
	while (i < data->nbr_philo)
	{
		if (pthread_mutex_init(&data->philo[i].own_fork, NULL) != 0)
			return (0);
		data->philo[i].index = i;
		data->philo[i].alive = true;
		data->philo[i].full = false;
		data->philo[i].nbr_of_eat = 0;
		data->philo[i].die_time = data->time_to_die;
		data->philo[i].eat_time = data->time_to_eat;
		data->philo[i].sleep_time = data->time_to_sleep;
		data->philo[i].other_fork = NULL;
		data->philo[i].data = data;
		data->philo[i].start_eat_time = time;
		i++;
	}
	return (0);
}
