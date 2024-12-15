/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 08:14:57 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/15 14:27:20 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_1(t_param *param)
{
	free(param->status);
	free(param->dth_time);
	free(param->forks);
}

void	cleanup_2(t_param *param, pthread_mutex_t *frk_lock)
{
	cleanup_1(param);
	free(frk_lock);
}

void	cleanup_3(t_param *param, pthread_mutex_t *frk_lock)
{
	clean_the_table(param->nb_philo, frk_lock);
	cleanup_2(param, frk_lock);
}

void	cleanup_4(t_param *param, pthread_mutex_t *frk_lock)
{
	clean_the_table(param->nb_philo, param->eating_lock);
	free(param->eating_lock);
	cleanup_3(param, frk_lock);
}

void	cleanup_5(t_param *param, pthread_mutex_t *frk_lock)
{
	clean_the_table(param->nb_philo, param->finished_lock);
	cleanup_4(param, frk_lock);
	free(param->finished_lock);
}
