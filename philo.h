/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 14:13:28 by vmusaely          #+#    #+#             */
/*   Updated: 2021/09/05 14:13:31 by vmusaely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

struct          s_data;

typedef struct  s_philo
{
	int             index;
	long long       last_eat;
	int             lfork;
	int	            rfork;
	int             eat_count;
	struct s_data	*data;
	pthread_mutex_t mutex;
}               t_philo;


typedef struct  s_data
{
	int         count;
	int	        time_to_die;
	int         time_to_eat;
	int         time_to_sleep;
	int	        must_eat;
	int         end;
	long long   start;

	t_philo	*philosophers;
	pthread_mutex_t *forks_m;
	pthread_mutex_t write_m;
	pthread_mutex_t is_dead;

}               t_data;


int		    ft_exit(char *s);
int         ft_init(t_data *data, int argc, char **argv);
int		    ft_is_digit(char *s);
int	        ft_atoi(char *str);
long long	ft_get_time(void);
void        ft_print_status(t_philo *philosopher, char *message);
void     	ft_clear(t_data *data);

#endif
