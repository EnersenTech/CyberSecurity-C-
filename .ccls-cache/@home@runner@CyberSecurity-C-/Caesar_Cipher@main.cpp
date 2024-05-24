#include <iostream>
#include <string>

char caesar(char c, unsigned int k) {
  // Step 1 : Encryption L = (L + K) mod 26
  if(isalpha(c) && c != toupper(c)){
    c = toupper(c);
    c = (((c-65) + k) % 26) + 65; 
  }
  // Step 2 : Decryption L = (L - K) mod 26
  else {
    c = (((c-65) -k) % 26) + 65; 
    c = tolower(c);
  }
  return c;
}

int main(void) {
  std::string input, output;
  int choice = 0;

  while (choice != 2) {
    std::cout << "Press 1 : Encryption/Decryption; Press 2: quit" <<std::endl;

    std::cin >> choice;

    if (choice == 1){
      unsigned int key;
      std::cout << "Choose key valule (number between 1 to 26) : ";
      std::cin >> key; 
      std::cin.ignore();
      

      std::cout << "Put lower case letters for encryption and" << std::endl; 
      std::cout << "upper case letters for decryption" << std::endl;
      std::getline(std::cin, input);

      for (int i = 0; i < input.length(); i++){
        output += caesar(input[i], key); 
      }
      std::cout << output << std::endl; 
      output.clear();
    }
  }
  
  return 0;
}