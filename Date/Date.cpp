#include "Date.h"
#include <ctime>

Date::Date()
{
	day = 1;
	month = 1;
	year = 2020;
}

Date::Date(string date) {
		year = stoi(date.substr(0, 4));
		month = stoi(date.substr(5, 2));
		day = stoi(date.substr(8, 2));
}
void output_date(Date date)
{
	cout << date.day << "/" << date.month << "/" << date.year;
}

//*Kiem tra nam nhuan
bool check_leap_year(int year)
{
	return ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0));
}
//*So ngay cua thang
int day_of_month(int month, int year)
{
	switch (month)
	{
	case 1:case 3:case 5:case 7:case 8:case 10:case 12:	return 31;
	case 4:case 6:case 9:case 11: return 30;
	default:
		if (check_leap_year(year))
		{
			return 29;
		}
		else return 28;
		break;
	}
}
//*Kiem tra tinh hop le cua ngay thang
bool check_date(Date date)
{
	if (date.year <= 0 || date.month <= 0)
	{
		return false;
	}
	if (date.month < 1 || date.month>12)
	{
		return false;
	}
	if (date.day <= 0 || date.day > day_of_month(date.month, date.year))
	{
		return false;
	}
	return true;
}
// Nhap ngay
void Date::enter_date() {
	string tmp;
	cout << "Enter the date (example: 2020-12-31): ";
	cin >> tmp;
	*this = Date(tmp);
}
//*Check xem ngay da cho co nam giua 2 ngay khac khong
bool ifDate(Date date, Date start, Date end) {
	if ((date.year>start.year)&&(date.year<=end.year)||(date.year>=start.year)&&(date.year<end.year)) {
		return true;
	} else if ((date.year==start.year)&&(date.year==end.year)) {
		if ((date.month>start.month)&&(date.month<=end.month)||(date.month>=start.month)&&(date.month<end.month)) {
		return true;
		} else if ((date.month==start.month)&&(date.month==end.month)){
			if ((date.day>=start.day)&&(date.day<=end.day)){
				return true;
			}
		}
	}
	return false;
}


Date getThisDate() {
	Date cur; 
	time_t now = time(0);
	tm* tmp = localtime(&now);
	cur.year = 1900 + tmp->tm_year;
	cur.month = tmp->tm_mon + 1;
	cur.day = tmp->tm_mday;
	return cur;
}
