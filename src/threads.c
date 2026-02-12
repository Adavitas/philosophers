/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:20:06 by adavitas          #+#    #+#             */
/*   Updated: 2026/02/12 17:47:25 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run_threads(t_table *tbl)
{
	int	i;

	tbl->t_start = get_time();
	i = -1;
	while (++i < tbl->nb_philos)
		tbl->philos[i].last_eat = tbl->t_start;
	pthread_create(&tbl->tid_mon, NULL, observer, tbl->philos);
	i = -1;
	while (++i < tbl->nb_philos)
		pthread_create(&tbl->philos[i].tid, NULL,
			lifecycle, &tbl->philos[i]);
	i = -1;
	while (++i < tbl->nb_philos)
		pthread_join(tbl->philos[i].tid, NULL);
	pthread_join(tbl->tid_mon, NULL);
}

void	destroy_all(t_table *tbl)
{
	int	i;

	i = -1;
	while (++i < tbl->nb_philos)
	{
		pthread_mutex_destroy(tbl->philos[i].mtx_meal);
		free(tbl->philos[i].mtx_meal);
		pthread_mutex_destroy(&tbl->forks[i]);
	}
	pthread_mutex_destroy(&tbl->mtx_print);
	pthread_mutex_destroy(&tbl->mtx_stop);
	free(tbl->forks);
}
