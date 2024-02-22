/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:21:51 by uaupetit          #+#    #+#             */
/*   Updated: 2024/02/22 15:23:47 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_all_phi_meal(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (!check_full_meal(&data->philo[i]))
			break ;
		i++;
	}
	if (i == data->nb_philo)
		return (1);
	return (0);
}

int	philo_is_dead(t_data *data)
{
	int	i;

	i = 0;
	while (check_death(data) == 0)
	{
		while (i < data->nb_philo)
		{
			if (check_full_meal(&data->philo[i]) == 0)
			{
				if (time_since_last_meal(&data->philo[i]) == 1)
				{
					death_init(&data->philo[i]);
					return (1);
				}
			}
			i++;
		}
		i = 0;
		if (check_all_phi_meal(data) == 1)
			return (1);
	}
	return (0);
}

void	death_init(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->dead_philo));
	philo->data->is_dead = 1;
	pthread_mutex_unlock(&(philo->data->dead_philo));
	pthread_mutex_lock(&(philo->data->print));
	printf("%lld %d died\n", get_time(philo),
		philo->num_philo);
	pthread_mutex_unlock(&(philo->data->print));
}

int	time_since_last_meal(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->data->meal);
	if ((get_time(philo) - philo->last_meal) > philo->t_die)
		i = 1;
	else
		i = 0;
	pthread_mutex_unlock(&philo->data->meal);
	return (i);
}

int	check_full_meal(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->data->meal);
	if (philo->nb_meal == -1)
		i = 0;
	else if (philo->done_meal < philo->data->nb_meal)
		i = 0;
	else
		i = 1;
	pthread_mutex_unlock(&philo->data->meal);
	return (i);
}
