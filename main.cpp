#include <iostream>
#include <stdexcept>
using std::cout, std::cerr, std::cin, std::endl;

class Queue{
private:
    int* arr;
    int front, rear;
    int capacity, count;
public:
    Queue(){
        front = -1, rear = -1;
        this->capacity = 15;
        count = 0;
    }
    Queue(const Queue& queue){
        front = -1, rear = -1;
        capacity = queue.max_size();
        count = 0;
        for(int i = 0; i < queue.count; i++){
            enqueue(queue.arr[i]);
        }
    }
    ~Queue(){
        delete[] arr;
        arr = nullptr;
    }
    int enqueue(const int element){
        // If the queue is empty
        if(isEmpty()){
            try{
                arr = new int[capacity];
                front = 0, rear = 0;
                arr[front] = element;
                count++;
                return 0;
            }
            catch(std::bad_alloc& e){
                cerr << "Failed to allocate memory for the queue: " << e.what() << endl;
                return -1;
            }
        }
        // If the queue is full
        else if(isFull()){
            try{
                // Creates a new queue with double the capacity
                int* newQueue = new int[capacity*2];
                capacity *= 2;
                
                // Copies the elements of the array to the new queue
                for(int i = 0; i < count; i++){
                    newQueue[i] = arr[i];
                }
                rear = (rear + 1) % capacity;
                arr[rear] = element;
                count++;
                return 0;
            }
            catch(std::bad_alloc& e){
                cerr << "Failed to allocate memory for the queue: " << e.what() << endl;
                return -1;
            }
        }
        else{
            // If the queue has elements inside
            rear = (rear + 1) % capacity;
            arr[rear] = element;
            count++;
            return 0;
        }
    }
    void dequeue(){
        if(isEmpty()){
            cout << "There is nothing in the queue." << endl;
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
            cout << "The queue is empty." << endl;
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
    int peek_random(int index){
        return arr[index];
    }
    bool isFull() const{
        // If the rear == front then it's full
        if(count == capacity && count != 0){
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
            cout << "Queue is full." << endl;
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
            cout << "Queue is full." << endl;
            return;
        }
        // Fills the queue with a specified element
        const int remainingSpace = capacity - count;
        for(int i = 0; i < remainingSpace; i++){
            enqueue(element);
        }
    }
    void fill(const int element, const int len){
        if(isFull()){
            cout << "Queue is full." << endl;
            return;
        }
        // Fills the array with a specified element up to a certain length
        const int remainingSpace = capacity - count;
        if(remainingSpace < len){
            cout << "Cannot fill up to that length." << endl;
            return;
        }
        for(int i = 0; i < len; i++){
            enqueue(element);
        }
        return;
    }
    void copy(Queue queue){
        if(isFull()){
            cout << "Queue is full." << endl;
            return;
        }

        // Fills the queue with the elements of another queue
        for(int i = 0; i < queue.size(); i++){
            enqueue(queue.peek_random(i));
        }
        /*
            This solution cannot use &queue otherwise the elements will get
            deleted and if we dont use the &queue in the parameter we make a
            copy of the queue which wastes memory so I need to find a better solution
            
            while(queue.size() != 0){
            enqueue(queue.peek_front());
            queue.dequeue();
            }
        */
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
    friend void copy(Queue& queue1, Queue& queue2);
};
void copy(Queue& queue1, Queue& queue2){
    if(queue1.isFull()){
        cout << "Queue is full." << endl;
        return;
    }

    // Fills the queue with the elements of another queue
    for(int i = 0; i < queue2.size(); i++){
            queue1.enqueue(queue2.peek_random(i));
    }
    
    /*
        This solution cannot work because it deletes the elements of the queue
        while(queue2.size() != 0){
        queue1.enqueue(queue2.peek_front());
        queue2.dequeue();
    }
    */
}

int main(){
    Queue queue1;    

    cout << "Queue 1:" << endl;
    queue1.fill(6, 5);
    for(int i = 0; i < 5; i++){
        queue1.enqueue(i*i);
    }
    queue1.dequeue();
    queue1.dequeue();
    queue1.fill(3);
    queue1.full_print();

    cout << "\nQueue 2:" << endl;
    Queue queue2;
    copy(queue2, queue1);
    //queue2.copy(queue);
    queue2.full_print();

    return 0;
}