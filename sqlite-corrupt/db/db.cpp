#include "db.h"

#include "fileutils.h"

#include <sqlite3.h>

#define SQLITE *(sqlite3**)&mData
#define SQLITE_IS_ERROR_DBWRITE(rc) (rc == SQLITE_READONLY || rc == SQLITE_CORRUPT)

using namespace std;

const char* Db::FILENAME = "/tmp/sqlitetest";

Db::Db() : mData(nullptr) {
  open();
}

Db::~Db() {
  term();
}

bool Db::write(const string& key, const string& value) {
  bool success = false;

  std::lock_guard<std::mutex> lck(mLock);

  sqlite3* &db = SQLITE;

  int retry = 0;
  int rc;
  do {
    if (!db)
      break;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "INSERT INTO item (key,value) values (?,?);", -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, value.c_str(), -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE)
      success = true;
    else
      printf("sqlite error %d: %s\n", rc, sqlite3_errstr(rc));

    sqlite3_finalize(stmt);
  } while (!success && SQLITE_IS_ERROR_DBWRITE(rc) && (++retry < 2) && open());

  return success;
}

bool Db::read(const string& key, string& value) {
  bool success = false;

  std::lock_guard<std::mutex> lck(mLock);

  sqlite3* &db = SQLITE;

  if (db) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT value FROM item where key = ?;", -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
      value = (const char*)sqlite3_column_text(stmt, 0);
      success = true;
    }
    else
      printf("sqlite error %d: %s\n", rc, sqlite3_errstr(rc));

    sqlite3_finalize(stmt);
  }

  return success;
}

bool Db::remove(const std::string& key) {
  bool success = false;

  std::lock_guard<std::mutex> lck(mLock);

  sqlite3* &db = SQLITE;

  int retry = 0;
  int rc;
  do
  {
    if (!db)
      break;

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "DELETE FROM item where key = ?;", -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE)
      success = true;
    else
      printf("sqlite error %d: %s\n", rc, sqlite3_errstr(rc));

    sqlite3_finalize(stmt);
  } while (!success && SQLITE_IS_ERROR_DBWRITE(rc) && (++retry < 2) && open());

  return success;
}

bool Db::open() {
  bool result = false;

  sqlite3* &db = SQLITE;

  if (!db || !FileUtils::fileExists(FILENAME)) {
    printf("opening %s\n", FILENAME);

    term();

    int rc = sqlite3_open(FILENAME, &db);

    printf("open %s - %s\n", FILENAME, rc == 0 ? "success" : "failure");

    if (rc) {
      term();
    } else {
      rc = sqlite3_exec(db, "CREATE TABLE if not exists item ("
                            "key TEXT,"
                            "value TEXT,"
                            "UNIQUE(key) ON CONFLICT REPLACE"
                            ");", 0, 0, nullptr);

      printf("create table - %s\n", rc == 0 ? "success" : "failure");

      if (rc == SQLITE_OK)
        result = true;
      else
        term();
    }
  }

  return result;
}

void Db::term() {
  sqlite3* &db = SQLITE;

  if (db)
    sqlite3_close_v2(db);

  db = nullptr;
}
