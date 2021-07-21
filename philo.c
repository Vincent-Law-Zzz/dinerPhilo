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
		usleep(200);
	}
}

int	main(int argc, char** argv)
{
	if (argc != 5 && argc != 6)
		write(1,"Error\n",7);
	ft_validation(argv);

	pthread_t thread;
	// pthread_t thread2;
    int status;
    // int status2;
	
    status = pthread_create(&thread, NULL, helloWorld, (void*)(1));
	status = pthread_create(&thread, NULL, helloWorld, (void*)(2));
	status = pthread_create(&thread, NULL, helloWorld, (void*)(3));
	status = pthread_create(&thread, NULL, helloWorld, (void*)(4));
	status = pthread_create(&thread, NULL, helloWorld, (void*)(5));
	status = pthread_create(&thread, NULL, helloWorld, (void*)(6));
	status = pthread_create(&thread, NULL, helloWorld, (void*)(7));
	// status = pthread_create(&thread, NULL, helloWorld2, NULL);
	status = pthread_join(thread, NULL);
	// status = pthread_create(&thread, NULL, helloWorld2, NULL);
	// status = pthread_join(thread, NULL);
	return (0);
}