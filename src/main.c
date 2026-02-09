#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;
	t_philo	philos[MAX_PHILOS];

	if (validate_input(ac, av))
		return (1);
	table.philos = philos;
	setup_table(&table, av);
	setup_philos(&table, av);
	run_threads(&table);
	destroy_all(&table);
	return (0);
}
