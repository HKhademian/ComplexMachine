#include "utils.h"
#include<cmath>

int isWhiteSpace(char ch) {
	return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
}

int trim(const char *eql, int &start, int &end) {
	while (start <= end && isWhiteSpace(eql[start])) start++; //ltrim
	while (start <= end && isWhiteSpace(eql[end])) end--; //rtrim
	//ltrim(eql, start, end);
	//rtrim(eql, start, end);
	return end < start ? 0 : end - start + 1;
}

double inrange(double val, double min, double max) {
	val = std::fmod(val + (0 - min), max - min);
	if (val < 0)
		return val + min;
	return val - max;
}

//void ltrim(const char *eql, int &start, int &end) {
//	while (start <= end && isWhiteSpace(eql[start])) start++; //ltrim
//}
//
//void rtrim(const char *eql, int &start, int &end) {
//	while (start <= end && isWhiteSpace(eql[end])) end--; //rtrim
//}
//
//char toLower(char c) {
//	return c >= 'A' && c <= 'Z' ? (char) (c - ('A' + 'a')) : c;
//}
//
//char toUpper(char c) {
//	return c >= 'a' && c <= 'a' ? (char) (c - ('a' + 'A')) : c;
//}
//
//int strncasecmp(const char *str1, const char *str2, int n) {
//	char l, r;
//	while ((l = toLower(*str1)) != 0 && (r = toLower(*str2)) != 0 && l == r) {
//		str1++;
//		str2++;
//	}
//	return l - r;
//}
