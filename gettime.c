
#include "philo.h"

long long ft_get_time()
{
	struct timeval	current_time;
	long long		res;

	gettimeofday(&current_time, NULL);
	res = current_time.tv_sec * 1000 + current_time.tv_usec/1000;
	return (res);
}

int	philo_may_die(t_diner *diner,t_philo *philo)
{
	long long current_time;

	current_time = ft_get_time() - diner->start_time - philo->meal_time;
	// printf( "%lld , %lld \n",current_time, diner->time_to_die);
	if (!diner->start_time || !diner->time_to_die)
		printf("EMPTY\n");
	if (current_time && diner->time_to_die && current_time > diner->time_to_die )
	{
		write(1,"DEAD\n",5);
		exit(0);
	}
	return (0);
}
