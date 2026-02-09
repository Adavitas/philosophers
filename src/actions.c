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
	grab_forks(ph);
	log_action(ph, "is eating");
	pthread_mutex_lock(ph->mtx_meal);
	ph->last_eat = get_time();
	ph->eat_count++;
	pthread_mutex_unlock(ph->mtx_meal);
	precise_sleep(ph->tt_eat);
	pthread_mutex_unlock(
		&ph->table->forks[(ph->id - 1) % ph->table->nb_philos]);
	pthread_mutex_unlock(
		&ph->table->forks[ph->id % ph->table->nb_philos]);
}

void	do_sleep(t_philo *ph)
{
	log_action(ph, "is sleeping");
	precise_sleep(ph->tt_sleep);
}

void	do_think(t_philo *ph)
{
	log_action(ph, "is thinking");
}

void	*lifecycle(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->id % 2 == 0)
		precise_sleep(1);
	if (ph->table->nb_philos == 1)
	{
		log_action(ph, "has taken a fork");
		precise_sleep(ph->tt_die);
		log_action(ph, "died");
		pthread_mutex_lock(&ph->table->mtx_stop);
		ph->table->sim_stop = 1;
		pthread_mutex_unlock(&ph->table->mtx_stop);
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
