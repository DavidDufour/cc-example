#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

int main()
{
	// file with input tweets
	ifstream tweets("tweet_input/tweets.txt");

	// file with the results from the first feature
	ofstream results("tweet_output/ft1.txt");

	// string for storing tweet
	string tweet;

	// words in tweet are separated by white space
	char_separator<char> whiteSpace(" \t\v\f");

	// frequency of each word in all tweets (running count)
    map<string,int> reduce;

	// reads the tweets in line by line
	while (getline(tweets, tweet))
    {
		// separate the words in a tweet by whitespace
		tokenizer<char_separator<char> > tokens(tweet, whiteSpace);
	
		// add to the count of each word in the frequency map
		for (tokenizer<char_separator<char> >::iterator it = tokens.begin(); it != tokens.end(); ++it)
			++reduce[*it];
    }

	// output the words from the tweets with their frequencies
	for (map<string,int>::iterator it = reduce.begin(); it != reduce.end(); ++it)
		results << it->first << " " << it->second << '\n';
}