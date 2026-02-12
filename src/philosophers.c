/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:19:38 by adavitas          #+#    #+#             */
/*   Updated: 2026/02/12 17:45:24 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
