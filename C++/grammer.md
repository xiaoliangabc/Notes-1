##Others
### pragma once 与 ifndef 
一般情况下用ifndef，两者功能一样，有细微差别。

## const
### 函数声明末尾加const
    class Foo 
    {
    public:
        int Bar(int random_arg) const
        {
            // code
        }
    };
Bar(int )函数声明末尾带有const，表示不允许Bar(int)函数对类Foo中的成员进行修改（mutable成员除外）。

## 继承
- 当在构造函数中调用虚函数时，虚函数表现为该类中虚函数的行为，即父类构造函数调用虚函数，则虚函数为父类中的虚函数；子类构造函数中调用虚函数，则调用的是子类中的虚函数；
- 如果不是在构造函数中调用虚函数，则会首先查看虚函数表，如果有实例实现，则调用实例。比如：父类中有虚函数watchTv，则调用父类中watchTv时，则因为子类实现了watchTv，则调用子类的watchTv。

## 遍历
考虑下面的需求，对vector<int>中的每个元素加1，如何做？

    void add(int& lhs)
    {
        lhs= lhs + 1;
    }
    for_each(intVector.begin(),intVector.end(),add);
    
考虑下面的需求，对vector<int>中的每个元素加一个变量，如何做？

    void add(int& lhs,int rhs)
    {
        lhs= lhs + rhs;
    }
    for_each(intVector.begin(),intVector.end(),boost::bind(add,_1,100));
    
## 容器
### 以下是一些选择容器的基本原则：
- #### 除法你有很好的理由选择其他容器，否则应该使用vector；
- #### 如果你的程序有很多小的元素，且空间的额外开销很重要，则不要使用list或forward_list；
- #### 如果程序要求随机访问元素，应使用vector或deque；
- #### 如果程序要求在容器的中间插入或删除元素，应使用list或forward_list；

### 容器介绍
- list:
  - 头尾都可以操作
  - 插入删除很快,随机访问很慢
- deque:
  - 双端队列，可以高效的在头尾两端插入和删除元素,
  - 双端队列不保证内部的元素是按连续的存储空间存储的，因此，不允许对指针直接做偏移操作来直接访问元素
### 容器操作
erase():删除该成员的同时返回指向下一个成员的指针;
    
    vector<int> A;
    vector<int>::iterator it=A.begin()    
    while(it!=A.end()){
        if(*it == 0){
            it = A.erase(it)
            continue;
        }
    }

## 锁
### 读写锁
#### 通常读写锁需要完成以下功能：
- 当 data 被线程A读取时，其他线程仍可以进行读取却不能写入
- 当 data 被线程A写入时，其他线程既不能读取也不能写入

#### 对应于功能1,2我们可以这样来描述：
- 当线程A获得共享锁时，其他线程仍可以获得共享锁但不能获得独占锁
- 当线程A获得独占锁时，其他线程既不能获得共享锁也不能获得独占锁


    void demo()
    {
        typedef boost::shared_lock<boost::shared_mutex> read_lock;
        typedef boost::unique_lock<boost::shared_mutex> write_lock;
        boost::shared_mutex read_write_mutex;
        int32_t data = 1;
        //线程A,读data
        {
            read_lock rlock(read_write_mutex);
            std::cout << data << std:; endl;
        }
        //线程B,读data
        {
        	read_lock rlock(read_write_mutex);
        	std::cout << data << std:; endl;
        }
        //线程C,写data
        {
        	write_lock rlock(read_write_mutex);
        	data = 2;
        }
    }

注意：上面的锁的作用域就是锁所在的{}


