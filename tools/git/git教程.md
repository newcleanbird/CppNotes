# git教程

## git安装

### 官网

[git官网](https://git-scm.com/download/win/)

### 检查

1. 打开控制面板（win+R 输入cmd），查看Git版本信息

   ```shell
   // 查看命令
   git --version
   ```

2. 查看仓库状态，并给予帮助提醒

   ```shell
   git status
   ```

## git配置

优先级：--local > --global > --system
用了--global这个参数，表示你这台机器上所有的Git仓库都会使用这个配置

### 配置用户名和邮箱

```cpp
git config --global user.name         # 查看
git config --global user.name 用户名  # 修改
git config --global user.email        # 查看
git config --global user.email 邮箱   # 修改

git config --global -l # 查看用户名和邮箱
```

任意位置右键点击 git bash 跳出界面后输入

### 配置SSH

1、打开git bash。
2、使用cd ~/.ssh可以查看是否已配置SSH。
3、执行生成公钥和私钥的命令ssh-keygen -t rsa 并按回车3下（为什么按三下，是因为有提示你是否需要设置密码，如果设置了每次使用Git都会用到密码，一般都是直接不写为空，直接回车就好了）。会在一个文件夹里面生成一个私钥 id_rsa和一个公钥id_rsa.pub。（可执行start ~命令，生成的公私钥在 .ssh的文件夹里面）。
4、.ssh如果不做特殊处理的话，一般是在C:\Users\Administrator目录下。如果看不到.ssh文件，可以使用ls -ah指令查看隐藏文件夹即可，这是存放秘钥的文件，打开这个文件会看到id_rsa和id_rsa.pub。id_rsa是私钥文件，id_rsa.pub是公钥文件。
5、执行查看公钥的命令cat ~/.ssh/id_rsa.pub 。

### 添加公钥至 github

将每台电脑的公钥添加到GitHub账户：

登录到你的GitHub账户。
进入设置(Settings) > SSH and GPG keys。
点击New SSH key或Add SSH key按钮。
给密钥起一个识别名称（比如Work Laptop或Home Desktop）。
将每台电脑生成的公钥（.pub文件中的内容）复制粘贴到Key文本框中，然后添加。

## 代理

1. 设置代理

   ```shell
   git config --global http.proxy  'http://127.0.0.1:9083' 
   git config --global https.proxy 'http://127.0.0.1:9083'
   ```

2. 取消代理

   ```shell
   git config --global --unset http.proxy
   git config --global --unset https.proxy
   ```

3. 查看代理

   ```shell
   git config --global --get http.proxy
   git config --global --get https.proxy
   ```

4. 拓展知识

   ```shell
   git helper -a // 查看全部git子命令
   ```

## 仓库

### 创建git仓库

```sh
git init 仓库名  #创建一个git仓库
git init        #将一个项目转化为使用git管理（创建.git目录）
```

目录结构：

   ```s
   project
      |------.git
               |--------branches
               |--------config        #仓库的配置文件
               |--------description
               |--------HEAD
               |--------hooks
               |--------info
               |--------objects
               |--------refs
   隐藏目录.git不算工作区，而是Git的版本库            
   ```

### 查看仓库状态

git status

### 远程仓库

最早，肯定只有一台机器有一个原始版本库，此后，别的机器可以“克隆”这个原始版本库，而且每台机器的版本库其实都是一样的，并没有主次之分
实际情况往往是这样，找一台电脑充当服务器的角色，每天24小时开机，其他每个人都从这个“服务器”仓库克隆一份到自己的电脑上，并且各自把各自的提交推送到服务器仓库里，也从服务器仓库中拉取别人的提交
GitHub就是提供Git仓库托管服务的，所以，只要注册一个GitHub账号，就可以免费获得Git远程仓库，即Github为我们的git仓库提供了一个远程仓库，有了这个远程仓库，妈妈再也不用担心我的硬盘了

1. 为本地与GitHub的通信配置ssh
**本地git仓库和GitHub上的远程仓库之间的传输是通过SSH加密的，所以，需要一点设置**：

   * 创建`ssh key`： `bash  ssh-keygen -t rsa -C "youremail@example.com"`
   * 登录你的GitHub帐号，`Settings -> SSH and GPG keys -> new SSH key` ，将`id_rsa.pub`的内容复制进去

   为什么GitHub需要SSH Key呢？因为GitHub需要识别出你推送的提交确实是你推送的，而不是别人冒充的，而Git支持SSH协议，所以，GitHub只要知道了你的公钥，就可以确认只有你自己才能推送

2. 让本地git仓库和远程仓库同步
在有了本地git仓库后，还需创建对应的远程仓库
   * 在GitHub上创建远程仓库（如果已有则省略）
   * 为本地仓库设置远程仓库信息（如果同时需要为本地仓库添加多个远程仓库（如果github+码云），则可以将origin分别换成github和gitee，推送操作时也要修改origin。添加后，远程库的名字就是origin，这是Git默认的叫法，也可以改成别的，但是origin这个名字一看就知道是远程库） `bash  git remote add origin https://github.com/用户名/仓库名`
     * **删除本地仓库的远程仓库信息**：git remote remove origin
     * **修改远端地址**：git remote set-url 新地址
     * **查看远程仓库信息**：git remote -v
   * **将本地git仓库push到远程仓库** bash  # 由于远程库是空的，我们第一次推送master分支时，加上了-u参数,Git不但会把本地的  # master分支内容推送的远程新的master分支，还会把本地的master分支和远程的master  # 分支关联起来，在以后的推送或者拉取时就可以简化命令  git push [-u] origin 分支名

3. 选择推送分支
   并不是一定要把本地分支往远程推送。哪些分支需要推送、哪些不需要呢？
   * master(main)：主分支，要时刻与远程同步
   * dev：开发分支，团队所有成员都需要在上面工作，所有也需要与远程同步
   * bug：只用于在本地修复bug，就没必要推送到远程了，除非老板要看看你每周修复了几个bug

### 协同工作

1. 拉取分支：
`git pull`
git clone时，默认情况下只能看到本地的master分支。如果要在dev分支上开发，就必须创建远程origin的dev分支到本地，可以使用如下命令创建本地dev分支：
`git checkout -b dev`

2. 将本地dev分支与远程origin/dev分支关联起来：
`git branch --set-upstream dev origin/dev`

### 使用GitHub

Bootstrap的官方仓库twbs/bootstrap、你在GitHub上克隆的仓库my/bootstrap，以及你自己克隆到本地电脑的仓库，他们的关系就像下图显示的那样：

如果你想修复bootstrap的一个bug，或者新增一个功能，立刻就可以开始干活，干完后，往自己的仓库推送

如果你希望bootstrap的官方库能接受你的修改，你就可以在GitHub上发起一个pull request。当然，对方是否接受你的pull request就不一定了

## 版本控制

隐藏目录.git不算工作区，而是Git的版本库。版本库里存了很多东西，其中最重要的就是**称为stage（或者叫index）的暂存区**。还有Git为我们自动创建的第一个分支master，以及指向master的一个指针叫HEAD

### 添加或删除修改

* 将修改添加到暂存区：
* `git add 文件/目录`

* 从暂存区删除修改：
* `git rm --cached 文件/目录`

* 以下命令可以将暂存区的修改重置，暂存区的改变会被移除到工作区：
* `git reset HEAD [文件名]`

* 以下命令可以丢弃工作区的修改：
* `git checkout -- [文件名]`

如果刚对一个文件进行了编辑，可以撤销文件的改变，回到编辑开始。命令其实起到“一键恢复”的作用，还可用于“误删恢复”。可以在 git reset HEAD [文件名] 后使用

### 提交版本

如果修改了`readme.txt`，添加了文件`LICENSE`，并将2者添加到暂存区后，暂存区的状态就变成这样：

使用commit提交修改，实际上就是把暂存区的所有内容提交到当前分支：
`git commit -m '信息'`

commit相当于游戏里面一次存档。对应一个版本

### 文件删除

`rm`做出的删除不会被暂存，`git rm`做出的改变会被暂存。如果使用`rm`删除掉，能使用`git rm`来暂存。`git rm`不在意文件已经不存在了

1. 删除(暂存)单个文件
 git rm

2. 删除(暂存)多个文件（一般情况下，更可能是对大量文件进行管理。可能同时会删除很多文件，不可能使用git rm一个个删除）
   `# 它会变量当前目录，将所有删除暂存`
   `git add -u .`
如果有文件被误删，可以使用`git checkout -- 文件名恢复`

### 工作现场保存与恢复

有时候在修复bug或某项任务还未完成，但是需要紧急处理另外一个问题。此时可以先保存工作现场，当问题处理完成后，再恢复bug或任务的进度

* 保存工作现场：
`git stash`

* 查看保存的工作现场：
`git stash list`

* 恢复工作现场：
`git stash apply`

* 删除stash内容：
`git stash drop`

* 恢复工作现场并删除stash内容（相当于上面2步合并）：
`git stash pop`

### 改动查询

`git diff [选项]           # 查看工作区中的修改`
`git diff [选项] --staged   # 查看已添加到暂存区的修改`
`git diff [选项] HEAD       # 查看当前所有未提交的修改`

选项：
`--color-words： 颜色`
`--stat：        不显示具体修改，只显示修改了的文件`

### 版本回退

`git reset --hard` 版本`ID/HEAD`形式的版本:

`git reset --hard HEAD      # 当前版本`
`git reset --hard HEAD^     # 上一个版本`
`git reset --hard HEAD^^    # 上上个版本`
`git reset --hard HEAD~n    # 前n个版本`

如果回到过去的版本，想要回到原来新的版本：

* 如果终端未关，可以找到新版本的id，通过上述命令回去新版本
* 如果终端已关，git reflog查看版本，再通过上述命令回去新版本

### 查看历史提交

`git log [选项]`

选项：
`--online：只显示提交提示信息`
`--stat：添加每次提交包含的文件信息`
`--path：查看每次提交改变的内容`
`--graph`

加文件名可以显示具体文件相关的所有提交信息

## 分支管理

### 创建与合并分支

每次commit相当于一次存档，对应一个版本。Git都把它们串成一条时间线，这条时间线就是一个分支。master就是主分支。HEAD指向当前分支，而master指向主分支的最近提交。每次提交，master分支都会向前移动一步

当创建一个分支时，如dev，Git创建一个指针dev，指向master相同的提交，再把HEAD指向dev，就表示当前分支在dev上：

从现在开始，对工作区的修改和提交就是针对dev分支了，比如新提交一次后，dev指针往前移动一步，而master指针不变：

假如我们在dev上的工作完成了，就可以把dev合并到master上。最简单的方法，就是直接把master指向dev的当前提交，就完成了合并：

合并完分支后，甚至可以删除dev分支。删除dev分支就是把dev指针给删掉，删掉后，我们就剩下了一条master分支：

上面的合并使用的是Fast forward。这种模式下，删除分支后，会丢掉分支信息。如果要强制禁用Fast forward模式，Git就会在merge时生成一个新的提交，这样，从分支历史上就可以看出分支信息。通过在git merge命令中使用--no-ff选项禁用Fast forward模式。比如在合并dev时：
`git merge --no-ff -m "merge with no-ff" dev`

由于会生成一个新的提交，所以需要使用-m指明新提交的信息。

相关命令如下：

* (创建分支并)切换到新分支：
`git checkout -b 新分支`

* 创建分支：
`git branch 新分支`

* 切换分支：
`git checkout 欲切换到的分支`

* 查看当前分支：
`git branch`

* 合并某分支到当前分支：
`git merge 欲合并到当前分支的分支`

* 查看历史分支情况：
`git log --graph --pretty=oneline --abbrev-commit`

* 删除未合并的分支：
`git branch -D 分支`

### 分支合并冲突

如果两个分支修改了同一文件，合并时会发生冲突。比如master分支和feature1分支都修改了readme.txt文件，各自都有新的提交：
这种情况下，Git无法执行“快速合并”，只能试图把各自的修改合并起来，但这种合并就可能会有冲突。此时readme.txt文件会变成如下形式：

```sh
Git is a distributed version control system.
Git is free software distributed under the GPL.
Git has a mutable index called stage.
Git tracks changes of files.

<<<<<<< HEAD
Creating a new branch is quick & simple.
=======
Creating a new branch is quick AND simple.
>>>>>>> feature1
```

Git用`<<<<<<<，=======，>>>>>>>`标记出不同分支的内容，此时需要手动修改后保存。然后再使用git commit进行一次提交。

### 分支管理策略

在实际开发中，我们应该按照几个基本原则进行分支管理:

首先，master分支应该是非常稳定的，也就是仅用来发布新版本，平时不能在上面干活
干活都在dev分支上，也就是说，dev分支是不稳定的，到某个时候，比如1.0版本发布时，再把dev分支合并到master上，在master分支发布1.0版本

你和你的小伙伴们每个人都在dev分支上干活，每个人都有自己的分支，时不时地往dev分支上合并就可以了

所以，团队合作的分支看起来就像这样：

当你从远程仓库克隆时，实际上Git自动把本地的master分支和远程的master分支对应起来了，并且，远程仓库的默认名称是origin

要**查看远程库的信息**，用`git remote`：

```sh
$ git remote 
origin
```

或者，用`git remote -v`**显示更详细的信息**：

```sh
$ git remote -v
origin  git@github.com:michaelliao/learngit.git (fetch)
origin  git@github.com:michaelliao/learngit.git (push)
```

上面显示了可以抓取和推送的origin的地址。如果没有推送权限，就看不到push的地址

**推送分支**
git push origin 欲推送的分支

* master分支是主分支，因此要时刻与远程同步
* dev分支是开发分支，团队所有成员都需要在上面工作，所以也需要与远程同步
* bug分支只用于在本地修复bug，就没必要推到远程了，除非老板要看看你每周到底修复了几个bug
* feature分支是否推到远程，取决于你是否和你的小伙伴合作在上面开发

## 开发例子

### 开发流程

使用Git将代码提交到GitHub可以分为以下几个步骤：

1. 步骤一：在GitHub上创建仓库
   1. 首先登录到GitHub账号，并创建一个新的仓库。点击页面右上角的New按钮，填写仓库名称、描述等信息，并选择是否设置为公共或私有仓库。

2. 步骤二：在本地电脑上安装Git
   1. 从[Git官网](https://git-scm.com/)下载适用于你操作系统的Git安装包，并按照指示安装。

3. 步骤三：在本地电脑上配置Git
   1. 打开命令行终端，并通过以下命令设置用户名和邮箱：git config –global user.name “你的用户名”和git config –global user.email “你的邮箱地址”。

4. 步骤四：将github文件拉到本地
   1. `git clone -m <sshlink>`

5. 步骤五：将代码添加到Git仓库
   1. 将你的代码复制到工作目录下。
   2. 使用以下命令将代码添加到Git仓库：git add .
      * 如果只想提交部分文件，可以使用git add命令加上文件路径。
      * `git add <filename>`
      * `git add *`

6. 步骤六：提交代码到本地仓库
   1. 使用以下命令将代码提交到本地仓库：
      git commit -m “提交信息”。
      提交信息应该清晰明了，对本次提交的内容进行简要描述。

7. 步骤七：将本地仓库与GitHub仓库关联
   1. 在GitHub上创建的仓库页面找到“HTTPS”或“SSH”链接，然后使用以下命令将本地仓库与GitHub仓库关联：
      git remote add origin 仓库链接。
      链接格式为：`https://github.com/你的用户名/仓库名称.git`。

8. 步骤八：将本地仓库代码推送到GitHub
   1. 使用以下命令将本地仓库代码推送到GitHub：git push -u origin master。
      这将把你的本地代码推送到GitHub的master分支。

9. 步骤九：验证代码是否成功推送至GitHub
   1. 刷新GitHub仓库页面，你应该能够看到刚刚推送的代码文件。

至此，你已经成功地将代码提交到GitHub。每次想要更新代码时，只需要重复步骤六到步骤九即可。

### 简单提交步骤

```shell
// 将文件切换到暂存的状态
git add <filename> 
// 将所有的文件都暂存
git add * 

// 提交：将暂存的文件提交到仓库中，提交日志"xxxx" 描述功能
git commit -m "xxxx"

// 提交所有未修改 = add * + commit
git commit -a -m "日志记录"
```
