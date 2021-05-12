#ifndef C_SAMPLES_KEYHOLDER_H
#define C_SAMPLES_KEYHOLDER_H

class KeyHolder {
public:
  KeyHolder();
  ~KeyHolder();

  void write(long secret);
  long read() const;
  bool empty() const;

private:
  char* ptr;
};

#endif //C_SAMPLES_KEYHOLDER_H
