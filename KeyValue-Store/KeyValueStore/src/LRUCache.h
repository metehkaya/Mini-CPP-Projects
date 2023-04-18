#ifndef LRUCACHE_H_
#define LRUCACHE_H_

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
using namespace std;


class LRUCache {
public:
	LRUCache(int memoryTotal);
	virtual ~LRUCache();
	string get(string key);
	void putBack(string key, string value, int mem);
	bool put(string key, string value, list<pair<string,string>>& toDisk);
	bool remove(string key);
	string printCache();
	int getMemoryRemaining();
	bool clear();
private:
	void touch(auto iter);
	int memoryTotal;
    int memoryRemaining;
    list<pair<string,string>> pairs;
    unordered_map<string, list<pair<string,string>>::iterator> cache;
};

#endif /* LRUCACHE_H_ */
