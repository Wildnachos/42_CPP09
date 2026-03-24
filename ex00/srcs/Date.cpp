#include "../incl/Date.hpp"

Date::Date()
{
	year = 0;
	month = 1;
	day = 1;
}

Date::Date(std::string str)
{
	std::stringstream ss(str);
	std::string tmp;

	char extra = 0;
	char sep1;
	char sep2;

	int res = std::sscanf(str.c_str(), "%d%c%d%c%d%c", &year, &sep1, &month, &sep2, &day, &extra);
	if (res == EOF || (extra && extra != ' '))
		throw Bad_Input();
	if (sep1 != '-' || sep2 != '-')
		throw Bad_Input();
	validate();
}

Date::Date(const Date& other) : year(other.year), month(other.month), day(other.day)
{
}

Date& Date::operator=(const Date& other)
{
	if (this == &other)
		return *this;
	year = other.year;
	month = other.month;
	day = other.day;
	
	return *this;
}

int	Date::get_year() const
{
	return year;
}

int	Date::get_month() const
{
	return month;
}

int	Date::get_day() const
{
	return day;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	os << date.get_year() << "-" << date.get_month() << "-" << date.get_day();
	return os;
}

bool Date::operator<(const Date& other) const
{
	if (year > other.year)
		return false;
	else if (year < other.year)
		return true;
	if (month > other.month)
		return false;
	else if (month < other.month)
		return true;
	if (day < other.day)
		return true;
	return false;
}

bool Date::isLeap(int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
				return true;
			else
				return false;
		}
		return true;
	}
	return false;
}

void Date::validate()
{
	if (year < 0)
		throw Bad_Input();
	if (month <= 0 || month > 12)
		throw Bad_Input();
	if (day <= 0 || day > 31)
		throw Bad_Input();
	if (day > 30 && (month != 1 && month != 3 && month != 5 && month != 7 && month != 8 && month != 10 && month != 12))
		throw Bad_Input();
	if (month == 2 && day > 28)
	{
		if (!isLeap(year))
			throw Bad_Input();
	}
}

Date::~Date()
{
}