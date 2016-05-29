#include <stdint.h>
#include "data.h"

data::data() {

}
data * data::getInstance() {
  if (instance == 0) {
    instance = new data;
    return instance;
  }
  return instance;
}
uint32_t data::getLatest() {
  
}
void data::readMem() {
  
}

