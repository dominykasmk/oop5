#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>



using std::cout;
using std::string;
using std::ifstream;
using std::istringstream;


int main( int argc, char *argv[] ) {

    if ( argc < 2 ) {
        cout << "Per mažai argumentų.\n";
        return EXIT_SUCCESS;
    }
    

    ifstream input_file{ argv[1] };
    if (!input_file)
        throw std::ios_base::failbit;

    string line;
    unsigned line_count = 0;
    std::regex url("(((http|https)://)|www.)[a-zA-Z0-9]{2,256}\\.[a-z]{2,6}");
    while ( getline( input_file, line ) ) {

        string::const_iterator searchStart( line.cbegin() );
        std::smatch res;
        while ( regex_search( searchStart, line.cend(), res, url ) )
        {
            cout << res[0];  
            searchStart = res.suffix().first;
            cout << '\n';
        }
    }


    return EXIT_SUCCESS;
}
