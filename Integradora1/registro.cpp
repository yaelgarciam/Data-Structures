/*

Yael García Morelos 
A01352461
Equipo 16
Act integradora 1 
24 de marzo del 2025

*/

#include "registro.h"

int bitacora::comparaciones(){
    return w;
}

registro bitacora::procesarDatos(const std::string &linea){
    std::istringstream stream(linea);
    registro registro;
    stream >> registro.mes >> registro.dia >> registro.hora >> registro.ip;
    getline(stream, registro.msj);
    return registro;
}

void bitacora::mergeFechas(std::vector<registro> &registros, int inicio, int fin){
    if (inicio >= fin) return;
    
    int centro = (inicio + fin) / 2;
    
    mergeFechas(registros, inicio, centro);
    mergeFechas(registros, centro + 1, fin);
    mezcla (registros, inicio, centro, fin);
}

void bitacora::mezcla(std::vector<registro> &registros, int inicio, int centro, int fin){
    std::vector<registro> temp(fin - inicio + 1);
    
    int i = inicio, j = centro + 1, k = 0;
    
    while (i <= centro && j <= fin) {
        if (comparar(registros[i], registros[j])) {
            temp[k++] = registros[i++];
        } else {
            temp[k++] = registros[j++];
        }
    }
    
    while (i <= centro) {
        temp[k++] = registros[i++];
    }
    while (j <= fin) {
        temp[k++] = registros[j++];
    }
    
    for (int i = 0; i < temp.size(); i++) {
        registros[inicio + i] = temp[i];
    }
}

int bitacora::numMes(std::string mes)
{
    static std::unordered_map<std::string, int> meses = {
        {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4},
        {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8},
        {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}
    };

    auto it = meses.find(mes);
    if (it != meses.end()) {
        return it->second;
    }

    return 0; 
}

bool bitacora::comparar(const registro &r1, const registro &r2){
    int mes1 = numMes(r1.mes);
    int mes2 = numMes(r2.mes);

    if (mes1 != mes2) {
        w++;
        return mes1 < mes2;  
    }
    
    if (r1.dia != r2.dia) {
        w++;
        return r1.dia < r2.dia;  
    }
    w++;
    return r1.hora < r2.hora;
    
}

int bitacora::busqBin(std::vector<registro> &registros, int min, int max, std::string dato){
    int avg;
    while (min <= max) {
        avg = (min + max) / 2;
        std::string regFormat = nuevoFormato(registros[avg]);

        if (dato == regFormat){
            q++;
            return avg;
        } else if (compBin(registros[avg], dato)){
            max = avg - 1;
        } else {
            min = avg + 1;
        }
    }
    return -1;
}

std::string bitacora::nuevoFormato(const registro dato){
    return dato.mes + " " + (dato.dia < 10 ? "0" : "") + std::to_string(dato.dia) + " " + dato.hora;
}

bool bitacora::compBin(const registro &reg, const std::string &dato)
{
    std::string mesStr;
    int dia;
    std::string hora;
    
    std::istringstream ss(dato);
      
    ss >> mesStr >> dia >> hora;
        
    int mes1 = numMes(reg.mes);
    int mes2 = numMes(mesStr);
    
    if (mes1 != mes2) return mes1 > mes2;

    if (reg.dia != dia) return reg.dia > dia;
        
    return reg.hora > hora;
}

int bitacora::casosExito(){
    return q;
}

int bitacora::diasMes(std::string mes) {
    static std::unordered_map<int, int> diasPorMes = {
        {1, 31}, {2, 28}, {3, 31}, {4, 30},
        {5, 31}, {6, 30}, {7, 31}, {8, 31},
        {9, 30}, {10, 31}, {11, 30}, {12, 31}
    };

    int numMes = this->numMes(mes);
    if (diasPorMes.find(numMes) != diasPorMes.end()) {
        return diasPorMes[numMes];
    }
    return 0;
}

std::vector<int> bitacora::difDias(std::vector<registro>& registros, int D) {
    int i = 0, j = 1;
    std::vector<int> resultado;

    while (j < registros.size()) {
        int dias1 = 0;
        int dias2 = 0;

        for (int m = 1; m < numMes(registros[i].mes); m++) {
            dias1 += diasMes(registros[i].mes);  
        }
        dias1 += registros[i].dia;  

        for (int m = 1; m < numMes(registros[j].mes); m++) {
            dias2 += diasMes(registros[j].mes);  
        }
        dias2 += registros[j].dia;  

        int diferenciaDias = dias2 - dias1;  

        if (diferenciaDias == D && registros[i].hora == registros[j].hora) {
            resultado.push_back(i);  
            resultado.push_back(j);  
            return resultado;        
        } 
        else if (diferenciaDias < D) {  
            j++;
        } else {  
            i++;
        }
    }

    resultado.push_back(-1);  
    return resultado;
}

std::ostream &operator<<(std::ostream &os, const registro &r){
    os << r.mes << " " << r.dia << " " << r.hora << " " << r.ip << " " << r.msj;
    return os;
}
