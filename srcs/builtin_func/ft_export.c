/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 14:12:47 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/11/12 00:36:25 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(char **en)
{
	int	i;

	i = -1;
	while (en[++i])
	{
		write(1, "declare -x ", ft_strlen("declare -x "));
		ft_putendl_fd(en[i], 1);
	}
}

void	add_export(char *str, char **new, int i)
{
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
}

static int	check_export(char *str, char ***en)
{
	int		i;
	char	**new;

	i = -1;
	while ((*en)[++i])
	{
		if (!ft_strncmp(find_key((*en)[i], '='), \
		find_key(str, '='), ft_strlen(str)))
		{
			(*en)[i] = ft_strdup(str);
			return (1);
		}
	}
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
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
	int		status;
	char	*temp;
	t_token	*token;

	status = 0;
	token = shell->cmd->token->next;
	if (!token)
		print_export(shell->envp);
	else
	{
		while (token)
		{
			temp = find_key(token->arg, '=');
			if (temp == NULL)
				export_no_value(token->arg, &shell->envp);
			else if (!is_export_valid(temp))
			{
				print_error2("export", token->arg, \
				": not a valid identifier");
			}
			else
				status = check_export(token->arg, &shell->envp);
			token = token->next;
		}
	}
	g_mini.exit_status = 0;
	return (status);
}
