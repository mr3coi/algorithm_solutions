#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iterator>
#include <limits>

#define MAX(x,y) ((x) >= (y) ? (x) : (y))
#define MIN(x,y) ((x) <= (y) ? (x) : (y))

unsigned int recursive_count(std::vector<bool>& handled,
							 std::vector<std::vector<unsigned int>>& pairs,
							 unsigned int num_students);

int main()
{
	unsigned int num_cases, num_students, num_pairs;

	std::cin >> num_cases;

	for (unsigned int c=0; c<num_cases; c++)
	{
		// =============================== I/O =================================
		// Get first line of input
		std::cin >> num_students >> num_pairs;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::vector<std::vector<unsigned int>> pairs(num_students, std::vector<unsigned int>());
		std::vector<bool> handled(num_students, false);

		// Get second line of input
		std::string pairs_line;
		std::getline(std::cin, pairs_line);
		std::istringstream iss(pairs_line);
		std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)),
										std::istream_iterator<std::string>());

		// Parse friendship pair information from input line
		for (unsigned int p=0; p<num_pairs*2; p+=2)
		{
			unsigned int std_a = std::stoul(parsed[p]);
			unsigned int std_b = std::stoul(parsed[p+1]);

			// Insert only unidirectionally: (smaller ID)->(larger ID)
			pairs[MIN(std_a,std_b)].push_back(MAX(std_a,std_b));
		}

		// =============================== Algorithm =================================
		std::cout << recursive_count(handled, pairs, num_students) << std::endl;
	}
}

unsigned int recursive_count(std::vector<bool>& handled,
							 std::vector<std::vector<unsigned int>>& pairs,
							 unsigned int num_students)
{
	// Aggregate variable
	unsigned int sum = 0;

	bool finished = true;
	for (unsigned int i=0; i<num_students; i++)
	{
		if (!handled[i]) {
			finished = false;
			handled[i] = true;

			for (unsigned int j: pairs[i]) {
				if (!handled[j]) {
					handled[j] = true;
					sum += recursive_count(handled, pairs, num_students);
					handled[j] = false;
				}
			}
			handled[i] = false;
			break;
		}
	}

	// finished == true <=> All students handled => 1 successful match-up found
	return (finished ? 1 : sum);
}
