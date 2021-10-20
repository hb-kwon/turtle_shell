/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:30:16 by ysong             #+#    #+#             */
/*   Updated: 2021/10/20 21:09:07 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int print_error1(char *msg, char *err_num)
{
	ft_putstr_fd("minishell :", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_num, 2);
	return (-1);
}

int print_error2(char *msg1, char *msg2, char *err_num)
{
	ft_putstr_fd("minishell :", 2);
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg2, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_num, 2);
	return (-1);
}

char	**make_buff(t_mini *shell)
{
	t_token	*temp;
	t_token	*tmp2;
	char	**buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp2 = shell->cmd->token;
	temp = shell->cmd->token;
	while (tmp2)
	{
		tmp2 = tmp2->next;
		j++;
	}
	buff = (char **)malloc(sizeof(char *) * (j + 1));
	while (temp)
	{
		buff[i] = temp->arg;
		temp = temp->next;
		i++;
	}
	buff[j] = NULL;
	return (buff);
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
