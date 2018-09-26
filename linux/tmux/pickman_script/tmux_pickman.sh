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
