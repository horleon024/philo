#include "philo.h"

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_write_return(const char *str, t_state *state)
{
	free(state);
	write(STDERR_FILENO, str, ft_strlen(str));
	return (1);
}

int	ft_print_error(t_state *state)
{
	int	i;

	if (state->error == 2)
		return (ft_write_return(ARGSERROR, state));
	else if (state->error == 3)
		return (ft_write_return(MALOCERROR, state));
	else if (state->error == 4)
	{
		free(state->philo);
		return (ft_write_return(MALOCERROR, state));
	}
	else if (state->error == 5)
	{
		free(state->philo);
		i = 0;
		while (i < state->nb_of_philo)
		{
			free(state->forks[i]);
			pthread_mutex_destroy(state->forks[i]);
			i++;
		}
		free(state->forks);
		return (ft_write_return(MALOCERROR, state));
	}
	return (1);
}
