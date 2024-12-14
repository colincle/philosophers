/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 08:14:57 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/14 16:20:47 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_the_table(int nb_philo, pthread_mutex_t *frk_lock)
{
	while (--nb_philo != 0)
	{
		pthread_mutex_destroy(&frk_lock[nb_philo]);
	}
}

void	end_philo(pthread_t **philo, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		pthread_join((*philo)[i++], NULL);
	}
}

void	cleanup_1(t_param *param)
{
	free(param->status);
	free(param->death_time);
	free(param->forks);
}

void	cleanup_2(t_param *param, pthread_mutex_t *frk_lock)
{
	clean_the_table(param->nb_philo, frk_lock);
	cleanup_1(param);
	free(frk_lock);
}

void	cleanup_3(t_param *param, pthread_mutex_t *frk_lock, pthread_t *reaper)
{
	cleanup_2(param, frk_lock);
	free(reaper);
}
