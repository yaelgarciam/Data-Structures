/*

Yael García Morelos 
A01352461
Equipo 16
Act Integradora 4 - Grafos, algoitmos.
28 de mayo del 2025

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



#include "Graph.h"


int main() {
    std::ifstream archivo("bitacoraGrafos.txt"); 
    if (!archivo.is_open()) {
        std::cerr << "Error: no se pudo abrir el archivo 'bitacoraGrafos.txt'" << std::endl;
        return 1;
    }

    std::stringstream input;
    input << archivo.rdbuf(); 

    Graph<Registro> grafo;
    grafo.readGraph(input, 1, 1); 

    archivo.close(); 
    grafo.gradosDeSalida("grados_ips.txt"); 
    grafo.maxHeapGradoSalida(); 
    grafo.fechaBotMaster();
    grafo.pathBotMaster(); 
}


/*
Referencias.

https://replit.com/@ertello/maxHeap?error=overlimit#MaxHeap.h
https://replit.com/@ertello/Grafos-Dijkstra?error=overlimit#Graph.h
https://replit.com/@ertello/Grafos-BFS?error=overlimit#Graph.h

https://chatgpt.com/share/68377246-1828-800c-8afb-229513e8705d
https://chatgpt.com/share/683776f3-8414-800f-a696-ee47a2da3f5b

*/