/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:25:25 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/13 12:09:21 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static t_data	ft_lauch_init(void)
{
	t_data data;
	
	data.env = NULL;
	data.argc = -1;
	data.argv = NULL;
	data.fd_input = -1;
	data.fd_output = -1;
	data.num_cmds = -1;
	data.pipe = NULL;
	data.pids = NULL;
	data.child = -1;
	data.cmd_path = NULL;
	data.cmds = NULL;
	data.heredoc = 0;
	return (data);
}

static void	 ft_generate_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_cmds - 1)
	{
		if(pipe(data->pipe + 2 * i) == -1)
			ft_error("Could not create pipe");
		i++;
	}
} 

void	ft_close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->num_cmds - 1) * 2)
	{
		close(data->pipe[i]);
		i++;
	}
}

t_data	init(int argc, char **argv, char **envp)
{
	t_data data;
	
	data = ft_lauch_init();//inicializar los valores de la struct
	data.env = envp;
	data.argc = argc;
	data.argv = argv;
	//printf("entra aqui");
	ft_get_fd_input(&data); //fd_input asociar la entrada
	ft_get_fd_output(&data); //fd_output asociar la salida
	data.num_cmds = argc - 3 - data.heredoc;
	data.pipe = malloc(sizeof(int) * 2 * (data.num_cmds - 1));  //malloc for fd[2]
	if(!data.pipe)
		ft_error("Pipe error");
	data.pids = malloc(sizeof(int) * data.num_cmds);
	if(!data.pipe)
		ft_error("Pips error");
	ft_generate_pipes(&data);
	return (data);
}