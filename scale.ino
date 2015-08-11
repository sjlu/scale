int analogWeight;
const int numberOfReadings = 250;
int readings[numberOfReadings];
int atReading = 0;
int totalReading = 0;

void setup() {

    pinMode(A0, INPUT);
    Spark.variable("analogWeight", &analogWeight, INT);

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

}