#pragma once 
#include "stdafx.h"
#include "UserReviews.h"

UserReviews::UserReviews(int userid, int movieid, int rating)
{
	userID = userid;
	movieID = movieid;
	Rating = rating;
	
}

UserReviews::~UserReviews()
{
}
