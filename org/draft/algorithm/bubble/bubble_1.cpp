/*
 * 这是第一版, 目标:
 * 1. 理解并实现bubble sort
 */

#include <iostream>
#include <string>

void bubble_sort(int _array[], int _array_size){

    for(int j = _array_size -1; j > 0; j--){
        bool flag = false;
        for(int i=0; i < j; i++){
            if(_array[i] > _array[i+1]){
                auto temp = _array[i];
                _array[i] = _array[i+1];
                _array[i+1] = temp;

                flag = true;
            }

            std::string info;
            for(int i=0; i< _array_size; i++){
                info += std::to_string(_array[i]);
            }
            std::cout << _array_size-j << "-" << i+1 << ": " << info << std::endl;
        }

        if(!flag ) break;
    }
}


int main(){
    int data[5] =  {1, 5, 2, 3, 4};
    bubble_sort(data, 5);
}
