#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# define ARGSERROR "Error with the arguments"
# define MALOCERROR "Error during allocating memory"

typedef struct s_philo
{
	pthread_mutex_t	mutex;
	int				id;
	int				eaten;
	double			deathtime;
	pthread_t		thread;
	struct s_state	*state;
}					t_philo;

typedef struct s_state
{
	struct timeval			start;
	int						nb_of_philo;
	int						t_to_die;
	int						t_to_eat;
	int						t_to_sleep;
	int						nb_to_eat;
	int						error;
	pthread_mutex_t			std_out;
	pthread_mutex_t			**forks;
	t_philo					**philo;
}							t_state;

int		ft_print_error(t_state *state);
int		ft_atoi(const char *str);
double	ft_get_time(t_state *state);
void	ft_print_action(t_philo *philo, char *str, int dead);
void	ft_init_state(int argc, char **argv, t_state *state);
void	ft_init_philos(t_state *state);
int		ft_is_alive(t_philo *philo);
void	*ft_simulate(void *arg);

#endif