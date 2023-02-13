/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:17:17 by cmorales          #+#    #+#             */
/*   Updated: 2023/02/13 12:26:32 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_strs(char *str, char **strs)
{
	int	i;

	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	if (strs != NULL)
	{
		i = 0;
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
		strs = NULL;
	}
}


void	exit_error(int error_status, t_data *data)
{
	//printf("Entra aqui\n");
	if (data)
	{
		ft_close_pipes(data);
		if (data->pipe != NULL)
			free(data->pipe);
		if (data->pids != NULL)
			free(data->pids);
		if (data->cmds != NULL || data->cmd_path != NULL)
			free_strs(data->cmd_path, data->cmds);
	}
	//if (data->heredoc == 1)
		//unlink(".heredoc.tmp");
	exit(error_status);
}


static void	ft_redirect_puts(int input, int output, t_data *data)
{

	(void)data;
	if(dup2(input, STDIN_FILENO) == -1)
		ft_error("Input failed");
	if(dup2(output, STDOUT_FILENO) == -1)
		ft_error("Output failed");
}

//redirects the first comand the end or the midle
static void	child_process(t_data *d)
{
	if(d->child == 0)
		ft_redirect_puts(d->fd_input, d->pipe[1], d);
	else if (d->child == d->num_cmds - 1)
		ft_redirect_puts(d->pipe[2 * d->child - 2], d->fd_output, d);
	else
		ft_redirect_puts(d->pipe[2 * d->child - 2], d->pipe[2 * d->child + 1], d);
	ft_close_pipes(d);
	if(execve(d->cmd_path,d->cmds, d->env) == -1)
	printf("Entra aqui\n");
		ft_free_paths(d->cmds);
}

static int parent_process(t_data *data)
{
	pid_t	wpid;
	int		status;
	//int		last_child;
	int		exit_code;

	ft_close_pipes(data);
	exit_code = 1;
	data->child--;
	//last_child = data->pids[data->num_cmds - 1];
	while(data->child >= 0)
	{
		wpid = waitpid(data->pids[data->child], &status, 0);
		if(wpid == data->pids[data->num_cmds - 1])
		{
			if(data->child == (data->num_cmds - 1) && WIFEXITED(status))
			 {
				exit_code = WEXITSTATUS(status);
				//printf("Entra aqui\n");
			 }
		}
		data->child--;
	}
	free(data->pids);
	free(data->pipe);
	//printf("%d", exit_code);
	return (exit_code);
} 

static int pipex(t_data *data)
{
	int exit_code;
	
	if (pipe(data->pipe) == -1)
		perror("unexpected error");
	data->child = 0;
	while (data->child < data->num_cmds)
	{
		data->cmds = ft_split(data->argv[data->child + 2 ], ' ');
		if (!data->cmds)
			perror("unexpected error");
		data->cmd_path = ft_get_path(data->cmds[0], data->env);
		data->pids[data->child] = fork();
		if (data->pids[data->child] == -1)
			perror("unexpected error");
		else if (data->pids[data->child] == 0)
			child_process(data);
		//free_strs(data->cmd_path, data->cmds);
		data->child++;
	}
	exit_code = parent_process(data);
	return (exit_code);
}

int main(int argc, char **argv, char **envp)
{
	//printf("Hola");
	t_data data;
	int	exit_code;
	
	printf("Entra aqui\n");
	data = init(argc, argv, envp);
	exit_code = pipex(&data);
	return (exit_code);
}