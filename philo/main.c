/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 08:14:57 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/03 14:22:05 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_t *forks;
	unsigned int		i;
	
	i = 0;	
	forks = malloc(sizeof(pthread_mutex_t) * parameters->number_of_philosophers);
	if (!forks)
		return (NULL);
	while (i < parameters->number_of_philosophers)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (--i != 0)
				pthread_mutex_destroy(&forks[i]);
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}


int	main(int argc, char **argv)
{
	t_parameters	parameters;
	pthread_t		*philosophers;
	pthread_mutex_t	*forks;

	philosophers = NULL;
	if (!intitialize_parameters(argc, argv, &parameters))
		return (0);
	forks = set_the_table(&parameters);
	if (start_philosophers(&philosophers, &parameters, &forks))
		return (0);
	end_philosophers(&philosophers, parameters.number_of_philosophers);
}
