#ifndef HELL0_HEADER
#define HELL0_HEADER

#include <Windows.h>
#include <process.h>

#include <iostream>

namespace hell0w0rld {
	template <typename a>
	struct Character {
		a character;
		hell0w0rld::Character<a> *next;

		void display();
	};

	template <typename b>
	class Word : protected Character<b> {
		public:
			hell0w0rld::Character<b> *chars;
			hell0w0rld::Word<b> *next;
			int length;

			Word();
			~Word();
			hell0w0rld::Character<b> &getNext();

			void addCharacter(char);
			void display();
	};

	template <typename c>
	class Sentence : protected Word<c> {
		private:
			hell0w0rld::Word<c> *words;
			int length;

		public:
			Sentence();
			void addSpace();
			void addSymbol(char);
			void addWord(char *, int);
			void clear();
	
			void display();
	};

	void display(const char *);
	void newLine();
}

/*
	hell0w0rld namespace functions 
*/
#pragma region hell0w0rld namespace functions

void hell0w0rld::display(const char *string) {
	HANDLE stdOutput;

	if ((stdOutput = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE){
		MessageBoxA(NULL, "STD_OUTPUT not available!", "Error", MB_OK);
	}
	else {
		AttachConsole(ATTACH_PARENT_PROCESS);
		unsigned long cChars;
		WriteConsoleA(stdOutput, string, 1, &cChars, NULL);
	}
}

void hell0w0rld::newLine() {
	const char *newLineChar = "\n";
	hell0w0rld::display(newLineChar);
}

#pragma endregion

/*
	Character class functions
*/
#pragma region Character class functions

template <typename a> void hell0w0rld::Character<a>::display() {
	hell0w0rld::display(character);
}

#pragma endregion

/*
	Word class functions
*/
#pragma region Word class functions

template <typename b> hell0w0rld::Word<b>::Word() {
	chars = new hell0w0rld::Character<b>;
	chars->next = 0;
	length = 0;
}
template <typename b> hell0w0rld::Word<b>::~Word() {
	hell0w0rld::Character<b> *pointer = chars;

	for(int i = 0; i < length; ++i) {
		if (pointer != 0) {
			hell0w0rld::Character<b> *old = pointer;

			pointer = old->next;
			delete old;
			old = 0;
		}
	}

	chars = 0;
}
template <typename b> hell0w0rld::Character<b> &hell0w0rld::Word<b>::getNext() {
	return next;
}
template <typename b> void hell0w0rld::Word<b>::addCharacter(char input) {
	hell0w0rld::Character<b> *pointer = chars;

	if (length == 0) {
		pointer->character = input;
		pointer->next = 0;
		length++;
	}
	else {
		while (pointer->next != 0) {
			pointer = pointer->next;
		}
		if (pointer->next == 0) {
			pointer->next = new hell0w0rld::Character<b>;
			pointer = pointer->next;
			pointer->character = input;
			pointer->next = 0;
		}

		length++;
	}
}
template <typename b> void hell0w0rld::Word<b>::display() {
	hell0w0rld::Character<b> *pointer = chars;

	for (int i = 0; i < length; ++i) {
		char *outputChar = &pointer->character;
		hell0w0rld::display((const char *)outputChar);
		pointer = pointer->next;
	}
}

#pragma endregion

/*
	Sentence class functions
*/
#pragma region Sentence class functions

template <typename c> hell0w0rld::Sentence<c>::Sentence() {
	words = new hell0w0rld::Word<c>;
	length = 0;
}
template <typename c> void hell0w0rld::Sentence<c>::addSpace() {
	hell0w0rld::Word<c> *pointer = words;

	if (this->length == 0) {
		pointer->addCharacter(' ');

		pointer->next = 0;

		this->length++;
	}
	else {
		while (pointer->next != 0) {
			pointer = pointer->next;
		}
		if (pointer->next == 0) {
			pointer->next = new hell0w0rld::Word<c>;
			pointer = pointer->next;
			pointer->addCharacter(' ');
			pointer->next = 0;
		}

		this->length++;
	}
}
template <typename c> void hell0w0rld::Sentence<c>::addSymbol(char input) {
	hell0w0rld::Word<c> *pointer = words;

	if (this->length == 0) {
		pointer->addCharacter(input);

		pointer->next = 0;

		this->length++;
	}
	else {
		while (pointer->next != 0) {
			pointer = pointer->next;
		}
		if (pointer->next == 0) {
			pointer->next = new hell0w0rld::Word<c>;
			pointer = pointer->next;
			pointer->addCharacter(input);
			pointer->next = 0;
		}

		this->length++;
	}
}
template <typename c> void hell0w0rld::Sentence<c>::addWord(char *input, int length) {
	hell0w0rld::Word<c> *pointer = words;

	if (this->length == 0) {
		for (int i = 0; i < length; ++i) {
			pointer->addCharacter(input[i]);
		}

		pointer->next = 0;

		this->length++;
	}
	else {
		while (pointer->next != 0) {
			pointer = pointer->next;
		}
		if (pointer->next == 0) {
			pointer->next = new hell0w0rld::Word<c>;
			pointer = pointer->next;
			for (int i = 0; i < length; ++i) {
				pointer->addCharacter(input[i]);
			}
			pointer->next = 0;
		}

		this->length++;
	}
}
template <typename c> void hell0w0rld::Sentence<c>::display() {
	hell0w0rld::Word<c> *pointer = words;

	for (int i = 0; i < this->length; ++i) {
		pointer->display();
		pointer = pointer->next;
	}
}
template <typename c> void hell0w0rld::Sentence<c>::clear() {
	hell0w0rld::Word<c> *pointer = words;

	for(int i = 0;i < length; ++i) {
		hell0w0rld::Word<c> *old = pointer;
		pointer = old->next;
		old->~Word();
	}

	delete words;

	words = new hell0w0rld::Word<c>;
	length = 0;
}

#pragma endregion

#endif