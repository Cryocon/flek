/* -*-C++-*- 

   "$Id: fListNode.h,v 1.2 2000/02/17 17:13:16 jamespalmer Exp $"
   
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

#ifndef _LIST_NODE_HH_
#define _LIST_NODE_HH_

#include <Flek/fBase.h>
#include <stddef.h>

typedef fBase::Ptr fValue;
typedef fValue& fReference;
typedef const fValue& fConstReference;

/** @package libflek_core
 * Class for a node of the list. Declared outside the list class to 
 * allow other classes to be derived from this (which can redefine the 
 * next() and prev() operators
 *
 * Abstract Base Class for list node - defines interface only
 */
class fListNode
{
public:

    typedef fListNode * Ptr;

     fListNode ()
       {}

     fListNode (const fListNode&)
       {}

     virtual ~fListNode()
       {}

     fListNode& operator = (const fListNode&)
       {
         return (*this);
       }

     virtual Ptr prev (void) = 0;
     virtual Ptr next (void) = 0;
     virtual fReference data (void) = 0;

     virtual void setPrev (Ptr) = 0;
     virtual void setNext (Ptr) = 0;
     virtual void setData (fConstReference) = 0;
};

/**
 * fList node for list of pointers - derived from fListNode ABC
 * This node stores the next and prev pointers separately
 */
class fListNodePtr : public fListNode
{
public:

  typedef fListNodePtr * Ptr;

  /**
   * Default constructor
   */
  fListNodePtr ()
    : fListNode (), bopData (NULL), lnpNext (NULL), lnpPrev (NULL)
    {}

  /**
   * Copy constructor
   */
  fListNodePtr (const fListNodePtr& pln)
    : fListNode (pln), bopData (pln.bopData), lnpNext (pln.lnpNext), lnpPrev (pln.lnpPrev)
    {}
     
  /**
   * Destructor
   */
  ~fListNodePtr ()
    {}

  /**
   * Assignment operator
   */
  fListNodePtr& operator = (const fListNodePtr& pln)
    {
      fListNode :: operator = (pln);
      bopData = pln.bopData; lnpNext = pln.lnpNext; lnpPrev = pln.lnpPrev;
      return (*this);
    }
  
  /**
   * Return pointer to next node
   */
  fListNode::Ptr next (void)
    {
      return lnpNext;
    }
  
  /**
   * Return pointer to prev node
   */
  fListNode::Ptr prev (void)
    {
      return lnpPrev;
    }
  
  /**
   * Return the pointer to the data
   */
  fReference data (void)
    {
      return bopData;
    }

  void setNext (fListNode::Ptr lnp)
    {
      lnpNext = lnp;
    }
  
  void setPrev (fListNode::Ptr lnp)
    {
      lnpPrev = lnp;
    }
  
  void setData (fConstReference bop)
    {
      bopData = bop;
    }

protected:

  fValue bopData;  // Pointer to actual data
  fListNode::Ptr lnpNext;  // Pointer to next node
  fListNode::Ptr lnpPrev;  // Pointer to previous node
       
};

#endif
