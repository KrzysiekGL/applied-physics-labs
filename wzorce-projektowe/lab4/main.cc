#include <cstdlib>
#include <memory>
#include <iostream>
#include <string>

class StrategyTransport {
public:
  virtual std::string executeCommute() = 0;
  virtual ~StrategyTransport() {};
};

class Bike : public StrategyTransport {
public:
  virtual std::string executeCommute() override {
    return std::string("Going by bike");
  }
};

class Bus : public StrategyTransport {
public:
  virtual std::string executeCommute() override {
    return std::string("Going by bus");
  }
};

class Cab : public StrategyTransport {
public:
  virtual std::string executeCommute() override {
    return std::string("Going by cab");
  }
};

class ContextCommute {
  std::unique_ptr<StrategyTransport> strategyTransport;
public:
  void setStrategyTransport(std::unique_ptr<StrategyTransport> && strategy) {
    strategyTransport = std::move(strategy);
  }
  std::string go() {
    if(strategyTransport) return strategyTransport->executeCommute();
    return "No strategy selected";
  }
};

void findTransport(ContextCommute & cc, int & money, int time_minutes) {
  if(time_minutes <= 15 && money >= 20) {
    cc.setStrategyTransport(std::make_unique<Cab>());
    money -= 20;
  }
  else if(time_minutes <= 30 && money >= 3) {
    cc.setStrategyTransport(std::make_unique<Bus>());
    money -= 3;
  }
  else cc.setStrategyTransport(std::make_unique<Bike>());
}

int main(int argc, char ** argv, char ** env) {
  int money = argc >= 2 ? std::atoi(argv[1]) : 0;
  int time_minutes = argc >= 3 ? std::atoi(argv[2]) : 0;
  int item_value = argc >= 4 ? std::atoi(argv[3]) : 0;

  ContextCommute cc;
  std::cout << "With selected parameters: " << cc.go() << '\n';

  findTransport(cc, money, time_minutes);
  std::cout << "With selected parameters: " << cc.go() << '\n';

  findTransport(cc, money, time_minutes);
  std::cout << "With selected parameters: " << cc.go() << '\n';

  findTransport(cc, money, time_minutes);
  std::cout << "With selected parameters: " << cc.go() << '\n';

  return 0;
}
