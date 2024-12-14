/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:17:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/14 17:16:35 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_param *param)
{
	if (!param->is_alive)
		return (0);
	return (1);
}

void	kill(t_reaper_arg *args, int i)
{
	args->param->is_alive = DEAD;
	printf("%-5lld Philosopher %d", time_us(args->param->start) / 1000, i + 1);
	printf(" died\n");
}

void	*reaper_routine(void *arg)
{
	t_reaper_arg	*args;
	unsigned int	i;

	args = (t_reaper_arg *)arg;
	while (1)
	{
		i = 0;
		while (i < args->param->nb_philo)
		{
			if (is_alive(args->param) && args->param->status[i] != EATING)
			{
				if (args->param->death_time[i] <= time_us(args->param->start))
				{
					kill(args, i);
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
