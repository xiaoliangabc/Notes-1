## tmux工作方式
- ### tmux最上级的组织是session,操作如下:
	tmux new-session -d -s S -n W1 #构建一个叫S的会话且默认窗口名为W1,S:0或者S:W1都可以访问到该窗口,-d代表在后台运行,不加就会直接在终端显示
	tmux detach #退出当前会话,依然在后台运行
	tmux ls #列出所有会话i
	tmux kill-session -t S #杀掉一个叫S的会话
- ### 第二层组织是windows,构建方式如下:
	tmux new-window -t S:1 -n W2 #在S会话下,新建一个窗口S:1,重命名为W2,访问的时候S:1和S:W2都可以访问到该窗口
	tmux select-window -t S:0 #选中第一个窗口
	tmux select-window -t S:W1 #效果同上
- ### 第三层组织是plane,操作方式如下:
	tmux selectp -t 0 #选中当前窗口下的第0个plane
	tmux splitw -h -p 50 #从当前plane(编号0)向右按照50:50的比例分裂出新的planei(编号1)
	tmux selectp -t 0 #选中当前窗口下的第0个plane
	tmux splitw -v -p 50 #从当前plane向下按照50:50的比例分裂出新的plane(编号1,原先的编号1-->2)
	
	tmux selectp -t 1 #选中第一个plane
	tmux send-keys -t "roscore" C-m #在当前选中的plane运行roscore命令
> 
## 基本命令(如果个性化配置后,crtl+b要根据自己的配置修改)
- Ctrl+b " — 水平分割标签
- Ctrl+b % — 竖直分割标签
- Ctrl+b 方向键 — 选择标签
- 按住 Ctrl+b不放，并且按方向键 — 调整标签大小
- Ctrl+b c — 创建 (c)reate 一个新窗口
- Ctrl+b n — 转到下一个 (n)ext 窗口
- Ctrl+b p — 转到之前的 (p)revious 窗口
-----

## tmux 自启动
> vim .bashrc
	if [ $TERM != "screen-256color" ] && [  $TERM != "screen" ]; then
	    tmux attach || tmux new; exit
	fi 

## 改造tmux
	cd ~
	vim .tmux.conf
### 1.更改前缀(ctrl+b -> ctrl+a)
	unbind C-b
	set -g prefix C-a
### 2.Alt+方向键选择标签
	bind -n M-Left select-pane -L
	bind -n M-Right select-pane -R
	bind -n M-Up select-pane -U
	bind -n M-Down select-pane -D

### 3.活动监听
- 如果你开了多个窗口，可能想当别的窗口发生什么的时候你能收到通知。粘贴这段命令：
	setw -g monitor-activity on
	set -g visual-activity on

### 4.用指定的颜色高亮显示当前窗口
	set-window-option -g window-status-current-bg yellowsetw -g monitor-activity on
------

## 脚本编写demo:
	tmux new-session -d -s S -n W1
	tmux new-window -t S:1 -n W2
	tmux select-window -t S:W1
	tmux selectp -t 0
	tmux splitw -h -p 50 
	tmux selectp -t 0
	tmux splitw -v -p 50

	tmux selectp -t 0
	tmux send-keys "roscore" C-m
