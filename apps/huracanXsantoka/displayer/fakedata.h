#ifndef FAKEDATA_H
#define FAKEDATA_H
#include <vector>
#include <unistd.h>
#include <tuple>
#define TB  std::tuple<int, char, char, char, char, char, char, char, char>
static std::vector<TB> fakecandata{
#ifndef SANTOKA
#endif
};
#endif // FAKEDATA_H
