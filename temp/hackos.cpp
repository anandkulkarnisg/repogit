#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the contacts function below.
 */

#include<iostream>
#include<string>
#include<map>

#include<iostream>
#include<string>
#include<map>
#include<utility>
#include<memory>
#include<shared_mutex>
#include<mutex>
#include<vector>
#include<iostream>
#include<string>
#include<map>
#include<utility>
#include<memory>
#include<shared_mutex>
#include<mutex>
#include<vector>

class Trie
{
private:

    // TrieNode is a core node structure of the Trie.
    class TrieNode
    {
    public:
        std::map<char, std::shared_ptr<TrieNode>> m_children;
        bool m_isComplete;
        long m_prefixCount;        // This stores sum of all words at this point as a prefix. Helps in quicker answering of the question how many words are there with a given prefix much faster!
        TrieNode() : m_isComplete(false) , m_prefixCount(0)
        {
        }
    };

    // Root node of the Trie Data Structure.
    std::shared_ptr<TrieNode> m_root;
    size_t m_counter=0;
    size_t m_wordCount=0;

    bool recursiveDelete(std::shared_ptr<TrieNode>, const std::string&, size_t& , const size_t& = 0);
    void recursiveWordSearch(const std::shared_ptr<TrieNode>, const std::string&, std::vector<std::string>&);
    bool isValidPrefixInternal(const std::string&, std::shared_ptr<TrieNode>&, std::shared_ptr<TrieNode>&);

public:
    Trie();
    Trie(const Trie&)=delete;
    Trie& operator=(const Trie&)=delete;

    void insertWord(const std::string&);
    bool isWord(const std::string&);
    std::pair<bool, size_t> deleteWord(const std::string&);
    bool isValidPrefix(const std::string&);
    void getWordsByPrefix(const std::string&, std::vector<std::string>&);
    long getWordCountByPrefix(const std::string&);
    void getAllTrieWords(std::vector<std::string>&);
    bool isEmpty();
    long getTrieSize();
    long getTrieWordCount();
    void debugFunc();
    ~Trie();
};

using namespace std;

Trie::Trie() : m_root(new TrieNode()) 
{
}

void Trie::insertWord(const std::string& word) 
{
    if (word.empty())
        return;

    shared_ptr<TrieNode> currNode = m_root;
    currNode->m_prefixCount++;
    shared_ptr<TrieNode> newNode;

    for (unsigned int i = 0; i < word.length(); ++i) 
    {
        if (currNode->m_children.empty()) 
        {
            newNode = shared_ptr<TrieNode>(new TrieNode());
            if(i<word.length()-1)
                newNode->m_prefixCount++;
            ++m_counter;
            currNode->m_children[word[i]] = newNode;
        } 
        else 
        {
            const auto& iter = currNode->m_children.find(word[i]);
            if (iter == currNode->m_children.end()) 
            {
                newNode = shared_ptr<TrieNode>(new TrieNode());
                newNode->m_prefixCount++;
                ++m_counter;
                currNode->m_children[word[i]] = newNode;
            } 
            else
            {
                newNode = iter->second;
                newNode->m_prefixCount++;
            }
        }
        currNode = newNode;
    }

    newNode->m_isComplete = true;
    ++m_wordCount;
}

bool Trie::isWord(const std::string& word) 
{
    if (word.empty())
        return (false);

    shared_ptr<TrieNode> currNode = m_root;
    for (unsigned int i = 0; i < word.size(); ++i) 
    {
        const auto& iter = currNode->m_children.find(word[i]);
        if (iter == currNode->m_children.end())
            return (false);
        else
            currNode = iter->second;
    }
    return (currNode->m_isComplete);
}

pair<bool, size_t> Trie::deleteWord(const std::string& word) 
{
    size_t modifyCounter=0;
    {
        recursiveDelete(m_root, word, modifyCounter);
    }

    bool returnStatus=false;
    if(modifyCounter>0)
        returnStatus=true;
    return(make_pair(returnStatus, modifyCounter));
}

bool Trie::recursiveDelete(shared_ptr<TrieNode> current, const std::string& word, size_t& modifyCounter, const size_t& index)
{
    // Do not take any locks inside this method. This method is called from deleteWord which is already protected via write Lock!
    if (index == word.length()) 
    {
        if (!current->m_isComplete)
            return (false);

        current->m_isComplete = false;
        ++modifyCounter;
        return (current->m_children.empty());
    }

    char ch = word[index];
    const auto& iter = current->m_children.find(ch);
    if (iter == current->m_children.end())
        return (false);

    size_t beforeModifyCounter=modifyCounter;
    bool shouldDeleteCurrentNode = recursiveDelete(iter->second, word, modifyCounter, index + 1);
    if (shouldDeleteCurrentNode) 
    {
        current->m_children.erase(iter);
        current->m_prefixCount--;
        --m_counter;
        ++modifyCounter;
        //return true if no mappings are left in the map.
        return (current->m_children.empty());
    }
    else
    {
        if(beforeModifyCounter!=modifyCounter)
            current->m_prefixCount--;
    }
    return (false);
}

bool Trie::isEmpty()
{
    return(m_root->m_children.empty());
}

long Trie::getTrieSize()
{
    return(m_counter*sizeof(TrieNode));    
}

bool Trie::isValidPrefixInternal(const string& prefix, shared_ptr<TrieNode>& nodeRef, shared_ptr<TrieNode>& prevRef)
{
    string wordItem;
    std::shared_ptr<TrieNode> current = m_root;

    for(unsigned int i=0; i<prefix.length(); ++i)
    {
        const auto& iter = current->m_children.find(prefix[i]);
        if(iter != current->m_children.end())
        {
            wordItem+=prefix[i];
            prevRef = current;
            current = iter->second;
        }
        else
            return(false);
    }

    if(wordItem!=prefix)
        return(false);

    nodeRef=current;
    return(true);
}

bool Trie::isValidPrefix(const string& prefix)
{
    shared_ptr<TrieNode> nodeRef;
    shared_ptr<TrieNode> prevRef;
    bool returnStatus = isValidPrefixInternal(prefix, nodeRef, prevRef);
    return(returnStatus);
}

void Trie::getWordsByPrefix(const string& prefix, vector<string>& wordList)
{
    // This method searches for all valid strings and returns a vector containing those words in the Trie which are having supplied prefix.
    // if none found the vector will be empty.

    // Check if the prefix is valid only then proceed.
    shared_ptr<TrieNode> prefixNode;
    shared_ptr<TrieNode> prevNode;
    bool prefixStatus = isValidPrefixInternal(prefix, prefixNode, prevNode);

    if(!prefixStatus)
        return;

    // Now we have prefix which is valid then all we need to is recursively search all words from this prefix onwards.
    recursiveWordSearch(prefixNode, prefix, wordList);
}

void Trie::recursiveWordSearch(const shared_ptr<TrieNode> node, const string& passedWord, vector<string>& wordList)
{
    if(node->m_isComplete)
        wordList.push_back(passedWord);

    if(node->m_children.size()==0)
        return;

    for(const auto& iter : node->m_children)
        recursiveWordSearch(iter.second, passedWord+iter.first, wordList);
}


// This is a heavy word search algorithm and must not be used frequently. It has only a rare requirment for debugging purpose.
void Trie::getAllTrieWords(vector<string>& wordList)
{
     // We identify all the characters in the root map as prefixes and then search all words starting with them.
     if(m_root->m_children.size()==0)
         return;

     vector<string> prefixList;
     prefixList.reserve(m_root->m_children.size());
     for(const auto& iter : m_root->m_children)
         prefixList.emplace_back(string(1,iter.first));

     vector<string> prefixWordList;
     prefixWordList.reserve(m_wordCount);

     for(const auto& iter : prefixList)
     {
         prefixWordList.clear();
         getWordsByPrefix(iter,prefixWordList);
         copy(prefixWordList.begin(), prefixWordList.end(), back_inserter(wordList));

     }
}

long Trie::getWordCountByPrefix(const std::string& prefix)
{
    shared_ptr<TrieNode> nodeRef;
    shared_ptr<TrieNode> prevRef;
    bool returnStatus = isValidPrefixInternal(prefix, nodeRef, prevRef);
    if(returnStatus)
        return(prevRef->m_prefixCount);
    else
        return(0);
}

// Return the number of words inserted in the Trie so far.
long Trie::getTrieWordCount()
{
    return(m_wordCount);
}

Trie::~Trie()
{
    // We dont need to release anything here since shared_ptr will destroy the nodes that are allocated on heap!
}
vector<int> contacts(vector<vector<string>> queries, Trie& inputTrie) 
{
   vector<int> results; 
   results.reserve(queries.size());
   for(unsigned int i=0; i<queries.size(); ++i)
   {
       vector<string> query = queries[i];
       int count=0;
       for(unsigned int j=0; j<query.size(); j+=2)
       {
           string action = query[j];
           string word = query[j+1];           
           
           if(action=="add")
               inputTrie.insertWord(word);
           else
               results.emplace_back(inputTrie.getWordCountByPrefix(word));               
        }        
   }
 return(results);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));
    Trie sampleTrie;

    int queries_rows;
    cin >> queries_rows;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<string>> queries(queries_rows);
    for (int queries_row_itr = 0; queries_row_itr < queries_rows; queries_row_itr++) 
    {
        queries[queries_row_itr].resize(2);

        for (int queries_column_itr = 0; queries_column_itr < 2; queries_column_itr++) 
        {
            cin >> queries[queries_row_itr][queries_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> result = contacts(queries, sampleTrie);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) 
    {
        fout << result[result_itr];

        if (result_itr != result.size() - 1) 
        {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

