#include<iostream>
#include <memory>
#include <fstream>
int main(int argc, char *argv[]){
  std::ifstream config_file("pq_index.json");
  std::istreambuf_iterator<char> is_iter(config_file);
  std::string config_contents(is_iter, std::istreambuf_iterator<char>());
  std::cout<<config_contents<<std::endl;
//   Keson::Value config_keson = Keson::Parse(config_contents);
//   if (!config_keson.IsValid()) {
//     kestrel_log(KESTREL_ERROR, "failed to parsing the config json\n");
//     exit(EXIT_FAILURE);
//   }
  config_file.close();

  return -1;
}