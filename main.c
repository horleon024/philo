/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:01:53 by lhorefto          #+#    #+#             */
/*   Updated: 2021/07/24 12:02:16 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_check_death(t_state *state)
{
	int	i;
	int	j;

	while (1)
	{
		i = 0;
		j = 0;
		while (i < state->nb_of_philo)
		{
			if (!state->philo[i]->eaten)
				j++;
			if (j == state->nb_of_philo)
				return ;
			if (!ft_is_alive(state->philo[i]))
			{
				pthread_mutex_lock(&state->philo[i]->mutex);
				ft_print_action(state->philo[i], "died", 1);
				return ;
			}
			i++;
		}
	}
}

static void	ft_free_and_destroy(t_state *state, int j)
{
	int	i;

	i = 0;
	while (i < state->nb_of_philo)
	{
		pthread_mutex_destroy(state->forks[i]);
		if (i < j - 1 || j == state->nb_of_philo)
			pthread_mutex_destroy(&state->philo[i]->mutex);
		free(state->forks[i]);
		if (i < j)
			free(state->philo[i]);
		i++;
	}
	pthread_mutex_destroy(&state->std_out);
	free(state->forks);
	free(state->philo);
	free(state);
}

int	main(int argc, char **argv)
{
	t_state	*state;
	int		ret;

	state = (t_state *)malloc(sizeof(t_state));
	if (!state)
		return (1);
	ft_init_state(argc, argv, state);
	if (state->error)
		return (ft_print_error(state));
	pthread_mutex_init(&state->std_out, NULL);
	ret = ft_init_philos(state);
	if (ret)
	{
		ft_free_and_destroy(state, ret);
		return (1);
	}
	ft_check_death(state);
	ft_free_and_destroy(state, state->nb_of_philo);
	return (0);
}
