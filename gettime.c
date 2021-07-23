
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
	long long time;

	time = ft_get_time();
	current_time = time - diner->start_time - philo->meal_time;
	// printf( "%lld , %lld id %d\n",current_time, diner->time_to_die, philo->id);
	if (!diner->start_time || !diner->time_to_die)
		printf("EMPTY\n");
	if (current_time > diner->time_to_die)
	{
		// if (current_time > diner->time_to_die)
		// {
			pthread_mutex_lock(&diner->death);
			printf("[%lld ms philosopher № %d is deeeeeeeeeeeeeeeeeeeeeeeeeeead :(]\n",time - diner->start_time ,philo->id);
			// pthread_mutex_lock(&diner->death);
			exit(0);
		// }
	}
	return (0);
}
