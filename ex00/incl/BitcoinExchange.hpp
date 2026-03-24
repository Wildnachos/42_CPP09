#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstring>
#include <stdlib.h> 
#include <climits>
#include <cmath>
#include "Date.hpp"

bool 	read_validate_data(std::ifstream &data_file, std::map <Date, double> *data);
void	lookup_vals(std::ifstream &data_file, const std::map <Date, double> *data);
