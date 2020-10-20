#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/**
 * @brief Checking the occurrence of letters of one word in another.
 * @param _a  First word.
 * @param _b  Second word.
 * @return  True if the words consist of the same letters otherwise false.
 * 
 * Check the occurrence of letters in a nutshell.
 * True - the number of occurrences of letters is the same.
 * False - the number of occurrences of letters does not match.
*/
bool _compare( const std::string &_a, const std::string &_b )
{
    int count_a[ 'z' - 'a' + 1] = { 0 }; // The number of occurrences of letters in the word '_a'
    int count_b[ 'z' - 'a' + 1] = { 0 }; // The number of occurrences of letters in the word '_b'

    // For the word '_a'
    for( int i = 0; i < _a.size(); ++i )
        if( isalpha( _a[ i ] ) ) // We need letters only
            count_a[ 'z' - tolower( _a[ i ] ) ]++;

    // For the word '_b'
    for( int i = 0; i < _b.size(); ++i )
        if( isalpha( _b[ i ] ) ) // We need letters only
            count_b[ 'z' - tolower( _b[ i ] ) ]++;

    /**
     * We check the occurrence of letters from the word 'b' in the word 'a'.
     * If the number of occurrences of any letter is different - return false.
    */
   for( int i = 0; i < 'z' - 'a'; ++i )
       if( count_a[ i ] != count_b[ i ] )
            return false;

    // Words are anagrams
    return true;
}

 /**
   *  @brief Count the number of copies of a value in a sequence.
   *  @param  _first  An input iterator.
   *  @param  _last   An input iterator.
   *  @param  _value  The value to be counted.
   *  @return   The number of iterators i in the range [_first, _last]
   *  for which *i ==  _value
*/
int _count( std::vector< int >::iterator _first, std::vector< int >::iterator _last, int _value )
{
    int _n = 0;
    for( ; _first != _last; ++_first )
        if( *_first == _value )
            ++_n;

    return _n;
}

int main( void )
{
    // Open the file; in case of failure, we quit
    std::fstream file( "file.txt" );
    if( !file.is_open() )
    {
        std::cerr << "Cannot to open file! " << std::endl;
        return EXIT_FAILURE;
    }

    std::vector< std::string > lines;
    std::string input;

    /**
     * We fill the vector with strings.
     * 1 word - 1 line.
    */
    while( file >> input )
        lines.push_back( input );

    // Close the file
    file.close();

    // Connectivity vector for words
    std::vector< int > connectivity( lines.size() );
    for( int i = 0; i < lines.size(); ++i )
        connectivity[ i ] = i;

    for( int i = 0; i < lines.size(); ++i )
    {
        for( int j = 0; j < lines.size(); ++j )
        {
            // If two words are not connected yet
            if( connectivity[ i ] != connectivity[ j ] )
            {
                // Checking for the number of occurrences of letters of one word in another
                if( _compare( lines[ i ], lines[ j ] ) )
                {
                    // Linking words (strings)
                    // Remember the old key for further comparison
                    int old_key = connectivity[ i ];

                    for( int k = 0; k < connectivity.size(); ++k )
                    {
                        // Change the old key to a new one
                        if( connectivity[ k ] == old_key )
                            connectivity[ k ] = connectivity[ j ];
                    }
                }
            }
        }
    }

    // Output of all connected words (lines), i.e. anagram output
    for( int i = 0; i < connectivity.size(); ++i )
    {   
        unsigned int out = 0; // Used if there is a word to output (for comma and next line)
        
        // Display only connected words (strings)
        if( _count( connectivity.begin(), connectivity.end(), i ) > 1 )
        {
            for( int j = 0; j < connectivity.size(); ++j )
            {
                if( connectivity[ j ] == i )
                {
                    if( out )
                        std::cout << ", ";

                    std::cout << lines[ j ];

                    out++;
                }
            }
            std::cout << std::endl;
        }
    }

    return EXIT_SUCCESS;
}