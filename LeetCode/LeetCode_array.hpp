#pragma once
#include<iostream>
#include<string>
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
