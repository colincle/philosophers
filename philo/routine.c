/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:17:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/07 16:25:00 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	gr_routine(void *arg)
{
	t_gr_arg *arguments;
	int		i;
	
	arguments = (t_gr_arg *)arg;
	while(1)
	{
		i = 0;
		while (arguments->philosophers[i])
		{
			if (arguments->parameters->time_of_death[i] <= get_time_ms)
				//kill philosopher
			i++;
		}
	}
}
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
	printf("philosopher %d will die at %lld\n", arguments->id, arguments->parameters->time_of_death[arguments->id - 1]);
	pthread_mutex_lock(&arguments->fork[left]);
	pthread_mutex_lock(&arguments->fork[right]);
	printf("philosopher %d is eating\n", arguments->id);
	usleep(arguments->parameters->time_to_eat);
	pthread_mutex_lock(&arguments->parameters->set_time_to_die);
	arguments->parameters->time_of_death[arguments->id - 1] = get_time_ms() + arguments->parameters->time_to_die;
	printf("philosopher %d will die at %lld\n", arguments->id, arguments->parameters->time_of_death[arguments->id - 1]);
	pthread_mutex_unlock(&arguments->parameters->set_time_to_die);
	printf("philosopher %d is done eating\n", arguments->id);
	pthread_mutex_unlock(&arguments->fork[right]);
    pthread_mutex_unlock(&arguments->fork[left]);
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
		printf("philosopher %d is thinking\n", arguments->id);
	}
	return NULL;
}
