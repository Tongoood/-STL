
//客户端程序不能直接含入<stl_hashtable.h>应该含有用到hashtable的容器头文件
//例如<hash_set.h>或者<hash_map.h>
#include <iostream>
#include <unordered_map>

int main() {
    // 创建一个 hashtable，存储键值对
    std::unordered_map<std::string, int> myHashtable;

    // 插入键值对
    myHashtable["Alice"] = 25;
    myHashtable["Bob"] = 30;
    myHashtable["Charlie"] = 35;

    // 查找值
    std::cout << "Age of Alice: " << myHashtable["Alice"] << std::endl;
    std::cout << "Age of Bob: " << myHashtable["Bob"] << std::endl;

    // 检查键是否存在
    if (myHashtable.find("David") == myHashtable.end()) {
        std::cout << "David is not in the hashtable." << std::endl;
    }

    // 遍历 hashtable
    for (const auto& pair : myHashtable) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    std::cout << myHashtable.size() << std::endl;
    std::cout << myHashtable.bucket_count() << std::endl;
    std::cout << myHashtable.max_bucket_count() << std::endl;



    return 0;
}
