
#include <string>
#include <iostream>
#include <vector>
#include<algorithm>


const int ALPHABET_SIZE = 255;		// characters.

/*
* INPUT: pattern as string, length of pattern as in, int array of size alphabet to be filled.
* values in array should be -1 (if not in the pattern) or the index position of a character in the pattern.
* PERFORMANCE: O(m+n) (this is a hint as to what is provided).
*/
void badCharHeur(std::string pattern, int length, int in_pattern[ALPHABET_SIZE])
{
	for (int i = 0; i < 255; i++) {
		in_pattern[i] = -1;
	}
	for (int i = 0; i < length; i++) {
		in_pattern[int(pattern[i])] = i;
	}
}


/*
* INPUT: A text to search through and a pattern to search for.
* Returns a structure with the indexes of the first character of each occurence of the pattern in the text. Empty if none.
* PERFORMANCE: Boyer-Moore-Horspool should run in O(mn) in the worst-case and should be sublinear in the average case.
*/
std::vector<int> BMH(std::string text, std::string pattern)
{
	int pattern_len = pattern.size();
	int text_len = text.size();
	int shift_position = 0; // possible position for first char of pattern
	std::vector<int> results;	// PUT VECTOR OF INTEGERS HERE as per lectures. 
	int badChar[255]; 	//being passed into a function that takes an array of ALPHABET SIZE (255). 
	badCharHeur(pattern,pattern_len,badChar);
	// TODO: Fill bad character heuristic lookup.
	while (shift_position <= text_len - pattern_len)
	{
		int characters_unmatched = pattern_len- 1;									
		while (characters_unmatched >= 0 && pattern[characters_unmatched] == text[shift_position + characters_unmatched])
		{
			//while pattern matches the text, going backwards
			characters_unmatched--;//reduce the number of characters to be matched 
		}
		if(characters_unmatched < 0){ //If the pattern has been matched

			results.push_back(shift_position); // Add shift position to results
			if (shift_position + pattern_len < text_len)
			{
				shift_position += pattern_len - badChar[text[shift_position + pattern_len]];
			}
			else {
				shift_position++;
			}
		} 
		else
		{
			shift_position += std::max(1, characters_unmatched - badChar[text[shift_position + characters_unmatched]]);
		}
	}
	return results;
}

/*
* INPUT: pattern as string, length of pattern as in, pointer to array to be used as LPS structure.
* For each character in the pattern, fill the LPS structure with the length of the longest proper prefix-suffix,
*/
void computeLPS(std::string pat, int M, int* lps)
{
	int len = 0;
	lps[0] = 0;
	int i = 1;
	while (i < M)
	{
		if (pat[i] == pat[len])
		{
			len++;
			lps[i] = len;
			i++;
		}
		else
		{
			if (len != 0) len = lps[len - 1];
			else
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

/*
* INPUT: A text to search through and a pattern to search for.
* Returns a structure with the indexes of the first character of each occurence of the pattern in the text. Empty if none.
* PERFORMANCE: O(m+h) in the worst case and similar in the average case.
*/
std::vector<int> KMP(std::string text, std::string pattern)
{
	int pattern_len = pattern.size(); //work them out once rather than having it done every time 
	int text_len = text.size();
	int* lps= new int [pattern_len]; //Because we can't dynamically allocate an array by just putting length as the index of a new array, use pointers.  
	computeLPS(pattern, pattern_len, lps); //pass parameters
	std::vector<int> results; //results vector 

	int i = 0;
	int j = 0;
	while (i < text_len) {
		if (pattern[j] == text[i]) { 
			i++;
			j++;
		}
		if (j == pattern_len) {
			results.push_back(i - j);
			j = lps[j - 1];
		}
		else if (i < text_len && pattern[j] != text[i]) {
			if (j!= 0) {
				j = lps[j - 1];
			}
			else {
				i = i + 1;
			}
		}

	}

	return results;
}

