#include <Flek/fDate.h>
#include <time.h>
#include <iostream.h>
#include <iomanip.h>

// This class is based on the date class by Dave Freese
// <dfreese@intrepid.net>

const int fDate::Days[] = 
  { 0, 31, 28, 31, 30,  31,  30,  31,  31,  30,  31,  30, 31 };

const int fDate::JDays[] = 
  { 0,  0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

void fDate::today ()
{
  time_t t;
  struct tm *now;
  time (&t);
  now = localtime (&t);
  Year = now->tm_year + 1900;
  Month = now->tm_mon + 1;
  Day = now->tm_mday;
}

fDate::fDate()
{
  today ();
  Fmt = 0;
}

fDate::fDate (const fDate &dt) : fBase (dt)
{
  setDate (dt);
}

fDate::fDate (int y, int m, int d)
{
  setDate (y, m, d);
  Fmt = 0;
}

fBase::Ptr fDate::copy (void) const
{
  return new fDate (*this);
}

void fDate::setDate (int y, int m, int d)
{
  if (isValid (y, m, d)) {
    Year = y;
    Month = m;
    Day = d;
  } else
    today();
}

void fDate::setDate (const fDate &dt)
{
  Year = dt.Year;
  Month = dt.Month;
  Day = dt.Day;
  Fmt = dt.Fmt;
}

void fDate::setFormat (int iFmt)
{
  Fmt = iFmt;
}

void fDate::year (int y)
{
  Year = y;
}

int fDate::year ()
{
  return Year;
}

void fDate::month (int m)
{
  Month = m;
}

int fDate::month ()
{
  return Month;
}

void fDate::day (int d)
{
  Day = d;
}

int fDate::day ()
{
  return Day;
}

bool fDate::leapYear (int y)
{
  if (y % 400 == 0 || ( y % 100 != 0 && y % 4 == 0 ))
    return true;
  return false;
}

bool fDate::isValid (int y, int m, int d)
{
  if (y < 1970 || y > 2035) return false;
  if (m < 1 || m > 12) return false;
  if (d < 1 ) return false;
  if (leapYear (y)) {
    if ((m == 2) && (d > 29))
      return false;
    else
      return true;
  }
  if (d > Days[m]) return false;
  return true;
}

ostream &operator<< (ostream &output, const fDate &d)
{
  static char *monthName[13] = { "", 
				 "Jan", "Feb", "Mar", "Apr", "May", "Jun",
				 "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
  switch (d.Fmt) {
  case 1 :
    output << monthName[d.Month] << ' ' << d.Day << ", " << d.Year;
    break;
  case 0 :
  default :
    output << d.Year << '/' ;
    cout.setf (ios::right, ios::adjustfield);
    cout.fill ('0');
    output << setw (2) << d.Month << '/' << d.Day;
    break;
  }
  return output;
}

bool fDate::endOfMonth (int d)
{
  if (Month == 2 && leapYear (Year))
    return (d == 29);  // last day of Feb in leap year
  else
    return (d == Days[Month]);
}

void fDate::helpIncrement ()
{
  if (endOfMonth (Day) && Month == 12) {  // end year
    Day = 1;
    Month = 1;
    ++Year;
  } else if (endOfMonth (Day)) {
    Day = 1;
    ++Month;
  } else
    ++Day;
}

fDate &fDate::operator++ ()
{
  helpIncrement();
  return *this;     // reference return to create an lvalue
}

fDate fDate::operator++ (int)
{
  fDate temp = *this;
  helpIncrement ();
  return temp;     // return non-increment, saved temporary object
}

const fDate &fDate::operator+= (int ndays)
{
  for( int i = 0; i < ndays; i++)
    helpIncrement();
  return *this;    // enables cascading
}


bool fDate::operator== (const fDate &d)
{
  if (this->Year != d.Year) return false;
  if (this->Month != d.Month) return false;
  if (this->Day != d.Day) return false;
  return true;
}

bool fDate::operator!= (const fDate &d)
{
  return (!(*this == d));
}

bool fDate::operator< (const fDate &d)
{
  if (this->Year < d.Year) return true;
  if (this->Year > d.Year) return false;
  if (this->Month < d.Month) return true;
  if (this->Month > d.Month) return false;
  if (this->Day < d.Day) return true;
  return false;
}

bool fDate::operator> (const fDate &d)
{
  if (*this < d) return false;
  if (*this == d) return false;
  return true;
}

void fDate::operator= (const fDate &d)
{
  this->Year = d.Year;
  this->Month = d.Month;
  this->Day = d.Day;
}

double fDate::dJulian ()
{
  int DaysInYear = 365,
    JulianDay = 0;
  if (leapYear (Year)) DaysInYear++;
  JulianDay = JDays[Month] + Day;
  if (leapYear (Year) &&  (Month > 2))
    JulianDay++;
  return (Year + 1.0 * (JulianDay - 1) / DaysInYear);
}

