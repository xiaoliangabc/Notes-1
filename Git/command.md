### 添加所有改变的文件。(注:-A后还有一个句点)
> git add -A .

### 添加所有内容
> git add -A

### 添加新文件和编辑过的文件不包括删除的文件
> git add . 

### 表示添加编辑或者删除的文件，不包括新添加的文件
> git add -u 

### 新建一个分支并跳到该分支上
> git checkout -b new_local_branch_name = git branch new_local_branch_name git + checkout new_branch_name

### 查看当前本地分支
> git branch

### 查看当前远程分支
> git remote

### 查看当前远程分支的详细信息
> git remote -v

### 添加一个新的远程仓库,可以指定一个简单的名字,以便将来引用
> git remote add new_remote_branch_name git://github.com/xxxx/xxx.git


### OpenRE正确工作方式
> git clone https://github.com/HANDS-FREE/OpenRE.git
- fork一下OpenRE源码到自己仓库，然后到上一步clone的代码目录下，添加远程仓库到自己fork的仓库中
> git remote add luyifan_origin git@github.com:XwLu/OpenRE.git
- 跳到主分支
> git checkout master
- 看一下远程分支是不是origin和luyifan_origin
> git remote
- 保持本地项目代码和原始代码一致
> git pull origin
- 修改，提交，push到自己的远程仓库
> git push luyifan_origin master
- 发出pull request

### 合作开发：
- 查看所有远程仓库
> git remote -v
- 关联马文科的源仓库
> git remote add mawenke https://…… 
- 首先fetch一份原仓库变动到本地，这会生成一个分支 mawenke/master
> git fetch mawenke
- 可以查看所有分支
> git branch
- 切换到本地master分支
> git checkout master
- 合并 mawenke/master和master分支
> git merge mawenke/master
- 到这里就把源仓库更新到了本地仓库
- 最后更新副本仓库
> git push origin master
