#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <Arduino.h>

enum Level 
{
	Low, Normal, High
};

String LevelToString(Level level) {
	switch(level) {
		case Low: return "LOW";
		case Normal: return "NORMAL";
		case High: return "HIGH";
		default: return "UNKNOWN";
	}
}

#endif
