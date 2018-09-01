##Others
### pragma once 与 ifndef 
一般情况下用ifndef，两者功能一样，有细微差别。

### 赋值操作
	int c=(a>b)?b:a

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
    
