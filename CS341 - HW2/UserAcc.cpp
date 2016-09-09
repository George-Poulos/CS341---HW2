#pragma once 
#include "stdafx.h"
#include "UserAcc.h"

UserAcc::UserAcc(int userid, int ratings)
{
	userID = userid;
	overallRatings = ratings;
}

UserAcc::~UserAcc()
{
}
