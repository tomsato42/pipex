/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomsato <tomsato@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:23:01 by tomsato           #+#    #+#             */
/*   Updated: 2025/03/26 12:57:35 by tomsato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static char	*extract_token(const char **str)
{
	const char	*start;
	char		*token;
	char		quote_char;

	while (is_whitespace(**str))
		(*str)++;
	if (is_quote(**str))
	{
		quote_char = *(*str)++;
		start = *str;
		while (**str && **str != quote_char)
			(*str)++;
		token = ft_substr(start, 0, *str - start);
		if (**str == quote_char)
			(*str)++;
	}
	else
	{
		start = *str;
		while (**str && !is_whitespace(**str))
			(*str)++;
		token = ft_substr(start, 0, *str - start);
	}
	return (token);
}

char	**ft_split_with_quotes(const char *str)
{
	char	**result;
	char	*token;
	size_t	count;

	result = malloc(sizeof(char *) * ft_strlen(str) * 2);
	if (!result)
		return (NULL);
	count = 0;
	while (*str)
	{
		token = extract_token(&str);
		if (token)
			result[count++] = token;
	}
	result[count] = NULL;
	return (result);
}
