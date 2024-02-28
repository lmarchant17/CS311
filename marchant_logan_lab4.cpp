#ifndef COMPACT_QUEUE_H
#define COMPACT_QUEUE_H

#include <iostream>

template<typename T>
class compact_queue {
    T* data;
    bool full = false;
    size_t start = 0, last = 0; // last points to empty spot
    size_t datasize;    
public:
    compact_queue(size_t size){
        datasize = size;
        data = new T[size];
    }
    void enqueue(T item){
        if(full) {
            T* new_data = new T[datasize * 2];
            for(size_t ndi = 0; ndi < datasize; ndi++){
                new_data[ndi] = data[(ndi + start) % datasize ];
            }
            delete [] data;
            data = new_data;
            last = datasize;
            start = 0;
            datasize = datasize * 2;
            full = false;
        }
        data[last] = item;
        last++;
        if(last == datasize)
            last = 0;
        if(last == start)
            full = true;    
    }
    size_t size(){
        if(last > start)
            return last - start;
        if(full)
            return datasize;
        if(start > last)
            return datasize - start + last;
        return 0; // start and last are same, full = false
    }
    void sort(){
        bool changed = true;
        size_t idx, idxplus;
        while(changed){
            changed = false;
            for(size_t i = 0; i < size() - 1; i++) {
                if(start < last){
                    idx = i + start;
                    idxplus = idx + 1;
                } else if(last <= start) {
                    idx = i + start % datasize;
                    idxplus = (idx + 1) % datasize;
                }    
                if(data[idx] > data[idxplus]){
                    T temp = data[idx];
                    data[idx] = data[idxplus];                    
                    data[idxplus] = temp;
                    changed = true;
                }
            }
        }
    }
    bool empty(){
        return start == last && !full;
    }
    T dequeue(){
        if(full)
            full = false;
        return data[start++];
    }
    ~compact_queue(){
        delete [] data;
    }

    // C++11-style for loop support
    T* begin() { return data + start; }
    T* end() { return data + (full ? datasize : last); }

    // Overload the insertion operator to print queue
    friend std::ostream& operator<<(std::ostream& out, const compact_queue& q) {
        out << "[";
        for(auto item : q) {
            out << item << ", ";
        }
        out << "\b\b]";
        return out;
    }
};

#endif