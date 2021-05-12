#include <iostream>
#include <fstream>
#include<memory.h>

void ShowUsage()
{
    std::cout << "Usage for encryption" << std::endl;
    std::cout << "path_pt" << std::endl;//模型路径
    std::cout << "path_save_encryption" << std::endl;//保存路径
    //    std::cout << "length" << std::endl;
    std::cout << "example:\n ./encryption /data_2/small.pt /data_2/small_en" << std::endl;
}



int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        ShowUsage();
        return -1;
    }
    std::string path_pt = argv[1];
    std::string path_save_jiami = argv[2];

    std::string key = "rfvGY&7b";

    std::filebuf in;
    std::filebuf outbuf;
    outbuf.open(path_save_jiami,std::ios::out);
    if (!in.open(path_pt, std::ios::in)) {
        std::cout << "fail to open model pt" << std::endl;
        std::cout << "please check path: " << path_pt << std::endl;
        return 0;
    }

    FILE *in_file;
    in_file=fopen(path_pt.c_str(),"rb");//以读的方式打开二进制文件
    char ch=fgetc(in_file);

    int i = 0;
    while(!feof(in_file))
    {
        ch = ch^key[i>=key.size()?i=0:i++];
        outbuf.sputc(ch);
        ch=fgetc(in_file);
    }
    outbuf.sputc(ch);
    outbuf.close();

    std::cout<<"success crerate encryption model!" << std::endl;
    std::cout<<"key = "<< key << std::endl;

    return 0;
}
