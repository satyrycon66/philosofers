/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:21:00 by siroulea          #+#    #+#             */
/*   Updated: 2024/02/29 15:43:25 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosofers.h"

static char	*ft_itoa2(unsigned int nb, int len, long long i, int sign)
{
	char	*res;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	i = len - 1;
	while (i >= 0)
	{
		res[i] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
	if (sign == -1)
		res[0] = '-';
	return (res);
}

char	*ft_itoa(int n)
{
	long long		i;
	int				len;
	char			*res;
	int				sign;
	unsigned int	nb;

	sign = 1;
	nb = n;
	if (n < 0)
	{
		sign = -1;
		nb = -n;
	}
	if (n <= 0)
		len = 1;
	else
		len = 0;
	i = nb;
	while (i > 0)
	{
		i /= 10;
		len++;
	}
	res = ft_itoa2(nb, len, i, sign);
	return (res);
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

// int chek_philo(void)
// {
// 	t_data *data;

// 	data = get_data();
// 	int i;
// 		i = 0;
// 			 while(i < data->nbr_philo)
// 			 {
// 				check_death(&data->philo[i] );
// 				if(data->stop == true)
// 				return (0);
// 			i++;
// 		}
// 		return (1);
// }

void	display(t_philo *philo, char *str)
{
	long long	time;

	t_data *data;

	data = get_data();

	pthread_mutex_lock(&data->display);
	time = get_time() - philo->data->start_time;
	if(str[0] == 'D' && str[1] == 'e' && data->stop == false)
	{
		data->stop = true;
		// philo->alive = false;
		printf("%lld %d %s", time, philo->index, str);
	}
	
	else if (philo->alive == true && philo->full == false
		&& data->stop == false   )
		printf("%lld %d %s", time, philo->index, str);
	
	pthread_mutex_unlock(&data->display);
}
