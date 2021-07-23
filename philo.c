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

int	ft_validation(char **argv)
{
	int	i;
	int num;

	i = 1;
	num = 0;
	while (argv[i])
	{
		num = ft_atoi(argv[i]);
		if (!ft_isnum(argv[i])|| num < 0)
		{
			write(1, "Error\n", 7);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_usleep(useconds_t time)
{
	unsigned long long	t;
	t = ft_get_time();
	while (ft_get_time() - t < time)
		usleep(50);
}

void	take_a_fork(t_diner *diner, t_philo *philo)
{
	pthread_mutex_lock(philo->left_hand);
	pthread_mutex_lock(&diner->death);
	printf("[%lld ms philosopher № %d has taken a fork]\n",ft_get_time() - diner->start_time ,philo->id + 1);
	pthread_mutex_unlock(&diner->death);
	pthread_mutex_lock(philo->right_hand);
	pthread_mutex_lock(&diner->death);
	printf("[%lld ms philosopher № %d has taken a fork]\n",ft_get_time() - diner->start_time ,philo->id + 1);
	pthread_mutex_unlock(&diner->death);
}

void	eating(t_diner *diner, t_philo *philo)
{
	philo->status = EATING;
	if (diner->lim_of_meals == philo->count_of_meals)
	{
		philo->status = FINISH;
		return ;
	}
	pthread_mutex_lock(&diner->death);
	printf("[%lld ms philosopher № %d is eating]\n",ft_get_time() - diner->start_time,philo->id + 1);
	pthread_mutex_unlock(&diner->death);
	ft_usleep(diner->time_to_eat);
	philo->meal_time = ft_get_time() - diner->start_time + diner->time_to_eat;
	pthread_mutex_unlock(philo->right_hand);
	pthread_mutex_unlock(philo->left_hand);
	if (diner->lim_of_meals && philo->count_of_meals < diner->lim_of_meals)
		philo->count_of_meals = philo->count_of_meals + 1;
	if (diner->lim_of_meals == philo->count_of_meals)
	{
		philo->status = FINISH;
		return ;
	}
}

void	sleeping(t_diner *diner, t_philo *philo)
{
	philo->status = SLEEPING;
	pthread_mutex_lock(&diner->death);
	printf("[%lld ms philosopher № %d is sleeping]\n",ft_get_time() - diner->start_time ,philo->id + 1);
	pthread_mutex_unlock(&diner->death);
	ft_usleep(diner->time_to_sleep);
}

void	thinking(t_diner *diner, t_philo *philo)
{
	long long time;

	philo->status = THINKING;
	pthread_mutex_lock(&diner->death);
	time = ft_get_time() - diner->start_time;
	printf("[%lld ms philosopher № %d is thinking]\n",time ,philo->id + 1);
	pthread_mutex_unlock(&diner->death);
}

void	*philo_processing(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	while(1)
	{
		take_a_fork(philo->diner,philo);
		eating(philo->diner, philo);
		if (philo->status == FINISH)
			break ;
		sleeping(philo->diner,philo);
		thinking(philo->diner,philo);
	}
	return (NULL);
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
		diner->lim_of_meals = -1;
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
		diner->philo[i].count_of_meals = 0;
		forks_init(diner,&diner->philo[i]);
		pthread_mutex_init(&diner->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&diner->death, NULL);
	return (1);
}

void	ft_checker(t_diner *diner)
{
	int	i;
	int e;
	int counter;

	i = 0;
	e = 1;
	counter = 0;
	while (e)
	{
		if (philo_may_die(diner,&diner->philo[i]))
			exit(0);
		i++;
		if ( diner->lim_of_meals != -1 && diner->philo[i].status == FINISH)
			counter++;
		if (diner->lim_of_meals == 0 || counter == diner->number_of_philos)
			e = 0;
		if (i == diner->number_of_philos)
		{
			i = 0;
			counter = 0;
		}
	}
}

int	main(int argc, char** argv)
{
	t_diner *diner;
	int		flag;
	if (ft_atoi(argv[1]) == 0 || (argc != 5 && argc != 6) || ft_validation(argv) == 1)
	{
		write(1, "Error\n", 7);
		exit(0);
	}
	diner = malloc(sizeof(t_diner));
	parsing(diner,argv,argc);
	flag = diner_init(diner);
	int i = 0;
	while(i < diner->number_of_philos)
	{
		pthread_create(&diner->thread[i],NULL,philo_processing,(void *)(&diner->philo[i]));
		pthread_detach(diner->thread[i]);
		usleep(50);
		i++;
	}
	ft_checker(diner);
	return (0);
}