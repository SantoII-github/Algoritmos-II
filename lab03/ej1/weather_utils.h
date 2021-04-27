#ifndef _WEATHER_UTILS_H
#define _WEATHER_UTILS_H

#include "array_helpers.h"

/**
 * @brief Returns the lowest minimum temperature registered in the array
 */
int minimum_temp_historic(WeatherTable array);

/**
 * @brief Sets the elements of output to the highest maximum temperature of each year
 * @details
 * 
 *  Each entry corresponds to the year index + 1980, 
 *  where index is its position in the array.
 * 
 * @param array array which will be read
 * @param output array to which the temperature values will be written to 
 */
void max_temp_peryear(WeatherTable array, int output[YEARS]);

/**
 * @brief Used to print max_temp_peryear's results

 * @param input array that will be printed
 */
void print_max_temp_peryear(int input[YEARS]);

/**
 * @brief Sets the elements of output to the month of the year with the most rainfall. 
 * @details
 *  
 *  Each entry corresponds to the year index + 1980, 
 *  where index is its position in the array.
 * 
 * @param array array which will be read
 * @param output array to which the month values will be written to 
 */
void max_monthly_rainfall_peryear(WeatherTable array, t_month output[YEARS]);

/**
 * @brief Used to print max_monthly_rainfall_peryear's results

 * @param input array that will be printed
 */
void print_max_monthly_rainfall_peryear(t_month input[YEARS]);
#endif