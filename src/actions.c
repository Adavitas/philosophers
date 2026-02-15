/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:19:35 by adavitas          #+#    #+#             */
/*   Updated: 2026/02/15 20:55:48 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	grab_forks(t_philo *ph)
{
	int	l;
	int	r;

	l = (ph->id - 1) % ph->table->nb_philos;
	r = ph->id % ph->table->nb_philos;
	if (ph->id % 2 == 0)
	{
		pthread_mutex_lock(&ph->table->forks[r]);
		log_action(ph, "has taken a fork");
		pthread_mutex_lock(&ph->table->forks[l]);
	}
	else
	{
		pthread_mutex_lock(&ph->table->forks[l]);
		log_action(ph, "has taken a fork");
		pthread_mutex_lock(&ph->table->forks[r]);
	}
	log_action(ph, "has taken a fork");
}

void	do_eat(t_philo *ph)
{
	int	l;
	int	r;

	if (sim_ended(ph))
		return ;
	l = (ph->id - 1) % ph->table->nb_philos;
	r = ph->id % ph->table->nb_philos;
	grab_forks(ph);
	log_action(ph, "is eating");
	pthread_mutex_lock(ph->mtx_meal);
	ph->last_eat = get_time();
	ph->eat_count++;
	pthread_mutex_unlock(ph->mtx_meal);
	precise_sleep(ph->tt_eat);
	pthread_mutex_unlock(&ph->table->forks[l]);
	pthread_mutex_unlock(&ph->table->forks[r]);
}

void	do_sleep(t_philo *ph)
{
	if (sim_ended(ph))
		return ;
	log_action(ph, "is sleeping");
	precise_sleep(ph->tt_sleep);
}

void	do_think(t_philo *ph)
{
	size_t	think_time;

	if (sim_ended(ph))
		return ;
	log_action(ph, "is thinking");
	if (ph->table->nb_philos % 2 != 0)
	{
		think_time = (ph->tt_eat * 2 - ph->tt_sleep);
		if (think_time > 0 && think_time < ph->tt_die)
			precise_sleep(think_time / 2);
	}
}

void	*lifecycle(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->id % 2 == 0)
		precise_sleep(ph->tt_eat / 2);
	if (ph->table->nb_philos == 1)
	{
		log_action(ph, "has taken a fork");
		while (!sim_ended(ph))
			usleep(200);
		return (arg);
	}
	while (!sim_ended(ph))
	{
		do_eat(ph);
		do_sleep(ph);
		do_think(ph);
	}
	return (arg);
}
