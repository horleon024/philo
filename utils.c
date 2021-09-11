#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-2);
		nb *= 10;
		nb += str[i] - '0';
		i++;
	}
	return (nb);
}

void	ft_print_action(t_philo *philo, char *str, int dead)
{
	double			time;

	pthread_mutex_lock(&philo->state->std_out);
	time = ft_get_time(philo->state);
	printf("%.0f %d %s\n", time, philo->id + 1, str);
	if (!dead)
		pthread_mutex_unlock(&philo->state->std_out);
}

double	ft_get_time(t_state *state)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((double)(current.tv_usec - state->start.tv_usec) / 1000
		+ ((double)(current.tv_sec - state->start.tv_sec)) * 1000);
}

int	ft_is_alive(t_philo *philo)
{
	if (philo->deathtime == -1)
		return (1);
	if (philo->deathtime <= ft_get_time(philo->state))
		return (0);
	return (1);
}
