/*
 * I2C-Generator: 0.2.0
 * Yaml Version: 0.1.0
 * Template Version: 0.7.0-38-g217adaf
 */
/*
 * Copyright (c) 2021, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <Arduino.h>
#include <SensirionI2CSfm3000.h>
#include <Wire.h>

SensirionI2CSfm3000 sfm;


float scalingFactor = 140.0;
float offset = 32000;


void setup() {

    Serial.begin(115200);
    while (!Serial) {
        delay(100);
    }

    Wire.begin();

    uint16_t error;
    char errorMessage[64];

    sfm.begin(Wire, SFM300_I2C_ADDRESS_0);

    uint32_t serialNumber;

    error = sfm.readSerialNumber(serialNumber);
    if (error) {
        Serial.print("Error trying to execute serialNumber(): ");
        errorToString(error, errorMessage, 64);
        Serial.println(errorMessage);
    } else {
        Serial.print("SerialNumber:");
        Serial.print(serialNumber);
        Serial.println();
    }

    error = sfm.startContinuousMeasurement();
    
    if (error) {
        Serial.print("Error trying to execute startContinuousMeasurement(): ");
        errorToString(error, errorMessage, 64);
        Serial.println(errorMessage);
    }
}

void loop() {
    uint16_t error;
    char errorMessage[64];

    delay(100);

    // Read Measurement
    float flow;

    error = sfm.readMeasurement(flow, scalingFactor, offset);

    if (error) {
        Serial.print("Error trying to execute readMeasurement(): ");
        errorToString(error, errorMessage, 64);
        Serial.println(errorMessage);
    } else {
        Serial.print("Flow:");
        Serial.print(flow);
        Serial.println();
    }
}
