# QT_chatroom

##本项目主要实现的功能是基于QT的聊天室

1、先通过mysql认证登录（如果需要添加这个功能的话，需要先下载mysql客户端，本人使用的是在阿里云上使用了mysql.8以上版本）（这里的认证包含注册和登录的页面，表单会提交给mysql服务器端，判断索引）

2、成功登录之后，先重新输入用户名，然后就可以注册到同一个聊天界面中了

##build

1、首先打开QtChatRoomServer端，找一个机器运行main函数，可以是云服务器（当然如果不是localhost的话，记得一定要是公网IP，不然访问不到）

2、修改register_mysql中的IP地址（你的服务器端的ip），在代码中已标识

3、运行register_mysql中main函数即可，这里就相当于一个客户端

##可以优化的点

1、mysql索引优化（在超级多的用户下，mysql端如果对索引加上优化会更好）

2、如果在分布式的场景下，可以先考虑对mysql水平分表，再加入链接池，这样可以更快的让用户登录

3、可以在QT界面的美化上下功夫

4、更好的提升并发水平（例如加入nginx负载均衡等）
