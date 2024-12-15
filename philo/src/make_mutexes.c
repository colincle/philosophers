/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:25:38 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/15 14:30:19 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*make_fork_mutexes(t_param *param)
{
	pthread_mutex_t	*frk_lock;
	unsigned int	i;

	i = 0;
	frk_lock = malloc(sizeof(pthread_mutex_t) * param->nb_philo);
	if (!frk_lock)
	{
		cleanup_1(param);
		return (NULL);
	}
	while (i < param->nb_philo)
	{
		if (pthread_mutex_init(&frk_lock[i], NULL) != 0)
		{
			while (--i != 0)
			{
				pthread_mutex_destroy(&frk_lock[i]);
			}
			cleanup_2(param, frk_lock);
			return (NULL);
		}
		i++;
	}
	return (frk_lock);
}

pthread_mutex_t	*make_eating_mutexes(t_param *param, pthread_mutex_t *frk_lock)
{
	pthread_mutex_t	*eating_lock;
	unsigned int	i;

	i = 0;
	eating_lock = malloc(sizeof(pthread_mutex_t) * param->nb_philo);
	if (!eating_lock)
	{
		cleanup_3(param, frk_lock);
		return (NULL);
	}
	while (i < param->nb_philo)
	{
		if (pthread_mutex_init(&eating_lock[i], NULL) != 0)
		{
			while (--i != 0)
			{
				pthread_mutex_destroy(&eating_lock[i]);
			}
			free(eating_lock);
			cleanup_3(param, frk_lock);
			return (NULL);
		}
		i++;
	}
	return (eating_lock);
}

pthread_mutex_t	*make_finish_mutexes(t_param *param, pthread_mutex_t *frk_lock)
{
	pthread_mutex_t	*finish_lock;
	unsigned int	i;

	i = 0;
	finish_lock = malloc(sizeof(pthread_mutex_t) * param->nb_philo);
	if (!finish_lock)
	{
		cleanup_4(param, frk_lock);
		return (NULL);
	}
	while (i < param->nb_philo)
	{
		if (pthread_mutex_init(&finish_lock[i], NULL) != 0)
		{
			while (--i != 0)
			{
				pthread_mutex_destroy(&finish_lock[i]);
			}
			free(finish_lock);
			cleanup_4(param, finish_lock);
			return (NULL);
		}
		i++;
	}
	return (finish_lock);
}
