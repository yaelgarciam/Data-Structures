/*

Yael García Morelos 
A01352461
Equipo 16
Act Integradora 3 - Estructuras de datos jerárquicas
13 de mayo del 2025

*/

#ifndef _HEAP_H_
#define _HEAP_H_

#include <iostream>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <queue>

template <class T>
class Heap {
  private:
    std::vector<T> data;

    int maxCapacity;

    int currentSize;

    int parent(int k);
    int left(int k);
    int right(int k);

  public:
    Heap();
    Heap (std::vector<T> data);
    ~Heap();
    std::vector<T> getData() { return data; }

    bool empty();
    int getCurrentSize();
    std::string getIP(const std::string IP);
    void heapify(int n, int i);
    void heapSort();
    std::unordered_map<std::string, int> countIP(std::vector<T> data);
    void printIPMax(std::unordered_map<std::string, int> ipCount);
    void findIPMin (std::unordered_map<std::string, int> ipCount);
};

//O(1)
template <class T> Heap<T>::Heap() {
  data.clear();
  maxCapacity = 0;
  currentSize = 0;
}
//O(n)
template <class T>Heap<T>::Heap(std::vector<T> data) {
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
            if (rightChild < currentSize && getIP(this->data[rightChild].getIp()) < getIP(this->data[leftChild].getIp())) {
                largestChild = rightChild;
            }
            if (getIP(this->data[k].getIp()) >= getIP(this->data[largestChild].getIp())) break;
            
            std::swap(this->data[k], this->data[largestChild]);
            k = largestChild;
        }
    }
}
//O(1)
template <class T>Heap<T>::~Heap() {
  data.clear();
  maxCapacity = 0;
  currentSize = 0;
}
//O(1)
template <class T>int Heap<T>::parent(int k) {
  return (k - 1) / 2;
}
//O(1)
template <class T>int Heap<T>::left(int k) {
  return (2 * k + 1);
}
//O(1)
template <class T>int Heap<T>::right(int k) {
  return (2 * k + 2);
}
//O(1)
template <class T> int Heap<T>::getCurrentSize() { 
  return currentSize; 
}
//O(n) donde n es la longitud de la IP con puerto 
template <class T> std::string Heap<T>::getIP(const std::string IP){
  size_t pos = IP.find(':');
  return IP.substr(0, pos);
}
//O(log n*m) donde n es el tamaño del heap y m es la longitud de la IP
template <class T>void Heap<T>::heapify(int n, int i){
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  std::string ipLargest = getIP(data[largest].getIp());

  if (left < n && getIP(data[left].getIp()) > ipLargest) {
    largest = left;
    ipLargest = getIP(data[largest].getIp());
  }
  if (right < n && getIP(data[right].getIp()) > ipLargest) { 
    largest = right;
  }

  if (largest != i) {
    std::swap(data[i], data[largest]);
    heapify(n, largest);
  }
}
//O(n log n) donde n es el tamaño del heap
template <class T>void Heap<T>::heapSort(){
  int n = getCurrentSize();

  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(n, i);
  }

  for (int i = n - 1; i > 0; i--) {
    std::swap(data[0], data[i]);
    heapify(i, 0);
  }
}
// O(n*m) donde n es el tamaño del heap y m es la longitud de la IP, esto por llamar la función getIP
template <class T>std::unordered_map<std::string, int> Heap<T>::countIP(std::vector<T> reg) {
  std::unordered_map<std::string, int> ipCount;
        
  for (const auto& dat : reg) {
    std::string ip = getIP(dat.getIp());
    ipCount[ip]++;
  }
        
  return ipCount;
  
    
}
//O(n log n) donde n es el tamaño del heap
template <class T>void Heap<T>::printIPMax(std::unordered_map<std::string, int> ipCount) {
    std::priority_queue<std::pair<int, std::string>> maxHeap;

    for (const auto& [ip, count] : ipCount) {
        maxHeap.push({count, ip});
    }

    std::ofstream outFile("ips_con_mayor_acceso.txt");
    if (!outFile.is_open()) {
        std::cerr << "No se pudo crear el archivo ips_con_mayor_acceso.txt" << std::endl;
        return;
    }

    for (int i = 0; i < 10 && !maxHeap.empty(); ++i) {
        auto [count, ip] = maxHeap.top();
        std::cout << "IP: " << ip << " - Accesos: " << count << std::endl;
        outFile << "IP: " << ip << " - Accesos: " << count << std::endl;
        maxHeap.pop();
    }

    outFile.close();
}
// O(n log n) donde n es el tamaño del heap
template <class T>void Heap<T>::findIPMin (std::unordered_map<std::string, int> ipCount) {
    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<std::pair<int, std::string>>> minHeap;

    for (const auto& [ip, count] : ipCount) {
        minHeap.push({count, ip});
    }
        auto [count, ip] = minHeap.top();
        std::cout << "IP: " << ip << " - Accesos: " << count << std::endl;
        minHeap.pop();
    
}

#endif 


