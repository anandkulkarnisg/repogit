#include<iostream>
#include<vector>
#include<map>
#include<fstream>
#include<algorithm>

using namespace std;

// cat input.txt | sed "s/|/ /g" | sort -k 2 -r

vector<std::string> getSubArray(const vector<std::string>& raceArray, const std::size_t& startPos, const std::size_t& endPos)
{

	vector<std::string> resultArray;
	resultArray.reserve(5);

	for(unsigned int i=startPos; i<=endPos; ++i)
		resultArray.push_back(raceArray[i]);	

	return(resultArray);
}

vector<std::string> getRaceResult(vector<std::string> subArray, const map<std::string,float>& horseSpeedMap)
{
	vector<std::string> results;
	vector<float> speeds;

	results.reserve(5);
	speeds.reserve(5);

	for(auto iter : subArray)
	{
		float speed = horseSpeedMap.find(iter)->second;
		speeds.push_back(speed);
	}	

	std::sort(speeds.begin(), speeds.end(), std::greater<float>());

	for(auto iter : speeds)
	{
		for(auto iter2 : horseSpeedMap)
		{
			if(iter2.second == iter)
				results.push_back(iter2.first);
		}		
	}

	return(results);

}

int main(int argc, char* argv[])
{

	ifstream ifs(argv[1]);
	std::string text;
	text.clear();
	char Seperator = '|';
	map<std::string,float> horseSpeedMap;

	while(!ifs.eof())
	{
		getline(ifs, text);
		if(!ifs.eof())
		{
			std::size_t indexPos = text.find(Seperator);
			if(indexPos != std::string::npos)
			{
				std::string horseName = text.substr(0,indexPos);
				std::string horseSpeed = text.substr(indexPos+1,text.length());	
				if(horseSpeed != "Speed")
					horseSpeedMap[horseName] = std::stof(horseSpeed);
			}	
		}
	}

	ifs.close();

	// We now have the horses and their speeds read into the map.
	// Conduct races with in a group of five horses. The result of each race is only an order in which horses finished returned as vector.
	// Create a vector of 5 items each and run 5 races.

	vector<std::string> raceArray;
	raceArray.reserve(horseSpeedMap.size());	
	vector<vector<std::string>> raceResults;
	raceResults.reserve(7);
	vector<std::string> fastest;
	fastest.reserve(3);

	for(auto iter : horseSpeedMap)
		raceArray.push_back(iter.first);

//	cout << raceArray.size() << endl;

	std::size_t startPos = 0;
	std::size_t endPos = startPos + 4;

	for(unsigned int i=0; i<5; ++i)
	{
		vector<std::string> race = getRaceResult(getSubArray(raceArray, startPos, endPos), horseSpeedMap);			
		raceResults.push_back(race);

		startPos += 5;
		endPos += 5;

/*		for(auto iter : race)
			cout << iter << " , ";
		cout << endl; */
	}

	// Get an array of winners and race them for another result.
	vector<std::string> winners;
	winners.reserve(5);	

	for(auto iter : raceResults)
		winners.push_back(iter[0]);		

	// Get another race to find the fastest of winners.
	vector<std::string> race = getRaceResult(getSubArray(winners, 0, 4), horseSpeedMap);
/*	for(auto iter : race)
		cout << iter << " , ";
	cout << endl; */

	fastest.push_back(race[0]);
	raceResults.push_back(race);

	// Now we need another race. It will be between the second and third horse of the group where fastest horse belongs.
	// We also need the second fastest and its next in the group.
	// We also need the fastest third horse from its group.

	vector<std::string> finalRaceGroup;
	finalRaceGroup.reserve(5);

	std::string fastestHorse = race[0];
	std::string secondFastest = race[1];
	std::string thirdFastest = race[2];

	for(auto iter : raceResults)
	{
		if(iter[0] == fastestHorse)
		{
			finalRaceGroup.push_back(iter[1]);
			finalRaceGroup.push_back(iter[2]);	
		}		

		if(iter[0] == secondFastest)
		{
			finalRaceGroup.push_back(iter[0]);
			finalRaceGroup.push_back(iter[1]);
		}
		
		if(iter[0] == thirdFastest)
			finalRaceGroup.push_back(iter[0]);
	}

	// Race now.
	race = getRaceResult(getSubArray(finalRaceGroup, 0, 4), horseSpeedMap);
/*	for(auto iter : race)
		cout << iter << " , ";
	cout << endl; */
	fastest.push_back(race[0]);
	fastest.push_back(race[1]);

	cout << "Fastest three horses are = " << fastest[0] << " , " << fastest[1] << " , " << fastest[2] << endl;

	return(0);
}
