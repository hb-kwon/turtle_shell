/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 14:12:50 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/10/12 14:48:46 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_mini *shell)
{
	char *pwd;

	pwd=getcwd(0, 1024);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	(void)shell;
	return (0);
}
