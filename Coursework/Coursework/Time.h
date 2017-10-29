#pragma once
#include "stdafx.h"

struct Time_t
{
	/*int year;
	int month;
	int mday;
	int wday;*/
	boost::gregorian::date dat;
	int hours;
	int minutes;
};

class Time
{
public:
	Time();
	Time(Time_t time_);
	
	//
	// Setters
	//
	void Set_dat(boost::gregorian::date dat_);
	// Add ass many days to make current weekday = wday_
	void Set_next_weekday(const unsigned int wday_);
	// Set next nearly date
	void Set_next_month_day(const std::vector<unsigned int> month_list, const std::vector<unsigned int> days_list);

	//
	// Getters
	//
	boost::gregorian::date Get_dat() const;

	//
	// Operators
	//
	const Time operator+(const int num_of_days) const;
	const Time operator+=(const int num_of_days);
	const int operator-(const Time& right) const;
	const bool operator>(const Time& right) const;
	const bool operator<(const Time& right) const;
	const bool operator==(const Time& right) const;
	const bool operator!= (const Time& right) const;
private:
	Time_t time;
};

