/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:17:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/14 16:04:31 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo_arg *args)
{
	if (!is_alive(args->param))
		return ;
	printf("%-5lld Philosopher %d is sleeping\n", time_us(args->param->start)
		/ 1000, args->id);
	usleep(args->param->time_to_sleep);
}

void	swap_forks(unsigned int *left, unsigned int *right)
{
	unsigned int	temp;

	temp = *left;
	*left = *right;
	*right = temp;
}

void	take_forks(t_philo_arg *args, unsigned int *left, unsigned int *right)
{
	*left = args->id - 1;
	*right = args->id % args->param->nb_philo;
	if (args->id % 2 == 0)
		swap_forks(left, right);
	while (1)
	{
		if (!is_alive(args->param))
			return ;
		if (args->param->forks[*left] && args->param->forks[*right])
		{
			pthread_mutex_lock(&args->frk_lock[*left]);
			args->param->forks[*left] = USED;
			if (is_alive(args->param))
				printf("%-5lld Philosopher %d has taken a fork\n",
					time_us(args->param->start) / 1000, args->id);
			pthread_mutex_lock(&args->frk_lock[*right]);
			args->param->forks[*right] = USED;
			if (is_alive(args->param))
				printf("%-5lld Philosopher %d has taken a fork\n",
					time_us(args->param->start) / 1000, args->id);
			break ;
		}
	}
}

void	eating(t_philo_arg *args)
{
	unsigned int	left;
	unsigned int	right;

	take_forks(args, &left, &right);
	if (!is_alive(args->param))
		return ;
	args->param->death_time[args->id - 1] = time_us(args->param->start)
		+ args->param->time_to_die;
	args->param->status[args->id - 1] = EATING;
	if (is_alive(args->param))
		printf("%-5lld Philosopher %d is eating\n", time_us(args->param->start)
			/ 1000, args->id);
	usleep(args->param->time_to_eat);
	args->param->status[args->id - 1] = ALIVE;
	if (is_alive(args->param))
	{
		args->param->forks[right] = ON_THE_TABLE;
		pthread_mutex_unlock(&args->frk_lock[right]);
	}
	args->param->forks[left] = ON_THE_TABLE;
	pthread_mutex_unlock(&args->frk_lock[left]);
}

void	*routine(void *arg)
{
	t_philo_arg	*args;

	args = (t_philo_arg *)arg;
	args->param->death_time[args->id - 1] = time_us(args->param->start)
		+ args->param->time_to_die;
	while (1)
	{
		eating(args);
		sleeping(args);
		if (!is_alive(args->param))
			break ;
		printf("%-5lld Philosopher %d is thinking\n",
			time_us(args->param->start) / 1000, args->id);
	}
	free(arg);
	return (NULL);
}
