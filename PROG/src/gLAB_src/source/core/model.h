/****************************************************************************
   Copyright & License:
   ====================

   Copyright 2009 - 2018 gAGE/UPC & ESA

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 ***************************************************************************/

/****************************************************************************
 * Copyright: gAGE/UPC & ESA
 * Project: EDUNAV GNSS Lab Tool 
 * Supervisor: Jaume Sanz Subirana (group of Astronomy and GEomatics - gAGE/UPC)
 * Author: Pere Ramos-Bosch (group of Astronomy and GEomatics - gAGE/UPC)
 * Curator: Adria Rovira-Garcia ( gAGE/UPC )
 * Developers: Deimos Ibanez Segura ( gAGE/UPC )
 *             Jesus Romero Sanchez ( gAGE/UPC ) 
 *          glab.gage @ upc.edu
 * File: model.h
 * Code Management Tool File Version: 5.2  Revision: 0
 * Date: 2018/03/09
 ***************************************************************************/

/****************************************************************************
 * MODULE DESCRIPTION
 *
 * Name: model
 * Language: C
 *
 * Purpose:
 *  The purpose of this module is to fully model an epoch of data
 *
 * Function:
 *  This class is in charge of modeling an epoch of data. This module is fully
 *  configurable through a Toptions structure, being able to connect or disconnect
 *  each model separately.
 *
 * Dependencies:
 *  dataHandling, preprocessing
 *
 * Files modified:
 *  None
 *
 * Files read:
 *  None
 *
 * Resources usage:
 *  See Design Document
 ****************************************************************************/

/****************************
 *       RELEASE_HISTORY
 * -------------
 *          gLAB v1.3.1
 * Release: 2010/01/22
 * Change Log: First public version
 * -------------
 *          gLAB v1.3.2
 * Release: 2010/02/23
 * Change Log: Inertial/non-inertial velocity switch included
 *             TGDs from DCB files
 * -------------
 *          gLAB v1.4.0
 * Release: 2010/06/21
 * Change Log: No changes in this file
 * -------------
 *          gLAB v1.4.1
 * Release: 2010/07/09
 * Change Log: No changes in this file.
 * -------------
 *          gLAB v1.4.2
 * Release: 2010/07/31
 * Change Log: No changes in this file.
 * -------------
 *          gLAB v1.4.3
 * Release: 2010/08/31
 * Change Log: No changes in this file.
 * -------------
 *          gLAB v1.4.4
 * Release: 2010/09/22
 * Change Log: No changes in this file.
 * -------------
 *          gLAB v1.4.5
 * Release: 2010/10/31
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.0.0
 * Release: 2012/12/31
 * Change Log: gLAB version released together with the Educational Book:
 *             "GNSS Data Processing" (Vol. 1 and Vol. 2). ESA TM-23.
 *             Authors: J. Sanz Subirana, J.M. Juan Zornoza and M. Hernandez-Pajares
 *             ISBN: 978-92-9221-885-0 (two volumes)
 *             ISSN: 1013-7076
 *             December 2012.
 * -----------
 *          gLAB v2.2.0
 * Release: 2014/09/22
 * Change Log: Added functions for BeiDou, IONEX, Fast-PPP and NeQuick ionosphere models.
 *             Added functions for using Fast-PPP and IONEX DCBs.
 *             Added functions for ESA's troposphere model.
 * -----------
 *          gLAB v2.2.1
 * Release: 2014/12/23
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.2.2
 * Release: 2015/03/02
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.2.3
 * Release: 2015/05/28
 * Change Log: Added satellitePhaseCenterVarCorrection and receiverPhaseCenterVarCorrection functions for phase variation correction.
 * -----------
 *          gLAB v2.2.4
 * Release: 2015/07/01
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.2.5
 * Release: 2015/10/20
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.2.6
 * Release: 2015/11/25
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.2.7
 * Release: 2016/03/01
 * Change Log: Fixed iono sigma not being transformed from TECUs to meters of the frequency of the measurement in the filter
 * -----------
 *          gLAB v2.2.8
 * Release: 2016/04/12
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v3.0.0
 * Release: 2016/09/05 
 * Change Log: Added SBAS processing.
 *             Concatenated RINEX and SP3 files can be read now.
 * -----------
 *          gLAB v3.1.0
 * Release: 2016/09/26
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v3.1.1
 * Release: 2016/10/21
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v4.0.0
 * Release: 2017/03/03
 * Change Log: Added DGNSS processing.
 *             Added function NEU2XYZ.
 * -----------
 *          gLAB v4.1.0
 * Release: 2017/04/07
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v4.2.0
 * Release: 2017/05/22
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.0.0
 * Release: 2017/06/30
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.1.0
 * Release: 2017/11/24
 * Change Log:   Added functions for 'XYZ2Spherical' and 'Spherical2XYZ' for coordinate conversion.
 * -----------
 *          gLAB v5.1.1
 * Release: 2017/12/22
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.1.2
 * Release: 2018/01/12
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.1.3
 * Release: 2018/01/19
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.2.0
 * Release: 2018/03/09
 * Change Log: No changes in this file.
 * -----------
 *       END_RELEASE_HISTORY
 *****************************/

#ifndef MODEL_H_
#define MODEL_H_

/* System modules */
#include <stdio.h>
#include <math.h>

/* External classes */
#include "dataHandling.h"
#include "preprocessing.h"

/* Internal types, constants and data */

// Orientation routines
void getSatelliteOrientationACR (double *position, double *velocity, double orientation[3][3]);
void getSatelliteOrientation (TTime *t, double *position, double orientation[3][3]);
void fillSatelliteOrientation (TEpoch *epoch, int satIndex);
void XYZ2Spherical (double  *positionXYZ, double *positionSph);
void Spherical2XYZ (double  *positionSph, double *positionXYZ);
void XYZ2NEU (double *positionXYZ, double *positionNEU);
void NEU2XYZ (double *positionNEU, double *positionXYZ);
void fillGroundStationNEU (TEpoch *epoch);
void getGroundStationOrientation (double *position, double orientation[3][3]);
void fillGroundStationOrientation (TEpoch *epoch);
void getAzimuthElevation (double orientation[3][3], double *receiverPosition, double *satellitePosition, double *azimuth, double *elevation);
void fillAzimuthElevation (TEpoch *epoch, int satIndex);
void rotate (double *v, double angle, int axis);

// Transmission time estimation
int fillTransmissionTimeSat (TEpoch *epoch, TGNSSproducts *products, int ind, TSBAScorr *SBAScorr, TOptions *options);
void fillTransmissionTime (TEpoch *epoch, TGNSSproducts *products, TSBAScorr *SBAScorr, TOptions *options);
double computeFlightTime (TEpoch *epoch, TGNSSproducts *products, int satIndex, TSBAScorr *SBAScorr, TOptions *options);
void correctEarthRotation (double *x, double flightTime);

// Orbits and clocks products
double nsteffensen (double Mk, double e);
int satellitePhaseCenterCorrection3D (TTime *t, enum GNSSystem GNSS, int PRN, enum MeasurementType meas, double orientation[3][3], TConstellation *constellation, double *dr);
int satellitePhaseCenterCorrection (TTime *t, enum GNSSystem GNSS, int PRN, enum MeasurementType meas, double orientation[3][3], double *LoS, TConstellation *constellation, double *pc);
int satellitePhaseCenterVarCorrection (TTime *t, enum GNSSystem GNSS, int PRN, enum MeasurementType meas, double satearthdistance, double elevation, TConstellation *constellation, double *pvc);
double getClockBRDC (TBRDCblock *block,TTime *t);
void getPositionBRDC (TBRDCproducts *products, TBRDCblock *block,TTime *t, enum GNSSystem GNSS,double *position);
void getVelocityBRDC (TBRDCproducts *products, TBRDCblock *block,TTime *t,double *position, double *velocity, enum SatelliteVelocity satVel, enum GNSSystem GNSS);
double getClockSP3 (TGNSSproducts *products, TTime *t,enum GNSSystem GNSS,int PRN, TOptions *options);
int getPositionSP3 (TGNSSproducts *products, TTime *t,enum GNSSystem GNSS,int PRN, double *position, TOptions *options);
int getVelocitySP3 (TGNSSproducts *products, TTime *t,enum GNSSystem GNSS,int PRN, double *position, double *velocity, enum SatelliteVelocity satVel, TOptions *options);
int getSatellitePVTBRDCraw (TGNSSproducts *products, TTime *t, enum GNSSystem GNSS, int PRN, double *position, double *velocity, double *ITRFvel, double *clock, int SBASIOD, TOptions *options);
int getSatellitePVTSP3raw (TGNSSproducts *products, TTime *t, enum GNSSystem GNSS, int PRN, double *position, double *velocity, double *ITRFvel, double *clock, TOptions *options);
int getSatellitePVT (TGNSSproducts *products, TTime *t, double flightTime, enum GNSSystem GNSS, int PRN, double *position, double *velocity, double *ITRFvel, double *clock, int SBASIOD, TOptions *options);
int fillSatellitePVT (TEpoch *epoch, TGNSSproducts *products, TTime *t, double flightTime, int satIndex, int position, int velocity, int clock, int SBASIOD, TConstellation *constellation, TOptions *options);
void getLineOfSight (double *satPos, double *recPos, double *LoS);
void fillLineOfSight (TEpoch *epoch, int satIndex);
void findMoon (TTime *t, double* moonPosition);
void findSun (TTime *t, double* sunPosition);
void GSDtime_sun (TTime *t,double *gstr, double *slong, double *sra, double *sdec);

// Receiver antenna corrections
double receiverPhaseCenterCorrection (TAntenna *antenna, enum GNSSystem GNSS, enum MeasurementType meas, double orientation[3][3], double *LoS);
double receiverPhaseCenterVarCorrection (TAntenna *antenna, enum GNSSystem GNSS, enum MeasurementType meas, double elevation);
double receiverARPCorrection (double *ARP, double orientation[3][3], double *LoS);

// Relativistic correction
double relativisticCorrection (double *position, double *velocity);

// Wind up correction
double windUpCorrection (TEpoch *epoch, int satIndex);

// Tropospheric correction
double interpolateNiell (double x, double v[3][5], int i);
double xmNiell (double elevation, double vector[3]);
void tropNiell (TTime *t,double *positionNEU,double elevation,double *tropDryMap,double *tropWetMap);
double troposphericCorrection (TTime *t, double *positionNEU, double elevation, TTROPOGal *TropoGal, double *tropWetMap, double *ZTD, TOptions *options);
void troposphericCorrectionMOPS (TTime *t, double *positionNEU, double elevation,double *tropWetMOPS_Nominal,double *tropDryMOPS_Nominal);
void troposphericCorrectionGal (TTime *t, double *positionNEU, double elevation, TTROPOGal *TropoGal, double *tropWetESA_Nominal, double *tropDryESA_Nominal);
void troposphericGalparameters (TTime  *t, int ilat, int ilon, double latitude, double longitude, double  *positionNEU, double  elevation, double MapPoints[4][3], double *hgt_pix, TTROPOGal *TropoGal, TTROPOGalParameters *parameters); 

// Ionospheric correction
double klobucharModel (TEpoch *epoch,TGNSSproducts *products, int satIndex);
double beiDouKlobucharModel (TEpoch *epoch, TGNSSproducts *products, int satIndex);
double ionexModel (TEpoch *epoch, int satIndex, TIONEX *ionex, TOptions *options);
double FPPPModel (TEpoch *epoch, int satIndex, TFPPPIONEX *fppp, TOptions *options);
double NeQuickfunctionCall (TEpoch *epoch, int satIndex,TGNSSproducts *products, TOptions *options);

// Gravitational delay correction
double gravitationalDelayCorrection (double *receiverPosition, double *satellitePosition);

// TGD correction
void getTGDfromDCB (TTGDdata *tgdData, TReceiver *rec, enum GNSSystem GNSS, int PRN, TTime *t, enum MeasurementType measFrom, enum MeasurementType measTo, double *dcb, int *retDCB, int *retDCBC1P1);
double TGDCorrectionBRDC (TEpoch *epoch, int satIndex, int SBASIOD, TTime *t, TBRDCproducts *products, TOptions *options);
double TGDCorrectionIONEX (TEpoch *epoch, int satIndex,TIonexDCB *ionexDCB,TOptions *options);
double TGDCorrectionFPPP (TEpoch *epoch, int satIndex,TFPPPDCB *fpppDCB,TOptions *options);
double TGDCorrection (TEpoch *epoch, int satIndex, TTime *t, enum MeasurementType meas, int SBASIOD, TTGDdata *tgdData, TOptions *options);

// Solid tides
void fillSolidTideDisplacement (TEpoch *epoch);
double solidTidesCorrection (TEpoch *epoch, int satIndex);

// General
void fillGeometricDistance (TEpoch *epoch,int satIndex);
int fillMeasurementWeights (TEpoch *epoch, int satIndex, double SBASsigma, double DGNSSsigma, TOptions *options);

// ANTEX
TAntenna *getAntenna (char *name, TAntennaList *antennaList, TOptions *options);

// GPS Receiver type
TReceiverData *getReceiverType (char *name, TReceiverList *recList);

// General modeling
int modelEpoch (TEpoch *epoch, TOptions *options);
int modelSatellite (TEpoch *epoch, TEpoch *epochDGNSS, int satIndex, TGNSSproducts *products, TGNSSproducts *klbProd, TGNSSproducts  *beiProd, TGNSSproducts *neqProd, TIONEX *Ionex, TFPPPIONEX *Fppp, TTROPOGal *TropoGal, TTGDdata *tgdData, TConstellation *constellation, TSBASdata *SBASdata, TOptions *options);

// SBAS processing
int computeSBAS (TEpoch *epoch, TGNSSproducts  *products, TGNSSproducts *klbProd, TGNSSproducts  *beiProd, TGNSSproducts *neqProd, TIONEX *Ionex, TFPPPIONEX *Fppp, int satIndex, enum MeasurementType meas, int measIndex, TSBASdata *SBASdata, TSBAScorr *SBAScorr, TOptions *options);
double SBASIonoModel (TEpoch *epoch, TGNSSproducts *products, int satIndex, int *errorvalue, TSBAScorr *SBAScorr, TSBASdata *SBASdata, TOptions *options);
int SwitchSBASGEOMode (TEpoch  *epoch, int  numsatellites, int  numsatdiscardedSBAS, TSBASdata *SBASdata, TOptions  *options);

// DGNSS processing
void prepareDGNSScorrections (TEpoch *epoch, TEpoch *epochDGNSS, TGNSSproducts *products, TOptions *options);
void computeDGNSScorrections (TEpoch *epoch, TEpoch *epochDGNSS, TGNSSproducts *products, TOptions *options);
void preFillUsableSatellites (TEpoch *epoch, TEpoch *epochDGNSS, TGNSSproducts *products, TOptions *options);

#endif /*MODEL_H_*/
