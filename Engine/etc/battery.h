/*
 * battery.h
 *
 *  Created on: 27/10/2013
 *      Author: drb
 */

#ifndef BATTERY_H_
#define BATTERY_H_

#if __GNUC__
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

#define BATTERY_WARNING 1
#define BATTERY_NORMAL 0

namespace etc
{

	bool has_battery ();

	void batterySetWarningPercent ( int per );
	void batterySetWarningTime ( int time );

	void batterySetCheckInterval ( int time );
	int batteryGetCheckInterval ();

	int batteryStatus ();

} /* namespace etc */

#endif /* BATTERY_H_ */
