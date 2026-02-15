/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:19:56 by adavitas          #+#    #+#             */
/*   Updated: 2026/02/15 20:47:23 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	starved(t_philo *ph)
{
	pthread_mutex_lock(ph->mtx_meal);
	if (get_time() - ph->last_eat > ph->tt_die)
	{
		pthread_mutex_unlock(ph->mtx_meal);
		return (1);
	}
	pthread_mutex_unlock(ph->mtx_meal);
	return (0);
}

static int	scan_deaths(t_philo *phs, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (starved(&phs[i]))
		{
			log_action(&phs[i], "died");
			pthread_mutex_lock(&phs->table->mtx_stop);
			phs->table->sim_stop = 1;
			pthread_mutex_unlock(&phs->table->mtx_stop);
			return (1);
		}
	}
	return (0);
}

static int	all_ate(t_philo *phs, int n)
{
	int	i;
	int	done;

	if (phs->table->max_meals == -1)
		return (0);
	i = -1;
	done = 0;
	while (++i < n)
	{
		pthread_mutex_lock(phs[i].mtx_meal);
		if (phs[i].eat_count >= phs->table->max_meals)
			done++;
		pthread_mutex_unlock(phs[i].mtx_meal);
	}
	if (done == n)
	{
		pthread_mutex_lock(&phs->table->mtx_stop);
		phs->table->sim_stop = 1;
		pthread_mutex_unlock(&phs->table->mtx_stop);
		return (1);
	}
	return (0);
}

void	*observer(void *arg)
{
	t_philo	*phs;
	int		n;

	phs = (t_philo *)arg;
	n = phs->table->nb_philos;
	while (1)
	{
		if (scan_deaths(phs, n) || all_ate(phs, n))
			break ;
		usleep(500);
	}
	return (arg);
}
