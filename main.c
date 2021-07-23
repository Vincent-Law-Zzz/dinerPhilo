#include "philo.h"

void	ft_checker(t_diner *diner)
{
	int	i;
	int	e;
	int	counter;

	i = 0;
	e = 1;
	counter = 0;
	while (e)
	{
		if (diner->lim_of_meals != -1 && diner->philo[i].status == FINISH)
			counter++;
		if (diner->lim_of_meals == 0 || counter == diner->number_of_philos)
			e = 0;
		if (philo_may_die(diner, &diner->philo[i]))
			break ;
		i++;
		if (i == diner->number_of_philos)
		{
			i = 0;
			counter = 0;
		}
	}
}

void	pthread_inits(t_diner *diner)
{
	int	i;

	i = 0;
	while (i < diner->number_of_philos)
	{
		pthread_create(&diner->thread[i], NULL, philo_processing, \
			(void *)(&diner->philo[i]));
		pthread_detach(diner->thread[i]);
		usleep(50);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_diner	*diner;
	int		flag;

	if ((argc != 5 && argc != 6) || ft_atoi(argv[1]) == 0 \
		|| ft_validation(argv) == 1)
	{
		write(1, "Error\n", 7);
		return (0);
	}
	diner = malloc(sizeof(t_diner));
	parsing(diner, argv, argc);
	flag = diner_init(diner);
	if (!flag)
		return (0);
	pthread_inits(diner);
	ft_checker(diner);
	ft_free(diner);
	return (0);
}
