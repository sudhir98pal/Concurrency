/*Suppose you are given the following code:

class FooBar {
  public void foo() {
    for (int i = 0; i < n; i++) {
      print("foo");
    }
  }

  public void bar() {
    for (int i = 0; i < n; i++) {
      print("bar");
    }
  }
}
The same instance of FooBar will be passed to two different threads. Thread A will call foo() while thread B will call bar(). Modify the given program to output "foobar" n times.

 

Example 1:

Input: n = 1
Output: "foobar"
Explanation: There are two threads being fired asynchronously. One of them calls foo(), while the other calls bar(). "foobar" is being output 1 time.
Example 2:

Input: n = 2
Output: "foobarfoobar"
Explanation: "foobar" is being output 2 times.



*/



class FooBar 
{
private:
    int n;

public:
    mutex m;
    condition_variable  c;
        atomic<bool> f;
 
    
    FooBar(int n) 
    {
        this->n = n;
        f=true;
      
    }

    void foo(function<void()> printFoo)
    {
        
        for (int i = 0; i < n; i++)
        {
            
        	// printFoo() outputs "foo". Do not change or remove this line.
            
           unique_lock<mutex> foolock(m);
            
            c.wait(foolock,[this]{return f==true;});
             
                 printFoo();
            f=false;
           c.notify_all();
                
                 
             
         
        	
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++)
        {
          
        	// printBar() outputs "bar". Do not change or remove this line.
            unique_lock<mutex> barlock(m);
            
            c.wait(barlock,[this]{return f==false;});
             
                 printBar();
            f=true;
           c.notify_all();
           
              
            
           
        
            
        }
    }
};
