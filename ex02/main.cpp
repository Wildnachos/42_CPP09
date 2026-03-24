#include <iostream>
#include <vector>
#include <deque>
#include <ctime>
#include <cstring>
#include <climits>
#include <algorithm>
#include <cerrno>
#include <iomanip>
#include "incl/PmergeMe.hpp"

std::string join_str(int argc, char **argv)
{
	std::string start(argv[1]);
	if (argc == 2)
		return (start);
	int i = 2;
	while (i < argc)
	{
		start += " ";
		start += argv[i];
		i++;
	}
	return (start);
}

std::vector <Box_vect*> create_vect(char *str)
{
	std::vector <Box_vect*> res;
	char *token = std::strtok(str, " ");
	std::vector <int> vals;

	long num;
	char *end;

	while (token != 0)
	{
		errno = 0;
		num = std::strtol(token, &end, 10);
		if (errno == ERANGE || num > INT_MAX || num < INT_MIN)
		{
			std::cerr << "Error: value out of range.\n";
			free_boxes_vect(res);
			res.clear();
			return (res);
		}
		else if (num == 0 && end == token)
		{
			std::cerr << "Error: invalid arg.\n";
			free_boxes_vect(res);
			res.clear();
			return (res);
		}
		else if (num <= 0 || (*end != '\0' && *end != ' '))
		{
			std::cerr << "Error: only positive integers are accepted.\n";
			free_boxes_vect(res);
			res.clear();
			return (res);
		}
		else if (find(vals.begin(), vals.end(), num) != vals.end())
		{
			std::cerr << "Error: duplicate value.\n";
			free_boxes_vect(res);
			res.clear();
			return (res);
		}
		vals.push_back(num);
		Box_vect* tmp = init_box_vect(num);
		if (!tmp)
		{
			std::cerr << "Error: memory allocation\n";
			free_boxes_vect(res);
			res.clear();
			return (res);
		}
		res.push_back(tmp);
		token = std::strtok(0, " ");
	}
	if (res.size() == 0)
		std::cerr << "Error: no args.\n";
	return (res);
}

std::deque <Box_deq*> create_deq(char *str)
{
	std::deque <Box_deq*> res;
	char *token = std::strtok(str, " ");
	std::deque <int> vals;

	long num;
	char *end;

	while (token != 0)
	{
		errno = 0;
		num = std::strtol(token, &end, 10);
		if (errno == ERANGE || num > INT_MAX || num < INT_MIN)
		{
			std::cerr << "Error: value out of range.\n";
			free_boxes_deq(res);
			res.clear();
			return (res);
		}
		else if (num == 0 && end == token)
		{
			std::cerr << "Error: invalid arg.\n";
			free_boxes_deq(res);
			res.clear();
			return (res);
		}
		else if (num <= 0 || (*end != '\0' && *end != ' '))
		{
			std::cerr << "Error: only positive integers are accepted.\n";
			free_boxes_deq(res);
			res.clear();
			return (res);
		}
		else if (find(vals.begin(), vals.end(), num) != vals.end())
		{
			std::cerr << "Error: duplicate value.\n";
			free_boxes_deq(res);
			res.clear();
			return (res);
		}
		vals.push_back(num);
		Box_deq* tmp = init_box_deq(num);
		if (!tmp)
		{
			std::cerr << "Error: memory allocation\n";
			free_boxes_deq(res);
			res.clear();
			return (res);
		}
		res.push_back(tmp);
		token = std::strtok(0, " ");
	}
	if (res.size() == 0)
		std::cerr << "Error: no args.\n";
	return (res);
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: no arguments provided.\n";
		return (1);
	}
	
	std::string arg = join_str(argc, argv);
	char *arg_vect = new char[arg.size() + 1];
	char *arg_deq = new char[arg.size() + 1];
	char *arg_demo = new char [arg.size() + 1];

	arg.copy(arg_vect, arg.size(), 0);
	arg_vect[arg.size()] = 0;

	arg.copy(arg_demo, arg.size(), 0);
	arg_demo[arg.size()] = 0;

	arg.copy(arg_deq, arg.size(), 0);
	arg_deq[arg.size()] = 0;

	std::vector <Box_vect*> demo = create_vect(arg_demo);
	if (demo.size() == 0)
	{
		delete[] arg_vect;
		delete[] arg_deq;
		delete[] arg_demo;
		return (1);
	}
	std::clock_t	start = clock();
	
	std::vector <Box_vect*> arr = create_vect(arg_vect);
	
	int size_vect = arr.size();
	if (size_vect == 0)
	{
		delete[] arg_vect;
		delete[] arg_deq;
		delete[] arg_demo;
		return (1);
	}

	recursive_pairing_vect(arr);
	std::string res_vect = print_vect(arr);
	free_boxes_vect(arr);

	std::clock_t end = clock();

	double duration_vect = double(end - start) / double(CLOCKS_PER_SEC);

	start = clock();
	std::deque <Box_deq*> arr2 = create_deq(arg_deq);
	int size_deq = arr2.size();
	if (size_deq == 0)
	{
		delete[] arg_vect;
		delete[] arg_deq;
		delete[] arg_demo;
		return (1);
	}

	recursive_pairing_deq(arr2);
	std::string res_deq = print_deq(arr2);
	free_boxes_deq(arr2);

	end = clock();
	double duration_deq = double(end - start) / double(CLOCKS_PER_SEC);
	delete[] arg_vect;
	delete[] arg_deq;
	delete[] arg_demo;
	if (res_vect != res_deq)
	{
		std::cerr << "Oops! my sort doesn't work :(\n";
		return (1);
	}

	std::cout << "Before: " << print_vect(demo) << std::endl;
	free_boxes_vect(demo);
	std::cout << "After:  " << res_deq << std::endl;

	std::cout << std::setprecision(7);
	std::cout << "Time to process a range of " << size_vect << " elements with std::vector : " << duration_vect * 1000000 << " us\n";
	std::cout << "Time to process a range of " << size_deq << " elements with std::deque : " << duration_deq * 1000000 << " us\n";

}
