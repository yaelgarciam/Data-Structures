
#ifndef _MAXHEAP_H_
#define _MAXHEAP_H_

#include <iostream>

#include <stdexcept>
#include <vector>
#include <utility>


template <class T>
class MaxHeap {
  private:
    std::vector<T> data;

    int maxCapacity;

    int currentSize;

    int parent(int k);
    int left(int k);
    int right(int k);

  public:
    MaxHeap();
    MaxHeap(int _maxCapacity);
    MaxHeap (std::vector<T> data);
    MaxHeap (MaxHeap heap1, MaxHeap heap2);

    ~MaxHeap();
    int getMaxCapacity();
    void print();
    void push(T value);
    
    void pop();
    T top();
    bool empty();
    int getCurrentSize();

};

//O(1)
template <class T> MaxHeap<T>::MaxHeap() {
  data.clear();
  maxCapacity = 0;
  currentSize = 0;
}
//O(1)
template <class T> MaxHeap<T>::MaxHeap(int _maxCapacity) {
  data.resize(_maxCapacity);
  maxCapacity = _maxCapacity;
  currentSize = 0;
}
//O(n)
template <class T> MaxHeap<T>::MaxHeap(std::vector<T> data) {
   if (data.empty()) {
      throw std::out_of_range("Vector vacío");
   }
   maxCapacity = data.size();
   currentSize = data.size();
   this->data = data;

   for (int i = parent(currentSize - 1); i >= 0; i--) {
      int k = i;
    while (true) {
      int leftChild = left(k);
      int rightChild = right(k);
      if (leftChild >= currentSize) break; 
      int largestChild = leftChild;
      if (rightChild < currentSize && this->data[rightChild] > this->data[leftChild]) {
        largestChild = rightChild;
      }
      if (this->data[k] >= this->data[largestChild]) break;
      std::swap(this->data[k], this->data[largestChild]);
      k = largestChild;
    }
   }
}
//O(n)
template <class T> MaxHeap<T>::MaxHeap(MaxHeap heap1, MaxHeap heap2) {
   if (heap1.empty() && heap2.empty()) {
      throw std::out_of_range("Heaps vacios");
   }
   maxCapacity = heap1.getMaxCapacity() + heap2.getMaxCapacity();
   currentSize = heap1.getCurrentSize() + heap2.getCurrentSize();
   data.resize(maxCapacity);
   int i = 0;
   for (int j = 0; j < heap1.getCurrentSize(); j++) {
      data[i] = heap1.data[j];
      i++;
   }
   for (int j = 0; j < heap2.getCurrentSize(); j++) {
      data[i] = heap2.data[j];
      i++;
   }
   for (int i = parent(currentSize - 1); i >= 0; i--) {
      int k = i;
    while (true) {
      int leftChild = left(k);
      int rightChild = right(k);
      if (leftChild >= currentSize) break; 
      int largestChild = leftChild;
      if (rightChild < currentSize && this->data[rightChild] > this->data[leftChild]) {
        largestChild = rightChild;
      }
      if (this->data[k] >= this->data[largestChild]) break;
      std::swap(this->data[k], this->data[largestChild]);
      k = largestChild;
    }
   }
}
//O(1)
template <class T>MaxHeap<T>::~MaxHeap() {
  data.clear();
  maxCapacity = 0;
  currentSize = 0;
}
//O(1)
template <class T>int MaxHeap<T>::parent(int k) {
  return (k - 1) / 2;
}
//O(1)
template <class T>int MaxHeap<T>::left(int k) {
  return (2 * k + 1);
}
//O(1)
template <class T>int MaxHeap<T>::right(int k) {
  return (2 * k + 2);
}
// O(1)
template <class T> int MaxHeap<T>::getMaxCapacity() { 
  return maxCapacity; 
}
// O(n)
template <class T> void MaxHeap<T>::print() {
  std::cout << "Contenido del maxheap:" << std::endl;
  for (int i = 0; i < currentSize; i++) {
    std::cout << data[i] << ", ";
  }
  std::cout << std::endl;
}
// O(log n)
template <class T> void MaxHeap<T>::push(T key) {
  if (currentSize == maxCapacity) {
    throw std::out_of_range("Overflow: no es posible insertar la llave");
  }
  int k = currentSize;
  data[k] = key;
  currentSize++;
  while(k != 0 && data[parent(k)] < data[k]) {
    std::swap(data[k], data[parent(k)]);
    k = parent(k);
  }
}
// O(log n)
template <class T> void MaxHeap<T>::pop(){
   if (currentSize == 0) {
      throw std::out_of_range("Heap vacio");
    }
    data[0] = data[currentSize - 1];
    currentSize--;
    int k = 0;
    while (true) {
      int leftChild = left(k);
      int rightChild = right(k);
      if (leftChild >= currentSize) break; 
      int largestChild = leftChild;
      if (rightChild < currentSize && data[rightChild] > data[leftChild]) {
        largestChild = rightChild;
      }
      if (data[k] >= data[largestChild]) break;
      std::swap(data[k], data[largestChild]);
      k = largestChild;
    }
}
// O(1)
template <class T> T MaxHeap<T>::top(){
   if (currentSize == 0) {
      throw std::out_of_range("Heap vacio");
    }
    return data[0];
}
//O(1)
template <class T> int MaxHeap<T>::getCurrentSize() { 
  return currentSize; 
}
// O(1)
template <class T> bool MaxHeap<T>::empty() { 
  return currentSize == 0; 
}


#endif 