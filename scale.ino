int analogWeight;
const int numberOfReadings = 500;
int readings[numberOfReadings];
int atReading = 0;
int totalReading = 0;

int lastReading = 0;
int stableReading = 0;
const int numOfStableReadings = 250;
int stableReadingsCount = 0;

bool isBetween(int num, int min, int max) {
    if (num >= min && num <= max) {
        return true;
    }
    
    return false;
}

void setup() {

    pinMode(A0, INPUT);
    // Spark.variable("analogWeight", &analogWeight, INT);

    for (int i = 0; i < numberOfReadings; i++) {
        readings[i] = 0;
    }

}

void loop() {

    totalReading = totalReading - readings[atReading];
    readings[atReading] = analogRead(A0);
    totalReading = totalReading + readings[atReading];
    atReading = atReading + 1;
    
    if (atReading >= numberOfReadings) {
        atReading = 0;
    }

    analogWeight = totalReading / numberOfReadings;

    if (isBetween(analogWeight, stableReading - 2, stableReading + 2)) {
        stableReadingsCount++;
    } else {
        stableReading = analogWeight;
        stableReadingsCount = 0;
    }
    
    

    if (stableReadingsCount == numOfStableReadings) {
        int weightChange = stableReading - lastReading;
        if (abs(weightChange) > 20) {
            Spark.publish("wChange", String(weightChange));
            lastReading = stableReading;
        }
    }

}
