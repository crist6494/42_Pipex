/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:22:08 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/13 12:12:06 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* void	ft_get_heredoc(t_data *data)
{
	int tmp_fd;
	int fd_input;
	char *line;

	
} */

void	ft_get_fd_input(t_data *data)
{
	//printf("entra aqui");
	data->fd_input = open(data->argv[1], O_RDONLY, 644);
	if(data->fd_input == -1)
	{
		printf("Hola\n");
		ft_error(data->argv[1]);
	}
}

void	ft_get_fd_output(t_data *data)
{
	data->fd_output = open(data->argv[data->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(data->fd_output == -1)
	{
		printf("Holaaaa\n");
		ft_error(data->argv[data->argc - 1]);
	}
}