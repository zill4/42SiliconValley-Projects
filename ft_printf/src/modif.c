    #include "../includes/ft_printf.h"
    char *leftJustify(char *str, long min_p, long max_p, int hasPrec)
    {
        char *final;

        final = str;
        return (final);
    }
    char *setSign(char *str, int sign)
    {
        char *final;
        
        final = str;
        if (sign > 0)
            final[0] = '+';
        else
            final[0] = '-';
    }
    char *genModString(char *str, va_list ap, int *count)
    {
        // Apply modification in order of precidence. 
        // * first, second root modifiers such as l,ll, h, hh, and L.
        enum rootFlag { l, ll, h , hh, L };
        unsigned rf; // Root flag identifier.
        char *final; // The final string value.
        int i;
        long min_p;
        long max_p;
        long asterisk;
        int hasPrec;
        int sign;

        // Sign of determined root.
        sign = 0;
        // hasPrec is Has Precision depending on position this will give a string leading or ending zeros if it is a float or not.
        hasPrec = 0;
        // min and max precision/
        min_p = 0;
        max_p = 0;
        // Root flag
        rf = 0;
        // asterisk value
        asterisk = 0;
        i = 0;
        // For the length of String, must find the asterisk value first.
        while (str[i])
        {
            if (str[i] == '*'){
                asterisk = va_arg(ap, long);
            }
            i++;
        }
        i = 0;
        // For the length of String, must find the root flag identifiers.
        while (str[i])
        {
            if (str[i] == 'l')
            {
                str[i] = 'X';
                if (rf < 2)
                    rf++;
                else
                    printf("\nERROR!\n");
            }
            if (str[i] == 'L')
            {
                str[i] = 'X';
                if (rf == 0)
                    rf = 5;
                else
                    printf("\nERROR!\n");
            }
            if (str[i] == 'h')
            {
                str[i] = 'X';
                if (rf == 0)
                    rf = 3;
                else if (rf == 3)
                    rf = 4;
                else 
                    printf("\nERROR!\n");
            }
            i++;
        }
        i = 0;
        // For the remainder of the string the last important find is the precision indicator.
        while (str[i])
        {
            if (str[i] == '.')
            {
                if (ft_isdigit(str[i - 1]) || str[i - 1] == '*')
                {
                    // The minimum precision element
                    if (str[i - 1] == '*')
                        min_p = asterisk;
                    else if (ft_isdigit(str[i - 1]))
                        min_p = ft_atoi(str[i]);
                    // Cross out items that we have charted.
                    str[i - 1] = 'X';
                }
                if (ft_isdigit(str[i + 1]) || str[i + 1] == '*')
                {
                    if (str[i + 1] == '*')
                        max_p = asterisk;
                    else if (ft_isdigit(str[i + 1]))
                        max_p = ft_atoi(str[i]);
                    // Cross out items that we have charted.
                    str[i + 1] = 'X';
                }
                // Cross out items that we have charted.
                str[i] = '.';
            }
        }
        i = 0;
        // Now we can check all other no stipulating flags.
        while(str[i])
        {
            if (str[i] == '-')
                leftJustify(final, min_p, max_p, hasPrec);
            else if (str[i] == '+')
                setSign(final, sign);
            else if (str[i] == 'f')
                pf_atoib(va_arg(ap, float), 16, count); //Placeholder.
            // else if (str[i] == '0')

            // else if (ft_isdigit(str[i]))
            //     //Do something
            // else if (str[i] == '#')
            //     //Do something
            // else if (str[i] == ' ')
            //     //Do something
        }
    }
