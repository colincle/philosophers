/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 10:03:02 by ccolin            #+#    #+#             */
/*   Updated: 2024/09/07 10:08:12 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	debug_print_parameters(t_parameters *parameters)
{
	printf("number_of_philosophers = %u\n", parameters->number_of_philosophers);
	printf("time_to_die = %llu\n", parameters->time_to_die);
	printf("time_to_eat = %llu\n", parameters->time_to_eat);
	printf("time_to_sleep = %llu\n", parameters->time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat = %llu\n", parameters->number_of_times_each_philosopher_must_eat);
	return ;
}
