#pragma once 
#include "stdafx.h"
#include "Movie.h"


Movie::Movie(int movieid, string moviename, int pubyear, int reviews, double avgreview)
{
	movieID = movieid;
	movieName = moviename;
	pubYear = pubyear;
	Reviews = reviews;
	for (int &i : numberofRatings)
		i = 0;
	avgReview = avgreview;
}

Movie::~Movie()
{
}

