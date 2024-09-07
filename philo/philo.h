/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 08:15:04 by ccolin            #+#    #+#             */
/*   Updated: 2024/09/07 11:07:22 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>

typedef struct s_parameters
{
	unsigned int		number_of_philosophers;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	number_of_times_each_philosopher_must_eat;
}					t_parameters;

// initialization.c

int		intitialize_parameters(int argc, char **argv, t_parameters	*parameters);

// minilibft.c

char	*ft_strchr(const char *s, int c);

// debug.c

void	debug_print_parameters(t_parameters *parameters);

#endif