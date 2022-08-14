
     // variables to store the date and time components
    int hours, minutes, seconds, day, month, year;
 
    // `time_t` is an arithmetic time type
    time_t now;
    
    // Obtain current time
    // `time()` returns the current time of the system as a `time_t` value
    time(&now);
 
    // Convert to local time format and print to stdout
    printf("Today is %s", ctime(&now));
 
    // localtime converts a `time_t` value to calendar time and
    // returns a pointer to a `tm` structure with its members
    // filled with the corresponding values
    struct tm *local = localtime(&now);
 
    hours = local->tm_hour;         // get hours since midnight (0-23)
    minutes = local->tm_min;        // get minutes passed after the hour (0-59)
    seconds = local->tm_sec;        // get seconds passed after a minute (0-59)
 
    day = local->tm_mday;            // get day of month (1 to 31)
    month = local->tm_mon ;      // get month of year (0 to 11)
    year = local->tm_year ;   // get year since 1900
    
    // print local time
    if (hours < 12) {    // before midday
        printf("Time is %02d:%02d:%02d am\n", hours, minutes, seconds);
    }
    else {    // after midday
        printf("Time is %02d:%02d:%02d pm\n", hours, minutes, seconds);
    }
 
    // print the current date
    printf("Date is: %02d/%02d/%d\n", day, month, year);
    
    #define STRMAX 12
    char s_month[STRMAX];

    switch(month)
    {
        case 1:
           strncpy(s_month,"January",STRMAX);
            break;
        case 2:
            strncpy(s_month ,"February", STRMAX);
            break;
        case 3:
            strncpy(s_month ,"March", STRMAX);
            break;
        case 4:
            strncpy(s_month ,"April", STRMAX);
            break;
        case 5:
            strncpy(s_month ,"May", STRMAX);
            break;
        case 6:
           strncpy( s_month ,"June", STRMAX);
            break;
        case 7:
            strncpy(s_month ,"July", STRMAX);
            break;
        case 8:
            strncpy(s_month ,"August", STRMAX);
            break;
        case 9:
            strncpy(s_month ,"September", STRMAX);
            break;
        case 10:
            strncpy(s_month ,"October", STRMAX);
            break;
        case 11:
            strncpy(s_month ,"November", STRMAX);
            break;
        case 12:
            strncpy(s_month ,"December", STRMAX);
            break;
    }
    printf("\n HELLT %s",s_month);


#if 1   //show image for array    
    printf("show image for array\r\n");
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    //Paint_DrawNum(140, 40, 123456789, &Font16, BLACK, WHITE);
    //Paint_DrawBitMap(gImage_tank); //changed this
    //
    Paint_DrawString_EN(50, 0, s_month, &Font20, WHITE, BLACK);
    Paint_DrawLine(0,20,250,20, BLACK,DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    PAINT_TIME sPaint_times;
    sPaint_times.Hour = hours;
    sPaint_times.Min = minutes;
    sPaint_times.Sec = 00;
    Paint_DrawString_EN(50, 50, &sPaint_times, &Font20, WHITE, BLACK);
    Paint_DrawNum(50,80,month , &Font16, BLACK, WHITE);
    Paint_DrawNum(70,80,day , &Font16, BLACK, WHITE);
    Paint_DrawNum(90,80,year , &Font16, BLACK, WHITE);
    EPD_2IN13_V2_Display(BlackImage);
    DEV_Delay_ms(20000);
#endif


#if 1   //Partial refresh, example shows time    		
    printf("Partial refresh\r\n");
    EPD_2IN13_V2_Init(EPD_2IN13_V2_FULL);
    EPD_2IN13_V2_DisplayPartBaseImage(BlackImage);

    EPD_2IN13_V2_Init(EPD_2IN13_V2_PART);
    Paint_SelectImage(BlackImage);
    PAINT_TIME sPaint_time;
    sPaint_time.Hour = 12;
    sPaint_time.Min = 34;
    sPaint_time.Sec = 56;
    UBYTE num = 20;
    for (;;) {
        sPaint_time.Sec = sPaint_time.Sec + 1;
        if (sPaint_time.Sec == 60) {
            sPaint_time.Min = sPaint_time.Min + 1;
            sPaint_time.Sec = 0;
            if (sPaint_time.Min == 60) {
                sPaint_time.Hour =  sPaint_time.Hour + 1;
                sPaint_time.Min = 0;
                if (sPaint_time.Hour == 24) {
                    sPaint_time.Hour = 0;
                    sPaint_time.Min = 0;
                    sPaint_time.Sec = 0;
                }
            }
        }
        Paint_ClearWindows(140, 90, 140 + Font20.Width * 7, 90 + Font20.Height, WHITE);
        Paint_DrawTime(140, 90, &sPaint_time, &Font20, WHITE, BLACK);

        num = num - 1;
        if(num == 0) {
            break;
        }
        EPD_2IN13_V2_DisplayPart(BlackImage);
        DEV_Delay_ms(500);//Analog clock 1s
