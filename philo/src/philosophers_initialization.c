/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initialization.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:17:50 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/14 16:20:29 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*new_philo_arg(t_param *param, int i, pthread_mutex_t **frk_lock)
{
	t_philo_arg	*philo_arg;

	philo_arg = malloc(sizeof(t_philo_arg));
	if (!philo_arg)
		return (NULL);
	philo_arg->id = i + 1;
	philo_arg->param = param;
	philo_arg->frk_lock = *frk_lock;
	return ((void *)philo_arg);
}

int	strt_philo(pthread_t **philo, t_param *param,
		pthread_mutex_t **frk_lock)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	*philo = malloc(sizeof(pthread_t) * param->nb_philo);
	if (!*philo)
		return (0);
	while (i < param->nb_philo)
	{
		if (pthread_create(&(*philo)[i], NULL, routine,
			new_philo_arg(param, i, frk_lock)))
		{
			printf("Thread creation failed\n");
			j = 0;
			while (j < i)
				pthread_join((*philo)[j++], NULL);
			free(*philo);
			return (0);
		}
		i++;
	}
	return (1);
}
