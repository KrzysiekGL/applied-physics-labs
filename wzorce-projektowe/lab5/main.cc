#include <iostream>
#include <utility>
#include <vector>
#include <memory>

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
  std::shared_ptr<SubSumFinderInterface> ssl = std::make_shared<SubSumLinear>();
  std::shared_ptr<SubSumFinderInterface> ssq = std::make_shared<SubSumQuadratic>(ssl);

  Vector vec;
  for(int i=0; i<1000; ++i)
    vec.numbers.push_back(i);

  ssq->findSubSum(std::forward<Vector>(vec));

  return 0;
}
