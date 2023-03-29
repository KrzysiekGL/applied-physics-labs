#include <iostream>
#include <ratio>
#include <utility>
#include <vector>
#include <memory>
#include <random>
#include <thread>
#include <future>
#include <chrono>

struct Vector {
  int maxSubSum;
  std::vector<int> numbers;
};

class SubSumFinderInterface {
public:
  virtual ~SubSumFinderInterface() {}
  virtual void findSubSum(Vector && vec) = 0;
};

class SubSumFinderBase : public SubSumFinderInterface {
protected:
  SubSumFinderBase() {}
  SubSumFinderBase(std::shared_ptr<SubSumFinderInterface> next) : next(next) {}
  std::shared_ptr<SubSumFinderInterface> next;
};

class SubSumQuadratic : public SubSumFinderBase {
public:
  SubSumQuadratic() {}
  SubSumQuadratic(std::shared_ptr<SubSumFinderInterface> next) : SubSumFinderBase(next) {}
  void findSubSum(Vector && vec) override {
    // Try to solve the problem in less than 0.1 second (100 ms). Otherwise, forward it to the next.
    std::cout << "Quadratic: I'v got this vector: " << std::hex << &vec << std::dec << std::endl;

    std::chrono::system_clock::time_point delta_time =
      std::chrono::system_clock::now() + std::chrono::milliseconds(100);

    // Make a future that should be available in at most the delta_time
    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::thread([&](std::promise<int> p) {
      p.set_value_at_thread_exit(quadratic(vec.numbers));
    }, std::move(p)).detach();

    std::cout << "Quadratic: Wating for 100 ms...\n";

    if(std::future_status::ready == f.wait_until(delta_time)) {
      std::cout << "Quadratic: Solved the problem in <= to 100 ms\n";
      vec.maxSubSum = f.get();
      return;
    }
    else if(next!=NULL) {
      // Forward the problem
      std::cout << "Quadratic: Can't finish it in time; pass\n";
      next->findSubSum(std::forward<Vector>(vec));
    }
    // Cease execution and forwarding
    else std::cout << "Quadratic: Can't pass the problem. Leaving unresolved...\n";
 }
private:
  int quadratic(std::vector<int> vec) {
    return 0;
  }
};

class SubSumLinear : public SubSumFinderBase {
public:
  SubSumLinear() {}
  SubSumLinear(std::shared_ptr<SubSumFinderInterface> next) : SubSumFinderBase(next) {}
  void findSubSum(Vector && vec) override {
    // Try to solve the problem in less than 0.1 second (100 ms). Otherwise, forward it to the next.
    std::cout << "Linear: I'v got this vector: " << std::hex << &vec << std::dec << std::endl;

    std::chrono::system_clock::time_point delta_time =
      std::chrono::system_clock::now() + std::chrono::milliseconds(100);

    // Make a future that should be available in at most the delta_time
    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::thread([&](std::promise<int> p) {
      p.set_value_at_thread_exit(linear(vec.numbers));
    }, std::move(p)).detach();

    std::cout << "Linear: Wating for 100 ms...\n";

    if(std::future_status::ready == f.wait_until(delta_time)) {
      std::cout << "Linear: Solved the problem in <= to 100 ms\n";
      vec.maxSubSum = f.get();
      return;
    }
    else if(next!=NULL) {
      // Forward the problem
      std::cout << "Linear: Can't finish it in time; pass\n";
      next->findSubSum(std::forward<Vector>(vec));
    }
    // Cease execution and forwarding
    else std::cout << "Linear: Can't pass the problem. Leaving unresolved...\n";
  }
private:
  int linear(std::vector<int> vec) {
    return 0;
  }
};

int main(int argc, char ** argv, char ** env) {
  const int N = argc > 1 ? std::atoi(argv[1]) : 1000;

  std::shared_ptr<SubSumFinderInterface> ssl = std::make_shared<SubSumLinear>();
  std::shared_ptr<SubSumFinderInterface> ssq = std::make_shared<SubSumQuadratic>(ssl);

  // Prepare random number generator and uniform distribution between -10 and 10
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(-10, 10);

  // Prepare data (vector) to work on
  Vector vec;
  for(int i=0; i<N; ++i)
    vec.numbers.push_back(dist(rng));

#ifndef NO_FUN
  // Just for fun, print scaled histogram
  for(int i=0; i<21; ++i) {
    std::cout << i-10 << ":\t";
    int counter = 0;
    for(auto n : vec.numbers) {
      if(n==i-10 && (counter % (N>1000 ? int(0.001 * N) : 1) == 0)) std::cout << "|";
      counter++;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
#endif /* NO_FUN */

  // Find biggest sub sum in the vector
  ssq->findSubSum(std::forward<Vector>(vec));
  std::cout << "Main: Biggest sub sum found in the vector: " << vec.maxSubSum << '\n';

  return 0;
}
