/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 14:11:43 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/10/25 16:09:21 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_option(t_mini *shell)
{
	t_token	*tmp2;
	t_token	*check;
	int		j;
	int		i;

	j = 0;
	tmp2 = shell->cmd->token;
	check = shell->cmd->token;
	while (tmp2)
	{
		tmp2 = tmp2->next;
		j++;
	}
	i = -1;
	while (++i < j)
	{
		if (!ft_strcmp(check->arg, "-n"))
			return 0;
		check = check->next;
	}
	return (1);

}

int	ft_echo(t_mini *shell)
{
	int		i;
	int		flag;
	char	**temp;
	char	**buff;


	if (!check_option(shell))
		flag = 2;
	else
		flag = 1;
	buff = make_buff(shell);
	i = -1;
	while(buff[++i])
		ft_putstr_fd(buff[i], STDOUT);
	// i = 0;
	// while (buff[i])
	// 	i++;
	// temp = (char **)malloc(sizeof(char *) * (i - flag + 1));
	// i = -1;
	// while (buff[++i + flag])
	// 	temp[i] = buff[i + flag];
	// temp[i] = NULL;
	// i = -1;
	// while(temp[++i])
	// {
	// 	write(1, temp[i], ft_strlen(temp[i]));
	// 	write(1, " ", 1);
	// }
	// if (!check_option(shell))
	// 	return 0;
	// write(1, "\n", 1);
	// free(buff);
	return (0);
}
