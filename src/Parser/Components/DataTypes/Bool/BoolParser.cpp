#include "BoolParser.h"

Bool getParseBool(std::string str) {
  Bool bools;
  bools.setTypeBool(TypeBool::NONE);

  EventType eventType = getEventTypeByString(str);

  if(eventType != EventType::NONE) {
    bools.setTypeBool(TypeBool::EVENT);
  }
   

  return bools; 
}
