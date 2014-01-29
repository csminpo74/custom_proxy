#ifndef _CONFIG_H
#define _CONFIG_H

#include <vector>
#include <string>
#include <fstream>
#include "yaml-cpp/yaml.h"

class config {
public:
  config( const std::string file_name );
  std::vector< std::string > get_black_list(); 
  std::string get_file_name() {return config_file_name;}
  void parse();
private:
  std::string config_file_name;
  std::vector< std::string > black_lists;
};

#endif
