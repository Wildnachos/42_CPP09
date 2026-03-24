#include "incl/RPN.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: invalid amount of arguments\n";
		return (1);
	}

	if (!read_arg(argv[1]))
		return (1);
	return (0);
}
