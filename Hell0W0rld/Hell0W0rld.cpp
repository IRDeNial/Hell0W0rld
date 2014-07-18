/*
	Not your first hello world program
*/

#include "hell0.h"
#include <conio.h>

int main() {
	hell0w0rld::Sentence<char> sentence;

	sentence.addWord("Hello",5);
	sentence.addSymbol(',');
	sentence.addSpace();
	sentence.addWord("World",5);
	sentence.addSymbol('!');
	sentence.display();
	hell0w0rld::newLine();

	sentence.clear();

	sentence.addWord("I",1);
	sentence.addSpace();
	sentence.addWord("am",2);
	sentence.addSpace();
	sentence.addWord("here",4);
	sentence.addSymbol('!');
	sentence.display();
	hell0w0rld::newLine();

	sentence.clear();

	sentence.addSymbol(':');
	sentence.addSymbol(')');
	sentence.addSpace();
	sentence.addSymbol('<');
	sentence.addSymbol('3');
	sentence.display();
	hell0w0rld::newLine();

	sentence.clear();

	_getch();
	return 0;
}