# 定义变量
# 系统变量CFLAGS可以控制编译时的编译器参数
CFLAGS += -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE # 如果要使用getline函数的话需要在编译时加上宏_GNU_SOURCE
CC     = gcc $(CFLAGS)



# src = $(wildcard *.c) # $是使用函数的标识，获取当前目录下的所有.c文件
# obj = $(pathsubst %.c, %.o, $(src)) # 将当前目录下的c文件匹配替换成.o文件
# 不知道 make flen然后就能直接生成可执行文件是怎么做到的

# $(target):$(obj) 
#	$(CC) $< -o $@

clean:
	@echo Cleaning up executable files
	rm -f *.out