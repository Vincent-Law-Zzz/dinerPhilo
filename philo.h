#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo
{
	void			*diner;
	pthread_mutex_t	*left_hand;
	pthread_mutex_t	*right_hand;
	// int				time_to_die;
	long long			meal_time;
	int				count_of_meals;
	int				id;
}	t_philo;

typedef struct s_diner
{
	t_philo			*philo;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	death;
	int				number_of_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	long long		current_time;
	int				lim_of_meals;
}	t_diner;

long long ft_get_time();
int	philo_may_die(t_diner *diner,t_philo *philo);
int	ft_atoi(const char *str);
#endif