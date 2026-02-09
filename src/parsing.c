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
	if (!is_numeric(str) || ft_atoi(str) <= 0)
		return (0);
	if (max && ft_atoi(str) > MAX_PHILOS)
		return (0);
	return (1);
}

int	validate_input(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("Usage: ./philo 5 800 200 200 [meals]\n"));
	if (!is_valid_num(av[1], 1))
		return (printf("Error: invalid number_of_philosophers\n"));
	if (!is_valid_num(av[2], 0))
		return (printf("Error: invalid time_to_die\n"));
	if (!is_valid_num(av[3], 0))
		return (printf("Error: invalid time_to_eat\n"));
	if (!is_valid_num(av[4], 0))
		return (printf("Error: invalid time_to_sleep\n"));
	if (ac == 6 && !is_valid_num(av[5], 0))
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
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	return (res);
}
