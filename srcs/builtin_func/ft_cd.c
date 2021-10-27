/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:19:13 by hkwon             #+#    #+#             */
/*   Updated: 2021/10/27 16:55:45 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// buff에 알맞은 이름을 모르겠슴... cmd 이후의 line? 이라고 밖에
void	cd_home(char *path, char **buff, char **en)
{
	path = find_en("HOME", en);
	if (chdir(path) == -1)
		print_error1("cd", "HOME not set");
	(void)buff;
}

void	cd_en(char *path, char **buff, char **en)
{
	path = find_en(&(buff[1][1]), en);
	if (chdir(path) == -1)
		chdir(find_en("HOME", en));
}

int	ft_cd(t_mini *shell)
{
	char	*path;
	char	**buff;
	t_token *token;

	token = shell->cmd->token->next;
	buff = make_buff(shell);

	path = NULL;
	if (token->arg != NULL && token->arg[0] != '~' && token->arg[0] != '$')
	{
		path = token->arg;
		if (chdir(path) == -1)
			print_error2("cd", path, strerror(errno));
	}
	else if (token->arg == NULL || token->arg[0] == '~')
		cd_home(path, buff, shell->envp);
	else if (token->arg[0] == '$')
		cd_en(path, buff, shell->envp);
	return (0);
}
