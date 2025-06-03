
#ifndef _REGISTRO_H_
#define _REGISTRO_H_

#include <iostream>
#include <string>

#include <fstream>
#include <string>
#include <sstream>

class Registro {
  private:
    std::string mes;
    int dia;
    std::string hora;
    std::string ipOrigen;
    std::string ipDestino;
    int peso;
    std::string msj;
   
  public:
    Registro() = default;
    Registro(std::string mes, int dia, std::string hora, std::string ipOrigen, std::string ipDestino, int peso, std::string msj)
      : mes(mes), dia(dia), hora(hora), ipOrigen(ipOrigen), ipDestino(ipDestino), peso(peso), msj(msj) {}
       
    std::string getMes() const { return mes; }
    int getDia() const {  return dia;  }
    std::string getHora() const {   return hora;  }
    std::string getIpOrigen() const {  return ipOrigen;  }
    std::string getIpDestino() const {  return ipDestino;  }
    int getPeso() const {  return peso;  }
    std::string getMsj() const {  return msj; }
    void getFecha() const {
       std::cout << mes << " " << dia << " " << hora;
    }
     
    void setMes(const std::string& m) { mes = m; }
    void setDia(int d) { dia = d; }
    void setHora(const std::string& h) { hora = h; }
    void setIpOrigen(const std::string& ip) { ipOrigen = ip; }
    void setIpDestino(const std::string& ip) { ipDestino = ip; }
    void setPeso(int p) { peso = p; }
    void setMsj(const std::string& m) { msj = m; }

    static Registro procesarDatos(const std::string& linea){
      std::istringstream stream(linea);
      Registro registro;
      std::string mes, hora, ipOrigen, ipDestino, msj;
      int dia, peso;
      stream >> mes >> dia >> hora >> ipOrigen >> ipDestino >> peso;

      std::getline(stream, msj);
      registro.setMes(mes);
      registro.setDia(dia);
      registro.setHora(hora);
      registro.setIpOrigen(ipOrigen);
      registro.setIpDestino(ipDestino);
      registro.setPeso(peso);
      registro.setMsj(msj);
      return registro;
  }
    void print() {
        std::cout << mes << " "
              << dia << " "
              << hora << " "
              << ipOrigen << " "
              << ipDestino << " "
              << peso << " "
              << msj << std::endl;
  }
    bool operator<(const Registro& otro) const {
      static const std::map<std::string, int> mesANum = {
          {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4},
          {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8},
          {"Sep", 9}, {"Oct",10}, {"Nov",11}, {"Dec",12}
      };

      if (mesANum.at(mes) != mesANum.at(otro.mes))
          return mesANum.at(mes) < mesANum.at(otro.mes);

      if (dia != otro.dia)
          return dia < otro.dia;

      int h1, m1, s1;
      int h2, m2, s2;
      sscanf(hora.c_str(), "%d:%d:%d", &h1, &m1, &s1);
      sscanf(otro.hora.c_str(), "%d:%d:%d", &h2, &m2, &s2);

      if (h1 != h2) return h1 < h2;
      if (m1 != m2) return m1 < m2;
      return s1 < s2;
  }
    

};
#endif