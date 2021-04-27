#include "weather.h"
#include "weather_utils.h"
#include "array_helpers.h"

int minimum_temp_historic(WeatherTable array) {
    int historic_min_temp = array[0][0][0]._min_temp;
    for (unsigned int year = 0u; year < YEARS; ++year) {
        for (t_month month = january; month <= december; ++month) {
            for (unsigned int day = 0u; day < DAYS; ++day) {
                if (historic_min_temp > array[year][month][day]._min_temp) {
                    historic_min_temp = array[year][month][day]._min_temp;
                }
            }
        }
    }
    return historic_min_temp;
}

void max_temp_peryear(WeatherTable array, int output[YEARS]) {
    int max_temp_yearly;
    for (unsigned int year = 0u; year < YEARS; ++year) {
        max_temp_yearly = 0;
        for(t_month month = january; month <= december; ++month) {
            for(unsigned int day = 0u; day < DAYS; ++day) {
                if (max_temp_yearly < array[year][month][day]._max_temp) {
                    max_temp_yearly = array[year][month][day]._max_temp;
                }
            }
        }
        output[year] = max_temp_yearly;
    }
}

void print_max_temp_peryear(int input[YEARS]) {
    printf("Year | Highest Temperature\n");
    printf("---------------------------\n");
    for(unsigned int year = 0; year < YEARS; ++year) {
        printf("%u | %u\n", year+1980, input[year]);
    }
}

void max_monthly_rainfall_peryear(WeatherTable array, t_month output[YEARS]) {
    // First we declare the variables that will be needed in the for loop.
    unsigned int monthly_rainfall, highest_monthly_rainfall;
    t_month month_most_rainfall;
    for (unsigned int year = 0u; year < YEARS; ++year) {
        // For each year, we set the starting parameters to 0 and the first month.
        highest_monthly_rainfall = 0;                       
        month_most_rainfall = january;
        for(t_month month = january; month <= december; ++month) {
            // For each month, we calculate the monthly rainfall.
            monthly_rainfall = 0;
            for(unsigned int day = 0u; day < DAYS; ++day) {     
                monthly_rainfall = monthly_rainfall + array[year][month][day]._rainfall;
            }
            // If this month's monthly rainfall is higher than the one we have stored, we update our data.
            if (monthly_rainfall > highest_monthly_rainfall) {
                highest_monthly_rainfall = monthly_rainfall;
                month_most_rainfall = month;
            }
        }
        // Once we have the month with the most rainfall, we add the result to our output, then we repeat for each year.
        output[year] = month_most_rainfall;
    }
}

void print_max_monthly_rainfall_peryear(t_month input[YEARS]) {
    printf("Year | Month with most rainfall\n");
    printf("---------------------------\n");
    for(unsigned int year = 0; year < YEARS; ++year) {
        printf("%u | %u\n", year+1980, input[year]);
    }
}
