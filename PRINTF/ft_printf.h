/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:23:10 by eonen             #+#    #+#             */
/*   Updated: 2025/08/05 13:29:43 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_format(const char **format, va_list args);
int	ft_putstr(char *s);
int	ft_putchar(char c);
int	ft_putnbr_hex(unsigned int n, char case_type);
int	ft_putnbr_decimal(int n);
int	ft_put_unsigned_nbr(unsigned int n);
int	ft_put_hex_ptr(void *ptr);
int	ft_putnbr_base(unsigned long n, char *base_chars);
int	get_base_len(char *base_chars);

#endif
