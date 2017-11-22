#include "_Time.h"

Time::Time()
{
}

Time::Time(Time_t time_)
	: time(time_)
{
}

Time::Time(unsigned int year_, unsigned int month_, unsigned int day_, unsigned int hours_, unsigned int minutes_)
{
	if (year_ < 1400 || month_ <= 0 || month_ > 12 || day_ > boost::gregorian::date(year_, month_, 1).end_of_month().day() || hours_ >= 24 || minutes_ >= 60)
	{
		throw new WrongTimeFormat_ex;
	}

	time.dat = boost::gregorian::date(year_, month_, day_);
	time.hours = hours_;
	time.minutes = minutes_;
}

Time::Time(boost::gregorian::date dat_, unsigned int hours_, unsigned int minutes_)
	: time(dat_, hours_, minutes_)
{
}

Time Time::current_time()
{
	time_t c_time = std::time(NULL);
	tm *tm_c_time;
	tm_c_time = std::localtime(&c_time);

	return Time(tm_c_time->tm_year + 1900, tm_c_time->tm_mon + 1, tm_c_time->tm_mday, tm_c_time->tm_hour, tm_c_time->tm_min);
}

unsigned int Time::to_minute_left()
{
	time_t c_time = std::time(NULL);
	tm *tm_c_time;
	tm_c_time = std::localtime(&c_time);
	
	unsigned int n;
	if (tm_c_time->tm_sec == 0)
		n = 0;
	else
		n = 60 - tm_c_time->tm_sec;

	return n;
}

unsigned int Time::to_hour_left()
{
	time_t c_time = std::time(NULL);
	tm *tm_c_time;
	tm_c_time = std::localtime(&c_time);

	unsigned int n_sec = 0, n_min = 0, n;
	if (tm_c_time->tm_min == 0 && tm_c_time->tm_sec == 0)
		n = 0;
	else
	{
		n_min = (60 - tm_c_time->tm_min);
		if (tm_c_time->tm_sec != 0)
		{
			--n_min;
			n_sec = 60 - tm_c_time->tm_sec;
		}
		n = n_min * 60 + n_sec;
	}

	return n;
}

//
// Setters
//
void Time::Set_dat(boost::gregorian::date dat_)
{
	time.dat = dat_;
}

void Time::Set_next_weekday(const boost::date_time::weekdays wday_)
{
	int wday = time.dat.day_of_week();
	int inc = wday_ - wday;

	if (inc == 0)
		return;

	if (inc < 0)
		inc += 7;

	time.dat += boost::gregorian::date_duration(inc);
}
void Time::Set_next_month_day(const std::vector<boost::date_time::months_of_year> month_list, const std::vector<unsigned int> days_list)
{
	// Find nearly year and month
	boost::gregorian::date tmp;
	unsigned int m_index = 0;
	
	while (
		(m_index < month_list.size())
		&&
		((tmp = boost::gregorian::date(time.dat.year(), month_list[m_index], boost::gregorian::date(time.dat.year(), month_list[m_index], 1).end_of_month().day())) < time.dat)
		)
	{
		m_index++;
	}
	if (tmp < time.dat)
	{
		tmp = boost::gregorian::date(time.dat.year() + 1, month_list[0], time.dat.day());
	}

	// Find nearly day
	unsigned int d_index = 0;
	while (
		(d_index < days_list.size())
		&&
		(tmp = boost::gregorian::date(tmp.year(), tmp.month(), days_list[d_index])) < time.dat
		)
	{
		d_index++;
	}

	if (tmp < time.dat)
		if ((m_index += 1) >= month_list.size())
			tmp = boost::gregorian::date(tmp.year() + 1, month_list[0], days_list[0]);
		else
			tmp = boost::gregorian::date(tmp.year(), month_list[m_index], days_list[0]);
	else
		tmp = boost::gregorian::date(tmp.year(), month_list[m_index], days_list[d_index]);

	time.dat = tmp;
}

//
// Getters
//
boost::gregorian::date Time::Get_dat() const
{
	return time.dat;
}

Time_t Time::Get_time() const
{
	return time;
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
	if (time.dat == right.time.dat && time.hours == right.time.hours)
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

const bool Time::operator>=(const Time& right) const
{
	if (*this > right && *this == right)
		return true;

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

#ifdef DEBUG
void Time::output()
{
	printf("%d.%d.%d %d:%d\n", time.dat.year(), time.dat.month(), time.dat.day(), time.hours, time.minutes);
}
#endif // DEBUG
