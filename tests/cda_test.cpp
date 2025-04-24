#include "../datastructs.hpp"

int main() {
    CircularDynamicArray<int> cda(25);

    for (int i = 0; i < 25; i++) {
        cda[i] = i*10;
    }

    // cda = {10, 20, 30, ... , 240}
    
    cda.delFront();

    // cda = {20, 30, ... , 240}

    cda.delEnd();

    // cda = {20, 30, ... , 230}

    cda.addEnd(1001);

    // cda = {20, 30, ... , 230, 1001}

    cda.addEnd(1005);

    // cda = {20, 30, ... , 230, 1001, 1005}
    // 1005 should be at index 0 but have start = 1

    if (cda[24] != 1005) {
        return 1;
    }

    cda.clear();

    for (int i = 0; i < 25; i++) {
        cda.addEnd(i*10);

        if (i == 0 && cda.capacity() != 2) {
            return 1;
        }
        if (i == 4 && cda.capacity() != 8) {
            return 1;
        }
        if (i == 8 && cda.capacity() != 16) {
            return 1;
        }
        if (i == 16 && cda.capacity() != 32) {
            return 1;
        }
    }

    if (cda.linearSearch(60) != 6) {
        return 1;
    }
    if (cda.linearSearch(9) != -1) {
        return 1;
    }

    if (cda.QuickSelect(2) != 10) {
        return 1;
    }
    if (cda.QuickSelect(15) != 140) {
        return 1;
    }

    if (cda.WCSelect(2) != 10) {
        return 1;
    }
    if (cda.WCSelect(15) != 140) {
        return 1;
    }

    if (cda.binSearch(60) != 6) {
        return 1;
    }
    if (cda.binSearch(9) != -1) {
        return 1;
    }

    cda.clear();

    for (int i = 0; i < 25; i++) {
        cda.addFront(i*5);
    }

    if (cda[0] != 120) {
        return 1;
    }
    if (cda[15] != 45) {
        return 1;
    }

    cda.stableSort();

    if (cda[0] != 0) {
        return 1;
    }
    if (cda[15] != 75) {
        return 1;
    }

    // test deep copy assignment
    CircularDynamicArray<int> cda2 = cda;

    // cda2 should be a deep copy of cda
    for (int i = 0; i < cda.length(); i++) {
        if (cda[i] != cda2[i]) {
            return 1;
        }
    }

    // cda and cda2 should NOT be linked
    cda2.delEnd();
    cda2.addEnd(1005);
    if (cda[24] == cda2[24]) {
        return 1;
    }

    return 0;
}