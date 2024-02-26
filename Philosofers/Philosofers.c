#include "Philosofers.h"

int	check_death(t_philo *philo)
{
    //  t_data * data;

    // data = get_data();
	pthread_mutex_lock(&philo->data->pause);
	if (get_time() > (philo->start_eat_time + philo->die_time))
	{
		display(philo, "Dead\n");
		philo->data->stop = true;
		philo->alive = false;
		pthread_mutex_unlock(&philo->data->pause);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->pause);
	return (0);
}

int	take_forks(t_philo *philo)
{
    // t_data * data;

    // data = get_data();
	int	i;

	i = 0;
	check_death(philo);
	i += pthread_mutex_lock(&philo->own_fork);
	display(philo, "has taken a fork\n");
	if (philo->data->nbr_philo == 1)
	{
		ft_usleep(philo->die_time * 2, philo);
		return (0);
	}
	i += pthread_mutex_lock(philo->other_fork);
	display(philo, "has taken a fork\n");
	// if (i)
	// 	return (0);
	return (1);
}

int	eating(t_philo *philo)
{
    t_data *data;

    data = get_data();
	int	i;

	i = 0;
	display(philo, "is eating\n");
	philo->start_eat_time = get_time();
	philo->nbr_of_eat++;
	ft_usleep(philo->eat_time, philo);
	i += pthread_mutex_unlock(philo->other_fork);
	i += pthread_mutex_unlock(&philo->own_fork);
	if (philo->nbr_of_eat == data->number_of_times_each_philosopher_must_eat)
		philo->full = true;
	check_death(philo);
	if (i)
		return (0);
	return (1);
}

void	ft_usleep(int ms, t_philo *philo)
{
	long	time;

	if (ms < 0)
		return ;
	// (void)philo;
	time = get_time();
	while (get_time() < (time + ms) && !check_death(philo))
		usleep(10);
}

void	*routine(void *in)
{
     t_data * data;

    data = get_data();
	t_philo	*philo;

	philo = (t_philo *)in;
	if (philo->index % 2 == 0)
		ft_usleep(philo->eat_time / 10, philo);
	while (philo->full == false && philo->alive == true && !check_death(philo))
	{
		take_forks(philo);
		eating(philo);
		display(philo, "is sleeping\n");
		ft_usleep(philo->sleep_time, philo);
		display(philo, "is thinking\n");
		ft_usleep((philo->eat_time - philo->sleep_time), philo);
		pthread_mutex_lock(&philo->data->pause);
		if (philo->data->stop == true)
			philo->alive = false;
		pthread_mutex_unlock(&data->pause);
	}
	return (0);
}


