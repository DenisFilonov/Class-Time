#include "Time.h"

Time::Time()
{
	time_t now = time(0);
	tm* obj = new tm;
	localtime_s(obj, &now);

	hours = obj->tm_hour;
	minutes = obj->tm_min;
	seconds = obj->tm_sec;
	delete obj;
}

Time::Time(int hours, int minutes, int seconds, const char* format)
{
	*this = Time();
	strcpy_s(this->format, 4, format);
	if (strcmp(this->format, "utc") != 0 && (hours >= 1 && hours <= 12))
	{
		this->hours = hours;
		if (minutes >= 0 && minutes <= 59)
		{
			this->minutes = minutes;
		}
		if (seconds >= 0 && seconds <= 59)
		{
			this->seconds = seconds;
		}
	}
	else
	{
		if (hours >= 0 && hours <= 23) // вот так, потому const char* format = utc
		{
			this->hours = hours;
		}
		if (minutes >= 0 && minutes <= 59)
		{
			this->minutes = minutes;
		}
		if (seconds >= 0 && seconds <= 59)
		{
			this->seconds = seconds;
		}
	}
}

Time::Time(const Time& obj)
{
	this->hours = obj.hours;
	this->minutes = obj.minutes;
	this->seconds = obj.seconds;
	strcpy_s(this->format, 4, obj.format);
}

Time& Time::operator=(const Time& obj)
{
	this->hours = obj.hours;
	this->minutes = obj.minutes;
	this->seconds = obj.seconds;
	strcpy_s(this->format, 4, obj.format);
	return *this;
}

Time::~Time()
{
	//Тут пусто, бо нет дин.строк
}

void Time::setHours(int hours)
{
	if (strcmp(this->format, "utc") == 0 && (hours >= 0 && hours <= 23)) // вот так, потому const char* format = utc
	{
		this->hours = hours;
	}
	else if (strcmp(this->format, "utc") != 0 && (hours >= 1 && hours <= 12))
	{
		this->hours = hours;
	}
}

int Time::getHours() const
{
	return hours;
}

void Time::setMinutes(int minutes)
{
	if (minutes >= 0 && minutes <= 59)
	{
		this->minutes = minutes;
	}
}

int Time::getMinutes() const
{
	return minutes;
}

void Time::setSeconds(int seconds)
{
	if (seconds >= 0 && seconds <= 59)
	{
		this->seconds = seconds;
	}
}

int Time::getSeconds() const
{
	return seconds;
}

void Time::setFormat(int menu)
{
	switch (menu)
	{
	case 1:
		strcpy_s(this->format, 4, ""); // чистим массив от старой памяти
		strcpy_s(this->format, 3, "am");
		cout << "Формат \"am\" выставлен успешно.\n\n";
		break;

	case 2:
		strcpy_s(this->format, 4, ""); // чистим массив от старой памяти
		strcpy_s(this->format, 3, "pm");
		cout << "Формат \"pm\" выставлен успешно.\n\n";
		break;

	case 3:
		strcpy_s(this->format, 4, ""); // чистим массив от старой памяти
		strcpy_s(this->format, 4, "utc");
		cout << "Формат \"utc\" выставлен успешно.\n\n";
		break;

	default: if (menu > 3 && menu != 0 || menu < 0) cout << "Неверно выбран пункт меню.\n\n"; break;
	}
}

const char* Time::getFormat() const
{
	return format;
}

bool Time::isValidTime() const
{
	if (strcmp(this->format, "utc") != 0 && (hours >= 1 && hours <= 12) && (minutes >= 0 && minutes <= 59) && (seconds >= 0 && seconds <= 59))
	{
		return true;
	}
	else if (strcmp(this->format, "utc") == 0 && (hours >= 1 && hours <= 23) && (minutes >= 0 && minutes <= 59) && (seconds >= 0 && seconds <= 59))
	{
		return true;
	}
	else return false;
}

void Time::tickTime()
{
	seconds++;
	if (seconds == 60)
	{
		seconds = 0;
		minutes++;
		if (minutes == 60)
		{
			minutes = 0;
			hours++;
		}

		if (strcmp(this->format, "utc") == 0 && hours == 24) hours = 0;
		else hours = 12;
	}
}

void Time::untickTime()
{
	seconds--;
	if (seconds == -1)
	{
		seconds = 59;
		minutes--;
		if (minutes == -1)
		{
			minutes = 59;
			hours--;

			if (strcmp(this->format, "utc") == 0 && hours == -1) hours = 23;
			else hours = 11;
		}
	}
}

void Time::showTime() const
{
	cout << "\nВремя: " << hours / 10 << hours % 10 << ":" << minutes / 10 << minutes % 10 << ":" << seconds / 10 << seconds % 10;
}

bool operator==(const Time& obj1, const Time& obj2)
{
	Time lefttmp = obj1;
	Time righttmp = obj2;
	if (strcmp(lefttmp.format, "utc") != 0)
	{
		strcpy_s(lefttmp.format, 4, "");
		strcpy_s(lefttmp.format, 4, "utc");
	}
	if (strcmp(righttmp.format, "pm") == 0 && lefttmp.hours > 12)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
		righttmp.hours += 12;
	}
	else if (strcmp(righttmp.format, "utc") != 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
	}

	if (lefttmp.hours == righttmp.hours && lefttmp.minutes == righttmp.minutes && lefttmp.seconds == righttmp.seconds)
	{
		return true;
	}
	else return false;
}

bool operator!=(const Time& obj1, const Time& obj2)
{
	return !(obj1 == obj2);
}

bool operator>(const Time& obj1, const Time& obj2)
{
	Time lefttmp = obj1;
	Time righttmp = obj2;
	if (strcmp(lefttmp.format, "utc") != 0)
	{
		strcpy_s(lefttmp.format, 4, "");
		strcpy_s(lefttmp.format, 4, "utc");
	}
	if (strcmp(righttmp.format, "utc") != 0 && strcmp(righttmp.format, "pm") == 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
		righttmp.hours += 12;
	}
	else if (strcmp(righttmp.format, "utc") != 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
	}

	if (lefttmp.hours > righttmp.hours)
	{
		return true;
	}
	else if (lefttmp.hours == righttmp.hours && lefttmp.minutes > righttmp.minutes)
	{
		return true;
	}
	else if (lefttmp.hours == righttmp.hours && lefttmp.minutes == righttmp.minutes && lefttmp.seconds > righttmp.seconds)
	{
		return true;
	}
	else return false;
}

bool operator<(const Time& obj1, const Time& obj2)
{
	Time lefttmp = obj1;
	Time righttmp = obj2;
	if (strcmp(lefttmp.format, "utc") != 0)
	{
		strcpy_s(lefttmp.format, 4, "");
		strcpy_s(lefttmp.format, 4, "utc");
	}
	if (strcmp(righttmp.format, "utc") != 0 && strcmp(righttmp.format, "pm") == 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
		righttmp.hours += 12;
	}
	else if (strcmp(righttmp.format, "utc") != 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
	}

	if (lefttmp.hours < righttmp.hours)
	{
		return true;
	}
	else if (lefttmp.hours == righttmp.hours && lefttmp.minutes < righttmp.minutes)
	{
		return true;
	}
	else if (lefttmp.hours == righttmp.hours && lefttmp.minutes == righttmp.minutes && lefttmp.seconds < righttmp.seconds)
	{
		return true;
	}
	else return false;
}

bool operator>=(const Time& obj1, const Time& obj2)
{
	/*
	 if (this* > obj || *this == obj) return true;
	 else return false;
	*/

	Time lefttmp = obj1;
	Time righttmp = obj2;
	if (strcmp(lefttmp.format, "utc") != 0)
	{
		strcpy_s(lefttmp.format, 4, "");
		strcpy_s(lefttmp.format, 4, "utc");
	}
	if (strcmp(righttmp.format, "utc") != 0 && strcmp(righttmp.format, "pm") == 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
		righttmp.hours += 12;
	}
	else if (strcmp(righttmp.format, "utc") != 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
	}

	if (lefttmp.hours >= righttmp.hours)
	{
		return true;
	}
	else if (lefttmp.hours == righttmp.hours && lefttmp.minutes >= righttmp.minutes)
	{
		return true;
	}
	else if (lefttmp.hours == righttmp.hours && lefttmp.minutes == righttmp.minutes && lefttmp.seconds >= righttmp.seconds)
	{
		return true;
	}
	else return false;
}

bool operator<=(const Time& obj1, const Time& obj2)
{
	/*
	 if (this* < obj || *this == obj) return true;
	 else return false;
	*/
	Time lefttmp = obj1;
	Time righttmp = obj2;
	if (strcmp(lefttmp.format, "utc") != 0)
	{
		strcpy_s(lefttmp.format, 4, "");
		strcpy_s(lefttmp.format, 4, "utc");
	}
	if (strcmp(righttmp.format, "utc") != 0 && strcmp(righttmp.format, "pm") == 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
		righttmp.hours += 12;
	}
	else if (strcmp(righttmp.format, "utc") != 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
	}

	if (lefttmp.hours <= righttmp.hours)
	{
		return true;
	}
	else if (lefttmp.hours == righttmp.hours && lefttmp.minutes <= righttmp.minutes)
	{
		return true;
	}
	else if (lefttmp.hours == righttmp.hours && lefttmp.minutes == righttmp.minutes && lefttmp.seconds <= righttmp.seconds)
	{
		return true;
	}
	else return false;
}

ostream& operator<<(ostream& os, const Time& t)
{
	os << t.hours << ":" << t.minutes << ":" << t.seconds;
	return os;
}

istream& operator>>(istream& is, Time& t)
{
	is >> t.hours;
	cout << ":";
	is >> t.minutes;
	cout << ":";
	is >> t.seconds;
	return is;
}

/*bool Time::operator==(const Time& obj1, const Time& obj2) const&
{
	Time lefttmp = *this;
	Time righttmp = obj;
	if (strcmp(lefttmp.format, "utc") != 0)
	{
		strcpy_s(lefttmp.format, 4, "");
		strcpy_s(lefttmp.format, 4, "utc");
	}
	if (strcmp(righttmp.format, "pm") == 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
		righttmp.hours += 12;
	}
	else if (strcmp(righttmp.format, "utc") != 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
	}

	if (lefttmp.hours == righttmp.hours && lefttmp.minutes == righttmp.minutes && lefttmp.seconds == righttmp.seconds)
	{
		return true;
	}
	else return false;
}

bool Time::operator!=(const Time& obj) const&
{
	return !(*this == obj);
}

bool Time::operator>(const Time& obj) const&
{
	Time lefttmp = *this;
	Time righttmp = obj;
	if (strcmp(lefttmp.format, "utc") != 0)
	{
		strcpy_s(lefttmp.format, 4, "");
		strcpy_s(lefttmp.format, 4, "utc");
	}
	if (strcmp(righttmp.format, "utc") != 0 && strcmp(righttmp.format, "pm") == 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
		righttmp.hours += 12;
	}
	else if (strcmp(righttmp.format, "utc") != 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
	}

	if (lefttmp.hours > righttmp.hours)
	{
		return true;
	}
	else if (lefttmp.hours == righttmp.hours && lefttmp.minutes > righttmp.minutes)
	{
		return true;
	}
	else if (lefttmp.hours == righttmp.hours && lefttmp.minutes == righttmp.minutes && lefttmp.seconds > righttmp.seconds)
	{
		return true;
	}
	else return false;
}

bool Time::operator<(const Time& obj) const&
{
	Time lefttmp = *this;
	Time righttmp = obj;
	if (strcmp(lefttmp.format, "utc") != 0)
	{
		strcpy_s(lefttmp.format, 4, "");
		strcpy_s(lefttmp.format, 4, "utc");
	}
	if (strcmp(righttmp.format, "utc") != 0 && strcmp(righttmp.format, "pm") == 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
		righttmp.hours += 12;
	}
	else if (strcmp(righttmp.format, "utc") != 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
	}

	if (lefttmp.hours < righttmp.hours)
	{
		return true;
	}
	else if (lefttmp.hours == righttmp.hours && lefttmp.minutes < righttmp.minutes)
	{
		return true;
	}
	else if (lefttmp.hours == righttmp.hours && lefttmp.minutes == righttmp.minutes && lefttmp.seconds < righttmp.seconds)
	{
		return true;
	}
	else return false;
}

bool Time::operator>=(const Time& obj) const&
{
	Time lefttmp = *this;
	Time righttmp = obj;
	if (strcmp(lefttmp.format, "utc") != 0)
	{
		strcpy_s(lefttmp.format, 4, "");
		strcpy_s(lefttmp.format, 4, "utc");
	}
	if (strcmp(righttmp.format, "utc") != 0 && strcmp(righttmp.format, "pm") == 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
		righttmp.hours += 12;
	}
	else if (strcmp(righttmp.format, "utc") != 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
	}

	if (lefttmp.hours >= righttmp.hours)
	{
		return true;
	}
	else if (lefttmp.hours == righttmp.hours && lefttmp.minutes >= righttmp.minutes)
	{
		return true;
	}
	else if (lefttmp.hours == righttmp.hours && lefttmp.minutes == righttmp.minutes && lefttmp.seconds >= righttmp.seconds)
	{
		return true;
	}
	else return false;
}

bool Time::operator<=(const Time& obj) const&
{
	Time lefttmp = *this;
	Time righttmp = obj;
	if (strcmp(lefttmp.format, "utc") != 0)
	{
		strcpy_s(lefttmp.format, 4, "");
		strcpy_s(lefttmp.format, 4, "utc");
	}
	if (strcmp(righttmp.format, "utc") != 0 && strcmp(righttmp.format, "pm") == 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
		righttmp.hours += 12;
	}
	else if (strcmp(righttmp.format, "utc") != 0)
	{
		strcpy_s(righttmp.format, 4, "");
		strcpy_s(righttmp.format, 4, "utc");
	}

	if (lefttmp.hours <= righttmp.hours)
	{
		return true;
	}
	else if (lefttmp.hours == righttmp.hours && lefttmp.minutes <= righttmp.minutes)
	{
		return true;
	}
	else if (lefttmp.hours == righttmp.hours && lefttmp.minutes == righttmp.minutes && lefttmp.seconds <= righttmp.seconds)
	{
		return true;
	}
	else return false;
}*/

Time& Time::operator+=(int n)
{
	for (int i = 0; i < n; i++)
	{
		this->tickTime();
	}
	return *this;
}

Time& Time::operator-=(int n)
{
	for (int i = 0; i < n; i++)
	{
		this->untickTime();
	}
	return *this;
}

Time Time::operator+(int n) const&
{
	Time tmp = *this;
	for (int i = 0; i < n; i++)
	{
		tmp.tickTime();
	}
	return tmp;
}

Time Time::operator-(int n) const&
{
	Time tmp = *this;
	for (int i = 0; i < n; i++)
	{
		tmp.untickTime();
	}
	return tmp;
}

Time Time::operator--() const&
{
	Time tmp = *this;
	tmp.tickTime();
	return *this;
}

Time Time::operator++() const&
{
	Time tmp = *this;
	tmp.untickTime();
	return *this;
}

