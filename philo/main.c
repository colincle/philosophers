/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 08:14:57 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/10 12:56:34 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long get_time_ms(unsigned long long start)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	unsigned long long current_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);

	if (start)
		return current_ms - start;
	return current_ms;
}

void	end_philosophers(pthread_t **philosophers, unsigned int n)
{
	unsigned int		i;
	
	i = 0;
	while (i < n)
	{
		pthread_join((*philosophers)[i++], NULL);
	}
}

pthread_mutex_t *set_the_table(t_parameters *parameters)
{
	pthread_mutex_t *forks_locks;
	unsigned int		i;
	
	i = 0;	
	forks_locks = malloc(sizeof(pthread_mutex_t) * parameters->number_of_philosophers);
	if (!forks_locks)
		return (NULL);
	while (i < parameters->number_of_philosophers)
	{
		if (pthread_mutex_init(&forks_locks[i], NULL) != 0)
		{
			while (--i != 0)
				pthread_mutex_destroy(&forks_locks[i]);
			free(forks_locks);
			return (NULL);
		}
		i++;
	}
	return (forks_locks);
}


int	main(int argc, char **argv)
{
	t_parameters	parameters;
	pthread_t		*philosophers;
	pthread_t		*grim_reaper;
	pthread_mutex_t	*forks_locks;

	philosophers = NULL;
	if (!intitialize_parameters(argc, argv, &parameters))
		return (0);
	forks_locks = set_the_table(&parameters);
	grim_reaper = malloc(sizeof(pthread_t));
	if (!grim_reaper)
		return (0);
	if (start_philosophers(&philosophers, &parameters, &forks_locks))
		return (0);
	if (pthread_create(grim_reaper, NULL, gr_routine, gr_args(&parameters, philosophers)))
	{
		err("Thread creation failed");
		return (0);
	}
	pthread_join(*grim_reaper, NULL);
	end_philosophers(&philosophers, parameters.number_of_philosophers);
	return (0);
}
