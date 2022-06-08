#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>


using std::cout;
using std::unordered_map;
using std::pair;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::ispunct;


void read_file( const string file_name, unordered_map<string, int>& frequency );
void write_file( const string file_name, unordered_map<string, int>& frequency );
bool is_number( const string& word );


int main() {

    unordered_map<string, int> frequency; 
    /*  
    text_map.insert(pair<string, int>("labas", 1)); 

    cout << text_map["labas"] << '\n';

    if (text_map.count("labas") == 0) 
        text_map["labas"]++;

    cout << text_map["labas"] << '\n';
    */

    try {
        read_file( "tekstas.txt",  frequency );
    }
    catch ( string e ) {
        std::cerr << "Klaida atidarinėjant failą\n";
    }

    for (auto word : frequency ) {
        cout << word.first << " " << word.second << '\n';
    }

    try {
        write_file( "output.txt", frequency );
    }
    catch ( string e ) {
        std::cerr << "Klaida atidarinėjant failą\n";
    }

    return EXIT_SUCCESS;
}


void read_file( const string file_name, unordered_map<string, int>& frequency ) {
    
    ifstream input_file{ file_name };
    if (!input_file)
        throw std::ios_base::failbit;

    string line;
    while ( getline( input_file, line ) ) {


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

            frequency[word]++;
        }
        
    }

    input_file.close();
}

void write_file( const string file_name, unordered_map<string, int>& frequency ) {

    ofstream output_file{ file_name };
    if ( !output_file )
        throw std::ios_base::failbit;

    for (auto word : frequency ) {
        if ( word.second > 1 ) {
            output_file << word.first << " " << word.second << '\n';
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
