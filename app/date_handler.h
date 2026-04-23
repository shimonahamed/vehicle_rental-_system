#ifndef DATE_HANDLER_H
#define DATE_HANDLER_H
#include <stdio.h>
#include <time.h>
#include "../struct/models.h"


void date_handler(int days, char *input_date, char *custom_date) {

    time_t t;
    struct tm *tm_info;

    time(&t);

    // ➕ Case 1: Add days to current date
    if (days > 0) {

        time_t new_time = t + (days * 24 * 60 * 60);
        tm_info = localtime(&new_time);

        sprintf(custom_date, "%02d-%02d-%04d",
                tm_info->tm_mday,
                tm_info->tm_mon + 1,
                tm_info->tm_year + 1900);
    }

    // 📅 Case 2: date difference
    else if (input_date != NULL && custom_date != NULL) {

        struct tm input_tm = {0};
        int d, m, y;

        sscanf(input_date, "%d-%d-%d", &d, &m, &y);

        input_tm.tm_mday = d;
        input_tm.tm_mon = m - 1;
        input_tm.tm_year = y - 1900;

        time_t input_time = mktime(&input_tm);

        double diff = difftime(t, input_time);
        diff_days = diff / (60 * 60 * 24);

        sprintf(custom_date, "%d", diff_days);
    }
}

#endif