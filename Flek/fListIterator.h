/* -*-C++-*- 

   "$Id: fListIterator.h,v 1.2 2000/02/17 17:13:16 jamespalmer Exp $"
   
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

#ifndef _LIST_ITERATOR_HH_
#define _LIST_ITERATOR_HH_

#include <Flek/fListNode.h>

typedef fListNode fLink;

/** @package libflek_core
 * Generic Iterator for the list
 */
class fIterator
{
public:
  
  /** 
   * Default constructor.
   */
  fIterator ()
    : node (NULL)
    {}

  /** 
   * Copy constructor.
   */
  fIterator (const fIterator& itr)
    : node (itr.node)
    {}
  
  /**
   * Destructor.
   */
  ~fIterator ()
    {
      node = NULL;
    }
  
  /**
   * Assignment operator.
   */
  fIterator& operator = (const fIterator& itr)
    {
      node = itr.node;
      return (*this);
    }
          
  // Comparison operators

  /** 
   * Equality operator.
   */
  bool operator == (const fIterator& itr) const
    {
      return node == itr.node;
    }

  /**
   * Inequality operator.
   */
  bool operator != (const fIterator& itr) const
    {
      return node != itr.node;
    }

  /**
   * Dereference operator.
   */  
  fReference operator * () const
    {
      return this->dereference ();
    }
  
  //--- Manipulators ---//
  
  /**
   * Prefix increment.
   */
  void operator ++ ()
    {
      increment ();
    }
  
  /** 
   * Postfix increment.
   */
  void operator ++ (int)
    {
      increment ();
    }
  
  /** 
   * Prefix decrement.
   */
  void operator -- ()
    {
      decrement ();
    }
  
  /** 
   * Postfix decrement.
   */
  void operator -- (int)
    {
      decrement ();
    }

protected:
  
  // A node of the list
  fLink::Ptr node;
  
  /**
   * One argument constructor.
   */
  fIterator (fLink::Ptr new_node)
    : node (new_node)
    {}
  
  /** 
   * Increment function.
   */
  void increment (void)
    {
      node = node->next ();
    }
  
  /**
   * Decrement function.
   */
  void decrement (void)
    {
      node = node->prev ();
    }
  
  /**
   * Dereference function.
   */
  fReference dereference (void) const 
    {
      return node->data ();
    }
  
private:
  
  friend class fList;
  friend class fConstIterator;  

};

/**
 * Generic Iterator for the list - const version
 */
class fConstIterator
{
public:
  
  /** 
   * Default constructor.
   */
  fConstIterator()
    : node (NULL)
    {}
  
  /** 
   * Copy constructor.
   */
  fConstIterator(const fConstIterator& itr)
    : node (itr.node)
    {}
  
  /** 
   * Copy constructor.
   */
  fConstIterator(const fIterator& itr)
    : node (itr.node)
    {}

  /**
   * Destructor.
   */  
  ~fConstIterator ()
    {
      node = NULL;
    }
  
  /**
   * Assignment operator.
   */
  fConstIterator& operator = (const fConstIterator& itr)
    {
      node = itr.node;
      return (*this);
    }

  /**
   * Assignment operator.
   */
  fConstIterator& operator = (const fIterator& itr)
    {
      node = itr.node;
      return (*this);
    }
          
  // Comparison operators

  /** 
   * Equality operator.
   */          
  bool operator == (const fConstIterator& itr) const
    {
      return node == itr.node;
    }

  /**
   * Inequality operator.
   */
  bool operator != (const fConstIterator& itr) const
    {
      return node != itr.node;
    }

  /**
   * Dereference operator.
   */
  fConstReference operator * () const
    {
      return this->dereference();
    }
     
  // Manipulators
  
  /**
   * Prefix increment.
   */
  void operator ++ ()
    {
      increment ();
    }
   
  /** 
   * Postfix increment.
   */
  void operator ++ (int)
    {
      increment ();
    }

  /** 
   * Prefix decrement.
   */
  void operator -- ()
    {
      decrement ();
    }

  /** 
   * Postfix decrement.
   */
  void operator -- (int)
    {
      decrement ();
    }

protected:
  
  fLink::Ptr node;  // A node of the list
  
  fConstIterator (fLink::Ptr new_node)                   // 1 arg constructor
    : node(new_node)
    {}
  
  /** 
   * Increment function.
   */
  void increment (void)
    {
      node = node->next ();
    }
  
  /**
   * Decrement function.
   */
  void decrement (void)
    {
      node = node->prev ();
    }

  /**
   * Dereference function.
   */
  fConstReference dereference (void) const
    {
      return node->data();
    }
  
private:
  
  friend class fList;  
  
};

#endif


