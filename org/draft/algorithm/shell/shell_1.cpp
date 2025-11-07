/*
 * 这是第一版, 目标:
 * 1. 理解并实现
 *
 * 已知问题:
 * 每次gap循环中, 先把数组拆分, 再分别对每个拆分对数组进行了插入排序
 * 导致使用了2次for循环, 一次 for: gap, 一次for: 拆分后对数组.
 * 实际上可以简化, 因为拆分后的数组之间没有联系. 因此没必要先排序数组A, 再排序B, 再排序C
 * 可以在一次for循环中, 同时完成对A, B, C的排序
 * A 排序前n个元素之后, 排序B的前n个元素, 再排序C...依次执行即可
 */

#include <iostream>
#include <string>

namespace shell_sort_1{
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
        //对拆分后的数组 依次进行排序
        for (int index=0; index < gap; index++){
            //拆分后的数组 进行 插入排序
            for(int i = index + gap; i < _array_size; i+=gap){
                std::string info;
                for(auto temp = index; temp < _array_size; temp+=gap){
                    info += std::to_string(_array[temp]);
                    info += " ";
                }
                std::cout << gap << "-" << index << "-" << (i-index)/gap << ": " <<  info << std::endl;

                auto temp = _array[i];
                int j = i;
                for (; j >=gap && _array[j-gap] > temp; j-=gap){
                    _array[j] = _array[j-gap];
                }
                _array[j] = temp;
            }
        }
    }

    std::string info;
    for(auto temp = 0; temp < _array_size; temp++){
        info += std::to_string(_array[temp]);
        info += " ";
    }
    std::cout <<  info << std::endl;
}

}

// int main(){
//     int data[9] =  {7, 5, 2, 3, 4, 1, 9, 6, 8};
//     shell_sort(data, 9);
// }
