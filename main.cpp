#include <iostream>
#include <map>
#include <iterator>
#include <limits>

template<typename K, typename V>
class interval_map
{

public:
	using MapIter = typename std::map<K,V>::iterator;

	explicit interval_map(const V& val){
		startVal=val;
		mMap.insert(mMap.end(), std::make_pair(std::numeric_limits<K>::lowest(),val));
	}

	void assign(const K& keyBegin, const K& keyEnd, const V& val){
		if(!(keyBegin< keyEnd)){
			//тут можно выбросить исключение,вернуть код ошибки и логировать введение пустого интервала
		}
		if((--mMap.upper_bound(keyBegin))->second == val &&(keyEnd < (mMap.upper_bound(keyEnd)->first))){
			MapIter upEnd = mMap.upper_bound(keyEnd);
			MapIter lowEnd = mMap.lower_bound(keyEnd);
			MapIter dEnd;
			MapIter delBegin;
			MapIter lowBegin = mMap.lower_bound(keyBegin);

			delBegin=lowBegin;

			if(lowEnd == upEnd){
				lowEnd--;
			}
			dEnd = lowEnd;
			mMap.erase(delBegin, ++dEnd);
		}else{


			MapIter upBegin = mMap.upper_bound(keyBegin);
			MapIter lowBegin = mMap.lower_bound(keyBegin);
			MapIter delBegin;

			K startKey;

			delBegin=lowBegin;
			startKey = lowBegin->first;

			if(--lowBegin != mMap.end()){
				startKey=lowBegin->first;
			}

			MapIter upEnd = mMap.upper_bound(keyEnd);
			MapIter lowEnd = mMap.lower_bound(keyEnd);
			MapIter dEnd;

			K endKey;

			if(lowEnd == upEnd){
				lowEnd--;
			}
			dEnd = lowEnd;

			V lastVal = dEnd->second;
			endKey =lowEnd->first;

			mMap.erase(delBegin, ++dEnd);

			mMap.insert(std::begin(mMap),std::make_pair(keyBegin, val));
			mMap.insert(std::begin(mMap),std::make_pair(keyEnd, lastVal));

			MapIter startIter =mMap.find(startKey);
			MapIter endIter =mMap.find(endKey);
			V secondVal= startIter->second;
			startIter++;
			endIter++;

			while(startIter != endIter){

				if(startIter->second == secondVal){
					MapIter delIt= startIter;
					startIter++;
					mMap.erase(delIt);
				}else {
					secondVal= startIter->second;
					startIter++;
				}
			}
		}
	}

	const V& operator[](const K& key) const {
		return (--mMap.upper_bound(key))->second;
	}

	int mapSize(){
		return mMap.size();
	}
private:
	std::map<K,V> mMap;
	V startVal;

};
using namespace std;

int main()
{
	interval_map<unsigned int,char> inMap('A');
//		inMap.assign(2,8,'d');
//		inMap.assign(5,10,'d');
//		inMap.assign(10,20,'C');
//		inMap.assign(12,13,'C');
//		inMap.assign(20,30,'W');
//		inMap.assign(30,40,'X');
//		inMap.assign(32,37,'X');
//		inMap.assign(33,35,'+');
//		inMap.assign(40,45,'W');


//	cout << endl;

//	for(int i=-1;i<50;i++)
//		cout << inMap[i] <<" "<<i<<" = i  "<< "map size = "<<inMap.mapSize()<<endl;
	return 0;
}








