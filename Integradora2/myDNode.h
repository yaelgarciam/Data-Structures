/*

Yael García Morelos 
A01352461
Equipo 16
Act Integradora 2 - Estructura de Datos Lineales
07 de abril del 2025

*/

#ifndef _MYDNODE_H_
#define _MYDNODE_H_

template <class T>
class myDNode {
  private:
    T data;
    myDNode<T> *next;
    myDNode<T> *prev;

  public:
    myDNode();
    myDNode(T value);
    
    template<typename U> friend class DLinkedList;

};

template <class T>
myDNode<T>::myDNode() : data{}, next{nullptr}, prev{nullptr} {}

template <class T>
myDNode<T>::myDNode(T value) : data{value}, next{nullptr}, prev{nullptr} {}


#endif  
