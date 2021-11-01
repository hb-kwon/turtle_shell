/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 07:27:54 by ysong             #+#    #+#             */
/*   Updated: 2021/11/01 22:16:56 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reprocess(t_mini *shell)
{
	int		fd;
	int		i;
	char	*path;
	char	**buff;

	buff = make_buff(shell);
	fd = open(find_token(shell, ARG),  O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd < 0)
	{
		print_error2(find_token(shell, ARG), "no such file or dicretory","");
		return (0);
	}
	if(!(path = find_path(shell, find_token(shell, COMMAND))))
		return (print_error2(find_token(shell, ARG), "no such file or dicretory",""));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (check_cmd(find_token(shell, COMMAND)))
	{
		i = -1;
		while (++i < BLTIN_NUM)
		{
			if (!ft_strcmp(find_token(shell, COMMAND), blt_str(i)))
			{
				run_blt(shell, i);
				break ;
			}
		}
	}
	else if (execve(path, buff, shell->envp) == -1)
		return (print_error2(find_token(shell, ARG), "no such file or dicretory",""));
	free(path);
	free(buff);
	return (EXIT_SUCCESS);
}

int add_reprocess(t_mini *shell)
{
	int fd;
	int i;
	char *path;
	char **buff;

    buff = make_buff(shell);
    fd = open(find_token(shell, ARG),  O_WRONLY | O_CREAT | O_APPEND, 0744);
    if (fd < 0)
    {
        print_error2(find_token(shell, ARG), "no such file or dicretory","");
        return (0);
    }
    if(!(path = find_path(shell, find_token(shell, COMMAND))))
            return (print_error2(find_token(shell, ARG), "no such file or dicretory",""));
    dup2(fd, STDOUT_FILENO);
    close(fd);
    if (check_cmd(find_token(shell, COMMAND)))
    {
        i = -1;
        while (++i < BLTIN_NUM)
        {
            if (!ft_strcmp(find_token(shell, COMMAND), blt_str(i)))
            {
                run_blt(shell, i);
                break ;
            }
        }
    }
    else if (execve(path, buff, shell->envp) == -1)
            return (print_error2(find_token(shell, ARG), "no such file or dicretory",""));
    free(path);
    free(buff);
    return (EXIT_SUCCESS);
}

int outreprocess(t_mini *shell)
{
	int		fd;
	int		i;
	char	*path;
	char	**buff;

    buff = make_buff(shell);
    fd = open(find_token(shell, ARG), O_WRONLY | O_CREAT | O_RDONLY, 0744);
    if (fd < 0)
    {
        print_error2(find_token(shell, ARG), "no such file or dicretory","");
        return (0);
    }
    if(!(path = find_path(shell, find_token(shell, COMMAND))))
            return (print_error2(find_token(shell, ARG), "no such file or dicretory",""));
    dup2(fd, STDIN_FILENO);
    close(fd);
    if (check_cmd(find_token(shell, COMMAND)))
    {
        i = -1;
        while (++i < BLTIN_NUM)
        {
            if (!ft_strcmp(find_token(shell, COMMAND), blt_str(i)))
            {
                run_blt(shell, i);
                break ;
            }
        }
    }
    else if (execve(path, buff, shell->envp) == -1)
            return (print_error2(find_token(shell, ARG), "no such file or dicretory",""));
    free(path);
    free(buff);
    return (EXIT_SUCCESS);
}
int add_outreprocess(t_mini *shell)
{
    int fd;
    int i;
    char *path;
    char **buff;

    buff = make_buff(shell);
    fd = open(find_token(shell, ARG), O_WRONLY | O_CREAT | O_APPEND, 0744);
    if (fd < 0)
    {
        print_error2(find_token(shell, ARG), "no such file or dicretory","");
        return (0);
    }
    if(!(path = find_path(shell, find_token(shell, COMMAND))))
            return (print_error2(find_token(shell, ARG), "no such file or dicretory",""));
    dup2(fd, STDIN_FILENO);
    close(fd);
    if (check_cmd(find_token(shell, COMMAND)))
    {
        i = -1;
        while (++i < BLTIN_NUM)
        {
            if (!ft_strcmp(find_token(shell, COMMAND), blt_str(i)))
            {
                run_blt(shell, i);
                break ;
            }
        }
    }
    else if (execve(path, buff, shell->envp) == -1)
            return (print_error2(find_token(shell, ARG), "no such file or dicretory",""));
    free(path);
    free(buff);
    return (EXIT_SUCCESS);
}
int redirect(t_mini *shell)
{
	int	i;
	int	temp;
	int	status;
	pid_t	pid;

    i = 0;
    pid = fork();
    if (pid == 0)
    {
        if (shell->cmd->re_flag == RD_IN)
            temp = reprocess(shell);
        else if (shell->cmd->re_flag == RD_OUT)
            temp = outreprocess(shell);
        else if (shell->cmd->re_flag == RD_APPEND)
            temp = add_reprocess(shell);
        else if (shell->cmd->re_flag == RD_HEREDOC)
            temp = add_outreprocess(shell);
        exit(temp);
    }
    wait(&status);
    return (0);
}
