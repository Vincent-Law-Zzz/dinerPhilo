#include "philo.h"

void	fork_free(pthread_mutex_t *fork, int num)
{
	int	i;

	i = 0;
	if (fork)
	{
		while (i < num)
		{
			pthread_mutex_destroy(&fork[i]);
			i++;
		}
	}
}

int	ft_free(t_diner *diner)
{
	if (diner->thread)
		free(diner->thread);
	if (diner->fork)
	{
		fork_free(diner->fork, diner->number_of_philos);
		free(diner->fork);
	}
	if (diner->philo)
		free(diner->philo);
	pthread_mutex_destroy(&diner->death);
	if (diner)
		free(diner);
	return (0);
}
