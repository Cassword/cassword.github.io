
#include <map>
#include <vector>
#include <iostream>


// Hint: Use find(iterator, iterator, value).
bool personPrefersNewDog(std::vector<std::vector<int>> personPref, int person, int dog1, int dog2)
{
	// find the index of dog1 and dog2 in the person's preference list
	auto dog1Index = std::find(personPref[person].begin(), personPref[person].end(), dog1);
	auto dog2Index = std::find(personPref[person].begin(), personPref[person].end(), dog2);

	// if dog1 comes before dog2 in the preference list, return true
	if (dog1Index < dog2Index) {
		return true;
	}
	else {
		return false;
	}
}

int dogMatchedToPerson(int person, std::map<int, int> matches)
{
	// loop through the map and find the dog that is matched with the given person
	for (auto& pair : matches) {
		if (pair.second == person) {
			return pair.first;
		}
	}

	return -1;
}


std::map<int, int> stableMarriage(std::vector<std::vector<int>> dogPref, std::vector<std::vector<int>> personPref) //I cannot for the life of me figure out an implementation like the pseudocode wants - I have spent hours on this - this works. 
{
    std::map<int, int> matches;

    std::vector<int> freeDogs;
    for (int i = 0; i < dogPref.size(); i++) {
        freeDogs.push_back(i);
    }

    // Create a map to store the proposal counts for each dog
    std::map<int, int> proposalCounts;

    // while there are still free dogs
    while (!freeDogs.empty()) {
        // get the next free dog
        int dog = freeDogs.back();
        freeDogs.pop_back();

        // Check if the dog has proposed to all people
        if (proposalCounts[dog] == personPref.size()) {
            continue;
        }

        // get the next person on the dog's preference list
        int person = dogPref[dog][0];
        // remove the person from the dog's preference list
        dogPref[dog].erase(dogPref[dog].begin());

        // if the person is not currently matched with a dog
        if (matches.count(person) == 0) {
            // match the dog and person
            matches[person] = dog;

            proposalCounts[dog]++;
        }
        else {
            // get the dog that the person is currently matched with
            int otherDog = matches[person];

            // if the person prefers the new dog over the current dog
            if (personPrefersNewDog(personPref, person, dog, otherDog)) {
                matches[person] = dog;
                freeDogs.push_back(otherDog);
                proposalCounts[dog]++;
            }
            else {
                // add the new dog to the list of free dogs
                freeDogs.push_back(dog);
            }
        }
    }

    std::map<int, int> matches_inv; //we have to invert it - I wish I had time to fix this. I don't. 

    for (auto pair : matches) {
        matches_inv[pair.second] = pair.first;
    }

    return matches_inv;
}

