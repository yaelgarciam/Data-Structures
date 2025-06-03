/*

Yael García Morelos 
A01352461
Equipo 16
Act integradora 1 
24 de marzo del 2025

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
///      g++ main.cpp registro.cpp -o main.exe         ///
///               main.exe < test0X.txt                ///
///                                                    ///
///     Nota: en el segundo comando, la X se debe de   ///
/// cambiar dependiendo de la prueba a realizar, en la ///
///    carpeta podemos encontrar 4 casos de prueba     ///
///                                                    ///
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


#include "registro.h"



int main (){
    bitacora Bitacora;
    std::vector<registro> registros;
    std::string linea, fecha; 
    int n, dias;
    std::vector<int>resultado;
    

    std::ifstream file;
    file.open("bitacoraData.txt", std::ios::in);

    if (!file.is_open()) {
        std::cout << "No se pudo abrir el archivo";
        return 1;
    }

    while(std::getline(file, linea)){
        registros.push_back(Bitacora.procesarDatos(linea));
    }
    file.close();
    linea = "";

    Bitacora.mergeFechas(registros, 0, registros.size() - 1);

    
    std::ofstream outFile("bitacora_ordenada.txt");
    if (!outFile.is_open()) {
        std::cout << "No se pudo crear el archivo de salida." << std::endl;
        return 1;
    }

    for (const auto &registro : registros) {
        outFile << registro.mes << " " << registro.dia << " " << registro.hora
                << " " << registro.ip << registro.msj << std::endl;
    }

    std::ifstream file2;
    file2.open("bitacora_ordenada.txt", std::ios::in);

    if (!file2.is_open()) {
        std::cout << "No se pudo abrir el archivo";
        return 1;
    }

    std::ofstream out("resultados_busqueda.txt");
    if (!outFile.is_open()) {
        std::cout << "No se pudo crear el archivo de salida." << std::endl;
        return 1;
    }


    std::cin >> n; std::cin.ignore();
    std::vector <int> avg (n);

    for (int i = 0; i < n; i++){
        std::getline(std::cin, fecha);
        avg[i] = Bitacora.busqBin(registros, 0, registros.size() - 1, fecha);
    
        if (avg[i] != -1) {
            out << "[" << avg[i] << "] " << registros[avg[i]] << std::endl;
        } else {
            out  << "Fecha no encontrada: " << fecha << std::endl;
        }
    }
    
    std::cin >> dias;

    resultado = Bitacora.difDias(registros, dias);
    out << "Busqueda del primer par de registros con " << dias << " dias de diferencia: " << std::endl;
    if (resultado[0] == -1) {
        out << "No existe dicho par de registros." << std::endl;
    } else {
        out << "[" << resultado[0] << "] " << registros[resultado[0]] << std::endl;
        out << "[" << resultado[1] << "] " << registros[resultado[1]] << std::endl;
        }
    outFile.close();

    int inicio = avg[0];



    ////////////////////////////////////////////////////////
    
    std::cout << "Ordenamiento MergeSort." << std::endl;
    std::cout << "Comparaciones: "<< Bitacora.comparaciones() << std::endl << std::endl;
    std::cout << "Numero total de operaciones de busqueda por fecha solicitadas: " << n << std::endl;
    std::cout << "Numero total de busquedas exitosas: " << Bitacora.casosExito() << std::endl;
    std::cout << "Numero total de busquedas no exitosas: " << n - Bitacora.casosExito() << std::endl << std::endl;
    std::cout << "Busqueda del primer par de registros con " << dias << " dias de diferencia: " << std::endl;
    if (resultado[0] == -1) {
        std::cout << "No existe dicho par de registros." << std::endl;
    } else {
        std::cout << "[" << resultado[0] << "] " << registros[resultado[0]] << std::endl;
        std::cout << "[" << resultado[1] << "] " << registros[resultado[1]] << std::endl;
        }

    /////////////////////////////////////////////////////////
    

}