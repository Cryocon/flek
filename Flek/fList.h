/* -*-C++-*- 

   "$Id: fList.h,v 1.1 2000/02/16 21:23:57 jamespalmer Exp $"
   
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

/**
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
  
  fList();                                           // Default constructor
  fList(const fList& new_list);                       // Copy constructor
  ~fList();                                          // Destructor
  fList& operator = (const fList& new_list);          // Assignment operator
  
  
  virtual fBase::Ptr copy(void) const            // Copy function - implement base class fn
    {
      Ptr newlist = new fList(*this);
      return newlist;
    }
  
  void setCopyFlag(void)                            // Set the copy flag to true
    {
      useCopy = true;
    }
  
  void resetCopyFlag(void)                          // Reset the copy flag to false
    {
      useCopy = false;
    }
  
  bool empty(void) const                            // Is list empty
    {
      return length == 0;
    }
  
  Size size(void) const                             // Size of list
    {
      return length;
    }
  
  fIterator begin(void)                              // Beginning of list
    {
      return fIterator(node->next());
    }
  
  fConstIterator begin(void) const                   // Beginning of list
    {
      return fConstIterator(node->next());
    }
  
  fIterator end(void)                                // End of list
    {
      return fIterator(node);
    }
  
  fConstIterator end(void) const                     // End of list
    {
      return fConstIterator(node);
    }
  
  fReference front(void);                            // Value at front of list
  fConstReference front(void) const;                 // Value at front of list
  
  fReference back(void);                             // Value at end of list
  fConstReference back(void) const;                  // Value at end of list
  
  //-- Insertion functions --//
  
  // Insert a single value
  void insertBefore (fIterator& pos, fConstReference data); // Insertion before
  void insertAfter (fIterator& pos, fConstReference data); // Insertion after
  void insert (fIterator& pos, fConstReference data)   // Default insertion
    {
      insertAfter(pos, data);
    }

  // Insert a range of values - assumes last can be reached from first
  // through finite number of ++ operations
  void insertBefore(fIterator& pos, fConstIterator& first, fConstIterator& last);
  void insertAfter(fIterator& pos, fConstIterator& first, fConstIterator& last);
  void insert(fIterator& pos, fConstIterator& first, fConstIterator& last)
    {
      insertAfter (pos,first,last);
    }
  
  void push_front (fConstReference data);             // Insert at beginning 
  void push_back (fConstReference data);              // Insert at end
  
  
  //-- Deletion functions --//
  
  void erase (fIterator& pos);                        // Erase specified node
  void erase (fConstReference data);                  // Erase node with specified data
  void erase (fIterator& first, fIterator& last);      // Erase range of nodes
  void erase (void);                                 // Erase all nodes
  
  void pop_front (void);                             // Delete first node
  void pop_back (void);                              // Delete last node
  
  //-- Search functions --//
  
  fIterator getNode (fConstReference data);            // Get node with specified data
  fConstIterator getNode (fConstReference data) const; // const version
  
  //-- Array type access functions --//
  
  fValue get (uint i) const;                 // Get i'th element
  void set (uint i, fConstReference data);            // Set i'th element to given data
  
  //-- Access list as circular list --//
  
  fIterator next (fIterator pos);                      // Get next valid node
  fConstIterator next (fConstIterator pos) const;      // const version
  
  fIterator prev (fIterator pos);                      // Get prev valid node
  fConstIterator prev (fConstIterator pos) const;      // const version
  
  //-- Functions to access whole list --//
  
  void apply (fFunctionPtr func);                     // Apply given function to all elements
  void apply (fConstFunctionPtr func) const;          // const version

protected:
  
  // List class member data
  
  fLink::Ptr node; // Pointer to first node
  Size length;   // Length of list
  bool useCopy;  // Flag to indicate if the copy() function
                 // should be used during insertion
                 // Default is true
};

#endif

