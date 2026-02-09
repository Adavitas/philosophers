#include "philo.h"

void	precise_sleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(100);
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		write(2, "gettimeofday() error\n", 21);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
