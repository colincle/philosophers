/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 08:14:57 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/14 16:20:47 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*set_the_table(t_param *param)
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

int	init_simulation(int argc, char **argv, t_param *param,
		pthread_mutex_t **frk_lock)
{
	if (!intitialize_param(argc, argv, param))
		return (0);
	*frk_lock = set_the_table(param);
	return (*frk_lock != NULL);
}

int	main(int argc, char **argv)
{
	t_param			param;
	pthread_t		*philo;
	pthread_t		*reaper;
	pthread_mutex_t	*frk_lock;

	philo = NULL;
	if (!init_simulation(argc, argv, &param, &frk_lock))
		return (0);
	reaper = malloc(sizeof(pthread_t));
	if (!reaper)
		return (cleanup_2(&param, frk_lock), 0);
	if (!strt_philo(&philo, &param, &frk_lock)
		|| pthread_create(reaper, NULL, reaper_routine, reaper_args(&param,
				philo)))
		return (printf("Thread creation failed\n"), cleanup_3(&param, frk_lock,
				reaper), free(philo), end_philo(&philo,
				param.nb_philo), 0);
	pthread_join(*reaper, NULL);
	end_philo(&philo, param.nb_philo);
	cleanup_3(&param, frk_lock, reaper);
	free(philo);
	return (0);
}
