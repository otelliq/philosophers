/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otelliq <otelliq@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 22:40:54 by otelliq           #+#    #+#             */
/*   Updated: 2023/06/24 23:31:13 by otelliq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fill(t_phil *s, char **av)
{
	s->philo_n = ft_atoi(av[1]);
	s->t_die = ft_atoi(av[2]);
	s->t_eat = ft_atoi(av[3]);
	s->t_sleep = ft_atoi(av[4]);
	if (s->philo_n <= 0 || s->t_eat <= 0 || s->t_die <= 0
		|| s->t_sleep <= 0)
		return (1);
	if (av[5])
	{
		s->nb_time_eat = ft_atoi(av[5]);
		if (s->nb_time_eat <= 0)
			return (1);
	}
	else
		s->nb_time_eat = 0;
	return (0);
}

int	ft_init(int ac, char **av, t_phil *s)
{
	if (ac == 5 || ac == 6)
	{
		if (fill(s, av))
			return (1);
		s->phil = malloc(sizeof(t_m_s) * s->philo_n);
		s->fork = malloc(sizeof(pthread_mutex_t) * s->philo_n);
		s->threads = malloc(sizeof(pthread_t) * s->philo_n);
		if (!s->fork || !s->phil || !s->threads)
			return (1);
		pthread_mutex_init(&(s->death), NULL);
		pthread_mutex_init(&(s->print), NULL);
		pthread_mutex_init(&(s->data), NULL);
		pthread_mutex_init(&(s->flag_d), NULL);
		s->flag = 0;
		s->died = 0;
	}
	return (0);
}
