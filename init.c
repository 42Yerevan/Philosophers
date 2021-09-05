/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:13:19 by vmusaely          #+#    #+#             */
/*   Updated: 2021/09/05 14:13:21 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_init_philos(t_data *data)
{
    int i;

    i = 0;
    while (i < data->count)
    {
        data->philosophers[i].index = i + 1;
        data->philosophers[i].lfork = i;
        data->philosophers[i].rfork = (i + 1) % data->count;
        data->philosophers[i].eat_count = 0;
        data->philosophers[i].data = data;
        pthread_mutex_init(&data->philosophers[i].mutex, NULL);
        i++;
    }
}

int     ft_init_mutexes(t_data *data)
{
    int i;

    i = 0;
    if (!(data->forks_m = malloc(sizeof(pthread_mutex_t) * data->count)))
        return (1);
    while (i < data->count)
    {
        pthread_mutex_init(&data->forks_m[i], NULL);
        i++;
    }
    pthread_mutex_init(&data->write_m, NULL);
    pthread_mutex_init(&data->is_dead, NULL);
    pthread_mutex_lock(&data->is_dead);
    return (0);
}

int     ft_init(t_data *data, int argc, char **argv)
{
    int i;

	i = 1;
    data->philosophers = NULL;
    data->forks_m = NULL;
	while (i < argc)
	{
		if (ft_is_digit(argv[i]) || ft_atoi(argv[i]) > 2147483647)
			return (1);
		i++;
	}
    data->end = 0;
	data->count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (i == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
    data->philosophers = malloc(sizeof(t_philo) * data->count);
    if (!(data->philosophers))
        return (1);    
    ft_init_philos(data);
	return (ft_init_mutexes(data));
}
