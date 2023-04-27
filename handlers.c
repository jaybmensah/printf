#include "main.h"

/**
 * handle_flags - Determines if a flag exists in a format specifier string.
 * @flag: A pointer to a string containing the format specifier flag.
 * @index: A pointer to an integer containing the index of the flag character.
 * Return: 1 if the flag exists, and 0 otherwise.
 */
unsigned char handle_flags(const char *flag, char *index)
{
	int i, j;
	unsigned char ret = 0;
	flag_t flags[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', NEG},
		{0, 0}
	};

	for (i = 0; flag[i]; i++)
	{
		for (j = 0; flags[j].flag != 0; j++)
		{
			if (flag[i] == flags[j].flag)
			{
				(*index)++;
				if (ret == 0)
					ret = flags[j].value;
				else
					ret |= flags[j].value;
				break;
			}
		}
		if (flags[j].value == 0)
			break;
	}

	return (ret);
}

/**
 * handle_length - Determines if a length mod exists in a format specifier str.
 * @modifier: A pointer to a string containing the format specifier modifier.
 * @index: A pointer to an integer containing the index of the modifier
 * character.
 * Return: 1 if the modifier exists, and 0 otherwise.
 */
unsigned char handle_length(const char *modifier, char *index)
{
	if (*modifier == 'h')
	{
		(*index)++;
		return (SHORT);
	}

	else if (*modifier == 'l')
	{
		(*index)++;
		return (LONG);
	}

	return (0);
}

/**
 * handle_width - Parses the width specifier from a format specifier
 * string and returns its value.
 * @args: A va_list containing the arguments for the format specifier.
 * @modifier: A pointer to a string containing the format specifier modifier.
 * @index: A pointer to an integer containing the index of the width
 * specifier character.
 * Return: The width specifier value as an integer.
 */
int handle_width(va_list args, const char *modifier, char *index)
{
	int value = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * handle_precision - Parses the precision specifier from a format
 * specifier string and returns its value.
 * @args: A va_list containing the arguments for the format specifier.
 * @modifier: A pointer to a string containing the format specifier modifier.
 * @index: A pointer to an integer containing the index of the precision
 * specifier character.
 * Return: The precision specifier value as an integer.
 */
int handle_precision(va_list args, const char *modifier, char *index)
{
	int value = 0;

	if (*modifier != '.')
		return (-1);

	modifier++;
	(*index)++;

	if ((*modifier <= '0' || *modifier > '9') &&
	     *modifier != '*')
	{
		if (*modifier == '0')
			(*index)++;
		return (0);
	}

	while ((*modifier >= '0' && *modifier <= '9') ||
	       (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * handle_specifiers - Handle format specifiers for printf function
 * @specifier: The specifier to be handled
 * @char: value of character
 * @int: value of int
 * Return: unsigned int (*)(va_list, buffer_t *, unsigned char,
 * int, int, unsigned char)
 */
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
unsigned char, int, int, unsigned char)
{
	int i;
	converter_t converters[] = {
			{'c', convert_c},
			{'s', convert_s},
			{'d', convert_di},
			{'i', convert_di},
			{'%', convert_percent},
			{'b', convert_b},
			{'u', convert_u},
			{'o', convert_o},
			{'x', convert_x},
			{'X', convert_X},
			{'S', convert_S},
			{'p', convert_p},
			{'r', convert_r},
			{'R', convert_R},
			{0, NULL}
	};

	for (i = 0; converters[i].func; i++)
	{
		if (converters[i].specifier == *specifier)
			return (converters[i].func);
	}

	return (NULL);
}
