/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:19:32 by adavitas          #+#    #+#             */
/*   Updated: 2026/02/12 17:43:26 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

# define MAX_PHILOS 200

typedef pthread_mutex_t	t_mtx;
typedef pthread_t		t_tid;

typedef struct s_table	t_table;

typedef struct s_philo
{
	int		id;
	t_tid	tid;
	t_mtx	*mtx_meal;
	size_t	tt_die;
	size_t	tt_eat;
	size_t	tt_sleep;
	size_t	last_eat;
	int		eat_count;
	t_table	*table;
}			t_philo;

struct	s_table
{
	t_tid	tid_mon;
	t_philo	*philos;
	t_mtx	mtx_print;
	t_mtx	mtx_stop;
	t_mtx	*forks;
	int		nb_philos;
	int		max_meals;
	size_t	t_start;
	int		sim_stop;
};

int		validate_input(int argc, char **argv);
int		ft_atoi(char *str);
void	precise_sleep(size_t ms);
size_t	get_time(void);
void	run_threads(t_table *tbl);
void	destroy_all(t_table *tbl);
void	setup_table(t_table *tbl, char **argv);
void	setup_philos(t_table *tbl, char **argv);
void	*lifecycle(void *arg);
void	do_eat(t_philo *ph);
void	do_sleep(t_philo *ph);
void	do_think(t_philo *ph);
void	log_action(t_philo *ph, char *msg);
int		sim_ended(t_philo *ph);
void	*observer(void *arg);

#endif
