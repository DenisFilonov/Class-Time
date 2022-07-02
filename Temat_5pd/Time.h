#pragma once
#include <iostream>
#include <ctime>
using namespace std;

class Time
{
	int hours;
	int minutes;
	int seconds;
	char format[4];// am/pm (12-hours), utc (24-hours)

public:
	Time(); // Current local time
	Time(int hours, int minutes, int seconds, const char* format = "utc");
	Time(const Time& obj);
	Time& operator = (const Time& obj);
	~Time();

	void setHours(int hours);
	int getHours()const;
	void setMinutes(int minutes);
	int getMinutes()const;
	void setSeconds(int seconds);
	int getSeconds()const;
	void setFormat(int menu = 2); // !!! to update time by the new format: utc to pm
	const char* getFormat()const; //utc/am/pm

	bool isValidTime()const; //time check
	void tickTime(); //every tick add one second
	void untickTime(); //every tick remove one second
	void showTime()const; //show time by the format

	//--------- Comparison operators ---------
	friend bool operator == (const Time& obj1, const Time& obj2);
	friend bool operator != (const Time& obj1, const Time& obj2);
	friend bool operator > (const Time& obj1, const Time& obj2);
	friend bool operator < (const Time& obj1, const Time& obj2);
	friend bool operator >= (const Time& obj1, const Time& obj2);
	friend bool operator <= (const Time& obj1, const Time& obj2);

	//--------- Assignment operators ---------	
	Time& operator += (int n);
	Time& operator -= (int n);

	//--------- Ariphmetic operators ---------
	Time operator + (int n)const&;
	Time operator - (int n)const&;
	Time operator -- ()const&;
	Time operator ++ ()const&;

	friend ostream& operator << (ostream& os, const Time& t);
	friend istream& operator >> (istream& is, Time& t);
};
