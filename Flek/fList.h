/* -*-C++-*- 

   "$Id: fList.h,v 1.3 2000/02/19 18:33:54 jamespalmer Exp $"
   
   Copyright 1999-2000 by the Flek development team.
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
   
   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA.
  
   Please report all bugs and problems to "flek-devel@sourceforge.net".
   
*/

#ifndef _LIST_HH_
#define _LIST_HH_

#include <Flek/fBase.h>
#include <Flek/fListNode.h>
#include <Flek/fListIterator.h>

typedef unsigned int uint;
typedef size_t Size;

typedef void (*fFunctionPtr)(fReference data);
typedef void (*fConstFunctionPtr)(fConstReference data);

/** @package libflek_core
 * The generic fList class. The node is a pointer to a fListNode which is an ABC
 * This list uses the PtrfListNode as the node of the list
 * Derived lists can use some other node derived from fListNode or PtrListNode
 * 
 * This list is derived from BaseObject to allow list of lists
 */
class fList : public fBase
{
public:

  typedef fList * Ptr;

  //--- fList class member functions ---//

  /**
   * Default constructor.
   */
  fList();

  /**
   * Copy constructor.
   */
  fList(const fList& new_list, bool Copy=true);

  /**
   * Destructor.
   */
  ~fList();

  /**
   * Assignment operator.
   */
  fList& operator = (const fList& new_list);
  
  /**
   * Copy function - implement base class fn
   */
  virtual fBase::Ptr copy(void) const
    {
      Ptr newlist = new fList(*this);
      return newlist;
    }
  
  /**
   * Is list empty.
   */
  bool empty(void) const
    {
      return length == 0;
    }
  
  /**
   * Size of list.
   */
  Size size(void) const
    {
      return length;
    }
  
  /**
   * Beginning of list.
   */
  fIterator begin(void)
    {
      return fIterator(node->next());
    }
  
  /**
   * Beginning of list.
   */
  fConstIterator begin(void) const
    {
      return fConstIterator(node->next());
    }

  /**
   * End of list  
   */
  fIterator end (void)
    {
      return fIterator(node);
    }
  
  /**
   * End of list
   */
  fConstIterator end (void) const
    {
      return fConstIterator (node);
    }

  /**
   * Value at front of list
   */
  fReference front(void);

  /**
   * Value at front of list
   */
  fConstReference front(void) const;
  
  /**
   * Value at end of list
   */
  fReference back(void);

  /**
   * Value at end of list.
   */
  fConstReference back(void) const;
  
  //-- Insertion functions --//
  
  /**
   * Insertion before the iterator position with a single value.
   */
  void insertBefore (fIterator& pos, fConstReference data, bool Copy=false); 

  void insertBefore (fIterator& pos, fBase & data, bool Copy=true)
    {
      insertBefore (pos, &data, Copy);
    }
  
  /**
   * Insertion after the iterator position with a single value.
   */
  void insertAfter (fIterator& pos, fConstReference data, bool Copy=false);

  void insertAfter (fIterator& pos, fBase & data, bool Copy=true)
    {
      insertAfter (pos, &data, Copy);
    }
  
  /**
   * Insertion (by default) after the iterator position with a single value.
   */
  void insert (fIterator& pos, fConstReference data, bool Copy=false)
    {
      insertAfter(pos, data, Copy);
    }

  /**
   * Insertion before the iterator position with a range of values.
   * (Assumes last can be reached from first with a finite number of ++
   * operations.
   */
  void insertBefore(fIterator& pos, fConstIterator& first, fConstIterator& last, bool Copy=false);

  /**
   * Insertion after the iterator position with a range of values.
   * (Assumes last can be reached from first with a finite number of ++
   * operations.
   */
  void insertAfter(fIterator& pos, fConstIterator& first, fConstIterator& last, bool Copy=false);

  /**
   * Insertion (by default) after the iterator position with a range of values.
   * (Assumes last can be reached from first with a finite number of ++
   * operations.
   */
  void insert(fIterator& pos, fConstIterator& first, fConstIterator& last, bool Copy=false)
    {
      insertAfter (pos,first,last,Copy);
    }
  
  /**
   * Insert at beginning from an fBase (or subclass) pointer.  By default a new copy
   * of the data <b>will not</b> be made.
   */
  void push_front (fConstReference data, bool Copy=false);

  /**
   * Insert at beginning from an fBase reference.  By default a new copy <b>will</b>
   * be made.
   */
  void push_front (fBase & data, bool Copy=true)
    {
      push_front (&data, Copy);
    }

  /**
   * Insert at end from an fBase (or subclass) pointer.  By default a new copy
   * of the data <b>will not</b> be made.
   */
  void push_back (fConstReference data, bool Copy=false);

  /**
   * Insert at end from an fBase reference.  By default a new copy <b>will</b>
   * be made.
   */
  void push_back (fBase & data, bool Copy=true)
    {
      push_back (&data, Copy);
    }

  
  //-- Deletion functions --//
  
  /**
   * Erase specified node.
   */
  void erase (fIterator& pos);

  /**
   * Erase node with specified data.
   */
  void erase (fConstReference data);

  /**
   * Erase range of nodes.
   */
  void erase (fIterator& first, fIterator& last);

  /**
   * Erase all nodes.
   */
  void erase (void);
  
  /**
   * Delete first node.
   */
  void pop_front (void);

  /**
   * Delete last node.
   */
  void pop_back (void);
  
  // Search functions
  
  /**
   * Get node with specified data.
   */
  fIterator getNode (fConstReference data);
  fConstIterator getNode (fConstReference data) const; // const version
  
  // Array type access functions

  /**
   * Get i'th element.
   */
  fValue get (uint i) const;

  /** 
   * Set i'th element to given data.
   */
  void set (uint i, fConstReference data);
  
  // Access list as circular list

  /**
   * Get the next valid node.
   */
  fIterator next (fIterator pos);

  /**
   * Get the next valid node.
   */
  fConstIterator next (fConstIterator pos) const;

  /**
   * Get the previous valid node.
   */  
  fIterator prev (fIterator pos);

  /**
   * Get the previous valid node.
   */  
  fConstIterator prev (fConstIterator pos) const;
  
  // Functions to access whole list
  
  /**
   * Apply given function to all elements.
   */
  void apply (fFunctionPtr func);

  /**
   * Apply given function to all elements.
   */
  void apply (fConstFunctionPtr func) const;

protected:
  
  // Pointer to first node
  fLink::Ptr node; 

  // Length of list
  Size length;

};

#endif

