/*

Yael García Morelos 
A01352461
Equipo 16
Act Integradora 2 - Estructura de Datos Lineales
07 de abril del 2025

*/

#ifndef _DLINKEDLIST_H
#define _DLINKEDLIST_H

#include "myDNode.h"
#include "registro.h"


#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>

template <class T>class DLinkedList {
  private:
    myDNode<T> *head;
    myDNode<T> *tail;
    int n;

  public:
    DLinkedList(); //O(1)
    ~DLinkedList();//O(n)

    
    void insert (T value);//O(1)
    int getSize();//O(1)
    void printList();//O(n)
    myDNode<T>* getNodeAt(int indice);//O(n)
    myDNode<T>* getHead();//O(1)

    void mergeSort(); //O(n log n)
    void sort(int inicio, int fin); //O(log n)
    void merge(int inicio, int fin); //O(n)
    bool comparar(const Registro &r1, const Registro &r2); //O(1)
    int numMes(std::string mes); //O(1)

    DLinkedList<T> busqLista(int indiceInicio, int indiceFin); //O(n)
    int busqIndice(const Registro& fecha, int inicio, int fin); //O(log n)


    void listaDocB(std::string nombreArchivo);//O(n)
    void listaDocF(std::string nombreArchivo);//O(n)
    Registro procesarDatos(const std::string &linea);//O(1)
};


template <class T>DLinkedList<T>::DLinkedList() {
  head = nullptr;
  tail = nullptr;
  n = 0;
}
template <class T>DLinkedList<T>::~DLinkedList() {
  myDNode<T> *p, *q;
  p = head;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  head = nullptr;
  tail = nullptr;
  n = 0;
}

//(Rodriguez, 2025)
template <class T>int DLinkedList<T>::getSize(){
    return n;
}
template <class T> void DLinkedList<T>::printList(){
    if (getSize() == 0) throw std::out_of_range("Lista vacia");

    myDNode<T> *p = head;
    while(p != nullptr) {
      std::cout << p->data << " ";
      p = p->next;
    }
}
template<class T> void DLinkedList<T>::insert(T value){
    myDNode<T>* newNode = new myDNode<T>(value);
    
    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    n++;
}
template<class T> myDNode<T>* DLinkedList<T>::getNodeAt(int indice) {
    if (indice < 0 || indice >= n) throw std::out_of_range("Fuera de rango");

    myDNode<T>* current = head;
    for (int i = 0; i < indice; i++) {
        current = current->next;
    }
    return current;
}
template<class T>myDNode<T>* DLinkedList<T>::getHead(){
    return head;
}

//(GeeksforGeeks, 2023) 
//(De La Cueva et al., 2020)
template <class T> void DLinkedList<T>::mergeSort(){
    if (getSize() == 0) throw std::out_of_range("Lista vacia");

    sort(0, getSize()-1); 
}
template <class T> void DLinkedList<T>::merge(int inicio, int fin) {
    int centro = (inicio + fin) / 2;
    DLinkedList<Registro> temp;
    myDNode<Registro>* left = getNodeAt(inicio);
    myDNode<Registro>* right = getNodeAt(centro + 1);
    int i = inicio, j = centro + 1;

    while (i <= centro && j <= fin) {
        if (!comparar(left->data, right->data)) {
            temp.insert(left->data);
            left = left->next;
            i++;
        } else {
            temp.insert(right->data);
            right = right->next;
            j++;
        }
    }

    while (i <= centro) {
        temp.insert(left->data);
        left = left->next;
        i++;
    }

    while (j <= fin) {
        temp.insert(right->data);
        right = right->next;
        j++;
    }

    myDNode<Registro>* current = getNodeAt(inicio);
    myDNode<Registro>* tempNode = temp.getHead();

    for (int i = 0; i <= (fin - inicio); i++) {
        current->data = tempNode->data;
        current = current->next;
        tempNode = tempNode->next;
    }
}
template <class T> void DLinkedList<T>::sort(int inicio, int fin){
  if (inicio >= fin) return;

  int centro = (inicio + fin) / 2;
   sort(inicio, centro);
   sort(centro + 1, fin);

   merge(inicio, fin);
}

template<class T> bool DLinkedList<T>::comparar(const Registro &r1, const Registro &r2){
   int mes1 = numMes(r1.getMes());
   int mes2 = numMes(r2.getMes());

   if (mes1 != mes2) {
       return mes1 < mes2;  
   }
   
   if (r1.getDia() != r2.getDia()) {
       return r1.getDia() < r2.getDia();  
   }
   return r1.getHora() < r2.getHora();
   
}
template<class T> int DLinkedList<T>::numMes(std::string mes){
   static std::unordered_map<std::string, int> meses = {
       {"Jan", 1}, {"Feb", 2}, {"Mar", 3},
       {"Apr", 4}, {"May", 5}, {"Jun", 6},
       {"Jul", 7}, {"Aug", 8}, {"Sep", 9},
       {"Oct", 10}, {"Nov", 11}, {"Dec", 12}
   };
   
   auto it = meses.find(mes);
   if (it != meses.end()) {
       return it->second;
   }
   return -1; 
}

//(Rodriguez, 2025)
//(De La Cueva et al., 2020)
template<class T> int DLinkedList<T>::busqIndice(const Registro& fecha, int inicio, int fin) {
    int resultado = -1;

    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;
        Registro current = getNodeAt(medio)->data;

        if (!comparar(current, fecha) && !comparar(fecha, current)) {
           
            resultado = medio;
            fin = medio - 1; 
        }
        else if (comparar(current, fecha)) {
            
            fin = medio - 1;
        } else {
            inicio = medio + 1;
        }
    }

    return resultado;
}
template<class T> DLinkedList<T> DLinkedList<T>::busqLista(int indiceInicio, int indiceFin){

    DLinkedList<T> resultado;

    if (indiceInicio == -1 || indiceFin == -1) {
        return resultado;
    }

    myDNode<T>* current = getNodeAt(indiceFin);

    for (int i = indiceFin; i <= indiceInicio; i++) {
        resultado.insert(current->data);
        current = current->next;
    }

    return resultado;
}

//(De La Cueva et al., 2020)
template<class T> void DLinkedList<T>::listaDocB(std::string nombreArchivo) {
    if (getSize() == 0) throw std::out_of_range("Lista vacia");

   std::ofstream outFile(nombreArchivo);

   if (!outFile.is_open()) {
       std::cout << "No se pudo crear el archivo de salida." << std::endl;
   } else {
       myDNode<Registro> *current = head;  

       while (current != nullptr) {
           outFile << current->data.getMes() << " " 
                   << current->data.getDia() << " " 
                   << current->data.getHora() << " " 
                   << current->data.getIp() << " " 
                   << current->data.getMsj() << std::endl;
           current = current->next;  
       }
       outFile.close();
   }
}
template<class T> void DLinkedList<T>::listaDocF(std::string nombreArchivo){

    std::ofstream outFile(nombreArchivo);
 
    if (!outFile.is_open()) {
        std::cout << "No se pudo crear el archivo de salida." << std::endl;
    } else {
        if (getSize() == 0) {
            outFile << "Resultado: 0 registros";
            return;
        }
        outFile << "Resultado: " << getSize() << std::endl;
        myDNode<Registro> *current = head;  
 
        while (current != nullptr) {
            outFile << current->data.getMes() << " " 
                    << current->data.getDia() << " " 
                    << current->data.getHora() << " " 
                    << current->data.getIp() << " " 
                    << current->data.getMsj() << std::endl;
            current = current->next;  
        }
        outFile.close();
    }
}
template<class T> Registro DLinkedList<T>::procesarDatos(const std::string &linea){
  std::istringstream stream(linea);
  Registro registro;
  std::string mes, hora, ip, msj;
  int dia;
  stream >> mes >> dia >> hora;
  if (!(stream >> ip)) ip = "";
  getline(stream, msj);
  registro.setMes(mes);
  registro.setDia(dia);
  registro.setHora(hora);
  registro.setIp(ip);
  registro.setMsj(msj);
  return registro;
}


#endif

/*
Referencias.

https://www.geeksforgeeks.org/merge-sort-for-linked-list/

De La Cueva, V. M., González, L. H., & Salinas, E. G. (2020). 
Estructura de datos y algoritmos fundamentales. (1.a ed.) [eBook]. Editorial Digital Tecnológico de Monterrey. 

Rodriguez, E. [ertello]. (2025). Double linked list. 
Replit. https://replit.com/@ertello/Double-Linked-List?error=overlimit#main.cpp
 
*/