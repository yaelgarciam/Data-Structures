/*

Yael García Morelos 
A01352461
Equipo 16
Act Integradora 2 - Estructura de Datos Lineales
07 de abril del 2025

*/

#ifndef REGISTRO_H
#define REGISTRO_H

#include <iostream>
#include <string>

class Registro {
   private:
       std::string mes;
       int dia;
       std::string hora;
       std::string ip;
       std::string msj;
   
   public:
       Registro() = default;
       Registro(std::string mes, int dia, std::string hora, std::string ip, std::string msj)
           : mes(mes), dia(dia), hora(hora), ip(ip), msj(msj) {}
       
       std::string getMes() const { return mes; }
       int getDia() const {  return dia;  }
       std::string getHora() const {   return hora;  }
       std::string getIp() const {  return ip;  }
       std::string getMsj() const {  return msj; }
     
       void setMes(const std::string& m) { mes = m; }
       void setDia(int d) { dia = d; }
       void setHora(const std::string& h) { hora = h; }
       void setIp(const std::string& i) { ip = i; }
       void setMsj(const std::string& m) { msj = m; }

     
   };
#endif