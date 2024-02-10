/*
 * 这是第2版, 目标:
 * 1. 修复第一版问题
 *
 */

#include <iostream>
#include <string>

int get_gap(int& pre_gap){
    if(pre_gap == 1) return false;

    if(pre_gap == 0) pre_gap = 5;
    else if(pre_gap == 5) pre_gap = 3;
    else if(pre_gap == 3) pre_gap = 1;

    return true;
}

void shell_sort(int _array[], int _array_size){

    int gap = 0;
    while(get_gap(gap)) {//每次gap循环
        //拆分后的数组 同时进行排序
        for(int i = gap; i < _array_size; i++){
            std::string info;
            for(int temp=0; temp < _array_size; temp++){
                info += std::to_string(_array[temp]);
                info += " ";
            }
            std::cout << gap << "-" << i-gap << ": " <<  info << std::endl;

            auto temp = _array[i];
            int j = i;
            for (; j >=gap && _array[j-gap] > temp; j-=gap){
                _array[j] = _array[j-gap];
            }
            _array[j] = temp;
        }
    }

    std::string info;
    for(auto temp = 0; temp < _array_size; temp++){
        info += std::to_string(_array[temp]);
        info += " ";
    }
    std::cout <<  info << std::endl;
}


int main(){
    int data[9] =  {7, 5, 2, 3, 4, 1, 9, 6, 8};
    shell_sort(data, 9);
}
