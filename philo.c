#include "philo.h"

int	ft_isdigit(int ch)
{
	if ((ch > 47) && (ch < 58))
		return (1);
	return (0);
}

int	ft_isnum(char *str)
{
	int	flag;

	flag = 0;
	if (str[0] == '-')
	{
		flag = 1;
		str++;
	}
	while (*str != '\0')
	{
		if (ft_isdigit(*str))
			str++;
		else
			return (0);
	}
	return (1);
}

void	ft_validation(char **argv)
{
	int	i;
	int	j;
	int	num;
	int	counter;

	i = 1;
	while (argv[i])
	{
		j = 1;
		num = ft_atoi(argv[i]);
		counter = 0;
		while (argv[j])
		{
			if (num == ft_atoi(argv[j]))
				counter++;
			j++;
		}
		if (!ft_isnum(argv[i]) || counter  == 2)
		{
			write(1, "Error\n", 7);
			exit(0);
		}
		i++;
	}
}

void	take_a_fork(t_diner *diner,t_philo *philo)
{
	pthread_mutex_lock(philo->left_hand);
	pthread_mutex_lock(&diner->death);
	printf("[%lld ms philosopher № %d has taken a fork]\n",ft_get_time() - diner->start_time ,philo->id);
	pthread_mutex_unlock(&diner->death);
	pthread_mutex_lock(philo->right_hand);
	pthread_mutex_lock(&diner->death);
	printf("[%lld ms philosopher № %d has taken a fork]\n",ft_get_time() - diner->start_time ,philo->id);
	pthread_mutex_unlock(&diner->death);
}

// void	eating(t_philo *philo)
// {
	

// }

void	*philo_processing(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	printf("time time to eat %lld\n", ((t_diner *)philo->diner)->time_to_eat);
	while(1)
	{
		take_a_fork(philo->diner,philo);
		// eating(philo);
		usleep(400000);
	}
}
void	parsing(t_diner *diner,char **argv, int argc)
{
	diner->number_of_philos = ft_atoi(argv[1]);
	diner->time_to_die = ft_atoi(argv[2]);
	diner->time_to_eat = ft_atoi(argv[3]);
	diner->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		diner->lim_of_meals =  ft_atoi(argv[5]);
	else
		diner->lim_of_meals = 0;
}


void	forks_init(t_diner *diner, t_philo *philo)
{
	philo->left_hand = &diner->fork[philo->id];
	if (philo->id == diner->number_of_philos - 1)
		philo->right_hand = &diner->fork[0];
	else
		philo->right_hand = &diner->fork[philo->id + 1];
}
int	diner_init(t_diner *diner)
{
	int	i;

	i = 0;
	diner->thread = (pthread_t *)malloc(sizeof(pthread_t) * diner->number_of_philos);
	diner->philo = (t_philo *)malloc(sizeof(t_philo) * diner->number_of_philos);
	diner->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * diner->number_of_philos);
	diner->start_time = ft_get_time();
	while (i < diner->number_of_philos)
	{
		diner->philo[i].id = i;
		diner->philo[i].diner = diner;
		diner->philo[i].meal_time = 1; 
		forks_init(diner,&diner->philo[i]);
		pthread_mutex_init(&diner->fork[i], NULL);
		usleep(100);
		i++;
	}
	pthread_mutex_init(&diner->death, NULL);
	return (1);
}

void	ft_checker(t_diner *diner)
{
	int	i;

	i = 0;
	while (1)
	{
		usleep(diner->time_to_die);
		if (philo_may_die(diner,&diner->philo[i]))
			exit(0);
		i++;
		if (i == diner->number_of_philos)
			i = 0;
	}
}

int	main(int argc, char** argv)
{
	t_diner *diner;
	int		flag;
	if (argc != 5 && argc != 6)
	{
		write(1, "Error\n", 7);
		exit(0);
	}
	ft_validation(argv);
	diner = malloc(sizeof(t_diner));
	parsing(diner,argv,argc);
	flag = diner_init(diner);
	usleep(100);
	int i = 0;
	while(i < diner->number_of_philos)
	{
		pthread_create(&diner->thread[i],NULL,philo_processing,(void *)(&diner->philo[i]));
		pthread_detach(diner->thread[i]);
		usleep(100);
		printf(" I %d\n", i);
		i++;
	}
	
	printf(" num %d die %lld eat %lld sleep %lld count %d\n", diner->number_of_philos,diner->time_to_die,diner->time_to_eat,diner->time_to_sleep, (argc == 6)?diner->lim_of_meals:0);
	ft_checker(diner);
	return (0);
}