/**
 * @file datastructs.h
 * 
 * @brief Includes some less common data structures
 * 
 * @details This file includes the following data structures:
 * * - Circular Dynamic Array
 * * - Heap
 * * - Red-Black Tree
 */

#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include <iostream>

using namespace std;

/**
 * @brief Implements a circular dynamic array that can dynamically resize itself
 * 
 * @tparam elmtype The type of element stored in the circular dynamic array
 */
template <typename elmtype> class CircularDynamicArray {

   public:
    /**
     * @brief Default Constructor
     * 
     * @details Initializes the circular dynamic array with a capacity of 2. End is set to -1 for addEnd() and addFront() functionality.
     */
    CircularDynamicArray() {
        cap = 2;
        size = 0;
        start = 0;
        end = -1;
        info = new elmtype[2];
    }

    /**
     * @brief Constructor for a set capacity
     * 
     * @details Initializes the circular dynamic array with a set capacity. End is set to capacity - 1 for addEnd() and addFront() functionality.
     * 
     * @param capacity The capacity of the circular dynamic array
     */
    CircularDynamicArray(int capacity) {
        cap = capacity;
        size = capacity;
        start = 0;
        end = capacity - 1;
        info = new elmtype[capacity];
    };

    /**
     * @brief Copy constructor (deep copy)
     * 
     * @details Deep copies all values from the source circular dynamic array
     * 
     * @param src The source circular dynamic array to copy
     */
    CircularDynamicArray(CircularDynamicArray const &src) {
        cap = src.cap;
        size = src.size;
        start = src.start;
        end = src.end;
        elmtype *tempInfo = new elmtype[cap];
        for (int i = 0; i < size; i++) {
            tempInfo[i] = src.info[i];
        }
        info = tempInfo;
    }
    
    /**
     * @brief Destructor
     * 
     * @details Deletes the array data
     */
    ~CircularDynamicArray() { if (info != nullptr) {delete[] info;} };

    /**
     * @brief Returns the size of the array
     */
    int length() { return size; }

    /**
     * @brief Returns the capacity of the array
     */
    int capacity() { return cap; }
    
    /**
     * @brief Returns the value of the element at index i
     */
    elmtype atRef(int i) {
        if (i < 0 || i > cap) {
            return burner;
        }
        return info[(i + start) % cap];
    }
    
    /**
     * @brief Returns a pointer to the element at index i
     */
    elmtype *atPoint(int i) {
        if (i < 0 || i > cap) {
            return &burner;
        }
        return &info[(i + start) % cap];
    }

    /**
     * @brief Bracket operator. Returns burner element if index is invalid.
     */
    elmtype &operator[](int i) {
        if (i < 0 || i > cap) {
            return burner;
        }
        return info[(i + start) % cap];
    }

    /**
     * @brief Equals operator. Deep copies all values.
     */
    CircularDynamicArray &operator=(const CircularDynamicArray &R) {
        cap = R.cap;
        size = R.size;
        start = R.start;
        end = R.end;
        delete[] info;
        info = new elmtype[cap];
        for (int i = 0; i < size; i++) {
            info[i] = R.info[i];
        }
        return *this;
    }

    /**
     * @brief Adds an element to the front of the array
     * 
     * @details Time complexity: O(1) (Amortized)
     */
    void addFront(elmtype v) {
        checkCapIncrease();
        if (start > 0) {
            info[start - 1] = v;
        } else {
            info[cap - 1] = v;
            start = cap;
        }
        start--;
        size++;
    };

    /**
     * @brief Adds an element to the end of the array
     * 
     * @details Time complexity: O(1) (Amortized)
     */
    void addEnd(elmtype v) {
        checkCapIncrease();
        info[(end + 1) % cap] = v;
        end++;
        end %= cap;
        size++;
    }

    /**
     * @brief Removes the element at the front of the array
     * 
     * @details Time complexity: O(1) (Amortized)
     */
    void delFront() {
        start++;
        start %= cap;
        size--;
        checkCapDecrease();
    };

    /**
     * @brief Removes the element at the end of the array
     * 
     * @details Time complexity: O(1) (Amortized)
     */
    void delEnd() {
        end--;
        if (end == -1) {
            end = cap - 1;
        }
        size--;
        checkCapDecrease();
    };

    /**
     * @brief Clears all array data and resets the array to its default state
     */
    void clear() {
        size = 0;
        cap = 2;
        start = 0;
        end = 0;
        delete[] info;
        info = new elmtype[cap];
    };

    /**
     * @brief Swaps two elements
     */
    void swap(elmtype *a, elmtype *b) {
        elmtype temp = (*a);
        (*a) = (*b);
        (*b) = temp;
    }

    /**
     * @brief Returns the Kth smallest element of the array using the median as the partition element
     * 
     * @details Time complexity: O(size)
     * 
     * @param k The index of the element to find
     * 
     * @return The Kth smallest element of the array
     */
    elmtype QuickSelect(int k) {
        if (k <= 0 || k > size) {
            return burner;
        }
        return select(k, standard);
    }

    /**
     * @brief Returns the Kth smallest element of the array using the median of medians (subarray size = 5) as the partition element
     * 
     * @details Time complexity: O(size)
     * 
     * @param k The index of the element to find
     * 
     * @return The Kth smallest element of the array
     */
    elmtype WCSelect(int k) {
        if (k <= 0 || k > size) {
            return burner;
        }
        return select(k, worstCase);
    }

    /**
     * @brief Performs a mergesort on the array
     * 
     * @details Time complexity: O(size * lg(size))
     */
    void stableSort() { mergeSort(0, size - 1); };

    /**
     * @brief Performs a linear search for element e
     * 
     * @details Time complexity: O(size)
     * 
     * @param e The element to search for
     * 
     * @return The index of the element if found, -1 otherwise
     */
    int linearSearch(elmtype e) {
        for (int i = 0; i < size; i++) {
            if (atRef(i) == e) return i;
        }
        return -1;
    };

    /**
     * @brief Performs a binary search for element e
     * 
     * @details Time complexity: O(lg(size))
     * 
     * @param e The element to search for
     * 
     * @return The index of the element if found, -1 otherwise
     */
    int binSearch(elmtype e) {
        for (int m = size / 2, l = 0, r = size; l <= r; m = (r + l) / 2) {
            if (e == atRef(m)) {
                return m;
            } else if (e > atRef(m)) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return -1;
    }

   private:
    // Array Data

    /**
     * @brief The capacity of the array
     */
    int cap;

    /**
     * @brief The size of the array
     */
    int size;

    /**
     * @brief The index of the first element in the array
     */
    int start;

    /**
     * @brief The index of the last element in the array
     */
    int end;

    /**
     * @brief The array data, indexed by start and end
     */
    elmtype *info;

    /**
     * @brief Burner element for error handling
     */
    int burner;

    /**
     * @brief The type of search to perform in the select function
     * 
     * @details standard uses the median as the partition element, worstCase uses the median of medians with subarray size 5
     *          standard is faster for most cases, worstCase is faster for worst case scenarios
     */
    enum searchType { standard, worstCase };

    /**
     * @brief Used in delFront and delEnd functions to half the capacity of the array if size < cap / 4
     * 
     * @details Time complexity: O(1) (Amortized)
     */
    void checkCapDecrease() {
        if (((cap / 4) - 1) > size) {
            elmtype *newArr = new elmtype[cap / 2];
            for (int i = 0; i < size; i++) {
                newArr[i] = info[start + i];
            }
            cap /= 2;
            start = 0;
            delete[] info;
            info = newArr;

            if (size > 0) {
                end = size - 1;
            } else {
                end = 0;
            };
        }
        return;
    };

    /**
     * @brief Used in addFront and addEnd functions to double the capacity of the array if size == cap
     * 
     * @details Time complexity: O(1) (Amortized)
     */
    void checkCapIncrease() {
        if (size == cap) {
            elmtype *newArr = new elmtype[cap * 2];
            for (int i = 0; i < size; i++) {
                newArr[i] = info[(start + i) % cap];
            }
            delete[] this->info;
            info = newArr;
            cap *= 2;
            start = 0;
            end = size - 1;
        }
        return;
    };

    /**
     * @brief Used by stableSort function to merge subarrays
     * 
     * @details Time complexity: O(nlg(n))
     * 
     * @param l The left index of the subarray
     * @param m The middle index of the subarray (used to split the array)
     * @param r The right index of the subarray
     */
    void merge(int l, int m, int r) {
        int sub1 = m - l + 1, sub2 = r - m;

        elmtype *linfo = new elmtype[sub1], *rinfo = new elmtype[sub2];

        for (int i = 0; i < sub1; i++) {
            int tempIndex = (l + i + start) % cap;
            linfo[i] = info[tempIndex];
        }
        for (int j = 0; j < sub2; j++) {
            int tempIndex = (m + j + 1 + start) % cap;
            rinfo[j] = info[tempIndex];
        }

        int indexL = 0, indexR = 0, indexM = l;

        // Primary Merge Loop
        while (indexL < sub1 && indexR < sub2) {
            if (linfo[indexL] <= rinfo[indexR]) {
                info[(indexM + start) % cap] = linfo[indexL];
                indexL++;
            } else {
                info[(indexM + start) % cap] = rinfo[indexR];
                indexR++;
            }
            indexM++;
        }

        // Merge Remaining Lefts
        while (indexL < sub1) {
            info[(indexM + start) % cap] = linfo[indexL];
            indexL++;
            indexM++;
        }

        // Merge Remaining Rights
        while (indexR < sub2) {
            info[(indexM + start) % cap] = rinfo[indexR];
            indexR++;
            indexM++;
        }

        // Clean Up and Return
        delete[] linfo;
        delete[] rinfo;
        return;
    };

    /**
     * @brief Used by stableSort function to perform a mergesort on the array
     * 
     * @details Time complexity: O(nlg(n))
     * 
     * @param l The left index of the subarray
     * @param r The right index of the subarray
     */
    void mergeSort(int l, int r) {
        if (l >= r) {
            return;
        }

        int m = l + (r - l) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    };

    /**
     * @brief Used by QuickSelect and WCSelect to recursively search for the Kth smallest element
     * 
     * @details Time complexity: O(n)
     * 
     * @param k The index of the element to find
     * @param type The type of search to perform
     * 
     * @return The Kth smallest element of the array
     */
    elmtype select(int k, searchType type) {

        elmtype tempArr[size];
        for (int i = 0; i < size; i++) {
            tempArr[i] = atRef(i);
        }

        // Selects the correct function based on the type
        if (type == standard) {
            return KthSmallest(tempArr, 0, size - 1, k);
        }
        return KthSmallestWC(tempArr, 0, size - 1, k);
    }

    /**
     * @brief Recursively finds the Kth smallest element of the array
     * 
     * @details Time complexity: O(n)
     * 
     * @param arr The array to search
     * @param l The left index of the subarray
     * @param r The right index of the subarray
     * @param k The index of the element to find
     * 
     * @return The Kth smallest element of the array
     */
    elmtype KthSmallest(elmtype *arr, int l, int r, int k) {
        elmtype pivot = arr[(l + r) / 2];
        int pos = partition(arr, l, r, pivot);

        if (pos - l == k - 1) {
            return arr[pos];
        } else if (pos - l > k - 1) {
            return KthSmallest(arr, l, pos - 1, k);
        } else {
            return KthSmallest(arr, pos + 1, r, k - pos + l - 1);
        }
    }

    /**
     * @brief Gets the Kth smallest element of the subarray. Only used on WCSelect
     * 
     * @details Time complexity: O(n)
     * 
     * @param arr The array to search
     * @param l The left index of the subarray
     * @param r The right index of the subarray
     * @param k The index of the element to find
     * 
     * @return The Kth smallest element of the array
     */
    elmtype KthSmallestWC(elmtype *arr, int l, int r, int k) {
        int n = r - l + 1, i;
        elmtype median[(n + 4) / 5];
        for (i = 0; i < n / 5; i++) {
            median[i] = getMedian(arr + l + i * 5, 5);
        }
        if (n > i * 5) {
            median[i] = getMedian(arr + l + i * 5, n % 5);
            i++;
        }
        elmtype medOfMed =
            (i == 1) ? median[i - 1] : KthSmallestWC(median, 0, i - 1, i / 2);
        int pos = partition(arr, l, r, medOfMed);

        if (pos - l == k - 1) {
            return arr[pos];
        } else if (pos - l > k - 1) {
            return KthSmallestWC(arr, l, pos - 1, k);
        } else {
            return KthSmallestWC(arr, pos + 1, r, k - pos + l - 1);
        }
    }

    /**
     * @brief Gets the median of the subarray. Only used on WCSelect subarrays due to inefficiency
     * 
     * @details Time complexity: O(n^2)
     */
    elmtype getMedian(elmtype *arr, int n) {
        sort(arr, n);
        return arr[n / 2];
    }

    /**
     * @brief Partitions the subarray
     * 
     * @details Time complexity: O(r - l)
     * 
     * @param arr The array to partition
     * @param l The left index of the subarray
     * @param r The right index of the subarray
     * @param pivot The pivot element
     * 
     * @return The index of the pivot element
     */
    int partition(elmtype arr[], int l, int r, elmtype pivot) {
        int i;
        for (i = l; i < r; i++) {
            if (arr[i] == pivot) {
                break;
            }
        }
        swap(&arr[i], &arr[r]);
        i = l;
        for (int j = l; j <= r - 1; j++) {
            if (arr[j] <= pivot) {
                swap(&arr[i], &arr[j]);
                i++;
            }
        }
        swap(&arr[i], &arr[r]);
        return i;
    }

    /**
     * @brief Sorts a subarray. Only used on WCSelect subarrays due to inefficiency
     * 
     * @details Time complexity: O(n^2)
     */
    void sort(elmtype *arr, int n) {
        for (int i = 0; i < n; i++) {
            elmtype *smallest = &arr[0];
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < (*smallest)) {
                    smallest = &arr[j];
                }
            }
            if (&arr[i] != smallest) {
                swap(&arr[i], smallest);
            }
        }
    }
};

/**
 * @brief Implements a Minimum Heap
 * 
 * @tparam keyType The type of key stored in the heap
 */
template<typename keyType> class Heap {

    public:

    /**
     * @brief Default Constructor
     */
    Heap() { info = new CircularDynamicArray<keyType>; }

    /**
     * @brief Constructs a heap with keys K and size s
     */
    Heap(keyType K[], int s) {
        info = new CircularDynamicArray<keyType>(s);
        
        for (int i = 0; i < s; i++) {
            (*info)[i] = K[i];
        }

        heapify();
    }

    /**
     * @brief Destructor
     */
    ~Heap() {
        // The CDA is deleted in its cleanup, deleting here will segfault
    }

    /**
     * @brief Returns the minimum key in the heap
     * 
     * @details Time complexity: O(1)
     * 
     * @return The minimum key
     */
    keyType peekKey() {
        return (*info)[0];
    }

    /**
     * @brief Inserts a new node with key k
     * 
     * @details Time complexity: O(lg(n)), n = size
     * 
     * @param k The key to insert
     */
    void insert(keyType k) {
        info->addEnd(k);
        siftUp(info->length() - 1);
    }

    /**
     * @brief Prints all keys in the heap in level order
     */
    void printKey() {
        for (int i = 0; i < info->length(); i++) {
            cout << (*info)[i] << " ";
        }
        if (info->length() != 0) {cout << endl;}
    }

    /**
     * @brief Removes the minimum key from the heap and restores heap priority
     * 
     * @details Time complexity: O(lg(n)), n = size
     * 
     * @return The minimum key
     */
    keyType extractMin() {
        keyType min = (*info)[0];
        (*info)[0] = (*info)[info->length() - 1];
        info->delEnd();
        siftDown(0);
        return min;
    }

    private:
    
    /**
     * @brief The array that stores the heap
     */
    CircularDynamicArray<keyType> *info;

    /**
     * @brief Turns the array into a minHeap by repeatedly performing siftDown
     * 
     * @details Time complexity: O(n)
     */
    void heapify() {
        for (int i = info->length() / 2; i >= 0; i--) {
            siftDown(i);
        }
    }

    /**
     * @brief Sifts the node at index i down in the heap
     * 
     * @details Time complexity: O(lg(n))
     * 
     * @param i The index of the node to sift down
     */
    void siftDown(int i) {
        int l = lIndex(i), r = rIndex(i), min = i;

        if (l < info->length() && (*info)[l] < (*info)[i]) { min = l; }
        if (r < info->length() && (*info)[r] < (*info)[min]) { min = r; }
        if (min != i) { swap(i, min); siftDown(min); }
    }

    /**
     * @brief Sifts the node at index i up in the heap
     * 
     * @details Time complexity: O(lg(n))
     * 
     * @param i The index of the node to sift up
     */
    void siftUp(int i) {
        for (i; i != 0 && (*info)[i] < (*info)[pIndex(i)]; i = pIndex(i)) {
            swap(i, pIndex(i));
        }
    }

    /**
     * @brief Swaps two elements in the heap
     * 
     * @details Time complexity: O(1)
     * 
     * @param a The index of the first element
     * @param b The index of the second element
     */
    void swap(int a, int b) {
        keyType temp = (*info)[a];
        (*info)[a] = (*info)[b];
        (*info)[b] = temp;
    }

    /**
     * @brief Returns the index of the parent of the node at index i
     * 
     * @details Time complexity: O(1)
     * 
     * @param i The index of the node
     * 
     * @return The index of the parent
     */
    int pIndex(int i) {
        return (i-1) / 2;
    }

    /**
     * @brief Returns the index of the left child of the node at index i
     * 
     * @details Time complexity: O(1)
     * 
     * @param i The index of the node
     * 
     * @return The index of the left child
     */
    int lIndex(int i) {
        return (i*2) + 1;
    }

    /**
     * @brief Returns the index of the right child of the node at index i
     * 
     * @details Time complexity: O(1)
     * 
     * @param i The index of the node
     * 
     * @return The index of the right child
     */
    int rIndex(int i) {
        return (i*2) + 2;
    }
};

/**
 * @brief Enumerated valuetype to track if the node's color is Red or Black
 */
enum color {Red, Black};

/**
 * @brief Node for a Red-Black Tree
 * 
 * @details This class represents a node in a Red-Black Tree. It contains pointers to its left and right children, its parent, and its key and value. It also contains the color of the node (Red or Black) and the size of the subtree rooted at this node.
 * @details This class also has all of its elements set to public. This is because it is not intended to be used on its own; rather, it is for use by the RBTree class, which requires direct access to the node's elements to avoid unnecessary function calls.
 * 
 * @tparam keyType The type of key stored in the node
 * @tparam valueType The type of value stored in the node
 */
template<typename keyType, typename valueType> class RBNode {

    public:
    /**
     * @brief The key of the node
     */
    keyType *key;

    /**
     * @brief The value of the node
     */
    valueType *val;

    /**
     * @brief The left child of the node
     */
    RBNode *l;

    /**
     * @brief The right child of the node
     */
    RBNode *r;

    /**
     * @brief The parent of the node
     */
    RBNode *p;

    /**
     * @brief The color of the node
     */
    color c;

    /**
     * @brief The size of the subtree rooted at this node
     */
    int size;

    /**
     * @brief Default constructor
     * 
     * @details Initializes the node with default values. The key and value pointers are dynamically allocated. Color is set to Red.
     */
    RBNode() {
        key = new keyType;
        val = new valueType;
        l = nullptr;
        r = nullptr;
        p = nullptr;
        size = 0;
        c = Red;
    }

    /**
     * @brief Constructor for a node with specified key and value
     * 
     * @details Initializes the node with the specified key and value. The color is set to Red, size is set to 1, and relatives are set to null.
     * 
     * @param k The key of the node
     * @param v The value of the node
     */
    RBNode(keyType k, valueType v) {
        key = new keyType; *key = k;
        val = new valueType; *val = v;
        l = nullptr;
        r = nullptr;
        p = nullptr;
        size = 1;
        c = Red;
    }
    
    /**
     * @brief Constructor for a nil node
     * 
     * @details Initializes the node as a nil node. The key and value pointers are set to null, and the color is set to Black.
     * 
     * @param nilCon A boolean value to indicate that this is a nil node. The value is not used.
     */
    RBNode(bool nilCon) {
        l = nullptr;
        r = nullptr;
        p = nullptr;
        key = nullptr;
        val = nullptr;
        size = 0;
        c = Black;
    }

    /**
     * @brief Constructor for a node with specified key, value, color, size, and parent
     * 
     * @param k The key of the node
     * @param v The value of the node
     * @param setc The color of the node
     * @param s The size of the subtree rooted at this node
     * @param parent The parent of the node
     */
    RBNode (keyType k, valueType v, color setc, int s, RBNode<keyType, valueType> *parent) {
        key = new keyType(k);
        val = new valueType(v);
        l = nullptr;
        r = nullptr;
        p = parent;
        c = setc;
        size = s;
    }

    /**
     * @brief Copy constructor (deep copy)
     */
    RBNode(const RBNode<keyType, valueType> &src) {
        *key = *src.key;
        *val = *src.val;
        l = src.l;
        r = src.r;
        p = src.p;
        c = src.c;
        size = src.size;
    }
    
    /** 
     * @brief Destructor
     * 
     * @details Checks if the key and value pointers are not null before deleting them.
     */
    ~RBNode() {
        if (key != nullptr) {delete key;}
        if (val != nullptr) {delete val;}
    }

    /**
     * @brief Deletes a node and all its children
     * 
     * @details Deletes the node and all its children recursively. The nil node is passed as a parameter to avoid deleting it.
     * 
     * @param nil The nil node of the tree
     */
    void cascade(RBNode *nil) {
        if (this == nil) {return;}
        if (l != nil && l != nullptr) {
            l->cascade(nil);
        }
        if (r != nil && r != nullptr) {
            r->cascade(nil);
        }
        delete this;
    }

    /**
     * @brief Copy equals operator
     */
    RBNode &operator=(RBNode R) {
        if (this == R) {
            return *this;
        }
        delete key; key = new keyType(R.key);
        delete val; val = new valueType(R.val);
        c = R.c;
        return *this;
    }

    /**
     * @brief Prints the preorder traversal of the tree
     */
    void preorder () {
        if (key == nullptr) {
            return;
        }
        printNode();
        if (l->key != nullptr) {cout << " "; l->preorder();}
        if (r->key != nullptr) {cout << " "; r->preorder();}
    }
    
    /**
     * @brief Prints the inorder traversal of the tree
     */
    void inorder () {
        if (key == nullptr) {
            return;
        }
        if (l->key != nullptr) {l->inorder(); cout << " ";}
        printNode();
        if (r->key != nullptr) {cout << " "; r->inorder();}
    }

    /**
     * @brief Prints the postorder traversal of the tree
     */
    void postorder () {
        if (key == nullptr) {
            return;
        }
        if (l->key != nullptr) {l->postorder(); cout << " ";}
        if (r->key != nullptr) {r->postorder(); cout << " ";}
        printNode();
    }

    /**
     * @brief Prints the node's key
     */
    void printNode() {
        cout << *key;
    }

    /**
     * @brief Prints the K smallest elements of the subtree rooted at this node
     * 
     * @details Prints the K smallest elements of the subtree rooted at this node. The function is called recursively on the left and right children. Time complexity is O(k + lg(size))
     * 
     * @param k The number of elements to print
     */
    void printk(int &k) {
        if (l->key != nullptr) {
            l->printk(k);
            if (k > 0) {
                cout << " ";
            }
        }
        if (k < 1) {
            return;
        }
        cout << *key;
        k--;
        if (k < 1) {
            return;
        }
        if (r->key != nullptr) {
            cout << " ";
            r->printk(k);
        }
    }

    /**
     * @brief Searches for the node with key k and returns a pointer to the value
     * 
     * @details Performs a DFS search for the node with key k. If the key is found, it returns a pointer to the value of the node. Otherwise, it returns nullptr. Time complexity is O(lg(size))
     * 
     * @param k The key to search for
     * 
     * @return A pointer to the value of the node with key k, or nullptr if the key is not found
     */
    valueType *searchValue(keyType k) {
        if (k == *key) {
            return val;
        } else if (k < *key && l != nullptr) {
            return l->searchValue(k);
        } else if (k > *key && r != nullptr) {
            return r->searchValue(k);
        } else {
            return nullptr;
        }
    }

    /**
     * @brief Searches the subtree rooted at this node for the node with key k
     * 
     * @details Performs a DFS search for the node with key k. If the key is found, it returns a pointer to the node. Otherwise, it returns nullptr. Time complexity is O(lg(size))
     * 
     * @param k The key to search for
     * 
     * @return A pointer to the node with key k, or nullptr if the key is not found
     */
    RBNode<keyType, valueType> *searchNode(keyType k) {
        if (k == *key) {
            return this;
        } else if (k < *key && l->key != nullptr) {
            return l->searchNode(k);
        } else if (k > *key && r->key != nullptr) {
            return r->searchNode(k);
        } else {
            return nullptr;
        }
    }

    /**
     * @brief Returns the predecessor of the node
     * 
     * @details Returns the predecessor of the node. The predecessor is the largest node in the left subtree. If the left child is null, it returns nullptr. Time complexity is O(lg(size))
     * 
     * @return A pointer to the predecessor node, or nullptr if the left child is null
     */
    RBNode<keyType, valueType> *predecessor() {
        if (l == nullptr) {
            return nullptr;
        }
        RBNode *curr;
        for (curr = l; curr->l != nullptr; curr = curr->l) {continue;}
        return curr;
    }

    /**
     * @brief Returns the smallest node of the subtree rooted at this node
     * 
     * @details Returns the smallest node of the subtree rooted at this node. The smallest node is the leftmost node in the subtree. If the left child is null, it returns this node. Time complexity is O(lg(size))
     * 
     * @return A pointer to the smallest node in the subtree rooted at this node
     */
    RBNode<keyType, valueType> *min() {
        if (l == nullptr) {
            return this;
        }
        RBNode *curr;
        for (curr = l; curr->l != nullptr; curr = curr->l) {continue;}
        return curr;
    }
    
    /**
     * @brief Returns the Kth smallest element in the subtree rooted at this node
     * 
     * @details Returns the Kth smallest element in the subtree rooted at this node. The function is called recursively on the left and right children. Time complexity is O(lg(size))
     * 
     * @param k The index of the smallest element to return
     */
    keyType select(int k) {
        if (k == l->size + 1) {
            return (*key);
        } else if (k <= l->size) {
            return l->select(k);
        } else {
            return r->select(k - l->size - 1);
        }
    }
};

/**
 * @brief Implements a Red-Black Tree
 * 
 * @tparam keyType The type of key stored in the tree
 * @tparam valueType The type of value stored in the tree
 * 
 * @details This class implements a Red-Black Tree, a self-balancing binary search tree. It maintains balance using rotations and recoloring during insertions and deletions, ensuring efficient operations with a time complexity of O(log n).
 * 
 * The tree has the following properties:
 * - Each node has a color (Red or Black).
 * - The root node is always Black.
 * - Red nodes cannot have Red children (no two consecutive Red nodes).
 * - Every path from a node to its descendant nil nodes has the same number of Black nodes (Black height).
 * - The nil node (a sentinel node representing the end of the tree) is always Black.
 * 
 * These properties ensure that the tree remains approximately balanced, 
 * making it suitable for applications requiring fast lookups, insertions, and deletions.
 */
template<typename keyType, typename valueType> class RBTree {
    public:

    /**
     * @brief Default constructor
     */
    RBTree() {
        nil = new RBNode<keyType, valueType>(true);
        root = nil;
    }

    /**
     * @brief Constructs a tree with a single node with key k and value v
     * 
     * @details This constructor initializes the tree with a single node with the given key and value. The nil node is created, and the root is set to the new node. The color of the root is set to Black. Time complexity: O(1)
     * 
     * @param k The key of the root node
     * @param v The value of the root node
     */
    RBTree(keyType k, valueType v) {
        nil = new RBNode<keyType, valueType>(true);
        root = new RBNode<keyType, valueType>(k, v);
        root->c = Black; // root is black
    }

    /**
     * @brief Constructs a tree with arrays k and v as the insert values and size = s.
     * 
     * @details This constructor initializes the tree with the given arrays of keys and values. It creates a nil node and inserts each key-value pair into the tree. The root is set to nil initially. Time complexity: O(s)
     * 
     * @note If s is larger than the size of either array, this will cause a segmentation fault. Any s smaller than the size of either array will work up to the specified index, but the rest of the array will be ignored.
     * 
     * @param k The array of keys to insert
     * @param v The array of values to insert
     * @param s The size of the arrays
     */
    RBTree(keyType *k, valueType *v, int s) {
        nil = new RBNode<keyType, valueType>(true); // nil node's special constructor
        root = nil;
        for (int i = 0; i < s; i++) {
            insert(k[i], v[i]);
        }
    }

    /**
     * @brief Copy constructor (deep copy)
     * 
     */
    RBTree(const RBTree<keyType, valueType> &src) {
        nil = new RBNode<keyType, valueType>(true);
        root = nil;
        copy(src.nil, src.root, root, nil);
    }

    /**
     * @brief Destructor
     * 
     * @details This destructor deletes the tree by calling the cascade function on the root node. The cascade function recursively deletes all nodes in the tree. Time complexity: O(size)
     */
    ~RBTree() {
        root->cascade(nil);
    }
    
    /**
     * @brief Copy equals operator
     * 
     * @details This operator assigns the values of the source tree to the current tree. It first deletes the current tree and then copies the values from the source tree. Time complexity: O(n), n = R.root->size
     * 
     * @param R The source tree to copy from
     * 
     * @return A reference to the current tree
     */
    RBTree<keyType, valueType> &operator=(const RBTree<keyType, valueType> &R) {
        if (this == &R) {
            return *this;
        }

        root->cascade(nil);
        nil = new RBNode<keyType, valueType>(true);
        root = nil;
        copy(*&R.nil, *&R.root, root, nil);
        return *this;
    }

    /**
     * @brief Prints the preorder traversal of the tree.
     * 
     * @details This function prints the preorder traversal of the tree. It calls the root's preorder function, which prints the nodes in preorder. Time complexity: O(n)
     */
    void preorder () {
        root->preorder();
        cout << endl;
    }
    
    /**
     * @brief Prints the inorder traversal of the tree.
     * 
     * @details This function prints the inorder traversal of the tree. It calls the root's inorder function, which prints the nodes in inorder. Time complexity: O(n)
     */
    void inorder () {
        root->inorder();
        cout << endl;
    }

    /**
     * @brief Prints the postorder traversal of the tree.
     * 
     * @details This function prints the postorder traversal of the tree. It calls the root's postorder function, which prints the nodes in postorder. Time complexity: O(n)
     */
    void postorder () {
        root->postorder();
        cout << endl;
    }
    
    /**
     * @brief Prints the K smallest elements of the tree.
     * 
     * @details This function prints the K smallest elements of the tree. It calls the root's printk function, which prints the K smallest elements in preorder traversal. Time complexity: O(k + lg(size))
     */
    void printk (int k) {
        root->printk(k);
        cout << endl;
    }

    /**
     * @brief Returns the size of the tree.
     * 
     * @return The size of the tree
     */
    int size() {
        return root->size;
    }

    /**
     * @brief Searches the tree for key k and returns a pointer to the node's value.
     * 
     * @details This function searches the tree for key k and returns a pointer to the node's value. If the key is not found, it returns nullptr. Time complexity: O(lg(size))
     * 
     * @param k The key to search for
     * 
     * @return A pointer to the value of the node with key k, or nullptr if the key is not found
     */
    valueType *search (keyType k) {
        return root->searchValue(k);
    }

    /**
     * @brief Inserts a new node with key k and value v into the tree.
     * 
     * @details This function inserts a new node with key k and value v into the tree. It first creates a new node and sets its size to 1. Then, it traverses the tree to find the correct position for the new node. Finally, it calls the insertFixTree function to restore the Red-Black Tree properties. Time complexity: O(lg(size))
     * 
     * @param k The key of the new node
     * @param v The value of the new node
     */
    void insert(keyType k, valueType v) {
        
        RBNode<keyType, valueType> *z = new RBNode<keyType, valueType>(k, v);
        z->size = 1;
        z->l = nil; z->r = nil;
        RBNode<keyType, valueType> *y = nil;
        RBNode<keyType, valueType> *x = root;

        while (x != nil) {
            (x->size)++;
            
            y = x;

            if (*(z->key) < *(x->key)) {
                x = x->l;
            } else {
                x = x->r;
            }
        }

        z->p = y;
        if (y == nil) {
            root = z;
        } else if (*(z->key) < *(y->key)) {
            y->l = z;
        } else {
            y->r = z;
        }

        z->l = nil;
        z->r = nil;
        insertFixTree(z);  
    }
        // Removes the node with key k from the tree.
        // Time complexity: O()

    /**
     * @brief Removes the node with key k from the tree.
     * 
     * @details This function removes the node with key k from the tree. It first searches for the node with key k. If the node is found, it removes it and restores the Red-Black Tree properties. Time complexity: O(lg(size))
     * 
     * @param k The key of the node to be removed
     * 
     * @return 1 if the node was removed, 0 if the node was not found.
     */
    int remove(keyType k) {
        RBNode<keyType, valueType> *z = root->searchNode(k);
        if (z == nullptr) {
            return 0;
        }
        RBNode<keyType, valueType> *y = z;
        RBNode<keyType, valueType> *x;

        for (RBNode<keyType, valueType> *i = z->p; i != nil; i = i->p) {
            i->size--;
        }
        
        color yOrigcolor = y->c;

        if (z->l == nil) {
            x = z->r;
            transplant(z, z->r);
        } else if (z->r == nil) {
            x = z->l;
            transplant(z, z->l);
        } else {
            y = max(z->l);
            yOrigcolor = y->c;
            x = y->l;
            if (y->p == z) {
                x->p = y;
            } else {
                transplant(y, y->l);
                y->l = z->l;
                y->l->p = y;
                for (RBNode<keyType, valueType> *i = x->p; i != nil && i != y; i = i->p) {
                    i->size--;
                }
            }
            transplant(z, y);
            y->r = z->r;
            y->r->p = y;
            y->c = z->c;
            y->size = y->l->size + y->r->size + 1;
        }

        if (yOrigcolor == Black) {
            deleteFixTree(x);
        }

        return 1;
    }

    /**
     * @brief Returns the rank of the node with key k.
     * 
     * @details This function returns the rank of the node with key k. The rank is the number of nodes with keys less than k. If the key is not found, it returns 0. Time complexity: O(lg(root->size))
     */
    int rank(keyType k) {
        RBNode<keyType, valueType> *node = root->searchNode(k);
        if (node == nullptr) {
            return 0;
        }
        int rank = node->l->size + 1;
        
        for (RBNode<keyType, valueType> *curr = node; curr != root; curr = curr->p) {
            if (curr == curr->p->r) {
                rank += curr->p->l->size + 1;
            }
        }
        return rank;
    } 

    /**
     * @brief Returns the Kth smallest element in the tree.
     * 
     * @note This function currently is delegated to a function in the Node but should be migrated to the tree. This was done due to the original project specifications.
     * 
     * @details This function returns the Kth smallest element in the tree. The Kth smallest element is the node with rank k. If k is out of bounds or not found, it returns nullptr.
     * 
     * @param k The rank of the smallest element to return
     * 
     * @return A pointer to the Kth smallest element in the tree, or nullptr if k is out of bounds
     */
    keyType select(int k) {
        return root->select(k);
    }

    /**
     * @brief Finds the successor of the node with key k and returns a pointer to its key.
     * 
     * @details This function finds the successor of the node with key k. The successor is the smallest node in the right subtree. If the right child is null, it returns nullptr. Time complexity: O(lg(size))
     * 
     * @param k The key of the node whose successor is to be found
     * 
     * @return A pointer to the key of the successor node, or nullptr if there is no successor
     */
    keyType *successor(keyType k) {
        RBNode<keyType, valueType> *curr = root->searchNode(k);
        if (curr == nullptr) {
            return nullptr;
        }

        if (curr->r != nil) {
            for (curr = curr->r; curr->l != nil; curr = curr->l) {continue;}
            return curr->key;
        } else {
            RBNode<keyType, valueType> *i;
            for (i = curr->p; i != nil && curr == i->r; i = i->p) {curr = i;}
            return i->key;
        }
        
    }

    /**
     * @brief Finds the predecessor of the node with key k and returns a pointer to its key.
     * 
     * @details This function finds the predecessor of the node with key k. The predecessor is the largest node in the left subtree. If the left child is null, it returns nullptr. Time complexity: O(lg(size))
     * 
     * @param k The key of the node whose predecessor is to be found
     * 
     * @return A pointer to the key of the predecessor node, or nullptr if there is no predecessor
     */
    keyType *predecessor(keyType k) {
        RBNode<keyType, valueType> *curr = root->searchNode(k);
        if (curr == nullptr) {
            return nullptr;
        }

        if (curr->l != nil) {
            for (curr = curr->l; curr->r != nil; curr = curr->r) {continue;}
            return curr->key;
        } else {
            RBNode<keyType, valueType> *i;
            for (i = curr->p; i != nil && curr == i->l; i = i->p) {curr = i;}
            return i->key;
        }
    }
    
    private:

    /**
     * @brief The root of the Red-Black Tree
     */
    RBNode<keyType, valueType> *root;
    
    /**
     * @brief The nil node of the Red-Black Tree
     */
    RBNode<keyType, valueType> *nil;

    /**
     * @brief Deep copy support function.
     * 
     * @details This function recursively copies the nodes of the tree. It creates new nodes with the same key, value, color, and size as the copied nodes. The parent pointers are also set correctly. Time complexity: O(root->size)
     * 
     * @param copiedNil The nil node of the copied tree
     * @param copiedNode The root node to be copied
     * @param newNode A reference to the new node being created
     * @param newParent A reference to the parent of the new node
     */
    void copy(RBNode<keyType, valueType> *copiedNil, RBNode<keyType, valueType> *copiedNode, RBNode<keyType, valueType> *&newNode, RBNode<keyType, valueType> *&newParent) {
        newNode = new RBNode<keyType, valueType>(*(copiedNode->key), *(copiedNode->val), copiedNode->c, copiedNode->size, newParent);

        if (copiedNode->l == copiedNil || copiedNode->l == nullptr) {
            newNode->l = nil;
        } else {
            copy(copiedNil, copiedNode->l, newNode->l, newNode);
        }
        if (copiedNode->r == copiedNil || copiedNode->r == nullptr) {
            newNode->r = nil;
        } else {
            copy(copiedNil, copiedNode->r, newNode->r, newNode);
        }
    }

    /**
     * @brief Returns a pointer to the smallest node in the tree.
     * 
     * @details This function traverses the left child of the node until it reaches the leftmost node, which is the smallest node in the tree. Time Complexity: O(lg(node->size))
     * 
     * @note This function currently returns a pointer to the smallest node as well as editing the parameter node to become the smallest node. This should be fixed.
     * 
     * @param node The node from which to start the search
     * 
     * @return A pointer to the smallest node in the tree
     */
    RBNode<keyType, valueType> *min(RBNode<keyType, valueType> *node) {
        for (node; node->l != nil; node = node->l) {
            continue;
        }
        return node;
    }

    /**
     * @brief Returns a pointer to the largest node in the tree.
     * 
     * @details This function traverses the right child of the node until it reaches the rightmost node, which is the largest node in the tree. Time Complexity: O(lg(node->size))
     * 
     * @note This function currently returns a pointer to the largest node as well as editing the parameter node to become the largest node. This should be fixed.
     * 
     * @param node The node from which to start the search
     * 
     * @return A pointer to the largest node in the tree
     */
    RBNode<keyType, valueType> *max(RBNode<keyType, valueType> *node) {
        for (node; node->r != nil; node = node->r) {
            continue;
        }
        return node;
    }

    /**
     * @brief Fixes the tree after an insert operation has been performed.
     * 
     * @details This function restores the Red-Black Tree properties after a node has been inserted. It ensures that the tree remains balanced and that the properties of Red-Black Trees are maintained.
     * 
     * @param z The node that was just inserted
     */
    void insertFixTree(RBNode<keyType, valueType> *z) {
        RBNode<keyType, valueType> *y;

        while (z->p->c == Red) {
            if (z->p == z->p->p->l) {
                y = z->p->p->r;

                if (y->c == Red) {
                    z->p->c = Black;
                    y->c = Black;
                    z->p->p->c = Red;
                    z = z->p->p;
                } else {
                    if (z == z->p->r) {
                        z = z->p;
                        lRotate(z);
                    }

                    z->p->c = Black;
                    z->p->p->c = Red;
                    rRotate(z->p->p);
                }
            } else {
                y = z->p->p->l;

                if (y->c == Red) {
                    z->p->c = Black;
                    y->c = Black;
                    z->p->p->c = Red;
                    z = z->p->p;
                } else {
                    if (z == z->p->l) {
                        z = z->p;
                        rRotate(z);
                    }

                    z->p->c = Black;
                    z->p->p->c = Red;
                    lRotate(z->p->p);
                }
            }   
        }
        root->c = Black;
    }

    /**
     * @brief Fixes the tree after a delete operation has been performed.
     * 
     * @details This function restores the Red-Black Tree properties after a node has been deleted. It ensures that the tree remains balanced and that the properties of Red-Black Trees are maintained. Time Complexity: 
     * 
     * @param x The root of the subtree that needs to be fixed
     */
    void deleteFixTree(RBNode<keyType, valueType> *x) {

        RBNode<keyType, valueType> *w; 
        while (x != root && x->c == Black) {
            if (x == x->p->l) {
                w = x->p->r;
                if (w->c == Red) {
                    w->c = Black;
                    x->p->c = Red;
                    lRotate(x->p);
                    w = x->p->r;
                }

                if (w->l->c == Black && w->r->c == Black) {
                    w->c = Red;
                    x = x->p;
                } else {
                    if (w->r->c == Black) {
                        w->l->c = Black;
                        w->c = Red;
                        rRotate(w);
                        w = x->p->r;
                    }

                    w->c = x->p->c;
                    x->p->c = Black;
                    w->r->c = Black;
                    lRotate(x->p);
                    x = root;
                }
            } else {
                w = x->p->l;
                if (w->c == Red) {
                    w->c = Black;
                    x->p->c = Red;
                    rRotate(x->p);
                    w = x->p->l;
                }

                if (w->r->c == Black && w->l->c == Black) {
                    w->c = Red;
                    x = x->p;
                } else {
                    if (w->l->c == Black) {
                        w->r->c = Black;
                        w->c = Red;
                        lRotate(w);
                        w = x->p->l;
                    }

                    w->c = x->p->c;
                    x->p->c = Black;
                    w->l->c = Black;
                    rRotate(x->p);
                    x = root;
                }
            }
        }
    }

    /**
     * @brief Performs a right rotation of the tree to maintain balance after insertions and deletions.
     * 
     * @details This function rotates the tree to the right around the given node x. It updates the parent and child pointers accordingly.
     * 
     * @param x The node around which to perform the right rotation
     */
    void rRotate(RBNode<keyType, valueType> *x) {
        RBNode<keyType, valueType> *y = x->l;
        x->l = y->r;
        if (y->r != nil) {
            y->r->p = x;
        }
        y->p = x->p;
        if (x->p == nil) {
            root = y;
        } else if (x == x->p->r) {
            x->p->r = y;
        } else {
            x->p->l = y;
        }   
        y->r = x;
        x->p = y;
        y->size = x->size;
        x->size = x->l->size + x->r->size + 1;
    }

    /**
     * @brief Performs a left rotation of the tree to maintain balance after insertions and deletions.
     * 
     * @details This function rotates the tree to the left around the given node x. It updates the parent and child pointers accordingly.
     * 
     * @param x The node around which to perform the left rotation
     */
    void lRotate(RBNode<keyType, valueType> *x) {
        RBNode<keyType, valueType> *y = x->r;
        x->r = y->l;
        if (y->l != nil) {
            y->l->p = x;
        }
        y->p = x->p;
        if (x->p == nil) {
            root = y;
        } else if (x == x->p->l) {
            x->p->l = y;
        } else {
            x->p->r = y;
        }   
        y->l = x;
        x->p = y;
        y->size = x->size;
        x->size = x->l->size + x->r->size + 1;
    }

    /**
     * @brief Used to perform a transplant if a node with children is deleted
     * 
     * @param u The node to be replaced
     * @param v The node to replace u
     */
    void transplant(RBNode<keyType, valueType> *u, RBNode<keyType, valueType> *v) {

        // If u is the root, set the root to v
        if (u->p == nil) {
            root = v;

        // If u is the left child of its parent, set the left child of its parent to v
        } else if (u == u->p->l) {
            u->p->l = v;

        // If u is the right child of its parent, set the right child of its parent to v
        } else {
            u->p->r = v;
        } 

        // Set the parent of v to the parent of u
        v->p = u->p;
    }
};
#endif