#pragma once 

// Keyboard 
class Keyboard{
  public: 
    Keyboard();
    ~Keyboard();

    int forward(char letter);
    char backward(int signal);
};

