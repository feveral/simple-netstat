# Simple Netstat Implementation

This is a simple implementation of Linux `netstat -nap` command using pure C.



### Simple Usage Example
```
sudo ./simple-netstat
List of TCP connections:
Proto Local Address           Foreign Address         PID/Program name and arguments
tcp   127.0.0.1:3306          0.0.0.0:0               1283/mysqld
tcp   0.0.0.0:57621           0.0.0.0:0               5737/spotify
tcp   127.0.1.1:53            0.0.0.0:0               1550/dnsmasq --no-resolv --keep-in-foreground --no-hosts --bind-interfaces --pid-file=/var/run/NetworkManager/dnsmasq.pid -
tcp   0.0.0.0:57622           0.0.0.0:0               5373/spotify
tcp   0.0.0.0:22              0.0.0.0:0               1280/sshd -D
tcp   127.0.0.1:631           0.0.0.0:0               4475/cupsd -l
tcp   0.0.0.0:46171           0.0.0.0:0               5737/spotify
tcp   140.114.234.148:43376   104.199.241.251:4070    5373/spotify
tcp6  :::22                   :::0                    1280/sshd -D
tcp6  ::1:631                 :::0                    4475/cupsd -l

List of UDP connections:
Proto Local Address           Foreign Address         PID/Program name and arguments
udp   0.0.0.0:38006           0.0.0.0:0               1088/avahi-daemon: running [feveral-X555LB.local]
udp   224.0.0.251:5353        0.0.0.0:0               2914/chrome --type=utility --field-trial-handle=4925825803119342673,1834046040889519585,131072 --lang=zh-TW --serv
udp   224.0.0.251:5353        0.0.0.0:0               2869/chrome
udp   0.0.0.0:5353            0.0.0.0:0               1088/avahi-daemon: running [feveral-X555LB.local]
udp   127.0.1.1:53            0.0.0.0:0               1550/dnsmasq --no-resolv --keep-in-foreground --no-hosts --bind-interfaces --pid-file=/var/run/NetworkManager/dnsmasq.pid -
udp   0.0.0.0:57621           0.0.0.0:0               5737/spotify
udp   0.0.0.0:57621           0.0.0.0:0               5373/spotify
udp   0.0.0.0:49655           0.0.0.0:0               1550/dnsmasq --no-resolv --keep-in-foreground --no-hosts --bind-interfaces --pid-file=/var/run/NetworkManager/dnsmasq.pid -
udp   0.0.0.0:631             0.0.0.0:0               4476/cups-browsed
udp   0.0.0.0:42037           0.0.0.0:0               5373/spotify
udp6  :::5353                 :::0                    1088/avahi-daemon: running [feveral-X555LB.local]
udp6  :::57638                :::0                    1088/avahi-daemon: running [feveral-X555LB.local]
```


### Build & Run

- build
```
make
```

- clean
```
make clean
```

- run without any option
```
sudo ./hw-netstat
```

- run with option
```
sudo ./hw-netstat --tcp
```

- run with option and string filter(support regex expression)
```
sudo ./hw-netstat --udp ptt.cc
sudo ./hw-netstat --udp p.*c
```


**If you run without sudo, some pid/program name won't show**
```
./hw-netstat
```
