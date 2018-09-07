## 基本命令
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

## 脚本编写
	selectp -t 0 # 选择第一个标签
	splitw -h -p 50 # 分割成两半

	selectp -t 1 # 选择第二个标签
	splitw -v -p 50 #  分割成两半
	selectp -t 0 # 返回第一个标签
- 值得一提的是这种脚本文件可以做的不仅是打开标签，你也可以在里面预置运行命令，例如：
	splitw -h -p 50 'vim' #分割现在的标签，并同时在新标签里面运行vim
------

## 面板最大化(V1.8之后的版本自带该功能)
- 首先编写一个zoom脚本
	mkdir .tmux
	touch zoom
	vim zoom
- 粘贴如下内容
	#!/bin/bash -f
	currentwindow=`tmux list-window | tr '\t' ' ' | sed -n -e '/(active)/s/^[^:]*: *\([^ ]*\) .*/\1/gp'`;
	currentpane=`tmux list-panes | sed -n -e '/(active)/s/^\([^:]*\):.*/\1/gp'`;
	panecount=`tmux list-panes | wc | sed -e 's/^ *//g' -e 's/ .*$//g'`;
	inzoom=`echo $currentwindow | sed -n -e '/^zoom/p'`;
	if [ $panecount -ne 1 ]; then
	    inzoom="";
	fi
	if [ $inzoom ]; then
	    lastpane=`echo $currentwindow | rev | cut -f 1 -d '@' | rev`;
	    lastwindow=`echo $currentwindow | cut -f 2- -d '@' | rev | cut -f 2- -d '@' | rev`;
	    tmux select-window -t $lastwindow;
	    tmux select-pane -t $lastpane;
	    tmux swap-pane -s $currentwindow;
	    tmux kill-window -t $currentwindow;
	else
	    newwindowname=zoom@$currentwindow@$currentpane;
	    tmux new-window -d -n $newwindowname;
	    tmux swap-pane -s $newwindowname;
	    tmux select-window -t $newwindowname;
	fi
- 绑定一个快捷指令
	unbind z
	bind z run ". ~/.tmux/zoom"



