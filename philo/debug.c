/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 10:03:02 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/10 17:11:40 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	debug_print_param(t_param *param)
{
	printf("number_of_philosophers = %u\n", param->number_of_philosophers);
	printf("time_to_die = %llu\n", param->time_to_die);
	printf("time_to_eat = %llu\n", param->time_to_eat);
	printf("time_to_sleep = %llu\n", param->time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat = %llu\n",
		param->number_of_times_each_philosopher_must_eat);
	return ;
}
