#include "keyboard.h"
#include <string>
#include <iostream>



Keyboard::Keyboard(){
};
Keyboard::~Keyboard(){
};

int Keyboard::forward(char letter){
  int signal;
  std::string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for(std::string::iterator it = alphabets.begin(); it != alphabets.end(); it++){
    if((*it) == letter){
      signal = it - alphabets.begin();
    }
  }

  std::cout << signal << std::endl;

  return signal;
}

char Keyboard::backward(int signal){

  std::string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char letter = alphabets[signal];

  std::cout << letter << std::endl;
  return letter;
}