#include <iostream>
#include <memory>

enum class Beer {
  Ale,
  Stout
};

class IBeer {
public:
  virtual ~IBeer() {}
  virtual void drink() = 0;
  virtual void waste() = 0;
};

class IBeerFactory {
public:
  virtual ~IBeerFactory() {}
  virtual std::unique_ptr<IBeer> fetchMeABeer(Beer beer, bool premium) = 0;
};

class IAle : public IBeer {
};

class IStout : public IBeer {
};

class QueensAle : public IAle {
  void drink() override { std::cout << "Queens Ale drink\n"; }
  void waste() override { std::cout << "Queens Ale waste...\n"; }
};

class QueensStout : public IStout {
  void drink() override { std::cout << "Queens Stout drink\n"; }
  void waste() override { std::cout << "Queens Stout waste...\n"; }
};

class QueensFactory : public IBeerFactory {
public:
  QueensFactory() {}
  std::unique_ptr<IBeer> fetchMeABeer(Beer beer, bool premium) override {
    std::unique_ptr<IBeer> b;
    switch(beer) {
    case Beer::Ale:
      b = std::make_unique<QueensAle>();
      break;
    case Beer::Stout:
      b = std::make_unique<QueensStout>();
      break;
    }
    return std::move(b);
  }
};

class KentshireAle : public IAle {
  void drink() override { std::cout << "Kentshire Ale drink\n"; }
  void waste() override { std::cout << "Kentshire Ale waste...\n"; }
};

class KentshireStout : public IStout {
  void drink() override { std::cout << "Kentshire Stout drink\n"; }
  void waste() override { std::cout << "Kentshire Stout waste...\n"; }
};

class KentshireFactory : public IBeerFactory {
public:
  KentshireFactory() {}
  std::unique_ptr<IBeer> fetchMeABeer(Beer beer, bool premium) override {
    std::unique_ptr<IBeer> b;
    switch(beer) {
    case Beer::Ale:
      b = std::make_unique<KentshireAle>();
      break;
    case Beer::Stout:
      b = std::make_unique<KentshireStout>();
      break;
    }
    return std::move(b);
  }
};

class Factory : public IBeerFactory {
public:
  std::unique_ptr<IBeer> fetchMeABeer(Beer beer, bool premium) override {
    std::unique_ptr<IBeerFactory> factory;
    if(premium)
      factory = std::make_unique<QueensFactory>();
    else
      factory = std::make_unique<KentshireFactory>();

    return std::move(factory->fetchMeABeer(beer, premium));
  }
};

int main(int argc, char ** argv, char ** env) {
  std::unique_ptr<IBeerFactory> factory = std::make_unique<Factory>();

  std::unique_ptr<IBeer> beer = factory->fetchMeABeer(Beer::Ale, false);
  beer->waste();

  beer = factory->fetchMeABeer(Beer::Stout, true);
  beer->drink();

  return 0;
}

