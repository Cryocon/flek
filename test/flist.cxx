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

  A a1(1), a2(2), a3(3);
  
  cout << "Data Set: " << endl;
  cout << a1 << a2 << a3 << endl << endl;
  
  list.push_back (&a1);
  list.push_back (&a2);
  list.push_back (&a3);

  cout << "Testing Iteration: " << endl;
  last = list.end();
  for (p = list.begin (); p != last; p++)
    {
      cout << *((A *)(*p));
    }

  A * a4ptr;
  a4ptr = (A *)list.get (1);
  fIterator pos = list.getNode (a4ptr);
  
  list.insertAfter (pos, &a1);
  list.insertBefore (pos, &a3);

  cout << endl << endl;

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
