/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:17:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/13 15:35:39 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_param *param)
{
	if (!param->is_alive)
		return (0);
	return (1);
}

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
		while (i < args->param->number_of_philosophers)
		{
			if (is_alive(args->param)
				&& args->param->status[i] != EATING)
			{
				if (args->param->time_of_death[i] <= time_us(args->param->start))
				{
					args->param->is_alive = DEAD;
					printf("%-5lld Philosopher %d died\n", time_us(args->param->start) / 1000, i + 1);
					terminate = 1;
					break ;
				}
			}
			i++;
		}
		if (!is_alive(args->param))
			break ;
		usleep(100);
	}
	free(arg);
	return (NULL);
}

void	sleeping(t_philo_arg *args)
{
	if (!is_alive(args->param))
		return ;
	printf("%-5lld Philosopher %d is sleeping\n", time_us(args->param->start)
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
		if (!is_alive(args->param))
			return ;
		if (args->param->forks[left] && args->param->forks[right])
		{
			pthread_mutex_lock(&args->forks_locks[left]);
			args->param->forks[left] = USED;
			if (is_alive(args->param))
				printf("%-5lld Philosopher %d has taken a fork\n", time_us(args->param->start) / 1000, args->id);
			pthread_mutex_lock(&args->forks_locks[right]);
			args->param->forks[right] = USED;
			if (is_alive(args->param))
				printf("%-5lld Philosopher %d has taken a fork\n", time_us(args->param->start) / 1000, args->id);
			break ;
		}
	}
	args->param->time_of_death[args->id - 1] = time_us(args->param->start) + args->param->time_to_die;
	args->param->status[args->id - 1] = EATING;
	if (is_alive(args->param))
		printf("%-5lld Philosopher %d is eating\n", time_us(args->param->start) / 1000, args->id);
	usleep(args->param->time_to_eat);
	args->param->status[args->id - 1] = ALIVE;
	if (is_alive(args->param))
	args->param->forks[right] = ON_THE_TABLE;
	pthread_mutex_unlock(&args->forks_locks[right]);
	args->param->forks[left] = ON_THE_TABLE;
	pthread_mutex_unlock(&args->forks_locks[left]);
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
		if (!is_alive(args->param))
			break ;
		printf("%-5lld Philosopher %d is thinking\n", time_us(args->param->start) / 1000, args->id);
	}
	free(arg);
	return (NULL);
}
