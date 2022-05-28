#include <iostream>
#include <vector>
#include <unordered_map>

class Graph {
    public:
        Graph() {};
        ~Graph() {};

        void addVertex(int vertex) {
            adjacentList.insert(std::make_pair(vertex, std::vector<int>()));
            numberOfNodes++;
        };

        void addConnection(int node1, int node2)
        {
            try {
                std::vector<int>& connections1 = adjacentList.at(node1);
                connections1.push_back(node2);
            }
            catch (std::out_of_range e) {
                std::cout << "Ops, something wrong" << std::endl;
            }
        }

        void addEdge(int node1, int node2) {
            addConnection(node1, node2);
            addConnection(node2, node1);
        };

        void printConnections() const {
            for (auto it = adjacentList.cbegin(); it != adjacentList.cend(); it++) {
                std::cout << it->first << " --> ";

                for (int c : it->second)
                {
                    std::cout << c << ' ';
                }

                std::cout << std::endl;
            }
        }

    private:
        int numberOfNodes = 0;
        std::unordered_map<int, std::vector<int>> adjacentList;
};

int main() {
    Graph g;
    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);
    g.addVertex(6);
    g.addEdge(3, 1);
    g.addEdge(3, 4);
    g.addEdge(4, 2);
    g.addEdge(4, 5);
    g.addEdge(1, 2);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(6, 5);

    g.printConnections();

    return 0;
}
