#include "main.h"

/**
 * get_count - Computes the total number of characters to be printed
 *             for a given integer.
 * @d: The integer to compute the count for.
 * @plus_flag: A flag indicating if the plus sign should be printed.
 * @space_flag: A flag displays space should be printed instead of a plus sign.
 *
 * Return: The total number of characters to be printed for `d`.
 */
static int get_count(long int d, int plus_flag, int space_flag)
{
	int count = 0;

	if (d == LONG_MIN)
		count = 19;
	else
	{
		for (long int copy = (d < 0) ? -d : d; copy > 0; copy /= 10)
			count++;
	}
	count += (d == 0) ? 1 : 0;
	count += (d < 0) ? 1 : 0;
	count += (plus_flag == 1 && d >= 0) ? 1 : 0;
	count += (space_flag == 1 && d >= 0) ? 1 : 0;

	return (count);
}

/**
 * print_integer - Prints an integer to the output buffer.
 * @d: The integer to print.
 * @output: The output buffer.
 * @prec: The precision modifier.
 * @flags: The flag modifiers.
 * @len: The length modifier.
 * @pad: The padding character.
 * @plus_flag: A flag with plus sign should be printed.
 * @space_flag: A flag displays space should be printed instead of a plus sign.
 *
 * Return: The number of bytes stored to the output buffer.
 */
static unsigned int print_integer(long int d, buffer_t *output,
		int prec, unsigned char flags, unsigned char len,
		char pad, int plus_flag, int space_flag)
{
	unsigned int ret = 0;

	if (!(d == 0 && prec == 0))
		ret += convert_sbase(output, d, "0123456789", flags, 0, prec);

	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}

/**
 * convert_di - Converts an argument to a signed int and
 *              stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_di(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	long int d;
	unsigned int ret = 0;
	char pad, space = ' ', neg = '-', plus = '+';
	int plus_flag = (PLUS_FLAG == 1 && d >= 0);
	int space_flag = (SPACE_FLAG == 1 && d >= 0);

	if (len == LONG)
		d = va_arg(args, long int);
	else
		d = va_arg(args, int);
	if (len == SHORT)
		d = (short)d;

	/* Handle space flag */
	if (space_flag)
		ret += _memcpy(output, &space, 1);

	/* Handle width */
	int count = get_count(d, plus_flag, space_flag

