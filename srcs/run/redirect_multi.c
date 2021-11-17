/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_multi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:26:31 by ysong             #+#    #+#             */
/*   Updated: 2021/11/17 21:33:01 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
    원하는 값 은
    열어야 될 파일이 무엇인지
    입력 받고자 하는 파일이 무엇인지

    1. 토큰의 갯수를 세서 0, 3 이나 2, 0 처럼 한부분이 0이라면
    해당하는 문자를 리턴해준다
    2. 2개가 모두 0 이상이면 두개를 하나씩 만들어서 따로 동작하도록
    만들자
*/

int count_rd_option(t_mini *shell, int option)
{
    t_token *temp;
    int in_count;
    int out_count;

    temp = shell->cmd->token;
    in_count = 0;
    out_count = 0;
    while(temp)
    {
        if (temp->type == RD_IN || \
        temp->type == RD_HEREDOC)
            in_count++;
        if (temp->type == RD_OUT || \
        temp->type == RD_APPEND)
            out_count++;
        temp = temp->next;
    }
    if (option == 0)
        return (in_count);
    else if (option == 1)
        return (out_count);
    else
        return (-1);

}

int rd_option_only_out(t_mini *shell, int *rd_fds)
{
    t_token *temp;
    char *open_file;
    int     type;

    type = 0;
    temp = shell->cmd->token;
    while (temp)
    {
        if (temp->type == RD_OUT || temp->type == RD_APPEND)
        {
            open_file = temp->arg;
            type = temp->type;
            close(open(open_file, O_WRONLY | O_CREAT | O_APPEND, 0644));

        }
        temp = temp->next;
    }
    if (type == RD_OUT)
        return (multi_redirect_out(open_file, rd_fds));
    else
        return (multi_redirect_app(open_file, rd_fds));
}

int rd_option_only_in(t_mini *shell, int *rd_fds)
{
    t_token *temp;
    char *open_file;
    int     type;

    type = 0;
    temp = shell->cmd->token;
    while (temp)
    {
        if (temp->type == RD_IN || temp->type == RD_HEREDOC)
        {
            open_file = temp->arg;
            close(open(open_file, O_RDONLY));
            type = temp->type;
        }
        temp = temp->next;
    }
    if (type == RD_IN)
        return (multi_redirect_in(open_file, rd_fds));
    else
        multi_redirect_herdoc(shell, rd_fds);
    return (1);
}

int rd_option_in_and_out(t_mini *shell, int *rd_fds)
{
    t_token *temp;
    int     last_type;
	int		old_fds[2];

    last_type = 0;
	save_old_fds(old_fds);
    // (void)rd_fds;
    temp = shell->cmd->token;
    while (temp)
    {
        if (temp->type == RD_IN || temp->type == RD_HEREDOC ||
            temp->type == RD_OUT || temp->type == RD_APPEND)
            last_type = temp->type;
        temp = temp->next;
    }
    if (last_type == RD_IN || last_type == RD_HEREDOC)
    {
        rd_option_only_out(shell,rd_fds);
        // redirect_restore(rd_fds, old_fds);
        rd_option_only_in(shell,rd_fds);
    }
    if (last_type == RD_OUT || last_type == RD_APPEND)
    {
        rd_option_only_in(shell,rd_fds);
        // redirect_restore(rd_fds, old_fds);
        rd_option_only_out(shell,rd_fds);
    }
    return (1);
}

int multi_rd(t_mini *shell, int *rd_fds)
{
    // 0은 in
    // 1은 out
    int rd_in_count;
    int rd_out_count;


    rd_in_count = count_rd_option(shell, 0);
    rd_out_count = count_rd_option(shell, 1);
    if (rd_in_count == 0)
        return (rd_option_only_out(shell, rd_fds));
    else if (rd_out_count == 0)
        return (rd_option_only_in(shell, rd_fds));
    else
        return (rd_option_in_and_out(shell, rd_fds));
    return (0);
}