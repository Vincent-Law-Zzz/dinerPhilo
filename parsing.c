#include "philo.h"

int	ft_validation(char **argv)
{
	int	i;
	int	num;

	i = 1;
	num = 0;
	while (argv[i])
	{
		num = ft_atoi(argv[i]);
		if (!ft_isnum(argv[i]) || num < 0)
		{
			write(1, "Error\n", 7);
			return (1);
		}
		i++;
	}
	return (0);
}

void	forks_init(t_diner *diner, t_philo *philo)
{
	philo->left_hand = &diner->fork[philo->id];
	if (philo->id == diner->number_of_philos - 1)
		philo->right_hand = &diner->fork[0];
	else
		philo->right_hand = &diner->fork[philo->id + 1];
}

void	parsing(t_diner *diner, char **argv, int argc)
{
	diner->number_of_philos = ft_atoi(argv[1]);
	diner->time_to_die = ft_atoi(argv[2]);
	diner->time_to_eat = ft_atoi(argv[3]);
	diner->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		diner->lim_of_meals = ft_atoi(argv[5]);
	else
		diner->lim_of_meals = -1;
}

int	diner_init(t_diner *diner)
{
	int	i;

	i = 0;
	diner->thread = (pthread_t *)malloc(sizeof(pthread_t) \
		* diner->number_of_philos);
	diner->philo = (t_philo *)malloc(sizeof(t_philo) \
		* diner->number_of_philos);
	diner->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* diner->number_of_philos);
	if (!diner->thread || !diner->philo || !diner->fork)
		return (ft_free(diner));
	diner->start_time = ft_get_time();
	while (i < diner->number_of_philos)
	{
		diner->philo[i].id = i;
		diner->philo[i].diner = diner;
		diner->philo[i].meal_time = 1;
		diner->philo[i].count_of_meals = 0;
		diner->philo[i].status = MISSING;
		forks_init(diner, &diner->philo[i]);
		pthread_mutex_init(&diner->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&diner->death, NULL);
	return (1);
}
