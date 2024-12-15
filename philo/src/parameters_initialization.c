/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_initialization.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 08:27:13 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/10 14:09:40 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_param(t_param *param, int argc)
{
	if (param->nb_philo < 1)
	{
		printf("Error\nInvalid argument(s). ");
		printf("There must be at least one philo.\n");
		return (0);
	}
	if (param->nb_philo == 0 || param->time_to_die == 0
		|| param->time_to_eat == 0 || param->time_to_sleep == 0)
	{
		printf("Error\nInvalid argument(s). ");
		printf("Please provide positive numbers for all param.\n");
		return (0);
	}
	if (argc == 6)
	{
		if (param->num_eats_per_philosopher == 0)
		{
			printf("Error\nInvalid argument(s). ");
			printf("Please provide positive numbers for all param.\n");
			return (0);
		}
	}
	return (1);
}

unsigned long long	get_parameter(char *str)
{
	unsigned long long	nbr;
	int					i;

	if (str_is_not_digits_only(str))
		return (0);
	i = 0;
	nbr = 0;
	while (str[i])
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr);
}

int	allocate_param_memory(t_param *param)
{
	unsigned int	i;

	param->status = malloc(sizeof(int) * param->nb_philo);
	if (!param->status)
		return (0);
	i = 0;
	while (i < param->nb_philo)
		param->status[i++] = ALIVE;
	param->is_alive = ALIVE;
	param->dth_time = malloc(sizeof(unsigned long long) * param->nb_philo);
	if (!param->dth_time)
		return (free(param->status), 0);
	param->forks = malloc(sizeof(int) * param->nb_philo);
	if (!param->forks)
		return (free(param->status), free(param->dth_time), 0);
	i = 0;
	while (i < param->nb_philo)
		param->forks[i++] = ON_THE_TABLE;
	return (1);
}

int	intitialize_param(int argc, char **argv, t_param *param)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error\nUsage: ./philo nb_philo time_to_die time_to_eat ");
		printf("time_to_sleep [num_eats_per_philosopher]\n");
		return (0);
	}
	param->strt = time_us(0);
	param->nb_philo = (unsigned int)get_parameter(argv[1]);
	param->time_to_die = get_parameter(argv[2]) * 1000;
	param->time_to_eat = get_parameter(argv[3]) * 1000;
	param->time_to_sleep = get_parameter(argv[4]) * 1000;
	param->num_eats_per_philosopher = 0;
	if (param->nb_philo == 1)
	{
		printf("%-5lld Philosopher ", time_us(param->strt) / 1000);
		printf("1 has taken a fork\n");
		usleep(param->time_to_die);
		printf("%-5lld Philosopher 1 has died\n", time_us(param->strt) / 1000);
		return (0);
	}
	if (argc == 6)
		param->num_eats_per_philosopher = (unsigned int)get_parameter(argv[5]);
	if (!check_param(param, argc) || !allocate_param_memory(param))
		return (0);
	return (1);
}
