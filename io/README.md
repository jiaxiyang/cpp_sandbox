## basic

![总体图](https://upload.cppreference.com/mwiki/images/0/06/std-io-complete-inheritance.svg)

1. 总体可分为`file io` 和 `string io`;
1. stream 可分为三类：`istream`, `ostream`和`stream`, 没一类根据 file 和 string 又分为两种，例如`istream`分为`ifstream`和`istringstream`
1. 两个头文件`<fstream>`和 `<sstream>`
1. `std::stringstream`是`std::basic_stringstream<char>`的 typedef

## file

1. 头文件`<fstream>`
1. 在 linux 平台下进行文件读写时，文本模式和二进制模式没有区别。windows:如果以“文本”方式打开文件，当读取文件的时候，系统会将所有的"/r/n"转换成"/n"；当写入文件的时候，系统会将"/n"转换成"/r/n"写入。[link](https://www.cnblogs.com/litaozijin/p/6582048.html)
1. 默认是文本模式打开。
1. 最好加上二进制模式，比较通用`std::ios_base::binary`
1. 读文件

```
CHECK(std::ifstream(file, std::ios_base::binary).read(reinterpret_cast<char*>(&result[0]), file_size).good())
        << "Failed to read baseline from " << file;
```

1. 写文件

```
const auto mode =
      std::ios_base::out | std::ios_base::binary | std::ios_base::trunc;
CHECK(std::ofstream(mc_code_file, mode)
              .write(reinterpret_cast<char*>(&mc_code[0]), mc_code.size())
              .good())
        << " faild to dump code to " << mc_code_file;
```

## string

1. 头文件`<sstream>`
