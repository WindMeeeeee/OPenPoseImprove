#### Tools
- OpenPose
- C++
- windows 10

---
##  简介

此项目主要依赖于CMU的项目OpenPose，目的是使用一个RBG摄像头来捕捉人体在空间中的关节点信息。  

---
## 工作
本工程是在范例工程11_asynchronous_custom_output基础上改编的，思想是通过后期的Bone Binding来实现人物朝向判定。  

---

## 效果
![ubc3v](./res/1.gif)
-  此效果是初期测试，因为使用广角摄像头，使得图像发生畸变（已解决）。 
-   

---
#### 项目使用
- 先下载OpenPose项目，并将案例跑通，windows下安装过程较为坎坷，建议多收集信息
- 将我的工程下11_asynchronous_custom_output.cpp;LocalKAT.h;LocalKAT.cpp加入到工程应用中，代替原项目中的文件。
- 接入摄像头，运行项目。
  
---
持续更新中
