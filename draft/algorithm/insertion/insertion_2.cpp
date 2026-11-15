/*
 * 这是第二版, 目标:
 * 1. 修改第一版中 元素移动
 */

#include <iostream>
#include <string>


std::string print_array(int _array[], int _array_size){
    std::string info;
    for(int temp=0; temp< _array_size; temp++){
        info += std::to_string(_array[temp]);
        info += " ";
    }

    return info;
}

void insertion_sort(int _array[], int _array_size){

    for(int i=1; i < _array_size; i++){

        auto temp = _array[i];
        int j = i;
        for(; j >0 && _array[j-1] > temp; j--){
            _array[j] = _array[j-1];

            std::cout << i << "-" << i-j + 1<< ": " << print_array(_array, _array_size) << std::endl;
        }
        _array[j] = temp;

        std::cout << i << ": " << print_array(_array, _array_size) << std::endl;
    }
}


int main(){
    int data[5] =  {1, 5, 2, 4, 3};
    insertion_sort(data, 5);
}
