#include <stdint.h>
#include <stdbool.h>
#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include "librdkafka/rdkafkacpp.h"
#include "publish.h"
#include "config.h"

publish * publish::instance = NULL;
char * publish::hostname = (char*)malloc(sizeof(char) * 80);

publish::publish() {
  std::string errstr;

  // set up the producer we are going to write
  conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
  char * topicName = getHostname();
  char * broke;
  sprintf(broke, "%s:%d", HOST, PORT);
  std::string brokers(broke);
  conf->set("metadata.broker.list", brokers, errstr); 
  DeliveryCallback ex_dr_cb;
  //conf->set("dr_cb", &ex_dr_cb, errstr);
  producer = RdKafka::Producer::create(conf, errstr); 

  RdKafka::Conf * tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);
  // create the name of the topic
  std::string topic_str(topicName);

  topic = RdKafka::Topic::create(producer, topic_str, tconf, errstr);

}

void DeliveryCallback::dr_cb(RdKafka::Message &message) {

}

char * publish::getHostname() {
  if (hostname[0] == '\0') {
    FILE * fp; 
    fp = popen("hostname", "r");
    char  line[80];
    while(fgets(line, 80, fp) != NULL) {
    // do nothing
    }
    strcpy(hostname, line);
  }
  return hostname;
}
publish * publish::getInstance() {
  if (instance == NULL) {
    instance = new publish();
    return instance;
  }
  return instance;
}

bool publish::publishResult(uint32_t result) {
  if (!producer) {
    return false;
  }
  char load[80];
  sprintf(load, "%d", result);
  std::string payload(load);
  RdKafka::ErrorCode  error = producer->produce(topic, 0, RdKafka::Producer::RK_MSG_COPY, const_cast<char *>(payload.c_str()), payload.size(), NULL, NULL);
  return true;
}
