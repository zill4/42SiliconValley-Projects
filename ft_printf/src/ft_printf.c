/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcrisp <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 10:45:50 by jcrisp            #+#    #+#             */
/*   Updated: 2018/09/20 19:09:30 by jcrisp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/ft_printf.h"
#include <stdio.h>
#include <limits.h>

// convert int to null-terminated string using spec base and umbers...
char    *get_num_unsign(uintmax_t num, int *n_digis, int base)
{
  int len;
  char *str;
  uintmax_t r;

  len = 0;
  r = num;
  *n_digis = (!num) ? 1 : 0;
  while (r)
  {
    r /= base;
    *n_digis += 1;
  }
  if (!(str = (char *)malloc(*n_digis)))
    return (NULL);
  *str = '0';
  len = (!num) ? 1 : 0;
  while (num)
  {
    r = num % base;
    num /= base;
    str[len++] = r + '0';
  }
  str[len] = '\0';
  str = ft_strrev(str);
  return (str);
}
// converts number to base 10 and decimal, using the number unsigned
static char *conv_dec(uintmax_t num, int *num_digi)
{
  return (get_num_unsign(num, num_digi, 10));
}
// converts number to base 8
static char *conv_oct(uintmax_t num, int *dig)
{
  return (get_num_unsign(num, dig, 8));
}
// Give me those spaces baby
int   print_spaces(int width, int len, int att)
{
  while ((width - len) > 0)
  {
    ft_putchar(((att & ZERO) && !(att &  MINUS)) ? '0' : ' ');
    len++;
  }
  return (len);
}
// get the hex number by assigning shit to some other shit.
static char *get_hexen(uintmax_t num, char *hex, char *hex_str)
{
  int i;
  int len;

  i = 0;
  len = !num ? 1 : 0;
  while (num)
  {
    hex[len++] = hex_str[num & 0xF];
    num >>= 4;
  }
  while (i < (len / 2))
  {
    hex[i] ^= hex[len - i - 1];
    hex[len - i - 1] ^= hex[i];
    hex[i] ^= hex[len - i - 1];
    i += 1;
  }
  return (hex);
}
// how many digis is that?
static int hex_digi(uintmax_t num)
{
  int len;
  
  len = !num ? 1 : 0;
  while (num)
  {
    len++;
    num >>= 4;
  }
  return (len);
}
// conv the numb to base 16 using hex num....
static char *conv_hex(uintmax_t num, int *n_digi)
{
  char *hex_nbr;
  char *hex_str;

  *n_digi = hex_digi(num);
  if (!(hex_nbr = ft_memalloc(sizeof(char) * (*n_digi) + 1)))
      return (NULL);
  *hex_nbr = '0';
  if (!(hex_str = ft_strdup("0123456789ABCDEF")))
    return (NULL);
  hex_nbr = get_hexen(num, hex_nbr, hex_str);
  free(hex_str);
  return (hex_nbr);
}
// Get flags and stores them in the attribute structure.
// If there is no flag function returns a zero else then one.

static int get_flags(char flg, t_argu *arg)
{
  // So we are basically |= gating the attribute flag tracker and if it returns true.
  // Then we regard this as a found attribute, and we return for the flag that we have found.
  flg == '#' ? arg->flags |= HASH : 0;
  flg == '0' ? arg->flags |= ZERO : 0;
  flg == '-' ? arg->flags |= MINUS : 0;
  flg == ' ' ? arg->flags |= SPACE : 0;
  flg == '+' ? arg->flags |= PLUS : 0;
  return (flg == '#' || flg == '0' || flg == '-' || flg == ' ' || flg == '+');
}

// modifies the length of the data type.
// as set within a given chart....

static int get_mod(char *string, t_argu *arg)
{
  int len;

  len = 0;
  while (string[len] == 'h' || string[len] == 'l' || string[len] == 'j' || string[len] == 'z')
  {
    // just check for given type and flag it if the return is true
    // hh cannout be hl or jj for example 
    if (string[len] == 'h' )
        string[len + 1] == 'h' ? (arg->flags |= HH) : (arg->flags |= H);
    if (string[len] == 'l')
        string[len + 1] == 'l' ? (arg->flags |= LL) : (arg->flags |= L);
    if (arg->flags == HH || arg->flags == LL)
      len++;
    if (string[len] == 'j')
      arg->flags |= J;
    if (string[len] == 'z')
      arg->flags |= Z;
    len++;
  }
  return (len); //Distance traveled within the parsing.
}
// Specifies the number of string characters, the number of decial palces....
// or the number of sig figits to be output. 
// For numbers, precision sis the minimum number of digits to be written.
// If the value to be written is shorter than this number, the result is padded......

static int get_prec(va_list ap, char *string, t_argu *arg)
{
  int prec;
  char *num;

  // prec is initialized to 0;
  prec = 0;
  // if we are currently at a '.'
  if (string[0] == '.')
  {
    prec = 1;
    if (string[prec] == '*')
    {
      // take that argument, assign precision to this task.
      arg->precision = va_arg(ap, int);
      // increase the precision to at least 2.
      prec++;
    }
    else
    {
      // THis lets upgrab all the numbers of which we are precise to...
      while (ft_isdigit(string[prec]))
        prec++;
      if (!(num = ft_strsub(string, 1, prec)))
        return (0);
      arg->precision = (prec != 1) ? ft_atoi(num) : 0;
      free (num);
    }
  }
    return (prec);
}

// Gets the minimum number of chracters that are output. IF the number of
// Characters in the output values is less than the specified widith, blanks are added.
// to the left or the right of the values-depending on whether the left alignment is speced.

static int get_width (va_list ap, char *string, t_argu *arg)
{
  int width;
  char *num;

  width = 0;
  // If the midifier is an asterisk '*'
  if (string[width] == '*')
  {
    // Then you access the next variable argument.
    // Set it within the att to width
    arg->width = va_arg(ap, int);
    if (arg->width < 0)
    {
      arg->width *= -1; 
      arg->flags |= MINUS;
    }
    width = 1;
  }
  else
  {
    // While we get numbers...
    while (ft_isdigit(string[width]))
      width++;
    // increment save the to our string convert and return the value after free. 
    if (!width || !(num = ft_strsub(string, 0, width)))
        return (0);
    arg->width = ft_atoi(num);
    // free that num;
    free(num);
  }
  return (width);
}

// Get the flags, width, precision and len of the format. 
// returns bool yes or no whether the format is valid.
int   get_atts(char **string, va_list ap, t_argu *arg)
{
  char *init;
  int f_width;

  init = *string;
  while (get_flags(**string, arg))
      (*string)++;
// We now check for the width and have that return us the proper values.
  while ((f_width = get_width(ap, *string, arg)))
  {
    // width is returned as either a 0, 1 or the length of the characters 
    arg->flags |= WIDTH;
    // move format forward the correct number of characters in width.
    (*string) += f_width;
  }
  while ((f_width = get_prec(ap, *string, arg)))
  {
    // if precision exists bit shift flag to precision
    if (arg->precision >= 0)
        arg->flags |= PRECISION;
    (*string) += f_width;
  }
  while ((f_width = get_mod(*string, arg)))
      (*string) += f_width;
  // return if the format is moved forward further than the initial copy?
  return (*string > init);
}

// Why is this static?  bascially checks if each specifier is in the string...
// I feel like I can use strchr or something to find the character position....
static int spec_check(char c, char *str)
{
  int i;

  i = 0;

  while (str[i])
  {
      if (c == str[i])
        return (i);
    i++;
  }
  return (-1);
}

static int get_spec(char c, t_argu *arg, char *spec)
{
  int *tbl;
  int specifier;

  tbl = ft_memalloc(sizeof(int) * SPECI_SIZE);
  tbl[S] = S_BIT;
  tbl[P] = P_BIT;
  tbl[D] = D_BIT;
  tbl[I] = I_BIT;
  tbl[O] = O_BIT;
  tbl[U] = U_BIT;
  tbl[LOWER_X] = LOW_X_BIT;
  tbl[UPPER_X] = UPP_X_BIT;
  tbl[C] = C_BIT;
  // I'm not quite sure how |= gating works.
  if (((specifier = spec_check(c, spec)) != -1) && c)
    arg->flags |= tbl[specifier];
  free(tbl);
  return (specifier);
}

// parse the specifier to the following input 
int   spec_buff(va_list ap, char **string, t_argu *arg)
{
  // Specifier ends up getting set to a given bit value.
  int specifier;
  int valid;
  // storing the converted string %123.d
  char *conv;
  
  // This should already be assigned to zero
  arg->flags = 0;
  // allocate memory for our specifier string, to speci_size.
  if (!(conv = (char *)malloc(SPECI_SIZE)))
    return (0);
  conv = ft_strncpy(conv, SPECIFIERS, SPECI_SIZE);
  specifier = PRINTF_FAILURE; // Initialized to -1?
  while (**string)
  {
    // This basically if is true means it found the specifier...
    if ((spec_check(**string, conv) != -1) && (specifier = get_spec(**string, arg, conv)))
        break;
    if (!(valid = get_atts(string, ap, arg)))
        break;
  }
  free(conv);
  return (specifier);
}
int   print_str(va_list ap, t_argu *arg)
{
  int len;
  char *str;
  char *cpy;
  // We are not handling wide strings...
  // grab the string and if fails print (null)
  if (!(str = va_arg(ap, char *)))
    str = ft_strdup("(null)");
  if (arg->flags & PRECISION)
  {
    if (!(cpy = (char*)malloc(arg->precision)))
      return (0);
    cpy = ft_strncpy(cpy, str, arg->precision);
    str = cpy;
  }
  // get len of string...
  len = ft_strlen(str);
  if (!(arg->flags & MINUS))
    len = print_spaces(arg->width, len, arg->flags);
  ft_putstr(str);
  if (arg->flags & MINUS)
    len = print_spaces(arg->width, len, arg->flags);
  // printing done, return dat len.
  return (len);
}

// Get the number of digits of number and return them WOAH
// basically power..
static int num_digis(intmax_t num)
{
  int len;

  if (!num)
    return (1);
    len = num < 0 ? 1: 0;
    while (num)
    {
      num /= 10;
      len += 1;
    }
    return (len);
}
//Gotta zero in m8
int   num_zeros(t_argu *arg, int *len, int sign)
{
  int n_zeros;
  
  n_zeros = 0;
  if (arg->flags & PRECISION && arg->precision > *len - sign)
  {
    n_zeros += arg->precision - *len + sign;
    *len += n_zeros;
  }
  // If that is so then what do I do...
  if (arg->flags & WIDTH && arg->flags & ZERO && !(arg->flags & MINUS) && !(arg->flags & PRECISION) && arg->width > *len)
  {
    n_zeros += arg->width - *len;
    *len += n_zeros;
  }
  if (arg->flags & P_BIT)
    n_zeros++;
  return (n_zeros);
}
// The numbe rof spaces that must be checked out...
int  num_spaces(int arg, int wid, int *len)
{
  int n_spaces;
  n_spaces = 0;
  if (arg & WIDTH && (!(arg & ZERO) || arg & MINUS || arg & PRECISION) && wid > *len)
  {
    n_spaces += wid - *len;
    *len += n_spaces;
  }
  return (n_spaces);
}
// checks value of number based on flags..
// 1: for octal
// 2: for hex and address
// 0: for neither.
static int non_dec(uintmax_t num, int arg, int prec)
{
  if (arg & O_BIT && arg & HASH && ( num || arg & PRECISION) && !prec)
    return (1);
  else if (((arg & LOW_X_BIT || arg & UPP_X_BIT) && arg & HASH && num) || arg & P_BIT)
    return (2);
  return (0);
}
// need to print the sign
static void print_sign(intmax_t num, int arg)
{
  char sign;

  sign = 0;
  if (num > 0)
  {
      if (arg & PLUS)
          ft_putchar('+');
      else if (arg & SPACE)
        ft_putchar(' ');
  }
}
// format and print the signed numbers.
int   form_sign(intmax_t num, t_argu *arg)
{
  int len;
  int sign;
  int num_z;
  int num_s;

  len = 0;
  // Gets the given sign and returns it.
  sign = (num >= 0 && (arg->flags & PLUS || arg->flags & SPACE )) ? 1 : 0;
  // if there is precision and num is not 0
  if (!(arg->flags & PRECISION) || arg->precision || num)
    len += num_digis(num);
  len += sign;
  num_z = num_zeros(arg, &len, (num < 0 || sign));
  num_s = num_spaces(arg->flags, arg->width, &len);
  !(arg->flags & MINUS) ? ft_putnchar(' ', num_s) : 0;
  // print the sign if it applies.
  print_sign(num, arg->flags);
  ft_putnchar('0', num_z);
  if (!(arg->flags & PRECISION && !arg->precision && !num))
    ft_putunbr((num < 0) ? (-num) : (num));
  
  (arg->flags & MINUS) ? ft_putnchar(' ',num_s) : 0;
  return (len);
}

// Lets print a number because we have one of those things...
static int s_num(va_list ap, t_argu *arg)
{
  int len;

  len = 0;
  // Go for printing based on my modifiers
  if (arg->flags & J || arg->flags & Z)
    len = form_sign(va_arg(ap, intmax_t), arg);
  else if (arg->flags & LL)
    len = form_sign(va_arg(ap, long long), arg);
  else if (arg->flags & L)
    len = form_sign(va_arg(ap, long), arg);
  else if (arg->flags & HH)
    len = form_sign((char)va_arg(ap, int), arg);
  else if (arg->flags & H)
    len = form_sign((short)va_arg(ap, int), arg);
  else
    len = form_sign(va_arg(ap, int), arg);
  return (len);
}
// format unsiend number
int   form_usign(uintmax_t num, t_argu *arg, char *(*conv)(uintmax_t, int *))
{
  int len;
  int sign;
  int n_zeros;
  int n_spaces;
  char *n_conv;

  n_conv = conv(num, &len);
  sign = non_dec(num, arg->flags, arg->precision);
  if (arg->flags & LOW_X_BIT || arg->flags & P_BIT)
    ft_lower_str(n_conv);
  (arg->flags & PRECISION && !arg->precision && !num) ? len = 0 : len;
  len += sign;
  n_zeros = num_zeros(arg, &len, (sign == 2) ? 2 : 0);
  n_spaces = num_spaces(arg->flags, arg->width, &len);
  !(arg->flags & MINUS) ? ft_putnchar(' ', n_spaces) : 0;
  non_dec(num, arg->flags, arg->precision) ? ft_putchar('0') : 0;
  if (non_dec(num, arg->flags,arg->precision) > 1)
      arg->flags & UPP_X_BIT ? ft_putchar('X') : ft_putchar('x');
  ft_putnchar('0', n_zeros);
  if (!(arg->flags & PRECISION && !arg->precision && !num))
    ft_putstr(n_conv);
  // Throws error when freeing.
  // free(n_conv);
  (arg->flags & MINUS) ? ft_putnchar(' ', n_spaces) : 0;
  return (len);
}
// print the unsigned values now...
static int u_num(va_list ap, t_argu *arg)
{
  int len;

  len = 0;
  if (arg->flags & J)
    len = form_usign(va_arg(ap, uintmax_t), arg, &conv_dec);
  else if (arg->flags & Z)
    len = form_usign(va_arg(ap, size_t), arg, &conv_dec);
  else if (arg->flags & LL)
    len = form_usign(va_arg(ap, unsigned long long), arg, &conv_dec);
  else if (arg->flags & L)
    len = form_usign(va_arg(ap, unsigned long), arg, &conv_dec);
  else if (arg->flags & HH)
    len = form_usign((unsigned char)va_arg(ap, unsigned int), arg, &conv_dec);
  else if (arg->flags & H)
    len = form_usign((unsigned short)va_arg(ap, unsigned int), arg, &conv_dec);
  else
    len = form_usign(va_arg(ap, unsigned int), arg, &conv_dec);
  return (len);
}
// print that simple ass numbro
int     print_dec(va_list ap, t_argu *arg)
{
  int len;
  int flags;

  len = 0;
  flags = arg->flags;
  if (flags & D_BIT || flags & I_BIT)
    len = s_num(ap, arg);
  if (flags & U_BIT)
    len = u_num(ap, arg);
  return (len);
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
// printing hex now is super important...
int   print_hex(va_list ap, t_argu *arg)
{
    int len;
  if (arg->flags & P_BIT)
      len = form_usign((uintmax_t)va_arg(ap, void *), arg, &conv_hex);
  else if (arg->flags & J)
    len = form_usign(va_arg(ap, uintmax_t), arg, &conv_hex);
  else if (arg->flags & Z)
    len = form_usign(va_arg(ap, size_t), arg, &conv_hex);
  else if (arg->flags & LL)
    len = form_usign(va_arg(ap, unsigned long long), arg, &conv_hex);
  else if (arg->flags & L)
    len = form_usign(va_arg(ap, unsigned long), arg, &conv_hex);
  else if (arg->flags & HH)
    len = form_usign((unsigned char)va_arg(ap, unsigned int), arg, &conv_hex);
  else if (arg->flags & H)
    len = form_usign((unsigned short)va_arg(ap, unsigned int), arg, &conv_hex);
  else
    len = form_usign(va_arg(ap, unsigned int), arg, &conv_hex);
  return (len);
}
// prints out a a character.
int   print_char(va_list ap, t_argu *arg)
{
  int len;
  char c;

  c = va_arg(ap, int);
  //len should be just one...
  len = 1;
  if (!(arg->flags & MINUS))
    len = print_spaces(arg->width, len, arg->flags);
  ft_putchar(c);
  if (arg->flags & MINUS)
    len = print_spaces(arg->width, len, arg->flags);
  return (len);
}
static int print_no_spec(char c, t_argu *arg)
{
  int len;
  if (!(arg->flags & MINUS))
    len = print_spaces(arg->width, 1, arg->flags);
  ft_putchar(c);
  if (arg->flags & MINUS)
    len = print_spaces(arg->width, 1, arg->flags);
  return (len);
}
// Now that most of the flags have been collected each specifier can be printed.
static int print_spec(char string, va_list ap, t_argu *arg, int i)
{
  int   print;

  print = 0;
  if (i == S)
    print = print_str(ap, arg);
  else if (i == D || i == I || i == U)
    print = print_dec(ap, arg);
  else if (i == O)
    print = print_oct(ap, arg);
  else if (i == P || i == LOWER_X || I == UPPER_X)
    print = print_hex(ap, arg);
  else if (i == C)
    print = print_char(ap, arg);
  else
    print = print_no_spec(string, arg);
  return (print);
}
// Same as print_stdout
static int print_buff(char *string[], va_list ap)
{
  // the current specifier holder
  int specifier;
  // attribute holder.
  t_argu arg;

  //initialize current specifier to 0's.
  arg.flags = 0;
  arg.width = 0;
  arg.precision = 0;
  // return the specifier found from the given % flag.
  specifier = spec_buff(ap, (char **)string, &arg);
  if (!**string)
    return (-1);
  // return the specifier function for formatting???????
  // Flags and modifiers gathered, time to print.
  return (print_spec((char)**string, ap, &arg, specifier));
}
// Takes in a string*, and a variable number of arguments.
int ft_printf(char* string, ...)
{
  // We return character count as a part of the function.
  int   count;
  // Length is the a container for count
  int   len;
  // Our variable list to be be iterated through.
  va_list ap;
  len = 0;
  count = 0;
  va_start(ap, string);
  while (*string)
  {
    // If we run into the flag.
    if (*string == '%')
    {
        // Move the character forward.
        string += 1;
        // check if the buffer is returning prorperly after print attempt.
        if ((len = print_buff(&string, ap)) == PRINTF_FAILURE)
            break ;
        count += len;
    }
    else
    {
      ft_putchar(*string);
      count += 1;
    }
    string += 1;
  }  
  // exit the list.
  va_end(ap);
  return (count);
}

int main()
{
  unsigned int og = 0;
  unsigned int mg = 0;
  char *str = "BOB";
  char chr = 'b';
  int xnum = 123;
  int onum = 127;
  unsigned int unum = UINT_MAX;
  og = printf("OG Test 1\n");
  mg = ft_printf("MY Test 2\n");
  // ----------------------
  og += printf("OG Number: %d\n", 24);
  mg += ft_printf("MY Number: %d\n", 42);
  // ----------------------
  og += printf("OG Long: %ld\n", LONG_MAX);
  mg += ft_printf("MY Long: %ld\n", LONG_MAX);
  // ----------------------
  og += printf("OG Long Long: %lld\n", __LONG_LONG_MAX__);
  mg += ft_printf("MY Long Long: %lld\n", __LONG_LONG_MAX__);
  // ----------------------
  og += printf("OG Short: %hd\n", (short)SHRT_MAX);
  mg += ft_printf("MY Short: %hd\n", (short)SHRT_MAX);
  // ----------------------
  og += printf("OG Short: %hhd\n", (char)127);
  mg += ft_printf("MY Short: %hhd\n", (char)127);
  // ----------------------
  og += printf("OG String: %s", "Test\n");
  mg += ft_printf("MY String: %s", "Test\n");
  // ----------------------
  og += printf("OG pointer: %p\n", &og);
  mg += ft_printf("MY pointer: %p\n", &og);
  printf("\t\t\t---> my   length: %d <---\n", ft_printf("%+-d %s %c %x  ~random-words./\'\\ %o %u %p\n", SHRT_MAX, str, chr, xnum, onum, unum, str));
  printf("\t\t\t---> real length: %d <---\n", printf("%+-d %s %c %x  ~random-words./\'\\ %o %u %p\n",SHRT_MAX, str, chr, xnum, onum, unum, str));
  printf("\n");
  //const char * y = "monkeys";
  //printf ("<%d> is not justified.\n", x);

  // printf ("<%5d> is right-justified.\n", x);
  // printf ("<%-5d> The minus sign makes it left-justified.\n", x);
  // printf ("'%s' is not justified.\n", y);
  // printf ("'%10s' is right-justified.\n", y);
  // printf ("'%-10s' is left-justified using a minus sign.\n", y);
  printf("Printf: %d\n", og);
  printf("FT_Printf: %d\n", mg);
  return (0);
}