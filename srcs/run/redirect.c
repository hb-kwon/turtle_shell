/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 07:27:54 by ysong             #+#    #+#             */
/*   Updated: 2021/10/24 08:08:32 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_token(t_mini *shell, int type)
{
    t_token *temp = shell->cmd->token;

    while(temp->type != type)
        temp = temp->next;
    
    return temp->arg;
}
char	*find_path(t_mini *shell, char *cmd)
{
	int	i;
    char    *temp;
    char    *new_path;
    char    **paths;
    struct stat s;

	temp = find_en("PATH=", shell->envp);
    paths = ft_split(temp, ':');
    i = -1;
	while (paths[++i])
	{
        temp = ft_strjoin("/", cmd);
        new_path = ft_strjoin(paths[i], temp);
        free(temp);
        if (stat(new_path, &s) == 0)
            return (new_path);
        free(new_path);
	}
	return (ft_strdup(cmd));
}

int reprocess(t_mini *shell)
{
    int fd;
    int i;
    char *path;
    char **buff;

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
int outreprocess(t_mini *shell)
{
    int fd;
    int i;
    char *path;
    char **buff;

    buff = make_buff(shell);
    fd = open(find_token(shell, ARG),  O_RDONLY, 0744);
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
    int i;
    int temp;
    int status;
    pid_t pid;

    i = 0;
    pid = fork();
    if (pid == 0)
    {
        if (shell->cmd->re_flag == RD_IN)
            temp = reprocess(shell);
        else if (shell->cmd->re_flag == RD_OUT)
            temp = outreprocess(shell);
        exit(temp);
    }
    wait(&status);
    return (0);
}