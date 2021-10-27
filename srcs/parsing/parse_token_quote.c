/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:27:50 by hkwon             #+#    #+#             */
/*   Updated: 2021/10/27 17:53:10 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_char_join(char *before, char c)
{
	int		len;
	char	*after;
	int		i;

	len = ft_strlen(before);
	if (c == '\n')
		return (before);
	else
	{
		after = (char *)malloc(sizeof(char) * (len + 2));
		i = -1;
		if (before == NULL)
			after[0] = c;
		else
		{
			while (before[++i])
				after[i] = before[i];
			after[i] = c;
			free(before);
		}
		after[len + 1] = '\0';
	}
	return (after);
}

int		turn_on_flag(int *flag, int quote, int idx)
{
	if (*flag & quote)
		*flag ^= quote;
	else
		*flag |= quote;
	idx++;
	return (idx);
}

char	*set_value(char *arg, int idx)
{
	int		flag;
	char	*res;

	if (!arg)
		return (NULL);
	flag = 0;
	res = NULL;
	while (arg[idx])
	{
		if (arg[idx] == '\"' && !(flag & S_QUOTE))
			idx = turn_on_flag(&flag, D_QUOTE, idx);
		else if (arg[idx] == '\'' && !(flag & D_QUOTE))
			idx = turn_on_flag(&flag, S_QUOTE, idx);
		else
			res = ft_char_join(res, arg[idx++]);
	}
	return (res);
}

char	*find_value(char *name, char **envp)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(name);
	while (envp[++i])
	{
		if (!ft_strncmp(name, envp[i], len))
		{
			if (envp[i][len] == '=')
				return (ft_strchr(envp[i], '=') + 1);
		}
	}
	return (NULL);
}

char	*get_env_set_envp(char *env_temp, char *result)
{
	int	j;

	j = 0;
	while (env_temp && env_temp[j])
	{
		if (env_temp[j] == ' ' || env_temp[j] == '\t' || env_temp[j] == '\n')
		{
			result = ft_char_join(result, ' ');
			while (env_temp[j] == ' ' || \
				env_temp[j] == '\t' || env_temp[j] == '\n')
				j++;
		}
		else
		{
			result = ft_char_join(result, env_temp[j]);
			j++;
		}
	}
	return (result);
}

int	parse_nomal_string(char **res, char *args, int i)
{
	char	*name;
	char	*temp;

	if (args[i] == '$')
	{
		if (args[i + 1] == '?')
		{
			*res = ft_strjoin_free(*res, ft_itoa(g_mini.exit_status), 3);
			i += 2;
		}
		else
		{
			name = NULL;
			temp = NULL;
			while (!ft_strchr(" \t\n$\"\'\\/", args[++i]))
				name = ft_char_join(name, args[i]);
			temp = set_value(find_value(name, g_mini.envp), 0);
			*res = get_env_set_envp(temp, *res);
			if (name)
				free(name);
			if (temp)
				free(temp);
		}
	}
	else
		*res = ft_char_join(*res, args[i++]);
	return (i);
}

int	parse_get_dquote_env(char **res, char *args, int i)
{
	char	*name;
	char	*temp;

	name = NULL;
	temp = NULL;
	if (args[i + 1] == '?')
	{
		*res = ft_strjoin_free(*res, ft_itoa(g_mini.exit_status), 3);
		i += 2;
	}
	else
	{
		while (!ft_strchr(" \t\n\"\'\\/", args[++i]))
			name = ft_char_join(name, args[i]);
		temp = set_value(find_value(name, g_mini.envp), 0);
		*res = ft_strjoin_free(*res, temp, 1);
	}
	if (name)
		free(name);
	if (temp)
		free(temp);
	return (i);
}

int	parse_dquote_string(char **res, char *args, int i)
{
	i++;
	while (args[i] != '\"')
	{
		if (args[i] == '$')
			i = parse_get_dquote_env(res, args, i);
		else
			*res = ft_char_join(*res, args[i++]);
	}
	i++;
	return (i);
}

char	*parse_token_quote(char *args)
{
	char	*res;
	int		i;

	res = NULL;
	i = 0;
	while (args[i])
	{
		if (args[i] == '\'')
		{
			i++;
			while (args[i] != '\'')
				res = ft_char_join(res, args[i++]);
			i++;
		}
		else if (args[i] == '\"')
			i = parse_dquote_string(&res, args, i);
		else
			i = parse_nomal_string(&res, args, i);
	}
	free(args);
	return (res);
}
