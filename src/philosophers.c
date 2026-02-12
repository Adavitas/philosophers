#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	philos[MAX_PHILOS];

	if (validate_input(argc, argv))
		return (1);
	table.philos = philos;
	setup_table(&table, argv);
	setup_philos(&table, argv);
	run_threads(&table);
	destroy_all(&table);
	return (0);
}
