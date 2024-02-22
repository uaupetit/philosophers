/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:05:16 by uaupetit          #+#    #+#             */
/*   Updated: 2024/02/22 15:23:47 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	thread_loop(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_start_time(data);
	while (i < data->nb_philo)
	{
		if (pthread_create(&(data->philo[i].thread), NULL,
				thread_routine, &(data->philo[i])) == 0)
			i++;
		else
		{
			ft_free(data);
			return (1);
		}
	}
	while (philo_is_dead(data) == 0)
		;
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	ft_free(data);
	return (0);
}

void	*thread_routine(void *philosophe)
{
	t_philo	*philo;

	philo = (t_philo *)philosophe;
	if (philo->num_philo % 2)
		ft_usleep(10, philo);
	while (check_death(philo->data) == 0 && check_full_meal(philo) == 0)
	{
		lock_fork(philo);
		print_message(philo, "has taken a fork");
		print_message(philo, "has taken a fork");
		print_message(philo, "is eating");
		philo->last_meal = get_time(philo);
		philo->done_meal++;
		ft_usleep(philo->t_eat, philo);
		unlock_fork(philo);
		print_message(philo, "is sleeping");
		ft_usleep(philo->t_sleep, philo);
		print_message(philo, "is thinking");
		if (philo->nb_philo % 2)
			ft_usleep(10, philo);
	}
	return (NULL);
}

void	print_message(t_philo *philo, char *str)
{
	if (check_death(philo->data) == 0)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%lld %d %s\n", get_time(philo), philo->num_philo, str);
		pthread_mutex_unlock(&philo->data->print);
	}
	return ;
}

void	lock_fork(t_philo *philo)
{
	if (philo->num_philo % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
}

void	unlock_fork(t_philo *philo)
{
	if (philo->num_philo % 2)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}
