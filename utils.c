/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:13:36 by vmusaely          #+#    #+#             */
/*   Updated: 2021/09/05 14:13:39 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_exit(char *s)
{
	printf("%s\n", s);
	return (-1);
}

int		ft_is_digit(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void    ft_print_status(t_philo *philosopher, char *message)
{
    pthread_mutex_lock(&philosopher->data->write_m);
    printf("%lld %d %s\n", (ft_get_time() - philosopher->data->start), philosopher->index, message);
    if (*message != 'd')
        pthread_mutex_unlock(&philosopher->data->write_m);
}

void     ft_clear(t_data *data)
{
	int	i;

	if (data->forks_m)
	{
		i = 0;
		while (i < data->count)
			pthread_mutex_destroy(&data->forks_m[i++]);
		if (data->forks_m)
			free(data->forks_m);
	}
	if (data->philosophers)
	{
		i = 0;
		while (i < data->count)
			pthread_mutex_destroy(&data->philosophers[i++].mutex);
		if (data->philosophers)
			free(data->philosophers);
	}
	pthread_mutex_destroy(&data->write_m);
	pthread_mutex_destroy(&data->is_dead);
    free(data);
	// printf("check\n");
}

long long	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}
