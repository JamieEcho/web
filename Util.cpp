
#include <sstream>
#include "Util.hpp"

std::string i2s(int num) {
  std::ostringstream os;
  os << num;
  return os.str();
}

