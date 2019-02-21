#include<iostream>
#include<string>
#include<map>

using namespace std;

class Trie
{
	private:
		class TrieNode
		{
			public:
				map<char,TrieNode*> m_children;
				bool m_isComplete;
				TrieNode()
				{
					m_children=map<char,TrieNode*>();
					m_isComplete=false;
				}
		};

		TrieNode* m_root;
	public:
		Trie()
		{
			m_root=new TrieNode();
		}

		void insertWord(const std::string& word)
		{
			TrieNode* trieRootNode = m_root;
			for(const auto& iter : word)
			{
				TrieNode* node = trieRootNode->m_children.find(iter)->second;
				if(node == nullptr)
				{
					node = new TrieNode();
					node->m_children[iter]=node;
				}
				else
				{
					const auto& mapIter = node->m_children.find(iter);
					if(mapIter != node->m_children.end())
						node->m_children[iter]=node;
				}

				*trieRootNode = *node;
				trieRootNode = node->m_children.find(iter)->second;
			}
			trieRootNode->m_isComplete=true;
		}
		void show()
		{
			TrieNode* TrieNodeIter = m_root;
			while(TrieNodeIter->m_isComplete!=true)
			{
				cout << TrieNodeIter->m_children.begin()->first;
				TrieNodeIter = TrieNodeIter->m_children.begin()->second;
			}	
			cout << '\n';
		}
};

int main(int argc, char* argv[])
{
	Trie sampleTrie;
	sampleTrie.insertWord("AbracaDabra");
	sampleTrie.insertWord("Anand");
	sampleTrie.show();
	return(0);
}
