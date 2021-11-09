/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 22:38:28 by ysong             #+#    #+#             */
/*   Updated: 2021/11/10 01:49:15 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_token(t_mini *shell, int type)
{
	t_token	*temp;

	temp = shell->cmd->token;
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
		if (!stat(new_path, &s))
			return (new_path);
		free(new_path);
	}
	ft_free(paths);
	return (ft_strdup(cmd));
}

char	*find_value(char *name, char **envp)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(name);
	while (envp[++i])
	{
		if (!ft_strncmp(name, envp[i], len))
		{
			if (envp[i][len] == '=')
				return (ft_strchr(envp[i], '=') + 1);
		}
	}
	return (NULL);
}
