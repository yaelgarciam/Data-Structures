/*

Yael García Morelos 
A01352461
Equipo 16
Act Integradora 3 - Estructuras de datos jerárquicas
13 de mayo del 2025

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
///       g++ -Wall -std=c++17 main.cpp -o main.exe    ///
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



#include "heap.h"
#include "registro.h"

int main (){
    std::vector<Registro> registro;  
    std::string linea;
   
    std::ifstream file;
    file.open("bitacoraHeap.txt", std::ios::in);

    if (!file.is_open()) {
        std::cout << "No se pudo abrir el archivo";
        return 1;
    }

    while(std::getline(file, linea)){
        registro.push_back(Registro::procesarDatos(linea));
        }
    file.close();
    linea = "";
   
    Heap<Registro> Heap(registro);
    Heap.heapSort();

    std::ofstream outFile("bitacora_ordenada.txt");
    if (outFile.is_open()) {
        for (const auto& heap : Heap.getData()) {
            outFile << heap.getMes() << " " << heap.getDia() << " " << heap.getHora() << " " << heap.getIp() << " " << heap.getMsj() << std::endl;
        }
        outFile.close();
    } else {
        std::cerr << "No se pudo crear el archivo de salida" << std::endl;
        return 1;
    }
    std::unordered_map<std::string, int> ipCount = Heap.countIP(Heap.getData());

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Las 10 IPs con mayor acceso son: " << std::endl;
    Heap.printIPMax(ipCount);
    std::cout << "----------------------------------------" << std::endl << std::endl;
    
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "La IP con menor acceso que sea mayor o igual a 3: " << std::endl;
    Heap.findIPMin(ipCount);
    std::cout << "----------------------------------------" << std::endl;

   return 0;
}

/*

REFERENCIAS:

https://www.geeksforgeeks.org/heap-sort/
https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
https://chatgpt.com/share/682555e4-689c-800f-9bae-24149f689991

*/