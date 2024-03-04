/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siroulea <siroulea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:08:41 by siroulea          #+#    #+#             */
/*   Updated: 2024/03/04 15:30:42 by siroulea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosofers.h"

int	ft_check_if_its_nbr(char **argv)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (argv[j])
	{
		while (argv[j][i])
		{
			if (argv[j][i] >= '0' && argv[j][i] <= '9')
			{
				i++;
			}
			else
				return (0);
		}
		i = 0;
		j++;
	}
	return (1);
}
