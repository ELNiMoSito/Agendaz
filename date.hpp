#ifndef __DATE_HPP__
#define __DATE_HPP__


	struct Time
	{
		int hour,minute;
	};

	struct Date
	{
		short int day,month,year;
		Time temps;
	};

void ChooseDateEnd(Date& dateend, Date &datebegin);
void ChooseDateBegin(Date& datebegin);
void maxday(Date & date, int& MAX);
	
#endif