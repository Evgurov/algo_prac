// ID: 83581581
// =========================================================================
// Search system is implemeted via `class Search_system`.
//
// * Field `documents_words` stores a hash table with unique words from 
// the whole set of documents as keys. For every unique word table contains 
// another table which maps sequential number of document in which this 
// word occurs to the number of occurances.
// * Field `documents_number` stores current number of documents in
// the searching system.
// -------------------------------------------------------------------------
// * Method `add_document(document)` complements the hash table with words
// from the new `document`.
// * Method `search(request)` returns 5 most relevant documents. It runs
// through the unique words of the `request`, finds this words in hash table
// and forms an array of pairs (relevance-document number), then the array
// is sorted and first 5 document numbers are taken.
// -------------------------------------------------------------------------
// Time complexity: 
// * Add document: O(k), where k - number of words in a document
// * Search: ~O(m + n * r), where m - number of documents in the searching
// system, n - number of unique words in the request, r - average number of 
// documents, in which words from the request occur.
// -------------------------------------------------------------------------
// Memory complexity:
// * At every moment searching system stores hash table with unique words
// of all documents in the searching system and hash table with documents 
// numbers and numbers of occurances in these documents which is O(n * r)
// memory, where n - number of unique words in all document currently being
// stored, and r - average number of document in which words occures.
// * Add document requires O(n) additional memory, where n - number of all
// words in a document.
// * Search requires O(m + n) additional memory, where m - number of docs,
// currently being stored, and n - number of unique words in a request.
// =========================================================================

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>

#include <unordered_map>
#include <unordered_set>

#include <algorithm>

std::ifstream in;
std::ofstream out;

//======== printing function ====================

template <typename Type>
void print(const Type& container) {
    for (const auto& element : container) {
        out << element << " ";
    }
}

//===============================================


//======== splitting strings =============================================

std::vector<std::string> split(std::string str){
    std::istringstream ist(str);
    std::vector<std::string> str_splitted;
    for (std::string word; ist >> word; str_splitted.push_back(word)) {}

    return str_splitted;
}

std::unordered_set<std::string> unique_split(std::string str){
    std::istringstream ist(str);
    std::unordered_set<std::string> str_splitted;
    for (std::string word; ist >> word; str_splitted.insert(word)) {}

    return str_splitted;
}

//=========================================================================

//============ searching system class =============================================

class Search_system {
    int documents_number;
    std::unordered_map<std::string, std::unordered_map<int, int>> documents_words;
public:
    Search_system() : documents_number() {};
    void add_document(const std::string& document);
    std::vector<int> search(const std::string& request) const;
};

void Search_system::add_document(const std::string& document) {
    std::vector<std::string> document_splitted = split(document);
    
    documents_number++;

    for (const std::string& word : document_splitted) {
        documents_words[word][documents_number]++;
    }
}

std::vector<int> Search_system::search(const std::string& request) const {
    std::unordered_set<std::string> unique_words = unique_split(request);

    std::vector<std::pair<int, int>> relevance(documents_number);
    int document_number = 1;
    for (auto& pair : relevance) {
        pair.second = -document_number;
        document_number++;
    }

    for (const auto& word : unique_words) {
        if (documents_words.find(word) != documents_words.end()) {
            for (const auto& doc_occurances : documents_words.at(word)) {
                relevance[doc_occurances.first - 1].first += doc_occurances.second; 
            }
        }
    }

    std::sort(relevance.rbegin(), relevance.rend());

    std::vector<int> top_5;
    int iter = 0;
    while (iter < relevance.size() && iter < 5 && (relevance[iter].first != 0)) {
        top_5.push_back(-relevance[iter].second);
        iter++;
    }

    return top_5;
}

//====================================================================================


int main() {
    in.open("input.txt");
    out.open("output.txt");

    Search_system system;

    int n_documents;
    in >> n_documents; 
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string document;
    for (int i = 0; i < n_documents; ++i) {
        std::getline(in, document);
        system.add_document(document);
    }

    int n_requests;
    in >> n_requests; 
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string request;
    for (int i = 0; i < n_requests; ++i) {
        std::getline(in, request);
        print(system.search(request)); out << std::endl;
    }

    in.close();
    out.close();
}