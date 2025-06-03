/*

Yael García Morelos 
A01352461
Equipo 16
Act Integradora 2 - Estructura de Datos Lineales
07 de abril del 2025

*/


//////////////////////////////////////////////////////////
///////////////////INSTRUCCIONES//////////////////////////
//////////////////////////////////////////////////////////
///                                                    ///
/// Este código esta diseñado para ingresar los datos  ///
///   desde el CMD, para asegurar un funcionamiento    /// 
///   eficaz, se recomienda utilizar los siguientes    ///
///     comandos siguiendo el orden proporcionado:     ///
///                                                    ///
///          g++ -Wall main.cpp -o main.exe            ///
///                    main.exe                        ///
///                                                    ///
///  Nota: para cumplir con el objetivo y procurar  un ///
///  buen funcionamiento, varias de las funciones y/o  ///
///   métodos se crearon con base en otros algoritmos. ///
///  Todo se encuentra citado y referenciado, además,  ///
///     cabe resaltar que no se copiaron textual,      ///
/// unicamente fueron utilizadas para identificar una  ///
///   estructura, resolver dudas y/o tener una mejor   ///
///            comprensión de la situación.            /// 
///                                                    ///
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////



#include "myDLinkedList.h"
#include "registro.h"

int main (){
    DLinkedList<Registro> registros;
    std::string linea;
    std::string f1, f2;
    DLinkedList<Registro> resultado;    

    std::ifstream file;
    file.open("bitacoraData.txt", std::ios::in);

    if (!file.is_open()) {
        std::cout << "No se pudo abrir el archivo";
        return 1;
    }

    while(std::getline(file, linea)){
        registros.insert(registros.procesarDatos(linea));
        }
    file.close();
    linea = "";

    registros.mergeSort(); 

    registros.listaDocB("bitacora_ordenada.txt");

    
    std::cout << "Ingrese la fecha de inicio (formato: Jan 01 00:00:00): ";
    std::getline(std::cin, f1);
    std::cout << "Ingrese la fecha de fin (formato: Jan 01 23:59:59): ";
    std::getline(std::cin, f2);
    
    Registro fechaInicio = registros.procesarDatos(f1);
    int indiceInicio = registros.busqIndice(fechaInicio, 0, registros.getSize() - 1);

    Registro fechaFin = registros.procesarDatos(f2);
    int indiceFin = registros.busqIndice(fechaFin, 0, registros.getSize() - 1);

    DLinkedList<Registro> registrosBuscados = registros.busqLista(indiceInicio, indiceFin);    
    registrosBuscados.listaDocF("resultado_busqueda.txt");

    registros.~DLinkedList();
    registrosBuscados.~DLinkedList();
    return 0;
}