#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <cmath>

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

  size_t height(int size) const;

private:
  /// Add whatever helper functions and data members you need below
  void heapify(size_t idx);
  void heapify_helper(size_t idx, int leaf);
  void trickle_up(size_t loc);
  std::vector<T> heap_;
  size_t size_;
  int m_;
  PComparator comp_;
  


};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
: m_(m), size_(0), comp_ (c)
{}
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{
  heap_.clear();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  heap_.push_back(item);
  ++size_;
  //trickle up
  trickle_up(size_ -1);
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::trickle_up(size_t loc)
{
  size_t parent = loc/m_;
  while(parent >= 0 && comp(heap_[loc], heap_[parent]))
  {
    std::swap(heap_[loc], heap_[parent]);
    loc = parent;
    parent= loc/m_;
  } 
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return heap_.empty();
}


template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return heap_.size();
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
    throw std::underflow_error("The stack is empty.");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heap_.front();


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
    throw std::underflow_error("The stack is empty.");

  }
  //switch the item
  heap_[0]=heap_[size_-1];
  heap_.pop_back();
  --size_;
  //heapify
  heapify(0);
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(size_t index)
{
  //find the start index of the leaf node -assuming that the size_ > 1
  int i = 0, leaf_start = 0 , leaf_end=0;
  if(height(size_) == 1) {leaf_end == 0; leaf_start = 0;}
  else
  {
    while (i < height(size_)) //when height >1
    {
      
      leaf_start += pow(m_, i);
      ++i; 
      leaf_end += (leaf_start + pow(m_, i) -1);
      
    }
  }
  heapify_helper(index, leaf_start);

 
}
template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify_helper(size_t index, int l_s)
{
  //recursion helper function starts here
  if(index > l_s ) {return;} //base case: if the index is a leaf node 
  int best_ch = index * m_ +1;//start from the most left child
  
  for(int i = 0 ; i < m_-1 ; ++i) //iterate through the possible m-th child
  {
    if(best_ch <= size_-1) //if there's right node exist
    {
      int rChild = best_ch +1;
      if(comp_(heap_[rChild], heap_[best_ch])  ){best_ch = rChild;}
    }
    ++best_ch;
  }

  //we found the best child now and so we need compare the parent and the child and swap 
  if(comp(heap_[best_ch], heap_[index]))
  {
    std::swap(heap_[best_ch], heap_[index]);
  }
  heapify_helper(best_ch,l_s );
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::height(int size) const
{
  int i = 1;
  int h = 1;
  while(size > i)
  {
    ++h;
    i*=m_;
  }
  if(size == 1) return 1;
  if (size == 0) return 0;
  return h;
}

#endif

