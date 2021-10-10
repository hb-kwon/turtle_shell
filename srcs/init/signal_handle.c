/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:08:55 by hkwon             #+#    #+#             */
/*   Updated: 2021/10/10 17:22:22 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_in()
{

}

void	signal_quit()
{

}

void	signal_handle(int sig_num)
{
	signal(SIGIN, signal_in);
	signal(SIGQUIT, signal_quit);
}
