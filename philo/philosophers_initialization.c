/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_initialization.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:17:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/07 12:08:35 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *new_philo_arg(t_parameters *parameters, int i, pthread_mutex_t **fork)
{
	t_philo_arg *philo_arg;

	philo_arg = malloc(sizeof(t_philo_arg));
	if (!philo_arg)
		return (NULL);
	
	philo_arg->id = i + 1;
	philo_arg->parameters = parameters;
	philo_arg->fork = *fork;
	return ((void *)philo_arg);
}

int	start_philosophers(pthread_t **philosophers, t_parameters *parameters, pthread_mutex_t **fork)
{
	unsigned int	i;

	i = 0;
	*philosophers = malloc(sizeof(pthread_t) * parameters->number_of_philosophers);
	if (!*philosophers)
		return (0);
	while (i < parameters-> number_of_philosophers)
	{
		if (pthread_create(&(*philosophers)[i], NULL, routine, new_philo_arg(parameters, i, fork)))
			err("Thread creation failed");
		i++;
	}
	return (0);
}
