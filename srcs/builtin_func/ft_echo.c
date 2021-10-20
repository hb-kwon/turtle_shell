/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 14:11:43 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/10/20 17:44:46 by hkwon            ###   ########.fr       */
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
	temp = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (buff[++i])
		temp[i] = buff[i];
	temp[i] = NULL;
	if (execve("/bin/echo", temp, shell->envp) == -1)
		fprintf(stderr, "에러 %s\n", strerror(errno));
	return (0);
}
