 vi /etc/ssh/sshd_config
 modify "delete#" "PermitRootLogin prohibit-password"    "passwordAuthentication yes" 
 /etc/init.d/ssh start
 sudo /usr/sbin/sshd -T 查看错误提示
 