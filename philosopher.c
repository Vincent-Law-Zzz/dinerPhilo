
#include "philo.h"

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