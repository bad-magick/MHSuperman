#pragma once

#include <vector>
#include <string>
using namespace std;

int ReadLoadCommands(vector<string> &loadCommands);
int ReadSpawnCommands(vector<string> &spawnCommands);

void WriteCommand(string filename);
void RemoveBugReport(void);
void RemoveAllTraces(void);
