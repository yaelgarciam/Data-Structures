#ifndef OPENHASH_H
#define OPENHASH_H


#include <stdexcept>
#include <functional>
#include "graph.h"

class OpenHash {
private:
    struct Entry {
        std::string key;
        IPSummary value;
        bool ocupado = false;
    };

    std::vector<Entry> table;
    int size;
    int colisiones;
    //O(1)
    int hashFunction(const std::string& ip) const {
        std::hash<std::string> h;
        return h(ip) % size;
    }

public:
    OpenHash(int tableSize) : size(tableSize), colisiones(0) {
        table.resize(size);
    }
    //O(1) peor de los casos O(n)
    void add(const std::string& key, const IPSummary& value) {
        int idx = hashFunction(key);
        int i = 0;

        while (table[idx].ocupado && table[idx].key != key) {
            colisiones++;
            idx = (idx + i * i) % size;
            i++;
        }

        table[idx].key = key;
        table[idx].value = value;
        table[idx].ocupado = true;
    }
    //O(1) peor de los casos O(n)
    const IPSummary& find(const std::string& key) const {
        int idx = hashFunction(key);
        int i = 0;

        while (table[idx].ocupado && table[idx].key != key) {
            idx = (idx + i * i) % size;
            i++;
        }

        if (table[idx].ocupado && table[idx].key == key)
            return table[idx].value;
        else
            throw std::runtime_error("IP no encontrada");
    }
    //O(n) peor de los casos O(n^2)
    void hashGraph(const Graph& grafo) {
        for (const auto& [ip, destinos] : grafo.getAdyacencias()) {
            IPSummary s;
            s.ip = ip;
            s.salientes = destinos.size();
            s.entrantes = grafo.getEntradas().count(ip) ? grafo.getEntradas().at(ip) : 0;
            add(ip, s);
        }

        for (const auto& [ip, entrantes] : grafo.getEntradas()) {
            try {
                find(ip);
            } catch (...) {
                IPSummary s;
                s.ip = ip;
                s.entrantes = entrantes;
                s.salientes = 0;
                add(ip, s);
            }
        }
    }
    //O(1)
    void getIPSummary(const std::string& ip) const {
        try {
            const IPSummary& resumen = find(ip);
            resumen.print();
        } catch (...) {
            std::cout << "IP no encontrada en la tabla hash.\n";
        }
    }
    //O(1)
    int getColisiones() const {
        return colisiones;
    }
};

#endif
