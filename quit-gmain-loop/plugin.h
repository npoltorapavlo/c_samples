#pragma once

struct IPlugin {
  virtual ~IPlugin() {};
  virtual void Init() = 0;
  virtual void DeInit() = 0;
};

class Plugin : public IPlugin {
public:
  Plugin() = default;
  ~Plugin();

  virtual void Init() override;
  virtual void DeInit() override;
};
