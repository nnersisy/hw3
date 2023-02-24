#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  PComparator cp;
  int m2;
  std::vector<T> heapVec;


};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c)
{
  cp = c;
  m2 = m;
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap()
{

}

//push-----------------------------------
template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item){
  if(empty())
  {
    heapVec.push_back(item);
		return;
  }
	heapVec.push_back(item);
	int newp = heapVec.size() - 1;
	while(cp(heapVec[newp],heapVec[(newp-1)/m2]))
	{
		std::swap(heapVec[newp], heapVec[(newp-1)/m2]);
		newp = (newp -1)/m2;
	}
	return;

}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("EMPTY HEAP");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
	return heapVec[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("EMPTY HEAP");

  }
	std::swap(heapVec[0], heapVec[heapVec.size()-1]);
	heapVec.pop_back();

	size_t i = 0;
  while(true)
	{
    size_t max= i;    
    T& newp= heapVec[i];
    for(int j = 1; j <= m2; j++)
		{
      if(m2*(i) + j < heapVec.size())
			{
        if(cp(heapVec[m2*(i) + j], heapVec[max]))
        {
          max= m2*(i) + j;
        }        
      }
      else break;
    }
    if(max == i || cp(newp, heapVec[max]))
    {
      break;
    }
    std::swap(newp, heapVec[max]);
    i= max; 
  }
}


//empty--------------------------
template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const{
  return heapVec.empty();
}

//size---------------------------
template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const{
  return heapVec.size();
}


#endif
