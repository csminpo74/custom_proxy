#include "config.hpp"

config::config( const std::string file_name ) 
  : config_file_name(file_name) 
{
}

void config::parse() {
  YAML::Node node = YAML::LoadFile(config_file_name);
  for(YAML::iterator it=node.begin(); it!=node.end(); ++it) {
    black_lists.push_back( it->as<std::string>() );
  }
}
