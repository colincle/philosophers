/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters_initialization.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 08:27:13 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/09 14:04:40 by ccolin           ###   ########.fr       */
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

static int	check_parameters(t_parameters *parameters, int argc)
{
	if (parameters->number_of_philosophers < 1)
		{
			printf("Error\nInvalid argument(s). There must be at least one philosophers.\n");
			return (0);
		}
	if (parameters->number_of_philosophers == 0 || parameters->time_to_die \
	== 0 || parameters->time_to_eat == 0 || parameters->time_to_sleep == 0)
	{
		printf("Error\nInvalid argument(s). Please provide positive numbers for all parameters.\n");
		return (0);
	}
	if (argc == 6)
		if (parameters->number_of_times_each_philosopher_must_eat == 0)
		{
			printf("Error\nInvalid argument(s). Please provide positive numbers for all parameters.\n");
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

int	intitialize_parameters(int argc, char **argv, t_parameters	*parameters)
{
	unsigned int		i;
	i = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Error\nUsage: ./philo number_of_philosophers time_to_die time_"
		"to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	parameters->start = get_time_ms();
	parameters->number_of_philosophers = (unsigned int)get_parameter(argv[1]);
	parameters->time_to_die = get_parameter(argv[2]);
	parameters->time_to_eat = get_parameter(argv[3]);
	parameters->time_to_sleep = get_parameter(argv[4]);
	if (argc == 6)
		parameters->number_of_times_each_philosopher_must_eat = (unsigned int)get_parameter(argv[5]);
	else
		parameters->number_of_times_each_philosopher_must_eat = 0;
	if (!check_parameters(parameters, argc))
		return (0);
	parameters->status = malloc(sizeof(int) * (parameters->number_of_philosophers));
	if (!parameters->status)
		return (0);
	while (i < parameters->number_of_philosophers)
		parameters->status[i++] = ALIVE;
	i = 0;
	parameters->is_alive = malloc(sizeof(int) * (parameters->number_of_philosophers));
	if (!parameters->is_alive)
		return (0);
	while (i < parameters->number_of_philosophers)
		parameters->is_alive[i++] = ALIVE;
	i = 0;
	parameters->time_of_death = malloc(sizeof(unsigned long long) * (parameters->number_of_philosophers));
	if (!parameters->time_of_death)
		return (0);
	while ((unsigned int)i < parameters->number_of_philosophers)
		parameters->time_of_death[i++] = parameters->start + parameters->time_to_die;
	return (1);
}
