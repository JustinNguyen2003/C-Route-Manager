/** @file route_manager.c
 *  @brief A pipes & filters program that uses conditionals, loops, and string processing tools in C to process airline routes.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Jose O.
 *  @author Saasha J.
 *  @author Victoria L.
 *  @author STUDENT_NAME
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */

struct Route{
    //this initializes a struct for a single airline route and its data
        char airline_name[50];
        char airline_icao_unique_code[50];
        char airline_country[50];
        char from_airport_name[50];
        char from_airport_city[50];
        char from_airport_country[50];
        char from_airport_icao_unique_code[50];
        float from_airport_altitude;
        char to_airport_name[50];
        char to_airport_city[50];
        char to_airport_country[50];
        char to_airport_icao_unique_code[50];
        float to_airport_altitude;
};


void getArgs(int argc, char *argv[], char **datasheet, char **airline, char **dest_country, char **src_country, char **dest_city, char **src_city){
    //this function takes command line arguments and places them into coresponding variables


    if (argc <= 4){
        *datasheet = strtok(argv[1], "=");
        *datasheet = strtok(NULL, "=");

        *airline = strtok(argv[2], "=");
        *airline = strtok(NULL, "=");

        *dest_country = strtok(argv[3], "=");
        *dest_country = strtok(NULL, "=");
    }
    
    else if(argc == 5){
        *datasheet = strtok(argv[1], "=");
        *datasheet = strtok(NULL, "=");

        *src_country = strtok(argv[2], "=");
        *src_country = strtok(NULL, "=");

        *dest_city = strtok(argv[3], "=");
        *dest_city = strtok(NULL, "=");

        *dest_country = strtok(argv[4], "=");
        *dest_country = strtok(NULL, "=");

    }

    else if (argc == 6){
        *datasheet = strtok(argv[1], "=");
        *datasheet = strtok(NULL, "=");

        *src_city = strtok(argv[2], "=");
        *src_city = strtok(NULL, "=");

        *src_country = strtok(argv[3], "=");
        *src_country = strtok(NULL, "=");

        *dest_city = strtok(argv[4], "=");
        *dest_city = strtok(NULL, "=");

        *dest_country = strtok(argv[5], "=");
        *dest_country = strtok(NULL, "=");

    }
    
}



struct Route make_route(char line[]){
    //this function takes a line from the .csv file as input and returns a single Route struct from that line

    struct Route route;
    char airline_name[40];
    char airline_icao_unique_code[40];
    char airline_country[40];
    char from_airport_name[40];
    char from_airport_city[40];
    char from_airport_country[40];
    char from_airport_icao_unique_code[40];
    float from_airport_altitude;
    char to_airport_name[40];
    char to_airport_city[40];
    char to_airport_country[40];
    char to_airport_icao_unique_code[40];
    float to_airport_altitude;


    int number = sscanf(line, "%[^,], %[^,] ,%[^,], %[^,],%[^,],%[^,],%[^,],%e,%[^,],%[^,],%[^,],%[^,],%e", airline_name, airline_icao_unique_code, airline_country, from_airport_name, from_airport_city, from_airport_country, from_airport_icao_unique_code, &from_airport_altitude, to_airport_name, to_airport_city, to_airport_country, to_airport_icao_unique_code, &to_airport_altitude);
    strcpy(route.airline_name, airline_name);
    strcpy(route.airline_icao_unique_code, airline_icao_unique_code);
    strcpy(route.airline_country, airline_country);
    strcpy(route.from_airport_name, from_airport_name);
    strcpy(route.from_airport_city, from_airport_city);
    strcpy(route.from_airport_country, from_airport_country);
    strcpy(route.from_airport_icao_unique_code, from_airport_icao_unique_code);
    route.from_airport_altitude = from_airport_altitude;
    strcpy(route.to_airport_name, to_airport_name);
    strcpy(route.to_airport_city, to_airport_city);
    strcpy(route.to_airport_country, to_airport_country);
    strcpy(route.to_airport_icao_unique_code, to_airport_icao_unique_code);
    route.to_airport_altitude = to_airport_altitude;

    return route;
}



int check_filters(struct Route *matchingRoutes, struct Route route, char* airline, char* dest_country, char* src_country, char* dest_city, char* src_city, int matched, int argc){
    //this function takes a single Route struct and all the given filters as input. It then checks if the Route matches the given filters. If it matches then it is placed in an array of Route structs

    if (argc==4){
        if (strcmp(route.airline_icao_unique_code, airline)==0 && strcmp(route.to_airport_country, dest_country)==0){
            matchingRoutes[matched] = route;
            matched++;
    
         }
         return matched;
    }

    else if (argc==5){
        if (strcmp(src_country, route.from_airport_country)==0 && strcmp(dest_city, route.to_airport_city)==0 && strcmp(dest_country, route.to_airport_country)==0){
            matchingRoutes[matched] = route;
            matched++;
        }
        return matched;
    }

    else if (argc==6){
        if(strcmp(src_city, route.from_airport_city)==0 && strcmp(src_country, route.from_airport_country)==0 && strcmp(dest_city, route.to_airport_city)==0 && strcmp(dest_country, route.to_airport_country)==0){
            matchingRoutes[matched] = route;
            matched++;
        }
        return matched;
    }
}



int process_lines(int argc, char *datasheet, struct Route *matchingRoutes, char* airline, char* dest_country, char* src_country, char* dest_city, char* src_city){
    //This function takes the .csv file and reads through all the lines and checks if each line matches the given filters. It then returns an integer of how many lines matched the filter.

    FILE* csvfile;
    csvfile = fopen(datasheet, "r");
    char line[1024];
    int count = 0;
    int matched = 0;
    int new_matched = 0;

    fgets(line, 1024, csvfile);
    while(fgets(line, 1024, csvfile)!=NULL){
        new_matched = check_filters(matchingRoutes, make_route(line), airline, dest_country, src_country, dest_city, src_city, matched, argc);
        matched = new_matched;

    }
    return matched;
}   



void output_text(int argc, struct Route *matchingRoutes, char* airline, char* dest_country, char* src_country, char* dest_city, char* src_city, int matched){
    //this function writes text to the output.txt file depending on the case and how many routes matched the filters

    FILE *outputfile;
    outputfile = fopen("output.txt", "w");
    int formatted = 0;
    int size = sizeof(matchingRoutes)/sizeof(matchingRoutes[0]);
    

    if (argc == 4){
        for (int i = 0; i<matched; i++){
            struct Route route = matchingRoutes[i];
            if (formatted == 0){
                fprintf(outputfile, "FLIGHTS TO %s BY %s (%s):\n", dest_country, route.airline_name, route.airline_icao_unique_code);
            }
            fprintf(outputfile, "FROM: %s, %s, %s TO: %s (%s), %s\n", route.from_airport_icao_unique_code, route.from_airport_city, route.from_airport_country, route.to_airport_name, route.to_airport_icao_unique_code, route.to_airport_city);
            formatted++;

        }
        if (formatted==0){
            fprintf(outputfile,"NO RESULTS FOUND.\n");
        }
    }

    else if(argc==5){
        for(int i = 0; i<matched; i++){
            struct Route route = matchingRoutes[i];
            if (formatted == 0){
                fprintf(outputfile, "FLIGHTS FROM %s TO %s, %s:\n", src_country, dest_city, dest_country);
            }
            fprintf(outputfile, "AIRLINE: %s (%s) ORIGIN: %s (%s), %s\n", route.airline_name, route.airline_icao_unique_code, route.from_airport_name, route.from_airport_icao_unique_code, route.from_airport_city);
            formatted++;
        }
        if (formatted==0){
            fprintf(outputfile,"NO RESULTS FOUND.\n");
        }
    }

    else if(argc==6){
        for(int i = 0; i<matched; i++){
            struct Route route = matchingRoutes[i];
            if(formatted==0){
                fprintf(outputfile, "FLIGHTS FROM %s, %s TO %s, %s:\n", src_city, src_country, dest_city, dest_country);
            }
            fprintf(outputfile, "AIRLINE: %s (%s) ROUTE: %s-%s\n", route.airline_name, route.airline_icao_unique_code, route.from_airport_icao_unique_code, route.to_airport_icao_unique_code);
            formatted++;
        }
        if (formatted==0){
            fprintf(outputfile, "NO RESULTS FOUND.\n");
        }
    }

    fclose(outputfile);
    exit(0);
}


int main(int argc, char *argv[])
{
        char *datasheet, *airline, *dest_country, *src_country, *dest_city, *src_city;              //creates variables for possible arguments
        getArgs(argc, argv, &datasheet, &airline, &dest_country, &src_country, &dest_city, &src_city);      //gets arguments from command line and assigns them to correct variables

        struct Route matchingRoutes[100];      //creates an array of structs to hold routes that match the given filters

        int matched = 0;    //initializing a counter to count how many routes match the filter

        matched = process_lines(argc, datasheet, matchingRoutes, airline, dest_country, src_country, dest_city, src_city); //compares every line in the .csv file and checks if it matches the filters (returns number of matched routes)

        output_text(argc, matchingRoutes,airline, dest_country, src_country, dest_city, src_city, matched);    //outputs text based on matching routes

    // TODO: your code.

    exit(0);
    
}


