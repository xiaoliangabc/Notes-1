## 注意：养成个好习惯，在工程中单独制作个srv的功能包
## srv中可以调用msg创建的消息类型
------
### 在包中新建srv文件夹，然后新建一个xxx.srv文件
------
### 接下来两个步骤和msg里的一样，所以新建过msg的话就不需要了
- 修改packgae.xml文件，添加如下两句
	<build_depend>message_generation</build_depend>
	<run_depend>message_runtime</run_depend>

- 修改Cmakelists文件 
	find_package(catkin REQUIRED COMPONENTS
		roscpp
		rospy
		std_msgs
		message_generation)
- 这边最重要的是添加message_generation
- 找到如下代码，并修改，有多少srv文件就添加多少
	add_service_files(
	FILES
	ABC.srv
	)

- 找到如下代码，解开注释
	generate_messages(
	DEPENDENCIES
	std_msgs
	)
- 也是在新建msg的时候就搞定了
------
### 重新编译，并检查
	rossrv show package_name/srv_name
- 输出正常就表示创建成功
