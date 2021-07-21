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

void* helloWorld(void *args)
{
	int i = (int)args;
	while(1)
	{
		printf("Im working %d\n", i);
		usleep(i * 400000);
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
}

int	main(int argc, char** argv)
{
	t_diner *diner;

	if (argc != 5 && argc != 6)
	{
		write(1,"Error\n",7);
		exit(0);
	}
	ft_validation(argv);
	diner = malloc(sizeof(t_diner));
	parsing(diner,argv,argc);
	printf(" num %d die %d eat %d sleep %d count %d\n", diner->number_of_philos,diner->time_to_die,diner->time_to_eat,diner->time_to_sleep, (argc == 6)?diner->lim_of_meals:0);
	return (0);
}