# Simple Netstat Implementation

- Student ID: 108062613
- Name: 楊宗翰

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

- run with option and regex string filter
```
sudo ./hw-netstat --udp d.*q
```


**If you run without sudo, some pid/program name won't show**
```
./hw-netstat
```