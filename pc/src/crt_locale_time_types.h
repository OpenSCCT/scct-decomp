struct LocaleTimeNames {
    char *short_day[7], *long_day[7];
    char *short_month[12], *long_month[12];
    char *am_pm[2];
    char *short_date, *long_date, *time;
    unsigned locale, calendar, references;
};

extern struct LocaleTimeNames *__lc_time_curr;
