/*
	Not your first hello world program
*/

#include <Windows.h>
#include <process.h>
#include <conio.h>

namespace hell0w0rld {
	template <typename a>
	struct Character {
		a character;
		hell0w0rld::Character<a> *next;
		
		void display() {
			hell0w0rld::display(character);
		}
	};

	template <typename b>
	class Word : public Character<b> {		
		public:
			hell0w0rld::Character<b> *chars;
			hell0w0rld::Word<b> *next;
			int length;

			Word() {
				chars = new hell0w0rld::Character<b>;
				chars->next = 0;
				length = 0;
			}
			~Word() {
				hell0w0rld::Character<b> *pointer = chars;

				while (pointer) {
					hell0w0rld::Character<b> *old = pointer;
					pointer = pointer->next;
					delete old;
				}
			}
			hell0w0rld::Character<b> &getNext() {
				return next;
			}
			void addCharacter(char input) {
				hell0w0rld::Character<b> *pointer = chars;

				if(length == 0) {
					pointer->character = input;
					pointer->next = 0;
					length++;
				} else {
					while(pointer->next != 0) {
						pointer = pointer->next;
					}
					if(pointer->next == 0) {
						pointer->next = new hell0w0rld::Character<b>;
						pointer = pointer->next;
						pointer->character = input;
						pointer->next = 0;
					}

					length++;
				}
			}
			void display() {
				hell0w0rld::Character<b> *pointer = chars;

				for(int i = 0;i < length; ++i) {
					char *outputChar = &pointer->character;
					hell0w0rld::display((const char *)outputChar);
					pointer = pointer->next;
				}
			}
	};

	template <typename c>
	class Sentence : public Word<c> {
		private:
			hell0w0rld::Word<c> *words;
			int length;

		public:
			Sentence() {
				words = new hell0w0rld::Word<c>;
				length = 0;
			}
			void addSpace() {
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
			void addSymbol(char input) {
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
			void addWord(char *input, int length) {
				hell0w0rld::Word<c> *pointer = words;

				if (this->length == 0) {
					for (int i = 0; i < length; ++i) {
						pointer->addCharacter(input[i]);
					}

					pointer->next = 0;
					
					this->length++;
				} else {
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

			void display() {
				hell0w0rld::Word<c> *pointer = words;

				for (int i = 0; i < this->length; ++i) {
					pointer->display();
					pointer = pointer->next;
				}
			}
	};
	
	void display(const char *string) {
		HANDLE stdOutput;

		if ((stdOutput = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE){
			MessageBoxA(NULL, "STD_OUTPUT not available!", "Error", MB_OK);
		} else {
			AttachConsole(ATTACH_PARENT_PROCESS);
			unsigned long cChars;
			WriteConsoleA(stdOutput, string, 1, &cChars, NULL);
		}
	}
}

int main() {
	hell0w0rld::Sentence<char> sentence;

	sentence.addWord("Hello",5);
	sentence.addSymbol(',');
	sentence.addSpace();
	sentence.addWord("World",5);
	sentence.addSymbol('!');
	sentence.display();

	getch();
	return 0;
}