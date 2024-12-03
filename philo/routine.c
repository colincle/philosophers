/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:17:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/03 15:35:56 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo_arg *arguments)
{
		printf("philosopher %d is sleeping\n", arguments->id);
		usleep(arguments->parameters->time_to_sleep);
}

void	eating(t_philo_arg *arguments)
{
	unsigned int	left;
	unsigned int	right;

	left = arguments->id - 1;
	if (arguments->id == arguments->parameters->number_of_philosophers)
		right = 0;
	else
		right = arguments->id;
	pthread_mutex_lock(&arguments->fork[left]);
	pthread_mutex_lock(&arguments->fork[right]);
	printf("philosopher %d is eating\n", arguments->id);fflush(stdout);
	usleep(arguments->parameters->time_to_eat);
	pthread_mutex_unlock(&arguments->fork[right]);
    pthread_mutex_unlock(&arguments->fork[left]);
	printf("philosopher %d is done eating\n", arguments->id);fflush(stdout);
}

void	*routine(void *arg)
{
	t_philo_arg *arguments;

	arguments = (t_philo_arg *)arg;
	printf("philosopher id %d created\n", arguments->id);
	while (1)
	{
		eating(arguments);
		sleeping(arguments);
	}
	return NULL;
}
