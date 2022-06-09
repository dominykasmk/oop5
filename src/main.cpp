#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <vector>


using std::cout;
using std::unordered_map;
using std::pair;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::ispunct;
using std::setw;
using std::left;
using std::right;
using std::vector;


void read_file( const string file_name, unordered_map<string, vector<int>>& frequency );
void write_file( const string file_name, unordered_map<string, vector<int>>& frequency );
bool is_number( const string& word );
void output_results( unordered_map<string, vector<int>>& frequency );


int main() {

    unordered_map<string, vector<int>> frequency; 

    try {
        read_file( "../tekstai/tekstas.txt",  frequency );
    }
    catch ( string e ) {
        std::cerr << "Klaida atidarinėjant failą\n";
    }

    /*
    for (auto word : frequency ) {
        cout << word.first << " " << word.second << '\n';
    }
    */

    try {
        write_file( "output.txt", frequency );
    }
    catch ( string e ) {
        std::cerr << "Klaida atidarinėjant failą\n";
    }

    output_results( frequency );

    return EXIT_SUCCESS;
}


void read_file( const string file_name, unordered_map<string, vector<int>>& frequency ) {
    
    ifstream input_file{ file_name };
    if (!input_file)
        throw std::ios_base::failbit;

    string line;
    unsigned line_count = 0;
    while ( getline( input_file, line ) ) {

        if (!line.empty())
            line_count++;

        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        //std::remove_if( line.begin(), line.end(), ispunct );
        istringstream iss( line ); 

        string word;
        while ( getline( iss, word, ' ' ) ) {

            if (ispunct(word.front()))
                word.erase(0, 1);

            if (ispunct(word.back()))
                word.erase(word.length() - 1, 1);

            if (word.length() == 0)
                continue;

            if (frequency[word].size() == 0)
                frequency[word].push_back(0);

            frequency[word][0]++;
            frequency[word].push_back(line_count);
        }
        
    }

    input_file.close();
}

void write_file( const string file_name, unordered_map<string, vector<int>>& frequency ) {

    ofstream output_file{ file_name };
    if ( !output_file )
        throw std::ios_base::failbit;

    for (auto word : frequency ) {
        if ( word.second[0] > 1 ) {
            output_file << word.first << " " << word.second[0] << '\n';
        }
    }


    output_file.close();
}


bool is_number( const string& word ) {
    string::const_iterator it = word.begin();
    while ( it != word.end() && std::isdigit(*it))
        ++it;

    return !word.empty() && it != word.begin();
}


void output_results( unordered_map<string, vector<int>>& frequency ) {
    printf("%-20s%-15s%-15s\n", "Zodis", "Pasikartojo", "Eilutese");

    for ( auto word : frequency ) {

        if (word.second[0] == 1)
            continue;

        printf("%-20s%-15d", word.first.c_str(), word.second[0]);
        
        if (word.second.size() > 1) {
            for (auto it = word.second.begin() + 1; it != word.second.end(); it++) {
                cout << *it << ' ';
            }
            cout << '\n';
        }
    }
}
