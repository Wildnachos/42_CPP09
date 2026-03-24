#include "incl/BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Invalid amount of arguments" << std::endl;
		return (1);
	}
	
	(void) argv;
	std::ifstream data_file("data/data.csv");
	if (!data_file.is_open())
	{
		std::cerr << "Error opening data.csv for reading" << std::endl;
		return (1);
	}
	
	std::map <Date, double> data;
	if (!read_validate_data(data_file, &data))
		return (1);
	if (data.empty())
	{
		std::cerr << "Error: no data." << std::endl;
		data_file.close();
		return (1);
	}

	data_file.close();
	
	std::ifstream input(argv[1]);
	if (!input.is_open())
	{
		std::cerr << "Error opening user input for reading" << std::endl;
		return (1);
	}

	lookup_vals(input, &data);
	input.close();

	return (0);
}
