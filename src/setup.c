#include "philo.h"

static void	setup_philo(t_philo *ph, t_table *tbl, char **av)
{
	ph->table = tbl;
	ph->mtx_meal = malloc(sizeof(t_mtx));
	pthread_mutex_init(ph->mtx_meal, NULL);
	ph->tt_die = ft_atoi(av[2]);
	ph->tt_eat = ft_atoi(av[3]);
	ph->tt_sleep = ft_atoi(av[4]);
	ph->last_eat = get_time();
	ph->eat_count = 0;
}

void	setup_philos(t_table *tbl, char **av)
{
	int	i;

	i = -1;
	while (++i < tbl->nb_philos)
	{
		tbl->philos[i].id = i + 1;
		setup_philo(&tbl->philos[i], tbl, av);
	}
}

void	setup_table(t_table *tbl, char **av)
{
	int	i;

	tbl->nb_philos = ft_atoi(av[1]);
	pthread_mutex_init(&tbl->mtx_print, NULL);
	pthread_mutex_init(&tbl->mtx_stop, NULL);
	tbl->forks = malloc(sizeof(t_mtx) * tbl->nb_philos);
	i = -1;
	while (++i < tbl->nb_philos)
		pthread_mutex_init(&tbl->forks[i], NULL);
	tbl->sim_stop = 0;
	if (av[5])
		tbl->max_meals = ft_atoi(av[5]);
	else
		tbl->max_meals = -1;
}
