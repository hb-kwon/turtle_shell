/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 14:12:47 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/11/09 02:34:57 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(char **en)
{
	int	i;

	i = -1;
	while (en[++i])
	{
		write(1, "declare -x ",ft_strlen("declare -x "));
		ft_putendl_fd(en[i], 1);
	}
}

static void	add_export(char *str, char **new, int i)
{
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
}

char *find_key(char *str, int key)
{
	int i;
	char *temp;

	temp = (char *)malloc(sizeof(char) * strlen(str));
	i = -1;
	while(str[++i])
	{
		if (str[i] == key)
		{
			temp[i] = 0;
			return (temp);
		}
		else
		{
			temp[i] = str[i];
		}
	}
	return (NULL);
}

static int	check_export(char *str, char ***en)
{
	int		i;
	char	**new;

	i = -1;
	while ((*en)[++i])
	{
		char *temp = find_key((*en)[i], '=');
		char *str_temp  = find_key(str, '=');
		if (!ft_strncmp(find_key((*en)[i],'='), find_key(str,'='), ft_strlen(str)))
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

int is_export_valid(char *str)
{
	int i;

	i = -1;
	if (ft_isdigit(str[++i]))
	{
		return (0);
	}
	//나중에 더많은 예외처리 추가예정
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
		while(token)
		{
			if (!is_export_valid(find_key(token->arg, '=')))
			{
				// todo printf_error 추가
				printf("error\n");
			}
			status = check_export(token->arg, &shell->envp);
			token = token->next;
		}
	}
	g_mini.exit_status = 0;
	return (status);
}
