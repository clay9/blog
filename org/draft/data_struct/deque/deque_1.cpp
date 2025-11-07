/*
 * 这是第一版, 目标:
 * 1.仿照std::deque接口
 *
 * 已知问题:
 * 1. 虽然命名为dequee(double-ended queue), 但实际实现的是FIFO的queeu
 *    dequee是双端都可插入|删除;
 *    queue 只能是FIFO
 */

#include <cstring>
#include <iostream>

//数组实现
const int MAXSIZE =3;
template<typename T>
struct deque_array{
    T data[MAXSIZE];
    int _front;
    int _rear;

    //创建
    deque_array();

    //是否空
    bool empty();
    //是否满
    bool full();
    //大小
    int size();

    //添加, 删除
    void insert(T const& val);
    void erase();

    //获取
    T front();
    T back();
};

template <typename T>
deque_array<T>::deque_array() {
    std::memset(&data, 0, sizeof(data));
    _front = -1;
    _rear = -1;
}
template <typename T>
bool deque_array<T>::empty(){
    return (_front == -1) && (_rear == -1);
}
template <typename T>
bool deque_array<T>::full(){
    if(_front ==0 && _rear == MAXSIZE-1) return true;
    if(_front - _rear == 1) return true;
    return false;
}
template <typename T>
int deque_array<T>::size(){
    if(empty()) return 0;
    if(_front == _rear) return 1;
    if(_front > _rear) return MAXSIZE - (_front - _rear -1);
    if(_front < _rear) return _rear - _front +1;
    return 0;
}
template <typename T>
void deque_array<T>::insert(T const& val){
    if(full()){
        std::cout << "insert fail. deque is full" << std::endl;
        return;
    }
    if(empty()){
        _front ++;
        _rear ++;
    }else{
        _rear++;
        if(_rear == MAXSIZE) _rear = 0;
    }

    data[_rear] = val;
}
template <typename T>
void deque_array<T>::erase(){
    if(empty()){
        std::cout << "erase fail. deque empty" << std::endl;
        return;
    }

    if(_front == _rear){
        _front = -1;
        _rear = -1;
    }else{
        _front++;
        if (_front == MAXSIZE) _front = 0;
    }
}
template <typename T>
T deque_array<T>::front(){
    if(empty() || _front < 0){
        std::cout << "call front() fail. deque empty" <<std::endl;
        T a;
        std::memset(&a, 0, sizeof(a));
        return a;
    }

    return data[_front];
}
template <typename T>
T deque_array<T>::back(){
    if(empty()){
        std::cout << "call back() fail. deque empty" <<std::endl;
        T a;
        std::memset(&a, 0, sizeof(a));
        return a;
    }

    return data[_rear];
}

void test_deque_array(){
    deque_array<int> da;
    da.front();
    da.back();
    da.erase();
    std::cout << da.size() << std::endl;

    da.insert(1);
    da.front();
    da.back();
    std::cout << da.size() << std::endl;
    da.erase();

    da.insert(1);
    da.insert(2);
    da.insert(3);
    da.insert(4);

    std::cout << da.size() << std::endl;

    while(!da.empty()){
        std::cout << da.front() << std::endl;
        da.erase();
    }

    std::cout << da.size() << std::endl;
}



//链表实现
template <typename T>
struct deque_element{
    T data;
    deque_element* next;
};

template<typename T>
struct deque_list{
    deque_element<T>* _front;
    deque_element<T>* _rear;

    deque_list() : _front(nullptr), _rear(nullptr){ }

    bool empty();
    int size();

    void insert(T const&);
    void erase();

    T front();
    T back();
};
template<typename T>
bool deque_list<T>::empty(){
    return _front == nullptr && _rear == nullptr;
}
template<typename T>
int deque_list<T>::size(){
    if(_front == nullptr) return 0;
    int size = 1;
    auto next_dl = _front->next;
    while( next_dl != nullptr){
        size++;
        next_dl = next_dl->next;
    }
    return size;
}
template<typename T>
void deque_list<T>::insert(T const& val){
    auto new_dl = new deque_element<T>;
    new_dl->data = val;
    new_dl->next = nullptr;

    if(_rear == nullptr){
        _front = new_dl;
        _rear = new_dl;
    }else{
        _rear->next = new_dl;
        _rear = new_dl;
    }
}
template<typename T>
void deque_list<T>::erase(){
    if(empty()){
        std::cout << "erase fail. deque empty" << std::endl;
        return;
    }

    if(_front == _rear){
        delete _front;
        _front = nullptr;
        _rear = nullptr;
    }else{
        auto temp_dl = _front;
        _front = _front->next;
        delete temp_dl;
    }
}
template<typename T>
T deque_list<T>::front(){
    if(empty()) {
        std::cout << "call front fail. deque empty()" << std::endl;
        T a;
        std::memset(&a, 0, sizeof(a));
        return a;
    }
    return _front->data;
}
template<typename T>
T deque_list<T>::back(){
    if(empty()) {
        std::cout << "call back fail. deque empty()" << std::endl;
        T a;
        std::memset(&a, 0, sizeof(a));
        return a;
    }
    return _rear->data;
}

void test_deque_list(){
    deque_list<int> dl;
    dl.front();
    dl.back();
    dl.erase();
    std::cout << dl.size() << std::endl;

    dl.insert(1);
    dl.front();
    dl.back();
    std::cout << dl.size() << std::endl;
    dl.erase();

    dl.insert(1);
    dl.insert(2);
    dl.insert(3);
    dl.insert(4);

    std::cout << dl.size() << std::endl;

    while(!dl.empty()){
        std::cout << dl.front() << std::endl;
        dl.erase();
    }

    std::cout << dl.size() << std::endl;
}

int main(){
    test_deque_array();

    std::cout <<"--------" << std::endl;
    test_deque_list();
}
