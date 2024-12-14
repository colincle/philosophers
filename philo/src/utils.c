/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 08:33:16 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/14 17:12:51 by ccolin           ###   ########.fr       */
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

unsigned long long	time_us(unsigned long long start)
{
	struct timeval		tv;
	unsigned long long	current_us;

	gettimeofday(&tv, NULL);
	current_us = (tv.tv_sec * 1000000) + tv.tv_usec;
	if (start)
	{
		return (current_us - start);
	}
	return (current_us);
}
