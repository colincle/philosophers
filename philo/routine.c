/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:17:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/10 12:54:42 by ccolin           ###   ########.fr       */
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
	while(1)
	{
		i = 0;
		if (arguments->parameters->number_of_philosophers <= kill_count)
			break ;
		while (i < arguments->parameters->number_of_philosophers)
		{
			if (arguments->parameters->is_alive[i] != DEAD && arguments->parameters->status[i] != EATING)
			{
				if (arguments->parameters->time_of_death[i] <= get_time_ms(arguments->parameters->start))
				{
					arguments->parameters->is_alive[i] = DEAD;
					printf("\n%lld | \t\t\tPhilosopher %d is dead\n\n", get_time_ms(arguments->parameters->start), i + 1);
					kill_count++;
				}
			}
			i++;
		}
		usleep(100);
	}
	//all philosophers are dead, exit the simulation
	return (NULL);
}
void	sleeping(t_philo_arg *arguments)
{
		if (!arguments->parameters->is_alive[arguments->id - 1])
			return ;
		printf("%lld | Philosopher %d is sleeping\n", get_time_ms(arguments->parameters->start), arguments->id);
		usleep(arguments->parameters->time_to_sleep);
}

void	eating(t_philo_arg *arguments)
{
	unsigned int left;
	unsigned int right;
	unsigned int temp;

	left = arguments->id - 1;
	right = arguments->id % arguments->parameters->number_of_philosophers;
	if (arguments->id % 2 == 0)
	{
		temp = left;
		left = right;
		right = temp;
	}
	while (1)
	{
		if (!arguments->parameters->is_alive[arguments->id - 1])
			return ;
		if (arguments->parameters->forks[left] && arguments->parameters->forks[right])
		{
			pthread_mutex_lock(&arguments->forks_locks[left]);
			arguments->parameters->forks[left] = USED;
			pthread_mutex_lock(&arguments->forks_locks[right]);
			arguments->parameters->forks[right] = USED;
			break ;
		}
	}
	arguments->parameters->status[arguments->id -1] = EATING;
	printf("%lld | Philosopher %d is eating\n",get_time_ms(arguments->parameters->start), arguments->id);
	usleep(arguments->parameters->time_to_eat);
	arguments->parameters->status[arguments->id -1] = ALIVE;
	printf("%lld | Philosopher %d is done eating\n",get_time_ms(arguments->parameters->start), arguments->id);
	arguments->parameters->forks[right] = ON_THE_TABLE;
	pthread_mutex_unlock(&arguments->forks_locks[right]);
	arguments->parameters->forks[left] = ON_THE_TABLE;
    pthread_mutex_unlock(&arguments->forks_locks[left]);
	arguments->parameters->time_of_death[arguments->id - 1] = get_time_ms(arguments->parameters->start) + arguments->parameters->time_to_die;
}

void	*routine(void *arg)
{
	t_philo_arg *arguments;

	arguments = (t_philo_arg *)arg;
	arguments->parameters->time_of_death[arguments->id - 1] = get_time_ms(arguments->parameters->start) + arguments->parameters->time_to_die;
	while (1)
	{
		eating(arguments);
		sleeping(arguments);
		if (!arguments->parameters->is_alive[arguments->id - 1])
			break ;
		printf("%lld | Philosopher %d is thinking\n", get_time_ms(arguments->parameters->start), arguments->id);
	}
	return NULL;
}

