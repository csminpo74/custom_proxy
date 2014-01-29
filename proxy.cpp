/**
 * @file   proxy.cpp
 * @author Alex Ott <alexott@gmail.com>
 * 
 * @brief  
 * 
 * 
 */

#include "proxy-server.hpp"
#include "config.hpp"
#include "boost/program_options.hpp"

namespace po = boost::program_options;
struct invalid_arguments {};

int main(int argc, char** argv) {
	try {
		int thread_num = 2, port = 10001;
		std::string interface_address;
    
    po::options_description desc("Allowed option");
    desc.add_options()
      ("help", "produce help message")
      ("thread_num", po::value<int>(), "set thread number")
      ("port", po::value<int>(), "set proxy port")
      ("config", po::value<std::string>()->default_value("config.yaml"), "set config file name");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
      std::cout << desc << "\n";
      return 1;
    }

    if (vm.count("thread_num")) {
      std::cout << "thread_num is set to " 
        << vm["thread_num"].as<int>() << ".\n";
      thread_num = vm["thread_num"].as<int>();
    } 
    if (vm.count("port")) {
      port = vm["port"].as<int>();
    }
    
    config *conf = new config(vm["config"].as<std::string>());
    conf->parse();
		ios_deque io_services;
		std::deque< ba::io_service::work> io_service_work;
		
		boost::thread_group thr_grp;
		
		for (int i = 0; i < thread_num; ++i) {
			io_service_ptr ios( new ba::io_service);
			io_services.push_back( ios);
			io_service_work.push_back( ba::io_service::work(*ios));
			thr_grp.create_thread( boost::bind( &ba::io_service::run, ios));
		}
		server server( io_services, port, interface_address);
		thr_grp.join_all();
	} catch ( std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
