#include<unordered_map>
#include<queue>
#include<set>
using namespace std;


class address {
public:
	int start, end;
	int value;
};

class file {
public:
	int id;
	vector<pair<int, int>> vitri;
}poolfile[12003];

struct CMP {
	bool operator()(address a, address b) const
	{
		return a.start > b.start;
	}
};

int n, indfile, remain_size;
unordered_map<int, int> hashid;



priority_queue<address, vector<address>, CMP> pq; // remaining empty storage

void init(int N) {
	n = remain_size = N;
	indfile = 0;
	pq = priority_queue < address, vector<address>, CMP>();
	hashid.clear();
	address tmp;
	tmp.start = 1;
	tmp.end = N;
	tmp.value = N;
	pq.push(tmp);
	return;
}

int add(int mId, int mSize) {
	
	if (remain_size < mSize)
	{
		return -1;
	}

	indfile++;
	hashid[mId] = indfile;
	poolfile[indfile].id = mId;
	poolfile[indfile].vitri.clear();
	int cur_start = 25000000;
	while (mSize > 0 && !pq.empty())
	{
		auto tmp = pq.top();	pq.pop();
		if (tmp.value <= mSize)
		{
			remain_size -= tmp.value;
			mSize -= tmp.value;
			if (cur_start > tmp.start)
			{
				cur_start = tmp.start;
			}
			poolfile[indfile].vitri.push_back(make_pair(tmp.start, tmp.end));
		}
		else
		{
			remain_size -= mSize;
			tmp.value -= mSize;
			if (cur_start > tmp.start)
			{
				cur_start = tmp.start;
			}
			poolfile[indfile].vitri.push_back(make_pair(tmp.start, tmp.start + mSize - 1));
			tmp.start += mSize;
			mSize = 0;
			pq.push(tmp);
		}
	}

	return cur_start;
}

int remove(int mId) {
	int ind = hashid[mId];
	int res = poolfile[ind].vitri.size();
	for (auto a : poolfile[ind].vitri)
	{
		address tmp;
		tmp.start = a.first;
		tmp.end = a.second;
		tmp.value = a.second - a.first + 1;
		remain_size += tmp.value;
		pq.push(tmp);
	}

	return res;
}

int count(int mStart, int mEnd) {

	return 0;
}