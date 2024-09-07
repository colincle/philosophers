/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_initialization.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:17:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/09/07 11:55:18 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_philosophers(pthread_t *philosophers, t_parameters *parameters)
{
	unsigned int	i;

	i = 0;
	philosophers = malloc(sizeof(pthread_t) * parameters->number_of_philosophers);
	if (!philosophers)
		return (0);
	while (i < parameters-> number_of_philosophers)
	{
		if (pthread_create(&philosophers[i]))
	}
}
