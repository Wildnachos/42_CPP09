#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>

class  Date
{
	private:
		int year;
		int month;
		int day;

		void validate();
		bool isLeap(int year);

	public:
		Date();
		Date(std::string str);
		~ Date();

		Date(const Date& other);
		Date& operator=(const Date& other);

		bool operator<(const Date& other) const;

		int	get_year() const;
		int	get_month() const;
		int	get_day() const;

	class Bad_Input : public std::exception
	{
		public:
				const char *what() const throw()
				{
					return ("bad input");
				}
	};

};

std::ostream& operator<<(std::ostream& os, const Date& date);