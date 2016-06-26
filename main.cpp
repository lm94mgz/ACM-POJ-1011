#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>
#include <utility>

using namespace std;

typedef int STICK_LENGTH;
typedef bool PROC_TEMPDATA;
typedef vector<pair<STICK_LENGTH, PROC_TEMPDATA>> STICK_CONTAINER;
typedef STICK_CONTAINER::size_type STICK_COUNT;

enum PROC_RESULT{
	SUCCESS = 0,

};

bool fit2Mosaic(
	STICK_CONTAINER &sc,
	STICK_COUNT &needCount,
	STICK_LENGTH &needLen,
	STICK_COUNT &curCount,
	STICK_LENGTH &curLen,
	const STICK_CONTAINER::iterator &countIt,
	STICK_CONTAINER::iterator &lenIt
)
{
	if (curLen + lenIt->first > needLen)
		return false;
	
	lenIt->second = true;
	curLen += lenIt->first;
	if (curLen == needLen)
	{
		curCount++;
		curLen = 0;
		if (curCount == needCount)
			return true;
		else
		{
			STICK_CONTAINER::iterator nextCountIt = countIt + 1;
			while (nextCountIt != sc.end() && nextCountIt->second)
				nextCountIt++;

			if (nextCountIt != sc.end() && fit2Mosaic(sc, needCount, needLen, curCount, curLen, nextCountIt, nextCountIt))
				return true;
			else
			{
				curLen = needLen;
				curCount--;

				curLen -= lenIt->first;
				lenIt->second = false;
				return false;
			}
		}
	}

	for (STICK_CONTAINER::iterator nextLenIt = lenIt + 1; nextLenIt != sc.end(); ++nextLenIt)
	{
		if (!nextLenIt->second)
		{
			if (!(nextLenIt - 1)->second && nextLenIt->first == (nextLenIt - 1)->first)
				continue;
			else if (fit2Mosaic(sc, needCount, needLen, curCount, curLen, countIt, nextLenIt))
				return true;
		}
	}

	curLen -= lenIt->first;
	lenIt->second = false;
	return false;
}


bool juge(STICK_CONTAINER &sc, STICK_COUNT needCount, STICK_LENGTH needLen)
{
	STICK_COUNT curCount = 0;
	STICK_LENGTH curLen = 0;
	STICK_CONTAINER::iterator countIt = sc.begin();
	STICK_CONTAINER::iterator lenIt = sc.begin();
	return fit2Mosaic(sc, needCount, needLen, curCount, curLen, countIt, lenIt);
}

int main()
{
	int count;

	for (cin >> count; count != 0; cin >> count)
	{
		int tmp, sum = 0;
		STICK_CONTAINER input;

		for (int i = 0; i < count; ++i)
		{

			cin >> tmp;
			sum += tmp;
			input.push_back(make_pair(tmp, false));
		}

		sort(input.begin(), input.end(), greater <STICK_CONTAINER::value_type>());

		for (STICK_LENGTH i = input.begin()->first; i <= sum; ++i)
		{
			if (sum%i == 0)
				if(juge(input, sum/i, i))
			{
				cout << i << endl;
				break;
			}
		}
	}

	return 0;
}
