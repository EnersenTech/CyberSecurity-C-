#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

typedef std::pair<int, int> Plug_Pair;

class Plugboard {
public:
  Plugboard();
  ~Plugboard();

  void setPlugPairs(); // A-R
  void show();
  void show1(std::vector<Plug_Pair> temp);
  int getRandomUniqueValue(std::vector<int> &usedValues);
  bool existsInVector(const std::vector<int> &vec, int val);

private:
  Plug_Pair pair;
  std::vector<Plug_Pair> sets;
};

Plugboard::Plugboard() {}

Plugboard::~Plugboard() {}

bool Plugboard::existsInVector(const std::vector<int> &vec, int val) {
  for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end();
       it++) {
    if (val == *it) {
      return true;
    }
  }
  return false;
}

int Plugboard::getRandomUniqueValue(std::vector<int> &usedValues) {
  int value;
  do {
    value = rand() % 26 + 1;
  } while (existsInVector(usedValues, value));
  usedValues.push_back(value);
  return value;
}

void Plugboard::setPlugPairs() {
  srand(time(NULL));
  std::vector<int> usedLeftValues;
  std::vector<int> usedRightValues;

  std::vector<Plug_Pair> temp;

  int right = rand() % 26 + 1;
  for (int i = 0; i < 26; ++i) {
    int left = getRandomUniqueValue(usedLeftValues);
    // int right = getRandomUniqueValue(usedRightValues);

    bool exist = true;

    while (exist) {
      exist = false;
      right = right % 26 + 1;
      for (std::vector<int>::iterator it = usedLeftValues.begin();
           it != usedLeftValues.end(); it++) {
        std::cout << "IT : " << *it << "right :" << right << std::endl;
        if ((*it) == right) {
          exist = false;
          break;
        }
      }
    }

    usedRightValues.push_back(right);
    usedLeftValues.push_back(right);

    // Swap push
    sets.push_back(std::make_pair(left, right));
  }
}

void Plugboard::show() {
  for (std::vector<Plug_Pair>::iterator it = sets.begin(); it != sets.end();
       ++it) {
    std::cout << (char)((*it).first + 64) << " " << (char)((*it).second + 64)
              << std::endl;
  }
}

void Plugboard::show1(std::vector<Plug_Pair> temp) {
  for (std::vector<Plug_Pair>::iterator it = temp.begin(); it != temp.end();
       ++it) {
    std::cout << (char)((*it).first + 64) << " " << (char)((*it).second + 64)
              << std::endl;
  }
  std::cout << "==================" << std::endl;
}

int main() {
  Plugboard pg;
  pg.setPlugPairs();
  pg.show();
  return 0;
}
