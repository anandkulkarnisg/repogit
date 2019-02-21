#include <bits/stdc++.h>
#include <map>

using namespace std;

// Complete the sherlockAndAnagrams function below.
int sherlockAndAnagrams(const string& inputString) 
{
    map<string, int> m_map;
    string t;
    for (int i = 0; i < inputString.length(); ++i)
        {
            for (int l = 1; i + l - 1 < inputString.length(); ++l)
            {
                t = inputString.substr(i, l);
                sort(t.begin(), t.end());
                m_map[t]++;
            }
        }
    
    int ans = 0;

	for(const auto& iter : m_map)
		cout << iter.first << " , " << iter.second << endl;

    for (const auto& iter : m_map)
        ans += (iter.second) * (iter.second - 1) / 2;
    return(ans);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = sherlockAndAnagrams(s);
        fout << result << "\n";
		cout << result << endl;
    }

    fout.close();

    return 0;
}

