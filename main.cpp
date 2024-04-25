#include <iostream>
using namespace std;

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
        rear = (rear + 1) % capacity;
        arr[rear] = element;
        count++;
    }
    void dequeue(){
        if(isEmpty()){
            cout << "There is nothing in the queue" << endl;
            return;
        }
        if(front == rear){
            front = -1, rear = -1;
            count--;
            return;
        }
        front = (front + 1) % capacity;
        count--;
    }
    void full_print(){
        if(isEmpty()){
            cout << "The queue is empty!" << endl;
            return;
        }
        for(int i = rear; i >= front; i--){
            if(i == front){
              cout << arr[i] << endl;
              return;
            }
            cout << arr[i] << "->";
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
    void fill(){
        for(int i = 0; i < capacity; i++){
            enqueue(i);
        }
    }
    int size(){
        return count;
    }
    void getFront(){
      cout << front << endl;
    }
};

int main(){
    Queue queue(10);

    /*queue.enqueue(20);
    queue.enqueue(10);
    queue.enqueue(15);
    queue.dequeue();
    queue.enqueue(50);
    queue.enqueue(571);*/
    queue.fill();
    cout << "Front: ";                   queue.getFront();
    queue.dequeue();
    queue.dequeue();
    cout << "Front: ";
    queue.getFront();
    queue.full_print();
    cout << endl;
    cout << "Empty: " << queue.isEmpty() << ", Full: " << queue.isFull() << endl;
    cout << "Front: " << queue.peek_front() << ", Back: " << queue.peek_back();

    return 0;
}