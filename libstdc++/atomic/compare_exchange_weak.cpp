// atomic::compare_exchange_weak example:
#include <iostream>       // std::cout
#include <atomic>         // std::atomic
#include <thread>         // std::thread
#include <vector>         // std::vector

// a simple global linked list:
struct Node { int value; Node* next; };
std::atomic<Node*> list_head (nullptr);

void append (int val) {     // append an element to the list
  Node* oldHead = list_head;
  Node* newNode = new Node {val,oldHead};

  // what follows is equivalent to: list_head = newNode, but in a thread-safe way:
  // 如果原子变量list_head的值等于oldHead, 则把list_head的值置为newNode; 
  // 否则(说明有别的线程已经更新了list_head), compare_exchange_weak会把oldHead的值设置为list_head的值(即更新过的list_head),
  // 我们则更新newNode->next以指向新的list_head
  while (!list_head.compare_exchange_weak(oldHead,newNode))
    newNode->next = oldHead;
}

int main ()
{
  // spawn 10 threads to fill the linked list:
  std::vector<std::thread> threads;
  for (int i=0; i<10; ++i) threads.push_back(std::thread(append,i));
  for (auto& th : threads) th.join();

  // print contents:
  for (Node* it = list_head; it!=nullptr; it=it->next)
    std::cout << ' ' << it->value;
  std::cout << '\n';

  // cleanup:
  Node* it; while (it=list_head) {list_head=it->next; delete it;}

  return 0;
}

/*
Possible output (the order may be different):
 9 8 7 6 5 4 3 2 1 0
*/
