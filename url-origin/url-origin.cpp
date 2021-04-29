#include <string>
#include <cassert>

using namespace std;

// helper functions
namespace {
  string GetUrlOrigin(const string &input) {
    // see https://tools.ietf.org/html/rfc3986
    auto path = input.find('/', input.find("//") + 2);
    auto fragment = input.rfind('#', path);
    auto end = fragment == string::npos ? path : fragment;
    auto query = input.rfind('?', end);
    if (query != string::npos)
      end = query;
    return input.substr(0, end);
  }
}

int main(int argc, char** argv) {
  assert(GetUrlOrigin("foo://example.com:8042/over/there?name=ferret#nose") == "foo://example.com:8042");
  assert(GetUrlOrigin("foo://example.com:8042?name=ferret#nose") == "foo://example.com:8042");
  assert(GetUrlOrigin("foo://example.com:8042#nose") == "foo://example.com:8042");
  assert(GetUrlOrigin("foo://example.com:8042") == "foo://example.com:8042");
  assert(GetUrlOrigin("foo://example.com") == "foo://example.com");
  assert(GetUrlOrigin("foo://") == "foo://");
  assert(GetUrlOrigin("foo://example.com:8042/over/there?name=https://google.com/") == "foo://example.com:8042");
  assert(GetUrlOrigin("foo://example.com:8042/over/there#name=https://google.com/") == "foo://example.com:8042");
  assert(GetUrlOrigin("foo://example.com:8042/over/there#bar://other.com:11111/over/there?name=ferret#nose") ==
         "foo://example.com:8042");
  assert(GetUrlOrigin("foo://example.com#bar://other.com:11111/over/there?name=ferret#nose") == "foo://example.com");
  assert(
      GetUrlOrigin("foo://example.com?url=bar://other.com:11111/over/there?name=ferret#nose") == "foo://example.com");
  assert(GetUrlOrigin("foo://example.com?name=google.com#http://") == "foo://example.com");
  assert(GetUrlOrigin("ftp://ftp.is.co.za/rfc/rfc1808.txt") == "ftp://ftp.is.co.za");
  assert(GetUrlOrigin("http://www.ietf.org/rfc/rfc2396.txt") == "http://www.ietf.org");
  assert(GetUrlOrigin("ldap://[2001:db8::7]/c=GB?objectClass?one") == "ldap://[2001:db8::7]");
  assert(GetUrlOrigin("mailto:John.Doe@example.com") == "mailto:John.Doe@example.com");
  assert(GetUrlOrigin("telnet://192.0.2.16:80/") == "telnet://192.0.2.16:80");
  assert(GetUrlOrigin("file:///home/root/") == "file://");
  assert(GetUrlOrigin("file:///") == "file://");
  assert(GetUrlOrigin("file://") == "file://");
  assert(GetUrlOrigin("file:/") == "file:");
  assert(GetUrlOrigin("/home/root/") == "/home");
  assert(GetUrlOrigin("home/root/") == "home");

  return 0;
}
