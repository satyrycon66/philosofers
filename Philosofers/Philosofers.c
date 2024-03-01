/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosofers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:49:42 by siroulea          #+#    #+#             */
/*   Updated: 2024/03/01 13:08:20 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosofers.h"

int	check_death(t_philo *philo)
{
	if (get_time() > (philo->start_eat_time + philo->die_time))
	{
		display(philo, "Dead\n");
		return (1);
	}
	return (0);
}

int	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->own_fork);
	check_death(philo);
	display(philo, "has taken a fork\n");
	if (philo->data->nbr_philo == 1)
	{
		ft_usleep(philo->die_time * 2, philo);
		return (0);
	}
	pthread_mutex_lock(philo->other_fork);
	display(philo, "has taken a fork\n");
	return (1);
}

int	eating(t_philo *philo)
{
	display(philo, "is eating\n");
	philo->start_eat_time = get_time();
	philo->nbr_of_eat += 1;
	ft_usleep(philo->eat_time, philo);
	if (philo->nbr_of_eat == philo->data->number_of_times_each_philosopher_must_eat)
		philo->full = true;
	check_death(philo);
	pthread_mutex_unlock(philo->other_fork);
	pthread_mutex_unlock(&philo->own_fork);
	return (0);
}

void	ft_usleep(int ms, t_philo *philo)
{
	long	time;

	if (ms < 0)
		return ;
	time = get_time();
	while (get_time() < (time + ms) && !check_death(philo))
	{
		usleep(10);
	}
}

void	*routine(void *in)
{
	t_philo	*philo;
	t_data	*data;

	data = get_data();
	philo = (t_philo *)in;
	if (philo->index % 2 != 0)
		ft_usleep(philo->eat_time / 2, philo);
	while (philo->full == false && philo->alive == true)
	{
		take_fork(philo);
		eating(philo);
		display(philo, "is sleeping\n");
		ft_usleep(philo->sleep_time, philo);
		display(philo, "is thinking\n");
		ft_usleep((philo->eat_time - philo->sleep_time), philo);
		pthread_mutex_lock(&data->display);
		if (data->stop == true)
			philo->alive = false;
		pthread_mutex_unlock(&data->display);
	}
	return (0);
}
