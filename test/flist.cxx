#include <Flek/fBase.h>
#include <Flek/fList.h>
#include <iostream.h>

class A : public fBase
{
public:
  
  int a;
  
  A (int val=1)
    : fBase (), a (val)
    {}
  
  A (const A& newa)
    : fBase (newa), a (newa.a)
    {}
  
  virtual ~A ()
    {}
  
  A& operator = (const A& newa)
    {
      fBase :: operator = (newa);
      a = newa.a;
      
      return *this;
    }
  
  virtual fBase::Ptr copy (void) const
    {
      A * newa = new A (*this);
      return newa;
    }
  
  friend ostream& operator << (ostream& o, const A& aobj)
    {
      o << "A :: a = " << aobj.a << endl;
      return o;
    }
};

typedef A * APtr;

void main (void)
{
  fList list;
  fIterator p;
  fIterator last;

  A a(1), b(2);
  
  //cout << "Data Set: " << endl;
  //cout << a1 << a2 << a3 << endl << endl;

  cout << "Testing node copy.. " << endl;
  
  a.a = 1;
  list.push_back (a);
  a.a = 2;
  list.push_back (a);
  a.a = 3;
  list.push_back (a);

  cout << "Testing node reference.. " << endl;

  b.a = 4;
  list.push_back (&b);  
  b.a = 5;
  list.push_back (&b);
  b.a = 6;
  list.push_back (&b);

  cout << "List should read: 1 2 3 6 6 6" << endl;
  
  cout << "Testing Iteration: " << endl;
  last = list.end();
  for (p = list.begin (); p != last; p++)
    {
      cout << *((A *)(*p));
    }

  A * a4ptr;
  a4ptr = (A *)list.get (1);
  fIterator pos = list.getNode (a4ptr);
  
  a.a = 7;
  list.insertAfter (pos, a);
  a.a = 9;
  list.insertBefore (pos, a);

  cout << endl << endl;
  
  cout << "List should read: 1 9 2 7 3 6 6 6" << endl;
  
  cout << "Testing Insertion: " << endl;
  last = list.end();
  for (p = list.begin (); p != last; p++)
    {
      cout << *((A *)(*p));
    }

  cout << "Testing List Copy" << endl;

  fList list2 = list;

  cout << "..." << endl;

  last = list2.end();
  for (p = list2.begin (); p != last; p++)
    {
      cout << *((A *)(*p));
    }

  cout << "Done" << endl;
}
