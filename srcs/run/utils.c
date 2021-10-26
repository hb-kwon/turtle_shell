/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:30:16 by ysong             #+#    #+#             */
/*   Updated: 2021/10/26 18:14:33 by hkwon            ###   ########.fr       */
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

// char	*ft_str_char_join(char *before, char c)
// {
// 	int		len;
// 	char	*after;
// 	int		i;

// 	len = ft_strlen(before);
// 	if (c == '\n')
// 		return (before);
// 	else
// 	{
// 		after = (char *)malloc(sizeof(char) * (len + 2));
// 		i = -1;
// 		if (before == NULL)
// 			after[0] = c;
// 		else
// 		{
// 			while (before[++i])
// 				after[i] = before[i];
// 			after[i] = c;
// 			free(before);
// 		}
// 		after[len + 1] = '\0';
// 	}
// 	return (after);
// }

char	*make_dup_no_quote(char *arg)
{
	// int		i;
	// int		j;
	// int		len;
	// char	flag;
	char	*res;

	res = arg;
	return (res);
}

char	**make_buff(t_mini *shell)
{
	t_token	*temp;
	t_token	*temp2;
	char	**buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp2 = shell->cmd->token;
	temp = shell->cmd->token;
	while (temp2)
	{
		temp2 = temp2->next;
		j++;
	}
	buff = (char **)malloc(sizeof(char *) * (j + 1));
	buff[j] = NULL;
	while (temp)
	{
		buff[i] = make_dup_no_quote(temp->arg);
		//debug
		printf("=========DEBUG=========\n");
		printf("buff check : %s\n", buff[i]);
		//end
		temp = temp->next;
		i++;
	}
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
