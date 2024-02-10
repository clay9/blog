/*
 * 这是第一版, 目标:
 * 1.仿照std::priority_queue接口
 *
 * 已知问题:
 * 数组表示的时候, 从数组index=1的位置开始存储, 而不是index=0的位置.
 * index=1的位置存储, child_left = p*2; child_right = p*2 +1; p = child /2
 * index=0的位置存储, child_left = p*2 +1; child_right = p*2 +2; p = (child-1) /2
 * 可以看出, 两者的计算方式不一致;
 */

#include <cstring>
#include <iostream>
#include <string>

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

void heap_array::info(){
    std::string info;
    for(int i=0; i <= last_eindex; i++){
        info += std::to_string(data[i]);
        info += " ";
    }
    std::cout << info << std::endl;
}

heap_array::heap_array(){
    last_eindex = -1;
}

int heap_array::top(){
    int top = (last_eindex == -1) ? -1 : data[0];

    std::cout << "top: " << top << std::endl;
    return top;
}

void heap_array::push(int val){
    if(last_eindex == MAXSIZE-1) return; //full
    if(last_eindex == -1) {
        data[++last_eindex] = val;
        //std::cout << "push " << last_eindex << ":" << val << std::endl;
        info();
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
    info();
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

    info();
}


int main(){
    heap_array ha;

    ha.top();

    ha.push(2);
    ha.push(1);
    ha.push(3);
    ha.push(4);
    ha.push(5);
    ha.push(6);

    ha.pop();
    ha.pop();
}
