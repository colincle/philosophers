/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 08:33:16 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/15 18:38:50 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return ((void *)0);
}

int	str_is_not_digits_only(char *str)
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

unsigned long long	time_us(unsigned long long strt)
{
	struct timeval		tv;
	unsigned long long	current_us;

	gettimeofday(&tv, NULL);
	current_us = (tv.tv_sec * 1000000) + tv.tv_usec;
	if (strt)
	{
		return (current_us - strt);
	}
	return (current_us);
}

void	swap_forks(unsigned int *left, unsigned int *right)
{
	unsigned int	temp;

	temp = *left;
	*left = *right;
	*right = temp;
}

void	set_time_of_death(t_philo_arg *args)
{
	if (args->id % 2 != 0)
		usleep(1500);
	args->param->dth_time[args->id - 1] = time_us(args->param->strt)
		+ args->param->time_to_die;
}
