#ifndef C_SAMPLES_USER_H
#define C_SAMPLES_USER_H

class User {
public:
  virtual ~User() = default;

  virtual void activate() = 0;
  virtual void deactivate() = 0;
};

#endif //C_SAMPLES_USER_H
