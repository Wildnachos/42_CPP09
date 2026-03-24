#include "../incl/PmergeMe.hpp"

Box_vect* init_box_vect(int i)
{
	Box_vect* res = new Box_vect;
	
	if (!res)
		return (0);
	res->i_lead = i;
	return (res);
}

void free_boxes_vect(std::vector<Box_vect*> arr)
{
	for (std::vector<Box_vect*>::iterator it = arr.begin(); it != arr.end(); it++)
		delete *it;
}

bool	check_followers_vect(std::vector <Box_vect*> &arr)
{
	size_t i = 0;
	while (i < arr.size())
	{
		if (arr[i]->Followers.size() > 0)
			return (true);
		i++;
	}
	return (false);
}

int	get_lim_vect(std::vector<Box_vect*> &arr, Box_vect* lim)
{
	int i = 0;
	std::vector<Box_vect*>::iterator it = arr.begin();
	while (*it != lim)
	{
		it++;
		i++;
	}

	return i;
}

void insert_vect(std::vector <Box_vect*> &tmp, Box_vect* box, Box_vect* lim)
{
	int size = get_lim_vect(tmp, lim);
	int	check;
	int start = 0;
	int end = size - 1;

	if (size == 0)
	{
		tmp.insert(tmp.begin(), box);
		return ;
	}

	while (size > 1)
	{		
		check = (size / 2) + start;
		if (size % 2 == 0)
			check--;

		if (box->i_lead < tmp[check]->i_lead)
			end = check;
		else
			start = check + 1;
		size = end - start + 1;
	}

	if (box->i_lead < tmp[start]->i_lead)
		tmp.insert(tmp.begin() + start, box);
	else
		tmp.insert(tmp.begin() + start + 1, box);
}

std::string	print_vect(std::vector <Box_vect*> &arr)
{
	std::ostringstream res;

	size_t i = 1;
	res << arr[0]->i_lead;
	while (i < arr.size())
	{
		res << " " << arr[i]->i_lead;
		i++;
	}
	return (res.str());
}

void generate_jacob_vect(std::vector<int> &res, int limit, int count)
{
	if (res[count - 1] >= limit)
		return ;
	res.push_back(2 * res[count - 1] + pow(-1, count));
	generate_jacob_vect(res, limit, ++count);
}

std::vector<int> generate_indexes_vect(std::vector<int> &jacob, int limit)
{
	std::vector<int> res;
	int ind = 1;
	int upper = jacob[ind];
	int lower = jacob[ind - 1];
	int start = upper;

	while ((int) res.size() < limit - 1)
	{
		while (start > limit)
			start--;
		if (start == lower)
		{
			ind += 1;
			upper = jacob[ind];
			lower = jacob[ind - 1];
			start = upper;
			continue ;
		}
		res.push_back(start - 1);
		start--;		
	}

	return (res);
}

void recursive_pairing_vect(std::vector <Box_vect*> &arr)
{
	if (arr.size() == 1)
		return ;

	int size = arr.size();
	int i = 0;
	std::vector<Box_vect*> tmp;
	while (i < size)
	{
		if (i % 2 == 0 && i != size - 1)
		{
			i++;
			continue ;
		}
		else if (i % 2 == 0 && i == size - 1)
		{
			arr[i]->Followers.push_back(0);
			tmp.push_back(arr[i]);
			i++;
			continue ;
		}
		if (arr[i]->i_lead < arr[i - 1]->i_lead)
		{
			arr[i - 1]->Followers.push_back(arr[i]);
			tmp.push_back(arr[i - 1]);
		}
		else
		{
			arr[i]->Followers.push_back(arr[i-  1]);
			tmp.push_back(arr[i]);			
		}
		i++;
	}
	arr = tmp;

	if (arr.size() != 1)
		recursive_pairing_vect(arr);

	size = arr.size();
	i = 0;
	tmp.clear();

	while (i < size)
	{
		std::vector <Box_vect*>::reverse_iterator it = arr[i]->Followers.rbegin();
		if (!(*it))
			arr[i]->Followers.pop_back();
		else
		{
			tmp.push_back(*it);
			tmp.push_back(arr[i]);
			arr[i]->Followers.pop_back();
		}
		i++;
	}



	insert_vect(arr, tmp[0], tmp[1]);

	if (tmp.size() > 2)
	{
		std::vector<int> jacob;
		jacob.push_back(1);
		generate_jacob_vect(jacob, tmp.size() / 2, 1);
		jacob.erase(jacob.begin());

		std::vector<int> indexes = generate_indexes_vect(jacob, tmp.size() / 2);
		size_t j = 0;
		while (j < indexes.size())
		{
			insert_vect(arr, tmp[indexes[j] * 2], tmp[(indexes[j] * 2) + 1]);
			j++;
		}
	}
	return ;
}

Box_deq* init_box_deq(int i)
{
	Box_deq* res = new Box_deq;
	
	if (!res)
		return (0);
	res->i_lead = i;
	return (res);
}

void free_boxes_deq(std::deque<Box_deq*> arr)
{
	for (std::deque<Box_deq*>::iterator it = arr.begin(); it != arr.end(); it++)
		delete *it;
}

bool	check_followers_deq(std::deque <Box_deq*> &arr)
{
	size_t i = 0;
	while (i < arr.size())
	{
		if (arr[i]->Followers.size() > 0)
			return (true);
		i++;
	}
	return (false);
}

int	get_lim_deq(std::deque<Box_deq*> &arr, Box_deq* lim)
{
	int i = 0;
	std::deque<Box_deq*>::iterator it = arr.begin();
	while (*it != lim)
	{
		it++;
		i++;
	}
	return i;
}

void insert_deq(std::deque <Box_deq*> &tmp, Box_deq* box, Box_deq* lim)
{
	int size = get_lim_deq(tmp, lim);
	int	check;
	int start = 0;
	int end = size - 1;

	if (size == 0)
	{
		tmp.insert(tmp.begin(), box);
		return ;
	}

	while (size > 1)
	{		
		check = (size / 2) + start;
		if (size % 2 == 0)
			check--;

		if (box->i_lead < tmp[check]->i_lead)
			end = check;
		else
			start = check + 1;
		size = end - start + 1;
	}

	if (box->i_lead < tmp[start]->i_lead)
		tmp.insert(tmp.begin() + start, box);
	else
		tmp.insert(tmp.begin() + start + 1, box);
}

std::string	print_deq(std::deque <Box_deq*> &arr)
{
	std::ostringstream res;

	size_t i = 1;
	res << arr[0]->i_lead;
	while (i < arr.size())
	{
		res << " " << arr[i]->i_lead;
		i++;
	}
	return (res.str());
}

void generate_jacob_deq(std::deque<int> &res, int limit, int count)
{
	if (res[count - 1] >= limit)
		return ;
	res.push_back(2 * res[count - 1] + pow(-1, count));
	generate_jacob_deq(res, limit, ++count);
}

std::deque<int> generate_indexes_deq(std::deque<int> &jacob, int limit)
{
	std::deque<int> res;
	int ind = 1;
	int upper = jacob[ind];
	int lower = jacob[ind - 1];
	int start = upper;

	while ((int) res.size() < limit - 1)
	{
		while (start > limit)
			start--;
		if (start == lower)
		{
			ind += 1;
			upper = jacob[ind];
			lower = jacob[ind - 1];
			start = upper;
			continue ;
		}
		res.push_back(start - 1);
		start--;		
	}

	return (res);
}

void recursive_pairing_deq(std::deque <Box_deq*> &arr)
{
	if (arr.size() == 1)
		return ;

	int size = arr.size();
	int i = 0;
	std::deque<Box_deq*> tmp;
	while (i < size)
	{
		if (i % 2 == 0 && i != size - 1)
		{
			i++;
			continue ;
		}
		else if (i % 2 == 0 && i == size - 1)
		{
			arr[i]->Followers.push_back(0);
			tmp.push_back(arr[i]);
			i++;
			continue ;
		}
		if (arr[i]->i_lead < arr[i - 1]->i_lead)
		{
			arr[i - 1]->Followers.push_back(arr[i]);
			tmp.push_back(arr[i - 1]);
		}
		else
		{
			arr[i]->Followers.push_back(arr[i-  1]);
			tmp.push_back(arr[i]);			
		}
		i++;
	}
	arr = tmp;

	if (arr.size() != 1)
		recursive_pairing_deq(arr);

	size = arr.size();
	i = 0;
	tmp.clear();

	while (i < size)
	{
		std::deque <Box_deq*>::reverse_iterator it = arr[i]->Followers.rbegin();
		if (!(*it))
			arr[i]->Followers.pop_back();
		else
		{
			tmp.push_back(*it);
			tmp.push_back(arr[i]);
			arr[i]->Followers.pop_back();
		}
		i++;
	}

	insert_deq(arr, tmp[0], tmp[1]);

	if (tmp.size() > 2)
	{
		std::deque<int> jacob;
		jacob.push_back(1);
		generate_jacob_deq(jacob, tmp.size() / 2, 1);
		jacob.erase(jacob.begin());

		std::deque<int> indexes = generate_indexes_deq(jacob, tmp.size() / 2);
		size_t j = 0;
		while (j < indexes.size())
		{
			insert_deq(arr, tmp[indexes[j] * 2], tmp[(indexes[j] * 2) + 1]);
			j++;
		}
	}
	return ;
}

