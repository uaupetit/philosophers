/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:48:45 by uaupetit          #+#    #+#             */
/*   Updated: 2024/02/22 15:23:47 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	initialize(t_data *data, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->is_dead = 0;
	data->nb_meal = 0;
	if (av[5])
		data->nb_meal = ft_atoi(av[5]);
	else
		data->nb_meal = -1;
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
	{
		printf("Cannot malloc philo\n");
		return (1);
	}
	return (0);
}

int	initialize_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meal, NULL);
	pthread_mutex_init(&data->dead_philo, NULL);
	return (0);
}

void	initialize_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].last_meal = 0;
		data->philo[i].num_philo = i + 1;
		data->philo[i].nb_philo = data->nb_philo;
		data->philo[i].t_die = data->t_die;
		data->philo[i].t_eat = data->t_eat;
		data->philo[i].t_sleep = data->t_sleep;
		data->philo[i].is_dead = 0;
		data->philo[i].done_meal = 0;
		data->philo[i].nb_meal = data->nb_meal;
		data->philo[i].data = data;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[i + 1];
		if (i == data->nb_philo - 1)
		{
			data->philo[i].left_fork = &data->forks[i];
			data->philo[i].right_fork = &data->forks[0];
		}
		i++;
	}
}

void	solo_philo(t_data *data)
{
	printf("0 1 has taken a fork\n");
	usleep(data->t_die * 1000);
	printf("%d 1 died\n", (data->t_die + 1));
	ft_free(data);
}
