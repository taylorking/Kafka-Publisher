class data {

  private: 
    data * instance;
    void readMem();
    data();
  public:
    data * getInstance();
    uint32_t getLatest();
};

