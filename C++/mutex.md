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
