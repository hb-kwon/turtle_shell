/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 14:11:43 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/10/13 09:46:07 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_mini *shell)
{
	int		i;
	char	**temp;
	char	**buff;

	buff = make_buff(shell);
	i = 0;
	while (buff[i])
		i++;
	temp = (char **)malloc(sizeof(char *) * i);
	i = -1;
	while (buff[++i])
		temp[i] = buff[i];
	temp[i] = NULL;
	if (execve("/bin/echo", temp ,shell->envp) == -1)
		fprintf(stderr, "에러 %s\n", strerror(errno));
	return (0);
}
