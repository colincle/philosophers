/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 08:15:04 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/07 16:24:59 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_parameters
{
	unsigned long long	start;
	unsigned int		number_of_philosophers;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	number_of_times_each_philosopher_must_eat;
	unsigned long long	*time_of_death;
	int					*is_alive;
	pthread_mutex_t		set_time_to_die;
	pthread_mutex_t		is_alive;
}					t_parameters;

typedef struct s_philo_arg
{
	unsigned int				id;
	pthread_mutex_t	*fork;
	t_parameters	*parameters;
}					t_philo_arg;

typedef struct s_gr_arg
{
	pthread_t 		*philosophers;
	t_parameters	*parameters;
}					t_gr_arg;


// initialization.c

int		intitialize_parameters(int argc, char **argv, t_parameters	*parameters);

// minilibft.c

char	*ft_strchr(const char *s, int c);

// debug.c

void	debug_print_parameters(t_parameters *parameters);

//routine.c

void	*routine(void *arg);

//error.c

void	err(char *str);

//philosophers_initialization.c

int	start_philosophers(pthread_t **philosophers, t_parameters *parameters, pthread_mutex_t **fork);

unsigned long long	get_time_ms(void);

void	gr_routine(void *arg);


#endif
