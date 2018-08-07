## [参考链接](http://blog.csdn.net/wxz3wxz/article/details/70237302)

使用树莓派编译程序的时候，我遇到了程序比较大，编译到某个文件的时候树莓派会死机，关机之后重启可以继续使用，但是编译到同一个地方树莓派又死机的问题。

这个问题出现的主要原因是我给树莓派安装的Ubuntu mate 16.04 系统默认设置的swap交换空间不够，而编译某些文件的时候需要较大的交换空间，树莓派的交换空间被用满所以树莓派看起来好像是死机了的样子。

解决方法，扩展Ubuntu的交换空间。

- 第一步：确保系统中有足够的空间来用做swap交换空间，我准备在一个独立的文件系统中添加一个swap交换文件，在/opt/image中添加2G的swap交换文件
> sudo mkdir image  
sudo touch swap

- 第二步：添加交换文件并设置其大小为2G，使用如下命令
> sudo dd if=/dev/zero of=/opt/image/swap bs=1024 count=2048000

 过段时间就返回如下结果：
2048000+0 records in
2048000+0 records out
2097152000 bytes (2.1 GB, 2.0 GiB) copied, 242.095 s, 8.7 MB/s

 ###  注意: 这个步骤说的好像很快的样子，但是给我等的都有点怀疑人生了，我一度以为又死机了，重启了2次，最后耐下心来等了几分钟，终于成功了，眼泪都要掉下来了。

- 第三步：创建（设置）交换空间，使用命令mkswap
> sudo mkswap /opt/image/swap  

 Setting up swapspace version 1, size = 2 GiB (2097147904 bytes)

- 第四步：检查现有的交换空间大小，使用命令free
> free -m

 total        used        free      shared  buff/cache   available

 Mem:            925         185          28          14         711         660

 Swap:             0           0           0

- 第五步：启动新增加的2G的交换空间，使用命令swapon
> sudo swapon /opt/image/swap

- 第六步:确认新增加的2G交换空间已经生效，使用命令free
> free -m

 total        used        free      shared  buff/cache   available

 Mem:            925         328          56          32         541         502

 Swap:          1999           0        1999

- 第七步：修改/etc/fstab文件，使得新加的2G交换空间在系统重新启动后自动生效
> sudo vim /etc/fstab  

 在文件最后加入：
> /opt/image/swap    /swap    swap    defaults 0 0

- 重启之后再次编译，YES，成功！！
