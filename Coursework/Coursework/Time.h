#pragma once
#include "stdafx.h"
#include "globals.h"

struct Time_t
{
	Time_t()
		: dat(boost::gregorian::date(1400, 1, 1)), hours(0), minutes(0)
	{}

	Time_t(boost::gregorian::date dat_, int hours_, int minutes_)
		: dat(dat_), hours(hours_), minutes(minutes_)
	{}
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
	void Set_next_weekday(const boost::date_time::weekdays wday_);
	// Set next nearly date
	void Set_next_month_day(const std::vector<boost::date_time::months_of_year> month_list, const std::vector<unsigned int> days_list);

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

#ifdef DEBUG
	void output();
#endif // !DEBUG

private:
	Time_t time;
};

