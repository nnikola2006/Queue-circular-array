#include <iostream>
using std::cout, std::cin, std::endl;

class Queue{
private:
    int* arr;
    int front = -1, rear = -1;
    int capacity = 0, count = 0;
public:
    Queue(int capacity){
        arr = new int[capacity];
        front = 0, rear = 0;
        this->capacity = capacity;
    }
    ~Queue(){
        delete[] arr;
        arr = nullptr;
    }
    void enqueue(int element){
        // If the array is full
        if(isFull()){
            cout << "Array is full!" << endl;
            return;
        }
        // If the array is empty
        if(isEmpty()){
            front = 0, rear = 0;
            arr[front] = element;
            count++;
            return;
        }
        // If the array has elementy in it
        rear = (rear + 1) % count;
        arr[rear] = element;
        count++;
    }
    void dequeue(){
        if(isEmpty()){
            cout << "There is nobody in the queue" << endl;
            return;
        }
        if(front == rear){
            front = -1, rear = -1;
            count--;
            return;
        }
        front = (front + 1) % count;
        count--;
    }
    void full_print(){
        if(isEmpty()){
            cout << "The queue is empty!" << endl;
            return;
        }
        for(int i = 0; i < count; i++){
            cout << arr[i] << ",";
        }
    }
    int peek_front(){
        if(!isEmpty()){
            return arr[front];
        }
        return -1;
    }
    int peek_back(){
        if(!isEmpty()){
            return arr[rear];
        }
        return -1;
    }
    bool isFull(){
        // If the rear == front then it's full
        if(count == capacity){
            return true;
        }
        return false;
    }
    bool isEmpty(){
        // If the count is 0 then it's empty
        if(count == 0){
            return true;
        }
        return false;
    }
    int size(){
        return count;
    }
};

int main(){
    Queue queue(10);

    // Doesn't print the correct values. Required fixing
    queue.enqueue(20);
    queue.enqueue(10);
    queue.enqueue(15);
    queue.full_print();
    // cout << queue.peek_front() << endl;
    // cout << queue.peek_back();
    // cout << queue.isEmpty() << "," << queue.isFull() << queue.peek_back() << queue.peek_front();

    return 0;
}