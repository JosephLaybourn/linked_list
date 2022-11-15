/******************************************************************************/
/*!
\file   List.cpp
\author Joey Laybourn
\par    email: j.laybourn\@digipen.edu
\par    DigiPen login: j.laybourn
\par    Course: CS170
\par    Section: B
\par    Lab: 8
\date   3/7/2018
\brief  
    This file contains the implementation of the following functions for the 
    List assignment.
      
    Functions include:
    
       + List
       + clear
       + empty
       + front
       + list_count
       + new_node
       + node_count
       + operator+
       + operator+=
       + operator=
       + operator[]
       + pop_front
       + push_front
       + push_back
       + size
       + ~List
       + nodes_alive
       + Node
       + ~Node
       + new_node
    
  Hours spent on this assignment: 3

  Specific portions that gave you the most trouble: Scope Resolution
*/
/******************************************************************************/

#include <iostream>
#include <iomanip> // setw
#include "List.h"  // List class

namespace CS170
{
  int List::Node::nodes_alive = 0; //!< the amount of Nodes alive
  int List::list_count_ = 0;       //!< the amount of lists created

  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  // Node methods
  // Constructor, destructor

    /**************************************************************************/
    /*!
    \brief
    Creates a new Node with some data in it.  
    */
    /**************************************************************************/
  List::Node::Node(int number)
  {
    data = number; // sets the argument to the Node data
    next = NULL;   // sets the next pointer to NULL
  }

    /**************************************************************************/
    /*!
    \brief
    Node destructor.  Does nothing
    */
    /**************************************************************************/
  List::Node::~Node()
  {
    nodes_alive--;
  }

  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  // public methods in this order: 
  // Constructors (default, copy, non-defaults), destructor, operators, others

    /**************************************************************************/
    /*!
    \brief
    Default constructor.  Initializes all variables
    */
    /**************************************************************************/
  List::List()
  {
    head_ = NULL;  // initializes the head pointer
    tail_ = NULL;  // initializes the tail pointer
    size_ = 0;     // initializes the size to 0
    list_count_++; // increments the list count
  }

    /**************************************************************************/
    /*!
    \brief
    Copy constructor.  Copies all the data
    
    \param copy
    the list that it is copied from
    */
    /**************************************************************************/
  List::List(const List &copy)
  {
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
    list_count_++;

    *this = copy;
  }

    /**************************************************************************/
    /*!
    \brief
    Creates a new Node with some data in it.  
    
    \param array
    the values that are to be stored in the list
    
    \param size
    the size of the array
    */
    /**************************************************************************/
  List::List(const int *array, const int size)
  {
    head_ = NULL;  // initializes the head pointer
    tail_ = NULL;  // initializes the tail pointer
    size_ = 0;     // initializes the size to 0
    list_count_++; // increments the list count

    if (array) // checks to see if the array has any values
    {
      for (int i = 0; i < size; i++)
      {
        push_back(array[i]);
      }
    }
  }

    /**************************************************************************/
    /*!
    \brief
    Frees all the nodes in the list
    */
    /**************************************************************************/
  List::~List()
  {
    clear(); // clear function removes all active Nodes
  }

    /**************************************************************************/
    /*!
    \brief
    copies all the data from rhs to this class
    
    \param rhs
    the list that will be copied
    
    \return List
    the copied list
    */
    /**************************************************************************/
  List &List::operator=(const List &rhs)
  {
    for (int i = 0; i < rhs.size_; i++)
    {
      push_back(rhs[i]);
    }
    return *this; // return this class
  }

    /**************************************************************************/
    /*!
    \brief
    Adds nodes to the back of the list
    
    \param rhs
    the list containing all the nodes to add to the back of the list
    
    \return List
    the updated list 
    */
    /**************************************************************************/
  List &List::operator+=(const List &rhs)
  {
    Node *temp = rhs.head_; // Head node that will be added to the list

    while (temp) // interates for the duration of the list
    {
      push_back(temp->data); // adds data to the back of the Node
      temp = temp->next;     // moves to the next Node
    }
    return *this; // returns this class
  }

    /**************************************************************************/
    /*!
    \brief
    Combines all the nodes together of two lists and stores it into a third list
    
    \param rhs
    the back of the new list
    
    \return List
    the new list that was created
    */
    /**************************************************************************/
  List List::operator+(const List &rhs) const
  {
    List combinedList(*this); // makes a clone of this class

    combinedList += rhs; // adds the values of rhs to this list

    return combinedList; // returns the new list
  }

    /**************************************************************************/
    /*!
    \brief
    gets a value at a certain node
    
    \param index
    the Node that will be checked
    
    \return int
    the value inside the specified Node
    */
    /**************************************************************************/
  int &List::operator[](const int index)
  {
    Node *indexNode = head_; // Node to walk through index times

    for (int i = 0; i < index; i++) // finds the Node at index position
    {
      indexNode = indexNode->next;  // goes to the next Node
    }
    return indexNode->data; // returns the data at this index
  }
    
    /**************************************************************************/
    /*!
    \brief
    gets a value at a certain node
    
    \param index
    the Node that will be checked
    
    \return int
    the value inside the specified Node
    */
    /**************************************************************************/
  int List::operator[](const int index) const
  {
    Node *indexNode = head_; // Node to walk through index times

    for (int i = 0; i < index; i++) // finds the Node at index position
    {
      indexNode = indexNode->next;  // goes to the next Node
    }
    return indexNode->data; // returns the data at this index
  }


    /**************************************************************************/
    /*!
    \brief
    adds a Node to the front of the list
    
    \param value
    the value that will be in the new node
    */
    /**************************************************************************/
  void List::push_front(int value)
  {
    size_++;
    Node *newHead = new_node(value);

    if (!head_)
    {
      head_ = newHead;
      tail_ = head_;
      return;
    }
    Node *prevHead = head_;
    head_ = newHead;
    head_->next = prevHead;
  }

    /**************************************************************************/
    /*!
    \brief
    adds a Node to the back of the list
    
    \param value
    the value that will be in the new node
    */
    /**************************************************************************/
  void List::push_back(int value)
  {
    size_++; // increments the size of the list
    Node *newTail = new_node(value);
    if (!head_)
    {
      head_ = newTail;
      tail_ = head_;
      return;
    }
    tail_->next = newTail;
    tail_ = tail_->next;
  }

    /**************************************************************************/
    /*!
    \brief
    removes the first Node of the list
    */
    /**************************************************************************/
  void List::pop_front()
  {
    if (!head_) // NULL check the List
    {
      return;
    }
    Node *headTemp = head_; // saves this Node to delete later
    head_ = head_->next;    // makes the head point to the Node after it
    delete headTemp;        // delete the old head
    size_--;                // decrement the size
  }

    /**************************************************************************/
    /*!
    \brief
    returns the value of the front node
    
    \return int
    the value of the front node
    */
    /**************************************************************************/
  int List::front() const
  {
    return head_->data; // returns the data at the beginning Node
  }

    /**************************************************************************/
    /*!
    \brief
    returns the amount of nodes
    
    \return int
    the amount of nodes in the list
    */
    /**************************************************************************/
  int List::size() const
  {
    return size_; // returns the size of the list
  }

  /**************************************************************************/
    /*!
    \brief
    checks to see if the list is empty
    
    \return bool
    true if empty, false if not
    */
    /**************************************************************************/
  bool List::empty() const
  {
    if (size_ == 0) // returns true if the list is empty
    {
      return true;
    }
    else            // returns false if there are Nodes in the list
    {
      return false;
    }
  }

    /**************************************************************************/
    /*!
    \brief
    removes all the nodes in the list
    */
    /**************************************************************************/
  void List::clear()
  {
    if (!head_) // NULL check the list
    {
      return;
    }
    int sizeSaved = size_;
    for (int i = 0; i < sizeSaved; i++)
    {
      pop_front(); // remove the head Node
    }
    size_ = 0;    // sets size to 0
    head_ = NULL; // sets head to NULL
    tail_ = NULL; // sets tail to NULL
  }

    /**************************************************************************/
    /*!
    \brief
    returns the amount of lists currently active
    
    \return int
    the amount of lists created
    */
    /**************************************************************************/
  int List::list_count()
  {
    return list_count_; // returns the amount of lists created
  }

    /**************************************************************************/
    /*!
    \brief
    returns the amount of Nodes allocated
    
    \return int
    the amount of nodes allocated
    */
    /**************************************************************************/
  int List::node_count()
  {
    return Node::nodes_alive; // returns the amount of Nodes active
  }

  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  // private methods

    /**************************************************************************/
    /*!
    \brief
    allocates a new Node
   
    \param data
    the value in the Node
    
    \return Node
    the Node that was created
    */
    /**************************************************************************/
  List::Node *List::new_node(int data) const
  {
    Node::nodes_alive++;   // increments the amount of Nodes alive
    return new Node(data); // returns a Node with a specified value
  }

  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  // non-member methods

    /**************************************************************************/
    /*!
    \brief
    prints out the values in a List
    
    \param os
    the output stream
    
    \param list
    the list being printed out
    
    \return ostream
    the output stream
    */
    /**************************************************************************/
  std::ostream & operator<<(std::ostream & os, const List &list)
  {
    // Start at the first node
    List::Node *pnode = list.head_;

    // Until we reach the end of the list
    while (pnode != 0)
    {
      os << std::setw(4) << pnode->data; // print the data in this node
      pnode = pnode->next;               // move to the next node
    }

    os << std::endl; // extra newline for readability
    return os;
  }

} //namespace CS170
