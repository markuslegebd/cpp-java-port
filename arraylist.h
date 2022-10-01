#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>

template<class T>
class ArrayList {

    public:
        ArrayList();
        ArrayList(int theSize);
        ArrayList(const ArrayList<T> & list);
        ArrayList(const ArrayList<T> &list, int theCapacity);
        ~ArrayList();
        void add(const T & element);
        void add(const T & element, int index);
        bool addToSort(const T & element);
        void add(const ArrayList<T> & list, int index);
        void add(const ArrayList<T> & list);
        bool removeElement(const T & element);
        const T * remove(int index);
        void removeAll();
        void removeAll(int newCapacity);
        bool move(int index1, int index2);
        const T * get(int index) const;
        const ArrayList<T> & subList(int index1, int index2) const;
        T * getArray() const;
        T * getSubArray(int index1, int index2) const;
        int binarySearch(const T & element) const;
        void quickSort();
        void insertionSort();
        void mergeSort();
        void shuffle();
        int getSize() const;
        int getCapacity() const;
        std::string toString() const;
        
    private:
        T * array;
        int size;
        int capacity;
        bool sorted;

        void reallocate(); 
        void reallocate(int newSize);
        const T & choosePivot(int index1, int index2);
        void quickSort(int index1, int index2);
        int binarySearch(const T & element, int index1, int index2) const;
        void insertionSort(int index1, int index2);
        T * mergeSort(T * array, int theCapacity, int arraySize);
};

template<class T>
ArrayList<T>::ArrayList() {

    array = new T[20];
    capacity = 20;
    size = 0;
}

template<class T>
ArrayList<T>::ArrayList(int theSize) {

    array = new T[theSize];
    capacity = theSize;
    size = 0;
}

template<class T>
ArrayList<T>::ArrayList(const ArrayList<T> & list) {

    array = new T[list.getSize() * 2];
    capacity = list.getSize() * 2;
    size = list.getSize();

    for (int i = 0; i < list.getSize(); i++) {

        array[i] = *list.get(i);
    }
}

template<class T>
ArrayList<T>::ArrayList(const ArrayList<T> & list, int theCapacity) {

    if (theCapacity >= list.getSize()) {

        array = new T[theCapacity];
        capacity = theCapacity;
    }
    else {

        array = new T[list->getSize() * 2];
        capacity = list->getSize() * 2;
    }

    size = list->size;

    for (int i = 0; i < size; i++) {

        array[i] = list->get(i);
    }
}

template<class T>
ArrayList<T>::~ArrayList() {

    delete [] array;
}

template<class T>        
void ArrayList<T>::reallocate() {

    capacity *= 2;
    T * temp = new T[capacity];

    for (int i = 0; i < size; i++) {

        temp[i] = array[i];
    }

    delete [] array;

    array = temp;
}

template<class T>
void ArrayList<T>::reallocate(int newSize) {

    capacity = newSize;
    T * temp = new T[newSize];

    for (int i = 0; i < size; i++) {

        temp[i] = array[i];

        delete [] array;

        array = temp;
    }
}

template<class T>
void ArrayList<T>::add(const T & element) {

    if ((size - 1) == capacity) {

        reallocate();
    }

    array[size] = element;
    size++;

    sorted = false;
}

template<class T>
void ArrayList<T>::add(const T & element, int index) {

    if (index >= 0 && index <= size) {

        if (index >= capacity || size == capacity) {

            int multiplicand = (index >= capacity) ? index : size;
            reallocate(multiplicand * 2);
        }

        for (int i = size; i > index; i--) {

            array[i] = array[i - 1];
        }

        array[index] = element;
        size++;

        sorted = false;
    }
}

template<class T>
void ArrayList<T>::add(const ArrayList<T> & list) {

    for (int i = 0; i < list.getSize(); i++) {

        add(list.get(i));
    }
}

template<class T>
void ArrayList<T>::add(const ArrayList<T> & list, int index) {

    if (index >= capacity || (index + list.getSize()) >= capacity) {

        reallocate((index + list.getSize()) * 2);
    }

    T* temp = new T[capacity + list.getSize()];

    for (int i = 0, j = 0, k = 0; i < size + list.getSize(); i++) {

        if (i >= index && i < index + list.getSize()) {

            temp[i] = *list.get(j);
            j++;
        }
        else {

            temp[i] = array[k];
            k++;
        }
    }

    delete [] array;
    array = temp;
    size += list.getSize();

    sorted = false;
}

template<class T>
bool ArrayList<T>::addToSort(const T & element) {

    if (sorted) {

        add(element, binarySearch(element));

        sorted = true;

        return true;
    }

    return false;
}

template<class T>
bool ArrayList<T>::removeElement(const T & element) {

    int index = binarySearch(element);

    if (index >= 0 && index < size) {

        remove(index);

        return true;
    }
    else {

        return false;
    }
}

template<class T>
const T * ArrayList<T>::remove(int index) {

    T * removed = NULL;

    if (index < size && index >= 0) {

        for (int i = index; i < size; i++) {

            array[i] = array[i + 1];
        }

        removed = array + index;
        size--;
    }

    return removed;
}

template<class T>
void ArrayList<T>::removeAll() {

    delete [] array;
    array = new T[capacity];

    sorted = false;
    size = 0;
}

template<class T>
void ArrayList<T>::removeAll(int newCapacity) {

    delete [] array;
    array = new T[newCapacity];

    sorted = false;
    capacity = newCapacity;
    size = 0;
}

template<class T>
bool ArrayList<T>::move(int index1, int index2) {

    if (index1 >= 0 && index2 >= 0 &&
            index1 < size && index2 < size) {

        T temp = array[index1];
        array[index1] = array[index2];
        array[index2] = temp;

        sorted = false;

        return true;
    }

    return false;
}

template<class T>
const T * ArrayList<T>::get(int index) const {

    return (index >= 0 && index < size) ? (array + index) : NULL;
}

template<class T>
int ArrayList<T>::getSize() const {

    return size;
}

template<class T>
int ArrayList<T>::getCapacity() const {

    return capacity;
}

template<class T>
const ArrayList<T> & ArrayList<T>::subList(int index1, int index2) const {

    if (index1 >= 0 && index1 < size && index2 >= 0 && index2 <= size && index1 < index2) {

        ArrayList<T> returnList = new ArrayList<T>(index2 - index1);

        for (int i = index1; i < index2; i++) {

            returnList.add(this->get(i));
        }

        return returnList;
    }

    return NULL;
}

template<class T>
T * ArrayList<T>::getArray() const {

    T * arrayCopy = new T[size];

    for (int i = 0; i < size; i++) {

        arrayCopy[i] = array[i];
    }

    return arrayCopy;
}

template<class T>
T * ArrayList<T>::getSubArray(int index1, int index2) const {

    if (index1 >= 0 && index1 < size && index2 >= 0 && index2 <= size && index1 < index2) {

        T* returnList = new T[index2 - index1];

        for (int i = index1; i < index2; i++) {

            returnList[i] = this->get(i);
        }

        return returnList;
    }

    return NULL;
}

template<class T>
int ArrayList<T>::binarySearch(const T & element) const {

    if (sorted) {

        return binarySearch(element, 0, size - 1);
    }
    else {

        return -1;
    }
}

template<class T>
int ArrayList<T>::binarySearch(const T & element, int index1, int index2) const {

    if (index1 < index2) {

        int pivot = (index1 + index2) / 2;

        if (element < array[pivot]) {

            return binarySearch(element, index1, pivot - 1);
        }
        else if (element > array[pivot]) {

            return binarySearch(element, pivot + 1, index2);
        }
        else {

            return pivot;
        }
    }
    else if (index1 == index2) {

        return index1;
    }
    else {

        return -1;
    }
}

template<class T>
void ArrayList<T>::quickSort() {

    int index1 = 0;
    int index2 = size - 1;

    quickSort(index1, index2);

    sorted = true;
}

template<class T>
const T & ArrayList<T>::choosePivot(int index1, int index2) {

    int center = (index1 + index2) / 2;

    if (array[center] < array[index1]) {

        move(index1, center);
    }
    if (array[index1] > array[index2]) {

        move(index1, index2);
    }
    if (array[center] > array[index2]) {

        move(center, index2);
    }

    move(center, index2 - 1);

    return array[index2 - 1];
}

template<class T>
void ArrayList<T>::quickSort(int index1, int index2) {

    if (index2 - index1 >= 10) {

        const T & pivot = choosePivot(index1, index2);

        int i = index1, j = index2 - 1;

        while (true) {

            while (array[++i] < pivot);
            while (array[--j] > pivot);

            if (i < j) {

                move(i, j);
            }
            else {

                break;
            }
        }

        move(i, index2 - 1);

        quickSort(index1, i - 1);
        quickSort(i + 1, index2);
    }
    else {

        insertionSort(index1, index2);
    }
}

template<class T>
void ArrayList<T>::mergeSort() {

    T* temp = mergeSort(array, capacity, size);
    delete [] array;
    array = temp;
    sorted = true;
}

template<class T>
T * ArrayList<T>::mergeSort(T * array, int theCapacity, int arraySize) {

    T * returnArray;

    if (arraySize > 1) {

        int size1 = arraySize / 2;
        int size2 = arraySize - size1;

        T* array1;
        T* array2;

        array1 = mergeSort(array, size1, size1);
        array2 = mergeSort(array + size1, size2, size2);

        returnArray = new T[theCapacity];

        int i = 0, j = 0, k = 0;
        while (i < arraySize) {

            if ((j < size1) &&  (k == size2 || array1[j] <= array2[k])) {

                returnArray[i] = array1[j];
                j++;
            }
            else {

                returnArray[i] = array2[k];
                k++;
            }

            i++;
        }


        delete [] array1;
        delete [] array2;
        array1 = 0;
        array2 = 0;
    }
    else {

        returnArray = new T[1];
        returnArray[0] = array[0];
    }

    return returnArray;
}

template<class T>
void ArrayList<T>::insertionSort() {

    insertionSort(0, size - 1);

    sorted = true;
}

template<class T>
void ArrayList<T>::insertionSort(int index1, int index2) {

    if (index1 < index2
            && index1 >= 0 && index1 < size
            && index2 >= 0 && index2 < size) {

        T element;

        for (int i = index1; i <= index2; i++) {

            element = array[i];

            for (int j = i; j >= 0; j--) {

                if (j == 0 || array[j - 1] <= element) {

                    array[j] = element;
                    break;
                }
                else {

                    array[j] = array[j - 1];
                }
            }
        }
    }
}

template<class T>
void ArrayList<T>::shuffle() {

    T temp;
    int random;

    for (int i = 0; i < size; i++) {
        random = rand() % size;

        temp = array[i];
        array[i] = array[random];
        array[random] = temp;
    }

    sorted = false;
}

template<class T>
std::string ArrayList<T>::toString() const {

    std::ostringstream streamOut;

    streamOut << "(";

    for (int i = 0; i < size; i++) {

        streamOut << array[i];

        if (i != (size - 1)) {

            streamOut << ", ";
        }
    }

    streamOut << ")\n";

    std::string returnString = streamOut.str();

    return returnString;
}

#endif /* ARRAYLIST_H_ */