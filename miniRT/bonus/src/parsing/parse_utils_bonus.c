/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:09:03 by rbaldin           #+#    #+#             */
/*   Updated: 2025/10/27 18:03:07 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	skipping_emptiness(char **str)
{
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
}

void	skip_comma(char **str)
{
	if (**str == ',')
		(*str)++;
}

static float	getting_float(char **str, float res)
{
	float	power;

	power = 1.0;
	while (ft_isdigit(**str))
	{
		res = res * 10.0 + (**str - '0');
		(*str)++;
	}
	if (**str == '.')
	{
		(*str)++;
		while (ft_isdigit(**str))
		{
			power /= 10.0;
			res = res + (**str - '0') * power;
			(*str)++;
		}
	}
	return (res);
}

float	ft_atof_dp(char **str)
{
	float	result;
	float	sign;

	result = 0.0;
	sign = 1.0;
	skipping_emptiness(str);
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1.0;
		(*str)++;
	}
	return (getting_float(str, result) * sign);
}

int	ft_atoi_dp(char **str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	skipping_emptiness(str);
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	while (ft_isdigit(**str))
	{
		result = result * 10 + (**str - '0');
		(*str)++;
	}
	return (result * sign);
}
