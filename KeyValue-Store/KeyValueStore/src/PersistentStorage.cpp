#include "PersistentStorage.h"

#include <iostream>
#include <fstream>

PersistentStorage::PersistentStorage(string path) {
    this->path = path;
    remove(path.c_str());
    remove(pathTemp.c_str());
    ofstream outDisk(path.c_str());
    outDisk.close();
}

PersistentStorage::~PersistentStorage() {
	remove(path.c_str());
	remove(pathTemp.c_str());
}

string PersistentStorage::get(string key) {
	string value = "";
	ifstream myfile(path.c_str());
	int lineIdx = 0;
	if(myfile.is_open()) {
		string line;
		while(getline(myfile,line)) {
			int idx = line.find(' ');
			if(idx != -1) {
				int len = line.length();
				string lineKey = line.substr(0,idx);
				string lineValue = line.substr(idx+1,len-idx-1);
				if(key == lineKey) {
					value = lineValue;
					break;
				}
			}
			lineIdx++;
		}
		myfile.close();
	}
	if(value != "")
		removeLine(lineIdx);
	return value;
}

bool PersistentStorage::put(list<pair<string,string>>& toDisk) {
	ofstream out;
    out.open(path.c_str(), std::ios::app);
    for(auto p : toDisk) {
    	string key = p.first;
    	string value = p.second;
    	out << key << " " << value << endl;
	}
	out.close();
	return true;
}

bool PersistentStorage::removeLine(int lineIdx) {
	bool success = false;
	ifstream myfile(path.c_str());
	ofstream out(pathTemp.c_str());
	if(myfile.is_open()) {
		string line;
		while(getline(myfile,line)) {
			if(lineIdx != 0)
				out << line << endl;
			else
				success = true;
			lineIdx--;
		}
		myfile.close();
	}
	out.close();
	remove(path.c_str());
	rename(pathTemp.c_str(), path.c_str());
	return success;
}

bool PersistentStorage::removeLine(string key) {
	bool success = false;
	ifstream myfile(path.c_str());
	ofstream out(pathTemp.c_str());
	if(myfile.is_open()) {
		string line;
		while(getline(myfile,line)) {
			int idx = line.find(' ');
			if(idx != -1) {
				int len = line.length();
				string lineKey = line.substr(0,idx);
				string lineValue = line.substr(idx+1,len-idx-1);
				if(key == lineKey)
					success = true;
				else
					out << line << endl;
			}
		}
		myfile.close();
	}
	out.close();
	remove(path.c_str());
	rename(pathTemp.c_str(), path.c_str());
	return success;
}

string PersistentStorage::printDisk() {
	string result = "";
	ifstream myfile(path.c_str());
	if(myfile.is_open()) {
		string line;
		while(getline(myfile,line)) {
			int idx = line.find(' ');
			if(idx != -1) {
				int len = line.length();
				string key = line.substr(0,idx);
				string val = line.substr(idx+1,len-idx-1);
				result += key + " " + val + "\n";
			}
		}
		myfile.close();
	}
	return result;
}

bool PersistentStorage::clear() {
    remove(path.c_str());
    remove(pathTemp.c_str());
	return true;
}
