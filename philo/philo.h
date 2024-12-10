/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 08:15:04 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/10 14:09:40 by ccolin           ###   ########.fr       */
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
	int					*status;
	int					*forks;
}					t_parameters;

typedef struct s_philo_arg
{
	unsigned int				id;
	pthread_mutex_t	*forks_locks;
	t_parameters	*parameters;
}					t_philo_arg;

typedef struct s_gr_arg
{
	pthread_t 		*philosophers;
	t_parameters	*parameters;
}					t_gr_arg;

#define EATING 100
#define ALIVE 101
#define DEAD 0
#define ON_THE_TABLE 102
#define USED 0

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

int	start_philosophers(pthread_t **philosophers, t_parameters *parameters, pthread_mutex_t **forks_locks);

unsigned long long	get_time_us(unsigned long long start);

void	*gr_routine(void *arg);

void *gr_args(t_parameters *parameters, pthread_t *philosophers);

#endif
