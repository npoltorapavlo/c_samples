#include "users/reader.h"
#include "users/writer.h"
#include "users/moderator.h"
#include "users/cleaner.h"

#include <list>
#include <thread>
#include <memory>
#include <algorithm>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  cout << "Press any key to exit..." << '\n';

  list<shared_ptr<User>> users = {
      make_shared<Reader>(100), // interval 0.1s
      make_shared<Reader>(100),
      make_shared<Writer>(100),
      make_shared<Writer>(100),
      make_shared<Moderator>(100),
  };

  for_each(users.begin(), users.end(), [](const shared_ptr<User>& it) {
    it->activate();
  });

  thread t([&users]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    users.emplace_back(make_shared<Cleaner>(500)); // interval 0.5s
    (*users.rbegin())->activate();
  });

  cin.get();

  cout << "Closing..." << '\n';

  if (t.joinable())
    t.join();

  users.clear();

  return 0;
}
