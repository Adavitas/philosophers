/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:20:01 by adavitas          #+#    #+#             */
/*   Updated: 2026/02/12 17:46:49 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	is_valid_num(char *str, int max)
{
	int	val;

	if (!is_numeric(str))
		return (0);
	val = ft_atoi(str);
	if (val <= 0)
		return (0);
	if (max && val > MAX_PHILOS)
		return (0);
	return (1);
}

int	validate_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Usage: ./philo 5 800 200 200 [meals]\n"));
	if (!is_valid_num(argv[1], 1))
		return (printf("Error: invalid number_of_philosophers\n"));
	if (!is_valid_num(argv[2], 0))
		return (printf("Error: invalid time_to_die\n"));
	if (!is_valid_num(argv[3], 0))
		return (printf("Error: invalid time_to_eat\n"));
	if (!is_valid_num(argv[4], 0))
		return (printf("Error: invalid time_to_sleep\n"));
	if (argc == 6 && !is_valid_num(argv[5], 0))
		return (printf("Error: invalid number_of_meals\n"));
	return (0);
}

int	ft_atoi(char *str)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	if (!str)
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	return (res);
}
