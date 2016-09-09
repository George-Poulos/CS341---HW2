#include "stdafx.h"
#include "Main.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>


vector<Movie> movieParser(string fileName) {
	string line;
	vector<Movie> movieListing;
	ifstream Stream(fileName);
	getline(Stream, line);
	string movieid, moviename, pubyear, reviews, avgrev;
	cout << "\nReading Movies...";
	int i = 0;
	while (getline(Stream, line)) {
		stringstream currline(line);
		getline(currline, movieid, ',');
		getline(currline, moviename, ',');
		getline(currline, pubyear, ',');
		Movie currMovie(stoi(movieid), moviename, stoi(pubyear), 0, 0);
		movieListing.push_back(currMovie);
		i++;
	}
	sort(movieListing.begin(), movieListing.end(), [](Movie &s1, Movie &s2) {
		if (s1.movieID < s2.movieID)
			return true;
		else
			return false;
	});
	cout << i << endl;
	return movieListing;
}

vector<UserReviews> reviewParser(string filename) {
	cout << "Reading Reviews...";
	string line;
	vector<UserReviews> reviewListing;
	ifstream Stream(filename);
	getline(Stream, line);
	string userid, movieid, rating;
	int i = 0;
	while (getline(Stream, line)) {
		stringstream currline(line);
		getline(currline, movieid, ',');
		getline(currline, userid, ',');
		getline(currline, rating, ',');

		UserReviews currReview(stoi(userid), stoi(movieid), stoi(rating));
		reviewListing.push_back(currReview);
		i++;
	}

	sort(reviewListing.begin(), reviewListing.end(), [](UserReviews &s1, UserReviews &s2) {
		if (s1.userID < s2.userID)
			return true;
		else
			return false;
	});
	cout << i << "\n" << endl;
	return reviewListing;
}

vector<UserAcc> UserListCreate(vector<UserReviews> &sortedReviewListing, vector<Movie> &sortedMovieListing) {
	int reviewIndex = 0, userid = -9999, i = 0;
	vector<UserAcc> userAcc;
	for (UserReviews & value : sortedReviewListing) {
		if (value.userID == userid) {
			userAcc[reviewIndex].overallRatings++;
			sortedMovieListing[value.movieID - 1].Reviews++;
			sortedMovieListing[value.movieID - 1].avgReview = sortedMovieListing[value.movieID - 1].avgReview + value.Rating;
			sortedMovieListing[value.movieID - 1].numberofRatings[value.Rating - 1]++;
		}
		else {
			userid = value.userID;
			if (userAcc.size() - reviewIndex >= 1)
				reviewIndex++;
			userAcc.push_back(UserAcc(userid, 1));
			sortedMovieListing[value.movieID - 1].Reviews++;
			sortedMovieListing[value.movieID - 1].avgReview = sortedMovieListing[value.movieID - 1].avgReview + value.Rating;
			sortedMovieListing[value.movieID - 1].numberofRatings[value.Rating - 1]++;
		}
		i++;
	}
	return userAcc;
}

void findMovieAvg(vector<Movie> &movieListing) {
	for (Movie & value : movieListing) {
		value.avgReview = (double)value.avgReview / (double)value.Reviews;
	}
}

void movieLoop(vector<Movie> &movieListing) {
	string id;
	sort(movieListing.begin(), movieListing.end(), [](Movie &s1, Movie &s2) {
		if (s1.movieID < s2.movieID)
			return true;
		else
			return false;
	});
	int max = movieListing.size();
	cout << "\n>> Movie Information <<\n" << endl;
	cout << "Please enter a movie ID [1.." << max << "], 0 to stop : ";
	cin >> id;
	while (stoi(id) != 0) {
		cout << "\n";
		int intID = stoi(id);
		if (intID < 1 || intID > max) {
			cout << "** Invalid movie id, please try again..." << endl;
		}
		else {
			intID--;
			cout << "Movie:\t'" << movieListing[intID].movieName << "'" << endl;
			cout << "Year:\t" << movieListing[intID].pubYear << endl;
			cout << "Avg rating:\t" << movieListing[intID].avgReview << endl;
			cout << "Num reviews:\t" << movieListing[intID].Reviews << endl;
			for (int i = 0; i < 5; i++)
				cout << "Num " << i + 1 << "'s:\t" << movieListing[intID].numberofRatings[i] << endl;
		}
		cout << "Please enter a movie ID [1.." << max << "], 0 to stop : ";
		cin >> id;
	}
}

int main()
{
	cout << "** Netflix Movie Review Analysis **" << endl;

	string movieFile = "Movies.csv";
	string revFile = "reviews-2.csv";
	ifstream  codesFile(movieFile);
	ifstream  crimesFile(revFile);

	if (!codesFile.good())
	{
		cout << "cannot open Movies file!" << endl;
		return -1;
	}

	if (!crimesFile.good())
	{
		cout << "cannot open Reviews file!" << endl;
		return -1;
	}

	vector<Movie> movieListing = movieParser(movieFile);
	vector<UserReviews>reviewListing = reviewParser(revFile);
	vector<UserAcc> users = UserListCreate(reviewListing, movieListing);
	findMovieAvg(movieListing);
	sort(users.begin(), users.end(), [](UserAcc &s1, UserAcc &s2) {
		if (s1.overallRatings > s2.overallRatings)
			return true;
		else if (s1.overallRatings < s2.overallRatings)
			return false;
		else
			return s1.userID < s2.userID;
	});

	sort(movieListing.begin(), movieListing.end(), [](Movie &s1, Movie &s2) {
		if (s1.avgReview > s2.avgReview)
			return true;
		else if (s1.avgReview < s2.avgReview)
			return false;
		else
			return s1.movieName.compare(s2.movieName) < 0;
	});

	cout << "\n\n>> Top-10 Movies <<" << endl;
	cout << "Rank\tID\tReviews\tAvg\tName" << endl;
	for (int i = 0; i < 10; i++) {
		cout << i + 1 << ".\t" << movieListing[i].movieID << "\t" << movieListing[i].Reviews
			<< "\t" << movieListing[i].avgReview << "\t'" << movieListing[i].movieName <<
			"'" << endl;
	}
	cout << "\n\n>> Top-10 Users <<" << endl;
	cout << "Rank\tID\tReviews" << endl;
	for (int i = 0; i < 10; i++) {
		cout << i + 1 << ".\t" << users[i].userID << "\t" << users[i].overallRatings << endl;
	}
	movieLoop(movieListing);

}



