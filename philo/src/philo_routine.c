/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:17:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/15 18:48:00 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo_arg *args)
{
	if (!is_alive(args->param))
		return ;
	printf("%-5lld Philosopher %d is sleeping\n", time_us(args->param->strt)
		/ 1000, args->id);
	usleep(args->param->time_to_sleep);
}

void	take_forks(t_philo_arg *args, unsigned int *left, unsigned int *right)
{
	*left = args->id - 1;
	*right = args->id % args->param->nb_philo;
	while (1)
	{
		if (!is_alive(args->param))
			return ;
		if (args->param->forks[*left])
		{
			pthread_mutex_lock(&args->frk_lock[*left]);
			args->param->forks[*left] = USED;
			if (is_alive(args->param))
				printf("%-5lld Philosopher %d has taken a fork\n",
					time_us(args->param->strt) / 1000, args->id);
			pthread_mutex_lock(&args->frk_lock[*right]);
			args->param->forks[*right] = USED;
			if (is_alive(args->param))
				printf("%-5lld Philosopher %d has taken a fork\n",
					time_us(args->param->strt) / 1000, args->id);
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
	pthread_mutex_lock(&args->param->eating_lock[args->id - 1]);
	args->param->status[args->id - 1] = EATING;
	if (is_alive(args->param))
		printf("%-5lld Philosopher %d is eating\n", time_us(args->param->strt)
			/ 1000, args->id);
	args->param->dth_time[args->id - 1] = time_us(args->param->strt)
		+ args->param->time_to_die;
	usleep(args->param->time_to_eat);
	args->param->status[args->id - 1] = ALIVE;
	args->param->forks[right] = ON_THE_TABLE;
	pthread_mutex_unlock(&args->frk_lock[right]);
	args->param->forks[left] = ON_THE_TABLE;
	pthread_mutex_unlock(&args->frk_lock[left]);
	pthread_mutex_unlock(&args->param->eating_lock[args->id - 1]);
	args->meal++;
}

void	finished(t_philo_arg *args)
{
	pthread_mutex_unlock(&args->param->finished_lock[args->id - 1]);
	args->param->finished++;
	pthread_mutex_lock(&args->param->finished_lock[args->id - 1]);
}

void	*routine(void *arg)
{
	t_philo_arg	*args;
	pthread_t	reaper;

	args = (t_philo_arg *)arg;
	set_time_of_death(args);
	pthread_create(&reaper, NULL, reaper_routine,
		reaper_args(args->param, args->id));
	while (1)
	{
		eating(args);
		if (args->meal == args->param->num_eats_per_philosopher)
		{
			finished(args);
			break ;
		}
		sleeping(args);
		if (!is_alive(args->param))
			break ;
		printf("%-5lld Philosopher %d is thinking\n",
			time_us(args->param->strt) / 1000, args->id);
	}
	pthread_join(reaper, NULL);
	free(arg);
	return (NULL);
}
