### 查看版本信息
> cat /etc/issue

### alias终端宏定义(.bashrc)
alias ssh_pcduino='ssh linaro@192.168.1.241'

### 查看USB口的使用
dmesg | grep usb*

### 给USB口附权限
sudo chmod +777 /dev/ttyUSB0

### 在当前路径下寻找相关目标
grep -r xxx ./
