/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:15:06 by uaupetit          #+#    #+#             */
/*   Updated: 2024/02/22 15:23:47 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philo);
	pthread_mutex_destroy(&(data->print));
	pthread_mutex_destroy(&(data->dead_philo));
	pthread_mutex_destroy(&(data->meal));
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	return (nb);
}

int	ft_atoi_char(const char str)
{
	int	sum;

	sum = 0;
	sum = str - 48;
	return (sum);
}

int	parsing(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (ac == 5 || ac == 6)
	{
		while (av[j])
		{
			while (av[j][i])
			{
				if (ft_isdigit(ft_atoi_char(av[j][i])) == 1)
					i++;
				else
					return (1);
			}
			i = 0;
			j++;
		}
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (parsing(ac, av) == 0)
	{
		if (initialize(&data, av) == 1)
			return (0);
		if (data.nb_philo <= 0 || data.t_die <= 0
			|| data.t_eat <= 0 || data.t_sleep <= 0)
		{
			printf("Invalid Arguments\n");
			return (0);
		}
		if (initialize_mutex(&data) == 1)
			return (0);
		initialize_philo(&data);
		if (data.nb_philo == 1)
		{
			solo_philo(&data);
			return (0);
		}
		if (thread_loop(&data) == 1)
			return (0);
	}
	else
		printf("Invalid Arguments\n");
}
