module;
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <compare>
#include <regex>
#include <Windows.h>
export module TIME;

export class Time
{
private:
	int hours;
	int minutes;
	int seconds;
	void valid_time();
public:
	int get_hours();
	int get_minutes();
	int get_seconds();
	Time();
	Time(int h, int m, int s);
	Time(const std::string& str);
	Time(int sec);
	Time(tm* time);

	friend std::ostream& operator<<(std::ostream& out, const Time& time) {
		out << time.hours << ":" << time.minutes << ":" << time.seconds;
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Time& time) {
		char c;
		in >> time.hours >> c >> time.minutes >> c >> time.seconds;
		time.valid_time();
		return in;
	}

	//перегрузки 
	bool operator== (const Time& time) const;
	bool operator!= (const Time& time) const;
	std::strong_ordering operator<=>(const Time& time) const;
	Time operator+ (const Time& time) const;

	Time operator- (int sec) const;
	int operator-(const Time& time) const;
	int to_seconds();
	int to_minutes();
	int seconds_between(const Time& time);
	Time operator+(int sec) const;
	Time seconds_plus(int sec);
	Time seconds_minus(int sec);
	int compare(const Time& time);
	std::string to_string();
	~Time();
};

void Time::valid_time()
{
	int tmp{};
	if (seconds > 59)
	{
		tmp = seconds / 60;
		seconds = seconds % 60;
		minutes += tmp;
		tmp = 0;
	}
	if (minutes > 59)
	{
		tmp = minutes / 60;
		minutes = minutes % 60;
		hours += tmp;
		tmp = 0;
	}

	if (seconds < 0)
	{
		minutes -= abs(seconds / 60) + 1;
		seconds += 60;
	}

	if (minutes < 0)
	{
		hours -= abs(minutes / 60) + 1;
		minutes += 60;
	}
}

int Time::get_hours()
{
	return hours;
}

int Time::get_minutes()
{
	return minutes;
}

int Time::get_seconds()
{
	return seconds;
}


Time::Time()
{
	hours = minutes = seconds = {};
}

Time::Time(int h, int m, int s) //учесть что секунд может быть больше
{
	hours = { h };
	minutes = { m };
	seconds = { s };
	valid_time();
}

Time::Time(const std::string& str)
{
	std::istringstream ss(str);
	char c;
	ss >> hours >> c >> minutes >> c >> seconds;
	valid_time();
}

Time::Time(int sec)
{
	seconds = { sec };
	hours = minutes = {};
	valid_time();
}

Time::Time(tm* time)
{
	hours = { time->tm_hour };
	minutes = { time->tm_min };
	seconds = { time->tm_sec };
}

bool Time::operator==(const Time& time) const
{
	return hours == time.hours && minutes == time.minutes && seconds == time.seconds;
}

bool Time::operator!=(const Time& time) const
{
	return !(hours == time.hours && minutes == time.minutes && seconds == time.seconds);
}

std::strong_ordering Time::operator<=>(const Time& time) const {
	std::strong_ordering res;
	if (hours != time.hours) { res = hours <=> time.hours; }
	else
		if (minutes != time.minutes) { res = minutes <=> time.minutes; }
		else
			res = seconds <=> time.seconds;
	return res;
}

Time Time::operator+(const Time& time) const
{
	return Time(hours + time.hours, minutes + time.minutes, seconds + time.seconds);
}

Time Time::operator-(int sec) const
{
	return Time(hours, minutes, seconds - sec);
}

int Time::operator-(const Time& time) const
{
	int final_sec{ hours * 3600 - time.hours * 3600
		+ minutes * 60 - time.minutes * 60
		+ seconds - time.seconds };
	return abs(final_sec);
}

int Time::to_seconds()
{
	return hours * 3600 + minutes * 60 + seconds;
}

int Time::to_minutes()
{
	int t{ hours * 60 + minutes };
	if (seconds > 0)
		t++;
	return t;
}

int Time::seconds_between(const Time& time)
{
	Time t(*this - time);
	return t.to_seconds();
}

Time Time::operator+(int sec) const
{
	return Time(hours, minutes, seconds + sec);
}

Time Time::seconds_plus(int sec)
{
	return Time((*this).to_seconds() + sec);
}

Time Time::seconds_minus(int sec)
{
	return Time((*this).to_seconds() - sec);
}

int Time::compare(const Time& time)
{
	int res{ -1 };
	std::strong_ordering id{ (*this) <=> time };
	if (id == std::strong_ordering::greater)
		res = 1;
	else
		if (id == std::strong_ordering::equal)
			res = 0;
	return res;
}

std::string Time::to_string()
{
	std::ostringstream str;
	str << hours << ":" << minutes << ":" << seconds;
	return str.str();
}

Time::~Time()
{
}