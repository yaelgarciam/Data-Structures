#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

struct IPSummary {
    std::string ip;
    int salientes;
    int entrantes;

    IPSummary() : salientes(0), entrantes(0) {}

    double relacion() const {
        return (entrantes == 0) ? salientes : (double)salientes / entrantes;
    }
    //O(n)
    void print() const {
        std::cout << "IP: " << ip << "\n"
                  << "Total de direcciones accesadas desde la IP: " << salientes << "\n"
                  << "Total de direcciones que intentaron acceder a la IP: " << entrantes << "\n"
                  << "Relacion entre el numero de direcciones accesadas y que intentaron acceder a la IP: "<< std::setprecision(2) << relacion() << "\n"
                  ;

    }
};

class Graph {
private:
    std::unordered_map<std::string, std::vector<std::string>> adyacencias;
    std::unordered_map<std::string, int> entradas;
    std::unordered_set<std::string> nodosUnicos;

public:
    //O(n)
    void readGraph(std::istream& in) {
        int n, m;
        in >> n >> m;
        in.ignore(); 

        std::vector<std::string> ipList;
        for (int i = 0; i < n; ++i) {
            std::string ip;
            std::getline(in, ip);
            ipList.push_back(ip);
            nodosUnicos.insert(ip);
        }

        for (int i = 0; i < m; ++i) {
            std::string line;
            std::getline(in, line);
            std::istringstream iss(line);
            std::string mes, dia, hora, ipOrig, ipDest;
            int peso;
            std::string resto;

            iss >> mes >> dia >> hora >> ipOrig >> ipDest >> peso;
            std::getline(iss, resto); 

            ipOrig = ipOrig.substr(0, ipOrig.find(':'));
            ipDest = ipDest.substr(0, ipDest.find(':'));

            adyacencias[ipOrig].push_back(ipDest);
            entradas[ipDest]++;
            nodosUnicos.insert(ipOrig);
            nodosUnicos.insert(ipDest);
        }
    }
    //O(1)
    const std::unordered_map<std::string, std::vector<std::string>>& getAdyacencias() const {
        return adyacencias;
    }
    //O(1)
    const std::unordered_map<std::string, int>& getEntradas() const {
        return entradas;
    }
    //O(1)
    bool existeIP(const std::string& ip) const {
        return nodosUnicos.count(ip);
    }
    //O(1)
    size_t sizeHash() const {
        return nodosUnicos.size() * 2;
    }
    // O(1)
    unsigned long ipToLong(const std::string& ip) {
    std::istringstream iss(ip);
    std::string octeto;
    unsigned long result = 0;

    while (std::getline(iss, octeto, '.')) {
        result = (result << 8) + std::stoul(octeto);
    }
    return result;
}
    // O(n log n)
    void ipDirecciones(const std::string& IP) {
        auto& accesadas = adyacencias.at(IP); 

        std::sort(accesadas.begin(), accesadas.end(), [this](const std::string& a, const std::string& b) {
            return ipToLong(a) > ipToLong(b);
        });

        for (const auto& ip : accesadas) {
            std::cout << ip << std::endl;
        }
    }
};

#endif
