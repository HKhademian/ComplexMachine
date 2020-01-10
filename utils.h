#ifndef ROUND_H
#define ROUND_H

#define ROUNDER(x, n) std::round((x)*(n))/(n)
#define ROUNDL(x, n) ROUNDER(x, std::pow(10,n))
#define ROUND2(x) ROUNDER((x), 100.0)
#define ROUND3(x) ROUNDER((x), 1000.0)
#define ROUND ROUND3
#endif

#ifndef UTILS_H
#define UTILS_H

int trim(const char *eql, int &start, int &end);

double inrange(double val, double min, double max);

//void ltrim(const char *eql, int &start, int &end);
//void rtrim(const char *eql, int &start, int &end);

#endif
