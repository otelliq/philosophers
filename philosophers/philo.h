/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otelliq <otelliq@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:58:52 by otelliq           #+#    #+#             */
/*   Updated: 2023/06/25 00:16:12 by otelliq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include<pthread.h>
# include<sys/time.h>

typedef struct s_m_s
{
	struct s_phil	*arg;
	long			last_meal;
	int				id;
	int				eaten;
	int				l_fork;
	int				r_fork;
	int				meals;
}t_m_s;

typedef struct s_phil
{
	t_m_s			*phil;
	pthread_t		*threads;
	int				died;
	int				philo_n;
	int				t_die;
	int				nb_time_eat;
	int				t_eat;
	int				t_sleep;
	int				r_fork;
	int				l_fork;
	int				flag;
	long			first_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	data;
	pthread_mutex_t	flag_d;
}t_phil;

long	int		timesamp(void);
void		myprintf(char *s, t_m_s *t);
void		mutex_destroy(t_phil *s, pthread_t *threads);
void		t_join(t_phil *s, pthread_t *threads);
int			ft_death(t_m_s *ph);
int			ft_atoi(char *str);
int			check_meals(t_m_s *s);
void		*checkdeath_meals(void *arg);
void		routine_help(t_m_s *philo);
void		delay(t_m_s *s, int n);
int			ft_init(int ac, char **av, t_phil *s);
#endif