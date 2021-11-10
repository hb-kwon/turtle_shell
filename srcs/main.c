/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 10:59:00 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/11/10 14:04:00 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 환경변수를 조작할 시 malloc과 free에 있어서 main 변수 envp를 그대로 사용하면
// error가 발생한다고 한다.

// 환경변수를 따로 저장할 문자열을 만들 것인가?
// 환경변수를 바로 사용할 것인가?
// 바로 사용했을 때 문제가 될 부분은 없는가?
// 수정할 일이 생기면 거기에 맞춰서 작성.
t_mini	g_mini;

int	main(int argc, char *argv[], char *envp[])
{
	char	**en;

	init_shell(&en, envp);
	minishell(en);
	ft_free(en);
	(void)argc;
	(void)argv;
	return (0);
}
