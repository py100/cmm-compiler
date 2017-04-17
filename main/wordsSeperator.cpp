#include <bits/stdc++.h>
#include "constants.h"


using namespace std;

class Scanner{
public:

	FILE *fp_r, *fp_w;

	int bufferTop;
	char buffer[BUFFER_SIZE];
	char thisWord[BUFFER_SIZE];

	map<string, TokenType> table;

	vector< pair<int,string> > tokens;

	char nextChar() {
		if (bufferTop > 0) {
			return buffer[--bufferTop];
		}
		return fgetc(fp_r);
	}

	void backForword(char now) {
		buffer[bufferTop++] = now;
	}

	void findWord(TokenType tokenType, const char *word) {
		fprintf(fp_w, "(%d, %s)\n", (int)tokenType, word);
		tokens.push_back( {(int)tokenType, string(word)} );
	}

	// todo simplify
	bool isSpace(char now) {
		return now == ' ' || now == '\n' || now == '\t';
	}

	bool isAlpha(char now) {
		return (now >= 'A' && now <= 'Z') || (now >= 'a' && now <= 'z') || now == '_';
	}

	bool isDigit(char now) {
		return now >= '0' && now <= '9';
	}

	map<string, int> signTable; int signs;

	Scanner() {}

	void init() {

		fp_r = fopen("test.c", "r");
		fp_w = fopen("words.txt", "w");
		bufferTop = 0;
		for (int i = 0; i < KEYWORD_NUM; i++) {
			string str = string(keywordList[i]);
			table[str] = (TokenType)i;
		}
	}

	void close() {
		fclose(fp_r);
		fclose(fp_w);
	}

	vector< pair<int,string> > scan() {

		char ch;
		int signs = 0;
		int wordLen;

		while((ch = nextChar()) != EOF) {

			printf("%c\n", ch);

			if (isSpace(ch)) {
				while(isSpace(ch)) ch = nextChar();
				backForword(ch);
			}

			else if (isAlpha(ch)) {
				wordLen = 0;

				while(isAlpha(ch) || isDigit(ch)) {
					thisWord[wordLen++] = ch;
					ch = nextChar();
				}

				thisWord[wordLen] = 0;
				backForword(ch);

				if (table.count(string(thisWord))) {
					findWord(table[string(thisWord)], thisWord);
				}
				else {
					findWord(T_IDENTIFER, thisWord);
					if (!signTable.count(string(thisWord))) {
						signTable[string(thisWord)] = ++signs;
					}
				}

			}
			else if (isDigit(ch)) {
				bool isReal = 0;
				wordLen = 0;
				while(isDigit(ch) || ch == '.') {
					if (ch == '.') {
						if (isReal) {
							backForword('.');
							break;
						}
						else {
							isReal = true;
							thisWord[wordLen++] = ch;
						}
					}
					else {
						thisWord[wordLen++] = ch;
						ch = nextChar();
					}
				}
				thisWord[wordLen] = 0;
				backForword(ch);

				if (isReal) {
					findWord(FLOAT_VAL, thisWord);
				}
				else {
					findWord(INT_VAL, thisWord);
				}
			}
			else {
				switch(ch) {
					case '*':
						switch(ch = nextChar()) {
							case '=':
								findWord(OP_OTHERS, "*=");
								break;

							default:
								backForword(ch);
								findWord(OP_MUL, "*");
								break;
						}
						break;

					case '/':
						switch(ch = nextChar()) {
							case '=':
								findWord(OP_OTHERS, "/=");
								break;

							default:
								backForword(ch);
								findWord(OP_DIV, "/");
								break;
						}
						break;

					case '%':
						switch(ch = nextChar()) {
							case '=':
								findWord(OP_OTHERS, "%=");
								break;

							default:
								backForword(ch);
								findWord(OP_MOD, "%");
								break;
						}
						break;

					case '+':
						switch(ch = nextChar()) {
							case '=':
								findWord(OP_OTHERS, "+=");
								break;

							case '+':
								findWord(OP_SADD, "++");
								break;

							default:
								backForword(ch);
								findWord(OP_ADD, "+");
								break;
						}
						break;


					case '-':
						switch(ch = nextChar()) {
							case '=':
								findWord(OP_OTHERS, "-=");
								break;

							case '-':
								findWord(OP_SSUB, "--");
								break;

							default:
								backForword(ch);
								findWord(OP_SUB, "-");
								break;
						}
						break;

					case '<':
						switch(ch = nextChar()) {
							case '=':
								findWord(OP_LE, "<=");
								break;

							default:
								backForword(ch);
								findWord(OP_LT, "<");
								break;
						}
						break;


					case '>':
						switch(ch = nextChar()) {
							case '=':
								findWord(OP_GE, ">=");
								break;

							default:
								backForword(ch);
								findWord(OP_GT, ">");
								break;
						}
						break;

					case '=':
						switch(ch = nextChar()) {
							case '=':
								findWord(OP_EQ, "==");
								break;

							default:
								backForword(ch);
								findWord(OP_ASS, "=");
								break;
						}
						break;

					case '!':
						switch(ch = nextChar()) {
							case '=':
								findWord(OP_NE, "!=");
								break;

							default:
								backForword(ch);
								findWord(OP_NOT, "!");
								break;
						}
						break;

					case '|':
						switch(ch = nextChar()) {
							case '|':
								printf("wowwowo === |\n");
								findWord(OP_OR, "||");
								break;

							default:
								backForword(ch);
								findWord(OP_OTHERS, "|");
								break;
						}
						break;

					case '&':
						switch(ch = nextChar()) {
							case '&':
								findWord(OP_AND, "&&");
								break;

							default:
								backForword(ch);
								findWord(OP_OTHERS, "&");
								break;
						}
						break;

					case '\"':
						findWord(DQ, "\"");
						wordLen = 0;
						ch = nextChar();
						while(ch != '\"') {
							thisWord[wordLen++] = ch;
							ch = nextChar();
						}
						thisWord[wordLen] = 0;
						findWord(CONST_STR, thisWord);
						findWord(DQ, "\"");
						break;

					case '\'':
						findWord(SQ, "\'");
						break;

					case '(':
						findWord(LEFT_BRA, "(");
						break;

					case ')':
						findWord(RIGHT_BRA, ")");
						break;

					case '[':
						findWord(LEFT_INDEX, "[");
						break;

					case ']':
						findWord(RIGHT_INDEX, "]");
						break;

					case '{':
						findWord(L_BOUNDER, "{");
						break;

					case '}':
						findWord(R_BOUNDER, "}");
						break;
					case ':':
						findWord(F_CON, ":");
						break;
					case ';':
						findWord(F_SEMIC, ";");
						break;
					case ',':
						findWord(F_COMMA, ";");
						break;
				}

			}

		}

		findWord(F_EOF, "#");
		fprintf(fp_w, "\n");

		for (auto psi : signTable) {
			fprintf(fp_w, "%s %d\n", psi.first.c_str(), psi.second);
		}
		return tokens;
	}

};


/*
int main() {

	scanner.init();
	scanner.scan();
	scanner.close();

	cout << "words finished" << endl;

	return 0;
}
*/