#include <vector>
#include <iostream>
#include <string>

class AbstractIDE {  // Product (abstract)
public:
   AbstractIDE() {}
   virtual ~AbstractIDE() {}
   virtual int getCost() = 0; // pure virtual method

   //str::string getName(){
   //    return m_name;
   //}

//private:
//   str::string m_name;
};
class WindowsIDE : public AbstractIDE { // Concrete Product
public:

   //WindowsIDE()
   //    : m_name(new str::string("windows"))
   //{}
   int getCost() override {
      return 4500;
   }
};

class MacIDE : public AbstractIDE { // Concrete Product
public:
   int getCost() override {
      return 99;
   }
};

class AbstractMalware {  // Product (abstract)
public:
   AbstractMalware() {}
   virtual ~AbstractMalware() {}
   virtual int getFrequency() = 0; // pure virtual method
};

class WindowsMalware : public AbstractMalware { // Concrete Product
public:
   int getFrequency() override {
      return std::numeric_limits<int>::max();
   }
};

class MacMalware : public AbstractMalware { // Concrete Product
public:
   int getFrequency() override {
      return 1;
   }
};
class AbstractOS { // Factory (abstract)
public:
   AbstractOS() {}
   virtual ~AbstractOS() { }
   virtual AbstractIDE *makeIDE() = 0; // pure virtual
   virtual AbstractMalware *makeMalware() = 0; // pure virtual
};

class Windows : public AbstractOS{ // Factory (concrete)
    AbstractIDE *makeIDE(){
        return new WindowsIDE;
    }
    AbstractMalware *makeMalware(){
        return new WindowsMalware;
    }
};

class Mac : public AbstractOS { // Factory (concrete)
    AbstractIDE *makeIDE(){
        return new MacIDE;
    }
    AbstractMalware *makeMalware(){
        return new MacMalware;
    }
};

int main() {

    // Create 2 new IDEs
    AbstractOS * win = new Windows();
    AbstractOS * mac = new Mac();

    std::vector<AbstractOS *> os;
    os.push_back(win);
    os.push_back(mac);

    for(AbstractOS * loop : os)
        {
            std::cout << "Cost: " << loop->makeIDE()->getCost() << ", Frequency: " << loop->makeMalware()->getFrequency() << std::endl;
            delete loop;
        }


    return 0;
}
