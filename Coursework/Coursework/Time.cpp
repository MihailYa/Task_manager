#include "Time.h"
#include "globals.h"

Time::Time()
{
	time.dat = boost::gregorian::date(1, 1, 0);
	time.hours = 0;
	time.minutes = 0;
}

Time::Time(Time_t time_)
	: time(time_)
{
}

//
// Setters
//
void Time::Set_dat(boost::gregorian::date dat_)
{
	time.dat = dat_;
}

void Time::Set_next_weekday(const unsigned int wday_)
{
	int wday = time.dat.day_of_week();
	int inc = wday_ - wday;

	if (inc == 0)
		return;

	if (inc < 0)
		inc += 7;

	time.dat += boost::gregorian::date_duration(inc);
}
void Time::Set_next_month_day(const std::vector<unsigned int> month_list, const std::vector<unsigned int> days_list)
{
	// Find nearly year and month
	boost::gregorian::date tmp;
	unsigned int index = 0;
	while (
		((tmp = boost::gregorian::date(time.dat.year(), month_list[index], time.dat.end_of_month.day())) < time.dat)
		&&
		(index < month_list.size())
		)
	{
		index++;
	}
	if (tmp < time.dat)
	{
		tmp = boost::gregorian::date(time.dat.year() + 1, month_list[0], time.dat.day());
	}

	// Find nearly day
	index = 0;
	while (
		(tmp = boost::gregorian::date(tmp.year(), tmp.month(), days_list[index])) < time.dat
		&&
		(index < days_list.size())
		)
	{
		index++;
	}

	if (tmp < time.dat)
	{
		tmp = boost::gregorian::date(tmp.year(), tmp.month(), days_list[index]) + boost::gregorian::months(1);
	}

	time.dat = tmp;
}

//
// Getters
//
boost::gregorian::date Time::Get_dat() const
{
	return time.dat;
}


const Time Time::operator+(const int num_of_days) const
{
	Time tmp = *this;
	tmp.time.dat += boost::gregorian::date_duration(num_of_days);

	return tmp;
}

const Time Time::operator+=(const int num_of_days)
{
	time.dat += boost::gregorian::date_duration(num_of_days);

	return *this;
}

const int Time::operator-(const Time& right) const
{
	if (time.dat == right.time.dat)
	{
		int time_left = time.minutes - right.time.minutes;
		if (time_left >= 0)
			return time_left;
	}

	return INF;
}

const bool Time::operator>(const Time& right) const
{
	if (time.dat > right.time.dat)
	{
		return true;
	}
	else if (time.dat == right.time.dat)
	{
		if (time.hours > right.time.hours)
		{
			return true;
		}
		else if (time.hours == right.time.hours)
		{
			if (time.minutes > right.time.minutes)
			{
				return true;
			}
		}
	}
	/*if (time.year > right.time.year)
	{
		return true;
	}
	else if (time.year == right.time.year)
	{
		if (time.month > right.time.month)
		{
			return true;
		}
		else if (time.month == right.time.month)
		{
			if (time.mday > right.time.mday)
			{
				return true;
			}
			else if (time.mday == right.time.mday)
			{
				if (time.hours > right.time.hours)
				{
					return true;
				}
				else if (time.hours == right.time.hours)
				{
					if (time.minutes > right.time.minutes)
					{
						return true;
					}
				}
			}
		}
	}
*/
	return false;
}

const bool Time::operator<(const Time& right) const
{
	if (*this != right)
		return !(*this > right);

	return false;
}

const bool Time::operator==(const Time& right) const
{
	if (time.dat == right.time.dat && time.hours == right.time.hours && time.minutes == right.time.minutes)
		return true;

	return false;
}

const bool Time::operator!=(const Time& right) const
{
	return !(*this == right);
}
