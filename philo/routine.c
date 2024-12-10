/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:17:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/10 17:54:55 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*gr_routine(void *arg)
{
	t_gr_arg		*args;
	unsigned int	i;
	int				terminate;

	terminate = 0;
	args = (t_gr_arg *)arg;
	while (1)
	{
		i = 0;
		if (terminate)
		{
			while (i < args->param->number_of_philosophers)
				args->param->is_alive[i++] = DEAD;
			break ;
		}
		while (i < args->param->number_of_philosophers)
		{
			if (args->param->is_alive[i] != DEAD
				&& args->param->status[i] != EATING)
			{
				if (args->param->time_of_death[i] <= time_us(args->param->start))
				{
					args->param->is_alive[i] = DEAD;
					printf("\n%lld | \t\t\tPhilosopher %d is dead\n\n", time_us(args->param->start) / 1000, i + 1);
					terminate = 1;
					break ;
				}
			}
			i++;
		}
		usleep(100);
	}
	// all philosophers are dead, exit the simulation
	return (NULL);
}
void	sleeping(t_philo_arg *args)
{
	if (!args->param->is_alive[args->id - 1])
		return ;
	printf("%lld | Philosopher %d is sleeping\n", time_us(args->param->start)
		/ 1000, args->id);
	usleep(args->param->time_to_sleep);
}

void	eating(t_philo_arg *args)
{
	unsigned int	left;
	unsigned int	right;
	unsigned int	temp;

	left = args->id - 1;
	right = args->id % args->param->number_of_philosophers;
	if (args->id % 2 == 0)
	{
		temp = left;
		left = right;
		right = temp;
	}
	while (1)
	{
		if (!args->param->is_alive[args->id - 1])
			return ;
		if (args->param->forks[left] && args->param->forks[right])
		{
			pthread_mutex_lock(&args->forks_locks[left]);
			args->param->forks[left] = USED;
			pthread_mutex_lock(&args->forks_locks[right]);
			args->param->forks[right] = USED;
			break ;
		}
	}
	args->param->time_of_death[args->id - 1] = time_us(args->param->start) + args->param->time_to_die;
	args->param->status[args->id - 1] = EATING;
	printf("%lld | Philosopher %d is eating\n", time_us(args->param->start)
		/ 1000, args->id);
	usleep(args->param->time_to_eat);
	args->param->status[args->id - 1] = ALIVE;
	printf("%lld | Philosopher %d is done eating\n", time_us(args->param->start) / 1000, args->id);
	args->param->forks[right] = ON_THE_TABLE;
	pthread_mutex_unlock(&args->forks_locks[right]);
	args->param->forks[left] = ON_THE_TABLE;
	pthread_mutex_unlock(&args->forks_locks[left]);
	printf("philosopger %d will die at %lld%c-----------%c", args->id, args->param->time_of_death[args->id - 1] / 1000, 10, 10); fflush(stdout); // debug
}

void	*routine(void *arg)
{
	t_philo_arg	*args;

	args = (t_philo_arg *)arg;
	args->param->time_of_death[args->id - 1] = time_us(args->param->start) + args->param->time_to_die;
	while (1)
	{
		eating(args);
		sleeping(args);
		if (!args->param->is_alive[args->id - 1])
			break ;
		printf("%lld | Philosopher %d is thinking\n",
			time_us(args->param->start) / 1000, args->id);
	}
	return (NULL);
}
