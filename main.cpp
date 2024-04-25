#include <iostream>
using namespace std;

class Queue{
private:
    int* arr;
    int front = -1, rear = -1;
    int capacity = 0, count = 0;
public:
    Queue(const int capacity){
        arr = new int[capacity];
        front = 0, rear = 0;
        this->capacity = capacity;
    }
    ~Queue(){
        delete[] arr;
        arr = nullptr;
    }
    void enqueue(const int element){
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
    void print(){
        // Checks if the queue is empty
        if(isEmpty()){
            cout << "The queue is empty!" << endl;
            return;
        }
        // Prints the elements of the array
        cout << "Queue: ";
        for(int i = rear; i > front; i--){
            cout << arr[i] << "->";
        }
        cout << arr[front] << endl;
    }
    void full_print(){
        // Prints everything about the queue
        cout << "All values for a queue:" << endl;
        cout << "Capacity: " << max_size() << ", size: " << size() << endl;
        cout << std::boolalpha << "Empty: " << isEmpty() << ", Full: " << isFull() << std::noboolalpha << endl;
        print();
    }
    int peek_front() const{
        // Returns the front element otherwise returns default value of front
        if(!isEmpty()){
            return arr[front];
        }
        return -1;
    }
    int peek_back() const{
        // Returns the rear element otherwise returns default value of rear
        if(!isEmpty()){
            return arr[rear];
        }
        return -1;
    }
    bool isFull() const{
        // If the rear == front then it's full
        if(count == capacity){
            return true;
        }
        return false;
    }
    bool isEmpty() const{
        // If the count is 0 then it's empty
        if(count == 0){
            return true;
        }
        return false;
    }
    int size() const{
        // Returns the size of the array
        return count;
    }
    int max_size() const{
        // Returns the capacity of the array
        return capacity;
    }
    void fill(){
        if(isFull()){
            cout << "Queue is full" << endl;
            return;
        }
        // Fills the queue with 0
        const int remainingSpace = capacity - count;
        for(int i = 0; i < remainingSpace; i++){
            enqueue(0);
        }
    }
    void fill(const int element){
        if(isFull()){
            cout << "Queue is full" << endl;
            return;
        }
        // Fills the array with a specified element
        const int remainingSpace = capacity - count;
        for(int i = 0; i < remainingSpace; i++){
            enqueue(element);
        }
    }
    void fill(const int element, const int len){
        if(isFull()){
            cout << "Queue is full" << endl;
            return;
        }
        // Fills the array with a specified element up to a certain length
        const int remainingSpace = capacity - count;
        if(remainingSpace < len){
            cout << "Cannot fill up to that length" << endl;
            return;
        }
        for(int i = 0; i < len; i++){
            enqueue(element);
        }
        return;
    }
    void clear(){
        // Empties the queue
        if(isEmpty()){
            return;
        }
        while(count != 0){
            dequeue();
        }
    }
};

int main(){
    Queue queue(10);    

    for(int i = 0; i < 6; i++){
        queue.enqueue(i*i);
    }
    queue.enqueue(7438);
    queue.fill(5, 2);
    queue.full_print();

    return 0;
}