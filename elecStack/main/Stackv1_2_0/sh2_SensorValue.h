/*
 * Copyright 2015-16 Hillcrest Laboratories, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License and 
 * any applicable agreements you may have with Hillcrest Laboratories, Inc.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** 
 * @file sh2_SensorValue.h 
 * @author David Wheeler
 * @date 10 Nov 2015
 * @brief Support for converting sensor events (messages) into natural data structures.
 *
 */

#ifndef SH2_SENSORVALUE_H
#define SH2_SENSORVALUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "sh2.h"
#include "sh2_err.h"
#include "sh2_util.h"

#define SCALE_Q(n) (1.0f / (1 << n))

const float scaleRadToDeg = 180.0 / 3.14159265358;


/* Note on quaternion naming conventions:
 * Quaternions are values with four real components that are usually
 * interpreted as coefficients in the complex quantity, Q.
 *
 * As in, Q = W + Xi + Yj + Zk
 *
 * Where i, j and k represent the three imaginary dimensions.
 *
 * So W represents the Real components and X, Y and Z the Imaginary ones.
 *
 * In the Hillcrest datasheets and in this code, however, the four components
 * are named real, i, j and k, to make it explicit which is which.  If you 
 * need to translate these names into the "wxyz" or "xyzw" convention, then, the
 * appropriate mapping is this:
 *     w = real
 *     x = i
 *     y = j
 *     z = k
 */
	
/**
 * @brief Raw Accelerometer
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_RawAccelerometer {
    /* Units are ADC counts */
    int16_t x;  /**< @brief [ADC counts] */
    int16_t y;  /**< @brief [ADC counts] */
    int16_t z;  /**< @brief [ADC counts] */

    /* Microseconds */
    uint32_t timestamp;  /**< @brief [uS] */
} sh2_RawAccelerometer_t;

/**
 * @brief Accelerometer
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_Accelerometer {
    float x;
    float y;
    float z;
} sh2_Accelerometer_t;

/**
 * @brief Raw gyroscope
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_RawGyroscope {
    /* Units are ADC counts */
    int16_t x;  /**< @brief [ADC Counts] */
    int16_t y;  /**< @brief [ADC Counts] */
    int16_t z;  /**< @brief [ADC Counts] */
    int16_t temperature;  /**< @brief [ADC Counts] */

    /* Microseconds */
    uint32_t timestamp;  /**< @brief [uS] */
} sh2_RawGyroscope_t;

/**
 * @brief Gyroscope
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_Gyroscope {
    /* Units are rad/s */
    float x;
    float y;
    float z;
} sh2_Gyroscope_t;

/**
 * @brief Uncalibrated gyroscope
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_GyroscopeUncalibrated {
    /* Units are rad/s */
    float x;  /**< @brief [rad/s] */
    float y;  /**< @brief [rad/s] */
    float z;  /**< @brief [rad/s] */
    float biasX;  /**< @brief [rad/s] */
    float biasY;  /**< @brief [rad/s] */
    float biasZ;  /**< @brief [rad/s] */
} sh2_GyroscopeUncalibrated_t;

/**
 * @brief Raw Magnetometer
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_RawMagnetometer {
    /* Units are ADC counts */
    int16_t x;  /**< @brief [ADC Counts] */
    int16_t y;  /**< @brief [ADC Counts] */
    int16_t z;  /**< @brief [ADC Counts] */

    /* Microseconds */
    uint32_t timestamp;  /**< @brief [uS] */
} sh2_RawMagnetometer_t;

/**
 * @brief Magnetic field
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_MagneticField {
    /* Units are uTesla */
    float x;  /**< @brief [uTesla] */
    float y;  /**< @brief [uTesla] */
    float z;  /**< @brief [uTesla] */
} sh2_MagneticField_t;

/**
 * @brief Uncalibrated magnetic field
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_MagneticFieldUncalibrated {
    /* Units are uTesla */
    float x;  /**< @brief [uTesla] */
    float y;  /**< @brief [uTesla] */
    float z;  /**< @brief [uTesla] */
    float biasX;  /**< @brief [uTesla] */
    float biasY;  /**< @brief [uTesla] */
    float biasZ;  /**< @brief [uTesla] */
} sh2_MagneticFieldUncalibrated_t;

/**
 * @brief Rotation Vector with Accuracy
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_RotationVectorWAcc {
    float i;  /**< @brief Quaternion component i */
    float j;  /**< @brief Quaternion component j */
    float k;  /**< @brief Quaternion component k */
    float real;  /**< @brief Quaternion component, real */
    float accuracy;  /**< @brief Accuracy estimate [radians] */
} sh2_RotationVectorWAcc_t;

/**
 * @brief Rotation Vector
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_RotationVector {
    float i;  /**< @brief Quaternion component i */
    float j;  /**< @brief Quaternion component j */
    float k;  /**< @brief Quaternion component k */
    float real;  /**< @brief Quaternion component real */
} sh2_RotationVector_t;

/**
 * @brief Atmospheric Pressure
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_Pressure {
    float value;  /**< @brief Atmospheric Pressure.  [hectopascals] */
} sh2_Pressure_t;

/**
 * @brief Ambient Light
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_AmbientLight {
    float value;  /**< @brief Ambient Light.  [lux] */
} sh2_AmbientLight_t;

/**
 * @brief Humidity
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_Humidity {
    float value;  /**< @brief Relative Humidity.  [percent] */
} sh2_Humidity_t;

/**
 * @brief Proximity
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_Proximity {
    float value;  /**< @brief Proximity.  [cm] */
} sh2_Proximity_t;

/**
 * @brief Temperature
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_Temperature {
    float value;  /**< @brief Temperature.  [C] */
} sh2_Temperature_t;

/**
 * @brief Reserved
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_Reserved {
    float tbd;  /**< @brief Reserved */
} sh2_Reserved_t;

/**
 * @brief TapDetector
 *
 * See the SH-2 Reference Manual for more detail.
 */
#define TAPDET_X      (1)
#define TAPDET_X_POS  (2)
#define TAPDET_Y      (4)
#define TAPDET_Y_POS  (8)
#define TAPDET_Z      (16)
#define TAPDET_Z_POS  (32)
#define TAPDET_DOUBLE (64)
typedef struct sh2_TapDetector {
    uint8_t flags;  /**< @brief TapDetector.  */
} sh2_TapDetector_t;

/**
 * @brief StepDetector
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_StepDetector {
    uint32_t latency;  /**< @brief Step detect latency [uS].  */
} sh2_StepDetector_t;

/**
 * @brief StepCounter
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_StepCounter {
    uint32_t latency;  /**< @brief Step counter latency [uS].  */
    uint16_t steps;    /**< @brief Steps counted. */
} sh2_StepCounter_t;

/**
 * @brief SigMotion
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_SigMotion {
    uint16_t motion;
} sh2_SigMotion_t;

/**
 * @brief StabilityClassifier
 *
 * See the SH-2 Reference Manual for more detail.
 */
#define STABILITY_CLASSIFIER_UNKNOWN (0)
#define STABILITY_CLASSIFIER_ON_TABLE (1)
#define STABILITY_CLASSIFIER_STATIONARY (2)
#define STABILITY_CLASSIFIER_STABLE (3)
#define STABILITY_CLASSIFIER_MOTION (4)
typedef struct sh2_StabilityClassifier {
    uint8_t classification;
} sh2_StabilityClassifier_t;

/**
 * @brief ShakeDetector
 *
 * See the SH-2 Reference Manual for more detail.
 */
#define SHAKE_X (1)
#define SHAKE_Y (2)
#define SHAKE_Z (4)
typedef struct sh2_ShakeDetector {
    uint16_t shake;
} sh2_ShakeDetector_t;

/**
 * @brief flipDetector
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_FlipDetector {
    uint16_t flip;
} sh2_FlipDetector_t;

/**
 * @brief pickupDetector
 *
 * See the SH-2 Reference Manual for more detail.
 */
#define PICKUP_LEVEL_TO_NOT_LEVEL (1)
#define PICKUP_STOP_WITHIN_REGION (2)
typedef struct sh2_PickupDetector {
    uint16_t pickup;   /**< flag field with bits defined above. */
} sh2_PickupDetector_t;

/**
 * @brief stabilityDetector
 *
 * See the SH-2 Reference Manual for more detail.
 */
#define STABILITY_ENTERED (1)
#define STABILITY_EXITED  (2)
typedef struct sh2_StabilityDetector {
    uint16_t stability;  /**< flag field with bits defined above. */
} sh2_StabilityDetector_t;

/**
 * @brief Personal Activity Classifier
 *
 * See the SH-2 Reference Manual for more detail.
 */
#define PAC_UNKNOWN (0)
#define PAC_IN_VEHICLE (1)
#define PAC_ON_BICYCLE (2)
#define PAC_ON_FOOT (3)
#define PAC_STILL (4)
#define PAC_TILTING (5)
#define PAC_WALKING (6)
#define PAC_RUNNING (7)
typedef struct sh2_PersonalActivityClassifier {
    uint8_t page;
    bool lastPage;
    uint8_t mostLikelyState;
    uint8_t confidence[10];
} sh2_PersonalActivityClassifier_t;

/**
 * @brief sleepDetector
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_SleepDetector {
    uint8_t sleepState;
} sh2_SleepDetector_t;

/**
 * @brief tiltDetector
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_TiltDetector {
    uint16_t tilt;
} sh2_TiltDetector_t;

/**
 * @brief pocketDetector
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_PocketDetector {
    uint16_t pocket;
} sh2_PocketDetector_t;

/**
 * @brief circleDetector
 *
 * See the SH-2 Reference Manual for more detail.
 */
typedef struct sh2_CircleDetector {
    uint16_t circle;
} sh2_CircleDetector_t;

/**
 * @brief heartRateMonitor
 *
 * See SH-2 Reference Manual for details.
 */
typedef struct sh2_HeartRateMonitor {
    uint16_t heartRate; /**< heart rate in beats per minute. */
} sh2_HeartRateMonitor_t;

/**
 * @brief Gyro Integrated Rotation Vector
 *
 * See SH-2 Reference Manual for details.
 */
typedef struct sh2_GyroIntegratedRV {
    float i;        /**< @brief Quaternion component i */
    float j;        /**< @brief Quaternion component j */
    float k;        /**< @brief Quaternion component k */
    float real;     /**< @brief Quaternion component real */
    float angVelX;  /**< @brief Angular velocity about x [rad/s] */
    float angVelY;  /**< @brief Angular velocity about y [rad/s] */
    float angVelZ;  /**< @brief Angular velocity about z [rad/s] */
} sh2_GyroIntegratedRV_t;

typedef struct sh2_IZroRequest {
    sh2_IZroMotionIntent_t intent;
    sh2_IZroMotionRequest_t request;
} sh2_IZroRequest_t;

typedef struct sh2_SensorValue {
    
    /** Which sensor produced this event. */
    uint8_t sensorId;

    /** @brief 8-bit unsigned integer used to track reports.
     *
     * The sequence number increments once for each report sent.  Gaps
     * in the sequence numbers indicate missing or dropped reports.
     */
    uint8_t sequence;

    /* Status of a sensor
     *   0 - Unreliable
     *   1 - Accuracy low
     *   2 - Accuracy medium
     *   3 - Accuracy high
     */
    uint8_t status; /**< @brief bits 7-5: reserved, 4-2: exponent delay, 1-0: Accuracy */

    uint64_t timestamp;  /**< [uS] */

    uint32_t delay; /**< @brief [uS] value is delay * 2^exponent (see status) */

    /** @brief Sensor Data
     *
     * Use the structure based on the value of the sensor
     * field.
     */
    union {
        sh2_RawAccelerometer_t rawAccelerometer;
        sh2_Accelerometer_t accelerometer; 
        sh2_Accelerometer_t linearAcceleration; 
        sh2_Accelerometer_t gravity; 
        sh2_RawGyroscope_t rawGyroscope; 
        sh2_Gyroscope_t gyroscope; 
        sh2_GyroscopeUncalibrated_t gyroscopeUncal; 
        sh2_RawMagnetometer_t rawMagnetometer; 
        sh2_MagneticField_t magneticField; 
        sh2_MagneticFieldUncalibrated_t magneticFieldUncal; 
        sh2_RotationVectorWAcc_t rotationVector; 
        sh2_RotationVector_t gameRotationVector; 
        sh2_RotationVectorWAcc_t geoMagRotationVector;
        sh2_Pressure_t pressure;
        sh2_AmbientLight_t ambientLight;
        sh2_Humidity_t humidity;
        sh2_Proximity_t proximity;
        sh2_Temperature_t temperature;
        sh2_Reserved_t reserved;
        sh2_TapDetector_t tapDetector;
        sh2_StepDetector_t stepDetector;
        sh2_StepCounter_t stepCounter;
        sh2_SigMotion_t sigMotion;
        sh2_StabilityClassifier_t stabilityClassifier;
        sh2_ShakeDetector_t shakeDetector;
        sh2_FlipDetector_t flipDetector;
        sh2_PickupDetector_t pickupDetector;
        sh2_StabilityDetector_t stabilityDetector;
        sh2_PersonalActivityClassifier_t personalActivityClassifier;
        sh2_SleepDetector_t sleepDetector;
        sh2_TiltDetector_t tiltDetector;
        sh2_PocketDetector_t pocketDetector;
        sh2_CircleDetector_t circleDetector;
        sh2_HeartRateMonitor_t heartRateMonitor;
        sh2_RotationVectorWAcc_t arvrStabilizedRV;
        sh2_RotationVector_t arvrStabilizedGRV;
        sh2_GyroIntegratedRV_t gyroIntegratedRV;
        sh2_IZroRequest_t izroRequest;
    } un;
} sh2_SensorValue_t;

int sh2_decodeSensorEvent(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);

// ------------------------------------------------------------------------
// Forward declarations

static int decodeRawAccelerometer(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeAccelerometer(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeLinearAcceleration(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeGravity(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeRawGyroscope(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeGyroscopeCalibrated(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeGyroscopeUncal(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeRawMagnetometer(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeMagneticFieldCalibrated(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeMagneticFieldUncal(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeRotationVector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeGameRotationVector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeGeomagneticRotationVector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodePressure(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeAmbientLight(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeHumidity(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeProximity(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeTemperature(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeReserved(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeTapDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeStepDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeStepCounter(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeSignificantMotion(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeStabilityClassifier(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeShakeDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeFlipDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodePickupDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeStabilityDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodePersonalActivityClassifier(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeSleepDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeTiltDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodePocketDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeCircleDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeHeartRateMonitor(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeArvrStabilizedRV(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeArvrStabilizedGRV(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeGyroIntegratedRV(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);
static int decodeIZroRequest(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event);

// ------------------------------------------------------------------------
// Public API

int sh2_decodeSensorEvent(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    // Fill out fields of *value based on *event, converting data from message representation
    // to natural representation.

    int rc = SH2_OK;

    value->sensorId = event->reportId;
    value->timestamp = event->timestamp_uS;

    if (value->sensorId != SH2_GYRO_INTEGRATED_RV) {
        value->sequence = event->report[1];
        value->status = event->report[2] & 0x03;
    }
    else {
        value->sequence = 0;
        value->status = 0;
    }

    // extract delay field (100uS units)
    
    
    switch (value->sensorId) {
        case SH2_RAW_ACCELEROMETER:
            rc = decodeRawAccelerometer(value, event);
            break;
        case SH2_ACCELEROMETER:
            rc = decodeAccelerometer(value, event);
            break;
        case SH2_LINEAR_ACCELERATION:
            rc = decodeLinearAcceleration(value, event);
            break;
        case SH2_GRAVITY:
            rc = decodeGravity(value, event);
            break;
        case SH2_RAW_GYROSCOPE:
            rc = decodeRawGyroscope(value, event);
            break;
        case SH2_GYROSCOPE_CALIBRATED:
            rc = decodeGyroscopeCalibrated(value, event);
            break;
        case SH2_GYROSCOPE_UNCALIBRATED:
            rc = decodeGyroscopeUncal(value, event);
            break;
        case SH2_RAW_MAGNETOMETER:
            rc = decodeRawMagnetometer(value, event);
            break;
        case SH2_MAGNETIC_FIELD_CALIBRATED:
            rc = decodeMagneticFieldCalibrated(value, event);
            break;
        case SH2_MAGNETIC_FIELD_UNCALIBRATED:
            rc = decodeMagneticFieldUncal(value, event);
            break;
        case SH2_ROTATION_VECTOR:
            rc = decodeRotationVector(value, event);
            break;
        case SH2_GAME_ROTATION_VECTOR:
            rc = decodeGameRotationVector(value, event);
            break;
        case SH2_GEOMAGNETIC_ROTATION_VECTOR:
            rc = decodeGeomagneticRotationVector(value, event);
            break;
        case SH2_PRESSURE:
            rc = decodePressure(value, event);
            break;
        case SH2_AMBIENT_LIGHT:
            rc = decodeAmbientLight(value, event);
            break;
        case SH2_HUMIDITY:
            rc = decodeHumidity(value, event);
            break;
        case SH2_PROXIMITY:
            rc = decodeProximity(value, event);
            break;
        case SH2_TEMPERATURE:
            rc = decodeTemperature(value, event);
            break;
        case SH2_RESERVED:
            rc = decodeReserved(value, event);
            break;
        case SH2_TAP_DETECTOR:
            rc = decodeTapDetector(value, event);
            break;
        case SH2_STEP_DETECTOR:
            rc = decodeStepDetector(value, event);
            break;
        case SH2_STEP_COUNTER:
            rc = decodeStepCounter(value, event);
            break;
        case SH2_SIGNIFICANT_MOTION:
            rc = decodeSignificantMotion(value, event);
            break;
        case SH2_STABILITY_CLASSIFIER:
            rc = decodeStabilityClassifier(value, event);
            break;
        case SH2_SHAKE_DETECTOR:
            rc = decodeShakeDetector(value, event);
            break;
        case SH2_FLIP_DETECTOR:
            rc = decodeFlipDetector(value, event);
            break;
        case SH2_PICKUP_DETECTOR:
            rc = decodePickupDetector(value, event);
            break;
        case SH2_STABILITY_DETECTOR:
            rc = decodeStabilityDetector(value, event);
            break;
        case SH2_PERSONAL_ACTIVITY_CLASSIFIER:
            rc = decodePersonalActivityClassifier(value, event);
            break;
        case SH2_SLEEP_DETECTOR:
            rc = decodeSleepDetector(value, event);
            break;
        case SH2_TILT_DETECTOR:
            rc = decodeTiltDetector(value, event);
            break;
        case SH2_POCKET_DETECTOR:
            rc = decodePocketDetector(value, event);
            break;
        case SH2_CIRCLE_DETECTOR:
            rc = decodeCircleDetector(value, event);
            break;
        case SH2_HEART_RATE_MONITOR:
            rc = decodeHeartRateMonitor(value, event);
            break;
        case SH2_ARVR_STABILIZED_RV:
            rc = decodeArvrStabilizedRV(value, event);
            break;
        case SH2_ARVR_STABILIZED_GRV:
            rc = decodeArvrStabilizedGRV(value, event);
            break;
        case SH2_GYRO_INTEGRATED_RV:
            rc = decodeGyroIntegratedRV(value, event);
            break;
        case SH2_IZRO_MOTION_REQUEST:
            rc = decodeIZroRequest(value, event);
            break;
        default:
            // Unknown report id
            rc = SH2_ERR;
            break;
    }

    return rc;
}

// ------------------------------------------------------------------------
// Private utility functions

static int decodeRawAccelerometer(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.rawAccelerometer.x = read16(&event->report[4]);
    value->un.rawAccelerometer.y = read16(&event->report[6]);
    value->un.rawAccelerometer.z = read16(&event->report[8]);
    value->un.rawAccelerometer.timestamp = read32(&event->report[12]);

    return SH2_OK;
}

static int decodeAccelerometer(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.accelerometer.x = read16(&event->report[4]) * SCALE_Q(8);
    value->un.accelerometer.y = read16(&event->report[6]) * SCALE_Q(8);
    value->un.accelerometer.z = read16(&event->report[8]) * SCALE_Q(8);

    return SH2_OK;
}

static int decodeLinearAcceleration(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.linearAcceleration.x = read16(&event->report[4]) * SCALE_Q(8);
    value->un.linearAcceleration.y = read16(&event->report[6]) * SCALE_Q(8);
    value->un.linearAcceleration.z = read16(&event->report[8]) * SCALE_Q(8);

    return SH2_OK;
}

static int decodeGravity(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.gravity.x = read16(&event->report[4]) * SCALE_Q(8);
    value->un.gravity.y = read16(&event->report[6]) * SCALE_Q(8);
    value->un.gravity.z = read16(&event->report[8]) * SCALE_Q(8);

    return SH2_OK;
}

static int decodeRawGyroscope(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.rawGyroscope.x = read16(&event->report[4]);
    value->un.rawGyroscope.y = read16(&event->report[6]);
    value->un.rawGyroscope.z = read16(&event->report[8]);
    value->un.rawGyroscope.temperature = read16(&event->report[10]);
    value->un.rawGyroscope.timestamp = read32(&event->report[12]);

    return SH2_OK;
}

static int decodeGyroscopeCalibrated(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.gyroscope.x = read16(&event->report[4]) * SCALE_Q(9);
    value->un.gyroscope.y = read16(&event->report[6]) * SCALE_Q(9);
    value->un.gyroscope.z = read16(&event->report[8]) * SCALE_Q(9);

    return SH2_OK;
}

static int decodeGyroscopeUncal(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.gyroscopeUncal.x = read16(&event->report[4]) * SCALE_Q(9);
    value->un.gyroscopeUncal.y = read16(&event->report[6]) * SCALE_Q(9);
    value->un.gyroscopeUncal.z = read16(&event->report[8]) * SCALE_Q(9);

    value->un.gyroscopeUncal.biasX = read16(&event->report[10]) * SCALE_Q(9);
    value->un.gyroscopeUncal.biasY = read16(&event->report[12]) * SCALE_Q(9);
    value->un.gyroscopeUncal.biasZ = read16(&event->report[14]) * SCALE_Q(9);

    return SH2_OK;
}

static int decodeRawMagnetometer(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.rawMagnetometer.x = read16(&event->report[4]);
    value->un.rawMagnetometer.y = read16(&event->report[6]);
    value->un.rawMagnetometer.z = read16(&event->report[8]);
    value->un.rawMagnetometer.timestamp = read32(&event->report[12]);

    return SH2_OK;
}

static int decodeMagneticFieldCalibrated(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.magneticField.x = read16(&event->report[4]) * SCALE_Q(4);
    value->un.magneticField.y = read16(&event->report[6]) * SCALE_Q(4);
    value->un.magneticField.z = read16(&event->report[8]) * SCALE_Q(4);

    return SH2_OK;
}

static int decodeMagneticFieldUncal(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.magneticFieldUncal.x = read16(&event->report[4]) * SCALE_Q(4);
    value->un.magneticFieldUncal.y = read16(&event->report[6]) * SCALE_Q(4);
    value->un.magneticFieldUncal.z = read16(&event->report[8]) * SCALE_Q(4);

    value->un.magneticFieldUncal.biasX = read16(&event->report[10]) * SCALE_Q(4);
    value->un.magneticFieldUncal.biasY = read16(&event->report[12]) * SCALE_Q(4);
    value->un.magneticFieldUncal.biasZ = read16(&event->report[14]) * SCALE_Q(4);

    return SH2_OK;
}

static int decodeRotationVector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.rotationVector.i = read16(&event->report[4]) * SCALE_Q(14);
    value->un.rotationVector.j = read16(&event->report[6]) * SCALE_Q(14);
    value->un.rotationVector.k = read16(&event->report[8]) * SCALE_Q(14);
    value->un.rotationVector.real = read16(&event->report[10]) * SCALE_Q(14);
    value->un.rotationVector.accuracy = read16(&event->report[12]) * SCALE_Q(12);

    return SH2_OK;
}

static int decodeGameRotationVector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.gameRotationVector.i = read16(&event->report[4]) * SCALE_Q(14);
    value->un.gameRotationVector.j = read16(&event->report[6]) * SCALE_Q(14);
    value->un.gameRotationVector.k = read16(&event->report[8]) * SCALE_Q(14);
    value->un.gameRotationVector.real = read16(&event->report[10]) * SCALE_Q(14);

    return SH2_OK;
}

static int decodeGeomagneticRotationVector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.geoMagRotationVector.i = read16(&event->report[4]) * SCALE_Q(14);
    value->un.geoMagRotationVector.j = read16(&event->report[6]) * SCALE_Q(14);
    value->un.geoMagRotationVector.k = read16(&event->report[8]) * SCALE_Q(14);
    value->un.geoMagRotationVector.real = read16(&event->report[10]) * SCALE_Q(14);
    value->un.geoMagRotationVector.accuracy = read16(&event->report[12]) * SCALE_Q(12);

    return SH2_OK;
}

static int decodePressure(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.pressure.value = read32(&event->report[4]) * SCALE_Q(20);

    return SH2_OK;
}

static int decodeAmbientLight(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.ambientLight.value = read32(&event->report[4]) * SCALE_Q(8);

    return SH2_OK;
}

static int decodeHumidity(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.humidity.value = read16(&event->report[4]) * SCALE_Q(8);

    return SH2_OK;
}

static int decodeProximity(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.proximity.value = read16(&event->report[4]) * SCALE_Q(4);

    return SH2_OK;
}

static int decodeTemperature(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.temperature.value = read16(&event->report[4]) * SCALE_Q(7);

    return SH2_OK;
}

static int decodeReserved(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.reserved.tbd = read16(&event->report[4]) * SCALE_Q(7);

    return SH2_OK;
}

static int decodeTapDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.tapDetector.flags = event->report[4];

    return SH2_OK;
}

static int decodeStepDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.stepDetector.latency = readu32(&event->report[4]);

    return SH2_OK;
}

static int decodeStepCounter(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.stepCounter.latency = readu32(&event->report[4]);
    value->un.stepCounter.steps = readu32(&event->report[8]);

    return SH2_OK;
}

static int decodeSignificantMotion(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.sigMotion.motion = readu16(&event->report[4]);

    return SH2_OK;
}

static int decodeStabilityClassifier(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.stabilityClassifier.classification = event->report[4];

    return SH2_OK;
}

static int decodeShakeDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.shakeDetector.shake = readu16(&event->report[4]);

    return SH2_OK;
}

static int decodeFlipDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.flipDetector.flip = readu16(&event->report[4]);

    return SH2_OK;
}

static int decodePickupDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.pickupDetector.pickup = readu16(&event->report[4]);

    return SH2_OK;
}

static int decodeStabilityDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.stabilityDetector.stability = readu16(&event->report[4]);

    return SH2_OK;
}

static int decodePersonalActivityClassifier(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.personalActivityClassifier.page = event->report[4] & 0x7F;
    value->un.personalActivityClassifier.lastPage = ((event->report[4] & 0x80) != 0);
    value->un.personalActivityClassifier.mostLikelyState = event->report[5];
    for (int n = 0; n < 10; n++) {
        value->un.personalActivityClassifier.confidence[n] = event->report[6+n];
    }
    
    return SH2_OK;
}

static int decodeSleepDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.sleepDetector.sleepState = event->report[4];

    return SH2_OK;
}

static int decodeTiltDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.tiltDetector.tilt = readu16(&event->report[4]);

    return SH2_OK;
}

static int decodePocketDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.pocketDetector.pocket = readu16(&event->report[4]);

    return SH2_OK;
}

static int decodeCircleDetector(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.circleDetector.circle = readu16(&event->report[4]);

    return SH2_OK;
}

static int decodeHeartRateMonitor(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.heartRateMonitor.heartRate = readu16(&event->report[4]);

    return SH2_OK;
}

static int decodeArvrStabilizedRV(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.arvrStabilizedRV.i = read16(&event->report[4]) * SCALE_Q(14);
    value->un.arvrStabilizedRV.j = read16(&event->report[6]) * SCALE_Q(14);
    value->un.arvrStabilizedRV.k = read16(&event->report[8]) * SCALE_Q(14);
    value->un.arvrStabilizedRV.real = read16(&event->report[10]) * SCALE_Q(14);
    value->un.arvrStabilizedRV.accuracy = read16(&event->report[12]) * SCALE_Q(12);

    return SH2_OK;
}

static int decodeArvrStabilizedGRV(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.arvrStabilizedGRV.i = read16(&event->report[4]) * SCALE_Q(14);
    value->un.arvrStabilizedGRV.j = read16(&event->report[6]) * SCALE_Q(14);
    value->un.arvrStabilizedGRV.k = read16(&event->report[8]) * SCALE_Q(14);
    value->un.arvrStabilizedGRV.real = read16(&event->report[10]) * SCALE_Q(14);

    return SH2_OK;
}

static int decodeGyroIntegratedRV(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.gyroIntegratedRV.i = read16(&event->report[0]) * SCALE_Q(14);
    value->un.gyroIntegratedRV.j = read16(&event->report[2]) * SCALE_Q(14);
    value->un.gyroIntegratedRV.k = read16(&event->report[4]) * SCALE_Q(14);
    value->un.gyroIntegratedRV.real = read16(&event->report[6]) * SCALE_Q(14);
    value->un.gyroIntegratedRV.angVelX = read16(&event->report[8]) * SCALE_Q(10);
    value->un.gyroIntegratedRV.angVelY = read16(&event->report[10]) * SCALE_Q(10);
    value->un.gyroIntegratedRV.angVelZ = read16(&event->report[12]) * SCALE_Q(10);

    return SH2_OK;
}

static int decodeIZroRequest(sh2_SensorValue_t *value, const sh2_SensorEvent_t *event)
{
    value->un.izroRequest.intent = (sh2_IZroMotionIntent_t)event->report[4];
    value->un.izroRequest.request = (sh2_IZroMotionRequest_t)event->report[5];

    return SH2_OK;
}



#ifdef __cplusplus
} // extern "C"
#endif

#endif
