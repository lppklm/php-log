# php-log
基于glog的php日志扩展

依赖

phpcpp
1.git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git
2.make && make install

glog
1.git clone https://github.com/google/glog.git
2../autogen.sh && ./configure && make && make install
期间可能会遇到各种报错 这时候是缺少某些必要依赖  自行google即可
我这边安装的有 automake 、 yum install libtool*


glog源码修改

1.glog会在记error日志的时候 往warn和info日志里面也写一份 所以如果warn、info、error都记到同一个文件时会产生两个创建文件错误  同理记warn的时候会产生一个创建文件错误。
这时候需要将报错的那段给注释掉
2.glog产生的文件名字 是类似log_20190930-020518.24465  即前缀(可手动设置)+年月日+时分秒+pid的形式 可修改代码改成 xxx.log
3.glog在往文件里写入数据的开始 会产生一个文件头  可以修改代码将其注释掉
4.glog生成的日志数据会带有xxx.cpp xxx line的字样  也可以将其注释掉
所有代码修改的diff 在glog_diff文件中 
