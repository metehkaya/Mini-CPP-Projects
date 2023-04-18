#include "KeyValueStore.h"

KeyValueStore::KeyValueStore(int memoryTotal, string path) {
    cache = new LRUCache(memoryTotal);
    disk = new PersistentStorage(path);
}

KeyValueStore::~KeyValueStore() {
	// TODO Auto-generated destructor stub
}

void KeyValueStore::getWords(string& s, vector<string>& words) {
	int len = s.length() , idx = 0;
	if(len > 0 && s[len-1] == '\n') {
		len--;
		s.pop_back();
	}
	while(idx < len && s[idx] == ' ')
		idx++;
	while(idx < len) {
		string word = "";
		while(idx < len && s[idx] != ' ')
			word.push_back(s[idx++]);
		words.push_back(word);
		while(idx < len && s[idx] == ' ')
			idx++;
	}
}

string KeyValueStore::procCmd(string& s) {
	string response;
	vector<string> words;
	getWords(s,words);
	int nWords = words.size();
	if(nWords == 3 && words[0] == "PUT") {
		string key = words[1];
		string value = words[2];
		bool success = put(key,value);
		response = (success ? "PUT Successful" : "PUT Failed");
	}
	else if(nWords == 2 && words[0] == "DELETE") {
		string key = words[1];
		bool success = remove(key);
		response = (success ? "DELETE Successful" : "DELETE Failed");
	}
	else if(nWords == 2 && words[0] == "GET") {
		string key = words[1];
		response = get(key);
	}
	else if(nWords == 1 && words[0] == "DISPLAY")
		response = printAll();
	else if(nWords == 2 && words[0] == "DISPLAY" && words[1] == "CACHE")
		response = printCache();
	else if(nWords == 2 && words[0] == "DISPLAY" && words[1] == "DISK")
		response = printDisk();
	else if(nWords == 1 && words[0] == "CLEAR") {
		bool success = clear();
		response = (success ? "CLEAR Successful" : "CLEAR Failed");
	}
	else
		response = "Command Invalid";
	return response;
}

string KeyValueStore::get(string key) {
	string value = cache->get(key);
	string result;
	if(value.empty()) {
		value = disk->get(key);
		if(!value.empty()) {
			result = value + " (IN DISK)";
			list<pair<string,string>> toDisk;
			cache->put(key,value,toDisk);
	        if(!toDisk.empty())
	        	disk->put(toDisk);
		}
		else
			result = "!!! KEY NOT FOUND !!!";
	}
	else
		result = value + " (IN CACHE)";
	return result;
}

bool KeyValueStore::put(string key, string value) {
	list<pair<string,string>> toDisk;
	bool cacheSuccess = cache->put(key,value,toDisk);
	if(cacheSuccess) {
		disk->removeLine(key);
		if(!toDisk.empty())
			disk->put(toDisk);
	}
	return cacheSuccess;
}

bool KeyValueStore::remove(string key) {
	bool success = cache->remove(key);
	if(success) {
		// Move pairs from disk to cache?
	}
	else
		success = disk->removeLine(key);
	return success;
}

bool KeyValueStore::clear() {
	bool success = true;
	if(cache->clear() == false)
		success = false;
	if(disk->clear() == false)
		success = false;
	return success;
}

string KeyValueStore::printCache() {
	return "Cache\n" + cache->printCache();
}

string KeyValueStore::printDisk() {
	return "Disk\n" + disk->printDisk();
}

string KeyValueStore::printAll() {
	return printCache() + printDisk();
}
