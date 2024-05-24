#include <cstdlib>
#include <iostream>
#include <vector>

// plain a b c d e f g ...
// cipher b h w e g q  ...
typedef std::vector<char> CharVec;
CharVec plain;
CharVec cipher;

void putCharInVec(void) {
  std::cout << "Plain : " << std::endl;
  for (int i = 0; i < 26; i++) {
    plain.push_back(i + 97); // a - z
  }

  // print plaintext
  for (int i = 0; i < 26; i++) {
    std::cout << plain[i] << "\t";
  }

  std::cout << std::endl << "Cipher : " << std::endl;

  int num;
  srand(time(NULL));
  for (int i = 0; i < 26; i++) {
    bool exist = true;
    while (exist) {
      exist = false;
      num = rand() % 26 + 65; // A - Z
      for (std::vector<char>::iterator it = cipher.begin(); it != cipher.end();
           it++) {
        if ((*it) == num) {
          exist = true;
          break;
        }
      }
    }
    cipher.push_back(num);
  }

  // print ciphertext
  for (int i = 0; i < 26; i++) {
    std::cout << cipher[i] << "\t";
  }
}

char monoAlphabetic(char c) {
  // Encryption
  if (c != toupper(c)) {
    for (int i = 0; i < 26; i++) {
      if (plain[i] == c)
        return cipher[i];
    }
  } else {
    // Decryption
    for (int i = 0; i < 26; i++) {
      if (cipher[i] == c)
        return plain[i];
    }
  }
  return 0;
}

int main(void) {
  std::string input, output;
  int choice = 0;
  putCharInVec();

  while (choice != 2) {
    std::cout << std::endl
              << "Press 1 : Encryption/Decryption; Press 2: quit" << std::endl;

    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1) {
      std::cout << "Put lower CASE letters for encryption and" << std::endl;
      std::cout << "UPPER CASE letters for decryption" << std::endl;
      getline(std::cin, input);

      for (int i = 0; i < input.length(); i++) {
        output += monoAlphabetic(input[i]);
      }
      std::cout << output << std::endl;
      output.clear();
    }
  }

  return 0;
}
