#ifndef BOOL_H
#define BOOL_H

#include <iostream>
#include <string>

enum class TypeBool {
    EVENT,
    CUSTOM_BOOL,
    NONE
};

class Bool {
 public:
  TypeBool getTypeBool();
  void setTypeBool(TypeBool boool);
  void setBoolean(bool bol);
  bool getBoolean();
 private:
   TypeBool typeBool;
   bool boool;
};

#endif