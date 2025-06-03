#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include "LinkedList.h"
#include "Registro.h"
#include "maxHeap.h"

#define INF 0x3f3f3f3f

template <class T>
class Graph {
private:
    int numNodes;
    int numEdges;
    int directedGraph;
    int weightedGraph;
    std::string ipBotMaster;
    int maxDist = -1;
    std::map<int, T> nodesInfo;
    std::vector<LinkedList<std::pair<int, int>>> adjList;
    std::map<std::string, int> ipToIndex;
    std::map<int, std::string> indexToIp;
    std::map<std::pair<int, int>, std::vector<Registro>> registrosPorConexion;



    void split(const std::string& line, std::vector<int>& res);

public:
    Graph();
    ~Graph();
    void readGraph(std::istream& input, int _directed, int _weighted);
    void print(int flagInfo = 0);
    std::pair<std::vector<int>, std::vector<int>> shortestPath(int v);
    int getNumNodes() const { return numNodes; }
    std::map<int, T> getNodesInfo() const { return nodesInfo; }
    std::map<std::string, int> getIpToIndex() const { return ipToIndex; }
    std::map<int, std::string> getIndexToIp() const { return indexToIp; }
    const std::vector<LinkedList<std::pair<int, int>>>& getAdjList() const { return adjList; }
    std::vector<Registro> getRegistrosConexion(const std::string& ipOrigen, const std::string& ipDestino) const {
    auto itU = ipToIndex.find(ipOrigen);
    auto itV = ipToIndex.find(ipDestino);
    if (itU != ipToIndex.end() && itV != ipToIndex.end()) {
        return getRegistrosConexion(itU->second, itV->second);
    } else {
        return {};
    }
}
    void printRegistrosEntreNodos(int nodeU, int nodeV) {
    std::pair<int, int> key = {nodeU, nodeV};

    // Verificamos si hay registros para esa conexión
    if (registrosPorConexion.find(key) != registrosPorConexion.end()) {
        const std::vector<Registro>& registros = registrosPorConexion[key];
        std::cout << "Conexiones entre nodo " << nodeU << " y nodo " << nodeV << ":\n";

        for (Registro reg : registros) {
            reg.print();  // Imprime cada registro
            std::cout << "---------------------------\n";
        }
    } else {
        std::cout << "No se encontraron registros entre nodo " << nodeU << " y nodo " << nodeV << ".\n";
    }
}
    void gradosDeSalida(const std::string& filename);
    void maxHeapGradoSalida();
    void fechaBotMaster();
    void pathBotMaster();
};
template <class T>
Graph<T>::Graph() : numNodes(0), numEdges(0), directedGraph(1), weightedGraph(1) {}

template <class T>
Graph<T>::~Graph() {
    adjList.clear();
    nodesInfo.clear();
    ipToIndex.clear();
    indexToIp.clear();
}

template <class T>
void Graph<T>::split(const std::string& line, std::vector<int>& res) {
    size_t strPos = line.find(" ");
    size_t lastPos = 0;
    while (strPos != std::string::npos) {
        res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
        lastPos = strPos + 1;
        strPos = line.find(" ", lastPos);
    }
    res.push_back(stoi(line.substr(lastPos)));
}

template <class T>
void Graph<T>::readGraph(std::istream& input, int _directed, int _weighted) {
    directedGraph = _directed;
    weightedGraph = _weighted;

    std::string line;
    int i = 1;

    while (std::getline(input, line)) {
        if (i == 1) {
            std::vector<int> res;
            split(line, res);
            numNodes = res[0];
            numEdges = res[1];
            adjList.resize(numNodes);
            i++;
            continue;
        }

        if (i > 1 && i < numNodes + 2) {
            std::string ip = line;
            ipToIndex[ip] = i - 2;
            indexToIp[i - 2] = ip;

            Registro data;
            data.setIpOrigen(ip);
            nodesInfo[i - 2] = data;

            i++;
            continue;
        }

        Registro registro = Registro::procesarDatos(line);
        std::string ipOrigen = registro.getIpOrigen();
        std::string ipDestino = registro.getIpDestino();

        // Eliminar puertos
        ipOrigen = ipOrigen.substr(0, ipOrigen.find(":"));
        ipDestino = ipDestino.substr(0, ipDestino.find(":"));

        if (ipToIndex.count(ipOrigen) == 0 || ipToIndex.count(ipDestino) == 0) {
            std::cerr << "IP no encontrada: " << ipOrigen << " o " << ipDestino << std::endl;
            continue;
        }

        int nodeU = ipToIndex[ipOrigen];
        int nodeV = ipToIndex[ipDestino];
        int peso = (weightedGraph == 1) ? registro.getPeso() : 1;

        adjList[nodeU].addLast(std::make_pair(nodeV, peso));

        // Guardar registro
        registrosPorConexion[{nodeU, nodeV}].push_back(registro);

        if (directedGraph == 0) {
            adjList[nodeV].addLast(std::make_pair(nodeU, peso));
            registrosPorConexion[{nodeV, nodeU}].push_back(registro);
        }

        i++;
    }
}

template <class T>
void Graph<T>::print(int flagInfo) {
    std::cout << "numNodes: " << numNodes << "\nnumEdges: " << numEdges << "\nAdjacency List\n";
    for (int nodeU = 0; nodeU < numNodes; ++nodeU) {
        std::cout << "vertex ";
        if (flagInfo) std::cout << nodesInfo[nodeU].getIpOrigen();
        else std::cout << nodeU + 1;
        std::cout << ": ";

        NodeLinkedList<std::pair<int, int>>* ptr = adjList[nodeU].getHead();
        while (ptr != nullptr) {
            int nodeV = ptr->data.first;
            int weight = ptr->data.second;
            if (weightedGraph == 1)
                std::cout << "{" << (flagInfo ? nodesInfo[nodeV].getIpOrigen() : std::to_string(nodeV + 1)) << ", " << weight << "} ";
            else
                std::cout << "{" << (flagInfo ? nodesInfo[nodeV].getIpOrigen() : std::to_string(nodeV + 1)) << "} ";
            ptr = ptr->next;
        }
        std::cout << '\n';
    }
}

template <class T>
std::pair<std::vector<int>, std::vector<int>> Graph<T>::shortestPath(int v) {
    std::vector<int> dist(numNodes, INF);
    std::vector<int> prev(numNodes, -1);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

    pq.emplace(0, v);
    dist[v] = 0;

    while (!pq.empty()) {
        int nodeU = pq.top().second;
        pq.pop();

        NodeLinkedList<std::pair<int, int>>* ptr = adjList[nodeU].getHead();
        while (ptr != nullptr) {
            int nodeV = ptr->data.first;
            int weight = ptr->data.second;

            if (dist[nodeV] > dist[nodeU] + weight) {
                dist[nodeV] = dist[nodeU] + weight;
                prev[nodeV] = nodeU;
                pq.emplace(dist[nodeV], nodeV);
            }

            ptr = ptr->next;
        }
    }

    return {dist, prev};
}

template <class T>
void Graph<T>::gradosDeSalida(const std::string& filename) {
    std::ofstream archivo(filename);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo para escritura: " << filename << std::endl;
        return;
    }

    // Recorremos todos los nodos
    for (int i = 0; i < numNodes; i++) {
        int gradoSalida = 0;

        // Contamos los nodos adyacentes (grado de salida)
        NodeLinkedList<std::pair<int, int>>* ptr = adjList[i].getHead();
        while (ptr != nullptr) {
            gradoSalida++;
            ptr = ptr->next;
        }

        // Escribimos la IP y el grado de salida
        archivo << "(" << indexToIp[i] << ", " << gradoSalida << ")\n";
    }

    archivo.close();
}

template <class T> void Graph<T>::maxHeapGradoSalida() {
    std::vector<std::pair<int, std::string>> gradoIps;

    for (int i = 0; i < numNodes; ++i) {
        int gradoSalida = 0;
        NodeLinkedList<std::pair<int, int>>* ptr = adjList[i].getHead();
        while (ptr != nullptr) {
            gradoSalida++;
            ptr = ptr->next;
        }

        gradoIps.push_back({gradoSalida, indexToIp[i]});
    }

    MaxHeap<std::pair<int, std::string>> heap(gradoIps);
    std::ofstream outFile("mayores_grados_ips.txt");

    if (outFile.is_open()) {
        int k = 0;
        while (k < 5 && !heap.empty()) {
            auto [grado, ip] = heap.top();
            outFile << "(" << ip << ", " << grado << ")\n";  
            heap.pop();
            if (k == 0){
                std::cout << "Posible IP del BotMaster: " << ip << std::endl;
                ipBotMaster = ip; 
            }
            k++;
        }
        outFile.close();  // Cerramos el archivo
            
    } else {
        std::cerr << "No se pudo abrir el archivo para escribir.\n";
    }
}

template <class T> void Graph<T>::fechaBotMaster() {
    if (ipBotMaster.empty()) {
        std::cerr << "BotMaster no ha sido identificado aún.";
        return;
    }

    int indexBM = ipToIndex[ipBotMaster];
    Registro* earliest = nullptr;

    for (const auto& entry : registrosPorConexion) {
        int from = entry.first.first;
        if (from == indexBM) {
            for (const Registro& reg : entry.second) {
                if (earliest == nullptr || reg < *earliest) {
                    earliest = new Registro(reg);
                }
            }
        }
    }

    if (earliest != nullptr) {
        std::cout << "Primera conexion del posible BotMaster: ";
        earliest->getFecha();
        delete earliest;
    } else {
        std::cout << "No se encontraron conexiones iniciadas por el BotMaster. ";
    }
}

template <class T> 
void Graph<T>::pathBotMaster() {
    std::ofstream archivo("distancia_botmaster.txt");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir archivo para escritura.\n";
        return;
    }

    if (ipToIndex.find(ipBotMaster) == ipToIndex.end()) {
        std::cerr << "IP BotMaster no está en el grafo.\n";
        return;
    }

    int indiceBotMaster = ipToIndex[ipBotMaster];
    auto resultado = shortestPath(indiceBotMaster);
    std::vector<int> distancias = resultado.first;
    std::vector<int> predecesores = resultado.second;

    int indiceMaxDist = -1;
    this->maxDist = -1;

    for (size_t i = 0; i < distancias.size(); ++i) {
        archivo << "(" << indexToIp[i] << ", ";
        if (distancias[i] >= INF)
            archivo << "INF";
        else {
            archivo << distancias[i];
            if (distancias[i] > this->maxDist) {
                this->maxDist = distancias[i];
                indiceMaxDist = i;
            }
        }
        archivo << ")\n";
    }
    archivo.close();

    std::cout << "\nIP que requiere un mayor esfuerzo desde el BotMaster: ";
    if (indiceMaxDist != -1) {
        std::cout << indexToIp[indiceMaxDist] << " con distancia " << this->maxDist << "\n";

        // Reconstrucción del camino
        std::vector<std::string> camino;
        for (int at = indiceMaxDist; at != -1; at = predecesores[at]) {
            camino.push_back(indexToIp[at]);
        }
        std::reverse(camino.begin(), camino.end());

        // Guardar en archivo
        std::ofstream ataqueFile("ataque_botmaster.txt");
        if (!ataqueFile.is_open()) {
            std::cerr << "Error al abrir archivo ataque_botmaster.txt.\n";
            return;
        }

        for (const auto& ip : camino) {
            ataqueFile << ip << "\n";
        }
        ataqueFile.close();
    }
}


#endif 
