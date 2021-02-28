/*** Functions ***/
#include <algorithm>
#include <functional> // for hash
#include <climits>	  // all useful constants
#include <cmath>
#include <cstdio>
#include <cstdlib> // random
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip> // right justifying std::right and std::setw(width)
/*** Data Structure ***/
#include <deque> // double ended queue
#include <list>
#include <queue> // including priority_queue
#include <stack>
#include <string>
#include <vector>
#include <regex>

using namespace std;

typedef string InputType;

#define DELI "#"

#define NOT_STARTED 0
#define FACT_NAME 1
#define PARA_NAME 2

int match(string reg, string db)
{
	smatch m;
	regex regEx(reg);
	int count = 0;
	auto it = sregex_iterator(db.begin(), db.end(), regEx);
	return distance(it, sregex_iterator());
}

void readInput()
{
	char c;
	unsigned state = FACT_NAME;
	string formated_db = DELI;
	bool last_new_line = false;
	// Do parsing fact here
	while (c = getchar())
	{
		if (c == '\n')
		{
			// CHeck blank line
			c = getchar();
			if (c == '\n')
			{
				// End of fact parsing
				break;
			}
		}
		// Keep parsing
		if (c == ' ')
		{
			// No space please
			continue;
		}
		else if (c == ')')
		{
			// End of a fact
			// Close and prepare for next fact
			formated_db += ")#";
		}
		else
		{
			formated_db.push_back(c);
		}
	}
	// Remove last deli
	formated_db.pop_back();
	// Do queries parsing
	state = FACT_NAME;
	string buff = DELI;
	while ((c = getchar()) != EOF)
	{
	PARSING_DOWN_HERE:
		if(c == '\n')
		{
			continue;
		}
		if (c == ' ')
		{
			// filtering space out
			continue;
		}
		else if (c == '(')
		{
			state = PARA_NAME;
			// Add the piece, ( is special regex so gotta escape
			buff += "\\(";
		}
		else if (c == ')')
		{
			// Done parsing a queries add last piece, do the search and restart
			// Add last piece, ) is special regex so gotta escape
			buff += "\\)";
			// We have a full regex here do search
			cout << match(buff, formated_db) << endl;
			// Restart
			state = FACT_NAME;
			buff = DELI;
		}
		else
		{
			if (state == FACT_NAME)
			{
				// Keep factname as it
				buff += c;
			}
			else
			{
				// state == PARA_NAME
				if ((buff[buff.size() - 1] == '(' || buff[buff.size() - 1] == ',') && c == '_')
				{
					// First legit character of a variable, change that to regex
					buff += "[A-Za-z0-9]*";
					// Skip the rest
					while (1)
					{
						c = getchar();
						if (c == ',')
						{
							// We have another name in the para list, so end the current para, read one new and repeat the para parsing
							buff += ',';
							c = getchar();
							goto PARSING_DOWN_HERE;
						}
						else if (c == ')')
						{
							// End of the queries
							goto PARSING_DOWN_HERE;
						}
						// Skip the rest of the para name if it is a variable
					}
				}
				else
				{
					buff +=c;
				}
			}
		}
	}
}

template <typename T>
void printOutput(T output, int TestCaseNum)
{
	cout << "Case #" << TestCaseNum << ": " << output << endl;
}

int main()
{
	readInput();
	return 0;
}
