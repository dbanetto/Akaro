/*
 * battery.cpp
 *
 *  Created on: 27/10/2013
 *      Author: drb
 */

#include "battery.h"

namespace etc
{
    /**
     * @brief The Settings for the battery
     */
    struct BatterySettings {
        //Minimum percentage left to warn
        int warning_percent = 20;
        //Minimum time left to warn (in seconds)
        int warning_time = 30*60;
        //Time between checks
        int check_interval = 60000;

        SDL_PowerState current_state;
    } BATTERY_SETTINGS;

    /**
     * @brief Returns true if the system has a battery
     * @note All but SDL_NO_BATTERY is true
     * @return bool
     */
    bool has_battery()
    {
        int secs  = 0, pct = 0;
        SDL_PowerState state = SDL_GetPowerInfo(&secs , &pct);

        switch (state)
        {
        case (SDL_POWERSTATE_ON_BATTERY):
        case (SDL_POWERSTATE_CHARGING):
        case (SDL_POWERSTATE_CHARGED):

            return true;


        case (SDL_POWERSTATE_NO_BATTERY):
        case (SDL_POWERSTATE_UNKNOWN):
        default: //better to be safe than sorry
            return false;
        }
    }

    void batterySetWarningPercent (int per)
    {
        BATTERY_SETTINGS.warning_percent = per;
    }

    void batterySetWarningTime (int time)
    {
        BATTERY_SETTINGS.warning_time = time;
    }

    void batterySetCheckInterval (int time)
    {
        BATTERY_SETTINGS.check_interval = time;
    }

    int batteryGetCheckInterval ()
    {
        return BATTERY_SETTINGS.check_interval;
    }


    /**
     * @brief Returns current status of the battery
     * @return Returns BATTERY_WARNING when condition set are meet
     */
    int batteryStatus ()
    {

        int secs  = 0, pct = 0;
        SDL_PowerState state = SDL_GetPowerInfo(&secs , &pct);
        BATTERY_SETTINGS.current_state = state;

        //Check if the Battery is charging or charged
        switch (state)
        {
            case (SDL_POWERSTATE_CHARGING):
            case (SDL_POWERSTATE_CHARGED):
                return BATTERY_NORMAL;
            default:
                break;
        }

        //Seconds left are unknown, skip
        if (secs != -1) {
            if (secs <= BATTERY_SETTINGS.warning_time) {
                return BATTERY_WARNING;
            }
        }
        //percent is unknown, skip
        if (pct != -1) {
            if (secs <= BATTERY_SETTINGS.warning_percent) {
                return BATTERY_WARNING;
            }
        }

        return BATTERY_NORMAL;
    }

} /* namespace etc */
