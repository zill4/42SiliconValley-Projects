#include "ft_printf.h"
#include "libft.h"

// converts number to base 8
static char *conv_oct(uintmax_t num, int *dig)
{
  return (get_num_unsign(num, dig, 8));
}
// printing octal is now important....
int   print_oct(va_list ap, t_argu *arg)
{
    int len;

  if (arg->flags & J)
    len = form_usign(va_arg(ap, uintmax_t), arg, &conv_oct);
  else if (arg->flags & Z)
    len = form_usign(va_arg(ap, size_t), arg, &conv_oct);
  else if (arg->flags & LL)
    len = form_usign(va_arg(ap, unsigned long long), arg, &conv_oct);
  else if (arg->flags & L)
    len = form_usign(va_arg(ap, unsigned long), arg, &conv_oct);
  else if (arg->flags & HH)
    len = form_usign((unsigned char)va_arg(ap, unsigned int), arg, &conv_oct);
  else if (arg->flags & H)
    len = form_usign((unsigned short)va_arg(ap, unsigned int), arg, &conv_oct);
  else
    len = form_usign(va_arg(ap, unsigned int), arg, &conv_oct);
  return (len);
}
