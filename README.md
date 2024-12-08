# 如何使用

```shell
# 安装 brpc 依赖，参考 https://github.com/apache/brpc/blob/master/docs/cn/getting_started.md

sudo apt-get install -y git g++ make libssl-dev libgflags-dev libprotobuf-dev libprotoc-dev protobuf-compiler libleveldb-dev

# 克隆项目

git clone --recurse-submodules https://github.com/youarefree123/learning_brpc.git
cd learning_brpc

# 编译
## 使用脚本, 编译产出都在build文件夹中

sh build.sh build 

# 或者手动编译

mkdir build && cd build
cmake ..
cmake --build . -j6

```

# 参考
