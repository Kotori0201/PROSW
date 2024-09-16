#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
#include<algorithm>
#include<math.h>
using namespace std;

class Post {
public:
	int id, numtag;
	string tags[5];
	Post() {};
	void setPost(int a, int b)
	{
		id = a;
		numtag = b;
	}
}poolpost[1000005];

int indx;
unordered_map<string, vector<int> > taghash;
unordered_map<int, int> hashid;
string tmp[5];

void init(int N, int mPostingIDs[], int mHashTagNum[], char mHashTags[][5][10])
{
	hashid.clear();
	taghash.clear();
	indx = 1;
	int tmpnum[1000];
	//for (int i = N - 1; i >= 0; i--)
	//{
	//	tmpnum[i] = mHashTagNum[i];
	//}
	for (int i = N - 1; i >= 0; i--)
	{
		hashid[mPostingIDs[i]] = indx;
		poolpost[indx].setPost(mPostingIDs[i], mHashTagNum[i]);
		//cout << *(&mHashTagNum[i]) << endl;
		int k = int(mHashTagNum[i]);
		for (int j = 0; j < mHashTagNum[i]; j++)
		{
			tmp[j] = "";
			tmp[j] = mHashTags[i][j];
			//string s = mHashTags[i][j];
			//cout << s << " ";
		}
		//cout << endl;
		sort(tmp, tmp + mHashTagNum[i]);

		for (int j = 0; j < mHashTagNum[i]; j++)
		{
			string s = tmp[j];
			poolpost[indx].tags[j] = s;
			taghash[s].push_back(poolpost[indx].id);
			for (int k = j + 1; k < mHashTagNum[i]; k++)
			{
				s = s + tmp[k];
				taghash[s].push_back(poolpost[indx].id);
			}

		}
		indx++;
	}
}

void addPosting(int mID, int mHashTagNum, char mHashTags[][10])
{

	poolpost[indx].setPost(mID, mHashTagNum);
	hashid[mID] = indx;
	for (int i = 0; i < mHashTagNum; i++)
	{
		tmp[i] = mHashTags[i];
	}
	sort(tmp, tmp + mHashTagNum);

	for (int i = 0; i < mHashTagNum; i++)
	{
		string s = tmp[i];
		poolpost[indx].tags[i] = s;
		taghash[s].push_back(poolpost[indx].id);
		for (int j = i + 1; j < mHashTagNum; j++)
		{
			s += tmp[j];
			taghash[s].push_back(poolpost[indx].id);
		}
	}

	indx++;
}

void removePosting(int mID)
{
	int ind = hashid[mID];
	for (int i = 0; i < poolpost[ind].numtag; i++)
	{
		string s = poolpost[ind].tags[i];
		for (int index = 0; index < taghash[s].size(); index++)
		{
			if (taghash[s][index] == mID)
			{
				taghash[s].erase(taghash[s].begin() + index);
				break;
			}
		}

		for (int j = i + 1; j < poolpost[ind].numtag; j++)
		{
			s += poolpost[ind].tags[j];
			for (int index = 0; index < taghash[s].size(); index++)
			{
				if (taghash[s][index] == mID)
				{
					taghash[s].erase(taghash[s].begin() + index);
					break;
				}
			}
		}
	}
}


int findPostingList(int M, char mKeyWords[][10], int mPageNum, int mAnsIDs[])
{
	string s = "";
	if (M == 1)
	{
		s = mKeyWords[0];
	}
	else
	{
		for (int i = 0; i < M; i++)
		{
			tmp[i] = mKeyWords[i];
		}
		sort(tmp, tmp + M);
		s = tmp[0] + tmp[1];
	}

	int left = (mPageNum - 1) * 10;
	if (left >= taghash[s].size())
		return 0;

	int right = left + 10;
	if (right > taghash[s].size())
	{
		right = taghash[s].size();
	}

	int res = 0;
	int ans[10];
	for (int i = left; i < right; i++, res++)
	{
		mAnsIDs[res] = taghash[s][taghash[s].size() - 1 - i];
		ans[res] = taghash[s][taghash[s].size() - 1 - i];
	}
	//int res = right - left;
	return res;
}
