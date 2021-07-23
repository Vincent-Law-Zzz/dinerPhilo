#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define MISSING -1
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define FINISH 0

typedef struct s_philo
{
	void			*diner;
	pthread_mutex_t	*left_hand;
	pthread_mutex_t	*right_hand;
	int				status;
	long long		meal_time;
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

long long	ft_get_time();
int			philo_may_die(t_diner *diner,t_philo *philo);
int			ft_atoi(const char *str);
void		pthread_inits(t_diner *diner);
int			diner_init(t_diner *diner);
void		forks_init(t_diner *diner, t_philo *philo);
void		parsing(t_diner *diner,char **argv, int argc);
void		*philo_processing(void *args);
void		ft_usleep(useconds_t time);
int			ft_validation(char **argv);
int			ft_free(t_diner *diner);
void		fork_free(pthread_mutex_t *fork, int num);
int			ft_isnum(char *str);


#endif