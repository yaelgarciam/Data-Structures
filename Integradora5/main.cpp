/*

Yael García Morelos 
A01352461
Equipo 16
Act Integradora 5 - Uso de Tablas Hash.
06 de junio del 2025

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
///     > g++ -Wall -std=c++17 main.cpp -o main.exe    ///
///                  > main.exe                        ///
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


#include <iostream>
#include <fstream>
#include "graph.h"
#include "openHash.h"

int main() {
    Graph grafo;
    std::ifstream file("bitacoraGrafos.txt");
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo.\n";
        return 1;
    }

    grafo.readGraph(file);
    file.close();

    OpenHash tablaHash(grafo.sizeHash());
    tablaHash.hashGraph(grafo);

    std::cout << "Colisiones generadas: " << tablaHash.getColisiones() << "\n";

    std::string ipBuscada;
    std::cout << "Ingrese la IP para consultar: ";
    std::cin >> ipBuscada;
    std::cout << "----------------------\n" << std::endl;


    if (grafo.existeIP(ipBuscada)) {
        tablaHash.getIPSummary(ipBuscada);
    } else {
        std::cout << "La IP ingresada no existe en la bitácora.\n";
    }
    
    return 0;
}

/*
Referencias:

https://github.com/MikeMirzayanov/open_addressing_hash_table
https://www.geeksforgeeks.org/implementing-hash-table-open-addressing-linear-probing-cpp/
https://chatgpt.com/share/6843a6ca-befc-800c-be82-9522916ab4ba

*/