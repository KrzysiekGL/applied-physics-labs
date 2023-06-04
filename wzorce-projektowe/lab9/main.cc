#include <iostream>
#include <atomic>

#include <boost/asio.hpp>

static std::atomic<int> c = 0;

int main(int argc, char ** argv, char ** env) {
  std::cout << "Main thread: " << c << '\n';

  boost::asio::thread_pool pool(argc > 1 ? std::atoi(argv[1]) : 4);

  for(int i=0; i<12; ++i)
    boost::asio::post(pool, [](){c++;});

  pool.join();

  std::cout << "Main thread: " << c << '\n';

  return 0;
}
