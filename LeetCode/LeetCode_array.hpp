#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;
void array_to_c(string& arr){
	for (int i = 0; i < arr.size(); ++i) {
		if (arr[i] == '[') {
			arr[i] = '{';
		}
		else if (arr[i] == ']') {
			arr[i] = '}';
		}
	}
}
string subreplace(string& s, const string& src, const string& dest) {
	if (src.size() > s.size()) {
		return s;
	}
	string res;
	int i = 0;
	for (i = 0; i < s.size() - src.size();) {
		if (s.substr(i, src.size()) == src) {
			res += dest;
			i += src.size();
		}
		else {
			res.push_back(s[i++]);
		}
	}
	res += s.substr(i);
	res.swap(s);
	return res;
}

vector<string> split(const string& s, char c) {
	int begin = 0;
	vector<string> res;
	for (int i = 0; i < s.size(); ++i) {
		if(s[i] == c && i != begin) {
			res.push_back(s.substr(begin, i - begin));
			begin = i + 1;
		}
	}
	if (begin != res.size()) {
		res.push_back(s.substr(begin));
	}
	return res;
}