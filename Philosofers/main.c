/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:38:54 by siroulea          #+#    #+#             */
/*   Updated: 2024/02/29 15:14:14 by siroulea         ###   ########.fr       */
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
	data->stop2 = false;
	data->philo = malloc(sizeof(t_philo *) * data->nbr_philo);
	if (argv[5])
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
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

// thread_routine est la fonction que le thread invoque directement
// après sa création. Le thread se termine à la fin de cette fonction.
void	*thread_routine(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 0;
	while (i < data->nbr_philo)
	{
		if(i == data->nbr_philo)
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

		// i = 0;
		//     while(i < data->nbr_philo)
		//     {
		//      printf("index:%d\n",data->philo[i].index);
		// 		printf("die time:%lld\n",data->philo[i].die_time);
		// 		printf("eat time:%lld\n",data->philo[i].eat_time);
		// 		printf("nbr of eat:%d\n",data->philo[i].nbr_of_eat);
		// 		printf("sleep_time:%lld\n",data->philo[i].sleep_time);
		// 		printf("start eat time:%lld\n",data->philo[i].start_eat_time);
		// 		printf("%d\n",data->philo[i].alive);
		// 	i++;
		//     }

		
// printf("%d\n",data->nbr_philo);
//   printf("%d\n",data->time_to_die);
//     printf("%d\n",data->time_to_eat);
//       printf("%d\n",data->time_to_sleep);
//         printf("%d\n",data->number_of_times_each_philosopher_must_eat);
// 			number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

// ◦ timestamp_in_ms X has taken a fork ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died