/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 14:12:47 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/11/16 18:54:13 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(char **en)
{
	int		i;
	char	*key;
	char	*value;
	char	**temp;

	i = -1;
	while (en[++i])
	{
		temp = ft_split(en[i], '=');
		key = temp[0];
		if (temp[1])
			value = temp[1];
		else
			value = NULL;
		export_print(en, key, value, i);
		ft_free_arr(temp);
	}
}

void	add_export(char *str, char ***en)
{
	int		i;
	int		j;
	char	**temp;

	i = -1;
	while ((*en)[++i])
		;
	temp = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while ((*en)[++i])
	{
		temp[i] = (char *)malloc(PATH_MAX + 1);
		j = -1;
		while ((*en)[i][++j])
			temp[i][j] = (*en)[i][j];
		temp[i][j] = 0;
	}
	temp[i++] = ft_strdup(str);
	temp[i] = 0;
	ft_free_arr(*en);
	(*en) = temp;
	return ;
}

static int	export_key_value(char *str, char ***en)
{
	int		i;
	int		len;
	char	*temp;

	i = -1;
	temp = find_key(str, '=');
	len = ft_strlen(temp);
	free(temp);
	while ((*en)[++i])
	{
		if (!ft_strncmp((*en)[i], str, len))
		{
			free((*en)[i]);
			(*en)[i] = ft_strdup(str);
			return (1);
		}
	}
	add_export(str, en);
	return (1);
}

static void	ft_export_process(t_token *token, t_mini *shell)
{
	if (!is_export_valid(token->arg))
	{
		print_error2("export", token->arg, \
		": not a valid identifier");
	}
	else if (ft_strchr(token->arg, '=') == NULL)
		export_no_value(token->arg, &shell->envp);
	else
		export_key_value(token->arg, &shell->envp);
}

int	ft_export(t_mini *shell)
{
	int		status;
	t_token	*token;

	status = 0;
	token = shell->cmd->token->next;
	if (!token)
		print_export(shell->envp);
	else
	{
		if (shell->cmd->pre_flag == 1)
			return (0);
		while (token)
		{
			ft_export_process(token, shell);
			token = token->next;
		}
	}
	g_mini.exit_status = 0;
	return (status);
}
