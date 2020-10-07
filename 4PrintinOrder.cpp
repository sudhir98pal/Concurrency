Suppose we have a class:

public class Foo {
  public void first() { print("first"); }
  public void second() { print("second"); }
  public void third() { print("third"); }
}
The same instance of Foo will be passed to three different threads. Thread A will call first(), thread B will call second(), 
and thread C will call third(). Design a mechanism and modify the program to ensure that second() is executed after first(),
and third() is executed after second().

 

Example 1:

Input: [1,2,3]
Output: "firstsecondthird"
Explanation: There are three threads being fired asynchronously. The input [1,2,3] means thread A calls first(), 
thread B calls second(), and thread C calls third(). "firstsecondthird" is the correct output.
Example 2:

Input: [1,3,2]
Output: "firstsecondthird"
Explanation: The input [1,3,2] means thread A calls first(), thread B calls third(), and thread C calls second(). 
"firstsecondthird" is the correct output.
 

Note:

We do not know how the threads will be scheduled in the operating system, even though the numbers in the
input seems to imply the ordering. The input format you see is mainly to ensure our tests' comprehensiveness.

solution 
********************************************
semaphore->(faster than mutex implementation)

#include <semaphore.h>
class Foo {
public:
    sem_t b,c;
    Foo() 
    {
        sem_init(&b, 0, 0);
        sem_init(&c, 0, 0);
    }

    void first(function<void()> printFirst) 
    {

        printFirst();
        sem_post(&b);
    }

    void second(function<void()> printSecond) 
    {
        sem_wait(&b);

        printSecond();
        sem_post(&c);
    }

    void third(function<void()> printThird)
    {
        sem_wait(&c);
        printThird();
    }
};

**********************************
mutex->

class Foo {
public:
    mutex m;
    int count;
    Foo()
    {
        count=1;
    }

    void first(function<void()> printFirst)
    {
        
      m.lock();
        while(count!=1)
        {
            m.unlock();
            m.lock();
             
        }
            printFirst();
            count=2;
        m.unlock();
   
    }

    void second(function<void()> printSecond)
    {
        
       m.lock();
        while(count!=2)
        {
            m.unlock();
            m.lock();
             
        }
            printSecond();
            count=3;
        m.unlock();
      
    }

    void third(function<void()> printThird) 
    {
        
        m.lock();
        while(count!=3)
        {
            m.unlock();
            m.lock();
             
        }
            printThird();
            count=1;
        m.unlock();
    }
};
