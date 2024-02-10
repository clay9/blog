/*
 * 这是第一版, 目标:
 * 1. 理解并实现selection sort
 */

#include <iostream>
#include <string>

void selection_sort(int _array[], int _array_size){

    for(int j = 0; j < _array_size-1; j++){
        int min_pos = j;

        for(int i = j; i < _array_size; i++){
            if(_array[i] < _array[min_pos]){
                min_pos = i;
            }
        }

        auto temp = _array[j];
        _array[j] = _array[min_pos];
        _array[min_pos] = temp;

        std::string info;
        for(int i=0; i< _array_size; i++){
            info += std::to_string(_array[i]);
        }
        std::cout << j+1 << ": " << info << std::endl;
    }
}




int main(){
    int data[5] =  {1, 5, 2, 3, 4};
    selection_sort(data, 5);
}
