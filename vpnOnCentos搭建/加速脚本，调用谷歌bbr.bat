yum -y install wget

wget --no-check-certificate https://github.com/teddysun/across/raw/master/bbr.sh

chmod +x bbr.sh

./bbr.sh

reboot 

Ilsmod | grep bbr

出现 tcp_bbr  ...... ok  加速脚本启动了