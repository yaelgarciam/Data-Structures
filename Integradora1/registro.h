/*

Yael García Morelos 
A01352461
Equipo 16
Act integradora 1 
24 de marzo del 2025

*/

#ifndef REGISTRO_H
#define REGISTRO_H

#include <fstream>
#include <iostream>
#include <sstream>

#include <vector>
#include <string>
#include <unordered_map>


struct registro{
    std::string mes;
    int dia;
    std::string hora;
    std::string ip;
    std::string msj;
};
std::ostream& operator<<(std::ostream& os, const registro& r);

class bitacora {
    private:
        long q = 0; 
        long w = 0; 


    public:

        int comparaciones();

        registro procesarDatos(const std::string &linea);
        void mergeFechas (std::vector<registro> &registros, int inicio, int fin);
        void mezcla (std::vector<registro> &registros, int inicio, int centro, int fin);
        int numMes (std::string mes);
        bool comparar (const registro &r1, const registro &r2);
        
        int busqBin (std::vector<registro> &registros, int min, int max, std::string dato);
        std::string nuevoFormato(const registro dato);
        bool compBin(const registro &reg, const std::string &dato);
        int casosExito();

        int diasMes(std::string mes);
        std::vector<int> difDias (std::vector<registro>& registros, int D);
};

#endif