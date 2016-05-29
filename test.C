#include <cstdio>
#include "librdkafka/rdkafkacpp.h"
#include "publish.h"
int main() {
  publish * instance = publish::getInstance();
  printf("%s\n", instance->getHostname());
  instance->publishResult(4);

}


