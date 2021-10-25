/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:03:49 by hkwon             #+#    #+#             */
/*   Updated: 2021/10/25 18:19:39 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_synerr(char c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
	write(STDERR_FILENO, &c, 1);
	ft_putstr_fd("\'\n", STDERR_FILENO);
	g_mini.exit_status = 258;
	return (0);
}

static int	quote_last_open(char flag)
{
	if (flag & S_QUOTE)
		return (ft_print_synerr('\''));
	else if (flag & D_QUOTE)
		return (ft_print_synerr('\"'));
	else
		return (0);
}

static void	quote_flag_onoff(char line, int *i, char *flag)
{
	if (line == '\'')
	{
		if (*flag & S_QUOTE)
			*flag ^= S_QUOTE;
		else if (!(*flag & D_QUOTE))
			*flag |= S_QUOTE;
		(*i)++;
	}
	else if (line == '\"')
	{
		if (*flag & D_QUOTE)
			*flag ^= D_QUOTE;
		else if (!(*flag & S_QUOTE))
			*flag |= D_QUOTE;
		(*i)++;
	}
}

int	init_check(char *line)
{
	int		i;
	char	flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (ft_strchr("\t\n ", line[i]))
			i++;
		else if (line[i] == '\'' || line[i] == '\"')
			quote_flag_onoff(line[i], &i, &flag);
		else if (line[i] == '\\' && (flag & D_QUOTE))
			i += 2;
		else
			i++;
	}
	if ((flag & S_QUOTE) || (flag & D_QUOTE))
		return (quote_last_open(flag));
	return (1);
}
