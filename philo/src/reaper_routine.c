/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:17:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/15 14:54:07 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_param *param)
{
	if (!param->is_alive)
		return (0);
	return (1);
}

void	kill(t_reaper_arg *args, int id, int silent)
{
	args->param->is_alive = DEAD;
	if (silent)
	{
		printf("%-5lld Philosopher %d", time_us(args->param->strt) / 1000, id);
		printf(" has died\n");
	}
}

void	*reaper_routine(void *arg)
{
	t_reaper_arg	*args;

	args = (t_reaper_arg *)arg;
	while (1)
	{
		if (args->param->finished == args->param->nb_philo)
		{
			kill(args, args->id, 0);
			break ;
		}
		pthread_mutex_lock(&args->param->eating_lock[args->id - 1]);
		if ((args->param->dth_time[args->id - 1] <= time_us(args->param->strt))
			&& args->param->is_alive)
		{
			kill(args, args->id, 1);
			pthread_mutex_unlock(&args->param->eating_lock[args->id - 1]);
			break ;
		}
		pthread_mutex_unlock(&args->param->eating_lock[args->id - 1]);
		if (!is_alive(args->param))
			break ;
		usleep(100);
	}
	free(arg);
	return (NULL);
}
