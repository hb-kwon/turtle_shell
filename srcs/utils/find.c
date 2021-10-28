/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 22:38:28 by ysong             #+#    #+#             */
/*   Updated: 2021/10/27 22:41:01 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_token(t_mini *shell, int type)
{
	t_token	*temp = shell->cmd->token;

	while (temp && temp->type != type)
		temp = temp->next;
    if (temp)
        return (temp->arg);
    else
        return (NULL);
}

char	*find_en(char *key, char **en)
{
	int	i;

	i = -1;
	while (en[++i])
	{
		if (!ft_strncmp(en[i], key, ft_strlen(key)))
			return (en[i] + ft_strlen(key) + 1);
	}
	return (NULL);
}

char	*find_path(t_mini *shell, char *cmd)
{
	int			i;
	char		*temp;
	char		*new_path;
	char		**paths;
	struct stat	s;

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