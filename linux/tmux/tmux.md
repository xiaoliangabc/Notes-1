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
	tmux kill-window -t S:W2 #杀掉S会话的W2窗口
- ### 第三层组织是pane,操作方式如下:
	tmux selectp -t 0 #选中当前窗口下的第0个pane
	tmux splitw -h -p 50 #从当前pane(编号0)向右按照50:50的比例分裂出新的pane(编号1)
	tmux selectp -t 0 #选中当前窗口下的第0个pane
	tmux splitw -v -p 50 #从当前plane向下按照50:50的比例分裂出新的pane(编号1,原先的编号1-->2)
	tmux selectp -t 0 #选中第0个pane
	tmux send-keys -t "roscore" C-m #在当前选中的pane运行roscore命令
	tmux kill-pane -t 2 #杀掉第2个pane

## 基本命令(如果个性化配置后,crtl+b要根据自己的配置修改)
- Ctrl+b " — 水平分割标签
- Ctrl+b % — 竖直分割标签
- Ctrl+b 方向键 — 选择标签
- 按住 Ctrl+b不放，并且按方向键 — 调整标签大小
- Ctrl+b c — 创建 (c)reate 一个新窗口
- Ctrl+b n — 转到下一个 (n)ext 窗口
- Ctrl+b p — 转到之前的 (p)revious 窗口
- ctrl+b & — 杀掉当前窗口
-----

## tmux 自启动(修改.bashrc)
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
	# 创建会话和窗口
	tmux new-session -d -s pickman -n control
	tmux select-window -t pickman:control
	# 先构建pane的布局
	tmux selectp -t 0
	tmux splitw -h -p 50
	tmux selectp -t 0
	tmux splitw -v -p 50
	tmux selectp -t 2
	tmux splitw -v -p 50
	tmux selectp -t 2
	tmux splitw -h -p 50
	
	
	# 再ctrl+x q查看一下pane的编号,往对应编号的pane里写指令
	tmux selectp -t 2
	tmux send-keys "roscore" C-m
	tmux selectp -t 0
	tmux send-keys "sleep 1;rosbag play /home/luyifan/BAG/BUG.bag --clock -s 20 -r 1.0" C-m
	tmux selectp -t 3
	tmux send-keys "sleep 2;rosrun rviz rviz -d /home/luyifan/Project/PathPlanning/pickman_ws/src/rviz/pickman.rviz" C-m
	tmux selectp -t 1
	tmux send-keys "sleep 3;rosrun create_map create_map" C-m
	tmux selectp -t 4
	tmux send-keys "sleep 3;rosrun dstar dstar" C-m
	
	tmux attach -t pickman
### Tips:用脚本来启动tmux和各类指令的时候,需要先-d再attach出来,否则指令不运行
