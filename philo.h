#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_mutex_t	*left_hand;
	pthread_mutex_t	*right_hand;
	pthread_t		*thread;
	int				meal_time;
	int				count_of_meals;
}	t_philo;

typedef struct s_diner
{
	t_philo			*philo;
	pthread_t		thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	stop;
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				start_time;
	int				current_time;
	int				lim_of_meals;
}	t_diner;

int	ft_atoi(const char *str);
#endif