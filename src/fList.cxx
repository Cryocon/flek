// $Id: fList.cxx,v 1.3 2000/02/17 18:28:02 jamespalmer Exp $

// Source code for the generic fList class

#include <Flek/fList.h>

fList::fList ()
  : node (NULL), length (0), useCopy (true)
{
  // Allocate memory for the control node
  // which will always be at the end of the list
  node = new fListNodePtr;
  node->setPrev(node);  node->setNext(node);
}

fReference fList::front (void)
{
  return *begin ();
}

fConstReference fList::front (void) const
{
  return *begin ();
}

fReference fList::back (void)
{
  fIterator temp = end ();
  --temp;
  return *temp;
}

fConstReference fList::back (void) const
{
  fConstIterator temp = end ();
  --temp;
  return *temp;
}

// Insert a value before a specified position
void fList::insertBefore (fIterator& pos, fConstReference data)
{
  // Create a new node
  fListNode::Ptr temp = new fListNodePtr;
  // Node referred to by Iterator
  fLink::Ptr itr_node = pos.node;

  if (useCopy)
    temp->setData (data->copy());
  else 
    temp->setData (data);
  
  temp->setNext (itr_node);
  temp->setPrev (itr_node->prev());

  // Update links of adjacent old nodes
  (itr_node->prev())->setNext (temp);
  itr_node->setPrev (temp);
  
  ++length;
}

// Insert a value after a specified position
void fList::insertAfter (fIterator& pos, fConstReference data)
{
  // Create a new node
  fListNode::Ptr temp = new fListNodePtr;
  // Node referred to by Iterator
  fLink::Ptr itr_node = pos.node;
  
  if (useCopy)
    temp->setData (data->copy());
  else
    temp->setData (data);
  
  temp->setNext (itr_node->next());
  temp->setPrev (itr_node);
  
  // Update links of adjacent old nodes
  (itr_node->next ())->setPrev (temp);
  itr_node->setNext (temp);
  
  ++length;
}

// Insert a range of values before a specified position
void fList::insertBefore (fIterator& pos, fConstIterator& first, fConstIterator& last)
{
  // Assumes that 'last' can be reached from 'first' through a finite
  // number of increment ( ++ ) operations
  // Otherwise this will go into an infinite loop!
  while (first != last)
    {
      insertBefore (pos, *first);
      ++first;
    }
}

// Insert a range of values after a specified position
void fList::insertAfter (fIterator& pos, fConstIterator& first, fConstIterator& last)
{
  // Assumes that 'last' can be reached from 'first' through a finite
  // number of increment ( ++ ) operations
  // Otherwise this will go into an infinite loop!
  
  // Insert in reverse order to preserve original sequence of first to last
  while (last != first)
    {
      insertAfter (pos, *last);
      --last;
    }
  insertAfter (pos, *first);
}

void fList::push_front (fConstReference data)
{
  fIterator temp = begin ();
  insertBefore (temp, data);
}

void fList::push_back (fConstReference data)
{
  fIterator temp = end ();
  insertBefore (temp, data);
}

void fList::erase (fIterator& pos)
{
  // Node referred to by Iterator
  fLink::Ptr itr_node = pos.node;

  // Free memory associated with the data field
  // Can we just say 'delete itr_node->data' ??
  
  // This needs to be modified, since we can't access the pointer directly
  if ((useCopy) && (itr_node->data()))
    delete (itr_node->data());
  itr_node->setData (NULL);

  // Update adjacent links
  (itr_node->prev())->setNext (itr_node->next());
  (itr_node->next())->setPrev (itr_node->prev());

  // Delete the memory allocated for node
  delete itr_node;

  --length;
}

void fList::erase (fConstReference data)
{
  fIterator first = begin();
  fIterator last = end();

  while (first != last)
    {
      if (*first == data)
	{
	  erase (first); break;
	}
      ++first;
    }
}

void fList::erase (fIterator& first, fIterator& last)
{
  // Assumes that 'last' can be reached from 'first' through a finite
  // number of increment ( ++ ) operations
  fIterator next;
  while (first != last)
    {
      next = first;
      next++;
      erase (first); 
      first = next;
    }
}

void fList::erase (void)
{
  fIterator temp1, temp2;
  temp1 = begin (); 
  temp2 = end ();
  erase (temp1, temp2);
}

void fList::pop_front (void)
{
  fIterator temp = begin ();
  erase (temp);
}

void fList::pop_back (void)
{
  fIterator temp = end ();
  --temp;        // end() returns NULL node at end of list
  erase (temp);
}

fList::fList (const fList& new_list)
  : node(NULL), length(0), useCopy(new_list.useCopy)
{
  // Create control node and insert the new list at the beginning
  node = new fListNodePtr;
  node->setPrev (node);  node->setNext (node);
  
  fIterator temp1;
  fConstIterator temp2,temp3;
  temp1 = begin ();
  temp2 = new_list.begin ();
  temp3 = new_list.end ();
  temp3--;
  insert (temp1, temp2, temp3);
}

fList::~fList()
{
  // Erase the whole list and delete the control node
  erase ();
  delete node;
}

fList& fList::operator = (const fList& new_list)
{
  // Does not change useCopy flag.
  if (this != &new_list)
    {
      // Erase all existing nodes and insert new list at beginning
      erase ();
      
      fIterator first1 = begin ();
      
      if (new_list.size () > 0) // non empty list.
	{
	  fConstIterator first2 = new_list.begin ();
	  fConstIterator last2 = new_list.end ();
	  last2--;
	  
	  insert (first1, first2, last2);
	}
    }

  return *this;
}

fIterator fList::getNode (fConstReference data)
{
  fIterator first = begin ();
  fIterator last = end ();
  
  while (first != last)
    {
      if (*first == data) return first;
      ++first;
    }
  
  return fIterator ();
}

fConstIterator fList::getNode (fConstReference data) const
{
  fConstIterator first = begin ();
  fConstIterator last = end ();

  while ( first != last )
     {
       if ( *first == data ) return first;
       ++first;
     }

  return fConstIterator ();
}

fValue fList::get (uint i) const
{
  fConstIterator first = begin ();
  fConstIterator last = end ();
  uint count=0;
  fValue element = NULL;
  
  while (first != last)
     {
       if ( count == i )
          {
            element = *first; break;
          }
       ++count; ++first;
     }
  return element;
}

void fList::set (uint i, fConstReference data) 
{
  fIterator first = begin ();
  fIterator last = end ();
  uint count=0;
  
  while (first != last)
     {
       if ( count == i )
          {
            first.node->setData (data); 
	    break;
          }
       ++count; ++first;
     }
}

fIterator fList::next (fIterator pos) 
{
  fIterator node = pos;
  ++node;
  if (node == end ()) ++node;
  return node;
}

fConstIterator fList::next(fConstIterator pos) const 
{
  fConstIterator node = pos;
  ++node;
  if (node == end ()) ++node;
  return node;
}

fIterator fList::prev (fIterator pos) 
{
  fIterator node = pos;
  --node;
  if (node == end ()) --node;
  return node;
}

fConstIterator fList::prev (fConstIterator pos) const
{
  fConstIterator node = pos;
  --node;
  if (node == end ()) --node;
  return node;
}

void fList::apply (fFunctionPtr func)
{
  fIterator first = begin ();
  fIterator last = end ();

  while (first != last)
    {
      func (*first);
      ++first;
    }
}

void fList::apply (fConstFunctionPtr func) const
{
  fConstIterator first = begin ();
  fConstIterator last = end ();

  while (first != last)
    {
      func (*first);
      ++first;
    }
}

