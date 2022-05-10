#ifndef __RULEESNGINE_H__
#define __RULESENGINE_H__

#include "Level.h"

bool InferRule1(Level ph, Level air, Level water)
{
	if(ph == Low && air == Low && water == Low) {
		return true;
	}
	if(ph == Low && air == Low && water == Normal) {
		return true;
	}
	if(ph == Low && air == Low && water == High) {
		return true;
	}

	if(ph == Low && air == Normal && water == Low) {
		return true;
	}
	if(ph == Low && air == Normal && water == Normal) {
		return true;
	}
	if(ph == Low && air == Normal && water == High) {
		return true;
	}

	if(ph == Low && air == High && water == Low) {
		return true;
	}
	if(ph == Low && air == High && water == Normal) {
		return true;
	}
	if(ph == Low && air == High && water == High) {
		return true;
	}

	return false;
}

bool InferRule2(Level ph, Level air, Level water)
{
	if(ph == Normal && air == Low && water == Low) {
		return true;
	}
	if(ph == Normal && air == Low && water == Normal) {
		return true;
	}
	if(ph == Normal && air == Low && water == High) {
		return true;
	}

	if(ph == Normal && air == Normal && water == Low) {
		return true;
	}
	if(ph == Normal && air == Normal && water == Normal) {
		return false; // ALL IS NORMAL: Don't Send Alert
	}
	if(ph == Normal && air == Normal && water == High) {
		return true;
	}

	if(ph == Normal && air == High && water == Low) {
		return true;
	}
	if(ph == Normal && air == High && water == Normal) {
		return true;
	}
	if(ph == Normal && air == High && water == High) {
		return true;
	}

	return false;
}


bool InferRule3(Level ph, Level air, Level water)
{
	if(ph == High && air == Low && water == Low) {
		return true;
	}
	if(ph == High && air == Low && water == Normal) {
		return true;
	}
	if(ph == High && air == Low && water == High) {
		return true;
	}

	if(ph == High && air == Normal && water == Low) {
		return true;
	}
	if(ph == High && air == Normal && water == Normal) {
		return true;
	}
	if(ph == High && air == Normal && water == High) {
		return true;
	}

	if(ph == High && air == High && water == Low) {
		return true;
	}
	if(ph == High && air == High && water == Normal) {
		return true;
	}
	if(ph == High && air == High && water == High) {
		return true;
	}

	return false;
}

#endif
