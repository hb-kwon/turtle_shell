/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_special_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:41:25 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/16 17:06:29 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	special_pipe(char *line, int *i)
{
	(*i)++;
	if (line[*i] == '|')
		return (ft_print_synerr('|'));
	else if (!line[*i])
		return (ft_print_synerr('|'));
	return (1);
}

static int	special_rd_in(char *line, int *i)
{
	(*i)++;
	if (!line[*i])
		return (ft_print_synerr('<'));
	else if (line[*i] == '<' && !line[(*i) + 1])
		return (ft_print_synerr('<'));
	else if (line[*i] == '<' && line[(*i) + 1] == '<')
		return (ft_print_synerr('<'));
	return (1);
}

static int	special_rd_out(char *line, int *i)
{
	(*i)++;
	if (!line[*i])
		return (ft_print_synerr('>'));
	else if (line[*i] == '>' && !line[(*i) + 1])
		return (ft_print_synerr('>'));
	else if (line[*i] == '>' && line[(*i) + 1] == '>')
		return (ft_print_synerr('>'));
	return (1);
}

int	special_flag_onoff(char *line, int *i)
{
	if (line[*i] == '|')
		return (special_pipe(line, i));
	else if (line[*i] == '<')
		return (special_rd_in(line, i));
	else if (line[*i] == '>')
		return (special_rd_out(line, i));
	else
		(*i)++;
	return (1);
}
