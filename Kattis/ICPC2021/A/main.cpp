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

vector<string> extractParaList(string s)
{
	int beg = s.find('(');
	int len = s.find(')') - beg + 1;
	s = s.substr(beg + 1, len - 2); // Dont get the ()
	vector<string> para;
	while (1)
	{
		beg = s.find(',');
		if (beg == string::npos)
		{
			para.push_back(s);
			break;
		}
		else
		{
			para.push_back(s.substr(0, beg));
			s = s.substr(beg + 1, s.size() - (beg + 1));
		}
	}
	return para;
}

int match(string full, string reg, string db)
{
	smatch m;
	regex regEx(reg);
	vector<string> potential;
	int count = 0;
	auto it1 = sregex_iterator(db.begin(), db.end(), regEx);
	auto listEnd = sregex_iterator();
	for (; it1 != listEnd; it1++)
	{
		potential.push_back(smatch(*it1).str());
	}
	if (potential.size() == 0)
	{
		return 0;
	}
	else
	{
		vector<string> queryPara = extractParaList(full);
		map<string, vector<int>> dict;
		for (unsigned i = 0; i < queryPara.size(); i++)
		{
			if (queryPara[i][0] == '_')
			{
				dict[queryPara[i]].push_back(i);
			}
		}
		for (auto m = potential.begin(); m != potential.end(); m++)
		{
			vector<string> matchpara = extractParaList(*m);
			// cout << *m << endl;
			// for (auto i = 0; i < matchpara.size(); i++)
			// {
			// 	cout << matchpara[i] << " ";
			// }
			// cout << endl;
			bool eachParaMatch = true;
			for (auto p = dict.begin(); p != dict.end(); p++)
			{
				// cout<<"Key: "<< p->first<<endl;
				if (p->first.size() != 1)
				{
					// for (auto i = 0; i < p->second.size(); i++)
					// {
					// 	cout << p->second[i] << " ";
					// }
					// cout << endl;
					bool same = true;
					for (auto i = 0; i < p->second.size(); i++)
					{
						// cout<<"matchpara[i]: "<<matchpara[p->second[0]]<<endl;
						if (matchpara[p->second[0]].compare(matchpara[p->second[i]]) != 0)
						{
							same = false;
							break;
						}
					}
					if (!same)
					{
						eachParaMatch = false;
						break;
					}
				}
			}
			if (eachParaMatch)
			{
				count++;
			}
		}
	}
	return count;
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
	string buffNoRegEx = DELI;
	map<string, int> varCount;
	while ((c = getchar()) != EOF)
	{
	PARSING_DOWN_HERE:
		if (c == '\n')
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
			buffNoRegEx += '(';
		}
		else if (c == ')')
		{
			// Done parsing a queries add last piece, do the search and restart
			// Add last piece, ) is special regex so gotta escape
			buff += "\\)";
			buffNoRegEx += ')';
			// We have a full regex here do search
			cout << match(buffNoRegEx, buff, formated_db) << endl;
			// Restart
			state = FACT_NAME;
			buff = DELI;
			buffNoRegEx = DELI;
		}
		else
		{
			if (state == FACT_NAME)
			{
				// Keep factname as it
				buff += c;
				buffNoRegEx += c;
			}
			else
			{
				// state == PARA_NAME
				if ((buff[buff.size() - 1] == '(' || buff[buff.size() - 1] == ',') && c == '_')
				{
					// First legit character of a variable, change that to regex
					buff += "[A-Za-z0-9]*";
					buffNoRegEx += '_';
					// Skip the rest
					while (1)
					{
						c = getchar();
						if (c == ',')
						{
							// We have another name in the para list, so end the current para, read one new and repeat the para parsing
							buff += ',';
							buffNoRegEx += ',';
							c = getchar();
							goto PARSING_DOWN_HERE;
						}
						else if (c == ')')
						{
							// End of the queries
							goto PARSING_DOWN_HERE;
						}
						else
						{
							buffNoRegEx += c;
						}
						// Skip the rest of the para name if it is a variable
					}
				}
				else
				{
					buff += c;
					buffNoRegEx += c;
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
