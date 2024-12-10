/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_initialization.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:17:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/10 11:34:35 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *gr_args(t_parameters *parameters, pthread_t *philosophers)
{
	t_gr_arg *gr_arg;

	gr_arg = malloc(sizeof(t_gr_arg));
	if (!gr_arg)
		return (NULL);
	
	gr_arg->parameters = parameters;
	gr_arg->philosophers = philosophers;
	return ((void *)gr_arg);
}

void *new_philo_arg(t_parameters *parameters, int i, pthread_mutex_t **forks_locks)
{
	t_philo_arg *philo_arg;

	philo_arg = malloc(sizeof(t_philo_arg));
	if (!philo_arg)
		return (NULL);
	
	philo_arg->id = i + 1;
	philo_arg->parameters = parameters;
	philo_arg->forks_locks = *forks_locks;
	return ((void *)philo_arg);
}

int	start_philosophers(pthread_t **philosophers, t_parameters *parameters, pthread_mutex_t **forks_locks)
{
	unsigned int	i;

	i = 0;
	*philosophers = malloc(sizeof(pthread_t) * parameters->number_of_philosophers);
	if (!*philosophers)
		return (0);
	while (i < parameters-> number_of_philosophers)
	{
		if (pthread_create(&(*philosophers)[i], NULL, routine, new_philo_arg(parameters, i, forks_locks)))
			err("Thread creation failed");
		i++;
	}

	return (0);
}
