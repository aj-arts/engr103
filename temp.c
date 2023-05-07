#include <stdio.h>

const int TEMPERATUREDATA[150] = {-138,-473,190,-441,1263,1426,40,926,672,1236,711,868,67,-71,1282,1030,362,623,-433,635,1429,1302,-478,558,569,-333,893,-44,511,-458,-271,873,-79,419,1284,37,698,-176,-185,-130,-87,1026,-409,480,1456,1373,362,670,496,781,-195,425,584,-173,-164,5,346,1229,813,1357,-376,1395,1082,45,314,867,934,-136,-457,1250,587,308,776,678,1288,1084,903,151,254,-101,1432,560,1176,868,1239,-488,-274,86,-406,1039,295,70,934,-122,967,101,-403,402,817,-8,152,256,801,-220,-214,941,1365,1189,-56,119,-60,229,-469,-383,-403,1271,-19,175,209,427,67,1356,997,-147,86,465,806,183,-281,124,1028,371,1232,329,1003,-481,-230,868,1208,215,-160,-351,1296,223,118,-255,346,951,421,1055};


/*

* void printHistogram()

* float *data : Pointer to an array of floats that will be processed for the histogram

* int size : The number of elements to process in the array (starts with 0 always)

* int range : Largest number for the histogram scale

* int bin_size : How big each bin of the histogram will be

* returns nothing but prints a lot of info.

*/

void printHistogram(float *data, int size, int range, int bin_size) {

    int histogram[range / bin_size];

    for (int i = 0; i < range / bin_size; i++) {

        histogram[i] = 0;

    }

    for (int i = 0; i < size; i++) {

        if (data[i] < range) {

            histogram[(int)data[i] / bin_size]++;

        }

    }

    for (int i = 0; i < range / bin_size; i++) {

        printf("%d - %d: ", i * bin_size, (i + 1) * bin_size - 1);

        for (int j = 0; j < histogram[i]; j++) {

            printf("*");

        }

        printf("\n");

    }

}


float makeVoltage(int value){

    if (value < 0 || value > 1023) //Checks if the value is in range

        return -1;

    return (5.0/1024 * value); //calculates the voltage based on a 10 bit input int

}


float makeCelsius(int value){

    if (value < 0 || value > 1023) //Checks if the value is in range

        return -1;

    return (.01 * (value - 511)); //calculates the degrees in Celsius based on a 10 bit input int

}

float makeFarheneit(int value){

    if (value < 0 || value > 1023) //Checks if the value is in range

        return -1;

    return (1.8 * makeCelsius(value) + 32); //calculates the degrees in Farheneit based on a 10 bit input int

}

void printIntArray(int *array, int size){

    for (int i = 0; i < size; i++){

        printf("%d ", array[i]);

    }

    printf("\n");
}

void printFloatArray(float *array, int size){

    for (int i = 0; i < size; i++){

        printf("%f ", array[i]);

    }

    printf("\n");
}

float averageValue(float *array, int size){

    float sum = 0;

    for (int i = 0; i < size; i++){

        sum += array[i];

    }

    return sum / size;

}

int main(){
    int sizeOfOldArray = sizeof(TEMPERATUREDATA) / sizeof(TEMPERATUREDATA[0]);
    int sizeOfNewArray = 0;
    for(int i = 0; i < sizeOfOldArray; i++){
        if(TEMPERATUREDATA[i] > 0 && TEMPERATUREDATA[i] < 1023){
            sizeOfNewArray++;
        }
    }

    int filteredData[sizeOfNewArray];
    for (int i = 0; i < sizeOfNewArray; i++) {
        for (int j = 0; j < sizeOfOldArray; j++){
            if (TEMPERATUREDATA[j] > 0 && TEMPERATUREDATA[j] < 1023)
            {
                filteredData[i] = TEMPERATUREDATA[j];
                i++;
            }
        }
    }

    float filteredDataFloat[sizeOfNewArray];
    for (int i = 0; i < sizeOfNewArray; i++) {
        filteredDataFloat[i] = filteredData[i];
    }

    int max = 0;
    int min = 0;
    for (int i = 0; i < sizeOfNewArray; i++) {
        if (filteredData[i] > filteredData[max]) {
            max = i;
        }
        if (filteredData[i] < filteredData[min]) {
            min = i;
        }
    }

    float celsiusData[sizeOfNewArray];
    for (int i = 0; i < sizeOfNewArray; i++) {
        celsiusData[i] = makeCelsius(filteredData[i]);
    }

    float voltageData[sizeOfNewArray];
    for (int i = 0; i < sizeOfNewArray; i++) {
        voltageData[i] = makeVoltage(filteredData[i]);
    }

    float farheneitData[sizeOfNewArray];
    for (int i = 0; i < sizeOfNewArray; i++) {
        farheneitData[i] = makeFarheneit(filteredData[i]);
    }

    printHistogram(filteredDataFloat, sizeOfNewArray, filteredDataFloat[max], 100);

    printf("The average, high and low for the temperature data in Celsius is: %f, %f, %f\n", averageValue(celsiusData, sizeOfNewArray), celsiusData[max], celsiusData[min]);
    printf("The average, high and low for the temperature data in Farheneit is: %f, %f, %f\n", averageValue(farheneitData, sizeOfNewArray), farheneitData[max], farheneitData[min]);
    printf("The average, high and low for the temperature data in Voltage is: %f, %f, %f\n", averageValue(voltageData, sizeOfNewArray), voltageData[max], voltageData[min]);

    printf("The percentage of bad data is: %d%% \n", (sizeOfOldArray - sizeOfNewArray) * 100 / sizeOfOldArray);

    return 0;
}