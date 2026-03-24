#include "../incl/BitcoinExchange.hpp"

bool read_validate_data(std::ifstream &data_file, std::map <Date, double> *data)
{
	std::string	buf;
	std::getline(data_file, buf);
	if (buf != "date,exchange_rate")
	{
		std::cerr << "Invalid data header.\n";
		return false;
	}

	while (getline(data_file, buf))
	{
		std::stringstream ss(buf);
		std::string tmp;
		
		std::getline(ss, tmp, ',');
		std::string date = tmp;
		Date d;

		try
		{
			d = Date(date);
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << " => " << date << '\n';
			return (false);
		}

		errno = 0;
		char* end;
		std::getline(ss, tmp);
		const char* start = tmp.c_str();
		double num = strtod(start, &end);
		
		if (errno == ERANGE)
		{
			std::cerr << "Error: out of range.\n";
			return (false);					
		}
		else if (*end || end == start || std::isnan(num))
		{
			std::cerr << "Error: invalid number.\n";
			return (false);	
		}
		else if (num < 0)
		{
			std::cerr << "Error: negative number.\n";
			return (false);
		}
		else if (num > INT_MAX)
		{
			std::cerr << "Error: too large a number.\n";
			return (false);
		}
		(*data)[d] = num;
	}
	return (true);
}

void	lookup_vals(std::ifstream &data_file, const std::map <Date, double> *data)
{
	std::string	buf;
	std::getline(data_file, buf);

	if (buf != "date | value")
	{
		std::cerr << "Invalid input header.\n";
		return ;
	}

	while (getline(data_file, buf))
	{
		std::stringstream ss(buf);
		std::string tmp;
		
		std::getline(ss, tmp, '|');
		std::string date = tmp;
		Date d;

		try
		{
			d = Date(date);
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << " => " << date << '\n';
			continue ;
		}

		errno = 0;
		char* end;
		std::getline(ss, tmp);
		const char* start = tmp.c_str();
		double num = strtod(start, &end);
	
		if (errno == ERANGE)
			std::cout << "Error: out of range.\n";
		else if (*end || end == start || std::isnan(num))
			std::cout << "Error: invalid number.\n";
		else if (num <= 0)
			std::cout << "Error: not a positive number.\n";
		else if (num >= 1000)
			std::cout << "Error: too large a number.\n";
		else
		{
			std::map<Date, double>::const_iterator it = (*data).begin();
			if (d < it->first)
				std::cout << "Error: data preceeds records.\n";
			else
			{
				if ((*data).count(d) != 0)
				{
					it = (*data).find(d);
					std::cout <<  d << " => " << num << " = " << it->second * num << std::endl;
				
				}
				else
				{
					it = data->lower_bound(d);
					std::cout <<  d << " => " << num << " = " << (--it)->second * num 
						<< " (estimation based on next available date: " << (it)->first << ")" << std::endl;
				}
			}
		}
	
	}
}