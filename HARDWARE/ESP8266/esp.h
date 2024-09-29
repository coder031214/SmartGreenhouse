#ifndef __esp_H
#define __esp_H
#include <stdbool.h>
char esp_Init(void);
char Esp_PUB(void);
void CommandAnalyse(void);
bool substringMatch(const char *text, const char *pattern);
int analy(char * memu);
bool substringMatch(const char *text, const char *pattern);
#endif
