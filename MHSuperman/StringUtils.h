#pragma once
#include <string>

char *ltrim(char *s);
char *rtrim(char *s);
char *strtrim(char *s);
std::string tolowers(std::string str);
std::string replaceChar(std::string str, char ch1, char ch2);
void gen_random(char *s, const int len);
int instr(char *SearchString, char *SearchTerm);
unsigned FindInStr(const std::string& src, const std::string& trm);
