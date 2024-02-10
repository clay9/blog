/*
 * 这是第一版, 目标:
 * 1. 理解并实现
 *
 * 理解: 分而治之
 * 分: (递归实现) 完全二叉树样式; 先执行最底层node, 再执行其兄弟node, 其次父节点; 其次兄弟节点, 父节点...
 * 分: (非递归)
 * 治: AB是有序其相邻的数组, C是新的数组;  治就是把AB的有序放到C中. 三个指针完成
 *
 */

#include <iostream>
#include <string>

//递归实现
void merge(int _array[], int _temp_array[], int L, int R, int R_end){
    int L_end = R -1;
    int temp = L, start=L;

    while(L <= L_end && R <= R_end){
        if(_array[L] <= _array[R]) _temp_array[temp++] = _array[L++];
        else _temp_array[temp++] = _array[R++];
    }

    while( L <= L_end) _temp_array[temp++] = _array[L++];
    while( R <= R_end) _temp_array[temp++] = _array[R++];

    for(int i = start; i<=R_end; i++){
        _array[i] = _temp_array[i];
    }

    std::string info;
    for(int i = start; i<=R_end; i++){
        info += std::to_string(_array[i]);
        info += " ";
    }
    std::cout << info << std::endl;
}
void merge_sort_p(int _array[], int _temp_array[], int L, int R_end){
    if(L < R_end){
        int center = (L + R_end) /2;
        merge_sort_p(_array, _temp_array, L, center);
        merge_sort_p(_array, _temp_array, center+1, R_end);

        merge(_array, _temp_array, L, center+1, R_end);
    }
}
void merge_sort(int _array[], int _array_size){
    int _temp[_array_size];
    merge_sort_p(_array, _temp, 0, _array_size -1);
}


//非递归实现
void merge_sort_nore(int _array[], int _array_size){
    int _temp_array[_array_size];

    int length =1;
    while (length < _array_size){
        int i = 0;
        for (; i <= _array_size-2*length; i+= length*2){
            merge(_array, _temp_array, i, i+length, i + length*2 -1);
        }

        //说明 最后还有个奇数数组 未合并, 与之前的数组合并
        if(i >0 && i<_array_size){
            merge(_array, _temp_array, i-2*length, i, _array_size-1);
        }

        std::string info;
        for(int i=0; i<_array_size; i++){
            info += std::to_string(_array[i]);
            info += " ";
        }
        std::cout << length << ": " << i << ": " << info << std::endl;

        length *= 2;
    }
}

int main(){
    int data[9] =  {9, 1, 5, 2, 3, 4, 7, 8, 6};

    int data2[8] =  {1, 5, 2, 3, 4, 7, 8, 6};
    //merge_sort(data, 9);
    merge_sort_nore(data, 9);
    //merge_sort_nore(data2, 8);
}
