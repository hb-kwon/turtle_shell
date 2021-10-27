/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 14:12:47 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/10/27 18:50:52 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(char **en)
{
	int i;

	i = -1;
	while (en[++i])
	{
		write(1, "declare -x ",ft_strlen("declare -x "));
		ft_putendl_fd(en[i], 1);
	}
}

void add_export(char *str, char **new, int i)
{
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
}

int check_export(char *str, char ***en)
{
	int i;
	char **new;

	i = -1;
	while((*en)[++i])
		if (!ft_strncmp((*en)[i], str, ft_strlen(str)))
		{
			(*en)[i] = ft_strdup(str);
			return (1);
		}
	if (!(new = malloc(sizeof(char*) * (i + 2))))
		return (0);
	i = -1;
	while ((*en)[++i])
		new[i] = ft_strdup((*en)[i]);
	add_export(str, new, i);
	*en = new;
	return (1);
}

int	ft_export(t_mini *shell)
{
	int i;
	int status;

	status = 0;
	i = 0;

	t_token *token;
	
	token = shell->cmd->token->next;
	if(!token)
		print_export(shell->envp);
	else
	{
		if(ft_strchr(token->arg, '='))
			status = check_export(token->arg, &shell->envp);
		else
			while(token)
			{
				status = check_export(token->arg, &shell->envp);
				token = token->next;
			}
	}
	return (status);
}
