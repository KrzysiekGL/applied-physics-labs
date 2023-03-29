#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <random>

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
    std::cout << "Quadratic: I'v got this vector: " << std::hex << &vec << std::endl;
    std::cout << "Can't handle it; pass\n\n";
    if(next!=NULL) next->findSubSum(std::forward<Vector>(vec));
  }
};

class SubSumLinear : public SubSumFinderBase {
public:
  SubSumLinear() {}
  SubSumLinear(std::shared_ptr<SubSumFinderInterface> next) : SubSumFinderBase(next) {}
  void findSubSum(Vector && vec) override {
    std::cout << "Linear: I'v got this vector: " << std::hex << &vec << std::endl;
    std::cout << "Can't handle it; pass\n\n";
    if(next!=NULL) next->findSubSum(std::forward<Vector>(vec));
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

  // Find biggest sub sum in the vector
  ssq->findSubSum(std::forward<Vector>(vec));
  std::cout << "Biggest sub sum found in the vector: " << vec.maxSubSum << '\n';

  return 0;
}
