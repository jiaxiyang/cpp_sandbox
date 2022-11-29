## Introduction

使用 cmake 一键将详细的版本信息注入到动态库或可执行程序中, 极大简化了版本管理。

### 痛点

工程编译出来的动态库或可执行程序未带版本信息，调试和测试出问题很难复现和回溯; 手动记录版本则耗时耗力，也容易出错。

### 解决方案

1. 使用 cmake 自动获取编译环境各种信息，生成配置文件
2. 根据配置文件和 C 文件模板生成 C 源码（有一个返回信息的函数）
3. 编译 C 源码并链接到各动态库或可执行程序中
4. 动态库：提供 version tool 工具使用用 dlopn 打开动态库，输出版本信息。
5. 可执行程序：运行时调用 C 函数输出版本信息

## Quick start

1. 将 cmake 文件夹中的`CPM.cmake`和`get_pg_cpm_functions.cmake`复制到目标工程的 cmake 文件夹中
2. CMakeLists.txt 中添加`include(cmake/get_pg_cpm_functions.cmake)`
3. 为动态库或可执行程序添加`pg_target_add_version(${target_name})`语句，其中 target_name 为动态库或可执行程序名称
4. 工程编译安装完成后，会在安装路径 bin 目录下生成`version_tool`工具。使用`version_tool`查看动态库版本信息。`version_tool -h`可以查看使用说明:

```shell
Usage:
        1. Check share libraries version
                ./version_tool so1 so2 ...

        2. Check linked share libraries version of elf
                ldd elf | grep "=> ." | awk '{print $3}' | xargs ./version_tool
```

5. 对可执行程序，可以在程序运行时打印版本信息。参考代码如：

```c++
#include <iostream>

extern "C" const char *pg_version_verbose();

int main(int argc, char *argv[]) {
  std::cout << pg_version_verbose() << std::endl;
}
```

## Examples

1. 在本工程下运行`bash -ex run.sh`。输出:

```shell
+ ./build/version_tool build/libversion.so
********************* ./build/version_tool *********************
	PROJECT_NAME: version
	TARGET_NAME:  version_tool
	BUILD_USER:   xiyang.jia
	GIT_VERSION:  25c23de
	BUILT_TYPE:   Release
	BUILT_TIME:   2022-11-24 14:46:35 [LOCAL]
	CXX:          /usr/bin/c++  GNU 9.3.0
	CXX_FLAG:
	CXX_RELEASE:  -O3 -DNDEBUG
	CXX_DEBUG:    -g
	ELF_ARCH:     x86_64-linux-gnu
	HOST:         e82da6797232 Linux-3.10.0-957.el7.x86_64
	HOST_CPU:     16 core AMD Ryzen Threadripper 2950X 16-Core Processor

********************* build/libversion.so *********************
	PROJECT_NAME: version
	TARGET_NAME:  version
	BUILD_USER:   xiyang.jia
	GIT_VERSION:  25c23de
	BUILT_TYPE:   Release
	BUILT_TIME:   2022-11-24 14:46:35 [LOCAL]
	CXX:          /usr/bin/c++  GNU 9.3.0
	CXX_FLAG:
	CXX_RELEASE:  -O3 -DNDEBUG
	CXX_DEBUG:    -g
	ELF_ARCH:     x86_64-linux-gnu
	HOST:         e82da6797232 Linux-3.10.0-957.el7.x86_64
	HOST_CPU:     16 core AMD Ryzen Threadripper 2950X 16-Core Processor

+ ./build/version_example
	PROJECT_NAME: version
	TARGET_NAME:  version_example
	BUILD_USER:   xiyang.jia
	GIT_VERSION:  25c23de
	BUILT_TYPE:   Release
	BUILT_TIME:   2022-11-24 14:46:35 [LOCAL]
	CXX:          /usr/bin/c++  GNU 9.3.0
	CXX_FLAG:
	CXX_RELEASE:  -O3 -DNDEBUG
	CXX_DEBUG:    -g
	ELF_ARCH:     x86_64-linux-gnu
	HOST:         e82da6797232 Linux-3.10.0-957.el7.x86_64
	HOST_CPU:     16 core AMD Ryzen Threadripper 2950X 16-Core Pro
```

2. pg_percept_sdk 和 pgpredict 工程实际测试

```shell
+ ./version_tool output/lib/libphpc.so output/lib/libtensorrt_predict.so
********************* ./version_tool *********************
	PROJECT_NAME: pg_percept_sdk
	TARGET_NAME:  version_tool
	BUILD_USER:   nvidia
	GIT_VERSION:  xavier_v2.18-0-g637197f-dirty
	BUILT_TYPE:   Release
	BUILT_TIME:   2022-11-24 12:14:59 [LOCAL]
	CXX:          /usr/bin/c++  GNU 7.5.0
	CXX_FLAG:
	CXX_RELEASE:  -O3 -DNDEBUG
	CXX_DEBUG:    -g
	ELF_ARCH:     aarch64-linux-gnu
	HOST:         nvidia-desktop Linux-4.9.253-tegra
	HOST_CPU:     1 core ARMv8 Processor rev 0 (v8l)

********************* output/lib/libphpc.so *********************
	PROJECT_NAME: pg_percept_sdk
	TARGET_NAME:  phpc
	BUILD_USER:   nvidia
	GIT_VERSION:  xavier_v2.18-0-g637197f-dirty
	BUILT_TYPE:   Release
	BUILT_TIME:   2022-11-24 12:15:04 [LOCAL]
	CXX:          /usr/bin/c++  GNU 7.5.0
	CXX_FLAG:      -fPIC
	CXX_RELEASE:  -O3 -DNDEBUG
	CXX_DEBUG:    -g
	ELF_ARCH:     aarch64-linux-gnu
	HOST:         nvidia-desktop Linux-4.9.253-tegra
	HOST_CPU:     1 core ARMv8 Processor rev 0 (v8l)

********************* output/lib/libtensorrt_predict.so *********************
	PROJECT_NAME: pgpredict
	TARGET_NAME:  tensorrt_predict
	BUILD_USER:   nvidia
	GIT_VERSION:  v0.7.3-1-g3672d51
	BUILT_TYPE:   Release
	BUILT_TIME:   2022-11-24 12:15:15 [LOCAL]
	CXX:          /usr/bin/c++  GNU 7.5.0
	CXX_FLAG:
	CXX_RELEASE:  -fPIC -O2 -Wall
	CXX_DEBUG:    -fPIC -O0 -g -Wall
	ELF_ARCH:     aarch64-linux-gnu
	HOST:         nvidia-desktop Linux-4.9.253-tegra
	HOST_CPU:     1 core ARMv8 Processor rev 0 (v8l)
```

## NOTE

1. **动态库中的 pg_version_verbose 符号要暴露出来, 否则 dlopen 打开动态库找不到 pg_version_verbose 定义**
1. 测试时，GIT_VERSION 信息不要带 dirty, 带 dirty 的不能回溯
1. 测试时，BUILD_TYPE 需要为 Release
1. `strings so | elf` 也能看到版本信息

## TODO

1. 使用注册机制来管理版本信息，生成代码在加载时自动注册信息到 map 中, 提供 c 函数打印结果。
1. 静态库版本管理
   - 思路：提供一个能够传参的 cmake 函数，将 target 名字作为参数来生成 c 函数，供可执行程序中调用。
