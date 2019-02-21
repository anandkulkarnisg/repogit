#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<memory>
#include<chrono>

using namespace std;

constexpr bool isDebugEnabled() { return false; }

class PersonalInfo
{
	private:
		long m_personalId;
		std::string m_ageInfo;
		std::string m_personalInfo;

	public:
		PersonalInfo(const long& personalId, const std::string& ageInfo, const std::string& personalInfo)
		{
			if(isDebugEnabled())
				cout << "I am being constructed" << endl;
			m_personalId = personalId;
			m_ageInfo = ageInfo;
			m_personalInfo = personalInfo;			
		}

		PersonalInfo(const PersonalInfo& copyItem)
		{
			if(isDebugEnabled())
				cout << "I am being copied" << endl;
			this->m_personalId = copyItem.m_personalId;
			this->m_ageInfo = copyItem.m_ageInfo;
			this->m_personalInfo = copyItem.m_personalInfo;	
		}	

		PersonalInfo& operator=(const PersonalInfo& assignItem)
		{
			if(&assignItem != this)
			{
				this->m_personalId = assignItem.m_personalId;
				this->m_ageInfo = assignItem.m_ageInfo;
				this->m_personalInfo = assignItem.m_personalInfo;
			}

			return(*this);
		}


		PersonalInfo(PersonalInfo&& moveItem)
		{
			if(isDebugEnabled())
				cout << "I am being moved" << endl;
			m_personalId = moveItem.m_personalId;	
			m_ageInfo = std::move(moveItem.m_ageInfo);
			m_personalInfo = std::move(moveItem.m_personalInfo);
		}

};


class FileLoader
{

	private:
		std::string m_fileName;
		char m_seperator;	
		vector<PersonalInfo> results;

	public:
		FileLoader(const std::string& fileName, const char& lineSeperator, const long& reserveSize)
		{
			m_fileName = fileName;
			m_seperator = lineSeperator;
			results.reserve(reserveSize);
		}

		vector<PersonalInfo> loadByPushBack()
		{
			ifstream ifs(m_fileName);
			std::string text;
			text.clear();

			while(!ifs.eof())
			{
				getline(ifs, text);
				if(text.length() > 0)
				{
					std::size_t firstPos = text.find(m_seperator);
					long personalId = std::stol(text.substr(0,firstPos));
					std::size_t secondPos = text.find(m_seperator, firstPos+1);
					std::string ageInfo = text.substr(firstPos+1,secondPos-firstPos-1);
					std::string personalInfo = text.substr(secondPos+1, text.length()-(secondPos-firstPos+1));
					results.push_back(PersonalInfo(personalId, ageInfo, personalInfo));
				}
			}

			ifs.close();
			return(results);
		}

		vector<PersonalInfo> loadByEmplaceBack()
		{
			ifstream ifs(m_fileName);
			std::string text;
			text.clear();

			while(!ifs.eof())
			{
				getline(ifs, text);
				if(text.length() > 0)
				{
					std::size_t firstPos = text.find(m_seperator);
					long personalId = std::stol(text.substr(0,firstPos));
					std::size_t secondPos = text.find(m_seperator, firstPos+1);
					std::string ageInfo = text.substr(firstPos+1,secondPos-firstPos-1);
					std::string personalInfo = text.substr(secondPos+1, text.length()-(secondPos-firstPos+1));
					results.emplace_back(personalId, ageInfo, personalInfo);
				}
			}

			ifs.close();
			return(results);
		}
};

int main(int argc, char* argv[])
{

	std::shared_ptr<FileLoader> loader(new FileLoader("testData.txt", ',', 10000000));
	std::chrono::high_resolution_clock::time_point t1 , t2;
	std::string mode;
	t1 = std::chrono::high_resolution_clock::now();
	if(argc > 1 && atoi(argv[1]) == 1)
	{
		mode = "push_back";
		loader->loadByPushBack();	
	}
	else
	{
		mode = "emplace_back";
		loader->loadByEmplaceBack();
	}
	t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();	
	cout << "duration using " << mode  << " = " << duration << " milli secs." << endl;
	return(0);
}
