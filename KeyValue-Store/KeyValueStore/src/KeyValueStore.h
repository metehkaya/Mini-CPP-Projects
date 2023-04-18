#ifndef KEYVALUESTORE_H_
#define KEYVALUESTORE_H_

#include "PersistentStorage.h"
#include "LRUCache.h"
#include <string.h>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

class KeyValueStore {
public:
	KeyValueStore(int memoryTotal, string path);
	virtual ~KeyValueStore();
	string procCmd(string& s);
	void getWords(string& s, vector<string>& words);
private:
	string get(string key);
	bool put(string key, string value);
	bool remove(string key);
	bool clear();
	string printCache();
	string printDisk();
	string printAll();
	LRUCache* cache;
	PersistentStorage* disk;
};

#endif /* KEYVALUESTORE_H_ */
