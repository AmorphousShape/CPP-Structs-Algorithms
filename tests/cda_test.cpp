#include "../datastructs.hpp"

#include <cassert>

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

    assert(cda[24] == 1005);

    cda.clear();

    for (int i = 0; i < 25; i++) {
        cda.addEnd(i*10);

        switch (i) {
            case 0:
                assert(cda.capacity() == 2);
                break;
            case 4:
                assert(cda.capacity() == 8);
                break;
            case 8:
                assert(cda.capacity() == 16);
                break;
            case 16:
                assert(cda.capacity() == 32);
                break;
        }
    }

    assert(cda.linearSearch(60) == 6);
    assert(cda.linearSearch(9) == -1);

    assert(cda.QuickSelect(2) == 10);
    assert(cda.QuickSelect(15) == 140);

    assert(cda.WCSelect(2) == 10);
    assert(cda.WCSelect(15) == 140);

    assert(cda.binSearch(60) == 6);
    assert(cda.binSearch(9) == -1);

    cda.clear();

    for (int i = 0; i < 25; i++) {
        cda.addFront(i*5);
    }

    assert(cda[0] == 120);
    assert(cda[15] == 45);

    cda.stableSort();

    assert(cda[0] == 0);
    assert(cda[15] == 75);

    // test deep copy assignment
    CircularDynamicArray<int> cda2 = cda;

    // cda2 should be a deep copy of cda
    for (int i = 0; i < cda.length(); i++) {
        assert(cda[i] == cda2[i]);
    }

    // cda and cda2 should NOT be linked
    cda2.delEnd();
    cda2.addEnd(1005);
    assert(cda[24] != cda2[24]);

    return 0;
}