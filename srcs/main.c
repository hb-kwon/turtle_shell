/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 10:59:00 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/11/11 20:01:46 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	g_mini;

int	main(int argc, char *argv[], char *envp[])
{
	char	**en;

	init_shell(&en, envp);
	minishell(en);
	ft_free_arr(en);
	(void)argc;
	(void)argv;
	return (0);
}
