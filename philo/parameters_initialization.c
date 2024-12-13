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

static int	str_is_not_digits_only(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr("0123456789", str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	check_param(t_param *param, int argc)
{
	if (param->number_of_philosophers < 1)
	{
		printf("Error\nInvalid argument(s). There must be at least one philosophers.\n");
		return (0);
	}
	if (param->number_of_philosophers == 0 || param->time_to_die == 0
		|| param->time_to_eat == 0 || param->time_to_sleep == 0)
	{
		printf("Error\nInvalid argument(s). Please provide positive numbers for all param.\n");
		return (0);
	}
	if (argc == 6)
		if (param->number_of_times_each_philosopher_must_eat == 0)
		{
			printf("Error\nInvalid argument(s). Please provide positive numbers for all param.\n");
			return (0);
		}
	return (1);
}

static unsigned long long	get_parameter(char *str)
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

int	intitialize_param(int argc, char **argv, t_param *param)
{
	unsigned int	i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Error\nUsage: ./philo number_of_philosophers time_to_die time_"
				"to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	param->start = time_us(0);
	param->number_of_philosophers = (unsigned int)get_parameter(argv[1]);
	param->time_to_die = get_parameter(argv[2]) * 1000;
	param->time_to_eat = get_parameter(argv[3]) * 1000;
	param->time_to_sleep = get_parameter(argv[4]) * 1000;
	if (argc == 6)
		param->number_of_times_each_philosopher_must_eat = (unsigned int)get_parameter(argv[5]);
	else
		param->number_of_times_each_philosopher_must_eat = 0;
	if (!check_param(param, argc))
		return (0);
	param->status = malloc(sizeof(int) * (param->number_of_philosophers));
	if (!param->status)
		return (0);
	while (i < param->number_of_philosophers)
		param->status[i++] = ALIVE;
	param->is_alive = ALIVE;
	i = 0;
	param->time_of_death = malloc(sizeof(unsigned long long)
			* (param->number_of_philosophers));
	if (!param->time_of_death)
	{
		free (param->status);
		return (0);
	}
	param->forks = malloc(sizeof(int) * (param->number_of_philosophers));
	if (!param->forks)
	{
		free (param->status);
		free (param->time_of_death);
		return (0);
	}
	while ((unsigned int)i < param->number_of_philosophers)
		param->forks[i++] = ON_THE_TABLE;
	return (1);
}
