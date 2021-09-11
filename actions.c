/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:00:57 by lhorefto          #+#    #+#             */
/*   Updated: 2021/07/24 11:45:31 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	if (ft_is_alive(philo))
	{
		ft_print_action(philo, "is sleeping", 0);
		if (philo->state->t_to_die < philo->state->t_to_eat
			+ philo->state->t_to_sleep)
			usleep((philo->state->t_to_die - philo->state->t_to_eat) * 1000);
		else
			usleep(philo->state->t_to_sleep * 1000);
	}
	pthread_mutex_unlock(&philo->mutex);
}

static void	ft_eat(t_philo *philo)
{
	int	i;

	i = philo->state->nb_of_philo;
	pthread_mutex_lock(philo->state->forks[philo->id]);
	ft_print_action(philo, "has taken a fork", 0);
	pthread_mutex_lock(philo->state->forks[(philo->id + 1) % i]);
	ft_print_action(philo, "has taken a fork", 0);
	pthread_mutex_lock(&philo->mutex);
	ft_print_action(philo, "is eating", 0);
	philo->deathtime = ft_get_time(philo->state) + philo->state->t_to_die;
	if (philo->state->t_to_die < philo->state->t_to_eat)
		usleep(philo->state->t_to_die * 1000);
	else
		usleep(philo->state->t_to_eat * 1000);
	philo->eaten -= 1;
	pthread_mutex_unlock(philo->state->forks[philo->id]);
	pthread_mutex_unlock(philo->state->forks[(philo->id + 1) % i]);
	pthread_mutex_unlock(&philo->mutex);
}

void	*ft_simulate(void *arg)
{
	t_philo	**philo;

	philo = arg;
	while ((*philo)->eaten != 0)
	{
		ft_print_action(*philo, "is thinking", 0);
		ft_eat(*philo);
		if ((*philo)->eaten)
			ft_sleep(*philo);
	}
	(*philo)->deathtime = -1;
	return (philo);
}
