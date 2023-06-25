/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otelliq <otelliq@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:59:57 by otelliq           #+#    #+#             */
/*   Updated: 2023/06/24 23:22:20 by otelliq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	delay(t_m_s *s, int n)
{
	long	x;

	(void) s;
	x = timesamp();
	while ((timesamp() - x) <= n)
	{
		usleep(100);
	}
}

void	*routine(void *hh)
{
	t_m_s	*philo;

	philo = (t_m_s *) hh;
	if (philo->arg->philo_n == 1)
	{
		myprintf("is thinking", philo);
		myprintf("has taken a fork", philo);
		delay(philo, philo->arg->t_die);
		return (NULL);
	}
	while (!ft_death(philo))
	{
		routine_help(philo);
	}
	return (NULL);
}

void	fill_phil(t_phil *s)
{
	int	i;

	i = 0;
	while (i < s->philo_n)
	{
		s->phil[i].id = i + 1;
		s->phil[i].eaten = 0;
		s->phil[i].r_fork = i;
		s->phil[i].l_fork = (i + 1) % s->philo_n;
		s->phil[i].arg = s;
		s->phil[i].last_meal = timesamp();
		i++;
	}
}

int	main(int ac, char **av)
{
	int			i;
	t_phil		*s;
	pthread_t	check;

	s = malloc(sizeof(t_phil));
	if (ft_init(ac, av, s))
		return (free (s), 1);
	s->first_time = timesamp();
	fill_phil(s);
	i = 0;
	while (i < s->philo_n)
		pthread_mutex_init(&s->fork[i++], NULL);
	i = 0;
	while (i < s->philo_n)
	{
		pthread_create(&s->threads[i], NULL, routine, (void *)&s->phil[i]);
		usleep(50);
		i++;
	}
	pthread_create(&check, NULL, checkdeath_meals, s);
	t_join(s, s->threads);
	mutex_destroy(s, s->threads);
	pthread_detach(check);
}

void	t_join(t_phil *s, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < s->philo_n)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
