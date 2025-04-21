#include "../algorithms.hpp"

#include <iostream>

int main () {
    APSP *apsp = new APSP(5);

    /*
        0->1 = 1
        0->2 = 2
        0->3 = 8
        0->4 = DNE
    */
    apsp->addEdge(0, 1, 1);
    apsp->addEdge(0, 2, 2);
    apsp->addEdge(0, 3, 8);

    /*
        1->0 = DNE
        1->2 = 3
        1->3 = DNE
        1->4 = 4
    */
    apsp->addEdge(1, 2, 3);
    apsp->addEdge(1, 4, 4);

    /*
        2->0 = DNE
        2->1 = 3
        2->3 = DNE
        2->4 = 5
    */
    apsp->addEdge(2, 1, 3);
    apsp->addEdge(2, 4, 5);

    /*
        3->0 = DNE
        3->1 = DNE
        3->2 = DNE
        3->4 = 6
    */
    apsp->addEdge(3, 4, 6);

    /*
        4->0 = DNE
        4->1 = DNE
        4->2 = DNE
        4->3 = 6
    */
    apsp->addEdge(4, 3, 6);

    // 0->1 = 1
    if (apsp->getCost(0, 1) != 1) {
        return 1;
    }

    // No path exists to 0, only from 0
    if (apsp->getCost(4, 0) != INT_MAX) {
        return 1;
    }

    // 0->1 = 1, 1->4 = 4, 1 + 4 = 5
    if (apsp->getCost(0, 4) != 5) {
        return 1;
    }

    // 1->4 = 4, 4->3 = 6, 4 + 6 = 10
    if (apsp->getCost(1, 3) != 10) {
        return 1;
    }
    
    return 0;
}