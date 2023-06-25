/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otelliq <otelliq@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 00:46:23 by otelliq           #+#    #+#             */
/*   Updated: 2023/06/24 23:15:56 by otelliq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	meals(t_phil *philos)
{
	int	i;

	i = 0;
	while (i < philos->philo_n)
	{
		pthread_mutex_lock(&(philos->data));
		if (philos->phil[i].eaten < philos->nb_time_eat)
		{	
			pthread_mutex_unlock(&(philos->data));
			return (0);
		}
		pthread_mutex_unlock(&(philos->data));
		i++;
	}
	pthread_mutex_lock(&(philos->death));
	philos->died = 1;
	pthread_mutex_unlock(&(philos->death));
	return (1);
}

int	in_while(t_phil *philos)
{
	int		i;
	long	time;

	i = 0;
	time = timesamp() - philos->first_time;
	while (i < philos->philo_n)
	{
		pthread_mutex_lock(&(philos->data));
		if (timesamp() - philos->phil[i].last_meal > philos->t_die)
		{
			pthread_mutex_unlock(&(philos->data));
			pthread_mutex_lock(&(philos->death));
			philos->died = 1;
			pthread_mutex_unlock(&(philos->death));
			pthread_mutex_lock(&philos->death);
			printf("%ld %d died\n", time, philos->phil[i].id);
			pthread_mutex_unlock(&philos->death);
			return (1);
		}
		pthread_mutex_unlock(&(philos->data));
		i++;
	}
	return (0);
}

void	*checkdeath_meals(void *arg)
{
	t_phil	*philos;

	philos = (t_phil *)arg;
	while (1)
	{
		if (philos->nb_time_eat != 0 && meals(philos))
		{
			pthread_mutex_unlock(&(philos->data));
			return (NULL);
		}
		if (in_while(philos))
			return (NULL);
	}
	return (NULL);
}

void	routine_help(t_m_s *philo)
{
	myprintf("is thinking", philo);
	pthread_mutex_lock(&philo->arg->fork[philo->r_fork]);
	myprintf("has taken a fork", philo);
	pthread_mutex_lock(&philo->arg->fork[philo->l_fork]);
	myprintf("has taken a fork", philo);
	myprintf("is eating", philo);
	pthread_mutex_lock(&(philo->arg->data));
	philo->last_meal = timesamp();
	pthread_mutex_unlock(&(philo->arg->data));
	delay(philo, philo->arg->t_eat);
	pthread_mutex_lock(&(philo->arg->data));
	philo->eaten++;
	pthread_mutex_unlock(&(philo->arg->data));
	pthread_mutex_unlock(&philo->arg->fork[philo->r_fork]);
	pthread_mutex_unlock(&philo->arg->fork[philo->l_fork]);
	myprintf("is sleeping", philo);
	delay(philo, philo->arg->t_sleep);
}
