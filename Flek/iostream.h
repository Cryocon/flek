// $Id: iostream.h,v 1.1 2000/02/06 08:43:40 jamespalmer Exp $

#ifndef _STREAMIO_HH_
#define _STREAMIO_HH_

// Miscellaneous functions for operating on IO streams in C++

#include <iostream.h>
#include <iomanip.h>

inline void removeWhiteSpace(istream& i)
{
  char c;

  while ( i )
     {
       i.get(c);
       if ( c != ' ' && c != '\t' && c != '\n' )
          {
            i.putback(c);
            break;
          }
     }
}

inline void removeSpaces(istream& i)
{
  char c;

  while ( i )
     {
       i.get(c);
       if ( c != ' ' )
          {
            i.putback(c);
            break;
          }
     }
}

inline void removeSpacesAndTabs(istream& i)
{
  char c;

  while ( i )
     {
       i.get(c);
       if ( c != ' ' && c != '\t' )
          {
            i.putback(c);
            break;
          }
     }
}

inline void readTillEOL(istream& i)
{
  char c;

  i.get(c);
  while ( i && c != '\n' )
     i.get(c);
}

#endif // #ifndef _STREAMIO_HH_

