/*
 * 这是第一版, 目标:
 * 1. 理解并实现
 *
 * 已知问题:
 * 排序思想错误, 导致数据移动次数增加.
 * 比如 1 2 6 7 5 正常插入排序应该如下
 * => 1 2 6 7 7
 * => 1 2 6 6 7
 * => 1 2 5 6 7
 * 每次的时候, 只需要把i-1的元素移动到i位置即可. 不需要管i-1位置的元素.
 * 最后在合适的位置插入元素5
 * 总共元素移动次数为2 + 1 = 3 => n + 1
 *
 * 而我实现的算法. 排序如下:
 * => 1 2 6 5 7
 * => 1 2 5 6 7
 * 导致每次即需要移动i-1位置, 也需要移动i位置. 有点类似冒泡排序相邻元素互换.
 * 总共元素移动次数为 2 * 2 = 4 => n + n
 */

#include <iostream>
#include <string>

namespace insertion_sort_1{
void insertion_sort(int _array[], int _array_size){

    for(int i=1; i < _array_size; i++){
        for(int j=i; j >0; j--){
            if(_array[j] >= _array[j-1]) {
                break;
            }else{
                auto temp = _array[j];
                _array[j]  = _array[j-1];
                _array[j-1] = temp;
            }

            std::string info;
            for(int i=0; i< _array_size; i++){
                info += std::to_string(_array[i]);
            }
            std::cout << i << "-" << i-j +1 << ": " << info << std::endl;
        }
    }
}
}

// int main(){
//     int data[5] =  {1, 5, 2, 4, 3};
//     insertion_sort(data, 5);
//}
