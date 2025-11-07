#ifndef stack_my
#define stack_my

#include <iostream>
#include <cstring>

/*
 * 这是第一版, 问题比较多
 * 1.未使用范型
 * 2.异常错误的处理
 * 3.接口设计
*/

namespace stack_1{
//数组实现的stack
//已知问题:
//1. 异常来取代错误码
//2. 类型只是int, 没有泛用性, 应该使用template代替
const int MAXSIZE = 3;
struct stack_array{
    int data[MAXSIZE];
    int current_point; //-1表示还没有占用

    //创建一个stack
    stack_array();
    //添加数据
    int push(int val);
    //取出一个数据
    int pop();
};

stack_array::stack_array(){
    std::memset(data, 0, sizeof(data));
    current_point = -1;
}
int stack_array::push(int val){
    if (current_point >= (MAXSIZE-1) ) return -1;
    current_point ++;

    data[current_point] = val;
    return 0;
}
int stack_array::pop(){
    if (current_point == -1 ) return -1;
    return data[current_point--];
}
void test_stack_array(){
    int result =0;
    stack_array sa;
    std::cout << "stack_array inited!" << std::endl;

    result = sa.pop();
    std::cout << "pop result: " << result << std::endl;

    result = sa.push(1);
    std::cout << "push result: " << result << std::endl;
    result = sa.push(2);
    std::cout << "push result: " << result << std::endl;

    result = sa.pop();
    std::cout << "pop result: " << result << std::endl;

    result = sa.push(3);
    std::cout << "push result: " << result << std::endl;
    result = sa.push(4);
    std::cout << "push result: " << result << std::endl;

    result = sa.pop();
    std::cout << "pop result: " << result << std::endl;
    result = sa.pop();
    std::cout << "pop result: " << result << std::endl;
    result = sa.pop();
    std::cout << "pop result: " << result << std::endl;
    result = sa.pop();
    std::cout << "pop result: " << result << std::endl;
}


//链表的实现
//已知问题:
//1. new 失败之后的处理
//2. 异常代替错误码
//3. 类型只是int, 没有泛用性, 应该使用template代替
struct stack_list{
    int data;
    stack_list *next;

    //create
    stack_list();
    //push
    int push(int val);
    //pop
    int pop();
};

stack_list::stack_list() :data(0), next(nullptr){

}
int stack_list::push(int val){
    //TODONOW new 失败的情况
    auto next_sl = new stack_list;
    next_sl->data = val;

    auto pre_next_sl = this->next;
    this->next = next_sl;
    next_sl->next = pre_next_sl;

    return 0;
}
int stack_list::pop(){
    auto pre_next_sl = this->next;
    if(pre_next_sl == nullptr){
        return -1;
    }else{
        int val = pre_next_sl->data;
        this->next = pre_next_sl->next;
        delete pre_next_sl;
        return val;
    }
}
void test_stack_list(){
    int result =0;
    stack_list sl;
    std::cout << "stack_list inited!" << std::endl;

    result = sl.pop();
    std::cout << "pop result: " << result << std::endl;

    result = sl.push(1);
    std::cout << "push 1 result: " << result << std::endl;
    result = sl.push(2);
    std::cout << "push 2 result: " << result << std::endl;

    result = sl.pop();
    std::cout << "pop result: " << result << std::endl;

    result = sl.push(3);
    std::cout << "push 3 result: " << result << std::endl;
    result = sl.push(4);
    std::cout << "push 4 result: " << result << std::endl;

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


// int main(){
//     stack_1::test_stack_list();
// }


#endif
