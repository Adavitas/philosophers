/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:19:58 by adavitas          #+#    #+#             */
/*   Updated: 2026/02/12 17:46:07 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sim_ended(t_philo *ph)
{
	pthread_mutex_lock(&ph->table->mtx_stop);
	if (ph->table->sim_stop)
	{
		pthread_mutex_unlock(&ph->table->mtx_stop);
		return (1);
	}
	pthread_mutex_unlock(&ph->table->mtx_stop);
	return (0);
}

void	log_action(t_philo *ph, char *msg)
{
	size_t	elapsed;

	pthread_mutex_lock(&ph->table->mtx_print);
	pthread_mutex_lock(&ph->table->mtx_stop);
	elapsed = get_time() - ph->table->t_start;
	if (!ph->table->sim_stop || msg[0] == 'd')
		printf("%zu %i %s\n", elapsed, ph->id, msg);
	pthread_mutex_unlock(&ph->table->mtx_stop);
	pthread_mutex_unlock(&ph->table->mtx_print);
}
