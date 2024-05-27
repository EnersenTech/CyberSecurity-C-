#include <iostream>
#include <string>

class Vigenere {
public:
  Vigenere();
  ~Vigenere();

  void setKey(std::string k) { key = k; }
  std::string getKey() { return key; }
  std::string encrypt(std::string input);
  std::string decrypt(std::string input);

private:
  std::string key;
};

Vigenere::Vigenere() {
  std::string k = getKey();
  for (int i = 0; i < k.length(); i++) {
    if (k[i] >= 'A' && k[i] <= 'Z') {
      k += k[i];
    } else if (k[i] >= 'a' && k[i] <= 'z') {
      k += k[i] + 'A' - 'a';
    }
  }
};

std::string Vigenere::encrypt(std::string input) {
  std::string output;
  std::string k = getKey();

  for (int i = 0, j = 0; i < input.length(); ++i) {
    char c = input[i];
    if (c >= 'a' && c <= 'z')
      c += 'A' - 'a';
    else if (c < 'A' || c > 'Z')
      continue;
    output +=
        (c + k[j] - 2 * 'A') % 26 +
        'A'; // added 'A' to bring it in range of ASCII alphabet [ 65-90 | A-Z ]
    j = (j + 1) % k.length();
  }
  return output;
};

std::string Vigenere::decrypt(std::string input) {
  std::string output;
  std::string k = getKey();

  for (int i = 0, j = 0; i < input.length(); ++i) {
    char c = input[i];
    if (c >= 'a' && c <= 'z')
      c += 'A' - 'a';
    else if (c < 'A' || c > 'Z')
      continue;
    output +=
        (c - k[j] + 26) % 26 +
        'A'; // added 'A' to bring it in range of ASCII alphabet [ 65-90 | A-Z ]
    j = (j + 1) % k.length();
  }

  return output;
};

Vigenere::~Vigenere() { std::cout << "End of instance." << std::endl; };

int main(void) {
  Vigenere pa;
  std::string key;
  std::string input;

  std::cout << "Put key value : " << std::endl;

  std::cin >> key;
  std::cin.ignore();
  pa.setKey(key);

  // Input the data to encrypt or decrypt
  std::cout << "Put your text " << std::endl;
  getline(std::cin, input);

  std::cout << "Press 1: Encrypt | 2: Decrypt" << std::endl;
  int choice;
  std::cin >> choice;

  if (choice == 1)
    std::cout << pa.encrypt(input) << std::endl;
  else
    std::cout << pa.decrypt(input) << std::endl;

  return 0;
}