#include "philo.h"

static int	ft_atoi_args(int argc, char **argv, t_state *state)
{
	if (argc < 5 || argc > 6)
		return (1);
	state->nb_of_philo = ft_atoi(argv[1]);
	state->t_to_die = ft_atoi(argv[2]);
	state->t_to_eat = ft_atoi(argv[3]);
	state->t_to_sleep = ft_atoi(argv[4]);
	if (argc < 6)
		state->nb_to_eat = -1;
	else
		state->nb_to_eat = ft_atoi(argv[5]);
	if (state->nb_of_philo < 1 || state->t_to_die == -2
		|| state->t_to_eat == -2 || state->t_to_sleep == -2
		|| state->nb_to_eat == -2)
		return (1);
	return (0);
}

static int	ft_init_forks(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->nb_of_philo)
	{
		state->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!state->forks[i])
			return (1);
		pthread_mutex_init(state->forks[i], NULL);
		i++;
	}
	return (0);
}

void	ft_init_state(int argc, char **argv, t_state *state)
{
	state->error = 0;
	if (ft_atoi_args(argc, argv, state))
	{	
		state->error = 2;
		return ;
	}
	gettimeofday(&state->start, NULL);
	state->philo = (t_philo **)malloc(state->nb_of_philo * sizeof(t_philo *));
	if (!state->philo)
	{
		state->error = 3;
		return ;
	}
	state->forks = (pthread_mutex_t **)malloc(state->nb_of_philo
			* sizeof(pthread_mutex_t *));
	if (!state->forks)
	{
		state->error = 4;
		return ;
	}
	if (ft_init_forks(state))
	{
		state->error = 5;
		return ;
	}
}

int	ft_init_philos(t_state *state)
{
	int				i;

	i = 0;
	while (i < state->nb_of_philo)
	{
		state->philo[i] = malloc(sizeof(t_philo));
		if (!state->philo[i])
			return (i);
		state->philo[i]->id = i;
		state->philo[i]->eaten = state->nb_to_eat;
		state->philo[i]->state = state;
		state->philo[i]->deathtime = ft_get_time(state) + state->t_to_die;
		pthread_mutex_init(&state->philo[i]->mutex, NULL);
		pthread_create(&state->philo[i]->thread, NULL,
			ft_simulate, &state->philo[i]);
		usleep(1000);
		i++;
	}
	return (0);
}
