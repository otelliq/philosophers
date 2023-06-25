/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otelliq <otelliq@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:53:08 by otelliq           #+#    #+#             */
/*   Updated: 2023/06/24 23:37:56 by otelliq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i++] - '0');
		if (res == 2147483648 && sign == -1)
			return (res * sign);
		else if (res > 2147483647)
			return (0);
	}
	return (res * sign);
}

long int	timesamp(void)
{
	struct timeval	time;

	gettimeofday (&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	mutex_destroy(t_phil *s, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < s->philo_n)
	{
		pthread_mutex_destroy(&s->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&(s->death));
	pthread_mutex_destroy(&(s->print));
	pthread_mutex_destroy(&(s->data));
	pthread_mutex_destroy(&(s->flag_d));
	free(s->phil);
	free(s->fork);
	free(threads);
	free(s);
}

int	ft_death(t_m_s *ph)
{
	int	died;

	pthread_mutex_lock(&(ph->arg->death));
	died = ph->arg->died;
	pthread_mutex_unlock(&(ph->arg->death));
	return (died);
}

void	myprintf(char *s, t_m_s *t)
{
	pthread_mutex_lock(&(t->arg->death));
	if (!t->arg->died)
	{
		pthread_mutex_unlock(&(t->arg->death));
		pthread_mutex_lock(&t->arg->print);
		printf("%ld %d %s\n", timesamp() - t->arg->first_time, t->id, s);
		pthread_mutex_unlock(&t->arg->print);
	}
	else
		pthread_mutex_unlock(&(t->arg->death));
}
