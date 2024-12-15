/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 08:14:57 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/15 14:30:06 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_the_table(int nb_philo, pthread_mutex_t *mutex)
{
	while (--nb_philo != 0)
	{
		pthread_mutex_destroy(&mutex[nb_philo]);
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

int	init_simulation(int argc, char **argv, t_param *param,
		pthread_mutex_t **frk_lock)
{
	if (!intitialize_param(argc, argv, param))
		return (0);
	*frk_lock = make_fork_mutexes(param);
	param->eating_lock = make_eating_mutexes(param, *frk_lock);
	param->finished_lock = make_finish_mutexes(param, *frk_lock);
	param->finished = 0;
	return (*frk_lock != NULL && param->eating_lock != NULL
		&& param->finished_lock != NULL);
}

int	main(int argc, char **argv)
{
	t_param			param;
	pthread_t		*philo;
	pthread_mutex_t	*frk_lock;

	philo = NULL;
	if (!init_simulation(argc, argv, &param, &frk_lock))
		return (0);
	if (!strt_philo(&philo, &param, &frk_lock))
		return (printf("Thread creation failed\n"), cleanup_5(&param, frk_lock),
			free(philo), end_philo(&philo,
				param.nb_philo), 0);
	end_philo(&philo, param.nb_philo);
	cleanup_5(&param, frk_lock);
	free(philo);
	return (0);
}
