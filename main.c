/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:13:11 by vmusaely          #+#    #+#             */
/*   Updated: 2021/09/05 14:13:13 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *ft_is_dead(void *philo)
{
	t_philo *p;
	long long time;

	p = (t_philo *)philo;
	while (1 && p->eat_count != p->data->must_eat)
	{
		pthread_mutex_lock(&p->mutex);
		time = ft_get_time() - p->last_eat;
		if ((time > p->data->time_to_die))
		{
			ft_print_status(p, "died");
			ft_clear(p->data);
			pthread_mutex_unlock(&p->data->is_dead);
			return ((void *)0);
		}
		usleep(1000);
		pthread_mutex_unlock(&p->mutex);
	}
	return (NULL);
}

void    ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_m[philo->lfork]);
	pthread_mutex_lock(&philo->data->forks_m[philo->rfork]);
	philo->last_eat = ft_get_time();
	ft_print_status(philo, "has taken a fork");
	ft_print_status(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->forks_m[philo->lfork]);
	pthread_mutex_unlock(&philo->data->forks_m[philo->rfork]);
}

void    ft_sleep_and_think(t_philo *philo)
{
	ft_print_status(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
	ft_print_status(philo, "is thinking");
}

void    *ft_routine(void *philo)
{
	pthread_t	tid;
	t_philo *philosopher;

	philosopher = (t_philo *)philo;
	if (pthread_create(&tid, NULL, &ft_is_dead, philo))
		return ((void *)1);
	pthread_detach(tid);
	while (1 && philosopher->eat_count != philosopher->data->must_eat)
	{
		ft_eat(philosopher);
		ft_sleep_and_think(philosopher);
		if (philosopher->eat_count == philosopher->data->must_eat)
			philosopher->data->end++;
	}
	if (philosopher->data->end == philosopher->data->count)
	{
		printf("Everyone ate enough\n");
		ft_clear(philosopher->data);
		pthread_mutex_unlock(&philosopher->data->is_dead);
	}
	return ((void *)0);
}

int     ft_create_threads(t_data *data)
{
	int         i;
	t_philo     *ph;
	pthread_t   tid;

	i = 0;
	ph = data->philosophers;
	ph->data->start = ft_get_time();
	while (i < data->count)
	{
		ph[i].last_eat = ft_get_time();
		if (pthread_create(&tid, NULL, &ft_routine, &(ph[i])))
			return (1);
		pthread_detach(tid);
		i++;
	}
	return (0);
}

int	    main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (ft_exit("Error: invalid arguments"));
	if (ft_atoi(argv[1]) == 1)
	{
		printf("0 1 dead\n");
		return (0);
	}
	if (!(data = malloc(sizeof(t_data))))
		return (ft_exit("Error"));
	if (ft_init(data, argc, argv))
	{
		ft_clear(data);
		return (ft_exit("Error"));
	}
	if (ft_create_threads(data))
	{
		ft_clear(data);
		return (ft_exit("Error"));
	}
	pthread_mutex_lock(&(data->is_dead));
	// ft_clear(data);
	return (0);
}
