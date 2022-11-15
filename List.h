////////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
////////////////////////////////////////////////////////////////////////////////

#include <iostream> // ostream

namespace CS170
{
  //! Linked List
  class List
  {
    public:
        // Three constructors
        
        //! Default Constructor
        List();
        
        //! Converts an array into a linked list
        List(const int *array, const int size);
        
        //! Copy Constructor
        List(const List &copy);
        
        //! Destructor
        ~List();
        
        // Seven methods:
        //! adds the item to the front of the list
        void push_front(int value);
        
        //! adds the item to the end of the list
        void push_back(int value);
        
        //! pop_front, removes the first item in the list
        void pop_front();
        
        //! returns the first item in the list
        int front() const;
        
        //! returns the number of items in the list
        int size() const;
        
        //! returns true if empty, else false
        bool empty() const;
        
        //! clears the list (removes all of the nodes)
        void clear();

        // Five operators: 
        //! Make 2 lists contain the same values
        List &operator=(const List &rhs);
        
        //! Adds the Nodes from rhs to the end of the list
        List &operator+=(const List &rhs);
        
        //! Creates a new list that contains values from both lists
        List operator+(const List &rhs) const;
        
        //   operator[] (2 of these)
        //! returns the value at the node index
        int &operator[](const int index);
        
        //! returns the value in the node index
        int operator[](const int index) const;

        //! Output operator for printing lists (<<)
      friend std::ostream & operator<<(std::ostream & os, const List &list);

        //! Returns the number of Lists that have been created
      static int list_count();

        //! Returns the number of Nodes that are still alive
      static int node_count();

    private:

        //! used to build a linked list of integers
      struct Node
      {
        Node(int);              //!< constructor
        ~Node();                //!< destructor
        Node *next;             //!< pointer to the next Node
        int data;               //!< the actual data in the node
        static int nodes_alive; //!< count of nodes still allocated
      };

      Node *head_; //!< pointer to the head of the list
      Node *tail_; //!< pointer to the last node
      int size_;   //!< number of items on the list

      static int list_count_;         //!< number of Lists created
      Node *new_node(int data) const; //!< allocate node, initialize data/next
  };
} // namespace CS170

#endif
////////////////////////////////////////////////////////////////////////////////
