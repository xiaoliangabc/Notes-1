# 创建会话和窗口
tmux new-session -d -s tiggo -n panel
tmux select-window -t tiggo:panel
# 先构建pane的布局
tmux selectp -t 0
tmux splitw -h -p 30
tmux selectp -t 0
tmux splitw -v -p 66
tmux selectp -t 0
tmux splitw -h -p 75
tmux selectp -t 1
tmux splitw -h -p 66
tmux selectp -t 2
tmux splitw -h -p 50
tmux selectp -t 4
tmux splitw -v -p 50
tmux selectp -t 4
tmux splitw -h -p 66
tmux selectp -t 5
tmux splitw -h -p 50
tmux selectp -t 7
tmux splitw -h -p 50

# 写指令
# 驱动
tmux selectp -t 0
tmux send-keys "roscore" C-m
tmux selectp -t 1
tmux send-keys "sleep 1;rosparam set use_sim_time true;rosbag play /home/luyifan/ROS_BAG/zizhu/2018-09-27/2018-09-27-16-17-50.bag --clock -r 2.0 -s 0" C-m
tmux selectp -t 2
tmux send-keys "sleep 1;rosrun tf_tiggo tf_tiggo" C-m
# 显示
tmux selectp -t 3
tmux send-keys "sleep 1;rosrun all_map all_map" C-m
# 感知
tmux selectp -t 4
tmux send-keys "sleep 1;roslaunch sensor_pipeline sensor_pipeline_all.launch" C-m
# 控制
tmux selectp -t 5
tmux send-keys "sleep 1;roslaunch speed_controller speed_controller.launch" C-m
tmux selectp -t 6
tmux send-keys "sleep 1;roslaunch steer_controller pure_pursuit.launch" C-m
#规划
tmux selectp -t 7
tmux send-keys "sleep 2;roslaunch global_path_planner global_path_planner_zizhu.launch" C-m
tmux selectp -t 8
tmux send-keys "sleep 2;roslaunch global_path_planner map_exchange_zizhu.launch" C-m
tmux selectp -t 9
tmux send-keys "sleep 2;rosrun statemachine statemachine_node" C-m

# 控制rosbag的播放
tmux selectp -t 1

tmux attach -t tiggo
