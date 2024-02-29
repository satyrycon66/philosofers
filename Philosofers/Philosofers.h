/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosofers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:23:24 by siroulea          #+#    #+#             */
/*   Updated: 2024/02/29 15:12:25 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_data
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long		start_time;
	bool			stop;
	bool			stop2;
	int				number_of_times_each_philosopher_must_eat;
	struct t_philo	*philo;
	pthread_mutex_t	pause;
	pthread_mutex_t	display;

}					t_data;

typedef struct t_philo
{
	pthread_t		tid;
	int				index;
	int				nbr_of_eat;
	long long		die_time;
	long long		eat_time;
	long long		start_eat_time;
	long long		sleep_time;
	bool			full;
	bool			alive;
	t_data			*data;

	pthread_mutex_t	own_fork;
	pthread_mutex_t	*other_fork;
	// struct s_stack	*next;

}					t_philo;

// Utils
char				*ft_itoa(int n);
void				*ft_calloc(size_t count, size_t size);
void				ft_bzero(void *b, size_t len);
int					ft_atoi(const char *str);
void				*routine(void *in);
t_data				*get_data(void);
long long			get_time(void);
void				ft_usleep(int ms, t_philo *philo);
void				display(t_philo *philo, char *str);
int	check_death(t_philo *philo);