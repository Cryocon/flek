#include <Flek/fDomAttr.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * fDomAttr::Klass        = "fDomAttr";
char * fDomAttrNumber::Klass  = "fDomAttrNumber";
char * fDomAttrInteger::Klass = "fDomAttrInteger";
char * fDomAttrDate::Klass    = "fDomAttrDate";

fDomAttr::fDomAttr ()
{
  Name = 0;
  Value = 0;
}

fDomAttr::fDomAttr (const fDomAttr& o)
{
  Name = strdup (o.Name);
  Value = strdup (o.Value);
}

fBase::Ptr fDomAttr::copy (void) const
{
  return (new fDomAttr (*this));
}

double fDomAttr::valueNumber () 
{ 
  char *end;
  double d;
  if (!strcmp (Value, "true"))
    return 1;
  if (!strcmp (Value, "false"))
    return 0;
  d = strtod (Value, &end);
  if (end == Value)
    return 0; // FIXME - it should == NaN;
  return d;
}

void fDomAttr::valueNumber (double d)
{
  char tmp[16];
  sprintf (tmp, "%g", d);
  value (tmp);
}

void fDomAttr::valueBoolean (bool d)
{
  if (d)
    value ("true");
  else
    value ("false");
}

bool fDomAttr::valueBoolean ()
{
  if (!strcmp (Value, "true"))
    return true;
  if (!strcmp (Value, "false"))
    return false;
  if (strlen (Value) > 0)
    return true;
  return false;
}

void fDomAttr::name (char *v)
{
  if (Name) free (Name);
  Name = strdup (v);
}

void fDomAttr::value (char *v)
{
  if (Value) free (Value);
  Value = strdup (v);
}

fDomAttrNumber::fDomAttrNumber ()
{
  Number = 0;
}

fDomAttrNumber::fDomAttrNumber (const fDomAttrNumber &n) : fDomAttr (n)
{
  Number = n.Number;
}

fBase::Ptr fDomAttrNumber::copy (void) const
{
  return (new fDomAttrNumber (*this));
}

char * fDomAttrNumber::value () 
{
  char tmp[16];
  sprintf (tmp, "%f", Number);
  if (Value) free (Value);
  Value = strdup (tmp);
  return (Value);
}

void fDomAttrNumber::value (char *d)
{
  sscanf (d, "%lf", &Number);
}

fDomAttrInteger::fDomAttrInteger ()
{
  Number = 0;
}

fDomAttrInteger::fDomAttrInteger (const fDomAttrInteger &n) : fDomAttr (n)
{
  Number = n.Number;
}

fBase::Ptr fDomAttrInteger::copy (void) const
{
  return (new fDomAttrInteger (*this));
}

char * fDomAttrInteger::value () 
{
  char tmp[16];
  sprintf (tmp, "%ld", Number);
  if (Value) free (Value);
  Value = strdup (tmp);
  return (Value);
}

void fDomAttrInteger::value (char *d)
{
  sscanf (d, "%ld", &Number);
}

fDomAttrDate::fDomAttrDate ()
{
}

fDomAttrDate::fDomAttrDate (const fDomAttrDate &n) : fDomAttr (n)
{
  Date = n.Date;
}

fBase::Ptr fDomAttrDate::copy (void) const
{
  return (new fDomAttrDate (*this));
}

char * fDomAttrDate::value () 
{
  char tmp[16];
  sprintf (tmp, "%d-%d-%d", Date.year (), Date.month (), Date.day ());
  if (Value) free (Value);
  Value = strdup (tmp);
  return (Value);
}

void fDomAttrDate::value (char *s)
{
  int m, d, y;
  sscanf (s, "%d-%d-%d", &y, &m, &d);
  Date.setDate (y, m, d);
}

double fDomAttrDate::valueNumber () 
{ 
  return (Date.year()*1000 
	  + Date.month()*100 
	  + Date.day()); 
}

void fDomAttrDate::valueNumber (double dd) 
{ 
  int y = (int)(dd / 1000);
  dd -= y;
  int m = (int)(dd / 100);
  dd -= m;
  int d = (int)dd;
  Date.setDate (y, m, d);

}

// Boolean is undefined for a date
bool fDomAttrDate::valueBoolean () 
{ 
  return true; 
}

void fDomAttrDate::valueBoolean (bool) 
{ }

fDate fDomAttrDate::valueDate ()
{ 
  return Date; 
}

void fDomAttrDate::valueDate (const fDate & d) 
{
  Date = d; 
}




/*

  fDomAttributeDouble
  fDomAttributeVector2
  fDomAttributeVector3
  fDomAttributeVector4


name   = fDomAttribute
radius = fDomAttributeDouble
center = fDomAttributeVector3
color  = fDomAttributeVector4

  <sphere name   = "mysphere" 
          radius = "5" 
          center = "0.3 5.67 33.2" 
          color  = "0.2 0.7 1.0 0.4" />

  <polygon name  = "mypolygon">
      <vertices>
         <vertex id = "0" point = "10 23 77" />
         <vertex id = "1" point = "10 23 77" />
         <vertex id = "2" point = "10 23 77" />
      </vertices>
      <edges>
         <edge id = "0" a = "0" b = "1" />
         <edge id = "1" a = "1" b = "2" />
         <edge id = "2" a = "2" b = "0" />
      </edges>
      <faces>
          <face id = "0" >
	     <edge i = "0" />
	     <edge i = "1" />
	     <edge i = "2" />
          </face>
      </faces>
  </polygon>


 */
