class publish {
  private:
    static char * hostname;
    static publish * instance;
    RdKafka::Producer * producer;
    RdKafka::Conf * conf;
    publish();
    RdKafka::Topic * topic;
  public:
    char * getHostname();
    static publish * getInstance();
    bool publishResult(uint32_t result);
};
class DeliveryCallback : public RdKafka::DeliveryReportCb {
  public:
    void dr_cb(RdKafka::Message &message);

};


