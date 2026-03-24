#include "../incl/RPN.hpp"

bool	is_op(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return (true);
	return (false);
}

int	perform_op(char op, std::stack<int>& vals, bool *zero_div)
{
	
	int	val2 = vals.top();
	vals.pop();
	int	val1 = vals.top();
	vals.pop();

	if (op == '+')
		return (val1 + val2);
	else if (op == '-')
		return (val1 - val2);
	else if (op == '*')
		return (val1 * val2);
	else
	{
		if (val2 == 0)
		{
			*zero_div = true;
			return (0);
		}
		return (val1 / val2);
	}
		
}

bool	read_arg(char* values)
{
	std::stack<int>	vals;
	char 	*end;
	long	num;
	int		res;

	while (values[0])
	{
		errno = 0;
		num = std::strtol(values, &end, 10);
		if (errno == ERANGE || num > INT_MAX || num < INT_MIN)
		{
			std::cerr << "Error: value out of range.\n";
			return (false);
		}
		else if (num == 0 && end == values)
		{
			if (!(is_op(values[0]) && (values[1] == ' ' || !values[1])))
			{
				std::cerr << "Error: invalid operator.\n";
				return (false);
			}
			else if (vals.size() < 2)
			{
				std::cerr << "Error: not enough arguments preceding operator.\n";
				return (false);	
			}
			
			bool zero_div = false;
			res = perform_op(values[0], vals, &zero_div);
			if (zero_div)
			{
				std::cerr << "Error: zero division.\n";
				return (false);	
			}
			else if (!values[1] && vals.size() == 0)
			{
				std::cout << res << std::endl;
				return (true);
			}
			else if (!values[1])
			{
				std::cerr << "Error: reached end of arguments before completing calculation.\n";
				return (false);	
			}
			vals.push(res);
			values += 2;
			continue ;
		}
		else if (num >= 10 || num <= -10)
		{
				std::cerr << "Error: values exceed 10 or -10.\n";
				return (false);		
		}
		else if (*end != 0 && *end != ' ')
		{
			std::cerr << "Error: only integers are accepted.\n";
			return (false);
		}
		vals.push(num);
		if (values[0] == '+' || values[0] == '-')
			values ++;
		values += 2;
	}
	std::cerr << "Error: reached end of arguments before completing calculation.\n";
	return (false);
}
