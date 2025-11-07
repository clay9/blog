/*
 * 这是第一版, 目标: 理解并实现堆排序
 *
 * 已知问题:
 * 1. 引入来strct heap_array, 导致空间复杂度O(n)
 * 2. heap的使用 数组元素遍历插入的 方式插入. 时间复杂度nlogN
 */

#include <cstring>
#include <iostream>
#include <string>

namespace heap_1{
const int MAXSIZE = 10;
struct heap_array {
    int data[MAXSIZE];
    int last_eindex;

    heap_array();

    int top();

    void push(int val);
    void pop();

    void info();
};

heap_array::heap_array(){
    last_eindex = -1;
}
int heap_array::top(){
    int top = (last_eindex == -1) ? -1 : data[0];

    //std::cout << "top: " << top << std::endl;
    return top;
}
void heap_array::push(int val){
    if(last_eindex == MAXSIZE-1) return; //full
    if(last_eindex == -1) {
        data[++last_eindex] = val;
        //std::cout << "push " << last_eindex << ":" << val << std::endl;
        //info();
        return;
    }

    int index = ++last_eindex;
    for(; index > 0; ){
        int parent = (index-1)/2;
        if(data[parent] > val) break;
        data[index] = data[parent];
        index = parent;
    }

    data[index] = val;

    //std::cout << "push " << index << ":" << val << std::endl;
    //info();
}
void heap_array::pop(){
    if(last_eindex == -1) return;

    int temp = data[last_eindex--];

    int index = 0;
    int child_index = 0;
    for(; index*2 + 1 <= last_eindex; index = child_index){
        //find max child
        child_index = index * 2 + 1;
        if(child_index + 1 <= last_eindex && data[child_index] < data[child_index + 1]){
            child_index++;
        }

        if(temp > data[child_index]) break;
        data[index] = data[child_index];
    }

    data[index] = temp;

    //info();
}
void heap_array::info(){
    std::string info;
    for(int i=0; i <= last_eindex; i++){
        info += std::to_string(data[i]);
        info += " ";
    }
    std::cout << last_eindex << ": " << info << std::endl;
}


void heap_sort(int _array[], int _array_size){
    heap_array ha;
    for(int i=0; i< _array_size; i++){
        ha.push(_array[i]);
    }
    ha.info();

    for(int i=_array_size-1; i>=0; i--){
        _array[i] = ha.top();
        ha.pop();
        ha.info();
    }
}

// int main(){
//     int data[7] = {5, 3, 4, 1, 2, 7, 6};
//     heap_sort(data, 7);

//     std::string info;
//     for(int i=0; i < 7; i++){
//         info += std::to_string(data[i]);
//         info += " ";
//     }
//     std::cout << info << std::endl;
// }
}
