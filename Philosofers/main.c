/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:38:54 by siroulea          #+#    #+#             */
/*   Updated: 2024/02/07 16:29:24 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosofers.h"

t_stack	*creat_node(int index)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	// node->tid = pthread_self();
    node->index = index;
	node->next = NULL;
    
	return (node);
}



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

void init_data(char **argv)
{
    t_data	*data;

	data = get_data();

    data->nbr_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
     if(argv[5])
    data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
    
}

t_stack	*creat_struct(t_stack	*head)
{
	 t_data	*data;
     data = get_data();
	t_stack	*current;
	int		i;

	i = 1;
	head = creat_node(i++);
	if (!head)
		return (NULL);
	current = head;
	while (i < data->nbr_philo +1)
	{
		current->next = creat_node(i);
		current = current->next;
		i++;
	}
	return (head);
}

// // thread_routine est la fonction que le thread invoque directement
// // après sa création. Le thread se termine à la fin de cette fonction.
// void	*thread_routine(void *data)
// {
// 	pthread_t tid;

// 	// La fonction pthread_self() renvoie
// 	// l'identifiant propre à ce thread.
// 	tid = pthread_self();
// 	printf("%sThread [%ld]: Le plus grand ennui c'est d'exister sans vivre.%s\n",
// 	 tid);
// 	return (NULL); // Le thread termine ici.
// }

int main(int argc ,char **argv)
{   
    t_data	*data;
    t_stack *head;
    t_stack	*current;

	data = get_data();
    	
    if(argc == 5 || argc == 6)
    {
        init_data(argv);
        head = creat_struct(head);
        
        current = head;  
        
        while(current->alive ==  true)
        {
            printf("%d\n",current->index);
			if (current->next == NULL)
			current = head;
			else
            current = current->next;
			
        }
        
   
    }
    return 0;
}

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