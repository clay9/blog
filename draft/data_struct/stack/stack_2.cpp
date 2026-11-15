#ifndef stack_my
#define stack_my

#include <exception>
#include <iostream>
#include <cstring>

/*
 * 这是第二版
 * 相对于第一版, 修改来
 * 1.范型
 *
 * 遗留的问题:
 * 1. pop或push fail的处理.
      std::stack如果没有元素, top()会发生段错误
 * 2. 接口应该模仿stack设计
      void push(T const&);
      void pop();
      T top();
      push, pop不返回数据, 通过top()来查看数据
*/
namespace stack_2{
//数组实现的stack
const int MAXSIZE = 3;
template <typename T>
struct stack_array{
    T data[MAXSIZE];
    int current_point; //-1表示还没有占用

    //创建一个stack
    stack_array();
    //添加数据
    void push(T const& val);
    //取出一个数据
    T pop();
};

template <typename T>
stack_array<T>::stack_array(){
    std::memset(data, 0, sizeof(data));
    current_point = -1;
}
template <typename T>
void stack_array<T>::push(T const& val){
    if (current_point >= (MAXSIZE-1) ) {
        std::cout << "push fail. stack is full" << std::endl;
        return;
    }
    current_point ++;

    data[current_point] = val;
}
template <typename T>
T stack_array<T>::pop(){
    if (current_point == -1 ) {
        std::cout << "pop fail. stack empty." << std::endl;
        T a;
        memset(&a, 0, sizeof(a));
        return a;
    }
    return data[current_point--];
}
void test_stack_array(){
    stack_array<int> sa;
    std::cout << "stack_array inited!" << std::endl;

    sa.pop();
    sa.push(1);
    sa.push(2);

    std::cout << "pop result: " << sa.pop() << std::endl;

    sa.push(3);
    sa.push(4);

    std::cout << "pop result: " << sa.pop() << std::endl;
    std::cout << "pop result: " << sa.pop() << std::endl;
    std::cout << "pop result: " << sa.pop() << std::endl;
    std::cout << "pop result: " << sa.pop() << std::endl;
}


//链表的实现
template <typename T>
struct stack_list{
    T data;
    stack_list *next;

    //create
    stack_list() : next(nullptr){}
    //push
    void push(T const& val);
    //pop
    T pop();
};

template <typename T>
void stack_list<T>::push(T const& val){
    try{
        auto next_sl = new stack_list;
        next_sl->data = val;

        auto pre_next_sl = this->next;
        this->next = next_sl;
        next_sl->next = pre_next_sl;
    }
    catch (std::exception& e){
        std::cout << "catch exception: " << e.what() << std::endl;
    }
}
template <typename T>
T stack_list<T>::pop(){
    auto pre_next_sl = this->next;
    if(pre_next_sl == nullptr){
        std::cout << "pop fail" << std::endl;
        T a;
        memset(&a, 0, sizeof(a));
        return a;
    }else{
        T val = pre_next_sl->data;
        this->next = pre_next_sl->next;
        delete pre_next_sl;
        return val;
    }
}
void test_stack_list(){
    int result =0;
    stack_list<int> sl;
    std::cout << "stack_list inited!" << std::endl;

    result = sl.pop();
    std::cout << "pop result: " << result << std::endl;

    sl.push(1);
    sl.push(2);

    result = sl.pop();
    std::cout << "pop result: " << result << std::endl;

    sl.push(3);
    sl.push(4);

     result = sl.pop();
    std::cout << "pop result: " << result << std::endl;
    result = sl.pop();
    std::cout << "pop result: " << result << std::endl;
    result = sl.pop();
    std::cout << "pop result: " << result << std::endl;
    result = sl.pop();
    std::cout << "pop result: " << result << std::endl;
}

}

int main(){
    stack_2::test_stack_array();
    stack_2::test_stack_list();
}


#endif
