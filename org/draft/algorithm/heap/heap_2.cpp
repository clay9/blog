/*
 * 这是第二版, 目标: 修复第一版中问题
 */

#include <iostream>
#include <string>

void info(int _array[], int _array_size) {
    std::string info;
    for(int i=0; i < _array_size; i++){
        info += std::to_string(_array[i]);
        info += " ";
    }
    std::cout << info << std::endl;
}

void sort(int _array[], int _array_size, int index){
    int temp = _array[index];
    int i = index;
    for(; i*2+1 < _array_size; ){
        //找到最大的儿子
        int child = i*2+1;
        if(child + 1 < _array_size && _array[child+1] > _array[child]){
            child ++;
        }

        //std::cout << _array_size-1 << ":" << i << "-" << child << std::endl;

        if(temp > _array[child]) break;
        _array[i] = _array[child];
        i = child;
    }
    _array[i] = temp;

    //std::cout << i << ":" << temp << std::endl;
}

void heap_sort(int _array[], int _array_size){
    //(_array_size-1-1)/2是第一个有叶子的node.
    //从该node 一直循环到根结点即可
    for(int i= (_array_size-1-1)/2; i>=0; i--){
        sort(_array, _array_size, i);
    }

    info(_array, _array_size);

    for(int i=_array_size-1; i>=0; i--){
        int temp = _array[0];
        _array[0] = _array[i];
        _array[i] = temp;

        sort(_array, i, 0);

        info(_array, _array_size);
    }

}

int main(){
    int data[7] = {5, 3, 4, 1, 2, 7, 6};
    heap_sort(data, 7);

}
