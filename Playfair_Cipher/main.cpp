#include <iostream>
#include <string>

class PlayFair {
public:
  PlayFair();
  ~PlayFair(); // Constructor & Deconstructor

  void setKey(std::string k) { key = k; }
  std::string getKey() { return key; }
  std::string keyWithoutDuplicateAlphabet(std::string k);
  std::string encrypt(std::string str);
  std::string decrypt(std::string str);

  void setMatrix();
  void showMatrix();

  int findRow(char ch);
  int findCol(char ch);

  char findLetterr(int x_val, int y_val);

private:
  char matrix[5][5];
  std::string key;
};

// Init instance
PlayFair::PlayFair(void) {
  std::cout << "Generate key matrix 5*5 : " << std::endl;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      matrix[i][j] = 0;
    }
  }
};

std::string PlayFair::keyWithoutDuplicateAlphabet(std::string k) {
  std::string str_wo_dup; // mono letter set e.g. hello -> helo

  for (std::string::iterator it = k.begin(); it != k.end(); it++) {
    bool alphabet_exist = false;
    for (std::string::iterator it1 = str_wo_dup.begin();
         it1 != str_wo_dup.end(); it1++) {
      if (*it1 == *it) {
        alphabet_exist = true;
      }
    }
    if (!alphabet_exist) {
      str_wo_dup.push_back(*it);
    }
  }
  return str_wo_dup;
}

void PlayFair::setMatrix() {
  std::string kwda = keyWithoutDuplicateAlphabet(getKey());
  // Getting the key with unique char
  int i_val, j_val;
  int count = 0;
  // Populating the playfair matrix with the key and other letters
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (count == kwda.length()) {
        break;
      } else {
        matrix[i][j] = toupper(kwda[(5 * i) + j]);
        ++count;
      }
    }
    if (count == kwda.length())
      break;
  }
  for (int i = 0; i < 26; i++) {
    char ch = 65 + i;
    bool alphabet_exist = false;
    for (std::string::iterator it = kwda.begin(); it != kwda.end(); it++) {
      if (ch == toupper(*it))
        alphabet_exist = true;
    }
    if (ch == 'J')
      alphabet_exist = true;

    bool exit = false;
    if (!alphabet_exist) {
      for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
          if (!isalpha(matrix[i][j])) {
            matrix[i][j] = toupper(ch);
            exit = true;
          }
          if (exit == true)
            break;
        }
        if (exit == true)
          break;
      }
    }
  }
}

void PlayFair::showMatrix() {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (matrix[i][j] != 'I')
        std::cout << matrix[i][j] << "\t";
      else
        std::cout << "I/J"
                  << "\t";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int PlayFair::findRow(char ch) {
  // Finding the specific row for a character
  if (ch == 'j')
    ch = 'i';
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (matrix[i][j] == toupper(ch))
        return i;
    }
  }
  return -1; // if not found
}

int PlayFair::findCol(char ch) {
  // Finding the specific column for a character
  if (ch == 'j')
    ch = 'i';
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (matrix[i][j] == toupper(ch))
        return j;
    }
  }
  return -1; // if not found
}

std::string PlayFair::encrypt(std::string str) {
  std::string output;

  // replace by x the repeating plaintext letters that are in the same pair
  for (int i = 1; i < str.length(); i += 2) {
    if (str[i - 1] == str[i]) {
      std::string temp1, temp2;
      for (int j = 0; j < i; j++) {
        temp1.push_back(str[j]);
      }
      for (int j = i; j < str.length(); j++) {
        temp2.push_back(str[j]);
      }
      str.clear();
      str = temp1 + 'x' + temp2;
    }
  }

  for (int i = 0; i < str.length(); i += 2) {
    // Rule.1 same row
    if (findRow(str[i]) == findRow(str[i + 1])) {
      output.push_back(matrix[findRow(str[i])][(findCol(str[i]) + 1) % 5]);
      output.push_back(matrix[findRow(str[i + 1])][(findCol(str[i + 1])) % 5]);
    }
    // Rule.2 same column
    else if (findCol(str[i]) == findCol(str[i + 1])) {
      output.push_back(matrix[(findRow(str[i]) + 1) % 5][findCol(str[i])]);
      output.push_back(
          matrix[(findRow(str[i + 1]) + 1) % 5][findCol(str[i + 1])]);
    }
    // Rule.3 other cases; rectangle range and oposite corner value
    else {
      output.push_back(matrix[findRow(str[i])][findCol(str[i + 1])]);
      output.push_back(matrix[findRow(str[i + 1])][findCol(str[i])]);
    }
  }
  if ((str.length() % 2) != 0) {
    output[output.length() - 1] = toupper(str[str.length() - 1]);
  }
  return output;
}

std::string PlayFair::decrypt(std::string str) {
  std::string output;

  for (int i = 0; i < str.length(); i = i + 2) {
    // for the letter pair falls in the same row
    if (findRow(str[i]) == findRow(str[i + 1])) {
      int y;
      if ((findCol(str[i]) - 1) >= 0) {
        y = (findCol(str[i]) - 1);
      } else {
        y = 4;
      }
      output.push_back(matrix[findRow(str[i])][y]);

      if ((findCol(str[i + 1]) - 1) >= 0) {
        y = (findCol(str[i + 1]) - 1);
      } else
        y = 4;
      output.push_back(matrix[findRow(str[i + 1])][y]);
    }
    // for the letter pair falls in the same coloumn
    else if (findCol(str[i]) == findCol(str[i + 1])) {
      int x;
      if ((findRow(str[i]) - 1) >= 0)
        x = (findRow(str[i]) - 1);
      else
        x = 4;
      output.push_back(matrix[x][findCol(str[i])]);
      if ((findRow(str[i + 1]) - 1) >= 0)
        x = (findRow(str[i + 1]) - 1);
      else
        x = 4;
      output.push_back(matrix[x][findCol(str[i + 1])]);
    }
    // for other cases
    else {
      output.push_back(matrix[findRow(str[i])][findCol(str[i + 1])]);
      output.push_back(matrix[findRow(str[i + 1])][findCol(str[i])]);
    }
    // remove x from the string
    for (int i = 0; i < output.length(); i++) {
      if (output[i] == 'X') {
        output.erase(output.begin() + i);
      }
    }
  }
  return output;
}

// Deconstruct function
PlayFair::~PlayFair(void) { std::cout << "End of instance." << std::endl; };

int main(void) {
  PlayFair pf;
  std::string key, input;

  std::cout << "Put key valule (put alphabets/words): " << std::endl;
  std::cin >> key;
  std::cin.ignore();
  pf.setKey(key);
  pf.setMatrix();
  pf.showMatrix();
  // Input the data to encrypt or decrypt
  std::cout << "Put your text " << std::endl;
  getline(std::cin, input);

  std::cout << "Press 1: Encrypt | 2: Decrypt" << std::endl;
  int choice;
  std::cin >> choice;

  if (choice == 1)
    std::cout << pf.encrypt(input) << std::endl;
  else
    std::cout << pf.decrypt(input) << std::endl;

  return 0;
}