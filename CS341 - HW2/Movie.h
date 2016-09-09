#include <string>
#include <vector>
using std::vector;
using namespace std;

class Movie
{
public:
	int  movieID;
	string  movieName;
	int  pubYear;
	int Reviews; 
	int numberofRatings[5];
	double avgReview;

	Movie(int movieid, string moviename, int pubyear, int reviews, double avgreview);
	~Movie();
};

