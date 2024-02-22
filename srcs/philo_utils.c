/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:12:34 by uaupetit          #+#    #+#             */
/*   Updated: 2024/02/22 15:23:47 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_usleep(int time, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < time && check_death(philo->data) == 0)
	{
		usleep(10000);
		i += 10;
	}
}

long long	get_start_time(t_data *data)
{
	struct timeval	tv;

	(void)data;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	get_time(t_philo *philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - philo->data->start_time);
}

int	ft_isdigit(int c)
{
	if (c >= 0 && c <= 9)
		return (1);
	else
		return (0);
}

int	check_death(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->dead_philo);
	i = data->is_dead;
	pthread_mutex_unlock(&data->dead_philo);
	return (i);
}
