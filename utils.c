
#include "philo.h"

int	ft_atoi(const char *str)
{
	long long	max;
	int			isneg;
	long long	res;

	res = 0;
	isneg = 1;
	max = 0;
	while (((*str >= 9) && (*str <= 13)) || (*str == 32))
		str++;
	if ((*str == '-') || (*str == '+'))
		if (*str++ == '-')
			isneg = -1;
	while ((*str >= '0') && (*str <= '9'))
	{
		res = res * 10 + (*str - '0');
		str++;
		if ((max > res) && (isneg == 1))
			return (-1);
		if ((max > res) && (isneg == -1))
			return (0);
		max = res;
	}
	return (res * isneg);
}

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

void	ft_usleep(useconds_t time)
{
	unsigned long long	t;
	t = ft_get_time();
	while (ft_get_time() - t < time)
		usleep(50);
}
