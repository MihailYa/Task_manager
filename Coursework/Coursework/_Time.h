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
	Time(unsigned int year_, unsigned int month_, unsigned int day_, unsigned int hours_, unsigned int minutes_);
	Time(boost::gregorian::date dat_, unsigned int hours_, unsigned int minutes_);

	Time(const Time& right);

	static Time current_time();
	/**
	* Get number of seconds left to nearly new minute
	* @return number of seconds
	*/
	static unsigned int to_minute_left();
	/**
	* Get number of minutes left to nearly new hour
	* @return number of minutes in SECONDS
	*/
	static unsigned int to_hour_left();

	//
	// Setters
	//
	void Set_dat(boost::gregorian::date dat_);
	/**
	* Increase current date, so current weekday = wday_
	* @param wday_ weekday
	*/
	void Set_next_weekday(const boost::date_time::weekdays wday_);
	/**
	* Increase current date to next nearly date dependce on month_list and days_list
	* @param month_list sorted, not empty vector of months from which choose must be done
	* @param days_list sorted, not empty vector of days from which choose must be done
	Example:
	input:
	*	this: 30.01.2017 22:50
	*	month_list = { 1, 2, 12 }
	*	days_list = { 29 }
	output:
	*	this: 29.12.2017 22:50
	*/
	void Set_next_month_day(const std::vector<boost::gregorian::months_of_year> month_list, const std::vector<unsigned int> days_list);

	//
	// Getters
	//
	boost::gregorian::date Get_dat() const;
	Time_t Get_time() const;
	std::string Get_as_string() const;

	//
	// Operators
	//
	const Time operator+(const int num_of_days) const;
	const Time operator+=(const int num_of_days);
	/**
	* Calculate difference between two Time's
	* @return number of minutes, if all except minutes in @this time is equal to @right time
	* * Otherwise: return INF
	*/
	const int operator-(const Time& right) const;
	/**
	* Calculate how many weeks must be added to @right, so @righth would be > @this
	* @param right Time dependce on which calculation must be done
	* @return number of weeks
	*/
	const int operator%(const Time& right) const;
	const bool operator>(const Time& right) const;
	const bool operator>=(const Time& right) const;
	const bool operator<(const Time& right) const;
	const bool operator<=(const Time& right) const;
	const bool operator==(const Time& right) const;
	const bool operator!=(const Time& right) const;

#ifdef DEBUG
	void output();
#endif // DEBUG

private:
	Time_t time;
};

