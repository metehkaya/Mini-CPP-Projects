#ifndef PERSISTENTSTORAGE_H_
#define PERSISTENTSTORAGE_H_

#include <list>
#include <string>
#include <vector>
using namespace std;

class PersistentStorage {
public:
	PersistentStorage(string path);
	virtual ~PersistentStorage();
	string get(string key);
	bool put(list<pair<string,string>>& toDisk);
	bool removeLine(int lineIdx);
	bool removeLine(string key);
	string printDisk();
	bool clear();
private:
	string path;
	const string pathTemp = "temp.txt";
};

#endif /* PERSISTENTSTORAGE_H_ */
