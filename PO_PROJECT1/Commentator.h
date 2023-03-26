#pragma once
#include <iostream>

using namespace std;

class Commentator
{
public:
	static void addComment(string comment);
	static void comment();
	static void clearComment();
protected:
	static string text;
};
