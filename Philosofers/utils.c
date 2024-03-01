/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:21:00 by siroulea          #+#    #+#             */
/*   Updated: 2024/03/01 13:02:29 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosofers.h"

void	ft_bzero(void *b, size_t len)
{
	size_t	i;

	i = 0;
	if (!b)
	{
		return ;
	}
	while (i < len)
	{
		((char *)b)[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*dest;

	dest = malloc(count * size);
	if (!dest)
		return (NULL);
	ft_bzero(dest, count * size);
	return (dest);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;
	int	i;

	i = 0;
	res = 0;
	sign = 1;
	if (!str)
		return (0);
	while (((str[i] != '\0' && str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if ((str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str[i] != '\0' && str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	res *= sign;
	return (res);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	display(t_philo *philo, char *str)
{
	long long	time;
	t_data		*data;

	data = get_data();
	pthread_mutex_lock(&data->display);
	time = get_time() - philo->data->start_time;
	if (str[0] == 'D' && str[1] == 'e' && data->stop == false)
	{
		data->stop = true;
		printf("%lld %d %s", time, philo->index, str);
	}
	else if (philo->alive == true && philo->full == false
		&& data->stop == false)
		printf("%lld %d %s", time, philo->index, str);
	pthread_mutex_unlock(&data->display);
}
