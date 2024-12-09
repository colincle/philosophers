/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:17:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/09 14:13:06 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*gr_routine(void *arg)
{
	t_gr_arg *arguments;
	unsigned int		i;
	unsigned int		kill_count;
	kill_count = 0;
	arguments = (t_gr_arg *)arg;
	usleep(arguments->parameters->time_to_die);
	while(1)
	{
		i = 0;
		if (arguments->parameters->number_of_philosophers <= kill_count)
			break ;
		while (i < arguments->parameters->number_of_philosophers)
		{
			if (arguments->parameters->is_alive[i] != DEAD && arguments->parameters->status[i] != EATING)
			{
				if (arguments->parameters->time_of_death[i] <= get_time_ms())
				{
					arguments->parameters->is_alive[i] = DEAD;
					printf("%lld | Philosopher %d is dead\n", get_time_ms(), i + 1);
					kill_count++;
				}
			}
			i++;
		}
		usleep(1000);
	}
	//all philosophers are dead, exit the simulation
	return (NULL);
}
void	sleeping(t_philo_arg *arguments)
{
		if (!arguments->parameters->is_alive[arguments->id - 1])
			return ;
		printf("%lld | Philosopher %d is sleeping\n", get_time_ms(), arguments->id);
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
	if (!arguments->parameters->is_alive[arguments->id - 1])
		return ;
	printf("Philosopher %d will die at %lld\n", arguments->id, arguments->parameters->time_of_death[arguments->id - 1]);
	pthread_mutex_lock(&arguments->fork[left]);
	if (!arguments->parameters->is_alive[arguments->id - 1])
	{
		pthread_mutex_unlock(&arguments->fork[left]);
		return ;
	}
	pthread_mutex_lock(&arguments->fork[right]);
	if (!arguments->parameters->is_alive[arguments->id - 1])
	{
		pthread_mutex_unlock(&arguments->fork[left]);
		pthread_mutex_unlock(&arguments->fork[right]);
		return ;
	}
	arguments->parameters->time_of_death[arguments->id - 1] = get_time_ms() + arguments->parameters->time_to_die;
	arguments->parameters->status[arguments->id -1] = EATING;
	printf("%lld | Philosopher %d is eating\n",get_time_ms(), arguments->id);
	usleep(arguments->parameters->time_to_eat);
	printf("Philosopher %d will die at %lld\n", arguments->id, arguments->parameters->time_of_death[arguments->id - 1]);
	arguments->parameters->status[arguments->id -1] = ALIVE;
	pthread_mutex_unlock(&arguments->fork[right]);
    pthread_mutex_unlock(&arguments->fork[left]);
}

void	*routine(void *arg)
{
	t_philo_arg *arguments;

	arguments = (t_philo_arg *)arg;
	while (1)
	{
		eating(arguments);
		sleeping(arguments);
		if (!arguments->parameters->is_alive[arguments->id - 1])
			break ;
		printf("%lld |  Philosopher %d is thinking\n", get_time_ms(), arguments->id);
	}
	return NULL;
}

