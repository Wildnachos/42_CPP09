#pragma once
#include <vector>
#include <iostream>
#include <math.h>
#include <deque>
#include <sstream>

struct Box_vect
{
	int		i_lead;
	std::vector <Box_vect*> Followers;
};

struct Box_deq
{
	int		i_lead;
	std::deque <Box_deq*> Followers;
};

Box_vect* 		init_box_vect(int i);
void 			recursive_pairing_vect(std::vector <Box_vect*> &arr);
std::string		print_vect(std::vector <Box_vect*> &arr);
void 			free_boxes_vect(std::vector<Box_vect*> arr);

Box_deq* 		init_box_deq(int i);
void 			recursive_pairing_deq(std::deque <Box_deq*> &arr);
std::string		print_deq(std::deque <Box_deq*> &arr);
void 			free_boxes_deq(std::deque<Box_deq*> arr);