#include <time.h>
#include <iostream.h>
#include <iomanip.h>
#include <stdio.h>
#include <Flek/FDate.H>

// This class is based on the date class by Dave Freese
// <dfreese@intrepid.net>

const int FDate::days[] = 
  { 0, 31, 28, 31, 30,  31,  30,  31,  31,  30,  31,  30, 31 };

const int FDate::julian_days[] = 
  { 0,  0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

const char *FDate::month_name[] = {
  "January",
  "Febuary",
  "March",
  "April",
  "May",
  "June",
  "July",
  "August",
  "September",
  "October",
  "November",
  "December"
};

void FDate::today () {
  time_t t;
  struct tm *now;
  time (&t);
  now = localtime (&t);
  Year = now->tm_year + 1900;
  Month = now->tm_mon + 1;
  Day = now->tm_mday;
}

FDate::FDate () {
  today ();
  Fmt = 0;
}

FDate::FDate (const FDate &dt) : FBase (dt) {
  set_date (dt);
}

FDate::FDate (int y, int m, int d) {
  set_date (y, m, d);
  Fmt = 0;
}

FBase::Ptr FDate::copy (void) const {
  return new FDate (*this);
}

void FDate::set_date (int y, int m, int d) {
  if (is_valid (y, m, d)) {
    Year = y;
    Month = m;
    Day = d;
  } 
  else
    today ();
}

void FDate::set_date (const FDate &dt) {
  Year = dt.Year;
  Month = dt.Month;
  Day = dt.Day;
  Fmt = dt.Fmt;
}

void FDate::set_format (int iFmt) {
  Fmt = iFmt;
}

void FDate::year (int y) {
  Year = y;
}

int FDate::year () {
  return Year;
}

void FDate::month (int m) {
  Month = m;
}

int FDate::month () {
  return Month;
}

void FDate::day (int d) {
  Day = d;
}

int FDate::day () {
  return Day;
}

bool FDate::leap_year (int y) {
  if (y % 400 == 0 || ( y % 100 != 0 && y % 4 == 0 ))
    return true;
  return false;
}

bool FDate::is_valid (int y, int m, int d) {
  if (y < 1970 || y > 2035) return false;
  if (m < 1 || m > 12) return false;
  if (d < 1 ) return false;
  if (leap_year (y)) {
    if ((m == 2) && (d > 29))
      return false;
    else
      return true;
  }
  if (d > days[m]) return false;
  return true;
}

ostream &operator<< (ostream &output, const FDate &d) {
  output << d.to_string ();
  return output;
}

bool FDate::end_of_month (int d) {
  if (Month == 2 && leap_year (Year))
    return (d == 29);  // last day of Feb in leap year
  else
    return (d == days[Month]);
}

void FDate::help_increment () {
  if (end_of_month (Day) && Month == 12) {  // end year
    Day = 1;
    Month = 1;
    ++Year;
  } else if (end_of_month (Day)) {
    Day = 1;
    ++Month;
  } else
    ++Day;
}

FDate &FDate::operator++ () {
  help_increment ();
  return *this;     // reference return to create an lvalue
}

FDate FDate::operator++ (int) {
  FDate temp = *this;
  help_increment ();
  return temp;     // return non-increment, saved temporary object
}

const FDate &FDate::operator+= (int ndays) {
  for (int i = 0; i < ndays; i++)
    help_increment();
  return *this;    // enables cascading
}

bool FDate::operator== (const FDate &d) {
  if (this->Year != d.Year) return false;
  if (this->Month != d.Month) return false;
  if (this->Day != d.Day) return false;
  return true;
}

bool FDate::operator!= (const FDate &d) {
  return (!(*this == d));
}

bool FDate::operator< (const FDate &d) {
  if (this->Year < d.Year) return true;
  if (this->Year > d.Year) return false;
  if (this->Month < d.Month) return true;
  if (this->Month > d.Month) return false;
  if (this->Day < d.Day) return true;
  return false;
}

bool FDate::operator> (const FDate &d) {
  if (*this < d) return false;
  if (*this == d) return false;
  return true;
}

void FDate::operator= (const FDate &d) {
  this->Year = d.Year;
  this->Month = d.Month;
  this->Day = d.Day;
}

double FDate::julian_date () {
  int days_in_year = 365, julian_day = 0;
  if (leap_year (Year)) days_in_year++;
  julian_day = julian_days[Month] + Day;
  if (leap_year (Year) &&  (Month > 2))
    julian_day++;
  return (Year + 1.0 * (julian_day - 1) / days_in_year);
}

void FDate::next_month () {
  if (Month == 12) {
    Month = 1;
    Year++;
  }
  else
    Month++;
  
  while ((Day >= 1) && (!is_valid ()))
    Day--;
}

void FDate::previous_year () {
  if (Month == 2 && Day == 29)
    Day = 28;
  Year--;
}

void FDate::next_year () {
  if (Month == 2 && Day == 29)
    Day = 28;
  Year++;
}

char* FDate::to_string (int fmt) const {
  static char temp[20];
  char        temp_month[10];
  switch (fmt) {
   case 1 :
    sprintf (temp, "%02d/%02d/%04d", Month, Day, Year);
    break;
   case 2 :  
    sprintf (temp, "%s %2d, %4d",
	     month_name[Month - 1], 
	     Day, 
	     Year);
    break;
   case 3 :
    strcpy (temp_month, month_name [Month - 1]);
    temp_month[3] = 0; 
    sprintf (temp, "%s %2d, %4d", temp_month, Day, Year);
    break;
   case 4 :
    strcpy (temp_month, month_name [Month - 1]);
    temp_month[3] = 0; 
    sprintf (temp, "%d %s %4d", Day, temp_month, Year);
    break;
   case 0 :
   default :
    sprintf (temp, "%02d/%02d/%02d", Month, Day, 
	     Year > 1999 ? Year - 2000 : Year - 1900);
    break;
  }      
  return temp;
}

char* FDate::to_string () const {
  return to_string (Fmt);
}
