#include "LRUCache.h"

LRUCache::LRUCache(int memoryTotal) {
    this->memoryTotal = memoryTotal;
    memoryRemaining = memoryTotal;
}

LRUCache::~LRUCache() {
	// TODO Auto-generated destructor stub
}

string LRUCache::get(string key) {
    auto iter = cache.find(key);
    if(iter == cache.end())
        return "";
    auto liter = iter->second;
    pair<string,string> p = (*liter);
    string value = p.second;
    touch(iter);
    return value;
}

void LRUCache::touch(auto iter) {
	// iter_prev = iter - 1
	// iter_next = iter + 1
	// iter_prev->next = iter_next
	// iter_next->prev = iter_prev
    auto liter = iter->second;
    // pair<string,string> p = (*liter);
    pairs.erase(iter->second);
    pairs.push_front((*liter));
    iter->second = pairs.begin();
}

void LRUCache::putBack(string key, string value, int mem) {
	memoryRemaining -= mem;
    cache[key] = pairs.end();
    pairs.push_back(make_pair(key,value));
}

bool LRUCache::put(string key, string value, list<pair<string,string>>& toDisk) {
    bool success = false;
	auto iter = cache.find(key);
    if(iter == cache.end()) {
        int newMemory = key.capacity() + value.capacity();
        if(newMemory <= memoryTotal) {
    		while(memoryRemaining < newMemory) {
    			pair<string,string> p = pairs.back();
    			string deletedKey = p.first;
    			string deletedValue = p.second;
    			int memoryDeleted = deletedKey.capacity() + deletedValue.capacity();
    			memoryRemaining += memoryDeleted;
                cache.erase(deletedKey);
                toDisk.push_back(pairs.back());
                pairs.pop_back();
            }
            success = true;
            memoryRemaining -= newMemory;
            pairs.push_front(make_pair(key,value));
            cache[key] = pairs.begin();
        }
    }
    return success;
}

bool LRUCache::remove(string key) {
	bool success = false;
	auto iter = cache.find(key);
	if(iter != cache.end()) {
		success = true;
		auto liter = iter->second;
		pair<string,string> p = (*liter);
		string value = p.second;
		pairs.erase(iter->second);
		cache.erase(iter);
		int memoryDeleted = key.capacity() + value.capacity();
		memoryRemaining += memoryDeleted;
	}
	return success;
}

string LRUCache::printCache() {
	string result = "";
	for(auto p : pairs) {
		string key = p.first;
		string value = p.second;
		result += key + " " + value + "\n";
	}
	return result;
}

int LRUCache::getMemoryRemaining() {
	return memoryRemaining;
}

bool LRUCache::clear() {
	memoryRemaining = memoryTotal;
	pairs.clear();
	cache.clear();
	return true;
}
