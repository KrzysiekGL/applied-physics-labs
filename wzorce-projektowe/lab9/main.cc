#include <ios>
#include <iostream>
#include <atomic>
#include <filesystem>
#include <string>

#include <boost/asio.hpp>

#ifdef THREAD_POOL
static std::atomic<int> c = 0;
#endif /* THREAD_POOL */

void searchDir(std::filesystem::directory_iterator dirIt, boost::asio::thread_pool & pool) {
  boost::asio::post(pool, [dirIt, &pool](){
    for(auto dirEntry : dirIt) {
      if(dirEntry.is_directory())
	// execute another post to the pool with recurese searchDir
	searchDir(std::filesystem::directory_iterator(dirEntry), pool);
      else {
	// search for the .txt files
	std::cout << dirEntry << '\n';
      }
    }
  });
}

int main(int argc, char ** argv, char ** env) {
#ifdef THREAD_POOL
  // Thread pool example
  std::cout << "Main thread: " << c << '\n';

  boost::asio::thread_pool pool(argc > 1 ? std::atoi(argv[1]) : 4);

  for(int i=0; i<12; ++i)
    boost::asio::post(pool, [](){c++;});

  pool.join();

  std::cout << "Main thread: " << c << '\n';
#endif /* THREAD_POOL */

#ifdef FILESYS
  // Filesystem example
  if(argc > 1)
    std::cout << argv[1] << " " << std::filesystem::file_size(argv[1]) << '\n';
#endif /* FILESYS */

  // Recursively search for all .txt files in the sandbox directory
  // Do it using asio thread pool from the boost

  boost::asio::thread_pool pool(argc>1? std::atoi(argv[1]) : 4);

  const std::string pathName = argc>2 ? argv[2] : "sandbox";
  const std::filesystem::path path(pathName);

  searchDir(std::filesystem::directory_iterator(path), pool);

  pool.join();

  return 0;
}
