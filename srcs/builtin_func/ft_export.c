/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 14:12:47 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/11/14 11:31:12 by ysong            ###   ########.fr       */
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

void	add_export(char *str, char ***en)
{
	// 기존에 있던 걸 free하고 
	int	i;
	int	j;
	char **temp;

	i = -1;
	while ((*en)[++i])
		;
	temp = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while((*en)[++i])
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
	char	**new;
	
	/*
		키와 벨류가 들어왔을 떄
		만약 기존에 있었다면 새로만든다
		없었다면 추가
	*/
	i = -1;
	char *temp;
	int		len;

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
		if (shell->cmd->pre_flag == 1)
			return (0);
		while (token)
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
			token = token->next;
		}
	}
	g_mini.exit_status = 0;
	return (status);
}
