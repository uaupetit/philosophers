/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:47:57 by uaupetit          #+#    #+#             */
/*   Updated: 2023/08/01 17:55:02 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				num_philo;
	int				nb_philo;
	int				t_die;
	int				t_sleep;
	int				t_eat;
	int				nb_meal;
	int				is_dead;
	int				done_meal;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_meal;
	int				is_dead;
	long long		start_time;
	long long		current_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	dead_philo;
	pthread_mutex_t	meal;
}	t_data;

int			main(int ac, char **av);
int			parsing(int ac, char **av);
int			ft_atoi(const char *nptr);
int			ft_atoi_char(const char str);
int			ft_isdigit(int c);

int			initialize(t_data *data, char **av);
int			initialize_mutex(t_data *data);
void		initialize_philo(t_data *data);
void		solo_philo(t_data *data);
int			thread_loop(t_data *data);
long long	get_start_time(t_data *data);

void		*thread_routine(void *philosophe);
int			count_meal(t_philo *philo);
void		lock_fork(t_philo *philo);
void		print_message(t_philo *philo, char *str);
void		ft_usleep(int time, t_philo *philo);
void		unlock_fork(t_philo *philo);
int			philo_is_dead(t_data *data);
int			check_death(t_data *data);
void		death_init(t_philo *philo);
int			time_since_last_meal(t_philo *philo);
int			check_meal(t_data *data);
void		thinking(t_philo *philo);
int			check_full_meal(t_philo *philo);
int			check_all_phi_meal(t_data *data);
long long	get_time(t_philo *philo);
void		ft_free(t_data *data);
void		thinking(t_philo *philo);
#endif
