/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 01:34:56 by jcrisp            #+#    #+#             */
/*   Updated: 2019/03/25 01:40:23 by jcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <inttypes.h>
# include <stdio.h>

typedef struct		s_argu{
	int				flags;
	int				precision;
	int				width;
}					t_argu;

# define PRINTF_FAILURE (-1)
# define FT_BIT(x) (1 << (x))
# define SPECIFIERS "spdiouxXc"
# define SPECI_SIZE (ft_strlen(SPECIFIERS))

# define S (0)
# define P (1)
# define D (2)
# define I (3)
# define O (4)
# define U (5)
# define LOWER_X (6)
# define UPPER_X (7)
# define C (8)
# define HASH       (FT_BIT(0))
# define ZERO       (FT_BIT(1))
# define MINUS      (FT_BIT(2))
# define PLUS       (FT_BIT(3))
# define SPACE      (FT_BIT(4))
# define S_BIT      (FT_BIT(5))
# define P_BIT      (FT_BIT(6))
# define D_BIT      (FT_BIT(7))
# define I_BIT      (FT_BIT(8))
# define O_BIT      (FT_BIT(9))
# define U_BIT      (FT_BIT(10))
# define LOW_X_BIT  (FT_BIT(11))
# define UPP_X_BIT  (FT_BIT(12))
# define C_BIT      (FT_BIT(13))
# define HH         (FT_BIT(14))
# define H          (FT_BIT(15))
# define LL         (FT_BIT(16))
# define L          (FT_BIT(17))
# define J          (FT_BIT(18))
# define Z          (FT_BIT(19))
# define WIDTH      (FT_BIT(20))
# define PRECISION  (FT_BIT(21))

int					ft_printf(const char *string, ...);
int					spec_buff(va_list arg, char **format, t_argu *attr);
int					print_spaces(int width, int len, int attr);
int					get_atts(char **format, va_list arg, t_argu *attr);
int					num_zeros(t_argu *attr, int *len, int sign);
int					num_spaces(int attr, int minw, int *len);
char				*get_num_unsign(uintmax_t n, int *nbdig, int base);
int					form_sign(intmax_t n, t_argu *attr);
int					form_usign(uintmax_t n, t_argu *attr, \
						char *(*convert)(uintmax_t, int *));
int					print_str(va_list ap, t_argu *attr);
int					print_hex(va_list ap, t_argu *attr);
int					print_dec(va_list ap, t_argu *attr);
int					print_oct(va_list ap, t_argu *attr);
int					print_char(va_list ap, t_argu *attr);

#endif
