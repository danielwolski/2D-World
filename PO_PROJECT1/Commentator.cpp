#include "Commentator.h"

string Commentator::text = "";

void Commentator::addComment(string comment)
{
	text += comment + "\n";
}

void Commentator::comment()
{
	if (text == "")
		return;
	cout << text;
}

void Commentator::clearComment()
{
	text = "";
}
