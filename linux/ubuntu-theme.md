- 如果你也希望加入到 Arc GTK 主题这一流行趋势的行列之中，可以直接在 Ubuntu 16.04 LTS 的「终端」中使用如下命令先行添加 Arc GTK theme 源之后进行安装：
> sudo sh -c "echo 'deb http://download.opensuse.org/repositories/home:/Horst3180/xUbuntu_16.04/ /' >> /etc/apt/sources.list.d/arc-theme.list"

- 要让 Arc GTK 主题源难免正常工作并定期收到主题更新，还需要安装在终端中执行如下命令安装软件源的密钥，不然无法正常使用：
> wget http://download.opensuse.org/repositories/home:Horst3180/xUbuntu_16.04/Release.key
> sudo apt-key add - < Release.key

- 上面第一行代码会自动下载 Arc GTK theme repository key，第二行代码会导入并启用软件 repo，当系统提示「OK」时表示已经导入成功，此时使用如下命令便可开始安装Arc GTK 主题：
> sudo apt update
> sudo apt install arc-theme

- 安装gnome-tweak-tool用于切换主题：
> sudo apt-get install gnome-tweak-tool

- 运行gnome-tweak-tool选择Arc-Dark为GTK+主题
- 后续看：http://tieba.baidu.com/p/4718551318
- 运行ccsm
