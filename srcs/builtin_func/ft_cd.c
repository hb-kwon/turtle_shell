/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 14:11:37 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/10/13 09:43:32 by ysong            ###   ########.fr       */
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

int		ft_cd(t_mini *shell)
{
	char	*path;
	char	**buff;

	buff = make_buff(shell);
	path = NULL;
	if (buff[1] != NULL && buff[1][0] != '~' && buff[1][0] != '$')
	{
		path = buff[1];
		if (chdir(path) == -1)
			print_error2("cd", path, strerror(errno));
	}
	else if (buff[1] == NULL || buff[1][0] == '~')
		cd_home(path, buff, shell->envp);
	else if (buff[1][0] == '$')
		cd_en(path, buff, shell->envp);
	return (0);
}
