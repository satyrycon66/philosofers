/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosofers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:23:24 by siroulea          #+#    #+#             */
/*   Updated: 2024/02/07 16:01:59 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_stack
{
	pthread_t       tid;
	int				index; 
    int             nbr_of_eat; 
    bool			alive;
    
	struct s_stack	*next;
  

}					t_stack;

typedef struct s_data
{
    int nbr_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;

}					t_data;

//Utils
char	*ft_itoa(int n);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *b, size_t len);
int 	ft_atoi(const char *str);
