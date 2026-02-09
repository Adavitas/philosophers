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
	if (!ph->table->sim_stop)
	{
		elapsed = get_time() - ph->table->t_start;
		pthread_mutex_unlock(&ph->table->mtx_stop);
		printf("%zu %i %s\n", elapsed, ph->id, msg);
	}
	else
		pthread_mutex_unlock(&ph->table->mtx_stop);
	pthread_mutex_unlock(&ph->table->mtx_print);
}
