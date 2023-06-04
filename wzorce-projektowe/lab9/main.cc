#include <iostream>
#include <atomic>
#include <filesystem>

#include <boost/asio.hpp>

static std::atomic<int> c = 0;

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

  

  return 0;
}
