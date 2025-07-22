// Aden Hilderbrand
// fuelConsumption.c
// 12/3/24
// this program determines fuel consumption based on user input 

#include <stdio.h>

int main(){
// init var
    int altitude, aircraft_type;
    float fuel_used;
    
// prompt for altitude (between 0 and 50,000) if invalid input, altitude = 1000
    printf("Enter altitude (in feet, between 0 and 50,000) : ");
    scanf("%d", &altitude);
    
    if (altitude < 0 || altitude > 50000){
        altitude = 1000;
    }
// prompt for aircraft type (1=propeller-driven, 2=jet-powered) if invalid input, print error message and attempt again
        printf("Enter aircraft type (1=propeller-driven, 2=jet-powered) : ");
        scanf("%d", &aircraft_type);
        
        if (aircraft_type != 1 && aircraft_type != 2){
            do {
                printf("Invalid. Enter 1 or 2 : ");
                scanf("%d", &aircraft_type);
            } while (aircraft_type != 1 && aircraft_type != 2);
        }
// find fuel consumption
// propeller-driven : fuel consumption = altitude in feet / 100.0
    if (aircraft_type == 1){
        fuel_used = altitude / 100.0;
// jet-powered : fuel consumption = altitude in feet / 200.0
    } else if (aircraft_type == 2){
        fuel_used = altitude / 200.0;
    }

    printf("Fuel consumption: %.2f GPH\n", fuel_used);   

    return 0;
}
