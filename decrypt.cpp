#include<iostream>
#include <torch/script.h>
#include <torch/torch.h>
#include <sstream>
#include <cstring>

int load_model(const std::string &model_path, const torch::DeviceType &device_type, int gpu_num,std::string key )
{
    char *buf = nullptr;
    FILE *file = fopen(model_path.c_str(), "r");
    fseek(file, 0, SEEK_END);
    unsigned size = ftell(file);
    fseek(file, 0, SEEK_SET);
    buf = (char *) malloc(size);
    std::memset(buf, 0, size);
    unsigned int i = 0, j = 0;
    while (!feof(file)) {
    char ch = (fgetc(file)) ^(key[i >= key.length() ? i = 0 : i++]);
    buf[j++] = ch;
    }

    std::istringstream ss;
    ss.rdbuf()->pubsetbuf(buf, j - 1);

    torch::jit::script::Module module_;
    try {
    // Deserialize the ScriptModule from a file using torch::jit::load().
        module_ = torch::jit::load(ss);
    }
    catch (const c10::Error &e) {
    std::cerr << "Error loading the model!\n";
    std::exit(EXIT_FAILURE);
    }
    free(buf);
    std::cout << "load model:" << model_path << " successful" << std::endl;
    module_.to(device_type);
    module_.eval();
    std::cout << "gpu_num:" << gpu_num << std::endl;
    return 0;
}
int main(){
    // set device type - CPU/GPU
    torch::DeviceType device_type;
    if (torch::cuda::is_available() ) {
        device_type = torch::kCUDA;
    } else {
        device_type = torch::kCUDA;
    }
    load_model(
            "your model path",
            device_type,
            0,
            "your key"
    );
}
