/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 14:12:30 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/10/12 15:05:38 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_mini *shell)
{
	int i;

	i = 0;
	while(shell->envp[i])
	{
		write(1, shell->envp[i], ft_strlen(shell->envp[i]));
		write(1,"\n",1);
		i++;
	}
	return (0);
}
