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
 * File: dataHandling.c
 * Code Management Tool File Version: 5.2  Revision: 0
 * Date: 2018/03/09
 ***************************************************************************/

/****************************************************************************
 * MODULE DESCRIPTION
 *
 * Name: dataHandling
 * Language: C
 *
 * Purpose:
 *  The purpose of this module is to centralize all the data structures of the 
 *  modules and allow an easy interface to them.
 *
 * Function:
 *  This class is in charge of declaring all the data structures used in all the
 *  modules. It defines all the required functions to access the information 
 *  inside the data structures, and a group of general functions.
 *
 * Dependencies:
 *  None
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
 * Change Log: First public version.
 * -------------
 *          gLAB v1.3.2
 * Release: 2010/02/23
 * Change Log: Corrected problem when processing with PCC (PC computed with C1).
 *             changeBase modified to be consistent with orientation matrix.
 *             Inertial/Non-inertial velocity switch included.
 *             minArcLength changed from 3 to 4.
 *             Included DCB data sources.
 *             Included SINEX, DCBs and GPS_Receiver_Type data files.
 *             Included strict radome option to enable/disable a relaxed matching
 *                  on ANTEX files.
 *             Corrected a bug when using PCC combination.
 *             When the receiver is of type 2 (no P1), the C1 will be provided instead
 *             Forward/Backward processing included.
 *             Corrected bug in t2doy function affecting the 31st of December and 
 *                  1st of January.
 * -------------
 *          gLAB v1.4.0
 * Release: 2010/06/21
 * Change Log: C1/P1 flexibility option is added to allow flexible handling of C1 and P1
 *             Included usable measurement index in TMeasOrder structure to select/deselect
 *                  individual measurements.
 *             Included prealignCP option to set/unset carrier-phase prealignment.
 *             Corrected a bug in t2doy function.
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
 * Change Log: Maximum number of filter iterations added.
 *             Increased robustness to non sequencialy transmitted ephemerides present
 *                  in RINEX Navigation Message files.
 * -------------
 *          gLAB v1.4.4
 * Release: 2010/09/22
 * Change Log: Included new DCB management.
 * -------------
 *          gLAB v1.4.5
 * Release: 2010/10/31
 * Change Log: Tropospheric correction option is extended to select independently the nominal and mapping used.
 *             Dilution Of Precision extension: (GDOP, PDOP, TDOP, VDOP, HDOP) new variables.
 *             Default precise orbit interpolation degree changed from 9 to 10.
 *             SIGMA_INF splitted into different SIGMA_INF_DR and SIGMA_INF_DT: receiver coordinates and clock.
 * -----------
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
 * Change Log: Added functions for initialising IONEX and F-PPP structures (both for ionosphere and DCB data).
 *             Added functions for handling IONEX and F-PPP structures (both for ionosphere and DCB data).
 *             Added function for computing the ionosphere mapping value.
 *             Added function for computing the pierce point value.
 *             Added functions for initialising ESA's troposphere model structures.
 *             Added functions for handling ESA's troposphere model structures.
 *             Modified some initialiase functions for handling RINEX 3.02 files.
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
 * Change Log: Added initialization values in initConstellationElement, initAntenna and initOptions functions for phase variation correction.
 * -----------
 *          gLAB v2.2.4
 * Release: 2015/07/01
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.2.5
 * Release: 2015/10/20
 * Change Log: No changes in this file
 * -----------
 *          gLAB v2.2.6
 * Release: 2015/11/25
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.2.7
 * Release: 2016/03/01
 * Change Log: Fixed "printError" function call, which failed to compile in some compilers
 * -----------
 *          gLAB v2.2.8
 * Release: 2016/04/12
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v3.0.0
 * Release: 2016/09/05 
 * Change Log: Added SBAS processing.
 *             Added user-defined error struct.
 *             Deleted satWas function.
 *             Added satIs function. It returns the index of the satellite in its dictionary.
 *             Added tsec function. It returns the MJDN + SoD in seconds.
 *             Modified structure definitions for handling Cycle Slip variables.
 *             Added QZSS and IRNSS constellations.
 * -----------
 *          gLAB v3.1.0
 * Release: 2016/09/26
 * Change Log: gpsws2ttime function now accepts negative seconds of week.
 *             Changed selectBRDCblock function to enable/disable the check of the transmission time of message.
 *             Fixed incorrect broadcast block selection when a block with a determined IODE was requested, and
 *                there was more than one block for the same satellite with the same IODE in the navigation file.
 *             Fixed rare problem when computing IONEX pierce point at high elevation.
 * -----------
 *          gLAB v3.1.1
 * Release: 2016/10/21
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v4.0.0
 * Release: 2017/03/03
 * Change Log: Added functions to initialise the RTCM structures.
 *             Added functions to initialise SBASplots structures.
 *             Added function date2doy.
 *             Added function doy2date.
 *             Added function SolutionModeNum2SolutionModeChar.
 *             Added ConcatenateSP3 function.
 *             Added comparison functions for qsort function.
 *             When searching a station in the SINEX file, it will only use the first four letters of the marker name
 *               in the RINEX observation file instead of the complete name.
 *             Fixed initialization of tropMapping variable (it was intialized to 'SimpleMominal' instead of 
 *               'SimpleMapping') in initOptions function (it didn't affect the code as both have the same integer value).
 *             Fixed incorrect memcpy call in t2tm function.
 * -----------
 *          gLAB v4.1.0
 * Release: 2017/04/07
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v4.2.0
 * Release: 2017/05/22
 * Change Log:   Added function 'mkdir_recursive' for creating directories recursively.
 *               Changed default SNR threshold from 35dbHz to 30dbHz.
 * -----------
 *          gLAB v5.0.0
 * Release: 2017/06/30
 * Change Log:   Fixed bug that made gLAB try to create an empty folder in Linux when the output path was absolute.
 * -----------
 *          gLAB v5.1.0
 * Release: 2017/11/24
 * Change Log:   Added functions 'ConvertCalendarDate', 'ConvertDoYDate', 'ConvertGPSWeekDate'
 *                 and 'ConvertMJDNDate' for date conversion.
 *               Added 'ConvertCartesianCoord', 'ConvertGeodeticCoord' and 'ConvertSphericalCoord'
 *                 for coordinate conversion.
 *               When 4 or more consecutive messages are wrong, UDREI data will timeout (for PA
 *                 mode only) instead of erasing all fast correction data.
 * -----------
 *          gLAB v5.1.1
 * Release: 2017/12/22
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v5.1.2
 * Release: 2018/01/12
 * Change Log:   Added initialization of 'numthreads' variable in 'initOptions' variable to the number of CPUs
 *                 in the machine.
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

/* External classes */
#include "dataHandling.h"
#include "input.h"
#include "output.h"
#include <string.h>
#if defined _OPENMP
 #include <omp.h>
#endif

extern int	ReadL1CAsItself;

/**************************************
 * Declarations of internal operations
 **************************************/

/*****************************************************************************
 * Name        : initOptions
 * Description : Initialises to the defaults a TOptions structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TOptions  *options              O  N/A  TOptions structure
 *****************************************************************************/
void initOptions (TOptions *options) {
	int	i,j,k;
	
	options->fdkml=NULL;
	options->fdkml0=NULL;
	options->KMLTimeStamps = 0;
	options->KMLTimeStampDec = 30.;
	options->numKMLTimeRanges = 0;
	options->referenceStations = 1;
	options->KMLtimeranges=NULL;
	options->fdstdESALOI=NULL;
	options->SP3Letter='L';
	options->SP3PRN=9;
	options->YearSoDRefFile=1;
	options->GPSWeekRefFile=0;
	options->CalendarTimeRefFile=0;
	options->GeodeticCoordRefFile=0;
	options->WriteSPPsolInDGNSSmodeSP3=0;
	options->WriteSPPsolInDGNSSmodeRefFile=0;
	strcpy(options->model_dir,"model_files");
	strcpy(options->tropoGaldir,"TropoGal");
	strcpy(options->NeQuickdir,"NeQuick");

	// Verbose options
	options->printModel = -1;
	options->printPrefit = -1;
	options->printPostfit = -1;
	options->printFilterSolution = -1;
	options->printInfo = 1;
	options->printCycleslips = 1;
	options->printSatellites = -1;
	options->printInput = -1;
	options->printMeas = -1;
	options->printOutput = 1;
	options->printSatSel = -1;
	options->printSatDiff = 1;
	options->printSatStat = 1;
	options->printSatStatTot = 1;
	options->printSatPvt = 1;

	options->printSBASOUT    = 1;
	options->printSBASCORR   = 0;
	options->printSBASVAR    = 0;
	options->printSBASIONO   = 0;
	options->printSBASUNSEL  = 0;
	options->printSBASUNUSED = 0;
	options->printInBuffer   = 0;
	options->printUserError  = 1;

	options->printDGNSS = 1;
	options->printDGNSSUNUSED = 0;

	options->printSummary = 1;

	options->ProgressEndCharac='\r';

	options->satVel = svITRF;

	// Processing and modeling options
	options->workMode = wmDOPROCESSING;
	options->receiverPositionSource = rpUNKNOWN;
	options->aprioriReceiverPositionGeod[0]=0;
	options->aprioriReceiverPositionGeod[1]=0;
	options->aprioriReceiverPositionGeod[2]=-999999; //This is an invalid value to know that user has set no input for this value
	options->strictradome = 0;
	options->antennaData = adNONE;
	options->ARPData = arpUNKNOWN;
	for (j=0;j<3;j++) {
		options->receiverARP[j] = 0;
		for (i=0;i<MAX_FREQUENCIES_PER_GNSS;i++) {
			options->receiverPCO[i][j] = 0;
		}
	}
	options->deprecatedMode = 0;
	options->prealignCP = 1;
	options->flexibleC1P1 = 1;
	options->csDataGap = -1;
	options->csLLI = 1;
	options->csNcon = -1;
	options->csNconMin = -2;
	options->csNconAutoDisabled = 0;
	options->csLI = 1;
	options->csLImaxjump = 1;
	options->csLImax = 0.08;
	options->csLIt = 60;
	options->csLIsamples = 7;
	options->csBW = 1;
	options->csBWInitStd = 2.;
	options->csBWmin = 0.8;
	options->csBWwindow = 300;
	options->csBWkfactor = 5;
	options->csBWsamples = 2;
	options->csL1C1 = 0;
	options->csUnconsistencyCheck = 1;
	options->csUnconsistencyCheckThreshold = 20.;
	options->csL1C1kfactor = 5.0;
	options->csL1C1window = 300;
	options->csL1C1init = 3.0;
	options->csL1C1samples = 2;
	options->timeTrans = 1;
	options->earthRotation = 1;
	options->satellitePhaseCenter = 1;
	options->satellitePhaseVar = 0;
	options->receiverPhaseVar = 0;
	options->relativisticCorrection = 1;
	options->windUpCorrection = 1;
	options->gravitationalCorrection = 1;
	options->solidTidesCorrection = 1;
	options->satelliteClockCorrection = 1;
	options->ionoModel = NoIono;
	options->ionoRMS = 100000;  //High value because it is not used. A normal value is 1
	options->troposphericCorrection = 1;
	options->useSigmaIono = 1;
	options->tropNominal = UNB3Nominal;
	options->tropMapping = SimpleMapping;
	options->p1c1dcbModel = p1c1FLEXIBLE;
// Found: options->p1p2dcbModel = p1c1NONE;
	options->p1p2dcbModel = p1p2NONE;
	options->SBAScorrections = 0;
	options->onlySBASiono = 0;
	options->decimate = -1.;
	options->orbitInterpolationDegree = 10;
	options->clockInterpolationDegree = 0;
	options->satelliteHealth = 1;
	options->brdcBlockTransTime = -1;
	options->MaxURABroadcast=9999999.;
	options->discardEclipsedSatellites = 0;
	options->maxKalmanIterations = 20;

	// Filtering options
	for (i=0;i<MAX_FILTER_MEASUREMENTS;i++) {
		//options->fixedMeasurementWeight[i] = 1;
		//options->elevationMeasurementWeight[i][0] = 0;
		//options->elevationMeasurementWeight[i][1] = 10 * d2r;
	}
	options->totalFilterMeasurements = 2;
	options->measurement[0] = PC;
	options->measurement[1] = LC;
	options->smoothMeas[0] = NA;
	options->smoothMeas[1] = NA;
	options->smoothEpochs = -1;
	options->maxdr2 = 10000;
	options->estimateTroposphere = 1;
	options->usePhase = 1;
	options->filterParams[PHI_PAR][DR_UNK] = 1;
	options->filterParams[PHI_PAR][DT_UNK] = 0;
	options->filterParams[PHI_PAR][TROP_UNK] = 1;
	options->filterParams[PHI_PAR][BIAS_UNK] = 1;
	options->filterParams[Q_PAR][DR_UNK] = 0;
	options->filterParams[Q_PAR][DT_UNK] = SIGMA_INF_DT*SIGMA_INF_DT;
	options->filterParams[Q_PAR][TROP_UNK] = 1e-4;
	options->filterParams[Q_PAR][BIAS_UNK] = 0;
	options->filterParams[P0_PAR][DR_UNK] = SIGMA_INF_DR*SIGMA_INF_DR;
	options->filterParams[P0_PAR][DT_UNK] = SIGMA_INF_DT*SIGMA_INF_DT;
	options->filterParams[P0_PAR][TROP_UNK] = 0.5 * 0.5;
	options->filterParams[P0_PAR][BIAS_UNK] = 20 * 20;
	options->elevationMask = 5. * d2r;
	options->filterIterations = 1;
	options->NextSP3 = 0;
	options->concatenSP3 = 0;
	options->LastSamplePrevDayOrb=0;
	options->LastSamplePrevDayClk=0;
	options->numPreciseFiles = 0;
	options->OrbitsMaxGaps=-1;
	options->ClocksMaxGaps=-1;
	options->OrbitsToTMaxGaps=-1;
	options->ClocksToTMaxGaps=-1;
	options->OrbitsMaxDistance=-1.;
	options->ClocksMaxDistance=-1.;
	options->OrbitsToTMaxDistance=-1.;
	options->ClocksToTMaxDistance=-1.;
	options->checkPhaseCodeJumps = 1;
	
	
	for (i=0;i<MAX_GNSS;i++) {
		for (j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
			options->includeSatellite[i][j] = 1;
			options->SNRvalues[i][j] = 33.;
			for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
				options->SNRweightComb[i][j][k]=SNRWeightCombMean;
				options->SNRweightCombVal[i][j][k][0]=0.5;
				options->SNRweightCombVal[i][j][k][1]=0.5;
				options->WeightConstantsValues[i][j][k][0]=1.;
				options->WeightConstantsValues[i][j][k][1]=0.;
				options->WeightConstantsValues[i][j][k][2]=0.;
				options->weightMode[i][j][k]=FixedWeight;
			}
		}
		for (j=0;j<MAX_FREQUENCIES_PER_GNSS;j++) {
			options->usableFreq[i][j] = 1;
		}
	}

	options->SNRfilter = -1;
	options->useraddednoise = 0;
	options->useraddednoisepreprocess = 0;

	options->writeRinexBfile = 0;
	options->writeEMSfile = 0;
	options->writePegasusfile = 0;
	options->onlyconvertSBAS = 0;
	options->onlySBASplots = 0;
	options->pegasuspurerinex = 0;
	options->pegasusaligned = 0;
	options->pegasusfs = ';';
	strcpy(options->sbasdir,SBASOUTPUTPATH);


	options->usetype0messages = 1;
	options->alarmmessageastype2 = 0;
	options->precisionapproach = PAMODE;
	options->UserForcedNPA = 0;
	options->excludeSmoothingConvergence = -1;
	options->switchmode = -1;
	options->GEOfallback = 0;
	options->MaintainGEO = 1;
	options->adquisitiontime=GEOACQUISIONTIME;
	options->minimumswitchtime=MINIMUMSWITCHTIME;
	options->GEOindex = -1;
	options->GEOPRN = -1;
	options->switchGEO = -1;
	options->mixedGEOdata = -1;
	options->initcoordNPA = 1;
	options->UDREIthreshold = 999999;
	options->SigmaOffsetNoMT10 = 8.;
	options->airborneReceiverType = 2;
	options->stepdetector = -1;
	options->SBASmaritime=0;
	options->prefitOutlierDetectorAbs = 0;
	options->prefitOutlierDetectorAbsThreshold= 30.;
	options->prefitOutlierDetectorMedian = 0;
	options->prefitOutlierDetectorMedianThreshold = 30.;
	options->FCtmout[0] = options->FCtmout[1] = -1;
	options->RRCtmout[0] = options->RRCtmout[1] = -1;
	options->usersigmamultipath = 0;
	options->sigma2multipath[0] = options->sigma2multipath[1] = -99999.;
	options->sigma2noise = -1;
	options->sigma2divergence = -1;
	options->stanfordesa = 0;
	options->stanfordesaLOI = 1;
	options->WIRHorThreshold = 0.7;
	options->WIRVerThreshold = 0.7;
	options->waitForNextDay = 1;
	options->useDatasummary = 1;
	options->SBASHourlyMaps = 0;
	options->NoAvailabilityPlot = 0;
	options->NoContRiskPlot = 0;
	options->NoIonoPlot = 0;
	options->minLatplots = 25.0;
	options->maxLatplots = 70.0;
	options->minLonplots = -30.0;
	options->maxLonplots = 40.0;
	options->AvailabilityPlotStep = 1.0;
	options->IonoPlotStep = 0.3;
	options->IonoPlotTimeStep = 300;
	options->ContRiskWindowSize = 15;
 	options->VerAlarmLimit = 50.0;
 	options->HorAlarmLimit = 40.0;
	options->percentile=95;
	options->SBASPlotsRecHeight = 0;
	options->NumSBASPlotsExclusionArea=0;
	options->SBASPlotsExclusionAreaDelimeters=NULL;
	options->NumSBASPlotsInclusionArea=0;
	options->SBASPlotsInclusionAreaDelimeters=NULL;
	options->NoFastCorrection = 0;
	options->NoRRCCorrection = 0;
	options->NoSlowCorrection = 0;
	options->NoIonoCorrection= 0;
	options->NoDeltaUDRE = 0;
	options->NoFastSigma = 0;
	options->NoFastDeg = 0;
	options->NoRRCSigma = 0;
	options->NoSlowSigma = 0;
	options->NoIonoSigma = 0;
	options->NoTropoSigma = 0;
	options->NoEnRouteSigma = 0;
	options->NoMT10=0;
	// DGNSS
	options->DGNSS = 0;
	options->dgnssMaxEph = 4.0 * 3600.0; // seconds
	options->dgnssSigma2noiseGPS = 0.25;
	options->dgnssSigma2multipath = 0.0625;
	options->epsURA3o = 0.01;
	options->sigmaInflation = 1;
	options->maxAgeDGNSS = 31.0; // seconds
	options->maxDGNSSPRC = 500.; // meters
	options->excludeSmoothingConvergenceUser = 0;
	options->excludeSmoothingConvergenceRef = 1;
	options->rtcmYear = 0;
	options->rtcmYearShort = 0;
	options->rtcmMonth = 0;
	options->rtcmDay = 0;
	options->rtcmHour = -1;
	options->RTCMmode = RTCMUNKNOWN;
	options->rinexVersion = 3;
	options->GDOPthreshold = -1;
	options->maxGDOP = 30.0; // meters
	options->excludeSmoothingConvergenceTime = 360; // sec
	options->DF = 0;

	for (i=0;i<MAX_SBAS_PRN;i++) {
		options->GEOPRNunsel[i] = 0;
	}

	options->solutionMode = SPPMode;

	options->OutputToTerminal=0;
	options->outFileStream=stdout;
	options->terminalStream=stdout;

	options->StartEpoch.MJDN=-1;
	options->StartEpoch.SoD=0.;
	options->EndEpoch.MJDN=-1;
	options->EndEpoch.SoD=0.;
	options->firstEpochSummary.MJDN=-1;
	options->firstEpochSummary.SoD=0.;
	options->recPosProvided=0;
	

	options->RefDegInterp=0;

	#if defined _OPENMP
		options->numthreads=omp_get_num_procs();
	#endif

}

/*****************************************************************************
 * Name        : initSatellite
 * Description : Initialise a TSatellite struct. It is only called after a cycle-slip is found
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  IO N/A  TEpoch struct
 * int  satIndex                   I  N/A  Pointing to the sat[satIndex]
 *                                         TSatellite structure that should be 
 *                                         initialised
 * int  satCSindex                 I  N/A  Pointing to the sat[satCSIndex] 
 *                                         TCS structure that should be initialised
 *****************************************************************************/
void initSatellite (TEpoch *epoch, int satIndex, int satCSindex) {
	int	i;

	epoch->cycleslip.arcLength[satCSindex] = 1;
	epoch->cycleslip.outlierLI[satCSindex] = 0;
	epoch->cycleslip.outlierBw[satCSindex] = 0;
	epoch->cycleslip.CS[satCSindex] = 1;
	epoch->cycleslip.CSPrealignFlag[satCSindex] = 1;
	epoch->cycleslip.narc[satCSindex]++;
	epoch->cycleslip.hasBeenCycleslip[satCSindex] = 1;
	epoch->cycleslip.windUpRadAccumReceiver[satCSindex] = 0.0;
	epoch->cycleslip.windUpRadAccumSatellite[satCSindex] = 0.0;
	epoch->sat[satIndex].ionoSigma = 0;
	epoch->sat[satIndex].hasSBAScor = 1;
	epoch->sat[satIndex].hasSNR = 1;
	
	for (i=0;i<MAX_FILTER_MEASUREMENTS;i++) {
		epoch->cycleslip.smoothedMeas[satCSindex][i] = 0.0;
	}

	for (i=0;i<epoch->measOrder[epoch->sat[satIndex].GNSS].nDiffMeasurements;i++) {
		epoch->cycleslip.preAlign[satCSindex][i] = 0.0;
	}

	for (i=0;i<MAX_SLIDING_WINDOW;i++) {
		epoch->cycleslip.windowMW[satCSindex][i] = 0.0;
		epoch->cycleslip.windowMWtime[satCSindex][i] = 0.0;
		epoch->cycleslip.windowL1C1[satCSindex][i] = 0.0;
		epoch->cycleslip.windowL1C1time[satCSindex][i] = 0.0;
	}
}

/*****************************************************************************
 * Name        : initEpoch
 * Description : Initialise a TEpoch struct
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  O  N/A  TEpoch struct
 * TOptions  *options              O  N/A  TOptions structure
 *****************************************************************************/
void initEpoch (TEpoch *epoch, TOptions  *options) {
	int i,j;

	epoch->firstepoch.SoD=-1.;
	epoch->secondepoch.SoD=-1.;
	epoch->PreviousEpoch.MJDN = -1;
	epoch->PreviousEpoch.SoD = -1;
	epoch->t.MJDN=-1;
	epoch->t.SoD=-1.;
	epoch->numEpochsfile=1.;
	epoch->numEpochsprocessed=-1.;
	epoch->PreviousPercentage=0;
	epoch->CurrentPercentage=0.;
	epoch->NewPercentage=0;

	epoch->numSatellites = 0;
	epoch->numAproxPosRead = 0;
	epoch->lastSBASindex = 0;
	epoch->prevNumSatellites = 0;
	epoch->numGNSS = 0;
	epoch->receiver.recType = rtUNKNOWN;
	epoch->receiver.interval = -1;
	epoch->receiver.intervalEstimate= -1;
	epoch->receiver.intervalDecimalsFactor = 1;
	epoch->receiver.DecimateVal=99999;
	epoch->receiver.name[0] = '\0';
	epoch->receiver.type[0] = '\0';
	epoch->receiver.aproxPosition[0] = EARTH_RADIUS;
	epoch->receiver.aproxPosition[1] = 0;
	epoch->receiver.aproxPosition[2] = 0;
	epoch->receiver.aproxPositionError = 1e10;
	epoch->receiver.equivalentC1P1 = 0;
	epoch->receiver.receiverSolConverged = 1;
	epoch->receiver.aproxPositionRover[0] = 0.;
	epoch->receiver.aproxPositionRover[1] = 0.;
	epoch->receiver.aproxPositionRover[2] = 0.;

	epoch->prealign = 0;
	epoch->ZTD = 0;
	epoch->IPPlat = 0;
	epoch->IPPlon = 0;

	epoch->dgnss.Nref = 0;
	epoch->dgnss.CLKref = 0.0;
	epoch->dgnss.epsURA = 0.01;
	
	for (i=0;i<3;i++) {
		epoch->solidTideDisplacement[i] = 0;
		epoch->receiver.ARP[i] = 0;
		for (j=0;j<MAX_FREQUENCIES_PER_GNSS;j++) {
			epoch->receiver.antenna.PCO[j][i] = 0;
		}
	}

	for (i=0;i<MAX_SATELLITES_VIEWED;i++) {
		epoch->satsviewed[i] = 0;
		epoch->sat[i].azimuth = 0.0;
		epoch->sat[i].elevation = 0.0;
		epoch->cycleslip.hasBeenCycleslip[i] = 0;
		epoch->cycleslip.use4smooth[i] = 1;
		epoch->cycleslip.preCheck[i] = 0;
		epoch->cycleslip.outlierLI[i] = 0;
		epoch->cycleslip.outlierBw[i] = 0;
		epoch->cycleslip.consistency[i] = 0;
		epoch->cycleslip.CS[i] = 0;
		epoch->cycleslip.CSPrealignFlag[i] = 0;
		epoch->cycleslip.narc[i] = 0;
		epoch->cycleslip.arcLength[i] = 0;
		epoch->cycleslip.Nconsecutive[i] = 0;
		epoch->cycleslip.initialLi[i] = 0.0;
		epoch->cycleslip.BWmean[i] = 0.0;
		epoch->cycleslip.BWmean300[i] = 0.0;
		epoch->cycleslip.BWsigma[i] = options->csBWInitStd*options->csBWInitStd;
		epoch->cycleslip.L1C1mean[i] = 0.0;
		epoch->cycleslip.L1C1sigma[i] = 0.0;
		epoch->cycleslip.L1Prev[i] = 0.0;
		epoch->cycleslip.C1Prev[i] = 0.0;
		epoch->sat[i].ionoSigma = 0.0;
		for (j=0;j<MAX_MEASUREMENTS_PER_SATELLITE;j++) {
			epoch->cycleslip.preAlign[i][j] = 0.0;
		}
		for (j=0;j<MAX_FILTER_MEASUREMENTS;j++) {
			epoch->cycleslip.smoothedMeas[i][j] = 0.0;
		}
		for (j=0;j<MAX_SLIDING_WINDOW;j++) {
			epoch->cycleslip.windowMW[i][j] = 0.0;
			epoch->cycleslip.windowMWtime[i][j] = 0.0;
			epoch->cycleslip.windowL1C1[i][j] = 0.0;
			epoch->cycleslip.windowL1C1time[i][j] = 0.0;
		}
		// DGNSS
		epoch->dgnss.msg[i] = 0;
		epoch->dgnss.health[i] = 0;
		epoch->dgnss.IODmsg1[i] = 0;
		epoch->dgnss.IODmsg2[i] = 0;
		epoch->dgnss.PRC[i] = 0.0;
		epoch->dgnss.PRCp[i] = 0.0;
		epoch->dgnss.sigmaInflation[i] = 1.0;
		epoch->dgnss.sigmaURA3[i] = 0.0;
		epoch->dgnss.sigmaURA3p[i] = 0.0;
		epoch->dgnss.C1[i] = 0.0;
		epoch->dgnss.C1s[i] = 0.0;
		epoch->dgnss.UDRE[i] = 0.0;
		epoch->dgnss.tPRC[i].SoD = 0.0;
		epoch->dgnss.tPRC[i].MJDN = 0.0;
		epoch->dgnss.tdeltaPRC[i].SoD = 0.0;
		epoch->dgnss.tdeltaPRC[i].MJDN = 0.0;
		epoch->DGNSSstruct=0;
	}

	for (j=0;j<MAX_GNSS;j++) {
		for (i=0;i<MAX_MEASUREMENTS;i++) {
			epoch->measOrder[j].meas2Ind[i] = -1;
			epoch->measOrder[j].conversionFactor[i] = 0;
			epoch->measOrder[j].usable[i] = 1;
		}
		for (i=0;i<MAX_SATELLITES_PER_GNSS;i++) {
			epoch->satInfo[j][i].lastEclipse.SoD = 0;
			epoch->satInfo[j][i].lastEclipse.MJDN = 0;
		}
		epoch->measOrder[j].hasSNRmeas=0;
		for(i=0;i<MAX_FREQUENCIES_PER_GNSS;i++) {
			epoch->measOrder[j].SNRmeaspos[i]=-1;
		}
	}

	epoch->ResetNumSwitch=0;

	epoch->KMLData=NULL;
	epoch->KMLTime=NULL;
	epoch->numKMLData=0;
	epoch->receiver.numRecStation=0;
	epoch->receiver.RecStationCoord=NULL;
	epoch->receiver.ChangedStaEpoch=NULL;
	epoch->receiver.look4interval = 1;
	epoch->receiver.RefPositionAvail=1;

	//Summary variables
	epoch->TotalEpochs=0;
	epoch->TotalEpochsSol=0;
	epoch->TotalEpochsDGNSS=0;
	epoch->TotalEpochsSPP=0;
	epoch->TotalEpochsRef=0;
	epoch->NumNoRefSumSkipped=0;
	epoch->NumNoRefSolSkipped=0;
	epoch->NumGDOPSkipped = 0;
	epoch->NumSingularMatrixSkipped = 0;
	epoch->NumNoSatSkipped = 0;
	epoch->HPEPercentileValues = -1.;
	epoch->VPEPercentileValues = -1.;
	epoch->HPEPercentileSamples = -1.;
	epoch->VPEPercentileSamples = -1.;
	epoch->MaxHError = -1.;
	epoch->MaxVError = -1.;
	epoch->HError = NULL;
	epoch->VError = NULL;
	epoch->StartSummaryEpoch.MJDN=-1;
	epoch->StartSummaryEpoch.SoD=0.;
	epoch->LastSummaryEpoch.MJDN=-1;
	epoch->LastSummaryEpoch.SoD=0.;
	epoch->StartSummaryPercentileEpoch.MJDN=-1;
	epoch->StartSummaryPercentileEpoch.SoD=0.;
	epoch->LastSummaryPercentileEpoch.MJDN=-1;
	epoch->LastSummaryPercentileEpoch.SoD=0.;
}

/*****************************************************************************
 * Name        : initGNSSproducts
 * Description : Initialise a TGNSSproducts struct
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TGNSSproducts*  products        O  N/A  TGNSSproducts struct
 *****************************************************************************/
void initGNSSproducts (TGNSSproducts *products) {
	products->BRDC = NULL;
	products->SP3 = NULL;
}

/*****************************************************************************
 * Name        : initBRDCproducts
 * Description : Initialise a TBRDCproducts struct
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TBRDCproducts  *BRDC            O  N/A  TBRDCproducts struct
 *****************************************************************************/
void initBRDCproducts (TBRDCproducts *BRDC) {
	int i,j;

	BRDC->numsats = 0;
	BRDC->numsatsPast = 0;
	BRDC->block = NULL;
	BRDC->blockPast = NULL;
	BRDC->numblocks = NULL;
	BRDC->numblocksPast = NULL;

	for (i=0;i<4;i++) {
		BRDC->ionA[i] = 0;	//Rinex v2
		BRDC->ionB[i] = 0;	//Rinex v2
		BRDC->ai[i] = 0;	//Rinex v3
		BRDC->bdsA[i] = 0;	//Rinex v3
		BRDC->bdsB[i] = 0;	//Rinex v3
	}

	for (i=0;i<MAX_GNSS;i++) {
		for (j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
			BRDC->index[i][j] = -1;
			BRDC->indexPast[i][j] = -1;
		}
	}

	BRDC->LeapSecondsAvail=0;
	BRDC->AT_LS  = 0;
	BRDC->AT_LSF = 0;
	BRDC->WN_LSF = 0;
	BRDC->DN     = 0;

	//Rinex v3
	for(i=0;i<6;i++) {
		BRDC->timeSysCorr[i].acoff[0] = 0;
		BRDC->timeSysCorr[i].acoff[1] = 0;
		BRDC->timeSysCorr[i].timeref = 0;
		BRDC->timeSysCorr[i].weekref = 0;
	} 
}

/*****************************************************************************
 * Name        : initBRDCblock
 * Description : Initialise a TBRDCblock struct
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TBRDCblock  *BRDCblock          O  N/A  TBRDCblock struct
 *****************************************************************************/
void initBRDCblock (TBRDCblock *BRDCblock) {
	BRDCblock->PRN = 0;
	BRDCblock->clockbias = 0;
	BRDCblock->clockdrift = 0;
	BRDCblock->clockdriftrate = 0;
	BRDCblock->IODE = 0;
	BRDCblock->IODNav = 0;
	BRDCblock->crs = 0;
	BRDCblock->deltan = 0;
	BRDCblock->M0 = 0;
	BRDCblock->cuc = 0;
	BRDCblock->e = 0;
	BRDCblock->cus = 0;
	BRDCblock->sqrta = 0;
	BRDCblock->toe = 0;
	BRDCblock->cic = 0;
	BRDCblock->OMEGA = 0;
	BRDCblock->cis = 0;
	BRDCblock->i0 = 0;
	BRDCblock->crc = 0;
	BRDCblock->omega = 0;
	BRDCblock->OMEGADOT = 0;
	BRDCblock->IDOT = 0;
	BRDCblock->codesOnL2 = 0;
	BRDCblock->GPSweek = 0;
	BRDCblock->L2Pdataflag = 0;
	BRDCblock->dataSources = 0;
	BRDCblock->GALweek = 0;
	BRDCblock->BDSweek = 0;
	BRDCblock->SVaccuracy = 0;
	BRDCblock->SVhealth = 0;
	BRDCblock->TGD = 0;
	BRDCblock->TGD2 = 0;
	BRDCblock->IODC = 0;
	BRDCblock->SISASignal = 0;
	BRDCblock->BGDE5a = 0;
	BRDCblock->BGDE5b = 0;
	BRDCblock->transTime = 0;
	BRDCblock->fitInterval = 0;
	BRDCblock->transTimeGAL = 0;
	BRDCblock->satposX = 0;
	BRDCblock->satvelX = 0;
	BRDCblock->sataccX = 0;
	BRDCblock->satposY = 0;
	BRDCblock->satvelY = 0;
	BRDCblock->sataccY = 0;
	BRDCblock->freqnumber = 0;
	BRDCblock->satposZ = 0;
	BRDCblock->satvelZ = 0;
	BRDCblock->ageofoperation = 0;
	BRDCblock->IODNGEO = 0;
	BRDCblock->URAGEO = 0;
}

/*****************************************************************************
 * Name        : initSP3products
 * Description : Initialise a TSP3products struct
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TSP3products  *SP3              O  N/A  TSP3products struct
 *****************************************************************************/
void initSP3products (TSP3products *SP3) {
	int i,j;

	SP3->orbits.numSatellites = 0;
	SP3->orbits.numSatellitesRead = 0;
	SP3->orbits.block = NULL;
	SP3->orbits.accuracy = NULL;
	SP3->orbits.numRecords = 0;
	SP3->orbits.interval = 0;
	SP3->orbits.velocityAvailable = 0;
	SP3->orbits.startTime.MJDN = 0;
	SP3->orbits.startTime.SoD = 0.;

	SP3->clocks.numSatellites = 0;
	SP3->clocks.numSatellitesRead = 0;
	SP3->clocks.block = NULL;
	SP3->clocks.numRecords = 0;
	SP3->clocks.vsizeblock = 0;
	SP3->clocks.interval = 0;
	SP3->clocks.startTime.MJDN = 0;
	SP3->clocks.startTime.SoD = 0.;

	for (i=0;i<MAX_GNSS;i++) {
		for (j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
			SP3->clocks.index[i][j] = -1;
			SP3->orbits.index[i][j] = -1;
			SP3->orbits.numblocsConcat[i][j]=0;
			SP3->clocks.numblocsConcat[i][j]=0;
		}
	}

	for(i=0;i<MAX_GNSS*MAX_SATELLITES_PER_GNSS;i++) {
		SP3->orbits.Concatblock[i] = NULL;
		SP3->clocks.Concatblock[i] = NULL;
	}
}

/*****************************************************************************
 * Name        : initSP3orbitblock
 * Description : Initialise a TSP3orbitblock struct
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TSP3orbitblock  *SP3            O  N/A  TSP3orbitblock struct
 *****************************************************************************/
void initSP3orbitblock (TSP3orbitblock *SP3orbitblock) {
	SP3orbitblock->v[0] = 0;
	SP3orbitblock->v[1] = 0;
	SP3orbitblock->v[2] = 0;
	SP3orbitblock->x[0] = 0;
	SP3orbitblock->x[1] = 0;
	SP3orbitblock->x[2] = 0;
	SP3orbitblock->orbitflags[0] = '\0';
}

/*****************************************************************************
 * Name        : initSP3clockblock
 * Description : Initialise a TSP3clockblock struct
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TSP3clockblock  *SP3            O  N/A  TSP3clockblock struct
 *****************************************************************************/
void initSP3clockblock (TSP3clockblock *SP3clockblock) {
	SP3clockblock->clock = INVALID_CLOCK;
	SP3clockblock->clockrate = 0;
	SP3clockblock->clockdriftrate = 0;
	SP3clockblock->clockflags[0] = '\0';
}

/*****************************************************************************
 * Name        : initIONEXDCB
 * Description : Initialise a TIonexDCB structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TIonexDCB  *IonexDCB            O  N/A  TIonexDCB struct
 *****************************************************************************/
void initIONEXDCB (TIonexDCB *IonexDCB){

	int i,j;

	IonexDCB->DCBavailable = 0;

	
	for (i=0;i<MAX_GNSS;i++) {
		for (j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
			IonexDCB->DCB[i][j] = -999999.;
			IonexDCB->DCBRMS[i][j] = 1e6;
		}
	}
}

/*****************************************************************************
 * Name        : initIONEX
 * Description : Initialise a TIONEX structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TIONEX  *IONEX                  O  N/A  TIONEX struct
 *****************************************************************************/
void initIONEX (TIONEX *IONEX) {

	IONEX->map = NULL;
	IONEX->numMaps = 0;
	IONEX->RMSavailable = 0;	//RMS values are not mandatory
	IONEX->HGTavailable = 0;	//HGT values are not mandatory
	IONEX->conversionFactor = 0.1; // Default conversion factor
	IONEX->exponent = -1;
	IONEX->satNumber = 0 ;
	IONEX->stationNumber = 0 ;
	IONEX->mapDimension = 2 ; // typically 2D dimension maps
	IONEX->numStationData = 0;
	IONEX->baseRadius = EARTH_RADIUS;
	IONEX->ionexStation = NULL;
	strcpy(IONEX->mappingFunction,"COSZ");

	initIONEXDCB(&IONEX->ionexDCB);
}

/*****************************************************************************
 * Name        : initIonoMap
 * Description : Initialise a TIonoMap structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TIonoMap  *ionoMap              O  N/A  TIonoMap struct
 *****************************************************************************/
void initIonoMap (TIonoMap *ionoMap) {
	ionoMap->dhgt = -1;
	ionoMap->dlat = -1;
	ionoMap->dlon = -1;

	ionoMap->RMS = NULL;
	ionoMap->TEC = NULL;
	ionoMap->HGT = NULL;
}

/*****************************************************************************
 * Name        : initIonexStation
 * Description : Initialise a TIonexStation structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TIonexStation  *ionexStation    O  N/A  TIonexStation struct
 *****************************************************************************/
void initIonexStation (TIonexStation *ionexStation) {
	ionexStation->stationInitials[0] = '\0';
	ionexStation->stationcode[0] = '\0';
	ionexStation->stationBias = 0;
	ionexStation->stationRMS = 0;
}

/*****************************************************************************
 * Name        : initFPPPDCB
 * Description : Initialise a TFPPPDCB structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TFPPPDCB  *FPPPDCB              O  N/A  TFPPPDCB struct
 *****************************************************************************/
void initFPPPDCB (TFPPPDCB *FPPPDCB) {

	int i,j;	

	FPPPDCB->DCBavailable = 0;

	for (i=0;i<MAX_GNSS;i++) {
		for (j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
			FPPPDCB->frac1[i][j] = 0;
			FPPPDCB->fracw[i][j] = 0;
			FPPPDCB->IFB[i][j] = -999999.;
		}
	}
}

/*****************************************************************************
 * Name        : initFPPPIONEX
 * Description : Initialise a TFPPPIONEX structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TFPPP  *FPPP                    O  N/A  TFPPPIONEX struct
 *****************************************************************************/
void initFPPPIONEX (TFPPPIONEX *FPPP) {

	FPPP->numMaps = 0;
	FPPP->baseRadius = EARTH_RADIUS/1000; // In Km
	strcpy(FPPP->mappingFunction,"COSZ");

	initFPPPDCB(&FPPP->fpppDCB);

}

/*****************************************************************************
 * Name        : initFPPPMap
 * Description : Initialise a TFPPPMap structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TFPPPMap  *FPPPMap              O  N/A  TFPPPMap struct
 *****************************************************************************/
void initFPPPMap (TFPPPMap *FPPPMap) {
	FPPPMap->dhgt = 0;
	FPPPMap->dlat = -1;
	FPPPMap->dlt = -1;
	
	FPPPMap->lat1 = -90;
	FPPPMap->lat2 = 90;
	
	FPPPMap->lt1 = 0;
	FPPPMap->lt2 = 360;

	FPPPMap->TEC = NULL;
	FPPPMap->SIGMA = NULL;
}


/*****************************************************************************
 * Name        : initFPPPMapData
 * Description : Fill with 9999 the TEC data vector of a TFPPPMap structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TFPPPMap  *FPPPMap              O  N/A  TFPPPMap struct
 *****************************************************************************/
void initFPPPMapData (TFPPPMap *FPPPMap){
	int nh,nlat,nlt;
	int mapType=0;
	double hgt,lt,lat;
	for(nh=0; nh<NUMBERFPPPMAPS;nh++)
	{
		hgt = FPPPMap->hgt1 + nh*FPPPMap->dhgt;
		
		for(nlat=0; nlat<FPPPMap->nlat;nlat++)
		{
			lat = FPPPMap->lat1 + nlat*FPPPMap->dlat;
			
			for(nlt=0; nlt<FPPPMap->nlt;nlt++)
			{
				lt = FPPPMap->lt1 + nlt*FPPPMap->dlt;
				setFPPPValue(FPPPMap, mapType, hgt, lat, lt, 9999);
				setFPPPValue(FPPPMap, 1-mapType, hgt, lat, lt, 9999);
			}
		}
	}
}


/*****************************************************************************
 * Name        : initiPiercePoint
 * Description : Initialise a TPiercePoint structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TIonexStation  *ionexStation    O  N/A  TPiercePoint struct
 *****************************************************************************/
void initPiercePoint (TPiercePoint *PiercePoint){
	PiercePoint->x = 0;
	PiercePoint->y = 0;
	PiercePoint->z = 0;
	PiercePoint->fi = 0;
	PiercePoint->longitude = 0;
	PiercePoint->elevation = 0;
	PiercePoint->localtime = 0;
	PiercePoint->mappingFunction = 0;
	
}

/*****************************************************************************
 * Name        : initTropoGalData
 * Description : Initialise a TTROPOGal structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTROPOGal *TropoGal             O  N/A  TTROPOGal struct
 *****************************************************************************/
void initTropoGalData (TTROPOGal *TropoGal) {

	int i;

	TropoGal->lat_pix_positions = 121; 	//Default Gal value
	TropoGal->lon_pix_positions = 241;	//Default Gal value 
	TropoGal->delta_lat_pix = -1.5;		//Default Gal value
	TropoGal->delta_lon_pix = 1.5;		//Default Gal value 
	TropoGal->lat_pix_init = 90;		//Map from 90 to -90 degrees
	TropoGal->lat_pix_end = -90;		//Map from 90 to -90 degrees
	TropoGal->lon_pix_init = 0;		//Map from 0 to 360 degrees
	TropoGal->lon_pix_end = 360;		//Map from 0 to 360 degrees

	for(i=0;i<3;i++) {
		TropoGal->am_a_size[i] = 0;	
		TropoGal->es_a_size[i] = 0;	
		TropoGal->ld_a_size[i] = 0;	
		TropoGal->ps_a_size[i] = 0;	
		TropoGal->tm_a_size[i] = 0;	
	}

	for(i=0;i<4;i++) {
		TropoGal->es_b_size[i] = 0;	
		TropoGal->ld_b_size[i] = 0;	
		TropoGal->tm_b_size[i] = 0;	
	}

	TropoGal->hgt_pix_values = NULL;	
	TropoGal->lnd_values  = NULL;	
	TropoGal->am_a_values = NULL;
	TropoGal->es_a_values = NULL;
	TropoGal->ld_a_values = NULL;
	TropoGal->ps_a_values = NULL;
	TropoGal->tm_a_values = NULL;
	TropoGal->es_b_values = NULL;
	TropoGal->ld_b_values = NULL;
	TropoGal->tm_b_values = NULL;

}

/*****************************************************************************
 * Name        : initTropoGalParameters
 * Description : Initialise a TTROPOGalParameters structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTROPOGal *TropoGal             I  N/A  TTROPOGal struct
 * TTROPOGalParameters *GalParam   O  N/A  TTROPOGalParameters struct
 *****************************************************************************/
void initTropoGalParameters (TTROPOGal *TropoGal,TTROPOGalParameters *GalParam) {
	
	int i;

	for (i=0;i<4;i++) {
		GalParam->gm[i]          = 0; 
		GalParam->ph[i]          = 0;
		GalParam->eh[i]          = 0;
		GalParam->tmh[i]         = 0;
		GalParam->g0[i]          = 0;
		GalParam->ps[i]          = 0; 
		GalParam->tm[i]          = 0; 
		GalParam->am[i]          = 0; 
		GalParam->es[i]          = 0; 
		GalParam->ld[i]          = 0; 
		GalParam->zwd_map[i]     = 0;
		GalParam->zhd_map[i]     = 0;
		GalParam->ztd_map[i]     = 0;
		GalParam->validpoint[i]  = 1;
	}

	GalParam->DoY = 0;
	GalParam->hour_minute = 0;

	GalParam->a  = NULL;
	GalParam->b  = NULL;
	
	GalParam->a = malloc(sizeof(double)*TropoGal->ps_a_size[2]);
	//GalParam->b = malloc(sizeof(double)*TropoGal->tm_b_size[3]);
	GalParam->b = malloc(sizeof(double)*4);
}

/*****************************************************************************
 * Name        : initFilterSolution
 * Description : Initialise a TFilterSolution structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TFilterSolution  *solution      O  N/A  TFilterSolution struct
 *****************************************************************************/
void initFilterSolution (TFilterSolution *solution) {
	int	i;

	solution->prevNumSatellites = 0;
	solution->prevNumSatellitesGPS = 0;

	for (i=0;i<MAX_UNK;i++) {
		solution->parameters[i] = 0;
	}

	for (i=0;i<MAX_VECTOR_UNK;i++) {
		solution->correlations[i] = 0;
	}
}

/*****************************************************************************
 * Name        : initConstellation
 * Description : Initialise a TConstellation structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TConstellation  *constellation  O  N/A  TConstellation struct
 *****************************************************************************/
void initConstellation (TConstellation *constellation) {
	constellation->numSatellites = 0;
	constellation->sat = NULL;
}

/*****************************************************************************
 * Name        : initConstellationElement
 * Description : Initialise a TConstellationElement structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TConstellationElement  *sat     O  N/A  TConstellationElement struct
 *****************************************************************************/
void initConstellationElement (TConstellationElement *sat) {
	int		i;
	
	sat->GNSS = GPS;
	sat->block = UNKNOWN_BLOCK;
	for (i=0;i<MAX_FREQUENCIES_PER_GNSS;i++)
		sat->PCO[i][0] = sat->PCO[i][1] = sat->PCO[i][2] = 0;
	sat->PRN = 0;
	sat->SVN = 0;
	sat->tDecommissioned.MJDN = 62502;  // 1st January 2030
	sat->tDecommissioned.SoD = 0;
	sat->tLaunch.MJDN = 0;
	sat->tLaunch.SoD = 0;

	//This data must be given in the ANTEX file
	sat->zen1 = 0;
	sat->zen2 = 0;
	sat->dzen = 0;
	sat->nzen = 1;		//Initalize to 1 to avoid division to zero, even though this value will be replaced by the data in the file

	//This values can appear or not in the file
	sat->azi1 = 0;
	sat->azi2 = 0;
	sat->dazi = 0;		//Set to 0. If greater than 0, then azimuth data is available
	sat->numazi = 0;		//Set to 0 because dazi is 0.

	sat->noazi = NULL;
	sat->azi = NULL;

}

/*****************************************************************************
 * Name        : initAntennaList
 * Description : Initialise a TAntennaList structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TAntennaList  *antennaList      O  N/A  TAntennaList struct
 *****************************************************************************/
void initAntennaList (TAntennaList *antennaList) {
	antennaList->numAnt = 0;
	antennaList->ant = NULL;
}

/*****************************************************************************
 * Name        : initAntenna
 * Description : Initialise a TAntenna structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TAntenna  *antenna              O  N/A  TAntenna struct
 *****************************************************************************/
void initAntenna (TAntenna *antenna) {
	int		i;
	
	for (i=0;i<MAX_FREQUENCIES_PER_GNSS;i++) 
		antenna->PCO[i][0] = antenna->PCO[i][1] = antenna->PCO[i][2] = 0;
	antenna->type[0] = '\0';
	antenna->type_ant[0] = '\0';
	antenna->type_radome[0] = '\0';

	//This data must be given in the ANTEX file
	antenna->azi1 = 0;
	antenna->azi2 = 0;
	antenna->dazi = 0;	
	antenna->numazi = 0;	

	//This values can appear or not in the file
	antenna->zen1 = 0;
	antenna->zen2 = 0;
	antenna->dzen = 0;	//Set to 0. If greater than 0, then azimuth data is available
	antenna->nzen = 0;

	antenna->noazi = NULL;
	antenna->azi = NULL;
}

/*****************************************************************************
 * Name        : initStat
 * Description : Initialise a TStat structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TStat  *stat                    O  N/A  TStat struct
 *****************************************************************************/
void initStat (TStat *stat) {
	stat->n = 0;
	stat->mean = 0;
	stat->mean2 = 0;
}

/*****************************************************************************
 * Name        : initTGD
 * Description : Initialise a TGDData structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTGDdata  *tgdData              O  N/A  TTGDdata struct
 * enum P1C1DCBModel  p1c1dcbModel I  N/A  P1C1 DCB source (p1c1UNKNOWN if still unavailable)
 * enum P1P2DCBModel  p1p2dcbModel I  N/A  P1P2 DCB source (p1p2UNKNOWN if still unavailable)
 *****************************************************************************/
void initTGD (TTGDdata *tgdData, enum P1C1DCBModel p1c1dcbModel, enum P1P2DCBModel p1p2dcbModel) {
	tgdData->BRDC = NULL;
	tgdData->DCB = NULL;
	tgdData->p1c1dcbModel = p1c1dcbModel;
	tgdData->p1p2dcbModel = p1p2dcbModel;

//	if (tgdData->p1c1dcbModel==p1c1STRICT ||tgdData->p1p2dcbModel==p1p2DCB) {
		tgdData->DCB = malloc(sizeof(TDCBdata));
		initDCB(tgdData->DCB);
//	}

	initIONEXDCB(&tgdData->ionexDCB);
	initFPPPDCB(&tgdData->fpppDCB);
}

/*****************************************************************************
 * Name        : initDCB
 * Description : Initialise a TDCBdata structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TDCBdata  *dcbData              O  N/A  TDCBdata struct
 *****************************************************************************/
void initDCB (TDCBdata *dcbData) {
	int i,j,k;
	
	dcbData-> n = 0;
	
	for (i=0;i<MAX_DCB_TYPES;i++) {
		dcbData->block[i].startTime.MJDN = 0;
		dcbData->block[i].startTime.SoD = 0;
		dcbData->block[i].endTime.MJDN = 0;
		dcbData->block[i].endTime.SoD = 0;
		dcbData->block[i].measFrom = NA;
		dcbData->block[i].measTo = NA;
		for (j=0;j<MAX_GNSS;j++) {
			for (k=0;k<MAX_SATELLITES_PER_GNSS;k++) {
				dcbData->block[i].dcb[j][k] = 0;
				dcbData->block[i].available[j][k] = 0;
			}
		}
	}
}

/*****************************************************************************
 * Name        : initReceiverList
 * Description : Initialise a TReceiverList structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TReceiverList  *recList         O  N/A  TReceiverList struct
 *****************************************************************************/
void initReceiverList (TReceiverList *recList) {
	recList->n = 0;
	recList->rec = NULL;
}

/*****************************************************************************
 * Name        : initStationList
 * Description : Initialise a TStationList structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TStationList  *stationList      O  N/A  TStationList struct
 *****************************************************************************/
void initStationList (TStationList *stationList) {
	stationList->n = 0;
	stationList->station = NULL;
}

/*****************************************************************************
 * Name        : initSBASdatabox
 * Description : Initialise a TSBASdatabox structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TSBASdatabox  *SBASdatabox      O  N/A  TSBASdatabox struct
 *****************************************************************************/
void initSBASdatabox (TSBASdatabox *SBASdatabox) {

	SBASdatabox->SBASdata = NULL;
	SBASdatabox->SBASdata = malloc(sizeof(TSBASdata));
	
	SBASdatabox->HWIR = -1.;
	SBASdatabox->VWIR = -1.;
	SBASdatabox->HPLPercentileValues = -1.;
	SBASdatabox->VPLPercentileValues = -1.;
	SBASdatabox->HPLPercentileSamples = -1.;
	SBASdatabox->VPLPercentileSamples = -1.;
	SBASdatabox->MaxHPL = -1.;
	SBASdatabox->MaxVPL = -1.;
	SBASdatabox->decimation = 100.;	//This value is for the first epoch, to ensure there is no discontinuity

	SBASdatabox->TotalPAEpochs = 0;
	SBASdatabox->TotalPAEpochsAvail = 0;
	SBASdatabox->TotalNPAEpochs = 0;
	SBASdatabox->NumEpochsRisk = 0;
	SBASdatabox->NumMI = 0;
	SBASdatabox->NumHMI = 0;
	SBASdatabox->NumVMI = 0;
	SBASdatabox->HPL = NULL;
	SBASdatabox->VPL = NULL;
	SBASdatabox->LastEpochAvailPrevCurrDisc.SoD = -1.;
	SBASdatabox->FirstEpochAvailAfterPrevDisc.SoD = -1.;

	//decimation, HerrorEpoch. VerrorEpoch, HWIREpoch, VWIREpoch, MaxHPLEpoch and MaxVPLEpoch does not need to be initialized
}


/*****************************************************************************
 * Name        : initSBASblock
 * Description : Initialise a TSBASblock structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TSBASblock  *sbasblock          O  N/A  TSBASblock struct
 *****************************************************************************/
void initSBASblock (TSBASblock *sbasblock) {

	sbasblock->frequency = 1;			//Only appears in RINEXB file
	sbasblock->receiverindex = 0 ;			//Only appears in RINEXB file
	sbasblock->datalength = 32 ;			//Only appears in RINEXB file (in EMS message is 32)
	strcpy(sbasblock->sourceidentifier,"SBA");	//Only appears in RINEXB file

	sbasblock->dontuse = 0;			//Will be 1 when a type 0 message is received, and will last one minute at least
	sbasblock->problems = 0;			//Will be 1 when a type 0 message is received and it is filled with 0
	sbasblock->messageslost=0;

	sbasblock->IODF=NULL;				//Will have 1 position for type 2,3,4,5,24 message and 4 position for type 6. For other messages will be empty.
	sbasblock->IODP=-1;				//Type 6 does not have IODP. -1 means value not set.
	sbasblock->numsatellites=-1;			//-1 means value not set.


	sbasblock->PRNactive=NULL;			//Will only contain data when a type 1 message arrives. 
	sbasblock->pos2PRN=NULL;			//Will only contain data when a type 1 message arrives. It will have 51 positions when memory is allocated.
	sbasblock->pos2GNSS=NULL;			//Will only contain data when a type 1 message arrives. It will have 51 positions when memory is allocated.
	sbasblock->PRN2pos=NULL;			//Will only contain data when a type 1 message arrives. 

	sbasblock->PRC=NULL;				//Will only contain data when a type 2,3,4,5,24 message arrives. It will have 13 positions for type 2,3,4,5 and 6 for type 24.
	sbasblock->RRC=NULL;				//Will only contain data when a type 2,3,4,5,24 message arrives. It will have 13 positions for type 2,3,4,5 and 6 for type 24.
	sbasblock->UDREI=NULL;				//Will only contain data when a type 2,3,4,5,24 message arrives. It will have 13 positions for type 2,3,4,5 and 6 for type 24.
	sbasblock->UDRE=NULL;				//Will only contain data when a type 2,3,4,5,24 message arrives. It will have 13 positions for type 2,3,4,5 and 6 for type 24.
	sbasblock->UDREsigma=NULL;			//Will only contain data when a type 2,3,4,5,24 message arrives. It will have 13 positions for type 2,3,4,5 and 6 for type 24.

	sbasblock->UDREIacu=NULL;			//Will only contain data when a type 6 message arrives. It will have 51 positions when memory is allocated.
	sbasblock->UDREacu=NULL;			//Will only contain data when a type 6 message arrives. It will have 51 positions when memory is allocated.
	sbasblock->UDREacusigma=NULL;			//Will only contain data when a type 6 message arrives. It will have 51 positions when memory is allocated.

	sbasblock->tlat=-1;				//Only appears in message type 7. -1 means value not set.
	sbasblock->aiind=NULL;				//Will only contain data when a type 7 message arrives. It will have 51 positions when memory is allocated.
	sbasblock->aifactor=NULL;			//Will only contain data when a type 7 message arrives. It will have 51 positions when memory is allocated.
	sbasblock->timeoutintervalnonprecise=NULL;	//Will only contain data when a type 7 message arrives. It will have 51 positions when memory is allocated.
	sbasblock->timeoutintervalprecise=NULL;	//Will only contain data when a type 7 message arrives. It will have 51 positions when memory is allocated.
	sbasblock->fastcorrupdateinterval=NULL;	//Will only contain data when a type 7 message arrives. It will have 51 positions when memory is allocated.
	

	sbasblock->degradationfactors=NULL;		//Will only contain data when a type 10 message arrives. It will have 16 positions when memory is allocated.

	sbasblock->longtermsaterrcorrections=NULL;	//Will only contain data when a type 25 or 24 message arrives. The size will change depending on the message.
	sbasblock->numlongtermsaterrcorrections=-1;	//Only appears in type 25 or 24 messages. -1 means value not set.

	sbasblock->BlockID=-1;				//Only appears in type 24 messages. -1 means value not set.

	sbasblock->geonavigationmessage=NULL;		//Will only contain data when a type 9 message arrives. It will have 17 positions when memory is allocated.

	sbasblock->geoalmanacsmessage=NULL;		//Will only contain data when a type 17 message arrives. It will have a matrix of 3x12, due there are 3 satellites in the message 
							//and 12 parameters per satellite
	sbasblock->numgeoalmanacs=-1;			//Only appears in type 17 messages. -1 means value not set.

	sbasblock->servicemessage=NULL;		//Will only contain data when a type 27 message arrives. It will have 9 positions when memory is allocated.
	sbasblock->regioncoordinates=NULL;		//Will only contain data when a type 27 message arrives. It will have a matrix of Nx9 positions when memory is allocated. 
							//N will vary between 1-5 dependeing on the the number of regions given in the message
	sbasblock->numregioncoordinates=-1;		//Only appears in type 27 messages. -1 means value not set

	sbasblock->networktimemessage=NULL;		//Will only contain data when a type 12 message arrives. It will have 12 positions when memory is allocated.

	sbasblock->clockephemeriscovariance=NULL;	//Will only contain data when a type 28 message arrives. It will have a matrix of Nx13 positions when memory is allocated, being N=1 or 2 
	sbasblock->numclockephemeriscovariance=-1;	//Only appears in message type 28. -1 means value not set

	sbasblock->igpmaskmessage=NULL;		//Will only contain data when a type 18 message arrives. It will have 204 positions when memory is allocated (201 for the IGP mask and 3 for parameters)

	sbasblock->ionodelayparameters=NULL;		//Will only contain data when a type 26 message arrives. It will have a matrix of 15x7 positions when memory is allocated.
	
}

/*****************************************************************************
 * Name        : initSBASdata
 * Description : Initialise a TSBASdata structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TSBASdata  *SBASdata            O  N/A  TSBASdata struct
 * int pos                         I  N/A  Slot of TSBASdata to be initialized
 *****************************************************************************/
void initSBASdata (TSBASdata *SBASdata, int pos) {
	int i,j,k,l;


	//-1 -> Timeout not set  9999999-> Timeout infinite
	//Message type number                0   1  2  3  4  5  6   7  8   9  10 11    12 13 14 15 16      17   18 19 20 21 22 23 24  25  26    27  28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63
	int timeoutnonprecision[64] = {9999999,600,-1,-1,-1,-1,18,360,-1,360,360,-1,86400,-1,-1,-1,-1,9999999,1200,-1,-1,-1,-1,-1,-1,360,600,86400,360,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	int timeoutprecision[64]    = {9999999,600,-1,-1,-1,-1,12,240,-1,240,240,-1,86400,-1,-1,-1,-1,9999999,1200,-1,-1,-1,-1,-1,-1,240,600,86400,240,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	int msgupdateinterval[64]   = {     -1,120,-1,-1,-1,-1, 6,120,-1,120,120,-1,  300,-1,-1,-1,-1,    300, 300,-1,-1,-1,-1,-1,-1,120,300,  300,120,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};


	if(pos==0) {
		memcpy(SBASdata[pos].timeoutmessages[0],&timeoutnonprecision,sizeof(timeoutnonprecision));
		memcpy(SBASdata[pos].timeoutmessages[1],&timeoutprecision,sizeof(timeoutprecision));
		memcpy(SBASdata[pos].msgupdateinterval,&msgupdateinterval,sizeof(msgupdateinterval));
	} else {
		//This is done because time out may be different from the default one (received from parameters)
		//This way, the user timeouts are propagated to all GEOs
		memcpy(SBASdata[pos].timeoutmessages[0],SBASdata[0].timeoutmessages[0],sizeof(timeoutnonprecision));
		memcpy(SBASdata[pos].timeoutmessages[1],SBASdata[0].timeoutmessages[1],sizeof(timeoutprecision));
		memcpy(SBASdata[pos].msgupdateinterval,SBASdata[0].msgupdateinterval,sizeof(msgupdateinterval));
	}



	//Set all satellites unselected by default
	for(i=0;i<5;i++) {
		SBASdata[pos].numsatellites[i]=0;
		for(j=0;j<MAX_GNSS;j++) {
			for(k=0;k<MAX_SBAS_PRN;k++) {
				SBASdata[pos].PRNactive[i][j][k]=0;
				SBASdata[pos].PRN2pos[i][j][k]=-1;
				SBASdata[pos].GEOPRN2pos[k]=-1;
				SBASdata[pos].failedmessages[k]=0;
				SBASdata[pos].missed4msg[k]=0;
				SBASdata[pos].useforbidden[j][k]=0;
			}
		}
	}
	//Set all values to -1 or 9999 (value not set)
	for(i=0;i<64;i++) {
		SBASdata[pos].oldlastmsgreceived[i].MJDN = -1;
		SBASdata[pos].oldlastmsgreceived[i].SoD = -1.;
		SBASdata[pos].lastmsgreceived[i].MJDN = -1;
		SBASdata[pos].lastmsgreceived[i].SoD = -1.;
		SBASdata[pos].oldmaskdiscarded[i]=0;
	}

	for(i=0;i<51;i++) {

		for(j=0;j<5;j++) {
			SBASdata[pos].lastlongtermdata[j][i].MJDN = -1;
			SBASdata[pos].lastlongtermdata[j][i].SoD = -1.;

			SBASdata[pos].prevlastlongtermdata[j][i].MJDN = -1;
			SBASdata[pos].prevlastlongtermdata[j][i].SoD = -1.;

			SBASdata[pos].lastcovmatrix[j][i].MJDN = -1;
			SBASdata[pos].lastcovmatrix[j][i].SoD = -1.;

			SBASdata[pos].fastcorrtimeout[0][j][i] = -1;
			SBASdata[pos].fastcorrtimeout[1][j][i] = -1;
			SBASdata[pos].fastcorrupdateinterval[j][i] = -1;
			SBASdata[pos].aifactor[j][i] = -1;
			SBASdata[pos].tlat[j] =  0;
			SBASdata[pos].lastfastdegfactor[j][i].MJDN = -1;
			SBASdata[pos].lastfastdegfactor[j][i].SoD = -1.;

		}


		SBASdata[pos].firstmessage.MJDN=-1;
		SBASdata[pos].firstmessage.SoD=-1.;
		//SBASdata[pos].oldlastfastcorrections[i].MJDN = -1;
		//SBASdata[pos].oldlastfastcorrections[i].SoD = -1;
		SBASdata[pos].oldlastintegrityinfo[i].MJDN = -1;
		SBASdata[pos].oldlastintegrityinfo[i].SoD = -1;
		//SBASdata[pos].oldlastfastdegfactor[i].MJDN = -1;
		//SBASdata[pos].oldlastfastdegfactor[i].SoD = -1;

		SBASdata[pos].lastintegrityinfo[i].MJDN = -1;
		SBASdata[pos].lastintegrityinfo[i].SoD = -1.;
		//SBASdata[pos].lastfastdegfactor[i].MJDN = -1;
		//SBASdata[pos].lastfastdegfactor[i].SoD = -1;

		SBASdata[pos].lastfastmessage[i] = -1;
		//SBASdata[pos].fastcorrtimeoutnonprecision[i] = -1;
		//SBASdata[pos].fastcorrtimeoutprecision[i] = -1;
		//SBASdata[pos].fastcorrupdateinterval[i] = -1;
		//SBASdata[pos].oldfastcorrtimeoutnonprecision[i] = -1;
		//SBASdata[pos].oldfastcorrtimeoutprecision[i] = -1;
		//SBASdata[pos].oldfastcorrupdateinterval[i] = -1;
		//SBASdata[pos].PRC[i] = 9999;
		//SBASdata[pos].RRC[i] = 9999;
		//SBASdata[pos].UDRE[i] = -1;
		//SBASdata[pos].UDREsigma[i] = -1;
		//SBASdata[pos].oldPRC[i] = -1;
		//SBASdata[pos].oldRRC[i] = -1;
		//SBASdata[pos].oldUDRE[i] = -1;
		//SBASdata[pos].oldUDREsigma[i] = -1;
		//SBASdata[pos].oldaifactor[i] = -1;
		SBASdata[pos].UDREI6[i]=-1;
		SBASdata[pos].UDRE6[i]=-1;
		SBASdata[pos].UDREsigma6[i]=-1;
		SBASdata[pos].oldUDREI6[i]=-1;
		SBASdata[pos].oldUDRE6[i]=-1;
		SBASdata[pos].oldUDREsigma6[i]=-1;

		//SBASdata[pos].IODFfastcorr[i]=-1;
		SBASdata[pos].IODFintegrity[i]=-1;
		//SBASdata[pos].oldIODFfastcorr[i]=-1;
		SBASdata[pos].oldIODFintegrity[i]=-1;

		for(j=0;j<5;j++) {
			SBASdata[pos].pos2PRN[j][i] = -1;
			SBASdata[pos].pos2GNSS[j][i] = -1;
			//SBASdata[pos].oldpos2PRN[j][i] = -1;
			//SBASdata[pos].oldpos2GNSS[j][i] = -1;
		}


		for(j=0;j<5;j++) {
			SBASdata[pos].poslastFC[j][i] = -1;
			SBASdata[pos].numFC[j][i] = 0;
			for(k=0;k<MAXSBASFASTCORR;k++) {
				SBASdata[pos].PRC[j][k][i] = 9999;
				SBASdata[pos].RRC[j][k][i] = 9999;
				SBASdata[pos].UDREI[j][k][i] = -1;
				SBASdata[pos].UDRE[j][k][i] = -1;
				SBASdata[pos].UDREsigma[j][k][i] = -1;
				SBASdata[pos].IODF[j][k][i] = -1;
				SBASdata[pos].lastfastcorrections[j][k][i].MJDN = -1;
				SBASdata[pos].lastfastcorrections[j][k][i].SoD = -1.;
			}
		}

		for(j=0;j<13;j++) {
			for(k=0;k<4;k++) {
				SBASdata[pos].longtermsaterrcorrections[k][i][j] = 9999;
				SBASdata[pos].prevlongtermsaterrcorrections[k][i][j] = 9999;
			}
		}

		for(j=0;j<13;j++) {
			for(k=0;k<5;k++) {
				SBASdata[pos].clockephemeriscovariance[k][i][j] = 9999;
			}
		}
	}
	
	if(pos==0) SBASdata[pos].PRN		=  0;
	else SBASdata[pos].PRN				= -1;

	SBASdata[pos].alarmtime.MJDN		= -1;
	SBASdata[pos].alarmtime.SoD			= -1.;
	SBASdata[pos].alarmTimeRemaining	=  0;	
	SBASdata[pos].alarmGEOPRN			=  0;
	SBASdata[pos].secondalarmGEOPRN		=  0;
	SBASdata[pos].cleared				=  0;
	SBASdata[pos].numreceivers			=  0;
	SBASdata[pos].numSBASsatellites		=  0;
	SBASdata[pos].dontuse				=  0;
	SBASdata[pos].problems				=  0;
	SBASdata[pos].IODPmask				=  4;	//Set to 4 to avoid invalid vector indexes
	SBASdata[pos].oldIODPmask			=  4;	//Set to 4 to avoid invalid vector indexes
	SBASdata[pos].oldnumsatellites		=  0;
	SBASdata[pos].IODPfastcorr			=  4;	//Set to 4 to avoid invalid vector indexes
	SBASdata[pos].oldIODPfastcorr		=  4;   //Set to 4 to avoid invalid vector indexes
	SBASdata[pos].IODPlongterm			=  4;   //Set to 4 to avoid invalid vector indexes
	SBASdata[pos].oldIODPlongterm		=  4;   //Set to 4 to avoid invalid vector indexes

	for(i=0;i<4;i++) {
		for(l=0;l<9;l++) {
			SBASdata[pos].numberofregions[l][i]=0;

			for(j=0;j<40;j++) {
				for(k=0;k<11;k++) {
					SBASdata[pos].regioncoordinates[l][i][j][k]=9999;
				}
			}
		}
	}

	for(i=0;i<8;i++) {
		for(j=0;j<9;j++) {
			SBASdata[pos].servicemessagesreceived[j][i]=-1;
			SBASdata[pos].maxprioritycode[j]=0;
			SBASdata[pos].totalservicemessagesreceived[j]=0;
		}
	}

	SBASdata[pos].IODPdegcorr	=  4;	//Set to 4 to avoid invalid vector indexes
	SBASdata[pos].oldIODPdegcorr	=  4;	//Set to 4 to avoid invalid vector indexes
	SBASdata[pos].IODS		=  8;	//Set to 8 to avoid invalid vector indexes
	SBASdata[pos].oldIODS		=  8;	//Set to 8 to avoid invalid vector indexes

	for(i=0;i<16;i++) {
		SBASdata[pos].degradationfactors[i]=-1;
		SBASdata[pos].olddegradationfactors[i]=-1;
	}

	for(i=0;i<17;i++) {
		SBASdata[pos].geonavigationmessage[i]=9999;
		SBASdata[pos].oldgeonavigationmessage[i]=9999;
	}

	for(i=0;i<12;i++) {
		SBASdata[pos].networktimemessage[i]=-9999;
		for(j=0;j<3;j++) {
			SBASdata[pos].geoalmanacsmessage[j][i]=-1;
			SBASdata[pos].oldgeoalmanacsmessage[j][i]=-1;
		}
	}

	SBASdata[pos].IODPcovariance		= -1;
	SBASdata[pos].oldIODPcovariance		= -1;
	SBASdata[pos].numIGPbandbroadcast	= -1;
	SBASdata[pos].numIGPbandreceived	=  0;
	SBASdata[pos].oldnumIGPbandreceived	=  0;
	SBASdata[pos].IODImask				=  4; //Initialize to 4 because it is not a valid IODI and is a valid position in vector
	SBASdata[pos].oldIODImask			=  4; //Initialize to 4 because it is not a valid IODI and is a valid position in vector
	SBASdata[pos].IODIcorr				= -1;
	SBASdata[pos].oldIODIcorr			= -1;
	SBASdata[pos].numgeoalmanacs		=  0;
	SBASdata[pos].oldnumgeoalmanacs		=  0;


	for(i=0;i<11;i++) {
		SBASdata[pos].IGPbandreceived[i]= -1;
		SBASdata[pos].oldIGPbandreceived[i]= -1;

		for(j=0;j<202;j++) {
			for(k=0;k<5;k++) {
				SBASdata[pos].IGPinMask[k][i][j]=0;
			}
			SBASdata[pos].Ionodelay[i][j]=-1;
			SBASdata[pos].IonoGIVE[i][j]=-1;
			SBASdata[pos].Ionosigma[i][j]=-1;
			SBASdata[pos].lastiono[i][j].MJDN=-1;
			SBASdata[pos].lastiono[i][j].SoD=-1.;
			SBASdata[pos].IGP2Mask[i][j]=4;	//Initialize to 4 because it is not a valid IODI and is a valid position in vector

		}

		for(j=0;j<14;j++) {
			for(k=0;k<15;k++) {
				SBASdata[pos].BlockIDPlace2Grid[i][j][k]=-1;
				SBASdata[pos].oldBlockIDPlace2Grid[i][j][k]=-1;
			}
		}
	}

	SBASdata[pos].sigmamultipathtype=-1;
	SBASdata[pos].numsigmamultipath=0;
	SBASdata[pos].sigmamultipathdata=NULL;

	SBASdata[pos].numSat60=0;
}

/*****************************************************************************
 * Name        : ClearSBASdata
 * Description : Clear a TSBASdata struct
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TSBASdata  *SBASdata            O  N/A  TSBASdata struct
 * int pos                         I  N/A  Slot of TSBASdata to be cleared
 *****************************************************************************/
void ClearSBASdata (TSBASdata *SBASdata, int pos) {

	int i,j,k,l;

	/*NOTE: The differences of this function from initSBASdata are:
		- we don't need to copy timeout values again
	- Values for message type 0 (DONTUSE) does not have to be erased
	- Common data (like number of satellites) which are stored in position 0 of TSBASdata vector does not have to be erased
	- Almanac data does not have to be erased
	- Number of satellites with fast and slow sigma of 60 metres does not have to be erased
	*/

	//Set all satellites unselected by default
	for(i=0;i<5;i++) {
		SBASdata[pos].numsatellites[i]=0;
		for(j=0;j<MAX_GNSS;j++) {
			for(k=0;k<MAX_SBAS_PRN;k++) {
				SBASdata[pos].PRNactive[i][j][k]=0;
				SBASdata[pos].PRN2pos[i][j][k]=-1;
				SBASdata[pos].failedmessages[k]=0;
				SBASdata[pos].missed4msg[k]=0;
				if(pos==0) continue;
				SBASdata[pos].GEOPRN2pos[k]=-1;
			}
		}
	}
	//Set all values to -1 or 9999 (value not set)
	for(i=0;i<64;i++) {
		SBASdata[pos].oldlastmsgreceived[i].MJDN = -1;
		SBASdata[pos].oldlastmsgreceived[i].SoD = -1.;
		SBASdata[pos].oldmaskdiscarded[i]=0;

		if(i==DONTUSE || i==GEOSATELLITEALMANACS) continue;

		SBASdata[pos].lastmsgreceived[i].MJDN = -1;
		SBASdata[pos].lastmsgreceived[i].SoD = -1.;
	}

	for(i=0;i<51;i++) {

		for(j=0;j<5;j++) {
			SBASdata[pos].lastlongtermdata[j][i].MJDN = -1;
			SBASdata[pos].lastlongtermdata[j][i].SoD = -1.;

			SBASdata[pos].prevlastlongtermdata[j][i].MJDN = -1;
			SBASdata[pos].prevlastlongtermdata[j][i].SoD = -1.;

			SBASdata[pos].lastcovmatrix[j][i].MJDN = -1;
			SBASdata[pos].lastcovmatrix[j][i].SoD = -1.;

			SBASdata[pos].fastcorrtimeout[0][j][i] = -1;
			SBASdata[pos].fastcorrtimeout[1][j][i] = -1;
			SBASdata[pos].fastcorrupdateinterval[j][i] = -1;
			SBASdata[pos].aifactor[j][i] = -1;
			SBASdata[pos].tlat[j] =  0;
			SBASdata[pos].lastfastdegfactor[j][i].MJDN = -1;
			SBASdata[pos].lastfastdegfactor[j][i].SoD = -1.;
		}


		SBASdata[pos].firstmessage.MJDN=-1;
		SBASdata[pos].firstmessage.SoD=-1.;
		//SBASdata[pos].oldlastfastcorrections[i].MJDN = -1;
		//SBASdata[pos].oldlastfastcorrections[i].SoD = -1.;
		SBASdata[pos].oldlastintegrityinfo[i].MJDN = -1;
		SBASdata[pos].oldlastintegrityinfo[i].SoD = -1.;
		//SBASdata[pos].oldlastfastdegfactor[i].MJDN = -1;
		//SBASdata[pos].oldlastfastdegfactor[i].SoD = -1.;

		SBASdata[pos].lastintegrityinfo[i].MJDN = -1;
		SBASdata[pos].lastintegrityinfo[i].SoD = -1.;
		//SBASdata[pos].lastfastdegfactor[i].MJDN = -1;
		//SBASdata[pos].lastfastdegfactor[i].SoD = -1.;

		SBASdata[pos].lastfastmessage[i]= -1;
		//SBASdata[pos].fastcorrtimeoutnonprecision[i] = -1;
		//SBASdata[pos].fastcorrtimeoutprecision[i] = -1;
		//SBASdata[pos].fastcorrupdateinterval[i] = -1;
		//SBASdata[pos].oldfastcorrtimeoutnonprecision[i] = -1;
		//SBASdata[pos].oldfastcorrtimeoutprecision[i] = -1;
		//SBASdata[pos].oldfastcorrupdateinterval[i] = -1;
		//SBASdata[pos].PRC[i] = 9999;
		//SBASdata[pos].RRC[i] = 9999;
		//SBASdata[pos].UDRE[i] = -1;
		//SBASdata[pos].UDREsigma[i] = -1;
		//SBASdata[pos].oldPRC[i] = -1;
		//SBASdata[pos].oldRRC[i] = -1;
		//SBASdata[pos].oldUDRE[i] = -1;
		//SBASdata[pos].oldUDREsigma[i] = -1;
		//SBASdata[pos].oldaifactor[i] = -1;
		SBASdata[pos].UDREI6[i]=-1;
		SBASdata[pos].UDRE6[i]=-1;
		SBASdata[pos].UDREsigma6[i]=-1;
		SBASdata[pos].oldUDREI6[i]=-1;
		SBASdata[pos].oldUDRE6[i]=-1;
		SBASdata[pos].oldUDREsigma6[i]=-1;

		//SBASdata[pos].IODFfastcorr[i]=-1;
		SBASdata[pos].IODFintegrity[i]=-1;
		//SBASdata[pos].oldIODFfastcorr[i]=-1;
		SBASdata[pos].oldIODFintegrity[i]=-1;

		for(j=0;j<5;j++) {
			SBASdata[pos].pos2PRN[j][i] = -1;
			SBASdata[pos].pos2GNSS[j][i] = -1;
			//SBASdata[pos].oldpos2PRN[j][i] = -1;
			//SBASdata[pos].oldpos2GNSS[j][i] = -1;
		}


		for(j=0;j<5;j++) {
			SBASdata[pos].poslastFC[j][i] = -1;
			SBASdata[pos].numFC[j][i] = 0;
			for(k=0;k<MAXSBASFASTCORR;k++) {
				SBASdata[pos].PRC[j][k][i] = 9999;
				SBASdata[pos].RRC[j][k][i] = 9999;
				SBASdata[pos].UDREI[j][k][i] = -1;
				SBASdata[pos].UDRE[j][k][i] = -1;
				SBASdata[pos].UDREsigma[j][k][i] = -1;
				SBASdata[pos].IODF[j][k][i] = -1;
				SBASdata[pos].lastfastcorrections[j][k][i].MJDN = -1;
				SBASdata[pos].lastfastcorrections[j][k][i].SoD = -1.;
			}
		}

		for(j=0;j<13;j++) {
			for(k=0;k<4;k++) {
				SBASdata[pos].longtermsaterrcorrections[k][i][j] = 9999;
				SBASdata[pos].prevlongtermsaterrcorrections[k][i][j] = 9999;
			}
		}

		for(j=0;j<13;j++) {
			for(k=0;k<5;k++) {
				SBASdata[pos].clockephemeriscovariance[k][i][j] = 9999;
			}
		}
	}
	
	SBASdata[pos].IODPmask				=  4;	//Set to 4 to avoid invalid vector indexes
	SBASdata[pos].oldIODPmask			=  4;	//Set to 4 to avoid invalid vector indexes
	SBASdata[pos].oldnumsatellites		=  0;
	SBASdata[pos].IODPfastcorr			=  4;   //Set to 4 to avoid invalid vector indexes
	SBASdata[pos].oldIODPfastcorr		=  4;   //Set to 4 to avoid invalid vector indexes
	SBASdata[pos].IODPlongterm			=  4;   //Set to 4 to avoid invalid vector indexes
	SBASdata[pos].oldIODPlongterm		=  4;   //Set to 4 to avoid invalid vector indexes

	for(i=0;i<4;i++) {
		for(l=0;l<9;l++) {
			SBASdata[pos].numberofregions[l][i]=0;

			for(j=0;j<40;j++) {
				for(k=0;k<11;k++) {
					SBASdata[pos].regioncoordinates[l][i][j][k]=9999;
				}
			}
		}
	}

	for(i=0;i<8;i++) {
		for(j=0;j<9;j++) {
			SBASdata[pos].servicemessagesreceived[j][i]=-1;
			SBASdata[pos].maxprioritycode[j]=0;
			SBASdata[pos].totalservicemessagesreceived[j]=0;
		}
	}

	SBASdata[pos].IODPdegcorr	=  4;	//Set to 4 to avoid invalid vector indexes
	SBASdata[pos].oldIODPdegcorr	=  4;	//Set to 4 to avoid invalid vector indexes
	SBASdata[pos].IODS		=  8;	//Set to 8 to avoid invalid vector indexes
	SBASdata[pos].oldIODS		=  8;	//Set to 8 to avoid invalid vector indexes

	for(i=0;i<16;i++) {
		SBASdata[pos].degradationfactors[i]=-1;
		SBASdata[pos].olddegradationfactors[i]=-1;
	}

	for(i=0;i<17;i++) {
		SBASdata[pos].geonavigationmessage[i]=9999;
		SBASdata[pos].oldgeonavigationmessage[i]=9999;
	}

	for(i=0;i<12;i++) {
		SBASdata[pos].networktimemessage[i]=-9999;
	}

	SBASdata[pos].cleared				=  1;

	SBASdata[pos].IODPcovariance		= -1;
	SBASdata[pos].oldIODPcovariance		= -1;
	SBASdata[pos].numIGPbandbroadcast	= -1;
	SBASdata[pos].numIGPbandreceived	=  0;
	SBASdata[pos].oldnumIGPbandreceived	=  0;
	SBASdata[pos].IODImask				=  4; //Initialize to 4 because it is not a valid IODI and is a valid position in vector
	SBASdata[pos].oldIODImask			=  4; //Initialize to 4 because it is not a valid IODI and is a valid position in vector
	SBASdata[pos].IODIcorr				= -1;
	SBASdata[pos].oldIODIcorr			= -1;


	for(i=0;i<11;i++) {
		SBASdata[pos].IGPbandreceived[i]= -1;
		SBASdata[pos].oldIGPbandreceived[i]= -1;

		for(j=0;j<202;j++) {
			for(k=0;k<5;k++) {
				SBASdata[pos].IGPinMask[k][i][j]=0;
			}
			SBASdata[pos].Ionodelay[i][j]=-1;
			SBASdata[pos].IonoGIVE[i][j]=-1;
			SBASdata[pos].Ionosigma[i][j]=-1;
			SBASdata[pos].lastiono[i][j].MJDN=-1;
			SBASdata[pos].lastiono[i][j].SoD=-1.;
			SBASdata[pos].IGP2Mask[i][j]=4;	//Initialize to 4 because it is not a valid IODI and is a valid position in vector

		}

		for(j=0;j<14;j++) {
			for(k=0;k<15;k++) {
				SBASdata[pos].BlockIDPlace2Grid[i][j][k]=-1;
				SBASdata[pos].oldBlockIDPlace2Grid[i][j][k]=-1;
			}
		}
	}



}

/*****************************************************************************
 * Name        : initSBAScorrections
 * Description : Initialise a TSBAScorr structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TSBAScorr  *SBAScorr            O  N/A  TSBAScorr struct
 *****************************************************************************/
void initSBAScorrections (TSBAScorr *SBAScorr) {
	SBAScorr->SatCoord[0]=SBAScorr->SatCoordbrdc[0]=SBAScorr->SatCoordCor[0]=0;
	SBAScorr->SatCoord[1]=SBAScorr->SatCoordbrdc[1]=SBAScorr->SatCoordCor[1]=0;
	SBAScorr->SatCoord[2]=SBAScorr->SatCoordbrdc[2]=SBAScorr->SatCoordCor[2]=0;

	SBAScorr->Clock=SBAScorr->Clockbrdc=SBAScorr->ClockCor=0;

	SBAScorr->uraindex=-1;

	SBAScorr->IOD=-1;
	SBAScorr->IODnoSBAS=-1;
	SBAScorr->ionocorrection=0;
	
	SBAScorr->PRC=0;
	SBAScorr->RRC=0;
	SBAScorr->RRCtime=0;
	SBAScorr->UDREI=-1;
	SBAScorr->UDREsigma=0;
	SBAScorr->fastcorrdegfactor=-1;
	SBAScorr->fastcorrtmout=-1;
	SBAScorr->fastcorrsmallertmout=-1;
	SBAScorr->tudre=-1;
	SBAScorr->tu=-1;
	SBAScorr->tPRC=-1;

	SBAScorr->longtermdegradation=0;
	SBAScorr->geonavdegradation=0;
	SBAScorr->enroutedegradation=0;
	SBAScorr->fastcorrdeg=0;
	SBAScorr->RRCdeg=0;
	SBAScorr->deltaudre=1;
	SBAScorr->deltaudresource=0;

	SBAScorr->mt10avail=-1;

	SBAScorr->sigma2flt=0;
	SBAScorr->sigma2iono=0;
	SBAScorr->sigma2tropo=0;
	SBAScorr->sigma2noise=0;
	SBAScorr->sigma2divergence=0;
	SBAScorr->sigma2multipath=0;
	SBAScorr->sigma2air=0;
	SBAScorr->SBASsatsigma2=0;

	SBAScorr->fastcorIODP=-1;
	SBAScorr->fastcorIODF=-1;
	SBAScorr->fastcorPRNpos=0;
	SBAScorr->longtermIODP=-1;
	SBAScorr->longtermPRNpos=0;
	SBAScorr->serviceIODS=-1;
	SBAScorr->covarianceIODP=-1;
	SBAScorr->covariancePRNpos=-2;
	SBAScorr->ionomodelflag=0;

	SBAScorr->SBASplotIonoAvail=0;
}

/*****************************************************************************
 * Name        : initStfdESA
 * Description : Initialise a TStdESA structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TStdESA  *StdESA                O  N/A  TStdESA struct
 *****************************************************************************/
void initStfdESA (TStdESA  *StdESA) {

	int i,j;

	// Compute number of pixels and allocate space
	StdESA->numpixelhor = StdESA->xmax/StdESA->xstep;
	StdESA->numpixelver = StdESA->ymax/StdESA->ystep;
	StdESA->counthor = NULL;
	StdESA->countver = NULL;
	StdESA->counthor = malloc(sizeof(int *)*StdESA->numpixelver);
	StdESA->countver = malloc(sizeof(int *)*StdESA->numpixelver);
	StdESA->numsamplesMI=0;
	StdESA->numsamplesHMI=0;
	StdESA->numsamplesVMI=0;
	StdESA->numsamplesProcessed=0;
	StdESA->numsamplesComputed=0;
	StdESA->numsamplesSingular=0;
	StdESA->HWIR=0.;
	StdESA->VWIR=0.;
	for (i=0;i<StdESA->numpixelver;i++) {
		StdESA->counthor[i] = malloc(sizeof(int)*StdESA->numpixelhor);
		StdESA->countver[i] = malloc(sizeof(int)*StdESA->numpixelhor);
		for (j=0;j<StdESA->numpixelhor;j++) {
			StdESA->counthor[i][j] = 0;
			StdESA->countver[i][j] = 0;
		}
	}

}

/*****************************************************************************
 * Name        : initSBASPlotsMode
 * Description : Initialise a TSBASPlots and Tepoch structure for SBAS plots mode
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch *epoch                   O  N/A  TEpoch struct
 * TSBASPlots *SBASplots           O  N/A  TSBASPlots struct
 * TOptions  *options              I  N/A  TOptions struct
 * int *retvalue                   O  N/A  Return value. 1->OK -1->Error allocating memory
 *****************************************************************************/
void initSBASPlotsMode (TEpoch *epoch, TSBASPlots *SBASplots, TOptions  *options, int *retvalue)  {
	int 	i;
	
	//Set the number of satellites in view to 32 (GPS PRN 1-32)
	epoch->numSatellites=32;
	//Set last index for SBAS satellite
	if(options->NoAvailabilityPlot==0) {
		//We are computing Availability plot, so we will loop through all satellites
		epoch->lastSBASindex=31;
	} else {
		//We are only computing ionosphere availability plot, so we will use only satellite in position 0 of epoch->sat
		epoch->lastSBASindex=0;
	}
	//Set GPS measurements available only to C1C
	epoch->measOrder[GPS].nDiffMeasurements=1;
	epoch->measOrder[GPS].GNSS=GPS;
	epoch->measOrder[GPS].meas2Ind[C1C]=0;
	epoch->measOrder[GPS].conversionFactor[C1C]=1.0;
	epoch->measOrder[GPS].ind2Meas[0]=C1C;
	//Set the PRN in each position (we will set them in order, but it is not relevant)
	for (i=0;i<epoch->numSatellites;i++) {
		epoch->sat[i].GNSS=GPS;
		epoch->sat[i].PRN=i+1;
		epoch->sat[i].meas[0].value=-1;
	}

	//To minimize memory usage, we will make a table with the minimum size possible.
	//Depending on the resolution (1º, 0.1º or 0.01º we will need more or less memory)
	if(options->AvailabilityPlotStep<0.1) {
		//Resolution is below than 0.1º
		SBASplots->AvailabilityMemFactor=100;
		//Resolution is below than 1º and equal or higher than 0.1º
	} else if (options->AvailabilityPlotStep<1.) {
		SBASplots->AvailabilityMemFactor=10;
	} else {
		//Resolution is equal or higher than 1º
		SBASplots->AvailabilityMemFactor=1;
	}

	if(options->IonoPlotStep<0.1) {
		//Resolution is below than 0.1º
		SBASplots->IonoMemFactor=100;
		//Resolution is below than 1º and equal or higher than 0.1º
	} else if (options->IonoPlotStep<1.) {
		SBASplots->IonoMemFactor=10;
	} else {
		//Resolution is equal or higher than 1º
		SBASplots->IonoMemFactor=1;
	}		//Compute offset for vector position
	
	if(options->minLatplots<=0.) {
		SBASplots->offsetLatAvail=(int)(fabs(options->minLatplots)*(double)SBASplots->AvailabilityMemFactor);
		SBASplots->offsetLatIono=(int)(fabs(options->minLatplots)*(double)SBASplots->IonoMemFactor);
	} else {
		SBASplots->offsetLatAvail=(int)(-options->minLatplots*(double)SBASplots->AvailabilityMemFactor);
		SBASplots->offsetLatIono=(int)(-options->minLatplots*(double)SBASplots->IonoMemFactor);
	}
	if(options->minLonplots<=0.) {
		SBASplots->offsetLonAvail=(int)(fabs(options->minLonplots)*(double)SBASplots->AvailabilityMemFactor);
		SBASplots->offsetLonIono=(int)(fabs(options->minLonplots)*(double)SBASplots->IonoMemFactor);
	} else {
		SBASplots->offsetLonAvail=(int)(-options->minLonplots*(double)SBASplots->AvailabilityMemFactor);
		SBASplots->offsetLonIono=(int)(-options->minLonplots*(double)SBASplots->IonoMemFactor);
	}

	//Set Availability and Risk pointer to NULL
	SBASplots->SBASNumEpochsAvail=NULL;
	SBASplots->SBASNumEpochsRisk=NULL;
	SBASplots->LastEpochAvailPrevCurrDisc=NULL;
	SBASplots->FirstEpochAvailAfterPrevDisc=NULL;
	SBASplots->SBASNumEpochsAvailHourly=NULL;
	SBASplots->SBASNumEpochsRiskHourly=NULL;
	SBASplots->LastEpochAvailPrevCurrDiscHourly=NULL;
	SBASplots->FirstEpochAvailAfterPrevDiscHourly=NULL;

	//Allocate memory for availability plot counter
	if(options->NoAvailabilityPlot==0) {
		//SBASplots->AvailabilityLatSize=1+(int)((options->maxLatplots-options->minLatplots)*(double)(SBASplots->AvailabilityMemFactor)/options->AvailabilityPlotStep);
		//SBASplots->AvailabilityLonSize=1+(int)((options->maxLonplots-options->minLonplots)*(double)(SBASplots->AvailabilityMemFactor)/options->AvailabilityPlotStep);
		SBASplots->AvailabilityLatSize=1+(int)((options->maxLatplots-options->minLatplots)*(double)(SBASplots->AvailabilityMemFactor));
		SBASplots->AvailabilityLonSize=1+(int)((options->maxLonplots-options->minLonplots)*(double)(SBASplots->AvailabilityMemFactor));
		SBASplots->SBASNumEpochsAvail=malloc(sizeof(int*)*SBASplots->AvailabilityLatSize);
		if(SBASplots->SBASNumEpochsAvail==NULL) {
			*retvalue=-1;
			return;
		}
		for(i=0;i<SBASplots->AvailabilityLatSize;i++) {
			SBASplots->SBASNumEpochsAvail[i]=calloc(SBASplots->AvailabilityLonSize,sizeof(int)); //Allocate memory and set it to 0
			if (SBASplots->SBASNumEpochsAvail[i]==NULL) {
				*retvalue=-1;
				return;
			}
		}

		//Allocate memory for continuity risk data
		if(options->NoContRiskPlot==0) {
			SBASplots->SBASNumEpochsRisk=malloc(sizeof(int*)*SBASplots->AvailabilityLatSize);
			if(SBASplots->SBASNumEpochsRisk==NULL) {
				*retvalue=-1;
				return;
			}
			SBASplots->LastEpochAvailPrevCurrDisc=malloc(sizeof(double*)*SBASplots->AvailabilityLatSize);
			if(SBASplots->LastEpochAvailPrevCurrDisc==NULL) {
				*retvalue=-1;
				return;
			}
			SBASplots->FirstEpochAvailAfterPrevDisc=malloc(sizeof(double*)*SBASplots->AvailabilityLatSize);
			if(SBASplots->FirstEpochAvailAfterPrevDisc==NULL) {
				*retvalue=-1;
				return;
			}
			for(i=0;i<SBASplots->AvailabilityLatSize;i++) {
				SBASplots->SBASNumEpochsRisk[i]=calloc(SBASplots->AvailabilityLonSize,sizeof(int)); //Allocate memory and set it to 0
				if (SBASplots->SBASNumEpochsRisk[i]==NULL) {
					*retvalue=-1;
					return;
				}
				SBASplots->LastEpochAvailPrevCurrDisc[i]=calloc(SBASplots->AvailabilityLonSize,sizeof(double)); //Allocate memory and set it to 0
				if (SBASplots->LastEpochAvailPrevCurrDisc[i]==NULL) {
					*retvalue=-1;
					return;
				}
				SBASplots->FirstEpochAvailAfterPrevDisc[i]=calloc(SBASplots->AvailabilityLonSize,sizeof(double)); //Allocate memory and set it to 0
				if (SBASplots->FirstEpochAvailAfterPrevDisc[i]==NULL) {
					*retvalue=-1;
					return;
				}
			}

		}

		//Repeat memory allocation for hourly maps
		if (options->SBASHourlyMaps==1)	{
			SBASplots->SBASNumEpochsAvailHourly=malloc(sizeof(int*)*SBASplots->AvailabilityLatSize);
			if(SBASplots->SBASNumEpochsAvailHourly==NULL) {
				*retvalue=-1;
				return;
			}
			for(i=0;i<SBASplots->AvailabilityLatSize;i++) {
				SBASplots->SBASNumEpochsAvailHourly[i]=calloc(SBASplots->AvailabilityLonSize,sizeof(int)); //Allocate memory and set it to 0
				if (SBASplots->SBASNumEpochsAvailHourly[i]==NULL) {
					*retvalue=-1;
					return;
				}
			}

			//Allocate memory for continuity risk data
			if(options->NoContRiskPlot==0) {
				SBASplots->SBASNumEpochsRiskHourly=malloc(sizeof(int*)*SBASplots->AvailabilityLatSize);
				if(SBASplots->SBASNumEpochsRiskHourly==NULL) {
					*retvalue=-1;
					return;
				}
				SBASplots->LastEpochAvailPrevCurrDiscHourly=malloc(sizeof(double*)*SBASplots->AvailabilityLatSize);
				if(SBASplots->LastEpochAvailPrevCurrDiscHourly==NULL) {
					*retvalue=-1;
					return;
				}
				SBASplots->FirstEpochAvailAfterPrevDiscHourly=malloc(sizeof(double*)*SBASplots->AvailabilityLatSize);
				if(SBASplots->FirstEpochAvailAfterPrevDiscHourly==NULL) {
					*retvalue=-1;
					return;
				}
				for(i=0;i<SBASplots->AvailabilityLatSize;i++) {
					SBASplots->SBASNumEpochsRiskHourly[i]=calloc(SBASplots->AvailabilityLonSize,sizeof(int)); //Allocate memory and set it to 0
					if (SBASplots->SBASNumEpochsRiskHourly[i]==NULL) {
						*retvalue=-1;
						return;
					}
					SBASplots->LastEpochAvailPrevCurrDiscHourly[i]=calloc(SBASplots->AvailabilityLonSize,sizeof(double)); //Allocate memory and set it to 0
					if (SBASplots->LastEpochAvailPrevCurrDiscHourly[i]==NULL) {
						*retvalue=-1;
						return;
					}
					SBASplots->FirstEpochAvailAfterPrevDiscHourly[i]=calloc(SBASplots->AvailabilityLonSize,sizeof(double)); //Allocate memory and set it to 0
					if (SBASplots->FirstEpochAvailAfterPrevDiscHourly[i]==NULL) {
						*retvalue=-1;
						return;
					}
				}
			}
		}
	}

	//Allocate memory for Iono availability counter
	SBASplots->IonoNumEpochsAvail=NULL;
	SBASplots->IonoNumEpochsAvailHourly=NULL;
	if(options->NoIonoPlot==0) {
		//SBASplots->IonoLatSize=1+(int)((options->maxLatplots-options->minLatplots)*(double)(SBASplots->IonoMemFactor)/options->IonoPlotStep);
		//SBASplots->IonoLonSize=1+(int)((options->maxLonplots-options->minLonplots)*(double)(SBASplots->IonoMemFactor)/options->IonoPlotStep);
		SBASplots->IonoLatSize=1+(int)((options->maxLatplots-options->minLatplots)*(double)(SBASplots->IonoMemFactor));
		SBASplots->IonoLonSize=1+(int)((options->maxLonplots-options->minLonplots)*(double)(SBASplots->IonoMemFactor));
		SBASplots->IonoNumEpochsAvail=malloc(sizeof(int*)*SBASplots->IonoLatSize);
		if(SBASplots->IonoNumEpochsAvail==NULL) {
			*retvalue=-1;
			return;
		}
		for(i=0;i<SBASplots->IonoLatSize;i++) {
			SBASplots->IonoNumEpochsAvail[i]=calloc(SBASplots->IonoLonSize,sizeof(int)); //Allocate memory and set it to 0
			if (SBASplots->IonoNumEpochsAvail[i]==NULL) {
				*retvalue=-1;
				return;
			}
		}

		//Repeat memory allocation for hourly maps
		if (options->SBASHourlyMaps==1)	{
			SBASplots->IonoNumEpochsAvailHourly=malloc(sizeof(int*)*SBASplots->IonoLatSize);
			if(SBASplots->IonoNumEpochsAvailHourly==NULL) {
				*retvalue=-1;
				return;
			}
			for(i=0;i<SBASplots->IonoLatSize;i++) {
				SBASplots->IonoNumEpochsAvailHourly[i]=calloc(SBASplots->IonoLonSize,sizeof(int)); //Allocate memory and set it to 0
				if (SBASplots->IonoNumEpochsAvailHourly[i]==NULL) {
					*retvalue=-1;
					return;
				}
			}
		}
	}

	*retvalue=1;
}

/*****************************************************************************
 * Name        : initUserError
 * Description : Initialise a TUserError structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TUserError *UserError           O  N/A  TUserError struct
 *****************************************************************************/
void initUserError (TUserError *UserError) {
	int i;

	for (i=0;i<NUMERRORFUNCTIONS;i++) {
		UserError->activeErrorsStart[i] = NULL;
		UserError->activeErrorsEnd[i] = NULL;
		UserError->ErrorParam[i] = NULL;
		UserError->measType[i] = NULL;
		UserError->System[i] = NULL;
		UserError->PRN[i] = NULL;
		UserError->numactiveErrors[i] = 0;
	}
	UserError->totalactiveErrors = 0;
}

/*****************************************************************************
 * Name        : initRTCM2
 * Description : Initialise a TRTCM2 structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TRTCM2 *rtcm2                   O  N/A  TRTCM2 struct
 *****************************************************************************/
void initRTCM2 (TRTCM2 *rtcm2) {
	// Initialise control variables
	rtcm2->doWeHaveHeaderCorr = 0;
	rtcm2->doWeHaveHeaderAnt = 0;
	rtcm2->antMSG3 = 0;
	rtcm2->antMSG24 = 0;
	rtcm2->firstPass = 0;
	rtcm2->firstPass2 = 0;

	// Initialise the RTCM v2.x header
	rtcm2->header.message_type = 0;
	rtcm2->header.station_id = 0;
	rtcm2->header.modi_zcount = 0.0;
	rtcm2->header.sequence_no = 0;
	rtcm2->header.dataword_no = 0;
	strcpy(rtcm2->header.station_health,"ini");

	// Initialise data read
	rtcm2->dataRead.indicator_end = 0;
	rtcm2->dataRead.offset = 0;
	strcpy(rtcm2->dataRead.ch_str,"ini");

	// Initialise variables
	rtcm2->i = 0;
	rtcm2->checkControl = 1;
	rtcm2->last2bits[0] = 0;
	rtcm2->last2bits[1] = 1;
	rtcm2->my_state = Initial;
	rtcm2->prevZcount = 0.0;
}

/*****************************************************************************
 * Name        : initRTCM3
 * Description : Initialise a TRTCM3 structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TRTCM3 *rtcm3                   O  N/A  TRTCM3 struct
 *****************************************************************************/
void initRTCM3 (TRTCM3 *rtcm3) {
	int i;

	// Initialise control variables
	rtcm3->doWeHaveHeader = 0;
	rtcm3->numObsHeaderRead = 0;
	rtcm3->doWeHaveAntennaPos = 0;
	rtcm3->doWeHaveAntennaName = 0;
	rtcm3->counter = 0;

	// Initialise the RTCM v3.x header
	rtcm3->header.message_type = 0;
	rtcm3->header.station_id = 0;
	rtcm3->header.epoch_time = 0;
	rtcm3->header.synchronous = '2';
	rtcm3->header.gps_no = 0;
	rtcm3->header.smooth_indicator = '2';
	rtcm3->header.smooth_interval = 0;

	// Initialise the RTCM v3.x message 1004
	for ( i = 0; i < 64; i++ ) {
		rtcm3->msg1004[i].satellite_id = 0;
		rtcm3->msg1004[i].l1_code_indicator = 0;
		rtcm3->msg1004[i].l1_pseudoR = 0;
		rtcm3->msg1004[i].l1_part_phaseR = 0;
		rtcm3->msg1004[i].l1_lock_indicator = 0;
		rtcm3->msg1004[i].l1_N_ambiguity = 0;
		rtcm3->msg1004[i].l1_cnr = 0;
		rtcm3->msg1004[i].l2_code_indicator = 0;
		rtcm3->msg1004[i].pseudoR_differ = 0;
		rtcm3->msg1004[i].l2Phase_l1Pseudo = 0;
		rtcm3->msg1004[i].l2_lock_indicator = 0;
		rtcm3->msg1004[i].l2_cnr = 0;
	}

	// Initialise the RTCM v3.x message 1006
	rtcm3->msg1006.message_type = 0;
	rtcm3->msg1006.station_id = 0;
	rtcm3->msg1006.gps_indicator = '2';
	rtcm3->msg1006.glonass_indicator = '2';
	rtcm3->msg1006.referStation_indicator = '2';
	rtcm3->msg1006.ecef_x = 0.0;
	rtcm3->msg1006.oscillator_indicator = '2';
	rtcm3->msg1006.ecef_y = 0.0;
	rtcm3->msg1006.ecef_z = 0.0;
	rtcm3->msg1006.antenna_height = 0.0;

	// Initialise the RTCM v3.x message 1008
	rtcm3->msg1008.message_type = 0;
	rtcm3->msg1008.station_id = 0;
	rtcm3->msg1008.descriptor_no = 0;
	strcpy(rtcm3->msg1008.descriptor,"ini");
	rtcm3->msg1008.setup_id = 0;
	rtcm3->msg1008.serialNum_no = 0;
	strcpy(rtcm3->msg1008.serialNum,"ini");

	for (i=0;i<MAX_SATELLITES_PER_GNSS;i++) {
		rtcm3->L1prevLLI[i] = -9999;
		rtcm3->L2prevLLI[i] = -9999;
	}

	strcpy(rtcm3->content_str,"ini");
	rtcm3->hour = malloc(sizeof(int));
	rtcm3->previousHour = malloc(sizeof(int));
}

/*****************************************************************************
 * Name        : initMSG1
 * Description : Initialise a TMSG1 structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TMSG1 *sc                       O  N/A  TMSG1 struct
 * int n                           I  N/A  Number of satellites
 *****************************************************************************/
void initMSG1 (TMSG1 *sc, int n) {
	int i;

	for ( i=0;i<n;i++ ) {
		sc[i].scale_factor = 0;
//		sc[i].udre_lowerlimit = 0.0;
//		sc[i].udre_upperlimit = 0.0;
		sc[i].udre = 0;
		sc[i].satellite_id = 0;
		sc[i].prc = 0;
		sc[i].rrc = 0;
		sc[i].iod = 0;
	}
}

/*****************************************************************************
 * Name        : initMSG2
 * Description : Initialise a TMSG2 structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TMSG2 *sc                       O  N/A  TMSG2 struct
 * int n                           I  N/A  Number of satellites
 *****************************************************************************/
void initMSG2 (TMSG2 *sc, int n) {
	int i;

	for (i=0;i<n;i++) {
		sc[i].scale_factor = 0;
//		sc[i].udre_lowerlimit = 0.0;
//		sc[i].udre_upperlimit = 0.0;
		sc[i].udre = 0;
		sc[i].satellite_id = 0;
		sc[i].delta_prc = 0;
		sc[i].delta_rrc = 0;
		sc[i].iod = 0;
	}
}

/*****************************************************************************
 * Name        : initMSG3
 * Description : Initialise a TMSG3 structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TMSG3 *sc                       O  N/A  TMSG3 struct
 *****************************************************************************/
void initMSG3 (TMSG3 *sc) {
	sc->x_coord = 0.0;
	sc->y_coord = 0.0;
	sc->z_coord = 0.0;
}

/*****************************************************************************
 * Name        : initMSG24
 * Description : Initialise a TMSG24 structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TMSG24 *sc                      O  N/A  TMSG24 struct
 *****************************************************************************/
void initMSG24 (TMSG24 *sc) {
	sc->x_coord = 0.0;
	sc->y_coord = 0.0;
	sc->z_coord = 0.0;
	sc->system_indicator = '2';
	sc->AH_indicator = '2';
	sc->antenna_height = 0.0;
}

/*****************************************************************************
 * Name        : changeBase
 * Description : Changes a 3D vector to the specified base
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *base                   I  N/A  Base (vectors of the base in the rows)
 * double  *vector                 IO N/A  Vector to be changed (output 
 *                                        overwrites this vector)
 *****************************************************************************/
void changeBase (double base[3][3], double vector[3]) {
	double	res[3];
	int		i,j;

	for (i=0;i<3;i++) {
		res[i] = 0;
		for (j=0;j<3;j++) {
			res[i] += base[i][j] * vector[j];
		}
	}

	memcpy (vector,res,sizeof(double)*3);
}

/*****************************************************************************
 * Name        : min
 * Description : Return the minimum between two numbers
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  a                       I  N/A  First number
 * double  b                       I  N/A  Second number 
 * Returned value (double)         O  N/A  Minimum between a and b
 *****************************************************************************/
double min (double a, double b) {
	if ( a < b ) return a;
	else return b;
}

/*****************************************************************************
 * Name        : max
 * Description : Return the maximum between two numbers
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  a                       I  N/A  First number
 * double  b                       I  N/A  Second number 
 * Returned value (double)         O  N/A  Maximum between a and b
 *****************************************************************************/
double max (double a, double b) {
	if (a<b) return b;
	else return a;
}

/*****************************************************************************
 * Name        : modulo
 * Description : Does the modulo mod of a number
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  a                       I  N/A  Number
 * double  mod                     I  N/A  Modulo base
 * Returned value (double)         O  N/A  Modulo
 *****************************************************************************/
double modulo (double a, double mod) {
	return a - ((int)(a/mod))*mod;
}

/*****************************************************************************
 * Name        : mod
 * Description : Does the modulo for an integer 
 *              (handling correctly negative numbers)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int     a                       I  N/A  Number
 * int     N                       I  N/A  Modulo base
 * Returned value (int)            O  N/A  Modulo
 *****************************************************************************/
int mod (int a, int N) {
	int r = a % N;
	return r < 0 ? r + N : r;
}

/*****************************************************************************
 * Name        : unitary
 * Description : Makes a vector unitary
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *vect                   IO N/A  3 dimension vector (output
 *                                           overwrites this vector)
 *****************************************************************************/
void unitary (double *vect) {
	double	module;

	module = sqrt(vect[0]*vect[0] + vect[1]*vect[1] + vect[2]*vect[2]);

	vect[0] /= module;
	vect[1] /= module;
	vect[2] /= module;
}

/*****************************************************************************
 * Name        : vectProd
 * Description : Makes the vectorial product between two vectors
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *a                      I  N/A  First vector
 * double  *b                      I  N/A  Second vector
 * double  *res                    O  N/A  Result vector [res = a x b]
 *****************************************************************************/
void vectProd (double *a, double *b, double *res) {
	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}

/*****************************************************************************
 * Name        : scalarProd
 * Description : Makes the scalar product between two vectors
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  *a                      I  N/A  First vector
 * double  *b                      I  N/A  Second vector
 * Returned value (double)         O  N/A  Result vector [res = a · b]
 *****************************************************************************/
double scalarProd (double *a, double *b) {
	return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

/*****************************************************************************
 * Name        : trim
 * Description : Trim a string (remove preceding and succeding spaces)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *line                     IO N/A  String to trim
 * Returned value (char*)          O  N/A  Pointer to *line
 *****************************************************************************/
char *trim (char *line) {
	int i;
	int pos=0;
	int lastnotspace=0;
	int state=0;
		// 0 -> Trimming first spaces
		// 1 -> Waiting to end string

	for (i=0;i<strlen(line);i++){
		if (state==0) {
			if (line[i]!=' ') {
				state = 1;
				line[pos] = line[i];
				pos++;
				lastnotspace = pos;
			}
		} else if (state==1) {
			line[pos] = line[i];
			pos++;
			if (line[i]!=' ' && line[i]!='\n') {
				lastnotspace = pos;
			}
		}
	}
	line[lastnotspace]='\0';
	return &line[0];
}

/*****************************************************************************
 * Name        : getstr
 * Description : Get a substring from a string and trim it
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *out                      O  N/A  Substring
 * char  *line                     I  N/A  Input string
 * int  ini                        I  N/A  Initial character position
 * int  length                     I  N/A  Length of the substring
 * Returned value (char*)          O  N/A  Pointer to *out
 *****************************************************************************/
char *getstr (char *out,char *line,int ini, int length) {
	int end;

	end = strlen(line);
	if (ini>=end) {
		out[0]='\0';
		return &out[0];
	}
	strncpy(out,&line[ini],length);
	out[length]='\0';
	trim(out);
	return &out[0];
}

/*****************************************************************************
 * Name        : getnumericalelements
 * Description : Gets the different numbers in a string separated with spaces
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *line                     I  N/A  Input string
 * int  *numelements               O  N/A  Number of elements in the string
 * double  *out                    O  N/A  Output vector
 *****************************************************************************/
void getnumericalelements (char *line, int *numelements, double *datavector) {
	int i,j,end, counter;
	int numberstarted; //0-> not reading number (spaces) 1->reading number byte per byte
	char aux[100];

	//Initialize variables
	j = 0;
	numberstarted = 0;
	counter = 0;
	end = strlen(line);

	//Intialize output vector
		
	for (i=0;i<end;i++){
		if (line[i]!=' ' && line[i]!='\n' && line[i]!=13) {
			if (numberstarted == 0) {
				numberstarted = 1;
			}	
			aux[j] = line[i];
			j++;
		} else if (numberstarted == 1) {
			aux[j] = '\0';
			counter++;
			datavector[counter-1] = atof(aux);
			j=0;
			numberstarted = 0;
		}
	}

	*numelements = counter;
}

/*****************************************************************************
 * Name        : checkConstellationChar
 * Description : Check the given character corresponds to the character of
 *                 a GNSS system
 * Parameters  :
 * Name                            |Da|Unit|Description
 * char c                           I  N/A  Character to be checked for a constellation
 * Returned value (int)             O  N/A  0-> Not a valid constellation letter
 *                                          1-> Valid constellation letter
 *****************************************************************************/
int checkConstellationChar(char c) {
	if (c!='G' && c!='E' && c!='R' && c!='S' && c!='C' && c!='J' && c!='I') return 0;
	else return 1;
}

/*****************************************************************************
 * Name        : whatIs
 * Description : Check whether an observation is carrier phase, pseudorange, 
 *               SNR or doppler
 * Parameters  :
 * Name                            |Da|Unit|Description
 * MeasurementType  meas            I  N/A  Measurement type (C1P, P1P...)
 * Returned value (MeasurementKind) O  N/A  Measurement kind (Pseudorange, CarrierPhase...)
 *****************************************************************************/
enum MeasurementKind whatIs (enum MeasurementType meas) {

	if (meas == NA) return UNKNOWN_MEAS;
	else if (meas>=ENDMEAS) {
		// Combination
		if (meas == LW || meas == LI || meas == LC || meas == G1C || meas == G1P || meas == G2C || meas == G2P || meas == DF || meas == BW) return CarrierPhase;
		else if (meas == PW || meas == PI || meas == PC || meas == PCC) return Pseudorange;
		else return UNKNOWN_MEAS;
	} else if (((meas-1)%4)==0) return Pseudorange;
	else if (((meas-2)%4)==0) return CarrierPhase;
	else if (((meas-3)%4)==0) return Doppler;
	else if (((meas)%4)==0) return SNR;
	else return UNKNOWN_MEAS;
}

/*****************************************************************************
 * Name        : getLambda
 * Description : Get the lambda corresponding to the GNSS and measurement
 * Parameters  :
 * Name                           |Da|Unit|Description
 * GNSSystem  GNSS                 I  N/A  GNSS system
 * MeasurementType  meas           I  N/A  Measurement type
 * Returned value (double)         O  m    Lambda on the measurement
 *****************************************************************************/
double getLambda (enum GNSSystem GNSS, enum MeasurementType meas) {
	if (GNSS == GPS) {
		if (meas <= S1N) return GPSl1;
		else if (meas <= S2N) return GPSl2;
		else if (meas <= S5X) return GPSl5;
	} else if (GNSS == Galileo) {
		if (meas <= S1N) return GALl1;
		else if (meas > S2N && meas <= S5X) return GALl5a;
		else if (meas <= S7X) return GALl5b;
		else if (meas <= S8X) return GALl5;
		else if (meas <= S6Z) return GALl6;
	} else if (GNSS == GLONASS) {
		return 1;
	} else if (GNSS == GEO) {
		if (meas <= S1N) return SBASl1;
		else if (meas > S2N && meas <= S5X) return SBASl5;
	}

	return 1;
}

/*****************************************************************************
 * Name        : getFrequency
 * Description : Get the frequency corresponding to the GNSS and measurement
 * Parameters  :
 * Name                           |Da|Unit|Description
 * GNSSystem  GNSS                 I  N/A  GNSS system
 * MeasurementType  meas           I  N/A  Measurement type
 * Returned value (double)         O  Hz   Frequency of the measurement
 *****************************************************************************/
double getFrequency (enum GNSSystem GNSS, enum MeasurementType meas) {
	return c0/getLambda (GNSS,meas);
}

/*****************************************************************************
 * Name        : getFrequencyInt
 * Description : Get the integer identifier value for the frequency 
 *               corresponding to the measurement
 * Parameters  :
 * Name                           |Da|Unit|Description
 * MeasurementType  meas           I  N/A  Measurement type
 * Returned value (int)            O  N/A  Frequency identifier of the measurement:
 *							GPS:		'G01' - 1 - L1
 *										'G02' - 2 - L2 
 *										'G05' - 5 - L5
 *							GLONASS:	'R01' - 1 - G1
 *										'R02' - 2 - G2
 *							Galileo:	'E01' - 1 - E1
 *										'E05' - 5 - E5a
 *										'E07' - 7 - E5b
 *										'E08' - 8 - E5 (E5a-E5b)
 *										'E06' - 6 - E56   
 *****************************************************************************/
int getFrequencyInt (enum MeasurementType meas) {
	if (meas <= S1N) return 1;
	else if (meas <= S2N) return 2;
	else if (meas <= S5X) return 5;
	else if (meas <= S7X) return 7;
	else if (meas <= S8X) return 8;
	else if (meas <= S6Z) return 6;
	else return 0;
}

/*****************************************************************************
 * Name        : measstr2meastype
 * Description : Transform from string to internal Measurement type
 * Parameters  :
 * Name                            |Da|Unit|Description
 * char  *str                       I  N/A  Measurement string
 * Returned value (MeasurementType) O  N/A  Measurement type
 *****************************************************************************/
enum MeasurementType measstr2meastype (char *str) {
	// Possible options:
	//    1st digit: C,L,D,S,P,G,B   [7]
	//    2nd digit: 1,2,5,6,7,8,W,I,C,F    [10]
	//    3rd digit: <empty>,A,B,C,D,I,L,M,N,P,Q,S,W,X,Y,Z   [16]

	static int	initialized = 0;
	static enum MeasurementType	s2t[7][10][16];
	int 		a1,a2,a3;

	if (!initialized) {
		for (a1=0;a1<7;a1++) {
			for (a2=0;a2<10;a2++) {
				for (a3=0;a3<16;a3++) {
					s2t[a1][a2][a3] = NA;
				}
			}
		}

		// Combinations
		s2t[1][6][0] = LW;
		s2t[4][6][0] = PW;
		s2t[6][6][0] = BW;
		s2t[1][7][0] = LI;
		s2t[4][7][0] = PI;
		s2t[1][8][0] = LC;
		s2t[4][8][0] = PC;
		s2t[4][8][3] = PCC;
		s2t[5][0][3] = G1C;
		s2t[5][0][9] = G1P;
		s2t[5][1][3] = G2C;
		s2t[5][1][9] = G2P;
		s2t[2][9][0] = DF;
		
		////// Automatically generated code block /////
		// RINEX 3.00
		s2t[0][0][1] = C1A; s2t[1][0][1] = L1A; s2t[2][0][1] = D1A; s2t[3][0][1] = S1A; s2t[0][0][2] = C1B; s2t[1][0][2] = L1B; s2t[2][0][2] = D1B; s2t[3][0][2] = S1B; s2t[0][0][3] = C1C; s2t[1][0][3] = L1C; s2t[2][0][3] = D1C; s2t[3][0][3] = S1C; s2t[0][0][9] = C1P; s2t[1][0][9] = L1P; s2t[2][0][9] = D1P; s2t[3][0][9] = S1P; s2t[0][0][12] = C1W; s2t[1][0][12] = L1W; s2t[2][0][12] = D1W; s2t[3][0][12] = S1W; s2t[0][0][13] = C1X; s2t[1][0][13] = L1X; s2t[2][0][13] = D1X; s2t[3][0][13] = S1X; s2t[0][0][14] = C1Y; s2t[1][0][14] = L1Y; s2t[2][0][14] = D1Y; s2t[3][0][14] = S1Y; s2t[0][0][15] = C1Z; s2t[1][0][15] = L1Z; s2t[2][0][15] = D1Z; s2t[3][0][15] = S1Z; s2t[0][0][7] = C1M; s2t[1][0][7] = L1M; s2t[2][0][7] = D1M; s2t[3][0][7] = S1M; s2t[1][0][8] = L1N; s2t[2][0][8] = D1N; s2t[3][0][8] = S1N;
		s2t[0][1][3] = C2C; s2t[1][1][3] = L2C; s2t[2][1][3] = D2C; s2t[3][1][3] = S2C; s2t[0][1][4] = C2D; s2t[1][1][4] = L2D; s2t[2][1][4] = D2D; s2t[3][1][4] = S2D; s2t[0][1][11] = C2S; s2t[1][1][11] = L2S; s2t[2][1][11] = D2S; s2t[3][1][11] = S2S; s2t[0][1][6] = C2L; s2t[1][1][6] = L2L; s2t[2][1][6] = D2L; s2t[3][1][6] = S2L; s2t[0][1][13] = C2X; s2t[1][1][13] = L2X; s2t[2][1][13] = D2X; s2t[3][1][13] = S2X; s2t[0][1][9] = C2P; s2t[1][1][9] = L2P; s2t[2][1][9] = D2P; s2t[3][1][9] = S2P; s2t[0][1][12] = C2W; s2t[1][1][12] = L2W; s2t[2][1][12] = D2W; s2t[3][1][12] = S2W; s2t[0][1][14] = C2Y; s2t[1][1][14] = L2Y; s2t[2][1][14] = D2Y; s2t[3][1][14] = S2Y; s2t[0][1][7] = C2M; s2t[1][1][7] = L2M; s2t[2][1][7] = D2M; s2t[3][1][7] = S2M; s2t[1][1][8] = L2N; s2t[2][1][8] = D2N; s2t[3][1][8] = S2N;
		s2t[0][2][5] = C5I; s2t[1][2][5] = L5I; s2t[2][2][5] = D5I; s2t[3][2][5] = S5I; s2t[0][2][10] = C5Q; s2t[1][2][10] = L5Q; s2t[2][2][10] = D5Q; s2t[3][2][10] = S5Q; s2t[0][2][13] = C5X; s2t[1][2][13] = L5X; s2t[2][2][13] = D5X; s2t[3][2][13] = S5X;
		s2t[0][4][5] = C7I; s2t[1][4][5] = L7I; s2t[2][4][5] = D7I; s2t[3][4][5] = S7I; s2t[0][4][10] = C7Q; s2t[1][4][10] = L7Q; s2t[2][4][10] = D7Q; s2t[3][4][10] = S7Q; s2t[0][4][13] = C7X; s2t[1][4][13] = L7X; s2t[2][4][13] = D7X; s2t[3][4][13] = S7X;
		s2t[0][5][5] = C8I; s2t[1][5][5] = L8I; s2t[2][5][5] = D8I; s2t[3][5][5] = S8I; s2t[0][5][10] = C8Q; s2t[1][5][10] = L8Q; s2t[2][5][10] = D8Q; s2t[3][5][10] = S8Q; s2t[0][5][13] = C8X; s2t[1][5][13] = L8X; s2t[2][5][13] = D8X; s2t[3][5][13] = S8X;
		s2t[0][3][1] = C6A; s2t[1][3][1] = L6A; s2t[2][3][1] = D6A; s2t[3][3][1] = S6A; s2t[0][3][2] = C6B; s2t[1][3][2] = L6B; s2t[2][3][2] = D6B; s2t[3][3][2] = S6B; s2t[0][3][3] = C6C; s2t[1][3][3] = L6C; s2t[2][3][3] = D6C; s2t[3][3][3] = S6C; s2t[0][3][13] = C6X; s2t[1][3][13] = L6X; s2t[2][3][13] = D6X; s2t[3][3][13] = S6X; s2t[0][3][15] = C6Z; s2t[1][3][15] = L6Z; s2t[2][3][15] = D6Z; s2t[3][3][15] = S6Z;
		////// End of automatically generated code block /////

		// RINEX 2.11
		s2t[0][0][0] = C1C; // C1
		s2t[4][0][0] = C1P; // P1
		s2t[1][0][0] = L1P; // L1
		s2t[2][0][0] = D1P; // D1
		s2t[3][0][0] = S1P; // S1
		
		s2t[0][1][0] = C2C;	// C2
		s2t[4][1][0] = C2P; // P2
		s2t[1][1][0] = L2P;	// L2
		s2t[2][1][0] = D2P;	// D2
		s2t[3][1][0] = S2P; // S2
		
		s2t[0][2][0] = C5X; // C5
		s2t[1][2][0] = L5X; // L5
		s2t[2][2][0] = D5X; // D5
		s2t[3][2][0] = S5X; // S5
		
		s2t[0][3][0] = C6X; // C6
		s2t[1][3][0] = L6X; // L6
		s2t[2][3][0] = D6X; // D6
		s2t[3][3][0] = S6X; // S6
		
		s2t[0][4][0] = C7X; // C7
		s2t[1][4][0] = L7X; // L7
		s2t[2][4][0] = D7X; // D7
		s2t[3][4][0] = S7X; // S7
		
		s2t[0][5][0] = C8X; // C8
		s2t[1][5][0] = L8X; // L8
		s2t[2][5][0] = D8X; // D8
		s2t[3][5][0] = S8X; // S8

		initialized = 1;
	}

	if (str[0]=='C') a1=0;
	else if (str[0]=='L') a1=1;
	else if (str[0]=='D') a1=2;
	else if (str[0]=='S') a1=3;
	else if (str[0]=='P') a1=4;
	else if (str[0]=='G') a1=5;
	else if (str[0]=='B') a1=6;
	else return NA;

	if (str[1]=='1') a2=0;
	else if (str[1]=='2') a2=1;
	else if (str[1]=='5') a2=2;
	else if (str[1]=='6') a2=3;
	else if (str[1]=='7') a2=4;
	else if (str[1]=='8') a2=5;
	else if (str[1]=='W') a2=6;
	else if (str[1]=='I') a2=7;
	else if (str[1]=='C') a2=8;
	else if (str[1]=='F') a2=9;
	else return NA;

	if (str[2]=='\0') a3=0;
	else if (str[2]=='A') a3=1;
	else if (str[2]=='B') a3=2;
	else if (str[2]=='C') a3=3;
	else if (str[2]=='D') a3=4;
	else if (str[2]=='I') a3=5;
	else if (str[2]=='L') a3=6;
	else if (str[2]=='M') a3=7;
	else if (str[2]=='N') a3=8;
	else if (str[2]=='P') a3=9;
	else if (str[2]=='Q') a3=10;
	else if (str[2]=='S') a3=11;
	else if (str[2]=='W') a3=12;
	else if (str[2]=='X') a3=13;
	else if (str[2]=='Y') a3=14;
	else if (str[2]=='Z') a3=15;
	else return NA;
	
	if (strncmp(str,"L1C",3)==0 && ReadL1CAsItself==0) {return s2t[1][0][0];} //Trick to make gLAB believe L1C is L1P 
	return s2t[a1][a2][a3];
}

/*****************************************************************************
 * Name        : meastype2measstr
 * Description : Transform from internal Measurement type to string
 * Parameters  :
 * Name                           |Da|Unit|Description
 * MeasurementType  meas           I  N/A  Measurement type
 * Returned value (char*)          O  N/A  Measurement string
 *****************************************************************************/
char *meastype2measstr (enum MeasurementType meas) {
	static char str[10];
	static int	initialized = 0;
	static char	l[34];
	char		type;
	int			aux;
	
	strcpy(str,"NAN");

	if (!initialized) {
		initialized = 1;
		l[0]='A'; l[1]='B'; l[2]='C'; l[3]='P'; l[4]='W'; l[5]='X'; l[6]='Y'; l[7]='Z'; l[8]='M'; l[9]='N';
		l[10]='C'; l[11]='D'; l[12]='S'; l[13]='L'; l[14]='X'; l[15]='P'; l[16]='W'; l[17]='Y'; l[18]='M'; l[19]='N';
		l[20]='I'; l[21]='Q'; l[22]='X'; l[23]='I'; l[24]='Q'; l[25]='X'; l[26]='I'; l[27]='Q'; l[28]='X'; l[29]='A';
		l[30]='B'; l[31]='C'; l[32]='X'; l[33]='Z';
	}

	if (meas<ENDMEAS) {
		switch (whatIs(meas)) {
			case Pseudorange:
				type='C';
				break;
			case CarrierPhase:
				type='L';
				break;
			case Doppler:
				type='D';
				break;
			case SNR:
				type='S';
				break;
			default:
				return str;
				break;
		}
		aux = getFrequencyInt(meas);
		sprintf(str,"%1c%1d%1c",type,aux,l[(int)((meas-1)/4)]);
	} else {
		switch (meas) {
			case 138:
				strcpy(str,"LW");
				break;
			case 139:
				strcpy(str,"BW");
				break;
			case 140:
				strcpy(str,"PW");
				break;
			case 141:
				strcpy(str,"LI");
				break;
			case 142:
				strcpy(str,"PI");
				break;
			case 143:
				strcpy(str,"LC");
				break;
			case 144:
				strcpy(str,"PC");
				break;
			case 145:
				strcpy(str,"PCC");
				break;
			case 146:
				strcpy(str,"G1C");
				break;
			case 147:
				strcpy(str,"G1P");
				break;
			case 148:
				strcpy(str,"G2C");
				break;
			case 149:
				strcpy(str,"G2P");
				break;
			case 150:
				strcpy(str,"DF");
				break;
			default:
				return str;
				break;
		}
	}

	return str;
}

/*****************************************************************************
 * Name        : gnsschar2gnsstype
 * Description : Transform from string to internal GNSS System type
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *system                   I  N/A  GNSS System string
 * Returned value (GNSSystem)      O  N/A  GNSSystem type
 *****************************************************************************/
enum GNSSystem gnsschar2gnsstype (char system) {
	if (system=='G' || system==' ') return GPS;
	else if (system=='E') return Galileo;
	else if (system=='R') return GLONASS;
	else if (system=='S') return GEO;
	else if (system=='C') return BDS;
	else if (system=='J') return QZSS;
	else if (system=='I') return IRNSS;

	return GPS; // Default value
}

/*****************************************************************************
 * Name        : gnsstype2gnssstr
 * Description : Transform from internal GNSS System type to string
 * Parameters  :
 * Name                           |Da|Unit|Description
 * GNSSystem  GNSS                 I  N/A  GNSSystem type
 * Returned value (char*)          O  N/A  GNSS System string
 *****************************************************************************/
char *gnsstype2gnssstr (enum GNSSystem GNSS) {
	static char str[10];

	strcpy(str,"NAN");

	switch (GNSS) {
		case GPS:
			strcpy(str,"GPS");
			break;
		case Galileo:
			strcpy(str,"GAL");
			break;
		case GLONASS:
			strcpy(str,"GLO");
			break;
		case GEO:
			strcpy(str,"GEO");
			break;
		case BDS:
			strcpy(str,"BDS");
			break;
		case QZSS:
			strcpy(str,"QZS");
			break;
		case IRNSS:
			strcpy(str,"IRN");
			break;
		default:
			strcpy(str,"NAN");
	}

	return str;
}

/*****************************************************************************
 * Name        : gnsstype2char
 * Description : Transform from internal GNSS System type to char
 * Parameters  :
 * Name                           |Da|Unit|Description
 * GNSSystem  GNSS                 I  N/A  GNSSystem type
 * Returned value (char)           O  N/A  GNSS System char
 *****************************************************************************/
char gnsstype2char (enum GNSSystem GNSS) {
	
	switch (GNSS) {
		case GPS:
			return 'G';
			break;
		case Galileo:
			return 'E';
			break;
		case GLONASS:
			return 'R';
			break;
		case GEO:
			return 'S';
			break;
		case BDS:
			return 'C';
			break;
		case QZSS:
			return 'J';
			break;
		case IRNSS:
			return 'I';
			break;
		default:
			return 'N';
	}

	return 'N';
}

/*****************************************************************************
 * Name        : satblockstr2satblock
 * Description : Transform from a satellite block string to the internal 
 *               satellite block
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *str                      I  N/A  Satellite block string
 * Returned value (SatelliteBlock) O  N/A  Internal satellite block
 *****************************************************************************/
enum SatelliteBlock satblockstr2satblock (char *str) {
	if (strcmp(str,"BLOCK I")==0) {
		return GPS_BLOCK_I;
	} else if (strcmp(str,"BLOCK II")==0) {
		return GPS_BLOCK_II;
	} else if (strcmp(str,"BLOCK IIA")==0) {
		return GPS_BLOCK_IIA;
	} else if (strcmp(str,"BLOCK IIR")==0) {
		return GPS_BLOCK_IIR;
	} else if (strcmp(str,"BLOCK IIR-A")==0) {
		return GPS_BLOCK_IIR;
	} else if (strcmp(str,"BLOCK IIR-B")==0) {
		return GPS_BLOCK_IIR;
	} else if (strcmp(str,"BLOCK IIR-M")==0) {
		return GPS_BLOCK_IIRM;
	} else if (strcmp(str,"GLONASS")==0) {
		return GLONASS_BLOCK;
	} else if (strcmp(str,"GLONASS-M")==0) {
		return GLONASS_BLOCK_M;
	}
	
	return UNKNOWN_BLOCK;
}

/*****************************************************************************
 * Name        : satblockstr2satblock
 * Description : Transform from an internal satellite block to a satellite  
 *               block string
 * Parameters  :
 * Name                           |Da|Unit|Description
 * SatelliteBlock  satBlock        I  N/A  Internal satellite block
 * Returned value (char *)         O  N/A  Satellite block string
 *****************************************************************************/
char *satblock2satblockstr (enum SatelliteBlock satBlock) {
	static char str[20];

	strcpy(str,"NAN");

	switch (satBlock) {
		case GPS_BLOCK_I:
			strcpy(str,"BLOCK I");
			break;
		case GPS_BLOCK_II:
			strcpy(str,"BLOCK II");
			break;
		case GPS_BLOCK_IIA:
			strcpy(str,"BLOCK IIA");
			break;
		case GPS_BLOCK_IIR:
			strcpy(str,"BLOCK IIR");
			break;
		case GPS_BLOCK_IIRM:
			strcpy(str,"BLOCK IIR-M");
			break;
		case GLONASS_BLOCK:
			strcpy(str,"GLONASS");
			break;
		case GLONASS_BLOCK_M:
			strcpy(str,"GLONASS-M");
			break;
		default:
			strcpy(str,"NAN");
	}

	return str;
}

/*****************************************************************************
 * Name        : timecorrstr2timecorrtype
 * Description : Transform from string to internal TimeSystemCorrection
 * Parameters  :
 * Name                                   |Da|Unit|Description
 * char  *str                              I  N/A  TimeSystemCorrection string
 * Returned value (TimeSystemCorrection)   O  N/A  TimeSystemCorrection type
 *****************************************************************************/
enum TimeSystemCorrection timecorrstr2timecorrtype (char *str) {
	if (strcmp(str,"GAUT")==0) {
				return GAUT;
		} else if (strcmp(str,"GPUT")==0) {
				return GPUT;
		} else if (strcmp(str,"SBUT")==0) {
				return SBUT;
		} else if (strcmp(str,"GLUT")==0) {
				return GLUT;
		} else if (strcmp(str,"GPGA")==0) {
				return GPGA;
		} else if (strcmp(str,"GLGP")==0) {
				return GLGP;
		} else if (strcmp(str,"QZGP")==0) {
				return QZGP;
		} else if (strcmp(str,"QZUT")==0) {
				return QZUT;
		} else if (strcmp(str,"BDUT")==0) {
				return BDUT;
		} else if (strcmp(str,"IRUT")==0) {
				return IRUT;
		} else if (strcmp(str,"IRGP")==0) {
				return IRGP;
		}

		return UNKNOWN_TIME_CORR;
}

/*****************************************************************************
 * Name        : timecorrtype2timecorrstr
 * Description : Transform from internal TimeSystemCorrection type to string
 * Parameters  :
 * Name                                 |Da|Unit|Description
 * enum TimeSystemCorrection timecorr    I  N/A  TimeSystemCorrection type
 * Returned value (char*)                O  N/A  TimeSystemCorrection string
 *****************************************************************************/
char *timecorrtype2timecorrstr (enum TimeSystemCorrection timecorr) {
	static char str[5];

	strcpy(str,"NAN");

	switch (timecorr) {
			case GAUT:
					strcpy(str,"GAUT");
					break;
			case GPUT:
					strcpy(str,"GPUT");
					break;
			case SBUT:
					strcpy(str,"SBUT");
					break;
			case GLUT:
					strcpy(str,"GLUT");
					break;
			case GPGA:
					strcpy(str,"GPGA");
					break;
			case GLGP:
					strcpy(str,"GLGP");
					break;
			case QZGP:
					strcpy(str,"QZGP");
					break;
			case QZUT:
					strcpy(str,"QZUT");
					break;
			case BDUT:
					strcpy(str,"BDUT");
					break;
			case IRUT:
					strcpy(str,"IRUT");
					break;
			case IRGP:
					strcpy(str,"IRGP");
					break;
			default:
					strcpy(str,"NAN");
	}

	return str;
}

/*****************************************************************************
 * Name        : SolutionModeNum2SolutionModeChar
 * Description : Transform from internal Solution mode type to string
 * Parameters  :
 * Name                            |Da|Unit|Description
 * enum SolutionMode numsol         I  N/A  Solution mode type
 * Returned value (char*)           O  N/A  Solution mode string
 *****************************************************************************/
char *SolutionModeNum2SolutionModeChar(enum SolutionMode numsol) {

	static char str[10];

	switch (numsol) {
		case SPPMode:
			strcpy(str,"SPP");
			break;
		case PPPMode:
			strcpy(str,"PPP");
			break;
		case SBASMode:
			strcpy(str,"SBAS");
			break;
		case DGNSSMode:
			strcpy(str,"DGNSS");
			break;
		default:
			strcpy(str,"Unknown");
			break;
	}

	return str;

}

/*****************************************************************************
 * Name        : WeightModeNum2WeightModestr
 * Description : Transform from internal Weight mode type to string
 * Parameters  :
 * Name                            |Da|Unit|Description
 * enum WeightMode weightMode       I  N/A  Weight mode type
 * Returned value (char*)           O  N/A  Weight mode string
 *****************************************************************************/
char *WeightModeNum2WeightModestr(enum WeightMode weightMode) {

	static char str[50];

	switch(weightMode) {
		case FixedWeight: case SBASFixedWeight: case DGNSSFixedWeight:
			strcpy(str,"Fixed");
			break;
		case ElevationWeight: case SBASElevWeight: case DGNSSElevWeight:
			strcpy(str,"Exponential elevation");
			break;
		case Elevation2Weight: case SBASElev2Weight: case DGNSSElev2Weight:
			strcpy(str,"Inverse of sin(elevation)");
			break;
		case SNRWeight: case SBASSNRWeight: case DGNSSSNRWeight:
			strcpy(str,"SNR");
			break;
		case SNRElevWeight: case SBASSNRElevWeight: case DGNSSSNRElevWeight:
			strcpy(str,"SNR and inverse of sin(elevation)");
			break;
		case SBASOnlyWeight:
			strcpy(str,"SBAS");
			break;
		case DGNSSOnlyWeight:
			strcpy(str,"DGNSS");
			break;
		default:
			strcpy(str,"Unknown");
			break;
	}

	return str;
}

/*****************************************************************************
 * Name        : getMeasModelValue
 * Description : Get the measurement and model value of a particular satellite
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * GNSSystem  system               I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN identifier of the satellite
 * MeasurementType  measType       I  N/A  Measurement type
 * double  *measurement            O  m    Measurement
 * double  *model                  O  m    Model
 * Returned value (int)            O  N/A  Status of the function
 *                                         1 => Measurement found
 *                                         0 => Not found
 *                                        -1 => Found, but not usable
 *****************************************************************************/
int getMeasModelValue (TEpoch *epoch, enum GNSSystem system, int PRN, enum MeasurementType measType, double *measurement, double *model) {
	int		ind;
	int		i,j;
	double	rawValue;
	double	conversionFactor;
	double	align;
	double	meas1,meas2;
	double	model1,model2;
	int		res1,res2;
	int		usable = 1;

	// Check if measurement is usable
	if ( !epoch->measOrder[system].usable[measType] ) usable = 0;

	if ( measType < ENDMEAS ) { // It is a measurement and NOT a combination
		// If it is a receiver type, that does not has P1, use C1 instead
		if ( epoch->receiver.recType == rtNOP1 && measType == C1P ) { 
			measType = C1C;
		}
		
		// Obtain the stored index of the measurement (-1 if not found)
		ind = epoch->measOrder[system].meas2Ind[measType];
		
		// If the measurement is not found, and it can make equivalences between C1 and P1
		if ( ind == -1 && epoch->receiver.equivalentC1P1 ) { 
			if ( measType == C1C ) {
				measType = C1P;
				ind = epoch->measOrder[system].meas2Ind[measType];
			} else if ( measType == C1P ) {
				measType = C1C;
				ind = epoch->measOrder[system].meas2Ind[measType];
			} 
		}
		if ( ind == -1 ) return 0; // Measurement not found
	} else if ( measType == PW ) {
		res1 = getMeasModelValue(epoch,system,PRN,C1P,&meas1,&model1);
		res2 = getMeasModelValue(epoch,system,PRN,C2P,&meas2,&model2);
		if ( res1 && res2 ) {
			if ( measurement != NULL ) *measurement = (GPSmf1*meas1 + GPSmf2*meas2) / (GPSmf1 + GPSmf2);
			if ( model != NULL ) *model =  (GPSmf1*model1 + GPSmf2*model2) / (GPSmf1 + GPSmf2);
			if ( usable ) return 1;
			else return -1;
		} else {
			return 0;
		}
	} else if ( measType == LW ) {
		res1 = getMeasModelValue(epoch,system,PRN,L1P,&meas1,&model1);
		res2 = getMeasModelValue(epoch,system,PRN,L2P,&meas2,&model2);
		if ( res1 && res2 ) {
			if ( measurement != NULL ) *measurement = (GPSmf1*meas1 - GPSmf2*meas2) / (GPSmf1 - GPSmf2);
			if ( model != NULL ) *model =  (GPSmf1*model1 - GPSmf2*model2) / (GPSmf1 - GPSmf2);
			if ( usable ) return 1;
			else return -1;
		} else {
			return 0;
		}
	} else if (measType==BW) {
		res1 = getMeasModelValue(epoch,system,PRN,LW,&meas1,&model1);
		res2 = getMeasModelValue(epoch,system,PRN,PW,&meas2,&model2);
		if (res1 && res2) {
			if (measurement!=NULL) *measurement = meas1 - meas2;
			if (model!=NULL) *model =  model1 - model2;
			if (usable) return 1;
			else return -1;
		} else {
			return 0;
		}
	} else if (measType==PI) {
		res1 = getMeasModelValue(epoch,system,PRN,C2P,&meas1,&model1);
		res2 = getMeasModelValue(epoch,system,PRN,C1P,&meas2,&model2);
		if (res1 && res2) {
			if (measurement!=NULL) *measurement = meas1 - meas2;
			if (model!=NULL) *model =  model1 - model2;
			if (usable) return 1;
			else return -1;
		} else {
			return 0;
		}
	} else if (measType==LI) {
		res1 = getMeasModelValue(epoch,system,PRN,L1P,&meas1,&model1);
		res2 = getMeasModelValue(epoch,system,PRN,L2P,&meas2,&model2);
		if (res1 && res2) {
			if (measurement!=NULL) *measurement = meas1 - meas2;
			if (model!=NULL) *model =  model1 - model2;
			if (usable) return 1;
			else return -1;
		} else {
			return 0;
		}
	} else if (measType==DF) {
		res1 = getMeasModelValue(epoch,system,PRN,L1P,&meas1,&model1);
		res2 = getMeasModelValue(epoch,system,PRN,L2P,&meas2,&model2);
		if (res1 && res2) {
			if (measurement!=NULL) *measurement = meas1 + 2.0 * ALPHAGPS12 * ( meas1 - meas2 );
			if (model!=NULL) *model =  model1 + 2.0 * ALPHAGPS12 * ( model1 - model2 );
			if (usable) return 1;
			else return -1;
		} else {
			return 0;
		}
	} else if (measType==PC) {
		res1 = getMeasModelValue(epoch,system,PRN,C1P,&meas1,&model1);
		res2 = getMeasModelValue(epoch,system,PRN,C2P,&meas2,&model2);
		if (res1 && res2) {
			if (measurement!=NULL) *measurement = (GPSmf1*GPSmf1*meas1 - GPSmf2*GPSmf2*meas2) / (GPSmf1*GPSmf1 - GPSmf2*GPSmf2);
			if (model!=NULL) *model =  (GPSmf1*GPSmf1*model1 - GPSmf2*GPSmf2*model2) / (GPSmf1*GPSmf1 - GPSmf2*GPSmf2);
			if (usable) return 1;
			else return -1;
		} else {
			return 0;
		}
	} else if (measType==PCC) {
		res1 = getMeasModelValue(epoch,system,PRN,C1C,&meas1,&model1);
		res2 = getMeasModelValue(epoch,system,PRN,C2P,&meas2,&model2);
		if (res1 && res2) {
			if (measurement!=NULL) *measurement = (GPSmf1*GPSmf1*meas1 - GPSmf2*GPSmf2*meas2) / (GPSmf1*GPSmf1 - GPSmf2*GPSmf2);
			if (model!=NULL) *model =  (GPSmf1*GPSmf1*model1 - GPSmf2*GPSmf2*model2) / (GPSmf1*GPSmf1 - GPSmf2*GPSmf2);
			if (usable) return 1;
			else return -1;
		} else {
			return 0;
		}
	} else if (measType==LC) {
		res1 = getMeasModelValue(epoch,system,PRN,L1P,&meas1,&model1);
		res2 = getMeasModelValue(epoch,system,PRN,L2P,&meas2,&model2);
		if (res1 && res2) {
			if (measurement!=NULL) *measurement = (GPSmf1*GPSmf1*meas1 - GPSmf2*GPSmf2*meas2) / (GPSmf1*GPSmf1 - GPSmf2*GPSmf2);
			if (model!=NULL) *model =  (GPSmf1*GPSmf1*model1 - GPSmf2*GPSmf2*model2) / (GPSmf1*GPSmf1 - GPSmf2*GPSmf2);
			if (usable) return 1;
			else return -1;
		} else {
			return 0;
		}
	} else if (measType==G1C) {
		res1 = getMeasModelValue(epoch,system,PRN,C1C,&meas1,&model1);
		res2 = getMeasModelValue(epoch,system,PRN,L1P,&meas2,&model2);
		if (res1 && res2) {
			if (measurement!=NULL) *measurement = (meas1 + meas2) / 2.0;
			if (model!=NULL) *model =  (model1 + model2) / 2.0;
			if (usable) return 1;
			else return -1;
		} else {
			return 0;
		}
	} else if (measType==G1P) {
		res1 = getMeasModelValue(epoch,system,PRN,C1P,&meas1,&model1);
		res2 = getMeasModelValue(epoch,system,PRN,L1P,&meas2,&model2);
		if (res1 && res2) {
			if (measurement!=NULL) *measurement = (meas1 + meas2) / 2.0;
			if (model!=NULL) *model =  (model1 + model2) / 2.0;
			if (usable) return 1;
			else return -1;
		} else {
			return 0;
		}
	} else if (measType==G2C) {
		res1 = getMeasModelValue(epoch,system,PRN,C2C,&meas1,&model1);
		res2 = getMeasModelValue(epoch,system,PRN,L2P,&meas2,&model2);
		if (res1 && res2) {
			if (measurement!=NULL) *measurement = (meas1 + meas2) / 2.0;
			if (model!=NULL) *model =  (model1 + model2) / 2.0;
			if (usable) return 1;
			else return -1;
		} else {
			return 0;
		}
	} else if (measType==G2P) {
		res1 = getMeasModelValue(epoch,system,PRN,C2P,&meas1,&model1);
		res2 = getMeasModelValue(epoch,system,PRN,L2P,&meas2,&model2);
		if (res1 && res2) {
			if (measurement!=NULL) *measurement = (meas1 + meas2) / 2.0;
			if (model!=NULL) *model =  (model1 + model2) / 2.0;
			if (usable) return 1;
			else return -1;
		} else {
			return 0;
		}
	} else {
		return 0; // Unknown measurement
	}

	// Seek satellite
	for (i=0;i<epoch->numSatellites;i++) {
		if ( epoch->sat[i].GNSS == system && epoch->sat[i].PRN == PRN ) {
			// Satellite found
			rawValue = epoch->sat[i].meas[ind].value;
			conversionFactor = epoch->measOrder[system].conversionFactor[measType];
			j = satIs(epoch,epoch->sat[i].PRN,epoch->sat[i].GNSS);
			align = epoch->cycleslip.preAlign[j][ind];
			if ( measurement != NULL ) *measurement =  (rawValue+align) * conversionFactor;
			if ( model != NULL ) *model = epoch->sat[i].meas[ind].model;
			if ( measurement != NULL && rawValue == -1 ) {
				*measurement = -1;
				return 0;
			}
			if ( usable ) return 1;
			else return -1;
		}
	}
	return 0;
}

/*****************************************************************************
 * Name        : getModelValue
 * Description : Get the model value of a particular satellite
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * GNSSystem  system               I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN identifier of the satellite
 * MeasurementType  measType       I  N/A  Measurement type
 * Returned value (double)         O  m    Model value (-1 invalid model)
 *****************************************************************************/
double getModelValue (TEpoch *epoch, enum GNSSystem system, int PRN, enum MeasurementType measType) {
	double	model;
	int		res;

	res = getMeasModelValue(epoch,system,PRN,measType,NULL,&model);

	if ( res == 1 ) {
		return model;
	} else {
		return -1;
	}
}

/*****************************************************************************
 * Name        : getMeasurementValue
 * Description : Get the model value of a particular satellite
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * GNSSystem  system               I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN identifier of the satellite
 * MeasurementType  measType       I  N/A  Measurement type
 * Returned value (double)         O  m    Measurement value  (-1 invalid measurement)
 *****************************************************************************/
double getMeasurementValue (TEpoch *epoch, enum GNSSystem system, int PRN, enum MeasurementType measType) {
	double	measurement;
	int		res;

	res = getMeasModelValue(epoch,system,PRN,measType,&measurement,NULL);

	if (res==1) {
		return measurement;
	} else {
		return -1;
	}
}

/*****************************************************************************
 * Name        : satIs
 * Description : Check if a satellite is in the satellite's dictionary
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TEpoch  *epoch                  I  N/A  TEpoch structure
 * int  PRN                        I  N/A  PRN identifier of the satellite
 * GNSSystem  system               I  N/A  GNSS system of the satellite
 * Returned value (int)            O  N/A  Status of the function
 *                                         -1  => Satellite not found
 *                                         0-N => Satellite index in
 *                                                the satellite's dictionary
 *****************************************************************************/
int satIs (TEpoch *epoch, int PRN, enum GNSSystem system) {
	int i;
	int counter = 0;

	PRN = PRN + system * MAX_SATELLITES_PER_GNSS;

	for ( i=0;i<MAX_SATELLITES_VIEWED;i++ ) {
		if ( epoch->satsviewed[i] == 0 )
			counter++;
	}
	if ( counter==MAX_SATELLITES_VIEWED )
		return -2;
	
	for ( i=0;i<MAX_SATELLITES_VIEWED;i++ ) {
		if ( epoch->satsviewed[i] == PRN ) {
			return i; // Satellite found
		} else if ( epoch->satsviewed[i] == 0 ) {
			return i; // Satellite found
		}
	}
	return -1; // Satellite not found
}

/*****************************************************************************
 * Name        : getProductsFirstEpochBRDC
 * Description : Return the first epoch TTime in a TGNSSproducts broadcast structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * Returned value (TTime)          O  N/A  Time of first observation in file
 *****************************************************************************/
TTime getProductsFirstEpochBRDC (TGNSSproducts *products){
	TTime	t;
	int		i;
	
	t.MJDN = 0;
	t.SoD = 0.;
	
	if (products->type!=BRDC) return t;
	
	// Initialise with the first transmission time of first satellite
	memcpy(&t,&products->BRDC->block[0][0].TtransTime,sizeof(TTime));
	// Get lower transmission time
	for (i=0;i<products->BRDC->numsats;i++) {
		if (tdiff(&products->BRDC->block[i][0].TtransTime,&t)<0) {
			memcpy(&t,&products->BRDC->block[i][0].TtransTime,sizeof(TTime));
		}
	}
	return t;
}

/*****************************************************************************
 * Name        : getProductsFirstEpochSP3
 * Description : Return the first epoch TTime in a TGNSSproducts SP3 structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * Returned value (TTime)          O  N/A  Time of first observation in file
 *****************************************************************************/
TTime getProductsFirstEpochSP3 (TGNSSproducts *products) {
	TTime	t;
	
	t.MJDN = 0;
	t.SoD = 0;
	
	if (products->type!=SP3) return t;
	
	return products->SP3->orbits.startTime; // Header start time
}

/*****************************************************************************
 * Name        : getProductsFirstEpoch
 * Description : Return the first epoch TTime in a TGNSSproducts structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * Returned value (TTime)          O  N/A  Time of first observation in file
 *****************************************************************************/
TTime getProductsFirstEpoch (TGNSSproducts *products) {
	if ( products->type == SP3 ) {
		return getProductsFirstEpochSP3(products);
	} else { // (products->type == BRDC)
		return getProductsFirstEpochBRDC(products);
	}
}

/*****************************************************************************
 * Name        : getProductsLastEpochBRDC
 * Description : Return the last epoch TTime in a TGNSSproducts broadcast structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * Returned value (TTime)          O  N/A  Time of last observation in file
 *****************************************************************************/
TTime getProductsLastEpochBRDC (TGNSSproducts *products) {
	TTime	t;
	int		i;
	
	t.MJDN = 0;
	t.SoD = 0;
	
	if (products->type!=BRDC) return t;
	
	// Initialise with the last toe time of first satellite
	memcpy(&t,&products->BRDC->block[0][products->BRDC->numblocks[0]-1].Ttoe,sizeof(TTime));
	// Get lower transmission time
	for (i=0;i<products->BRDC->numsats;i++) {
		if (tdiff(&products->BRDC->block[i][products->BRDC->numblocks[i]-1].Ttoe,&t)>0) {
			memcpy(&t,&products->BRDC->block[i][products->BRDC->numblocks[i]-1].Ttoe,sizeof(TTime));
		}
	}
	// Broadcast can be valid for longer periods (up to 2 hours later from Toe)
	t = tdadd(&t,7200);
	return t;
}

/*****************************************************************************
 * Name        : getProductsLastEpochSP3
 * Description : Return the last epoch TTime in a TGNSSproducts SP3 structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * Returned value (TTime)          O  N/A  Time of last observation in file
 *****************************************************************************/
TTime getProductsLastEpochSP3 (TGNSSproducts *products) {
	TTime	t;
	
	t.MJDN = 0;
	t.SoD = 0;
	
	if (products->type!=SP3) return t;

	//return products->SP3->orbits.block[0][products->SP3->orbits.numRecords - 1].t;
	return products->SP3->orbits.endTime;
}

/*****************************************************************************
 * Name        : getProductsLastEpoch
 * Description : Return the last epoch TTime in a TGNSSproducts structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 * Returned value (TTime)          O  N/A  Time of last observation in file
 *****************************************************************************/
TTime getProductsLastEpoch (TGNSSproducts *products) {
	if ( products->type == SP3 ) {
		return getProductsLastEpochSP3(products);
	} else { // (products->type == BRDC)
		return getProductsLastEpochBRDC(products);
	}
}

/*****************************************************************************
 * Name        : selectBRDCBlock
 * Description : Select the BRDC block with the following conditions
 *                  - Transmission time equal or lower than reference time
 *                  - Closest toe to reference time
 *                  - If SBAS IOD is not -1, select the block with that IODE
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TBRDCproducts  *products        I  N/A  TBRDCproducts structure used as base to return PVT
 * TTime  *t                       I  N/A  Reference time used
 * GNSSystem  GNSS                 I  N/A  GNSS system of the satellite
 * int  PRN                        I  N/A  PRN identifier of the satellite
 * TOptions  *options              I  N/A  TOptions structure
 * int SBASIOD                     I  N/A  SBAS IOD for long term corrections                                       
 * Returned value (TBRDCblock*)    O  N/A  Pointer to the corresponding block
 *****************************************************************************/
TBRDCblock *selectBRDCblock (TBRDCproducts *products, TTime *t, enum GNSSystem GNSS, int PRN, int SBASIOD, TOptions *options) {
	int			ind,indPast;
	int			i,j;
	int			limit;
	int			check;		
	int			selected = -1,timeSelected;
	double		diff;
	double		diffTransmitted;
	double		diffToe;
	double		diffToemax; 
	double		diffLastTransmitted = 9e9;
	TTime       tGLO;
	TBRDCblock	*block;


	ind = products->index[GNSS][PRN];
	indPast = products->indexPast[GNSS][PRN];

	if (ind==-1 && indPast==-1) return NULL;

	for(j=0;j<2;j++) {
		if (indPast==-1 && j==0) continue;
		if (ind==-1 && j==1) continue;
		if(j==0) limit=products->numblocksPast[indPast];
		else limit=products->numblocks[ind];

		for (i=0;i<limit;i++) {
			check=0;
			if(j==0)  block = &products->blockPast[indPast][i];
			else block = &products->block[ind][i];
			
			if (SBASIOD!=-1 && block->IODE!=SBASIOD) {continue;}
			diffTransmitted = tdiff(t,&block->TtransTime);
			if(GNSS==GLONASS) {
				tGLO.MJDN=block->Ttoe.MJDN;
				tGLO.SoD=block->Ttoe.SoD;
				//Transform from UTC to GPS time
				tGLO.SoD-=products->AT_LS;
				if(tGLO.SoD<0) {
					tGLO.SoD+=86400.;
					tGLO.MJDN--;
				}
				diffToe = tdiff(t,&tGLO);
				//Tranmission time of message of GLONASS broadcast block is directly saved in GPS time
			} else {
				diffToe = tdiff(t,&block->Ttoe);
			}
			diffToemax = 0.5 * 3600 * block->fitInterval; // Update diffToemax

			if (options->brdcBlockTransTime==0) {
				//Do not check that transmission time of message is equal or before current time
				if (fabs(diffTransmitted)<fabs(diffLastTransmitted) && diffToe<=diffToemax && diffToe>=-diffToemax) {
					check=1;
				}
			} else {
				//Check that transmission time of message is equal or before current time
				if (diffTransmitted>=0 && diffTransmitted<diffLastTransmitted && diffToe<=diffToemax && diffToe>=-diffToemax) {
					check=1;
				}
			}
			if (check) {
	//			if (block->SVhealth==0 || options->satelliteHealth==0) {
	//				diffLastTransmitted = diffTransmitted;
	//				selected = i;
	//			}

				// Update following ESA/EPO suggestion: 
				if (options->satelliteHealth==0) {
					diffLastTransmitted = diffTransmitted;
					selected = i;
					timeSelected=j;
				} else {
					// Last Transmitted Healthy Ephemerides
					if (GNSS==Galileo && block->SVhealth==0 && block->SISASignal!=-1) { 
						diffLastTransmitted = diffTransmitted;
						selected = i;
						timeSelected=j;
					} else if (GNSS!=Galileo && block->SVhealth==0) {
						diffLastTransmitted = diffTransmitted;
						selected = i;
						timeSelected=j;
					} else {// Last transmitted unhealthy block 
						diffLastTransmitted = diffTransmitted;
						selected = -1;
					}
				}
			}
		}
	}

	if (selected==-1) return NULL;

	// Check if selected is inside the fit interval
	if(timeSelected==0) {
		block = &products->blockPast[indPast][selected];
	} else {
		block = &products->block[ind][selected];
	}
	if(GNSS==GLONASS) {
		tGLO.MJDN=block->Ttoe.MJDN;
		tGLO.SoD=block->Ttoe.SoD;
		//Transform from UTC to GPS time
		tGLO.SoD-=products->AT_LS;
		if(tGLO.SoD<0) {
			tGLO.SoD+=86400.;
			tGLO.MJDN--;
		}
		diff = tdiff(t,&tGLO);
		//Tranmission time of message of GLONASS broadcast block is directly saved in GPS time
	} else {
		diff = tdiff(t,&block->Ttoe);
	}
	diffToemax = 0.5*3600*block->fitInterval; // Update diffToemax
	if (diff<=diffToemax && diff>=-diffToemax) return block;
	else return NULL;
}

/*****************************************************************************
 * Name        : MJDN
 * Description : Get the modified julian day from YY/MM/DD
 *               MJDN starts at 17/11/1858 at 0h UTC (JD=2400000.5)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * struct tm  tm                   I  N/A  Date
 * Returned value (int)            O  N/A  Integer days in Modified Julian Date
 *****************************************************************************/
int MJDN (struct tm *tm) {
	int y,m;

	y = tm->tm_year + 1900;
	m = tm->tm_mon + 1;
	if (m<=2) {
		y--;
		m+=12;
	}

	return (int)(365.25*y) + (int)(30.6001*(m+1)) + tm->tm_mday - 679019;
}

/*****************************************************************************
 * Name        : MonthName
 * Description : Get the month name from the month number
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int month                       I  N/A  Month number (1-12)
 * char *monthname                 O  N/A  Name of the month
 *****************************************************************************/
void MonthName (int month, char *monthname) {
	static char monthnames[12][10]={"January","February","March","April","May","June","July","August","September","October","November","December"};
	
	strcpy(monthname,monthnames[month-1]);
}



/*****************************************************************************
 * Name        : t2tm
 * Description : Get the calendar time from a TTime structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  TTime structure
 * tm  *tm                         O  N/A  tm structure
 * double  *seconds                O  N/A  Seconds of minute in double format
 *****************************************************************************/
void t2tm (TTime *t, struct tm *tm, double *seconds) {
	int		year;
	double	doy;
	time_t	tt;
	
	t2doy(t,&year,&doy);
	tm->tm_year = year - 1900;
	tm->tm_mday = (int)(doy);
	tm->tm_mon = 0;
	tm->tm_hour = (int)(t->SoD/3600.);
	tm->tm_min = (int)(modulo(t->SoD,3600.)/60.);
	tm->tm_sec = (int)(modulo(t->SoD,60.));
	tm->tm_isdst = -1;
	*seconds =  modulo(t->SoD,60.);
	tt = mktime(tm);
	//localtime_r(&tt,tm);
	memcpy(tm,localtime(&tt),sizeof(time_t));
}

/*****************************************************************************
 * Name        : t2tmnolocal
 * Description : Get the calendar time from a TTime structure without using
 *                localtime function
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  TTime structure
 * tm  *tm                         O  N/A  tm structure
 * double  *seconds                O  N/A  Seconds of minute in double format
 *****************************************************************************/
void t2tmnolocal (TTime *t, struct tm *tm, double *seconds) {
	int             year;
	int             day_of_month;
	int             month_days;
	int             month_number;
	double          doy;

	t2doy(t,&year,&doy);

	tday_of_month(t,&day_of_month, &month_days, &month_number);

	//IMPORTANT NOTE!! Read man page ctime ('man ctime') to understand how the system tm structure is defined
	tm->tm_year = year - 1900;	// The number of years since 1900.
	tm->tm_mday = day_of_month;	// The day of the month, in the range 1 to 31.
	tm->tm_yday = (int)doy -1; 	// The number of days since January 1, in the range 0 to 365
	tm->tm_mon = month_number-1;	// The number of months since January, in the range 0 to 11.
	tm->tm_hour = (int)(t->SoD/3600.); // The number of hours past midnight, in the range 0 to 23.
	tm->tm_min = (int)(modulo(t->SoD,3600.)/60.); // The number of minutes after the hour, in the range 0 to 59.
	tm->tm_sec = (int)(modulo(t->SoD,60.)); // The number of seconds after the minute, normally in the range 0 to 59, but can be up to 60 to allow for leap seconds.
	tm->tm_isdst = -1;	// A  flag that indicates whether daylight saving time is in effect at the time described.  The value is positive if
				//    daylight saving time is in effect, zero if it is not, and negative if the information is not available.
	*seconds =  modulo(t->SoD,60);
}

/*****************************************************************************
 * Name        : t2doy
 * Description : Get the Year/doy from a TTime structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  TTime structure
 * int  *year                      O  N/A  Year
 * double  *doy                    O  N/A  Day of year
 *****************************************************************************/
void t2doy (TTime *t, int *year, double *doy) {
	const int 	MJD_1980 = 44239;
	int     	day;    
	int     	ref = 1980; 
	int     	day_aux;
	int     	iy;
	
	day = t->MJDN - MJD_1980;
	
	day_aux = modulo(day,1461.);
	if (day_aux>365) {
		day_aux -= 366; 
		*doy = modulo (day_aux,365.) + 1;
		iy = (int)((double)(day_aux)/365.) + 1;
	} else {
		*doy = (double)(day_aux + 1);
		iy = 0; 
	}
	*year = ref + 4*(int)((double)(day)/1461.) + iy;
	*doy += t->SoD/86400.;
}

/*****************************************************************************
 * Name        : date2doy
 * Description : Get the Year/doy from date year, month and day
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int  year                       I  y    Year (must be of 4 digits)
 * int  month                      I  m    Month
 * int  day                        I  d    Day of month
 * Return value (int)              O  d    Day of Year
 *****************************************************************************/
int date2doy (int year, int month, int day) {
	int i, doy;
	int daysmonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if ( year < 1000 ) return -1;

	if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 )
		daysmonth[2] += 1;

	doy = 0;
	for ( i=0;i<month;i++ )
		doy += daysmonth[i];
	doy += day;

	return doy;
}

/*****************************************************************************
 * Name        : doy2date
 * Description : Get the date year, month and day from Year/doy
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int  year                       I  y    Year (4 digits)
 * int  doy                        I  d    Day of Year
 * int  *month                     O  m    Month
 * int  *day                       O  d    Day of month
 *****************************************************************************/
void doy2date (int year, int doy, int *month, int *day) {
	int i = -1;
	int res;
	int daysmonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if ( doy > 366 ) return;

	if ( (( year%4 == 0 ) && ( year%100 != 0 )) || year%400 == 0 )
		daysmonth[2] += 1;

	res = doy;
	while ( res > 0 ) {
		i += 1;
		res -= daysmonth[i];
	}

	*month = i;
	*day = daysmonth[i] + res;
}

/*****************************************************************************
 * Name        : t2doystr
 * Description : Get a string with the Year/DoY/SoD from a TTime structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  TTime structure
 * Returned value (char*)          O  N/A  String with Year / Doy / SoD (length=17)
 *****************************************************************************/
char *t2doystr (TTime *t) {
	static char	str[100];
	int			year;
	double		doy;
	
	t2doy(t,&year,&doy);
	sprintf(str,"%04d %03d %8.2f",year,(int)(doy),(doy-(int)(doy))*86400.0);

	return str;
}

/*****************************************************************************
 * Name        : gpsws2ttime
 * Description : Transforms between GPSweek and Seconds of Week to TTime structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int  GPSweek                    I  N/A  GPS Week
 * double  SoW                     I  s    Seconds of week
 * Returned value (TTime)          O  N/A  TTime structure
 *****************************************************************************/
TTime gpsws2ttime (int GPSweek, double SoW) {
	TTime		t;
	int			DoW;

	// GPSweek = 0 and SoW = 0 corresponds to MJDN = 44244
	// Check if Seconds of week is negative (meaning that is from previous week)
	if(SoW<0) {
		SoW+=604800.;
		GPSweek--;
	} else if (SoW>=604800.) {
		SoW-=604800.;
		GPSweek++;
	}
	DoW = (int)(SoW/86400.0);
	t.MJDN = (int)(44244 + GPSweek * 7.0 + DoW);
	t.SoD = SoW - DoW*86400.0;

	return t;
}

/*****************************************************************************
 * Name        : yeardoy2MJDN
 * Description : Get the modified julian day from Year/DoY/SoD
 *               MJDN starts at 17/11/1858 at 0h UTC (JD=2400000.5)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int  year                       I  N/A  Year
 * int  doy                        I  N/A  Day of Year
 * double  sod                     I  s    Seconds of day
 * Returned value (double)         O  N/A  MJDN
 ****************************************************************************/
double yeardoy2MJDN (int year, int doy, int sod) {
	double tmp;

	tmp = (int)(365.25 * (year-1)) + 428 + doy;
	tmp = tmp + 1720981.5 + (double)(sod)/86400. - 2400000.5;

	return tmp;
}


/*****************************************************************************
 * Name        : ttime2gpswsnoroll
 * Description : Transforms between TTime structure to GPSweek (without rollover)
 *                and Seconds of Week 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime *t                        I  N/A  TTime structure
 * int  GPSweek                    O  N/A  GPS Week
 * double  SoW                     O  s    Seconds of week
 * Returned value                  -  N/A  -
 *****************************************************************************/
void ttime2gpswsnoroll (TTime *t, int *GPSweek, double *SoW) {
	int gpsday,weekday;

	//44244 comes from adding 2400000.5 to convert to Julian Date and then substracting 2444244.5 to get the first day of GPS time
	gpsday = t->MJDN - 44244;
	weekday = gpsday%7;

	*GPSweek = (int)(gpsday - (gpsday%7)) / 7;
	*SoW = (double)(weekday) * 86400. + t->SoD;
}

/*****************************************************************************
 * Name        : cal2t
 * Description : Transforms between Calendar time (year, month, day of month, 
 *               hour, minute and second) to TTime structure
 *               MJDN starts at 17/11/1858 at 0h UTC (JD=2400000.5)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int  year                       I  y    Year (can be of 4 or 2 digits)
 * int  month                      I  m    Month
 * int  day                        I  d    Day of month
 * int  hour                       I  h    Hours of day
 * int  minute                     I  m    Minutes in hour
 * double  second                  I  s    Seconds of minute
 * Returned value (TTime)          O  N/A  TTime structure
 *****************************************************************************/
TTime cal2t (int year, int month, int day, int hour, int minute, double second) {
	struct tm	tm;
	TTime		t;
	
	if ( year < 100 ) { // 2 digits
		if ( year <= 70 ) { // 20XX
			tm.tm_year = year + 100;
		} else { // 19XX
			tm.tm_year = year;
		}
	} else { // 4 digits
		tm.tm_year = year - 1900;
	}
	
	tm.tm_mon = month - 1;
	tm.tm_mday = day;
	tm.tm_hour = hour;
	tm.tm_min = minute;
	tm.tm_sec = (int)second;
	t.MJDN = MJDN (&tm);
	t.SoD = tm.tm_hour*3600 + tm.tm_min*60 + second;
	
	return t;
}

/*****************************************************************************
 * Name        : tday_of_month
 * Description : Compute day of month from Ttime structure
 *               
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       I  N/A  TTime structure 
 * int    *day_of_month            O  N/A  Day of the month (1..31)
 * int    *month_days              O  N/A  Number of days of the month
 * int    *month_number            O  N/A  Month number (1..12)
 * Returned value                  O  -    -
 *****************************************************************************/
void tday_of_month (TTime *t, int *day_of_month, int *month_days, int *month_number) {
	int			year;
	int			leapyear = 0;
	int			daysum = 0, prevdaysum = 0;
	double		doy;

	// The following array has the number of days for each month, for a normal year and for a leap year
	static int number_days_month[2][12]={{31,28,31,30,31,30,31,31,30,31,30,31},{31,29,31,30,31,30,31,31,30,31,30,31}};

	t2doy(t,&year,&doy);

	// Check if we are in a leap year
	if ( year%400 == 0 )		leapyear = 1;
	else if ( year%100 == 0 )	leapyear = 0;
	else if ( year%4 == 0 )		leapyear = 1;
	else						leapyear = 0;
 

	// Check for the month we are currently in 
	*month_number = 0;
	*month_days = 0;
	while ( *month_days == 0 ) {
		daysum += number_days_month[leapyear][*month_number];
		if ( (int)doy <= daysum ) {
			*month_days = number_days_month[leapyear][*month_number];
			*day_of_month = (int)doy - prevdaysum;
		}
		*month_number = *month_number + 1;
		prevdaysum = daysum;	
	}
}

/*****************************************************************************
 * Name        : getcurrentsystemtime
 * Description : Get the system time and date
 *               
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *t                       O  N/A  TTime structure 
 * tm  *tm                         O  N/A  tm structure
 * Returned value                  O  -    -
 *****************************************************************************/
void getcurrentsystemtime (struct tm *tm) {
	time_t tt;

	tt = time(NULL);
	memcpy(tm,localtime(&tt),sizeof(struct tm));
}


/*****************************************************************************
 * Name        : tdiff
 * Description : Difference between two internal time structures in seconds, 
 *               equivalent to t1-t2
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *a                       I  N/A  Time 1
 * TTime  *b                       I  N/A  Time 2
 * Returned value (double)         O  s    Seconds between t1 and t2
 *****************************************************************************/
double tdiff (TTime *a, TTime *b) {
	double aux;

	aux = ( a->MJDN - b->MJDN ) * 86400.0 + ( a->SoD - b->SoD );
	// Sanity check to avoid rounding problems
	if ( fabs(aux) < 1e-6 ) aux = 0.0;

	return aux;
}

/*****************************************************************************
 * Name        : tsec
 * Description : Return MJDN + SoD in seconds
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *a                       I  N/A  Time 1
 * Returned value (double)         O  s    Seconds of t1
 *****************************************************************************/
double tsec (TTime *a) {
	return (a->MJDN) * 86400.0 + a->SoD;
}

/*****************************************************************************
 * Name        : tdadd
 * Description : Add a double (in seconds) from a TTime structure 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime  *a                       I  N/A  Reference time
 * double  b                       I  s    Time to add
 * Returned value (TTime)          O  N/A  a+b
 *****************************************************************************/
TTime tdadd (TTime *a, double b) {
	TTime		t;
	int			MJDNdiff;

	t.MJDN = a->MJDN;
	t.SoD = a->SoD + b;

	MJDNdiff = (int)(t.SoD/86400);

	t.MJDN += MJDNdiff;
	t.SoD -= MJDNdiff*86400;

	if (t.SoD<0) {
		t.MJDN--;
		t.SoD += 86400;
	}

	return t;
}

/*****************************************************************************
 * Name        : Gal_loc_month
 * Description : Locate months around a certain day (Galileo's Matlab function)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double doy                      I  N/A  Day of year [1..365.25]
 * int *im                         O  N/A  Indexes of the month [0 .. 11]
 * double *id                      O  N/A  Days of half month [-14.5 .. 380.75]
 * Returned value (int)            O  N/A  0 -> DoY value found in dom vector
 *                                         1 -> DoY value not found in dom vector
 *****************************************************************************/
int Gal_loc_month (double doy, int *im, double *id) {

	int i;
	int dom_positions = 14;
	double dom[14] = {-14.5,15.5,45.125,74.75,105.25,135.75,166.25,196.75,227.75,258.25,288.75,319.25,349.75,380.75};
	
	// Initialize to 0. If im[1]==9999 then the value of doy was found in dom vector
	im[0] = 0;
	im[1] = 9999;
	id[0] = id[1] = 0;
 
	for(i=0;i<dom_positions;i++) {
		if(dom[i] == doy) {
			im[0] = i;
			id[0] = dom[i];
			// Need to substract 1 because the matrix index starts at 0 (in Matlab starts at 1)
			im[0]--; 
			return 0;
		} else if (dom[i] > doy) {
			im[0] = i-1;
			im[1] = i;
			id[0] = dom[im[0]];
			id[1] = dom[im[1]];
			break;
		}
	}

	// DoY value not found in dom vector
	if ( im[0] == 0 ) {
		im[0] = 12;
	} else if ( im[0] == 12 ) {
		im[1] = 1;
	}

	// Need to substract 1 because the matrix index starts at 0 (in Matlab starts at 1)
	im[0]--;
	im[1]--;

	return 1;
}

/*****************************************************************************
 * Name        : ConvertCalendarDate
 * Description : Convert calendar date to other date formats and exit 
 *                (date conversion only). Only dates after year 1980 are supported.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int year                        I  N/A  Current year
 * int month                       I  N/A  Current month number
 * int day                         I  N/A  Current day number
 * int hour                        I  N/A  Current hour
 * int minute                      I  N/A  Current minute
 * double seconds                  I  N/A  Current second
 *****************************************************************************/
void ConvertCalendarDate(int year, int month, int day, int hour, int minute, double seconds) {

	int 		GPSweek,DoW,DoY;
	double		SoD,SecondsComp;
	double 		SoW;
	TTime		t;
	struct tm	tm;

	//Fill TTime struct
	t=cal2t (year,month,day,hour,minute,seconds);
	//Fill tm struct
	t2tmnolocal(&t, &tm, &SecondsComp);
	//Get DoY
	DoY=date2doy(year,month,day);
	SoD=(double)hour*3600.+(double)minute*60+seconds;
	//Get GPSWeek
	ttime2gpswsnoroll (&t, &GPSweek, &SoW);
	DoW = (int)(SoW/86400.0);

	printDates(year,month,day,hour,minute,seconds,DoY,SoD,GPSweek,DoW,SoW,t.MJDN);

}

/*****************************************************************************
 * Name        : ConvertDoYDate
 * Description : Convert Year/DoY/SoD date to other date formats and exit 
 *                (date conversion only). Only dates after year 1980 are supported.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int year                        I  N/A  Current year
 * int doy                         I  N/A  Current day of year
 * double sod                      I  N/A  Current second of day
 *****************************************************************************/
void ConvertDoYDate(int year, int doy, double sod) {
	int 		GPSweek,DoW;
	double		SecondsComp;
	double 		SoW;
	TTime		t;
	struct tm	tm;

	//Fill TTime struct
  	t.MJDN=yeardoy2MJDN (year,doy, (int)sod);
	t.SoD=sod;
	//Fill tm struct
    t2tmnolocal(&t, &tm, &SecondsComp);
	//Get GPSWeek
	ttime2gpswsnoroll (&t, &GPSweek, &SoW);
	DoW = (int)(SoW/86400.0);

	printDates(year,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,SecondsComp,doy,sod,GPSweek,DoW,SoW,t.MJDN);
}

/*****************************************************************************
 * Name        : ConvertGPSWeekDate
 * Description : Convert GPSWeek/SoW date to other date formats and exit 
 *                (date conversion only). Only dates after year 1980 are supported.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int GPSWeek                     I  N/A  Current GPS week
 * double SoW                      I  N/A  Current second of week
 *****************************************************************************/
void ConvertGPSWeekDate(int GPSWeek, double SoW) {
	int 		DoW;
	int			year;
	double		DoY;
	double		SecondsComp;
	TTime		t;
	struct tm	tm;

	//Fill TTime struct
	t=gpsws2ttime(GPSWeek,SoW);
	//Fill tm struct
    t2tmnolocal(&t, &tm, &SecondsComp);
	//Get DoW
	DoW = (int)(SoW/86400.0);
	//Get Year/DoY
	t2doy(&t,&year,&DoY);

	printDates(year,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,SecondsComp,(int)DoY,t.SoD,GPSWeek,DoW,SoW,t.MJDN);

}

/*****************************************************************************
 * Name        : ConvertMJDNDate
 * Description : Convert MJDN/SoD date to other dateformats and exit 
 *                (date conversion only). Only dates after year 1980 are supported.
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int GPSWeek                     I  N/A  Current MJDN
 * double SoD                      I  N/A  Current second of day
 *****************************************************************************/
void ConvertMJDNDate(int MJDN, double SoD) {

	int 		GPSweek,DoW;
	int			year;
	double		SecondsComp;
	double 		SoW,DoY;
	TTime		t;
	struct tm	tm;

	//Fill TTime struct
	t.MJDN=MJDN;
	t.SoD=SoD;
	//Fill tm struct
	t2tmnolocal(&t, &tm, &SecondsComp);
	//Get DoY
	t2doy(&t,&year,&DoY);
	//Get GPSWeek
	ttime2gpswsnoroll (&t, &GPSweek, &SoW);
	DoW = (int)(SoW/86400.0);

	printDates(year,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,SecondsComp,(int)DoY,t.SoD,GPSweek,DoW,SoW,t.MJDN);

}

/*****************************************************************************
 * Name        : ConvertCartesianCoord
 * Description : Convert cartesian coordiantes to other coordinate sytems 
 *                (coordinates conversion only)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double X                        I  m    X
 * double Y                        I  m    Y
 * double Z                        I  m    Z
 *****************************************************************************/
void ConvertCartesianCoord(double x, double y, double z) {

	double 	positionXYZ[3];
	double	positionNEU[3];
	double	positionSph[3];

	positionXYZ[0]=x;
	positionXYZ[1]=y;
	positionXYZ[2]=z;

	XYZ2NEU(positionXYZ,positionNEU);
	XYZ2Spherical(positionXYZ,positionSph);

	printCoordinates(positionXYZ,positionNEU,positionSph);

}

/*****************************************************************************
 * Name        : ConvertGeodeticCoord
 * Description : Convert geodetic coordiantes to other coordinate sytems 
 *                (coordinates conversion only)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double Longitude                I  º     Longitude [-180..180]
 * double Latitude                 I  º     Latitude [-90..90]
 * double Height                   I  m     Height
 *****************************************************************************/
void ConvertGeodeticCoord(double lon, double lat, double height) {

    double  positionXYZ[3];
    double  positionNEU[3];
    double  positionSph[3];

    positionNEU[0]=lat*d2r;
    positionNEU[1]=lon*d2r;
    positionNEU[2]=height;

    NEU2XYZ(positionNEU,positionXYZ);
    XYZ2Spherical(positionXYZ,positionSph);

    printCoordinates(positionXYZ,positionNEU,positionSph);

}

/*****************************************************************************
 * Name        : ConvertSphericalCoord
 * Description : Convert Spherical coordiantes to other coordinate sytems (coordinates conversion only)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double Longitude                I  º     Longitude [-180..180]
 * double Latitude                 I  º     Latitude [-90..90]
 * double Radius                   I  m     Radius
 *****************************************************************************/
void ConvertSphericalCoord(double lon, double lat, double Radius) {

    double  positionXYZ[3];
    double  positionNEU[3];
    double  positionSph[3];

    positionSph[0]=lat*d2r;
    positionSph[1]=lon*d2r;
    positionSph[2]=Radius;

	Spherical2XYZ(positionSph,positionXYZ);
	XYZ2NEU(positionXYZ,positionNEU);

    printCoordinates(positionXYZ,positionNEU,positionSph);

}

/*****************************************************************************
 * Name        : numSteps
 * Description : Return the number of increments of da between values a2 and a1
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double  a1                      I  N/A  First value
 * double  a2                      I  N/A  Second value
 * double  da                      I  N/A  Increment between values
 * Returned value (int)            O  N/A  Number of increments
 *****************************************************************************/
int numSteps (double a1, double a2, double da) {
	if (da==0) return 1;
	if (da==-1) return 0; // Uninitialised

	return (int)((a2-a1)/da+1); // +1 is to take into account that both a1 and a2 are included in the distance
}

/*****************************************************************************
 * Name        : allocateIonoMap
 * Description : Allocate memory for ionospheric map. The following fields of
 *               the structure must be already prepared for this function:
 *                    nhgt, nlat, nlon
 *               As they will be used to allocate memory in the members:
 *                    TEC & RMS
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TIonoMap  *ionoMap              IO N/A  Ionospheric map structure
 *****************************************************************************/
void allocateIonoMap (TIonoMap *ionoMap) {
	int		totalSize;

	totalSize = ionoMap->nhgt * ionoMap->nlat * ionoMap->nlon;

	ionoMap->TEC = (double*)(realloc(ionoMap->TEC,sizeof(double)*totalSize));
	ionoMap->RMS = (double*)(realloc(ionoMap->RMS,sizeof(double)*totalSize));
}

/*****************************************************************************
 * Name        : E
 * Description : Return the value 10^exponent withouth using pow function
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int  exponent                   I  N/A  Exponent
 * Returned value (double)         O  N/A  10^exponent
 *****************************************************************************/
double E (int exponent) {
	double	value = 1;
	int		i;

	if (exponent<0) {
		for (i=0;i>exponent;i--) value /= 10;
	} else if (exponent>0) {
		for (i=0;i<exponent;i++) value *= 10;
	}

	return value;
}

/*****************************************************************************
 * Name        : conv3Dto1D
 * Description : Transforms a 3 dimensional index to a single dimension index
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int  i                          I  N/A  First dimension  
 * int  j                          I  N/A  Second dimension
 * int  k                          I  N/A  Third dimension
 * int  ni                         I  N/A  Size of first dimension
 * int  nj                         I  N/A  Size of second dimension
 * Returned value (int)            O  N/A  1D index
 *****************************************************************************/
int	conv3Dto1D (int i, int j, int k, int ni, int nj) {
	if (ni==0 || nj==0) return 0;

	return k*ni*nj + j*ni + i;
}

/*****************************************************************************
 * Name        : ionoConv3Dto1D
 * Description : Transforms a 3 dimensional index to a single dimension index
 *               obtaining the data from a TIonoMap structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TIonoMap  *ionoMap              I  N/A  Ionospheric map structure
 * int  ihgt                       I  N/A  Height index  
 * int  ilat                       I  N/A  Latitude index
 * int  ilon                       I  N/A  Longitude index
 * Returned value (int)            O  N/A  1D index
 *****************************************************************************/
int ionoConv3Dto1D (TIonoMap *ionoMap, int ihgt, int ilat, int ilon) {
	return conv3Dto1D(ihgt,ilat,ilon,ionoMap->nhgt,ionoMap->nlat);
}

/*****************************************************************************
 * Name        : ionoHLLto1D
 * Description : Gives the 1D index of the double values of hgt, lat and lon
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TIonoMap  *ionoMap              I  N/A  Ionospheric map structure
 * double  hgt                     I  km   Height value  
 * double  lat                     I  deg  Latitude value
 * double  lon                     I  deg  Longitude value
 * Returned value (int)            O  N/A  1D index
 *****************************************************************************/
int ionoHLLto1D (TIonoMap *ionoMap, double hgt, double lat, double lon) {
	int		ilat, ilon, ihgt;

	if (ionoMap->nhgt==1) {
		ihgt=0;
	} else {
		ihgt = (int)((hgt-ionoMap->hgt1)/ionoMap->dhgt);
	}

	if (ionoMap->nlat==1) {
		ilat=0;
	} else {
		ilat = (int)((lat-ionoMap->lat1)/ionoMap->dlat);
	}

	if (ionoMap->nlon==1) {
		ilon=0;
	} else {
		ilon = (int)((lon-ionoMap->lon1)/ionoMap->dlon);
	}

	return ionoConv3Dto1D(ionoMap, ihgt, ilat, ilon);
}

/*****************************************************************************
 * Name        : setIonoValue
 * Description : Sets the TEC or RMS value of a ionospheric map
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TIonoMap  *ionoMap              IO N/A  Ionospheric map structure
 * int  type                       I  N/A  TEC, RMS or HGT (0, 1 or 2)
 * double  hgt                     I  km   Height value  
 * double  lat                     I  deg  Latitude value
 * double  lon                     I  deg  Longitude value
 * double  value                   I  TECU Value to fill
 * Returned value (int)            O  N/A  Status of function
 *                                         0 => Failed to set the value
 *                                         1 => Value properly set
 *****************************************************************************/
int setIonoValue (TIonoMap *ionoMap, int type, double hgt, double lat, double lon, double value) {
	int ind;

	ind = ionoHLLto1D(ionoMap,hgt,lat,lon);
	if (ind<0) return 0;

	if (type==0) { // TEC
		ionoMap->TEC[ind] = value;
	} else if (type==1) { // RMS
		ionoMap->RMS[ind] = value;
	} else if (type==2) { // HGT
				ionoMap->HGT[ind] = value;
	} else {
		return 0;
	}

	return 1;
}

/*****************************************************************************
 * Name        : getIonoValue
 * Description : Returns the TEC or RMS value of a ionospheric map
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TIonoMap  *ionoMap              I  N/A  Ionospheric map structure
 * int  type                       I  N/A  TEC, RMS or HGT (0, 1 or 2)
 * double  hgt                     I  km   Height value  
 * double  lat                     I  deg  Latitude value
 * double  lon                     I  deg  Longitude value
 * Returned value (double)         O  TECU Value of the cell (in TECUs).
 *                                    9999 is used for invalid values,
 *                                    as defined in IONEX format)
 *****************************************************************************/
double getIonoValue (TIonoMap *ionoMap, int type, double hgt, double lat, double lon) {
	int ind;

	ind = ionoHLLto1D(ionoMap,hgt,lat,lon);

	if (ind<0) return 9999;

	if (type==0) { // TEC
		return ionoMap->TEC[ind];
	} else if (type==1) { // RMS
		return ionoMap->RMS[ind];
	} else if (type==2) { // HGT
				return ionoMap->HGT[ind];
	}

	return 9999;
}

/*****************************************************************************
 * Name        : getIonoMapTotalSize
 * Description : Returns the total size of a map
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TIonoMap  *ionoMap              I  N/A  Ionospheric map structure
 * Returned value (int)            O  N/A  Map total size
 *****************************************************************************/
int getIonoMapTotalSize (TIonoMap *ionoMap) {
		return ionoMap->nhgt * ionoMap->nlat * ionoMap->nlon;
}

/*****************************************************************************
 * Name        : FPPPConv3Dto1D
 * Description : Transforms a 3 dimensional index to a single dimension index
 *               obtaining the data from a TFPPPMap structure
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TFPPPMap  *FPPPMap              I  N/A  FPPP map structure
 * int  ihgt                       I  N/A  Height index  
 * int  ilat                       I  N/A  Latitude index
 * int  ilt                        I  N/A  Local time index
 * Returned value (int)            O  N/A  1D index
 *****************************************************************************/
int FPPPConv3Dto1D (TFPPPMap *FPPPMap, int ihgt, int ilat, int ilt) {
	return conv3Dto1D(ihgt,ilat,ilt,NUMBERFPPPMAPS,FPPPMap->nlat);
}

/*****************************************************************************
 * Name        : FPPPHLLto1D
 * Description : Gives the 1D index of the double values of hgt, lat and lon
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TFPPPMap  *FPPPMap              I  N/A  FPPP map structure
 * double  hgt                     I  km   Height value  
 * double  lat                     I  deg  Latitude value
 * double  lt                      I  deg  Local time value
 * Returned value (int)            O  N/A  1D index
 *****************************************************************************/
int FPPPHLLto1D (TFPPPMap *FPPPMap, double hgt, double lat, double lt) {
	int		ilat, ilt, ihgt;

	if (hgt == FPPPMap->hgt1) { 
		ihgt = 0;
	} else if (hgt == FPPPMap->hgt2) {
		ihgt = 1;
	} else {
		return -1;
	}

	if (FPPPMap->nlat==1) {
		ilat=0;
	} else {
		ilat = (int)((lat-FPPPMap->lat1)/FPPPMap->dlat);
	}

	if (FPPPMap->nlt==1) {
		ilt=0;
	} else {
		ilt = (int)((lt-FPPPMap->lt1)/FPPPMap->dlt);
	}

	return FPPPConv3Dto1D(FPPPMap, ihgt, ilat, ilt);
}

/*****************************************************************************
 * Name        : setFPPPValue
 * Description : Sets the TEC or SIGMA value of a FPPP map
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TFPPPMap  *FPPPMap              IO N/A  FPPP map structure
 * int  type                       I  N/A  TEC, SIGMA (0 or 1)
 * double  hgt                     I  km   Height value  
 * double  lat                     I  deg  Latitude value
 * double  lt                      I  deg  Local time value
 * double  value                   I  TECU Value to fill
 * Returned value (int)            O  N/A  Status of function
 *                                         0 => Failed to set the value
 *                                         1 => Value properly set
 *****************************************************************************/
int setFPPPValue (TFPPPMap *FPPPMap, int type, double hgt, double lat, double lt, double value) {
	int ind;

	ind = FPPPHLLto1D(FPPPMap,hgt,lat,lt);
	if (ind<0) return 0;

	if (type==0) { // TEC
		FPPPMap->TEC[ind] = value;
	} else if (type==1) { // SIGMA
		FPPPMap->SIGMA[ind] = value;
	} else {
		return 0;
	}

	return 1;
}

/*****************************************************************************
 * Name        : getFPPPValue
 * Description : Returns the TEC or SIGMA value of a FPPP map
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TFPPPMap  *FPPPMap              I  N/A  FPPP map structure
 * int  type                       I  N/A  TEC, SIGMA (0 or 1)
 * double  hgt                     I  km   Height value  
 * double  lat                     I  deg  Latitude value
 * double  lt                      I  deg  Local time value
 * Returned value (double)         O  TECU Value of the cell (in TECUs).
 *                                    9999 is used for invalid values,
 *                                    as defined in IONEX format)
 *****************************************************************************/
double getFPPPValue (TFPPPMap *FPPPMap, int type, double hgt, double lat, double lt) {
	int ind;

	ind = FPPPHLLto1D(FPPPMap,hgt,lat,lt);

	if (ind<0) return 9999;

	if (type==0) { // TEC
		return FPPPMap->TEC[ind];
	} else if (type==1) { // SIGMA
		return FPPPMap->SIGMA[ind];
	}

	return 9999;
}

/*****************************************************************************
 * Name        : getFPPPMapTotalSize
 * Description : Returns the total size of a map
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TFPPP  *FPPPMap                 I  N/A  TFPPP structure
 * Returned value (int)            O  N/A  Map total size
 *****************************************************************************/
int getFPPPMapTotalSize (TFPPPMap *FPPPMap) {
	return NUMBERFPPPMAPS * FPPPMap->nlat * FPPPMap->nlt;
}

/*****************************************************************************
 * Name        : getIonoPiercePoint
 * Description : Computes the ionospheric pierce point for a 
 *                   satellite-receiver ray
 * Parameters  :
 * Name                             |Da|Unit|Description
 * TEpoch  *epoch                    I  N/A  TEpoch structure
 * TPiercePoint *PiercePoint         IO N/A  TPiercePoint structure
 * int  satIndex                     I  N/A  Index of the satellite to 
 *                                             obtain the correction
 * double earthRadius                I  Km   Earth radius (in Kilometers)
 * double altitude                   I  Km   IonoMap altitude (in Kilometers)
 * int mode                          I  N/A  0 => Use spherical coordinates for reference station (IONEX, FPPP)
 *                                           1 => Use geodetic coordinates for reference station (SBAS)
 * Returned value                    O  N/A  None
 *****************************************************************************/
void getIonoPiercePoint (TEpoch *epoch, TPiercePoint *PiercePoint, int satIndex, double earthRadius, double altitude, int mode){

	double rhox,rhoy,rhoz;
	double rho;
	double recx,recy,recz;
	double Rse;
	double raylambda;
	double xymodule;

	//For the calculations in the Pierce Point and in the rest of ionexModel and FPPPmodel, a geocentric elevation is used. That differs from gLAB's elevation, which is geodetic elevation

	earthRadius*= 1000; //Convert to meters 
	altitude*= 1000;    //Convert to meters
	
	if(mode==0) {
		recx=epoch->receiver.aproxPosition[0];
		recy=epoch->receiver.aproxPosition[1];
		recz=epoch->receiver.aproxPosition[2];
		earthRadius = sqrt(recx*recx+recy*recy+recz*recz); // For IONEX and F-PPP, the Earth Radius contains the Earth Radius plus the height from the user
	} else {
		//mode==1
		recx=earthRadius*cos(epoch->receiver.aproxPositionNEU[0])*cos(epoch->receiver.aproxPositionNEU[1]);
		recy=earthRadius*cos(epoch->receiver.aproxPositionNEU[0])*sin(epoch->receiver.aproxPositionNEU[1]);
		recz=earthRadius*sin(epoch->receiver.aproxPositionNEU[0]);
	}


	rhox = epoch->sat[satIndex].position[0] - recx;
	rhoy = epoch->sat[satIndex].position[1] - recy;
	rhoz = epoch->sat[satIndex].position[2] - recz;

	rho = sqrt(pow(rhox,2) + pow(rhoy,2) + pow (rhoz,2));
	Rse = (recx*rhox + recy*rhoy + recz*rhoz)/rho;
	raylambda = -Rse + sqrt(pow(earthRadius + altitude,2) - pow(earthRadius,2) + pow(Rse,2));

	PiercePoint->x = recx + raylambda*rhox/rho;
	PiercePoint->y = recy + raylambda*rhoy/rho;
	PiercePoint->z = recz + raylambda*rhoz/rho;
	
	xymodule = sqrt( pow(PiercePoint->x,2) + pow(PiercePoint->y,2) );
	
	PiercePoint->fi = atan2(PiercePoint->z,xymodule)*r2d;	//Latitude between -90..90º
	PiercePoint->longitude = atan2(PiercePoint->y,PiercePoint->x)*r2d; //Longitude between -180º..180º
	PiercePoint->elevation = asin(Rse/earthRadius)*r2d;

	epoch->IPPlat = PiercePoint->fi;
	epoch->IPPlon = PiercePoint->longitude;
}

/*****************************************************************************
 * Name        : getMappingFunction
 * Description : Computes the mapping function for a given grid at any height  
 * Parameters  :
 * Comment     : QFAC function is from "Mapping and Predicting the Earth's
 *                  Ionosphere Using the Global Positioning System", Stefan
 *                  Schaer Inaugural dissertation
 * Name                                 |Da|Unit|Description
 * TPiercePoint *PiercePoint             IO N/A  TPiercePoint structure
 * double earthRadius                    I  N/A  Earth radius from IONEX file
 * double altitude                       I  N/A  IonoMap altitude
 * TOptions  *options                    I  N/A  TOptions structure
 * Returned value                        O  N/A  None
 *****************************************************************************/
void getMappingFunction (TPiercePoint *PiercePoint, double earthRadius, double altitude, char functionType[5],TOptions *options){

	double	a0 = 1.0206;
	double	a1 = 0.4663;
	double	a2 = 3.5055;
	double	a3 = -1.8415;
	double  z = 90 + PiercePoint->elevation;

	earthRadius*= 1000; //Convert to meters
	altitude*= 1000;    //Convert to meters

	if (strncmp(functionType,"COSZ",4)==0 || strncmp(functionType,"NONE",4)==0){
		PiercePoint->mappingFunction = (altitude + earthRadius) / ( sqrt( pow(altitude + earthRadius,2) - pow(earthRadius*cos(PiercePoint->elevation*d2r),2) ) );
	}
	else if (strncmp(functionType,"QFAC",4)==0){
		PiercePoint->mappingFunction = a0 + a1*pow((z/90),2) + a2*pow((z/90),4) + a3*pow((z/90),6);
	}
	else{
		sprintf(messagestr,"Mapping function type \"%s\" in IONEX file not supported\n",functionType); 
		printError(messagestr,options);
	}

}


/*****************************************************************************
 * Name        : getConstellationElement
 * Description : Returns the TConstellationElement of a satellite for a given
 *               time
 * Parameters  :
 * Name                           |Da|Unit|Description
 * enum GNSSystem  GNSS            I  N/A  GNSS enumerator of the satellite
 * int  PRN                        I  N/A  PRN of the satellite
 * TTime  *t                       I  N/A  Reference time
 * TConstellation  *constellation  I  N/A  TConstellation structure
 * Returned value (TConstellationElement*)
 *                                 O  N/A  Pointer to the TConstellationElement
 *                                         selected
 *                                         NULL => Satellite not found
 *****************************************************************************/
TConstellationElement* getConstellationElement (enum GNSSystem GNSS, int PRN, TTime *t,TConstellation* constellation) {
	int i;

	for (i=0;i<constellation->numSatellites;i++) {
		if (constellation->sat[i].GNSS == GNSS && constellation->sat[i].PRN == PRN) {
			if (tdiff(t,&constellation->sat[i].tLaunch)>0 && tdiff(t,&constellation->sat[i].tDecommissioned)<0) {
				// If t is beyond tLaunch but lower than tDecommissioned
				return &constellation->sat[i];
			}
		}
	}
	return NULL;
}

/*****************************************************************************
 * Name        : getStation
 * Description : Get the station structure from its name (as a string)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *name                     I  N/A  Name of the station
 * TStationList  *stationList      I  N/A  List of stations to look for
 * Returned value (*TStatoin)      O  N/A  Pointer to the antenna inside TStationList
 *                                         If it is NULL, the station has not been
 *                                         found
 *****************************************************************************/
TStation *getStation (char *name, TStationList *stationList) {
	int		i;
	char	aux[5];

	//Copy only the first four characters of the station name, which will be the name in the SINEX
	strncpy(aux,name,4);
	aux[4]='\0';

	for (i=0;i<stationList->n;i++) {
		if (strcasecmp(aux,stationList->station[i].name)==0) return &stationList->station[i];
	}
	
	return NULL;
}

/*****************************************************************************
 * Name        : addStat
 * Description : Add a value to a TStat structure, computing the mean and square
 *               mean of all the values that have been inserted
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TStat  *stat                    IO N/A  TStat structure to operate
 * double  value                   I  N/A  Value to include to stat
 *****************************************************************************/
void addStat (TStat *stat, double value) {
	stat->mean = (stat->n*stat->mean + value)/(stat->n+1);
	stat->mean2 = (stat->n*stat->mean2 + value*value)/(stat->n+1);
	stat->n++;
}



/*****************************************************************************
 * Name        : ConcatenateSP3
 * Description : Concanate precise orbits and clocks from several (if available)
 *               and also take out all samples with invalid values
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int RefData                     I  N/A  Flag to indicate if data is for reference position
 *                                           (no clocks, only one satellite). Values are 0 or 1
 * TGNSSproducts  *products        IO N/A  TGNSSproducts structure
 * TGNSSproducts  *pastSP3Prod     I  N/A  TGNSSproducts structure for previous SP3 products
 * TGNSSproducts  *nextSP3Prod     I  N/A  TGNSSproducts structure for next SP3 products
 * TOptions  *options              I  N/A  TOptions structure to configure behaviour
 *****************************************************************************/
void ConcatenateSP3 (int RefData, TGNSSproducts *products, TGNSSproducts *pastSP3Prod, TGNSSproducts *nextSP3Prod,  TOptions  *options) {

	int 			i,GNSS,PRN;
	int				indJ,indK;
	int				ind,indPast,indNext,indTmp;
	int				iters;
	int				skippedSamples;
	int				validSamplesPast,validSamplesTmp,validSamplesNext,validSamplesAll;
	int				FirstSampleToBeSkipped;
	int				initPRN=1;
	double			diffTimePast,diffTimeNext;
	TSP3orbits		*orbitsNext;
	TSP3orbits		*orbitsPast;
	TSP3orbits		*orbitsTmp;
	TSP3clocks		*clocksTmp;
	TSP3clocks		*clocksNext;
	TSP3clocks		*clocksPast;

	if (RefData==1) {
		initPRN=0;
	}
	
	//Free memory from previous concatenations
	for(i=0;i<MAX_GNSS*MAX_SATELLITES_PER_GNSS;i++) {
		if(products->SP3->orbits.Concatblock[i]!=NULL) {
			free(products->SP3->orbits.Concatblock[i]);
		}
/*		if (RefData==0) {
			if(products->SP3->clocks.Concatblock[i]!=NULL) {
				free(products->SP3->clocks.Concatblock[i]);
			}
		}*/
	}

	for(GNSS=0;GNSS<MAX_GNSS;GNSS++) {
		for(PRN=initPRN;PRN<MAX_SATELLITES_PER_GNSS;PRN++) {
			//Concatenate SP3 orbits
			
			// orbitsTmp corresponds to the current products
			orbitsTmp = &products->SP3->orbits;
			ind = orbitsTmp->index[GNSS][PRN];

			// Take into account previous and following SP3 products to fit the polynomial
			orbitsPast = &pastSP3Prod->SP3->orbits;
			orbitsNext = &nextSP3Prod->SP3->orbits;
			indPast = orbitsPast->index[GNSS][PRN];
			indNext = orbitsNext->index[GNSS][PRN];
			if (RefData==1) {
				ind=indPast=indNext=0;
			}
			
			if (ind==-1 && indPast==-1 && indNext==-1) continue;


			// Check how many data can be allocated in arrays
			if(indPast!=-1 && ind!=-1) {
				diffTimePast=tdiff(&orbitsTmp->block[ind][0].t,&orbitsPast->block[indPast][0].t);
			} else if (indPast!=-1 && ind==-1) {
				diffTimePast=86400.; 
			} else {
				diffTimePast=0.;
			}

			if(indNext!=-1 && ind!=-1) {
				diffTimeNext=tdiff(&orbitsNext->block[indNext][0].t,&orbitsTmp->block[ind][0].t);
			} else if (indNext!=-1 && ind==-1) {
				diffTimeNext=86400.; 
			} else {
				diffTimeNext=0.;
			}

			if(ind==-1) {
				//There is no data for today, but for previous or next day data is available
				//Add a new index number
				orbitsTmp->index[GNSS][PRN]=orbitsTmp->numSatellites;
				indTmp=-1;
				ind=orbitsTmp->numSatellites;
				orbitsTmp->numSatellites++;
			} else {
				indTmp=ind;
			}

			//Check if there are past SP3 products than current time
			if ( diffTimePast >= 85500.0 && diffTimePast <= 87300.0 ) { //Leave a possible data gap of +-15 minutes (900 seconds)
				skippedSamples=0;
				indJ=indK=iters=0;
				for (i=0;i<orbitsPast->numRecords;i++) {
					if(orbitsPast->block[indPast][i].x[0]==0. && orbitsPast->block[indPast][i].x[1]==0. && orbitsPast->block[indPast][i].x[2]==0.) {
						skippedSamples++;
						continue;
					}
					indJ=i-skippedSamples;
					orbitsTmp->Concatblock[ind]=realloc(orbitsTmp->Concatblock[ind],sizeof(TSP3orbitblock)*(indJ+1));
					memcpy(&orbitsTmp->Concatblock[ind][indJ],&orbitsPast->block[indPast][i],sizeof(TSP3orbitblock));
				}
				validSamplesPast=orbitsPast->numRecords-skippedSamples;
				//Check if the last entry of previous file and first entry of current file are the same
				if(indTmp==-1) {
					//No samples for current day
					FirstSampleToBeSkipped=0;
					if(validSamplesPast>0) indJ++; //Only add one if we have read at least one valid sample
				} else if( tdiff(&orbitsTmp->block[ind][0].t,&orbitsPast->block[indPast][orbitsPast->numRecords-1].t)==0.)  {
					//Last entry of previous day and first entry of current day are the same
					//Check if last entry of previous day has invalid coordinates
					if(orbitsPast->block[indPast][orbitsPast->numRecords-1].x[0]==0. && orbitsPast->block[indPast][orbitsPast->numRecords-1].x[1]==0. && orbitsPast->block[indPast][orbitsPast->numRecords-1].x[2]==0.) {
						//Last entry of previous day is invalid, so the last one saved is from a previous epoch. indJ has to be increased.
						//If last entry had invalid coordinates, we would not need to increase indJ because we will overwrite the data
						if(validSamplesPast>0) indJ++; //Only add one if we have read at least one valid sample
						FirstSampleToBeSkipped=0;
					} else {
						//Last entry of previous day is valid, check if we need to keep the sample from the previous day or from current day
						if(options->LastSamplePrevDayOrb==1) {
							//Use Sample from previous day
							if(validSamplesPast>0) indJ++; //Only add one if we have read at least one valid sample
							FirstSampleToBeSkipped=1;
						} else {
							//Use Sample from next day
							FirstSampleToBeSkipped=0;
						}
					}
				} else {
					FirstSampleToBeSkipped=0;
					if(validSamplesPast>0) indJ++; //Only add one if we have read at least one valid sample
				}
				skippedSamples=0;
				if (indTmp!=-1) {
					for (i=FirstSampleToBeSkipped;i<orbitsTmp->numRecords;i++) {
						if(orbitsTmp->block[ind][i].x[0]==0. && orbitsTmp->block[ind][i].x[1]==0. && orbitsTmp->block[ind][i].x[2]==0.) {
							skippedSamples++;
							continue;
						}
						indK = indJ + i - skippedSamples-FirstSampleToBeSkipped;
						orbitsTmp->Concatblock[ind]=realloc(orbitsTmp->Concatblock[ind],sizeof(TSP3orbitblock)*(indK+1));
						memcpy(&orbitsTmp->Concatblock[ind][indK],&orbitsTmp->block[ind][i],sizeof(TSP3orbitblock));
					}
					validSamplesTmp=orbitsTmp->numRecords-skippedSamples;
					validSamplesAll=validSamplesTmp+validSamplesPast;
					if(validSamplesAll>0) iters = indK +1; //Only increase iters if we have valid values 
				} else {
					//No data for current time
					validSamplesTmp=0;
					validSamplesAll=validSamplesPast;
					if(validSamplesAll>0) {
						iters=indJ;
					} else {
						iters=0;
					}
				}
			} else { // No previous SP3 products
				skippedSamples=iters=0;
				if(indTmp!=-1) {
					for (i=0;i<orbitsTmp->numRecords;i++) {
						if(orbitsTmp->block[ind][i].x[0]==0. && orbitsTmp->block[ind][i].x[1]==0. && orbitsTmp->block[ind][i].x[2]==0.) {
							skippedSamples++;
							continue;
						}
						indK=i - skippedSamples;
						orbitsTmp->Concatblock[ind]=realloc(orbitsTmp->Concatblock[ind],sizeof(TSP3orbitblock)*(indK+1));
						memcpy(&orbitsTmp->Concatblock[ind][indK],&orbitsTmp->block[ind][i],sizeof(TSP3orbitblock));
					}
					validSamplesTmp=validSamplesAll=orbitsTmp->numRecords-skippedSamples;

					if(validSamplesAll>0) iters = indK +1; //Only increase iters if we have valid values 
				} else {
					validSamplesTmp=validSamplesAll=0;
					indK=0;
				}
			}
			// Fill arrays with future SP3 products
			skippedSamples=0;
			if ( diffTimeNext >= 85500.0 && diffTimeNext <= 87300.0 ) { //Leave a possible data gap of +-15 minutes (900 seconds)
				//Check if the last entry of previous file and first entry of current file are the same
				if(indTmp==-1) {
					FirstSampleToBeSkipped=0;
					if(validSamplesAll>0) indK++; //Only add one if we have read at least one valid sample
				} else if(tdiff(&orbitsNext->block[indNext][0].t,&orbitsTmp->block[ind][orbitsTmp->numRecords-1].t)==0.) {
					//Last entry of current day and first entry of next day are the same
					//Check if last entry of previous day has invalid coordinates
					if(orbitsTmp->block[ind][i].x[orbitsTmp->numRecords-1]==0. && orbitsTmp->block[ind][orbitsTmp->numRecords-1].x[1]==0. && orbitsTmp->block[ind][orbitsTmp->numRecords-1].x[2]==0.) {
						//Last entry of current day is invalid, so the last one saved is from a previous epoch. indK has to be increased.
						//If last entry had invalid coordinates, we would not need to increase indK because we will overwrite the data
						if(validSamplesAll>0) indK++; //Only add one if we have read at least one valid sample
						FirstSampleToBeSkipped=0;
					} else {
						//Last entry of previous day is valid, check if we need to keep the sample from the previous day or from current day
						if(options->LastSamplePrevDayOrb==1) {
							//Use Sample from previous day
							if(validSamplesAll>0) indK++; //Only add one if we have read at least one valid sample
							FirstSampleToBeSkipped=1;
						} else {
							//Use Sample from next day
							FirstSampleToBeSkipped=0;
						}
					}
				} else {
					FirstSampleToBeSkipped=0;
					if(validSamplesAll>0) indK++; //Only add one if we have read at least one valid sample
				}
				for (i=FirstSampleToBeSkipped;i<orbitsNext->numRecords;i++) {
					if(orbitsNext->block[indNext][i].x[0]==0. && orbitsNext->block[indNext][i].x[1]==0. && orbitsNext->block[indNext][i].x[2]==0.) {
						continue;
					}
					indJ = indK + i - skippedSamples-FirstSampleToBeSkipped;
					orbitsTmp->Concatblock[ind]=realloc(orbitsTmp->Concatblock[ind],sizeof(TSP3orbitblock)*(indJ+1));
					memcpy(&orbitsTmp->Concatblock[ind][indJ],&orbitsNext->block[indNext][i],sizeof(TSP3orbitblock));
				}
				validSamplesNext=orbitsNext->numRecords-skippedSamples;
				validSamplesAll+=validSamplesNext;
				if(validSamplesAll>0) iters = indJ +1; //Only increase iters if we have valid values 
			}

			orbitsTmp->numblocsConcat[GNSS][PRN]=iters;	

			if(RefData==1) break;

			//Concatenate clocks (from SP3 or CLK file)
			clocksTmp = &products->SP3->clocks;
			clocksPast = &pastSP3Prod->SP3->clocks;
			clocksNext = &nextSP3Prod->SP3->clocks;

			ind = clocksTmp->index[GNSS][PRN];
			indPast = clocksPast->index[GNSS][PRN];
			indNext = clocksNext->index[GNSS][PRN];

			if (ind==-1 && indPast==-1 && indNext==-1) continue;


			// Check how many data can be allocated in arrays
			if(indPast!=-1 && ind!=-1) {
				diffTimePast=tdiff(&clocksTmp->block[ind][0].t,&clocksPast->block[indPast][0].t);
			} else if (indPast!=-1 && ind==-1) {
				diffTimePast=86400.; 
			} else {
				diffTimePast=0.;
			}

			if(indNext!=-1 && ind!=-1) {
				diffTimeNext=tdiff(&clocksNext->block[indNext][0].t,&clocksTmp->block[ind][0].t);
			} else if (indNext!=-1 && ind==-1) {
				diffTimeNext=86400.; 
			} else {
				diffTimeNext=0.;
			}

			if(ind==-1) {
				//There is no data for today, but for previous or next day data is available
				//Add a new index number
				clocksTmp->index[GNSS][PRN]=clocksTmp->numSatellites;
				indTmp=-1;
				ind=clocksTmp->numSatellites;
				clocksTmp->numSatellites++;
			} else {
				indTmp=ind;
			}


			//We will create a new block with past, present and future clocks, and also without INVALID_CLOCK entries
			if ( diffTimePast >= 85500.0 && diffTimePast <= 87300.0 ) {	//Leave a possible data gap of +-15 minutes (900 seconds)
				skippedSamples=0;
				indJ=indK=iters=0;
				for ( i = 0; i < clocksPast->numRecords; i++ ) {
					if(clocksPast->block[indPast][i].clock==INVALID_CLOCK) {
						skippedSamples++;
						continue;
					}
					indJ=i-skippedSamples;
					clocksTmp->Concatblock[ind]=realloc(clocksTmp->Concatblock[ind],sizeof(TSP3clockblock)*(indJ+1));
					memcpy(&clocksTmp->Concatblock[ind][indJ],&clocksPast->block[indPast][i],sizeof(TSP3clockblock));
				}
				validSamplesPast=clocksPast->numRecords-skippedSamples;
				//Check if the last entry of previous file and first entry of current file are the same
				if (indTmp==-1) {
					//No samples for current day
					FirstSampleToBeSkipped=0;
					if(validSamplesPast>0) indJ++; //Only add one if we have read at least one valid sample
				} else if(tdiff(&clocksTmp->block[ind][0].t,&clocksPast->block[indPast][clocksPast->numRecords-1].t)==0.) {
					//Last entry of previous day and first entry of current day are the same
					//Check if last entry of previous day does not have INVALID_CLOCK
					if(clocksPast->block[indPast][clocksPast->numRecords-1].clock==INVALID_CLOCK) {
						//Last entry of previous day is invalid, so the last one saved is from a previous epoch. indJ has to be increased.
						//If last entry had a valid clock, we would not need to increase indJ because we will overwrite the data
						if(validSamplesPast>0) indJ++; //Only add one if we have read at least one valid sample
						FirstSampleToBeSkipped=0;
					} else {
						//Last entry of previous day is valid, check if we need to keep the sample from the previous day or from current day
						if(options->LastSamplePrevDayClk==1) {
							//Use Sample from previous day
							if(validSamplesPast>0) indJ++; //Only add one if we have read at least one valid sample
							FirstSampleToBeSkipped=1;
						} else {
							//Use Sample from next day
							FirstSampleToBeSkipped=0;
						}
					}
				} else {
					if(validSamplesPast>0) indJ++; //Only add one if we have read at least one valid sample
					FirstSampleToBeSkipped=0;
				}
				skippedSamples=0;
				if (indTmp!=-1) {
					for ( i = FirstSampleToBeSkipped; i < clocksTmp->numRecords; i++ ) {
						if(clocksTmp->block[ind][i].clock==INVALID_CLOCK) {
							skippedSamples++;
							continue;
						}
						indK = indJ + i - skippedSamples - FirstSampleToBeSkipped;
						clocksTmp->Concatblock[ind]=realloc(clocksTmp->Concatblock[ind],sizeof(TSP3clockblock)*(indK+1));
						memcpy(&clocksTmp->Concatblock[ind][indK],&clocksTmp->block[ind][i],sizeof(TSP3clockblock));
					}
					validSamplesTmp=clocksTmp->numRecords-skippedSamples;
					validSamplesAll=validSamplesTmp+validSamplesPast;
					if(validSamplesAll>0) iters= indK+1;
				} else {
					//No data for current time
					validSamplesTmp=0;
					validSamplesAll=validSamplesPast;
					if(validSamplesAll>0) {
						iters=indJ;
					} else {
						iters=0;
					}
				}
			} else { // No previous SP3 clocks
				if(indTmp!=-1) {
					skippedSamples=iters=0;
					for ( i = 0; i < clocksTmp->numRecords; i++ ) {
						if(clocksTmp->block[ind][i].clock==INVALID_CLOCK) {
							skippedSamples++;
							continue;
						}
						indK=i-skippedSamples;
						clocksTmp->Concatblock[ind]=realloc(clocksTmp->Concatblock[ind],sizeof(TSP3clockblock)*(indK+1));
						memcpy(&clocksTmp->Concatblock[ind][indK],&clocksTmp->block[ind][i],sizeof(TSP3clockblock));
					}
					validSamplesTmp=validSamplesAll=clocksTmp->numRecords-skippedSamples;
					if(validSamplesAll>0) iters=indK +1; //Only add one if we have read at least one valid sample
				} else {
					validSamplesTmp=validSamplesAll=0;
					indK=0;
				}
			}

			// Fill arrays with future SP3 clocks
			skippedSamples=0;
			if ( diffTimeNext >= 85500.0 && diffTimeNext <= 87300.0 ) { //Leave a possible data gap of +-15 minutes (900 seconds)
				//Check if the last entry of previous file and first entry of current file are the same
				if(indTmp==-1) {
					FirstSampleToBeSkipped=0;
					if(validSamplesAll>0) indK++; //Only add one if we have read at least one valid sample
				} else if(tdiff(&clocksNext->block[indNext][0].t,&clocksTmp->block[ind][clocksTmp->numRecords-1].t)==0.) {
					//Last entry of next day and first entry of current day are the same
					//Check if last entry of current day has INVALID_CLOCK
					if(clocksTmp->block[ind][clocksTmp->numRecords-1].clock==INVALID_CLOCK) {
						//Last entry of previous day is invalid, so the last one saved is from a previous epoch. indK has to be increased.
						//If last entry had a valid clock, we would not need to increase indK because we will overwrite the data
						if(validSamplesAll>0) indK++; //Only add one if we have read at least one valid sample
						FirstSampleToBeSkipped=0;
					} else {
						//Last entry of previous day is valid, check if we need to keep the sample from the previous day or from current day
						if(options->LastSamplePrevDayClk==1) {
							//Use Sample from previous day
							if(validSamplesAll>0) indK++; //Only add one if we have read at least one valid sample
							FirstSampleToBeSkipped=1;
						} else {
							//Use Sample from next day
							FirstSampleToBeSkipped=0;
						}
					}
				} else {
					FirstSampleToBeSkipped=0;
					if(validSamplesAll>0) indK++; //Only add one if we have read at least one valid sample
				}
				for ( i = FirstSampleToBeSkipped; i < clocksNext->numRecords; i++ ) {
					if(clocksNext->block[indNext][i].clock==INVALID_CLOCK) {
						skippedSamples++;
						continue;
					}
					indJ=indK + i - skippedSamples -FirstSampleToBeSkipped;
					clocksTmp->Concatblock[ind]=realloc(clocksTmp->Concatblock[ind],sizeof(TSP3clockblock)*(indJ+1));
					memcpy(&clocksTmp->Concatblock[ind][indJ],&clocksNext->block[indNext][i],sizeof(TSP3clockblock));
				}
				validSamplesNext=clocksNext->numRecords-skippedSamples;
				validSamplesAll+=validSamplesNext;
				if(validSamplesAll>0) iters=indJ +1; //Only add one if we have read at least one valid sample
			}
			clocksTmp->numblocsConcat[GNSS][PRN]=iters;	


		}//End for PRN loop
		if(RefData==1) break;
	}//End for GNSS loop

	//Save last epoch with data
	memcpy(&orbitsTmp->endTime,&orbitsNext->endTime,sizeof(TTime));
	if(RefData==0) { //When joining reference position data, there are no clocks!
		memcpy(&clocksTmp->endTime,&clocksNext->endTime,sizeof(TTime));
	}
	products->type=SP3;
	pastSP3Prod->type=SP3;
	nextSP3Prod->type=SP3;


}

/*****************************************************************************
 * Name        : freeSP3data
 * Description : Free SP3 orbit and clock data. This is necesary when concatening
 *                 SP3/clock files
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TGNSSproducts  *products        I  N/A  TGNSSproducts structure
 *****************************************************************************/
void freeSP3data(TGNSSproducts  *products) {

	int i;
	
	//Free orbit data
	for(i=0;i<products->SP3->orbits.numSatellitesRead;i++) {
		free(products->SP3->orbits.block[i]);
	}
	free(products->SP3->orbits.block);
	free(products->SP3->orbits.accuracy);

	products->SP3->orbits.block=NULL;
	products->SP3->orbits.accuracy=NULL;

	//Free clock data
	for(i=0;i<products->SP3->clocks.numSatellitesRead;i++) {
		free(products->SP3->clocks.block[i]);
	}
	free(products->SP3->clocks.block);

	products->SP3->clocks.block=NULL;
}



/*****************************************************************************
 * Name        : strbintostrhex
 * Description : Convert a binary string to a hexadecimal string
 *               (character by character)
 *               Note: If input string length is not a multiple of 4, it will
 *                     add trailing zeros at the end as necessary
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *binary                   I  N/A  String with the binary values (one bit per byte)
 * char  *hex                      O  N/A  String with the text values
 * int   capital                   I  N/A  To indicate if we want upper case or lower case characters
 *                                          0 => Lower case
 *                                          1 => Upper case
 *****************************************************************************/
void strbintostrhex (char *binary, char *hex, int capital) {

	int 	i,j;
	int 	len;
	int 	modulo;
	int 	ascii;
	char 	aux[2000],aux2[2000];
	char	*endptr;                //This is just for strtol function

	strcpy(aux,binary);	//Copy string to auxiliar variable, so we don't modify the input

	len=strlen(binary);	//Find input length
	modulo=len%4;		//Check if input bit length is a multiple of 4

	if(modulo!=0) {		//If it nos a multiple of 4 add trailing zeros
		for(i=0;i<4-len%4;i++) {
			sprintf(aux2,"%s0",aux);	
			strcpy(aux,aux2);
		}
	}

	j=0;			//j will indicate the position in the output string

	//Loop to process all bits in groups of 4
	for(i=0;i<(int)(len+modulo)/4;i++) {
		getstr(aux2,aux,i*4,4);		//Get 4 bits

		ascii=strtol(aux2,&endptr,2);	//Get the integer value

		if(ascii<10) ascii+=48;		//Add 48 to get the ascii code for 0-9
		else if(capital==1) ascii+=55;	//Add 55 to get the ascii code for A-F
		else ascii+=87;			//Add 87 to get the ascii code for a-f

		hex[j]=ascii;			//Put the ascii value in the hexadecimal string
		j++;
	}

	hex[j]='\0';				//Set the end of the string
}

/*****************************************************************************
 * Name        : SBASnavmode2SBASnavstr
 * Description : Transform from internal SBAS navigation mode to string
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int mode                        I  N/A  SBAS navigation mode
 * Returned value (char*)          O  N/A  SBAS navigation string
 *****************************************************************************/
char *SBASnavmode2SBASnavstr (int mode) {
	static char str[10];

	strcpy(str,"GPS");

	switch (mode) {
	case 0:
		strcpy(str,"NPA");
		break;
	case 1:
		strcpy(str,"PA");
		break;
	default:
		strcpy(str,"GPS");
	}

	return str;
}

/*****************************************************************************
 * Name        : strhextostrbin
 * Description : Convert a hexadecimal string to a binary string
 *               (character by character)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *hex                      I  N/A  String with the text values
 * char  *binary                   O  N/A  String with the binary values (one bit per byte)
 *****************************************************************************/
void strhextostrbin (char *hex,char *binary){

	int i,j,k;
	int ascii;		    	//Used to store the ASCII number of a character
	int length=strlen(hex);		//Find the length of the user's input

	char binary_reverse[5];
	
	for(i=0;i<length;i++){		//Repeat until user's input have all been read
					//i<length because the last character is "\0"
	
		ascii = hex[i];  	//Store a character in its ASCII number


		if(ascii>=48&&ascii<=57) {
			//ASCII number for 0-9
			ascii-=48;			//Substract 48 so the integer value stays between 0-9
		} else if(ascii>=65&&ascii<=70) {
			//ASCII code for A-F
			ascii-=55;			//Substract 55 so the integer value stays between 10-15
		} else if (ascii>=97&&ascii<=102) {
			//ASCII code for a-f
			ascii-=87;			//Substract 87 so the integer value stays between 10-15
		} else {
			//Not a valid hexademical character, put 0
			ascii=0;
		}
		
		j=0;    					//Counter used for arrays
		
		while(ascii!= 1) {				//Continue until ascii == 1
			if(ascii==0) {				//If ascii is 0 put a zero and escape while loop
				binary_reverse[j] = '0';	
				break;
			}	
			if(ascii%2== 0) {  			//If ascii is divisible by 2 then put a zero
				binary_reverse[j] = '0';	
			}
			else if(ascii%2==1) {  			//If it isn't divisible by 2 then put a 1
				binary_reverse[j] = '1';   	
			}
			ascii /= 2;				//Find the quotient of ascii / 2
			j++;    				//Add 1 to j for next loop
		}
		
		if(ascii==1) {    				//When ascii is 1, we have to add 1 to the beginning
			binary_reverse[j] = '1';
			j++;
		}
		
		if(j<4) { 					//Add zeros to the end of string if not 4 characters (1/2 byte)
			for(;j<4;j++) {  			//Add until binary_reverse[4] (4th element)
				binary_reverse[j] = '0';
			}
		}
	
		for(k=0;k<4;k++) { 				//Our array is reversed. put the numbers in the right order (last comes first)
			binary[4*i+k] = binary_reverse[3-k];
		}	
	}

	binary[4*i]='\0';					//Set the end of the string
}


/*****************************************************************************
 * Name        : strbintobinstr
 * Description : Convert the binary string (one bit per byte) to 
                   one string where each bit is one value of the message
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *binary                   I  N/A  String with the binary values (one bit per byte)
 * int   binarylen                 I  N/A  Length of binary string
 * char  *bitstr                   O  N/A  String with the binary values (one bit per bit)
 * int   bitstrlen                 I  N/A  Length of bitstr string
 *****************************************************************************/
void strbintobinstr (char *binary, int binarylen, unsigned char *bitstr, int bitstrlen) {
	int i;
	int bit;
	
	//Initialize bitstr to 0
	for(i=0;i<bitstrlen;i++) {
		bitstr[i]=0x00;
	}

	for(i=0;i<binarylen;i++){
		if(binary[i]=='0') bit=0;
		else bit=1;
		bitstr[(int)(i/8)]+=bit<<(7-i%8);
	}
}

/*****************************************************************************
 * Name        : twocomplementstrbintointeger
 * Description : Convert a two complement binary value in string 
 *                 (one bit per byte) to an integer number
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char  *binary                   I  N/A  String with the binary values (one bit per byte)
 * int binarylen                   O  N/A  Length of binary string
 * Returned value (integer)        O  N/A  The integer value of two complement binary value
 *****************************************************************************/
int twocomplementstrbintointeger (char *binary, int binarylen) {
	int i;
	char *endptr;		//for strtol function
	char aux[250];		//string to put the complemented number (without the sign bit)

	if(binary[0]=='0') {	//Positive number
		return strtol(binary,&endptr,2);
	} else {		//Negative number
		for(i=1;i<binarylen;i++) {		//Loop for complementing all the bits except the sign bit
			if(binary[i]=='0') {
				aux[i-1]='1';
			} else {
				aux[i-1]='0';
			}
		}
		aux[i-1]='\0';	//Set the end of the string
		return -1*(1+strtol(aux,&endptr,2));
	}
}


/*****************************************************************************
 * Name        : checksumSBAS
 * Description : Compute CRC-24Q parity in SBAS message
 * Parameters  :
 * Name                           |Da|Unit|Description
 * unsigned char *msg              I  N/A  String with the binary values (one message bit per string bit)
 * Returned value (int)            O  N/A  Returns the value of the computed CRC
 *****************************************************************************/
int checksumSBAS (unsigned char *msg) {

	int key=0x1864CFB;						//25 bit polynomial for this CRC, with bits 0,1,3,4,5,6,7,10,11,14,17,18,23,24 equal to 1
	int chk=0;							//Contains the value of the checksum
	int pos=0;							//Indicates the bit number we are reading in the whole message (starting in bit 0)						
	int i;
	int maxpos=250;							//The total message is 250 bits long (including the CRC bits)
	int end=0;
	int position,shift;
	unsigned char aux[32];

	for (i=0;i<32;i++) aux[i]=0;					//Initialize aux to 0
	for (i=0;i<28;i++) aux[i]=*( (unsigned char *)(msg  + i));	//Copy first 224 bits of message to aux
	aux[28] = *( (unsigned char *)(msg  + 28)) & 0xC0;		//Copy last 2 bits of message to aux (which are the first two bits of aux[28]) (0xC0=11000000)
									//The data message is 224 bits, where CRC has to be computed. The rest of the bits of aux are 0
	while (!end) {
		while ((chk & 0x1000000)==0 && !end) {			//(chk & 0x1000000)==0 means bit 25 of chk equal to 0.  !end means to not have arrived to the end of the message (not arrived to bit 250)
									//This while is true while we don't arrive to the last bit or when bit 25 of chk (checksum) is not 0, which means
									//that our current value of chk has more than 24 bits, which is the maximum number for this CRC
				chk=chk<<1;					//Move chk one bit to the right (equivalent to multiply chk per 2)
			shift=7-(pos%8);				//shift indicates which bit in the current byte of the message we want to read (from right to left)
			position=1<<shift;				//position=2^shift. Position is the mask to apply in order to read the current bit (all the others bits in the byte will be 0)
			chk+=(aux[(int)(pos/8)] & position)>>shift;	//Select the current byte of the message, apply the mask and move the bit to the the least significant position,
									//(so the integer value is 0 or 1), and then add this value to chk
			pos++;						//pos indicates the current bit we are reading. Add 1 in order to read the next bit.
			if (pos==maxpos) end=1;				//If we have arrived to the last bit set end=1
			}
		if ((chk & 0x1000000)!=0) chk=chk^key;			//(chk & 0x1000000)!=0 means bit 25 of chk not equal 0 (bit 25=1). chk=chk^key means chk = chk XOR key
									//Doing this XOR, bit 25 will be 0 again, so the checksum will be 24 bits long. If we have not arrived to the end
									//of the message, we will continue reading bits and computing the checksum
	}

	return chk;
}

/*****************************************************************************
 * Name        : openSBASwritefiles
 * Description : Open all the files needed for writing the SBAS data
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  **fdlist                  O  N/A  Vector of file descriptors for writing data
 * char  **filelist                O  N/A  Name of the SBAS files that will be written
 * char  *fileread                 O  N/A  Name of the SBAS file that is going to be read
 * int sourcefile                  I  N/A  Indicates from what type file the SBAS data has been read.
 *                                          0 => RINEXB
 *                                          1 => EMS
 * TOptions  *options              I  N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         1  => Files opened properly or no files need to be opened
 *                                         0  => Problem reading EMS file when searching for year
 *                                         -1 => Problems opening EMS file when searching for year
 *****************************************************************************/
int openSBASwritefiles (FILE **fdlist, char **filelist, char *fileread, int sourcefile, TOptions  *options) {

	int				i;
	int 			len=0;
	int 			ret;
	int				doy;
	int				year,yearprev;
	int				GPSweek;
	double			SoW;
	double  		doyprev;
	TTime   		t,tprev;
	FILE			*fd;
	char   		 	line[MAX_INPUT_LINE];
	char 			aux[MAX_MESSAGE_STR];
	char			name[MAX_INPUT_LINE];
	char			fullname[MAX_INPUT_LINE];
	char			path[MAX_INPUT_LINE];
	char   			extensionlist[12][5]={".smt",".s00",".s01",".sfc",".s06",".s07",".s10",".s18",".ssc",".s26",".s27",".s28"};
	char 		  	*filepointer;
	struct 	stat 	path_stat;

	//Initialize filelist vector and file descriptor vector
	for(i=0;i<18;i++) {
		fdlist[i]=NULL;						//Set file descriptors to NULL
		filelist[i]=malloc(sizeof(char)*MAX_INPUT_LINE); 	//Allocate space for the filelist
		filelist[i][0]='\0';					//Set the filelist string to empty
	}

		//Check if any file has to be written.
		if (options->writeRinexBfile==0 && options->writeEMSfile==0 && options->writePegasusfile==0) return 1;
	
	//Check if output directory has a slash or backslash at the end, and if it has one, take it out.
	if(options->sbasdir[strlen(options->sbasdir)-1]=='/'||options->sbasdir[strlen(options->sbasdir)-1]=='\\') {
		options->sbasdir[strlen(options->sbasdir)-1]='\0';
	}

	//First we have to check if SBAS directory exists, where data will be saved
	//Create directory recursively if needed
	ret=mkdir_recursive(options->sbasdir);
	if(ret!=0) {
	   //Error when creating the directory, and it is not due to that the directory already exists
	   sprintf(aux,"When creating '%s' folder for writing SBAS data",options->sbasdir);
	   printError(aux,options);
	}
	//mkdir_recursive assumes the last part is a file, so it does not create a folder. Create it now
	#if !defined (__WIN32__)
			ret=mkdir(options->sbasdir,S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH); //Permission of the directory set to 755
	#else
			ret=mkdir(options->sbasdir);
	#endif
	if(ret!=0 && errno!=EEXIST) {
	   //Error when creating the directory, and it is not due to that the directory already exists
	   sprintf(aux,"When creating '%s' folder for writing SBAS data",options->sbasdir);
	   printError(aux,options);
	} else if (ret!=0 && errno==EEXIST) {
		//Check that what exists is a directory and not a file
		stat(options->sbasdir, &path_stat);
		if (!S_ISDIR(path_stat.st_mode)) {
		   return -1;
		}
	}
	//Save the path in path variable (Depending if it Windows or Linux it will have slash or backslash)
	strcpy(path,options->sbasdir);
	#if !defined (__WIN32__)
		   strcpy(&path[strlen(path)],"/");
	#else
		   strcpy(&path[strlen(path)],"\\");
	#endif
		

	//Extract the name of the file without the extension and the path
	#if defined (__WIN32__)
		filepointer=strrchr(fileread,'\\');
	#elif defined (__CYGWIN__)
		filepointer=strrchr(fileread,'/');
		//In cygwin, we may have linux or windows pathes
		if(filepointer==NULL) {
			filepointer=strrchr(fileread,'\\');
		}
	#else
		filepointer=strrchr(fileread,'/');
	#endif

	if (filepointer==NULL) {
		//There is no directory path in the file
		getstr(name,fileread,0,8);
		strcpy(fullname,fileread);
	} else {
		//There are directories in the path
		getstr(name,filepointer,1,8);
		strcpy(fullname,(char *)(filepointer+sizeof(char)));
	}
	//Check if a RINEX B file has to be written
	if(options->writeRinexBfile==1) {
		if(sourcefile==0) {
			//The data file is a RINEXB, the new file will have the same filename but with a ".v" at the end (v stands for verified)
			strcpy(filelist[fdRINEXB],path);		//Put path in filelist
			len=strlen(path);
			strcpy(&filelist[fdRINEXB][len],fullname);	//Put original name in filename
			len=strlen(filelist[fdRINEXB]);
			strcpy(&filelist[fdRINEXB][len],".v");		//Add the ".v" at the end of the filename
		} else {
			//The data file is a EMS file. We have to change the extension from ".ems" to ".yyb.v", being yy the year
			//To get the year, we have to read the first line of the EMS file
			if ((fd = fopen(fileread,"r"))) {
					if(getL(line,&len,fd)!=-1) {
					getstr(aux,line,4,2);
					year=atoi(aux);
					fclose(fd);
				} else {
					//Error reading EMS file
					return 0;
				}
			} else {
				//Error opening EMS file
				return -1;	
			}
			strcpy(filelist[fdRINEXB],path);		//Put path in filename
			len=strlen(path);
			strcpy(&filelist[fdRINEXB][len],name);		//Put original name (without extension) in filename
			len=strlen(filelist[fdRINEXB]);
			sprintf(aux,".%02db.v",year);
			strcpy(&filelist[fdRINEXB][len],aux);		//Add the ".v" at the end of the filename
		}
		fdlist[fdRINEXB]=fopen(filelist[fdRINEXB],"w");
		if (fdlist[fdRINEXB]==NULL) {
			//No need to close files here because this was the first one to be opened
			sprintf(aux,"When creating [%s] file for writing RINEX B file",filelist[fdRINEXB]);
			printError(aux,options);
		}
		
	}

	//Check if a EMS file has to be written
	if(options->writeEMSfile==1) {
		if(sourcefile==0) {
				//The data file is a RINEXB, the new file will have the same filename but with a ".v" at the end (v stands for verified)
				strcpy(filelist[fdEMS],path);			//Put path in filelist
				len=strlen(path);
				strcpy(&filelist[fdEMS][len],name);		//Put original name (without extension) in filename
				len=strlen(filelist[fdEMS]);
				strcpy(&filelist[fdEMS][len],".ems.v");		//Add the ".v" at the end of the filename
		} else {
				//The data file is a EMS file. The new file will have the extension ".ems.v" (v stands for verified)
				strcpy(filelist[fdEMS],path);			//Put path in filename
				len=strlen(path);
				strcpy(&filelist[fdEMS][len],fullname);		//Put original name in filename
				len=strlen(filelist[fdEMS]);
				strcpy(&filelist[fdEMS][len],".v");		//Add the ".v" at the end of the filename
		}
		fdlist[fdEMS]=fopen(filelist[fdEMS],"w");
		if (fdlist[fdEMS]==NULL) {
				closefiles(fdlist,1);	//Close all other files before exiting (The only one open will be the RINEX B file)
				sprintf(aux,"When creating [%s] file for writing EMS file",filelist[fdEMS]);
				printError(aux,options);
			}	
		}

	//Check if a Pegasus file has to be written
	if(options->writePegasusfile==1) {
		//Get DoY from filename
		getstr(aux,fullname,4,3);
		doy=atoi(aux);

		if(sourcefile==0) {
			//The data file is a RINEXB, we can extract the year directly from the filename
			getstr(aux,fullname,9,2);
			year=atoi(aux)+2000;
		} else {
			//The data file is a EMS file, we need to read the first line of the file to extract the time in order to get the year and the GPS week
			if ((fd = fopen(fileread,"r"))) {
				if(getL(line,&len,fd)!=-1) {
					getstr(aux,line,4,2);
					year=atoi(aux)+2000;
					fclose(fd);
				} else {
					//Error reading EMS file
					return 0;
				}
			} else {
				//Error opening EMS file
				return -1;	
			}
		}
		//We need to find the GPS Week from Year/DoY.
		t.SoD=0;				//The second of day will be 0 because we only need the week number for the filename
		t.MJDN=(int)yeardoy2MJDN(year,doy,t.SoD);	//First get the modified julian date
		ttime2gpswsnoroll(&t, &GPSweek, &SoW);	//Get the GPS Week number

		//Open SBAS Ephemeris file
		strcpy(filelist[fdEPHEMERIS],path);		//Put path in filename
		len=strlen(path);
		strcpy(&filelist[fdEPHEMERIS][len],name);	//Put original name (without extension) in filename
		len=strlen(filelist[fdEPHEMERIS]);
		sprintf(aux,"_BRDC%03d0.%02dH",doy,year%100);
		strcpy(&filelist[fdEPHEMERIS][len],aux);	//Add the _BRDCXXX0.YYH at the end of the filename
		fdlist[fdEPHEMERIS]=fopen(filelist[fdEPHEMERIS],"w");
		if (fdlist[fdEPHEMERIS]==NULL) {
			closefiles(fdlist,18);	//Close all other files before exiting
			sprintf(aux,"When creating [%s] file for writing BRDC Pegasus file",filelist[fdEPHEMERIS]);
			printError(aux,options);
		}

		//We need to find the year/doy from the previous day (taking into account leap years)
		tprev.MJDN=--t.MJDN;
		tprev.SoD=0;
		t2doy(&tprev,&yearprev,&doyprev);

		//Open SBAS Ephemeris file for previous day
		strcpy(filelist[fdEPHEMERISPREVDAY],path);		//Put path in filename
		len=strlen(path);
		strcpy(&filelist[fdEPHEMERISPREVDAY][len],name);	//Put original name (without extension) in filename
		len=strlen(filelist[fdEPHEMERISPREVDAY]);
		sprintf(aux,"_BRDC%03d0.%02dH",(int)doyprev,yearprev%100);
		strcpy(&filelist[fdEPHEMERISPREVDAY][len],aux);	//Add the _BRDCXXX0.YYH at the end of the filename
		fdlist[fdEPHEMERISPREVDAY]=fopen(filelist[fdEPHEMERISPREVDAY],"w");
		if (fdlist[fdEPHEMERISPREVDAY]==NULL) {
			closefiles(fdlist,18);	//Close all other files before exiting
			sprintf(aux,"When creating [%s] file for writing BRDC Pegasus file",filelist[fdEPHEMERISPREVDAY]);
			printError(aux,options);
		}

		//Open SBAS Almanac file
		strcpy(filelist[fdALMANAC],path);		//Put path in filename
		len=strlen(path);
		strcpy(&filelist[fdALMANAC][len],name);		//Put original name (without extension) in filename
		len=strlen(filelist[fdALMANAC]);
		sprintf(aux,"_GEO%04d.alm",GPSweek);
		strcpy(&filelist[fdALMANAC][len],aux);		//Add the _GEOYYYY.alm at the end of the filename (YYYY is the GPS Week)
		fdlist[fdALMANAC]=fopen(filelist[fdALMANAC],"w");
		if (fdlist[fdALMANAC]==NULL) {
			closefiles(fdlist,18);	//Close all other files before exiting
			sprintf(aux,"When creating [%s] file for writing Almanac Pegasus file",filelist[fdALMANAC]);
			printError(aux,options);
		}


		for(i=2;i<14;i++) {
			//Open the rest of the files. The extension for these files are fixed
			strcpy(filelist[i],path);		//Put path in filename
			len=strlen(path);
			strcpy(&filelist[i][len],name);		//Put original name (without extension) in filename
			len=strlen(filelist[i]);
			strcpy(&filelist[i][len],extensionlist[i-2]);		//Add the extension at the end of the filename
			fdlist[i]=fopen(filelist[i],"w");
			if (fdlist[i]==NULL) {
				closefiles(fdlist,18);	//Close all other files before exiting
				sprintf(aux,"When creating [%s] file for writing Pegasus files",filelist[i]);
				printError(aux,options);
			}
		}
	

	}

	//Open log file
	strcpy(filelist[fdLOGFILE],path);			//Put path in filename
	len=strlen(path);
	strcpy(&filelist[fdLOGFILE][len],fullname);		//Put original name in filename
	len=strlen(filelist[fdLOGFILE]);
	strcpy(&filelist[fdLOGFILE][len],".log");		//Add the ".log" at the end of the filename

	fdlist[fdLOGFILE]=fopen(filelist[fdLOGFILE],"w");
	if (fdlist[fdLOGFILE]==NULL) {
		closefiles(fdlist,18);	//Close all other files before exiting
		sprintf(aux,"When creating [%s] file for writing log file",filelist[fdLOGFILE]);
		printError(aux,options);
	}

	return 1;
}

/*****************************************************************************
 * Name        : closefiles
 * Description : Close all the files given in the file descriptor list
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  **fdlist                  IO N/A  Vector of file descriptors to be closed
 * int numfiles                    I  N/A  Number of files to be closed
 *****************************************************************************/
void closefiles (FILE  **fdlist, int numfiles) {

	int i;

	for(i=0;i<numfiles;i++) {
		if(fdlist[i]!=NULL) fclose(fdlist[i]);
	}
	
}

/*****************************************************************************
 * Name        : freeSBASblock
 * Description : Free memory sbasblock struct to avoid memory leak
 *               (each call to malloc needs its correspondent free call)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int  messagetype                I  N/A  Message type identifier number
 * TSBASblock  *sbasblock          O  N/A  TSBASblock struct
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void freeSBASblock (int messagetype,TSBASblock *sbasblock,TOptions  *options) {

	int i,num;

	switch(messagetype) {
		case(PRNMASKASSIGNMENTS):
			free(sbasblock->pos2PRN);
			free(sbasblock->pos2GNSS);
			for(i=0;i<MAX_GNSS;i++) {
				free(sbasblock->PRNactive[i]);
				free(sbasblock->PRN2pos[i]);
			}
			free(sbasblock->PRNactive);
			free(sbasblock->PRN2pos);
			break;
		case(DONTUSE):
			if(options->alarmmessageastype2==0) break;
		case(FASTCORRECTIONS2):case(FASTCORRECTIONS3):case(FASTCORRECTIONS4):case(FASTCORRECTIONS5):
			free(sbasblock->IODF);
			free(sbasblock->PRC);
			free(sbasblock->UDREI);
			free(sbasblock->UDRE);
			free(sbasblock->UDREsigma);
			break;
		case(INTEGRITYINFO):
			free(sbasblock->IODF);
			free(sbasblock->UDREIacu);
			free(sbasblock->UDREacu);
			free(sbasblock->UDREacusigma);
			break;
		case(FASTCORRECTIONSDEGRADATIONFACTOR):
			free(sbasblock->aiind);
			free(sbasblock->aifactor);
			free(sbasblock->timeoutintervalnonprecise);
			free(sbasblock->timeoutintervalprecise);
			free(sbasblock->fastcorrupdateinterval);
			break;
		case(DEGRADATIONPARAMETERS):
			free(sbasblock->degradationfactors);
			break;
		case(LONGTERMSATELLITECORRECTIONS):
			for(i=0;i<sbasblock->numlongtermsaterrcorrections;i++) {
				free(sbasblock->longtermsaterrcorrections[i]);
			}
			free(sbasblock->longtermsaterrcorrections);
			break;
		case(MIXEDFASTLONGTERMCORRECTIONS):
			free(sbasblock->IODF);
			free(sbasblock->PRC);
			free(sbasblock->UDREI);
			free(sbasblock->UDRE);
			free(sbasblock->UDREsigma);
			
			for(i=0;i<sbasblock->numlongtermsaterrcorrections;i++) {
				free(sbasblock->longtermsaterrcorrections[i]);
			}
			free(sbasblock->longtermsaterrcorrections);
			break;
		case(GEONAVIGATIONMESSAGE):
			free(sbasblock->geonavigationmessage);
			break;
		case(GEOSATELLITEALMANACS):
			if(sbasblock->numgeoalmanacs==0) num=1;
			else num=sbasblock->numgeoalmanacs;

			for(i=0;i<num;i++) {
				free(sbasblock->geoalmanacsmessage[i]);
			}
			free(sbasblock->geoalmanacsmessage);
			break;
		case(SBASSERVICEMESSAGE):
			if(sbasblock->numregioncoordinates==0) num=1;
			else num=sbasblock->numregioncoordinates;

			free(sbasblock->servicemessage);
			for(i=0;i<num;i++) {
				free(sbasblock->regioncoordinates[i]);
			}
			free(sbasblock->regioncoordinates);
			break;
		case(SBASNETWORKTIMEPARAMETERS):
			free(sbasblock->networktimemessage);
			break;
				case(CLOCKEPHEMERISCOVARIANCEMATRIX):
			if(sbasblock->numclockephemeriscovariance==0) num=1;
			else num=sbasblock->numclockephemeriscovariance;

						for(i=0;i<num;i++) {
								free(sbasblock->clockephemeriscovariance[i]);
						}			
						free(sbasblock->clockephemeriscovariance);
			break;
		case(IONOSPHERICGRIDPOINTSMASKS):
						free(sbasblock->igpmaskmessage);
			break;
		case(IONOSPHERICDELAYCORRECTIONS):
			for(i=0;i<15;i++) {
				free(sbasblock->ionodelayparameters[i]);
			}
			free(sbasblock->ionodelayparameters);
			break;
		default:
			break;
	}
}


/*****************************************************************************
 * Name        : SBASMissingMessageClearData
 * Description : When 4 or more consecutive messages are missed, all fast 
                 corrections data for all PRN have to be erased and UDREI set
                 14 (Don't Use)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int GEOindex                    I  N/A  Index of the GEO which had 4 or more missed messages
 * TSBASdata  *SBASdata            IO N/A  Struct to save SBAS data
 *****************************************************************************/
void SBASMissingMessageClearData (int GEOindex, TSBASdata  *SBASdata) {

	int i,j,k;

	//We have lost 4 or more consecutive messages
	//We have to assume that sigma UDRE for all satellites are set to "Not monitored". Thus, we have to erase all data from all satellites
	//Loop through all Masks
	for(i=0;i<5;i++) {
		//Loop through all SBAS fast corrections
		for(j=0;j<MAXSBASFASTCORR;j++) {
			//Loop for all satellites in mask
			for(k=0;k<51;k++) {
				SBASdata[GEOindex].poslastFC[i][k] = -1;
				SBASdata[GEOindex].numFC[i][k] = 0;
				SBASdata[GEOindex].PRC[i][j][k] = 9999;
				SBASdata[GEOindex].RRC[i][j][k] = 9999;
				SBASdata[GEOindex].UDRE[i][j][k] = -1;
				SBASdata[GEOindex].UDREsigma[i][j][k] = -1;
				SBASdata[GEOindex].IODF[i][j][k] = -1;
				SBASdata[GEOindex].lastfastcorrections[i][j][k].MJDN = -1;
				SBASdata[GEOindex].lastfastcorrections[i][j][k].SoD = -1;
				if (j==0 && i==0) {
					SBASdata[GEOindex].lastfastmessage[k]=-1;
					SBASdata[GEOindex].IODFintegrity[k]=-1;
					SBASdata[GEOindex].oldIODFintegrity[k]=-1;
					SBASdata[GEOindex].UDREI6[k]=-1;
					SBASdata[GEOindex].UDRE6[k]=-1;
					SBASdata[GEOindex].UDREsigma6[k]=-1;
					SBASdata[GEOindex].oldUDREI6[k]=-1;
					SBASdata[GEOindex].oldUDRE6[k]=-1;
					SBASdata[GEOindex].oldUDREsigma6[k]=-1;
					SBASdata[GEOindex].lastintegrityinfo[k].MJDN = -1;
					SBASdata[GEOindex].lastintegrityinfo[k].SoD = -1.;
					SBASdata[GEOindex].oldlastintegrityinfo[k].MJDN = -1;
					SBASdata[GEOindex].oldlastintegrityinfo[k].SoD = -1.;
				}

				if(i==SBASdata[GEOindex].IODPfastcorr) {
					SBASdata[GEOindex].useforbidden[SBASdata[GEOindex].pos2GNSS[i][k]][SBASdata[GEOindex].pos2PRN[i][k]]=14;
				}
			}
		}
	}
}		

/*****************************************************************************
 * Name        : SBASErrorMessageTimeoutFastCorr
 * Description : When 4 or more consecutive messages are wrong, we need to timeout
 *                the fast corrections (for PA only) for this GEO and set it as not
 *                monitored (not available for navigation).
 *                This behaviour is done by following the following rules in MOPS-D
 *
 *                2.1.1.4.9 Message Timeout Periods:
 *                  For approach LNAV/VNAV, LP, LPV when no valid SBAS message has been received
 *                  for 4 seconds (indicating a probable communications link problem or SBAS signal
 *                  blockage), all UDREI data from that SBAS satellite shall timeout
 *
 *                2.1.1.5.2 SBAS UNHEALTHY Designation
 *                  The equipment shall designate any GPS or SBAS satellite as SBAS UNHEALTHY upon
 *                  the occurrence of any of the following conditions:
 *                   a) The equipment has successfully decoded a UDREI of 15, indicating that the
 *                      SBAS has assessed the satellite’s signal as unusable;
 *                   b) The step detection function has declared a step error;
 *                   c) For SBAS satellites, URA index is 15 or higher; or
 *                   d) For SBAS satellites, failure of parity on 4 successive messages.
 *                   
 *                 The SBAS UNHEALTHY status for that satellite shall be changed only after the
 *                 condition has cleared (including time-out of UDREI data) and none of the above
 *                 conditions exist. When an SBAS satellite is designated as UNHEALTHY due to any one
 *                 of the above conditions, the integrity and correction data can continue to be applied.
 *                
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int GEOindex                    I  N/A  Index of the GEO which had 4 or more missed messages
 * TTime *currentepoch             I  N/A  Current epoch
 * TSBASdata  *SBASdata            IO N/A  Struct to save SBAS data
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void SBASErrorMessageTimeoutFastCorr (int GEOindex, TTime *currentepoch, TSBASdata  *SBASdata, TOptions  *options) {
	int		i,j,k,l;
	double	timediffMsg,timediffTimeOut;
	double	UDREItmout;

	//UDREI data hast to timeout only on PA mode, so the reception time of the fast corrections will set just in the epoch where
	//they are already timed out
	UDREItmout=(double)(SBASdata[GEOindex].timeoutmessages[PAMODE][INTEGRITYINFO]);

	//Forced timeout of UDREI data is only for PA, so if user forced NPA mode do nothing
	if (options->UserForcedNPA==0) {
		//Loop through all Masks
		for(i=0;i<5;i++) {
			//Loop through all SBAS fast corrections
			for(j=0;j<MAXSBASFASTCORR;j++) {
				//Loop for all satellites in mask
				for(k=0;k<51;k++) {
					if (SBASdata[GEOindex].lastfastcorrections[i][j][k].MJDN!=-1) {
						timediffMsg=tdiff(currentepoch,&SBASdata[GEOindex].lastfastcorrections[i][j][k]);
						timediffTimeOut=timediffMsg-UDREItmout;
						if (timediffTimeOut<=1E-4) { //The 1E-4 is to avoid problems with decimals
							//UDRE data not timed out. Change the message reception time so during the modelling
							//process all UDRE data is timed out
							//The .1 second is to make message reception be one tenth of a second behind of the timeout (so for 0.1 data rate files they also timeout)
							SBASdata[GEOindex].lastfastcorrections[i][j][k]=tdadd(&SBASdata[GEOindex].lastfastcorrections[i][j][k],timediffTimeOut-.1);
						}//If data is timed out, leave the reception time as it is
					}
				}
			}
		}
	}
	//Set GEO to do not use (not available for ranging)
	if (GEOindex==0) {
		//If it is the mixed GEO, we need to set all GEOs to do not use (not available for ranging)
		for(l=1;l<=SBASdata[0].numSBASsatellites;l++) { //Loop through all GEOs
			SBASdata[GEOindex].useforbidden[GEO][SBASdata[l].PRN]=15;
		}
	} else {
		SBASdata[GEOindex].useforbidden[GEO][SBASdata[GEOindex].PRN]=15;
	}
}

/*****************************************************************************
 * Name        : SBAShandlespecialevents
 * Description : If we have decimation greater than one second, we still need 
 *                to handle special events every second such as alarm messages,
 *                or UDREI=15. This option is called only on decimated epochs,
 *                otherwise these events are already handled at computeSBAS function
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TTime currentepoch              I  N/A  Current epoch
 * TSBASdata  *SBASdata            IO N/A  Struct to save SBAS data
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void SBAShandlespecialevents (TTime currentepoch, TSBASdata  *SBASdata, TOptions  *options) {

	int						i,j,k;
	int						auxGEOPRN,UDREI,IODP,IODPfastcorr,posFC;
	double 					difftime,difftime2;
	unsigned int			nearestInt;
	static unsigned int		initialized=0;
	static unsigned int		Decimateval;
	TTime   				tudre;
	
	if (initialized==0) {
		Decimateval = (int)(options->decimate*10000.);
		initialized=1;
	}
	
	//Check if this epoch is decimated
	if (options->decimate==0.) return;
	else {
		nearestInt = (int)(currentepoch.SoD*10000.);
		if ( (nearestInt%Decimateval) == 0 ) return;
	}

	//Check if we have received a type 0 message
	if(options->usetype0messages==1 && SBASdata[0].dontuse==1) {
		//We have received a type 0 messages and we are treating it as it is, or
		//we are treating type 0 messages as type 2, but we have received a type 0 message will all zeros (0)
		//In this case, we need to erase all data from the current GEO (if we use mixed data, we will also erase the mixed data)

		//Check for the position in the SBASdata for the GEO from which we received the type 0 message
		i=SBASdata[0].GEOPRN2pos[SBASdata[0].alarmGEOPRN];

		//Check if we have cleared the data from the GEO
		if(SBASdata[0].cleared==0) {
			SBASdata[0].cleared=1;
			//Erase all data from this GEO except for almanac data
			ClearSBASdata(SBASdata,i);
			//Clear also the mixed data (as we cannot separate the valid from the unvalid data, we have to erase everything)
			ClearSBASdata(SBASdata,0);
		}

		//When we receive a type 0 message, we have to wait for one minute until we can use it again
		difftime=tdiff(&currentepoch,&SBASdata[i].lastmsgreceived[DONTUSE]);
		if((1-(difftime-(int)difftime))<1E-4) difftime=(int)difftime+1; //This is to account for problems when converting to integer, when a number is 1.99999998
		if((int)difftime>=59) {
			//When there is one second left, we clear the alarm condition and then skip processing
			SBASdata[i].dontuse=0;
			SBASdata[0].dontuse=0;
			SBASdata[0].cleared=0;
			SBASdata[0].alarmGEOPRN=0;
			SBASdata[i].problems=0;
			SBASdata[0].problems=0;
		}

		//Check if we have received an alarm message from another GEO satellite
		if(SBASdata[0].secondalarmGEOPRN!=0) {
			j=SBASdata[0].GEOPRN2pos[SBASdata[0].secondalarmGEOPRN];
			difftime2=tdiff(&currentepoch,&SBASdata[j].lastmsgreceived[DONTUSE]);
			if((1-(difftime2-(int)difftime2))<1E-4) difftime2=(int)difftime2+1; //This is to account for problems when converting to integer, when a number is 1.99999998
			if((int)difftime2>=59) {
				//When there is one second left, we clear the alarm condition for the second GEO with alarm
				SBASdata[j].dontuse=0;
				SBASdata[j].cleared=0;
				SBASdata[j].problems=0;
				SBASdata[0].secondalarmGEOPRN=0;
			} else {
				//Received an alarm from another GEO. Update alarm GEO PRN. In the next epoch it will be cleared
				auxGEOPRN=SBASdata[0].alarmGEOPRN;
				SBASdata[0].alarmGEOPRN=SBASdata[0].secondalarmGEOPRN;
				SBASdata[0].secondalarmGEOPRN=auxGEOPRN;
				SBASdata[0].dontuse=1;
			}
		}

	}

	//Next conditions will be done if we have selected a GEO PRN
	if(options->GEOindex>=0) {

		//Select IODP
		if(SBASdata[options->GEOindex].IODPfastcorr==-1) return; //No IODP available. Nothing else can be checked
		IODPfastcorr=SBASdata[options->GEOindex].IODPfastcorr; //IODPfastcorr is the IODP for current mask, which will be the same for all the for loop
		//Check for UDREI=14 or UDREI=15
		for(i=0;i<SBASdata[options->GEOindex].numsatellites[IODPfastcorr];i++) {
			IODP=SBASdata[options->GEOindex].IODPfastcorr; //We have to save again the IODP because in any satellite we may use the IODP for the current or the previous mask
			posFC=SBASdata[options->GEOindex].poslastFC[IODP][i];
			if (posFC==-1) {
				//No data in current mask, try previous
				IODP=SBASdata[options->GEOindex].oldIODPfastcorr;
				posFC=SBASdata[options->GEOindex].poslastFC[IODP][i];
				if (posFC==-1) {
					//No data for this satelllite
					continue;
				}
			}

			UDREI=0;
			if(SBASdata[options->GEOindex].lastfastmessage[i]==INTEGRITYINFO) {
				//Last fast correction data received is from message type 6
				if(SBASdata[options->GEOindex].IODFintegrity[i]==3) {
					//Alarm. Use IODF from message type 6 regardles of other IODF
					if(SBASdata[options->GEOindex].UDREI6[i]>=14) UDREI=SBASdata[options->GEOindex].UDREI6[i];
				} else if (SBASdata[options->GEOindex].IODFintegrity[i]!=SBASdata[options->GEOindex].IODF[IODP][posFC][i]) {
					//IODF from message type 6 does not match the IODF from messages type 2-5,24 and IODF!=3
					//We cannot use the UDREsigma from message type 6, so we keep using the last one from messages type 2-5,24
					if(SBASdata[options->GEOindex].UDREI[IODP][posFC][i]>=14) UDREI=SBASdata[options->GEOindex].UDREI[IODP][posFC][i];
				} else {
					if(SBASdata[options->GEOindex].UDREI6[i]>=14) UDREI=SBASdata[options->GEOindex].UDREI6[i];
				}
				tudre=SBASdata[options->GEOindex].lastintegrityinfo[i];
			} else {
				//Last fast correction data received is from message type is from type 2-5,24
				if(SBASdata[options->GEOindex].UDREI[IODP][posFC][i]>=14) UDREI=SBASdata[options->GEOindex].UDREI[IODP][posFC][i];
				tudre=SBASdata[options->GEOindex].lastfastcorrections[IODP][posFC][i];
			}
			//Check UDREI has not timed out
			difftime=tdiff(&currentepoch,&tudre);
			if(difftime<=(double)(SBASdata[options->GEOindex].timeoutmessages[options->precisionapproach][INTEGRITYINFO])) {
				//UDRE not timed out. 
				if(UDREI>=14) {
					//We have received an UDREI=14 or UDREI=15. We need to erase all the data
					for(k=0;k<5;k++) {
						SBASdata[options->GEOindex].poslastFC[k][i] = -1;
						SBASdata[options->GEOindex].numFC[k][i] = 0;
						if(k==SBASdata[options->GEOindex].IODPfastcorr) {
							SBASdata[options->GEOindex].useforbidden[SBASdata[options->GEOindex].pos2GNSS[k][i]][SBASdata[options->GEOindex].pos2PRN[k][i]]=UDREI;
						}
						for(j=0;j<MAXSBASFASTCORR;j++) {
							SBASdata[options->GEOindex].PRC[k][j][i] = 9999;
							SBASdata[options->GEOindex].RRC[k][j][i] = 9999;
							SBASdata[options->GEOindex].UDREI[k][j][i] = -1;
							SBASdata[options->GEOindex].UDRE[k][j][i] = -1;
							SBASdata[options->GEOindex].UDREsigma[k][j][i] = -1;
							SBASdata[options->GEOindex].IODF[k][j][i] = -1;
							SBASdata[options->GEOindex].lastfastcorrections[k][j][i].MJDN = -1;
							SBASdata[options->GEOindex].lastfastcorrections[k][j][i].SoD = -1;
						}
					}
				} else {
					k=SBASdata[options->GEOindex].IODPfastcorr;
					if (SBASdata[options->GEOindex].useforbidden[SBASdata[options->GEOindex].pos2GNSS[k][i]][SBASdata[options->GEOindex].pos2PRN[k][i]]>=14) {
						//We have received UDREI<=13, we need to clear the useforbidden if it was active
						SBASdata[options->GEOindex].useforbidden[SBASdata[options->GEOindex].pos2GNSS[k][i]][SBASdata[options->GEOindex].pos2PRN[k][i]]=0;
					}
				}
			}
		}
	}
	return;

}

/*****************************************************************************
 * Name        : IGP2latlon
 * Description : Given an IGP in a band number in the SBAS iono grid, compute
 *                its latitude and longitude (for SBAS iono)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * int bandnumber                  I  N/A  Band number (0-10)
 * int IGP                         I  N/A  IGP number (0-200)
 * int *IGPlat                     O  º    Latitude of the IGP (-90º..90º)
 * int *IGPlon                     O  º    Longitude of the IGP (-180º..180º)
 * Returned value (int)            O  N/A  1 => IGP in map
 *                                         0 => IGP not in map
 *****************************************************************************/
int IGP2latlon (int bandnumber, int IGP, int *IGPlat, int *IGPlon) {

	int 	dlon=0;

	IGP++;

	if (bandnumber<=8) {

		if (bandnumber==0) {
			dlon=-160;
			if (IGP==28) {
				*IGPlon=-180;
				*IGPlat=85;
			} else if((IGP>=29) && (IGP<=128)) {
				IGP=IGP-1;
			}
		}                                                        


		if (bandnumber==1) {
			dlon=-120;
			if (IGP==1) {
				*IGPlon=-140;
				*IGPlat=-85;
			} else if((IGP>=2) && (IGP<=128)) {
				IGP=IGP-1;
			}
		}                                                   


		if (bandnumber==2) {
			dlon=-80;
			if (IGP==78) {
				*IGPlon=-90;
				*IGPlat=85;
			} else if((IGP>=79) && (IGP<=128)) {
				IGP=IGP-1;
			}
		}                                                    


		if (bandnumber==3) {  
			dlon=-40;
			if (IGP==51) {
				*IGPlon=-10;
				*IGPlat=-85;
			} else if((IGP>=52) && (IGP<=128)) {     
				IGP=IGP-1;
			}
		}

		if (bandnumber==4) {
			dlon=0;
		}                                

		if (bandnumber==5) {
			dlon=40;
			if (IGP==101) {
				*IGPlon=-10;
				*IGPlat=-85;
			} else if((IGP>=102) && (IGP<=128)) {
				IGP=IGP-1;
			}
		}  

		if (bandnumber==6) {
			dlon=80;
			if (IGP==178) {
				*IGPlon=-10;
				*IGPlat=85;
			} else if((IGP>=128) && (IGP<=177)) {
				IGP=IGP+1;
			}
		}   

		if (bandnumber==7) {
			dlon=120;
			if (IGP==151) {
				*IGPlon=130;
				*IGPlat=-85;
			} else if((IGP>=128) && (IGP<=150)) {
				IGP=IGP+1;
			}
		}                                                         

		if (bandnumber==8) {
			dlon=160;
			if(IGP>=128) {
				IGP=IGP+1;
			}
		}                                                     

		if ((IGP<1) || (IGP>201)) {
			*IGPlon=9999;
			*IGPlat=9999;
			return 0;
		}                                                                                                                                           

	//       ...........................
		if(IGP==1) {
			*IGPlon=-20;
			*IGPlat=-75;
		} else if(IGP==2) { 
			*IGPlon=-20;
			*IGPlat=-65;
		} else if(IGP<=25) {
			*IGPlon=-20;
			*IGPlat=-55+5*(IGP-3);      
		} else if(IGP==26) {
			*IGPlon=-20;
			*IGPlat=65;
		} else if(IGP==27) {
			*IGPlon=-20;
			*IGPlat=75;                      
	//         ...........................
		} else if(IGP<=50) {
			*IGPlon=-15;
			*IGPlat=-55+5*(IGP-28);
	//         ...........................
		} else if(IGP==51) {
			*IGPlon=-10;
			*IGPlat=-75;                  
		} else if(IGP==52) {
			*IGPlon=-10;
			*IGPlat=-65;                  
		} else if(IGP<=75) {
			*IGPlon=-10;
			*IGPlat=-55+5*(IGP-53);
		} else if(IGP==76) {
			*IGPlon=-10;
			*IGPlat=65;
		} else if(IGP==77) {
			*IGPlon=-10;
			*IGPlat=75;
	//         ...........................                                                  
		} else if(IGP<=100) {
			*IGPlon=-5;
			*IGPlat=-55+5*(IGP-78);
	//         ...........................     
		} else if(IGP==101) {
			*IGPlon=0;
			*IGPlat=-75;
		} else if(IGP==102) {
			*IGPlon=0;
			*IGPlat=-65;
		} else if(IGP<=125) {
			*IGPlon=0;
			*IGPlat=-55+5*(IGP-103);
		} else if(IGP==126) {
			*IGPlon=0;
			*IGPlat=65;
		} else if(IGP==127) {
			*IGPlon=0;
			*IGPlat=75;
		} else if(IGP==128) {
			*IGPlon=0;
			*IGPlat=85;                      
	//         ...........................                      
		} else if(IGP<=151) {
			*IGPlon=5;
			*IGPlat=-55+5*(IGP-129);
	//         ...........................
		} else if(IGP==152) {
			*IGPlon=10;
			*IGPlat=-75;
		} else if(IGP==153) {
			*IGPlon=10;
			*IGPlat=-65;
		} else if(IGP<=176) {
			*IGPlon=10;
			*IGPlat=-55+5*(IGP-154);
		} else if(IGP==177) {
			*IGPlon=10;
			*IGPlat=65;
		} else if(IGP==178) {
			*IGPlon=10;
			*IGPlat=75;
	//         ...........................
		} else if(IGP<=201) {
			*IGPlon=15;
			*IGPlat=-55+5*(IGP-179);
	//       ...........................                        
		}
		*IGPlon=*IGPlon+dlon;

	//       ------------- Bands 9 and 10 -----------------
	} else if (bandnumber>=9) {
		if ((IGP>=1) && (IGP<37)) {
			*IGPlat=60;
			*IGPlon=(IGP-1)*5-180;
		} else if ((IGP>=37) && (IGP<73)) {
			*IGPlat=60;
			*IGPlon=(IGP-37)*5;
		} else if ((IGP>=73) && (IGP<91)) {
			*IGPlat=65;
			*IGPlon=(IGP-73)*10-180;
		} else if ((IGP>=91) && (IGP<109)) {
			*IGPlat=65;
			*IGPlon=(IGP-91)*10;
		} else if ((IGP>=109) && (IGP<127)) {
			*IGPlat=70;
			*IGPlon=(IGP-109)*10-180;
		} else if ((IGP>=127) && (IGP<145)) {
			*IGPlat=70;
			*IGPlon=(IGP-127)*10;
		} else if ((IGP>=145) && (IGP<163)) {
			*IGPlat=75;
			*IGPlon=(IGP-145)*10-180;
		} else if ((IGP>=163) && (IGP<181)) {
			 *IGPlat=75;
			 *IGPlon=(IGP-163)*10;
		} else if ((IGP>=181) && (IGP<187)) {
			*IGPlat=85;
			*IGPlon=(IGP-181)*30-180;
		} else if ((IGP>=187) && (IGP<=192)) {
			*IGPlat=85;
			*IGPlon=(IGP-187)*30;
		} else {
			*IGPlat=9999;
			*IGPlon=9999;
			return 0;
		}


		if (bandnumber==10) {
			*IGPlat=-*IGPlat;
			if (IGP>=181) *IGPlon=*IGPlon+10;
		}

	}
	return 1;
}

/*****************************************************************************
 * Name        : IPP2Sqr
 * Description : Given the latitude and longitude of an IPP, compute the left
 *               down corner (number 3) latitude and longitude IGP involved in the IPP 
 *               interpolation and the increment for the other corners (for SBAS iono)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double IPPlat                   I  º    Latitude of the IPP (-90º..90º)
 * double IPPlon                   I  º    Longitude of the IPP (-180º..180º or 0º..360º)
 * double *IGPlat                  O  º    Latitude of the left-down corner IGP (-90º..90º)
 * double *IGPlon                  O  º    Longitude of the left-down corner IGP (0º..360º)
 * double *increment               O  º    Distance to the IGP in the other corners (in degrees)
 * Returned value (int)            O  N/A  1 => Valid IGP
 *                                         0 => IGP not in map
 *****************************************************************************/

int IPP2Sqr (double IPPlat, double IPPlon, double *IGPlat, double *IGPlon, double *increment) {
 
	/*

	2-----1         3: (*IGPlat,*IGPlon)
	|     |         2: (*IGPlat,*IGPlon+*increment)
	| IPP |         4: (*IGPlat+*increment,*IGPlon)
	3-----4         1: (*IGPlat+*increment,*IGPlon+*increment)

	NOTE: when |IPPlat|>85 deg, *IGPlon is the longitude of the closest IGP to the west of the IPP*/

	double	difflat, tmplon=0.;
 

	//Compute the IGP for |IGPlat|>80. 
	//We look for the IGP closest to the west of the IPP
	
	if ((IPPlat>=85.)||(IPPlat<-85.)) {     

		*increment=0;

		*IGPlon=modulo(IPPlon+360,360);

		if (IPPlat>=85.) {  
			*IGPlat=85;
			if (*IGPlon<360) tmplon=270;
			if (*IGPlon<270) tmplon=180;
			if (*IGPlon<180) tmplon=90;
			if (*IGPlon<90)  tmplon=0;
			if (*IGPlon<0) return 0;

		} else if (IPPlat<-85.) {      

			*IGPlat=-85.;
			if (*IGPlon<310) tmplon=220;
			if (*IGPlon<220) tmplon=130;
			if (*IGPlon<130) tmplon=40;
			if (*IGPlon<40)  tmplon=310;
			if (*IGPlon<=360) tmplon=310;
			if (*IGPlon<0) return 0;
		}  

		*IGPlon=tmplon;
	   
	} else {

		//Compute the IGP in the other cases.
		*increment=10;
		difflat=5;
		if ((IPPlat>=-60.) && (IPPlat<60.)) {
			*increment=5;
			difflat=0;
		}
	 
		*IGPlon=IPPlon+360;
		*IGPlon=modulo(*IGPlon,360);
		*IGPlon=(int)(*IGPlon/(*increment))*(*increment);
	 
		*IGPlat=IPPlat+360-difflat;
		*IGPlat=modulo(*IGPlat,360);
		*IGPlat=(int)(*IGPlat/(*increment))*(*increment)+difflat;
		if (*IGPlat>180.) *IGPlat=*IGPlat-360;

	}

	return 1;
}

/*****************************************************************************
 * Name        : IGPLatLon2BandNumberIGP
 * Description : Given the latitude and longitude of an IGP, compute the 
 *                band number and IGP for bands 0-8 and bands 9-10 (for SBAS iono)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double IGPlat                   I  º    Latitude of the IGP (-90º..90º)
 * double IGPlon                   I  º    Longitude of the IGP (0º..360º)
 * int *Bandnumber                 O  N/A  Band number (0-10)
 * int *IGP                        O  N/A  IGP number for bands 0-8 (1-201)
 * int *IGP90                      O  N/A  IGP number for bands 9-10 (1-192)
 * Returned value (int)            O  N/A  1 => IGP found
 *                                         0 => IGP not in map
 *****************************************************************************/
int IGPLatLon2BandNumberIGP (double IGPlat, double IGPlon, int *Bandnumber, int *IGP, int *IGP90) {
 
	//-------------------------------------------------------
	//This subroutine computes the Bandnumber and IGP from the longitude (IGPlon) and latitude (IGPlat) of IGP.
	//The subroutine also checks if (IGPlat,IGPlon) corresponds to a valid IGP.


	//INPUT:
	//*IGP coordinates (IGPlat,IGPlon)


	//OUTPUT:
	//*Bandnumber= Band Number
	//*IGP= IGP in band
	//*IGP90= IGP in band 9 or 10

	//NOTE 1: The same IGP can belong to Bandnumber=0 to 8 and at the same time to Bandnumber=9.
	//In this case, the routine provides both, [*Bandnumber][*IGP] and *IGP90.

	//If IGP90=0, thence, the IGP does not belong to Band 9 nor 10.

	//........................................................

	double 	templon,templon2,templat,templat2,xx,yy;
	int 	nlon,nlat,lonstep,latstep,m;
 
 
	*Bandnumber=0;
	*IGP=0;
	*IGP90=0;

	//IGP check -------------------------------------------

	//Compute the corresponding IGP

	if (fabs(IGPlat)>75) {
		//Latitude over 75º or below -75º
		templon=modulo(IGPlon+360,360);
		nlon=(int)round(templon);
		if (IGPlat==85.0) {  
			//IGPlat equal to 85º
			if (nlon==180) {
				*Bandnumber=0;
				*IGP=28;
				*IGP90=181;
			} else if (nlon==270) {  
				*Bandnumber=2;
				*IGP=78;
				*IGP90=184;
			} else if (nlon==0) {      
				*Bandnumber=4;
				*IGP=128;
				*IGP90=187;
			} else if (nlon==90) {      
				*Bandnumber=6;
				*IGP=178;
				*IGP90=190;
			} else if (nlon==210) {
				*IGP90=182;
			} else if (nlon==240) {
				*IGP90=183;
			} else if (nlon==300) {
				*IGP90=185;
			} else if (nlon==330) {
				*IGP90=186;
			} else if (nlon==30) {
				*IGP90=188;
			} else if (nlon==60) {
				*IGP90=189;
			} else if (nlon==120) {
				*IGP90=191;
			} else if (nlon==150) {
				*IGP90=192;
			}
			return 1;
		} else if (IGPlat==-85.0) {
			//IGPlat equal to -85º
			if (nlon==220) {
				*Bandnumber=1;
				*IGP=1;
				*IGP90=182;
			} else if (nlon==310) {
				*Bandnumber=3;
				*IGP=51;
				*IGP90=185;
			} else if (nlon==40) {
				*Bandnumber=5;
				*IGP=101;
				*IGP90=188;
			} else if (nlon==130) {
				*Bandnumber=7;
				*IGP=151;
				*IGP90=191;
			} else if (nlon==190) {
				*IGP90=181;
			} else if (nlon==250) {
				*IGP90=183;
			} else if (nlon==280) {
				*IGP90=184;
			} else if (nlon==340) {
				*IGP90=186;
			} else if (nlon==10) {
				*IGP90=187;
			} else if (nlon==70) {
				*IGP90=189;
			} else if (nlon==100) {
				*IGP90=190;
			} else if (nlon==160) {
				*IGP90=192;
			}
			return 1;
		} else { 
			//IGPlat over 85º or below -85º
			return 0;
		}
	}


	//Checking IGPlat: [-75:75]
	//Note: we include IGPlat=+/-60 because, at this latitude, there are IGPs every 5 Deg (we need just to decide if it is IGP or not). 
	//If we need to find the left-down corner, we should exclude IGPlat=+/-60 (i.e., to put "</>" instead of "<=/>=" in the condition "if").

	if ((IGPlat>=-60.0)&&(IGPlat<=60.0)) {
		lonstep=5;
		latstep=5;
	} else {
		lonstep=10;
		latstep=5;
	}
 

	templon=modulo(IGPlon+360,360);
	templon=(int)(templon/lonstep)*lonstep;
	nlon=(int)round(templon);
 
	templat=modulo(IGPlat+360,360);
	templat=(int)(templat/latstep)*latstep;
	nlat=(int)round(templat);
	if (nlat>180) nlat=nlat-360;

	//Map to the interval [0:360]    
	templon2=modulo(IGPlon+360,360);
	templat2=modulo(IGPlat+360,360);
 
	//Comparing to check if it is a IGP
	xx=fabs(templon2-templon);
	yy=fabs(templat2-templat);
 
	if ((xx>0)||(yy>0)) {
		return 0;
	}

	//----------------------------------------------------

	if (nlon<20) {
		*Bandnumber=4;
		m=(nlon+20)/5;
	} else if (nlon<60) {
		*Bandnumber=5;
		m=(nlon-20)/5;
	} else if (nlon<100) {
		*Bandnumber=6;
		m=(nlon-60)/5;
	} else if (nlon<140) {
		*Bandnumber=7;
		m=(nlon-100)/5;
	} else if (nlon<180) {
		*Bandnumber=8;
		m=(nlon-140)/5;
	} else if (nlon<220) {
		*Bandnumber=0;
		m=(nlon-180)/5;
	} else if (nlon<260) {
		*Bandnumber=1;
		m=(nlon-220)/5;
	} else if (nlon<300) {
		*Bandnumber=2;
		m=(nlon-260)/5;
	} else if (nlon<340) {
		*Bandnumber=3;
		m=(nlon-300)/5;
	//} else if (nlon<=360) {
	} else {
		*Bandnumber=4;
		m=(nlon-340)/5;
	}
 
	if (m==0) {
		if (nlat==-75) {
			*IGP=1;
		} else if (nlat==-65) {
			*IGP=2;
		} else if (nlat==65) {
			*IGP=26;
		} else if (nlat==75) {
			*IGP=27;
		} else if ((nlat>=-55)&&(nlat<=55)) {
			*IGP=(nlat+55)/5+3;
		}
	} else if (m==1) {
		*IGP=(nlat+55)/5+28;
	} else if (m==2) {
		if (nlat==-75) {
			*IGP=51;
		} else if (nlat==-65) {
			*IGP=52;
		} else if (nlat==65) {
			*IGP=76;
		} else if (nlat==75) {
			*IGP=77;
		} else if ((nlat>=-55)&&(nlat<=55)) {
			*IGP=(nlat+55)/5+53;
		}
	} else if (m==3) {
		*IGP=(nlat+55)/5+78;
	} else if (m==4) {
		if (nlat==-75) {
			*IGP=101;
		} else if (nlat==-65) {
			*IGP=102;
		} else if (nlat==65) {
			*IGP=126;
		} else if (nlat==75) {
			*IGP=127;
		} else if (nlat==85) {
			*IGP=128;
		} else if ((nlat>=-55)&&(nlat<=55)) {
			*IGP=(nlat+55)/5+103;
		}
	} else if (m==5) {
		 *IGP=(nlat+55)/5+129;
	} else if (m==6) {
		if (nlat==-75) {
			*IGP=152;
		} else if (nlat==-65) {
			*IGP=153;
		} else if (nlat==65) {
			*IGP=177;
		} else if (nlat==75) {
			*IGP=178;
		} else if ((nlat>=-55)&&(nlat<=55)) {
			*IGP=(nlat+55)/5+154;
		}
	} else if (m==7) { 
		*IGP=(nlat+55)/5+179;
	}
	if (*Bandnumber==0) {
		if ((*IGP>=28)&&(*IGP<=128)) *IGP=*IGP+1;
		if ((m==0)&&(nlat==85)) *IGP=28;
	} else if (*Bandnumber==1) {
		if ((*IGP>=1)&&(*IGP<=128)) *IGP=*IGP+1;
		if ((m==0)&&(nlat==-85)) *IGP=1;
	} else if (*Bandnumber==2) {
		if ((*IGP>=78)&&(*IGP<=128)) *IGP=*IGP+1;
		if ((m==2)&&(nlat==85)) *IGP=78;
	} else if (*Bandnumber==3) {
		if ((*IGP>=51)&&(*IGP<=128)) *IGP=*IGP+1;
		if ((m==2)&&(nlat==-85)) *IGP=51;
	} else if (*Bandnumber==5) {
		if ((*IGP>=101)&&(*IGP<=128)) *IGP=*IGP+1;
		if ((m==4)&&(nlat==-85)) *IGP=101;
	} else if (*Bandnumber==6) {
		if ((*IGP>=128)&&(*IGP<=178)) *IGP=*IGP-1;
		if ((m==6)&&(nlat==85)) *IGP=178;
	} else if (*Bandnumber==7) {
		if ((*IGP>=128)&&(*IGP<=151)) *IGP=*IGP-1;
		if ((m==6)&&(nlat==-85)) *IGP=151;
	} else if (*Bandnumber==8) {
		if (*IGP>=128) *IGP=*IGP-1;
	}

	//New IONO bands 9 and 10: -----------------
	if ((nlat==60)||(nlat==-60)) {
		if (nlon>=180) {
			*IGP90=(nlon-180)/5+1;
		} else {
			*IGP90=(nlon+180)/5+1;
		}
	} else if ((nlat==65)||(nlat==-65)) {
		if (nlon>=180) {
			*IGP90=(nlon-180)/10+73;
		} else {
			*IGP90=(nlon+180)/10+73;
		}
	} else if ((nlat==70)||(nlat==-70)) {
		if (nlon>=180) {
			*IGP90=(nlon-180)/10+109;
		} else {
			*IGP90=(nlon+180)/10+109;
		}
	} else if ((nlat==75)||(nlat==-75)) {
		if (nlon>=180) {
			*IGP90=(nlon-180)/10+145;
		} else {
			*IGP90=(nlon+180)/10+145;
		}
	}
	//------------------------------------------

	if (*IGP+*IGP90<=0) {
		return 0;	
	}

	return 1;
}

/*****************************************************************************
 * Name        : IGPsearch
 * Description : Given the latitude and longitude of an IPP, the coordinates 
 *               of the left down corner IGP and the latitude and longitude
 *               increment (so as to define a region of IGP ), gather the number 
 *               in mask of the four IGP and check if a interpolation can be done
 *               (over a square or a triangle) (for SBAS iono)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double IPPlat                   I  º    Latitude of the IPP (-90º..90º)
 * double IPPlon                   I  º    Longitude of the IPP (-180º..180º or 0º..360º)
 * double IGPlat                   I  º    Left-down corner IGP latitude (-90º..90º)
 * double IGPlon                   I  º    Left-down corner IGP longitude (0º..360º)
 * double lat_inc                  I  º    Latitude increment (in degrees)
 * double lon_inc                  I  º    Longitude increment (in degrees) 
 * int IGPinMask[5][11][202]       I  N/A  Matrix indicating whether an IGP is monitored or not 
 * int IGP2Mask[11][202]           I  N/A  Matrix indicating to what mask correspond the last received for this IPP
 * int *InterpolationMode          O  N/A  Indicates the available InterpolationMode
 *                                           0 Full square in mask with IPP inside
 *                                           [1:4] Triangle in mask with IPP inside (the number indicates the excluded vertex)
 *                                           -1  Triangle in mask with IPP OUTSIDE
 *                                           -10 Less than three IGPs of the square in mask
 *                                           -20 IPP OUTSIDE of the square
 * int *IGPnumber                  O  N/A  Vector indicating the number in the mask of the IGPs around the IPP 
 * int *IGPBandNumber              O  N/A  Vector indicating the band number of the IGPs around the IPP 
 *****************************************************************************/
void IGPsearch (double IPPlat, double IPPlon, double IGPlat, double IGPlon, double lat_inc, double lon_inc, int IGPinMask[5][11][202], int IGP2Mask[11][202], int *InterpolationMode, int *IGPnumber, int *IGPBandNumber) {

	double 	IPPlon_aux,IGPlat_aux1,IGPlat_aux2,IGPlon_aux1,IGPlon_aux2,x,y,W;
	int 	inside,numIGPvalid;
	int 	Bandnumber1,Bandnumber2,Bandnumber3,Bandnumber4,IGP1,IGP2,IGP3,IGP4,IGP90;
	int 	IGP1valid,IGP2valid,IGP3valid,IGP4valid;
 
	//WARNING:
	//This routine can return IGP=0 when the IGP is not in the MT18 mask for bands 9 and 10 and, at the same time, it does not belong to any MOPS grid IGP for bands 0 to 8.

	IPPlon_aux=modulo(IPPlon+360,360);


	//LOOK SQUARE:
	IGPlon_aux1=IGPlon;
	IGPlat_aux1=IGPlat;
	IGPlon_aux2=IGPlon+lon_inc;
	IGPlat_aux2=IGPlat+lat_inc;
 
	*InterpolationMode=0;
	inside=0;
	if ((IPPlon_aux>=IGPlon_aux1)&&(IPPlon_aux<=IGPlon_aux2)) inside=1;
	if ((IPPlat>=IGPlat_aux1)&&(IPPlat<=IGPlat_aux2)) inside=inside+1;
	if (inside!=2) {
		*InterpolationMode=-20;
		return;
	}
 
	IGPLatLon2BandNumberIGP(IGPlat_aux2,IGPlon_aux2,&Bandnumber1,&IGP1,&IGP90);
	if (IGP90>0) {
		if (IGPinMask[IGP2Mask[9][IGP90]][9][IGP90]==1) {
			Bandnumber1=9;
			IGP1=IGP90;
		} else if (IGPinMask[IGP2Mask[10][IGP90]][10][IGP90]==1) {
			Bandnumber1=10;
			IGP1=IGP90;
		}
	}

	IGPLatLon2BandNumberIGP(IGPlat_aux2,IGPlon_aux1,&Bandnumber2,&IGP2,&IGP90);
	if (IGP90>0) {
		if (IGPinMask[IGP2Mask[9][IGP90]][9][IGP90]==1) {
			Bandnumber2=9;
			IGP2=IGP90;
		} else if (IGPinMask[IGP2Mask[10][IGP90]][10][IGP90]==1) {
			Bandnumber2=10;
			IGP2=IGP90;
		}
	}

	IGPLatLon2BandNumberIGP(IGPlat_aux1,IGPlon_aux1,&Bandnumber3,&IGP3,&IGP90);
	if (IGP90>0) {
		if (IGPinMask[IGP2Mask[9][IGP90]][9][IGP90]==1) {
			Bandnumber3=9;
			IGP3=IGP90;
		} else if (IGPinMask[IGP2Mask[10][IGP90]][10][IGP90]==1) {
			Bandnumber3=10;
			IGP3=IGP90;
		}
	}

	IGPLatLon2BandNumberIGP(IGPlat_aux1,IGPlon_aux2,&Bandnumber4,&IGP4,&IGP90);
	if (IGP90>0) {
		if (IGPinMask[IGP2Mask[9][IGP90]][9][IGP90]==1) {
			Bandnumber4=9;
			IGP4=IGP90;
		} else if (IGPinMask[IGP2Mask[10][IGP90]][10][IGP90]==1) {
			Bandnumber4=10;
			IGP4=IGP90;
		}
	}

	IGPnumber[1]=IGP1;
	IGPnumber[2]=IGP2;
	IGPnumber[3]=IGP3;
	IGPnumber[4]=IGP4;
	IGPBandNumber[1]=Bandnumber1;
	IGPBandNumber[2]=Bandnumber2;
	IGPBandNumber[3]=Bandnumber3;
	IGPBandNumber[4]=Bandnumber4;
 

	//NOTICE that, after introducing the Bands 9 and 10 we will look for IGPs that are only in the Band 9 or 10 (and they are not in the others bands). 
	//Thence, if these IGPs are not in the mask (i.e, IGPinMask[IGP2Mask[9][IGP90]][9][IGP90]!=1 or IGPinMask[IGP2Mask[10][IGP90]][10][IGP90]!=1), the IGP will set as "0", because it does not exist for the other bands!!!. 
	//This is the reason why we must to check if the IGP1,IGP2,IGP3 and IGP4 are zero before to use them as matrix index.

	IGP1valid=0;
	IGP2valid=0;
	IGP3valid=0;
	IGP4valid=0;
	if (IGP1>0) IGP1valid=IGPinMask[IGP2Mask[Bandnumber1][IGP1]][Bandnumber1][IGP1];
	if (IGP2>0) IGP2valid=IGPinMask[IGP2Mask[Bandnumber2][IGP2]][Bandnumber2][IGP2];
	if (IGP3>0) IGP3valid=IGPinMask[IGP2Mask[Bandnumber3][IGP3]][Bandnumber3][IGP3];
	if (IGP4>0) IGP4valid=IGPinMask[IGP2Mask[Bandnumber4][IGP4]][Bandnumber4][IGP4];
		 
	numIGPvalid=IGP1valid+IGP2valid+IGP3valid+IGP4valid;

	if (numIGPvalid==4)  {
		*InterpolationMode=0;
	} else if (numIGPvalid==3)  {
		//::::::::::::  LOOK TRIANGLE  :::::::::::::
		x=(IPPlon_aux-IGPlon)/lon_inc;
		y=(IPPlat-IGPlat)/lat_inc;

		*InterpolationMode=1;
		if (IGP2valid==0) {
			*InterpolationMode=2;
			x=1-x;
		} else if (IGP3valid==0) {
			*InterpolationMode=3;
			x=1-x;
			y=1-y;
		} else if (IGP4valid==0) {
			*InterpolationMode=4;
			y=1-y;
		}
		//:::::::::::::::::::::::::::::::::::::::::: 
		W=1-x-y;
		//If W>=0, the IPP is in the triangle, and it can be used for interpolation
		if(W<0) {
			*InterpolationMode=-1;
		}
	} else if (numIGPvalid<3) {
		*InterpolationMode=-10;
	}
 
	return;

}

/*****************************************************************************
 * Name        : SBASionoInterpolation
 * Description : For a given region around an IPP (defined by the IGP given),
 *               interpolate the vertical delay, the sigma error and the GIVE
 *               value according to the interpolation mode given (square or triangle)
 *               (for SBAS iono)
 *               
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double IPPlat                   I  º    Latitude of the IPP (-90º..90º)
 * double IPPlon                   I  º    Longitude of the IPP (-180º..180º or 0º..360º)
 * double IGPlat1                  I  º    Left-down corner IGP latitude (-90º..90º)
 * double IGPlon1                  I  º    Left-down corner IGP longitude (0º..360º)
 * double IGPlat2                  I  º    Right-up corner IGP latitude (-90º..90º)
 * double IGPlon2                  I  º    Right-up corner IGP longitude (0º..360º)
 * int *InterpolationMode          I  N/A  0     Interpolation in square
 *                                         [1:4] Interpolation in triangle (the number indicates the excluded vertex)
 *                                         -1    No interpolation in square
 *                                         [-1:-4] No Interpolation in triangle (the number indicates the excluded vertex)
 * double IGPDelays[5]             I  m    Vertical delays in the four grid points [1-4] from MT 26 (position 0 is not used) (in meters)
 * double IGPSigma2[5]             I  m^2  Sigma^2 in the four grid points [1-4] after applying formula A-58 in MOPS-C (position 0 is not used) (in meters^2)
 * double *VerticalDelay           O  m    Interpolated ionospheric vertical delay (in meters)
 * double *Sigma2                  O  m^2  Interpolated sigma error (in meters^2)
 * double **IPP_Weight             O  N/A  Weights for each of the corners involved in the IPP interpolation
 *****************************************************************************/
void SBASionoInterpolation (double IPPlat,double IPPlon,double IGPlat1,double IGPlon1,double IGPlat2,double IGPlon2,int *InterpolationMode,double IGPDelays[5],double IGPSigma2[5],double *VerticalDelay,double *Sigma2,double *IPP_Weight) {
 
	/*---------------------------------------------------------------

	INPUT:
	-----
	(IPPlat,IPPlon): IPP latitude and longitude (deg)

	* Square or triangle interpolation:
	(IGPlat1,IGPlat2,IGPlon1,IGPlon2):surrounding square grid-points latitude and longitude coordinates (deg)
	
	(IGPlat2,IGPlon1)   (IGPlat2,IGPlon2)
          v2..............v1
          .               .
          .               .
          .               .
          .               .
          .               .
          .               .
          .               .
          v3..............v4
	(IGPlat1,IGPlon1)   (IGPlat1,IGPlon2)
          WEST               EAST

	* Circle or semicircle interpolation (when |IPPlat|>85deg):
	(IPPlon3,xx,xx,xx):surrounding square grid-points longitude and where [3] is the closest IGP to the west of the IPP

        	   2          IPPlon3= Longitude of IGP[3]
        	/     \
          3         1
        W   \ *   /     
        	   4
        	 East
	
	
	InterpolationMode:
	InterpolationMode=-1 NO interpolation (skip)
	InterpolationMode=0  square interpolation
	InterpolationMode<>0 triangle interpolation, where the value of "InterpolationMode"
	indicates the "bad" corner (or quadrant)  |2 1|
	                                          |3 4|

	IGPDelays: Vertical Delay values at the surrounding square grid-points
  	   IGPDelays[2]|IGPDelays[1]
	  	   ----x----
	   IGPDelays[3]|IGPDelays[4]

	IGPSigma2: Sigma values at the surrounding square grid-points
	   IGPSigma2[2]|IGPSigma2[1]
	           ----x----
	   IGPSigma2[3]|IGPSigma2[4]

	Note:
	IGPSigma2 = (IGPGIVE+eps_iono)**2   (RSSiono=0)   (formula A-58 in MOPS-C)
	            IGPGIVE**2+eps_iono**2  (RSSiono=1)



	IT ALSO INCLUDES the interpolation for |IPPlat|>80deg (only with the four IGPs monitored [MOPS-B])


	A) INTERPOLATION OVER SQUARES or TRIANGLES:

	
	* Four points:
	-----------      

	(IGPlat2,IGPlon1)   (IGPlat2,IGPlon2)
	  W2=(1-x)*y          W1=x*y
          v2..............v1
          .               .
          .               .
          .               .
          .               .
          .     *         .
          .     |         .
          .     |         .
          v3____..........v4
	  W3=(1-x)*(1-y)      W4=x*(1-y)
	 (IGPlat1,IGPlon1)   (IGPlat1,IGPlon2)
	   WEST               EAST

	
	
	*VerticalDelay= v1*W1 + v2*W2 + v3*W3 + v4*W4
	
	
	where:
	
	(x,y): are taken from corner [3]
	
	
	
	* Three points: Four expressions.
	------------     
	
	a)
	
         v2        v1
        W2=y      W1=0
          |\
          |  \
          | *  \
          |______\
         v3        v4
	    W3=1-x-y     W4=x
	
	
	where:
	(x,y): are taken from corner [3]
	*VerticalDelay= v1*W1 + v2*W2 + v3*W3 + v4*W4
	

	NOTE: W2+W1 --> W2
	W3+W1 --> W3
	W4+W1 --> W4
	

	
	b)
        v2       v1
        W2=0     W1=y
          /|
          /  |
          /    |
          /      |
          --------
          v3     v4
        W3=1-x   W4=x-y
	
	
	(x,y): are taken from corner [3]
	*VerticalDelay= v1*W1 + v2*W2 + v3*W3 + v4*W4
	
	
	
	c)
          v2       v1
	   W2=1-x     W1=x+y-1
          ---------
          \       |
          \     |
          \   |
          \ |
          |
          v3       v4
         W3=0     W4=1-y
	
	
	(x,y): are taken from corner [3]
	*VerticalDelay= v1*W1 + v2*W2 + v3*W3 + v4*W4
	
	
	
	d)
	
          v2         v1
        W2=y-x      W1=x
          ________
          |        /
          |      /
          |    /
          |  /
          |/
          v3        v4
        W3=1-y     W4=0
	
	
	(x,y): are taken from corner [3]
	*VerticalDelay= v1*W1 + v2*W2 + v3*W3 + v4*W4
	
	



	B) INTERPOLATION OVER CIRCLES or SEMICIRCLES [|fi|>85deg]      
	
	* Four points:
	-----------

              2
           /     \      [3] closest IGP to the west of the IPP
         3         1
   	   W   \ *   /       y=(fabs(lat)-85)/10
	          4
              E          x=(lon - lon3)/90*(1-2*y)+y
	
	W1=x*y
	W2=(1-x)*y
	W3=(1-x)*(1-y)
	W4=x*(1-y)

	*VerticalDelay= v1*W1 + v2*W2 + v3*W3 + v4*W4



	* Three points: Two expressions:
	----------- 


	1) Not available IGP1:

              2
           /           [3] closest IGP to the west of the IPP
         3    |  
        W  \ *         y=(fabs(lat)-85)/10
              4
              E        x=(lon - lon3)/90*(1-2*y)+y

	W2=(1-x)*y
	W3=(1-x)*(1-y)
	W4=x

	NOTE: W3+W4 --> W4

	*VerticalDelay= v2*W2 + v3*W3 + v4*W4


	2) Not available IGP2:

	
	[3] closest IGP to the west of the IPP
          3 ------ 1
        W   \ *  /       y=(fabs(lat)-85)/10
              4
  	          E          x=(lon - lon3)/90*(1-2*y)+y

	W1=x*y
	W3=(1-x)
	W4=x*(1-y)

	NOTE: W2+W3 --> W3

	*VerticalDelay= v1*W1 + v3*W3 + v4*W4

	NOTE:
	If IGP3 or IGP4 are not available, the interpolation is not
	possible, because [3] is the closest IGP to the west of the IPP



	
	OUTPUT:
	------
	*VerticalDelay: Vertical Delay at the IPP (in meters)
	*Sigma2: User Ionospheric Vertical Error at the IPP (in meters^2)

	InterpolationMode= -1 ===> NOT MONITORED
	(in this case, also *Sigma2=-1)

	COMMENTS;
	--------
	The interpolation weights [W1,W2,W3,W4] are defined like the
	components of vector "IGPDelays", and corresponds to the 1st,2n,3st
	and 4th quadrants:
	i.e.:   W2|W1
	        --x--
	        W3|W4



	..................................................................*/


	double 	W1,W2,W3,W4,x,y,IPPlon_aux;
 
	IPP_Weight[1]=W1=0;
	IPP_Weight[2]=W2=0;
	IPP_Weight[3]=W3=0;
	IPP_Weight[4]=W4=0;

	IPPlon_aux=modulo(IPPlon+360,360);

	if ((IPPlat>=85.)||(IPPlat<-85.)) {
		//Interpolation for |IPPlat|>80deg
		//Notice that for |IPPlat|>80, IGPlon1 has been assigned to the IGPlon value provided by the function "IPP2Sqr" for this case.
		//That is, it corresponds to the closest IGP to IPP from west

		y=(fabs(IPPlat)-85.)/10;
		x=(IPPlon_aux-IGPlon1)/90*(1-2*y)+y;
		if ((x>1)||(y>1)) {
			*Sigma2=-1;
			*InterpolationMode=-1;
			return;
		}


		if (*InterpolationMode==0) {
			//Interpolating with four points
			W1=x*y;
			W2=(1-x)*y;
			W3=(1-x)*(1-y);
			W4=x*(1-y);
			*VerticalDelay=IGPDelays[1]*W1+IGPDelays[2]*W2+IGPDelays[3]*W3+IGPDelays[4]*W4;
			*Sigma2=IGPSigma2[1]*W1+IGPSigma2[2]*W2+IGPSigma2[3]*W3+IGPSigma2[4]*W4;
			IPP_Weight[1]=W1;
			IPP_Weight[2]=W2;
			IPP_Weight[3]=W3;
			IPP_Weight[4]=W4;
		 } else {              
			//Interpolating with Three points
			//MOPS does not define the weights for the three points interpolation when |fi|>85.(we assume these equations!!!)
			//NOTE: This interpolation is only valid in MOPS A. In this version, it will never execute this code

			if (*InterpolationMode==1) {
				W2=(1-x)*y;
				W3=(1-x)*(1-y);
				W4=x;
				*VerticalDelay=IGPDelays[2]*W2+IGPDelays[3]*W3+IGPDelays[4]*W4;
				*Sigma2=IGPSigma2[2]*W2+IGPSigma2[3]*W3+IGPSigma2[4]*W4;
				IPP_Weight[1]=0;
				IPP_Weight[2]=W2;
				IPP_Weight[3]=W3;
				IPP_Weight[4]=W4;
			} else if (*InterpolationMode==2) {
				W1=x*y;
				W3=(1-x);
				W4=x*(1-y);
				*VerticalDelay=IGPDelays[1]*W1+IGPDelays[3]*W3+IGPDelays[4]*W4;
				*Sigma2=IGPSigma2[1]*W1+IGPSigma2[3]*W3+IGPSigma2[4]*W4;
				IPP_Weight[1]=W1;
				IPP_Weight[2]=0;
				IPP_Weight[3]=W3;
				IPP_Weight[4]=W4;
			} else if (*InterpolationMode>2) {     
				*InterpolationMode=-1;
			} else if (*InterpolationMode<0) {
				*InterpolationMode=-1;
			}
		}
		return;
	}


	x=(IPPlon_aux-IGPlon1)/(IGPlon2-IGPlon1);
	y=(IPPlat -IGPlat1)/(IGPlat2-IGPlat1);

	if ((x>1)||(y>1)) {
		*Sigma2=-1;
		*InterpolationMode=-1;
		return;
	}

	if (*InterpolationMode<0) {
		*Sigma2=-1;
		*InterpolationMode=-1;
		return;
	}
	if (*InterpolationMode==0) {
		//Rectangle
		W1=x*y;
		W2=(1.-x)*y;
		W3=(1.-x)*(1.-y);
		W4=x*(1.-y);
		*VerticalDelay=IGPDelays[1]*W1+IGPDelays[2]*W2+IGPDelays[3]*W3+IGPDelays[4]*W4;
		*Sigma2=IGPSigma2[1]*W1+IGPSigma2[2]*W2+IGPSigma2[3]*W3+IGPSigma2[4]*W4;
		IPP_Weight[1]=W1;
		IPP_Weight[2]=W2;
		IPP_Weight[3]=W3;
		IPP_Weight[4]=W4;
	} else {
		//Triangle
		if (*InterpolationMode==2) {
			x=1.-x;
		} else if (*InterpolationMode==3) {
			x=1.-x;
			y=1.-y;
		} else if (*InterpolationMode==4) {
			y=1.-y;
		}
		W1=y;
		W2=1.-x-y;
		W3=x;
		//*Sigma2=-1 ==> OUTSIDE TRIANGLE: No correction
		if (W2<0) {
			 *Sigma2=-1;
			 *InterpolationMode=*InterpolationMode*(-1);
		} else {
			if (*InterpolationMode==1) {
				*VerticalDelay=IGPDelays[2]*W1+IGPDelays[3]*W2+IGPDelays[4]*W3;
				*Sigma2=IGPSigma2[2]*W1+IGPSigma2[3]*W2+IGPSigma2[4]*W3;
				IPP_Weight[1]=0;
				IPP_Weight[2]=W1;
				IPP_Weight[3]=W2;
				IPP_Weight[4]=W3;
			}
			if (*InterpolationMode==2) {
				*VerticalDelay=IGPDelays[1]*W1+IGPDelays[3]*W3+IGPDelays[4]*W2;
				*Sigma2=IGPSigma2[1]*W1+IGPSigma2[3]*W3+IGPSigma2[4]*W2;
				IPP_Weight[1]=W1;
				IPP_Weight[2]=0;
				IPP_Weight[3]=W3;
				IPP_Weight[4]=W2;
			}
			if (*InterpolationMode==3) {
				*VerticalDelay=IGPDelays[1]*W2+IGPDelays[2]*W3+IGPDelays[4]*W1;
				*Sigma2=IGPSigma2[1]*W2+IGPSigma2[2]*W3+IGPSigma2[4]*W1;
				IPP_Weight[1]=W2;
				IPP_Weight[2]=W3;
				IPP_Weight[3]=0;
				IPP_Weight[4]=W1;
			}
			if (*InterpolationMode==4) {
				*VerticalDelay=IGPDelays[1]*W3+IGPDelays[2]*W2+IGPDelays[3]*W1;
				*Sigma2=IGPSigma2[1]*W3+IGPSigma2[2]*W2+IGPSigma2[3]*W1;
				IPP_Weight[1]=W3;
				IPP_Weight[2]=W2;
				IPP_Weight[3]=W1;
				IPP_Weight[4]=0;
			}
		}
	} 
															   

	return;
}

/*****************************************************************************
 * Name        : InsideOutside
 * Description : For a given region (squared or triangular), check if the coordinate
 *               given (in latitude and longitude) is inside the region for
 *                SBAS message type 27
 *               
 * Parameters  :
 * Name                           |Da|Unit|Description
 * double latpos                   I  º    Coordinate latitude (-90º..90º)
 * double lonpos                   I  º    Coordinate longitude (0º..360º, -180º..180º)
 * double lat1                     I  º    Latitude  point 1 (-90º..90º)
 * double lon1                     I  º    Longitude point 1 (0º..360º, -180º..180º)
 * double lat2                     I  º    Latitude  point 2 (-90º..90º)
 * double lon2                     I  º    Longitude point 2 (0º..360º, -180º..180º)
 * double lat3                     I  º    Latitude  point 3 (-90º..90º) 
 * double lon3                     I  º    Longitude point 3 (0º..360º, -180º..180º)
 * double lat4                     I  º    Latitude  point 4 (-90º..90º)
 * double lon4                     I  º    Longitude point 4 (0º..360º, -180º..180º)
 *                                         Point4 is ignored if the region is triangular
 * int  shape                      I  N/A  0 -> triangular region
 *                                         1 -> squared region
 * Returned value (int)            O  N/A  1  => Coordinate inside region
 *                                         0  => Coordinate outside region
 *                                         -1 => Not a valid region
 *****************************************************************************/
int InsideOutside (double latpos, double lonpos, double lat1, double lon1, double lat2, double lon2, double lat3, double lon3, double lat4, double lon4, int shape) {

	/*In MOPS, message type 27 sends coordinates 1 and 2, but it doesn't define in which of these orders is given:
	 *
	 *       1             3                  2             4                   3             1                  4             2
	 *  (lat1,lon1)   (lat1,lon2)        (lat2,lon2)   (lat2,lon1)         (lat1,lon2)   (lat1,lon1)        (lat2,lon1)   (lat2,lon2)
	 *       x             x                  x             x                   x             x                  x             x
	 *                              or                               or                                 or
	 *       x             x                  x             x                   x             x                  x             x
	 *  (lat2,lon1)   (lat2,lon2)        (lat1,lon2)   (lat1,lon1)         (lat2,lon2)   (lat2,lon1)        (lat1,lon1)   (lat1,lon2)
	 *       4             2                  3             1                   2             4                  1             3
	 *
	 *  Coordinate 3 takes the coordinate 1 latitude and the coordinate 2 longitude.
	 *  For a square region, coordinate 4 takes the coordinate 2 latitude and the coordinate 1 longitude.
	 *  We will reorder the points so as it stays with the first shape shown above.
	 *
	 *  Additionally, the regions will not be longer than 179º, having this shape:
	 *
	 *    |lon2-lon1|<=179º           |lon2-lon1|>179º
	 *    
	 *   1 ·---------· 3              ---· 1   3 ·---
	 *     |/////////|                ///|       |///
	 *     |/////////|                ///|       |///
	 *   4 ·---------· 2              ---· 4   2 ·---
	 */




	int	vertexoutside=4;	//This variable states which vertex will not be used in the triangle interpolation
	double	tmplat,tmplon;
	double	x,y,Weight;

	//Set all longitudes between 0..360º
	lonpos=modulo(lonpos+360,360);
	lon1=modulo(lon1+360,360);
	lon2=modulo(lon2+360,360);
	lon3=modulo(lon3+360,360);
	lon4=modulo(lon4+360,360);

	//Check that coordinate 1 is in the upper part. If it is not the case, reorder the points
	if(lat1<lat2) {
		//Coordinate 1 is in the lower part. We need to reorder it
		tmplat=lat1;
		tmplon=lon1;
		lat1=lat2;
		lon1=lon2;
		lat2=tmplat;
		lon2=tmplon;
		lat3=lat1;
		lon3=lon2;
		lat4=lat2;
		lon4=lon1;

		if(lon1>lon2) vertexoutside=3;
		else vertexoutside=1;
	}

	//Check that coordinate 1 is in the upper-left corner. If it is not the case, reorder the points
	if(lon1>lon2) {
		//coordinate 1 is in the upper-right corner. We need to reorder it
		tmplon=lon1;
		lon1=lon2;
		lon2=tmplon;
		lon3=lon2;
		lon4=lon1;

		if(vertexoutside==4) vertexoutside=2;
	}

	if(lat1-lat2<1 || lon2-lon1<1) {
		//Distance between points in longitude or latitude are less than 1º. It is not a valid region
		return -1;
	}

	if(shape==1) {
		//Squared region
		if(latpos>=lat2 && latpos<=lat1) {
			if(lon2-lon1>179) {
				//The region goes through the extremes
				if(lonpos>=lon2 || lonpos<=lon1) return 1;
				else return 0;
			} else {
				//The region does not go through the extremes
				if(lonpos<=lon2 && lonpos>=lon1) return 1;
				else return 0;
			}
		} else {
			//Position outside region
			return 0;
		}
	} else if (shape==0) {
		//Triangular region
		if(lon2-lon1>179) {
			//The region goes through the extremes, so in this case it is easier to work with longitudes between -180..180º
			if(lonpos>180) lonpos-=360;
			if(lon1>180) lon1-=360;
			if(lon2>180) lon2-=360;
			if(lon3>180) lon3-=360;
			if(lon4>180) lon4-=360;
		}

		x=(lonpos-lon4)/(lon3-lon4);
		y=(latpos-lat4)/(lat3-lat4);

		if(vertexoutside==1) {
            /*This case:
                 1     3     
       (lat1,lon1)     (lat1,lon2)
                 x     x
                      /|             
                     / |             
                    /  |             
                   /   |             
                  /    |             
                 x-----x
       (lat2,lon1)     (lat2,lon2)
                 4     2     
            */
			 x=1-x;
		} else if (vertexoutside==2) {
            /*This case:
                 1     3     
       (lat1,lon1)     (lat1,lon2)
                 x-----x
                 |    /              
                 |   /               
                 |  /                
                 | /                 
                 |/                  
                 x     x
       (lat2,lon1)     (lat2,lon2)
                 4     2     
           */
			y=1-y;
		} else if (vertexoutside==3) {
           /*This case:
                 1     3     
       (lat1,lon1)     (lat1,lon2)
                 x     x
                 |\
                 | \
                 |  \
                 |   \
                 |    \
                 x-----x
       (lat2,lon1)     (lat2,lon2)
                 4     2     
         */
        //Nothing to change in this case
		} else if (vertexoutside==4) {
         /*This case:
                 1     3     
       (lat1,lon1)     (lat1,lon2)
                 x-----x
                  \    |             
                   \   |             
                    \  |             
                     \ |             
                      \|             
                 x     x
       (lat2,lon1)     (lat2,lon2)
                 4     2     
        */
			x=1-x;
			y=1-y;
		}
		Weight=1-x-y;
		if(Weight>=0) return 1;
		else return 0;
	} else {
		//Not a valid shape
		return -1;
	}
}

/*****************************************************************************
 * Name        : AWGN_generator
 * Description : Generate an AWGN sample using Box-Muller Transformation method
 *               
 * Parameters  : 
 * Name                           |Da|Unit|Description
 * double stddev                   I  m    Standard deviation of the AWGN to be generated
 * Returned value (double)         O  m    AWGN sample value (in meters) 
 *****************************************************************************/
double AWGN_generator (double stddev) {

	double		mean = 0;
	double		sample, val1, val2 = 0;

	while ( val2 == 0 ) {
		#if defined (__WIN32__)
			val2 = (double)(rand()) / ((double)RAND_MAX);
		#else
			val2 = (double)random() / ((double)RAND_MAX);
		#endif
	}

	#if defined (__WIN32__)
		val1 = cos((2.0*Pi)*(double)(rand()) / ((double)RAND_MAX));
	#else
		val1 = cos((2.0*Pi)*(double)random() / ((double)RAND_MAX));
	#endif
	sample = sqrt(-2.0*log(val2)) * val1;

	//The sample is now with mean 0 and variance=1
	//We can change the mean and variance as desired. In this case the mean will be 0 always
	sample = mean + sample * stddev;

	return sample;
}

/*****************************************************************************
 * Name        : qsort_compare_double
 * Description : Function to compare two doubles for qsort function 
 *               (from C library <stdlib.h>). The requisite for this function
 *               stated in the qsort man page is that when a<b, a negative
 *               value should be returned, when a=b zero should be a returned,
 *               and when a>b, a positive value should be returned
 *
 * Parameters  :
 * Name                           |Da|Unit|Description
 * const void *a                   I  N/A  First double value as 'const void' pointer 
 * const void *b                   I  N/A  Second double value as 'const void' pointer 
 * Returned value (int)            O  N/A  -1 -> a < b
 *                                          0 -> a=b
 *                                          1 -> a > b
 *****************************************************************************/
int qsort_compare_double(const void *a,const void *b) {
    double *x = (double *) a;
    double *y = (double *) b;
    if (*x < *y) return -1;
    else if (*x > *y) return 1;
    return 0;
    //NOTE: In some codes, instead of setting the return value with if-else,
    //they use the following line:
    //return (*x-*y);
    //This instructions is valid, except in the cases in the limits of decimal representation.
    //For example, if a = MAX_DOUBLE_VALUE and b = -10, then a-b will overflow the result and 
    // return an undefined value
}

/*****************************************************************************
 * Name        : qsort_compare_int
 * Description : Function to compare two integers for qsort function 
 *               (from C library <stdlib.h>). The requisite for this function
 *               stated in the qsort man page is that when a<b, a negative
 *               value should be returned, when a=b zero should be a returned,
 *               and when a>b, a positive value should be returned
 *
 * Parameters  :
 * Name                           |Da|Unit|Description
 * const void *a                   I  N/A  First integer value as 'const void' pointer 
 * const void *b                   I  N/A  Second integer value as 'const void' pointer 
 * Returned value (int)            O  N/A  -1 -> a < b
 *                                          0 -> a=b
 *                                          1 -> a > b
 *****************************************************************************/
int qsort_compare_int(const void *a,const void *b) {
    int *x = (int *) a;
    int *y = (int *) b;
    if (*x < *y) return -1;
    else if (*x > *y) return 1;
    return 0;
    //NOTE: In some codes, instead setting the return value with if-else,
    //they use the following line:
    //return (*x-*y);
    //This instructions is valid, except in the cases in the limits of integer representation.
    //For example, if a = MAX_INTEGER_VALUE and b = -10, then a-b will overflow the result and 
    // return an undefined value
}

/*****************************************************************************
 * Name        : mkdir_recursive
 * Description : Function to create directories recursively. The function 
 *                assumes that the string after the last slash (or backslash
 *                in Windows) is the filename, so it does not use the filename
 *                to create a directory.
 *
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char *path                      I  N/A  Directory
 * Returned value (int)            O  N/A  -1 -> Error when creating directory
 *                                          0 -> No error
 *****************************************************************************/
int mkdir_recursive(char *filepath) {

	int 			i;
	int 			len;
	int				ret;
	int				badDir=0;
	char			slash;
	struct 	stat 	path_stat;

	#if (defined __WIN32__) || (defined __CYGWIN__)
		int			colon=0;
	#endif

	len=strlen(filepath);
	for (i=0; i<len-1; i++) {
		#if defined (__WIN32__)
			if (filepath[i] == '\\') {
				slash='\\';
				if(i==0) {
					badDir=1;
					break;
				}
				//For windows, if path is absolute, we need to skip first part of path (the C: part)
				if (colon==1) {
					colon=0;
					continue;
				}
		#elif defined (__CYGWIN__)
			if (filepath[i] == '/'|| filepath[i] == '\\') {
				if (filepath[i] == '/') {
					if (i==0) continue; //If is a full path in Linux path style, skip the first part
					slash='/';
				} else if (filepath[i] == '\\') {
					slash='\\';
					if(i==0) {
						badDir=1;
						break;
					}
					//For windows, if path is absolute, we need to skip first part of path (the C: part)
					if (colon==1) {
						colon=0;
						continue;
					}
				}
		#else
			if (filepath[i] == '/') {
				if (i==0) continue; //If is a full path in Linux, skip the first part
				slash='/';
		#endif
				/* Temporarily truncate */
				filepath[i] = '\0';

				#if !defined (__WIN32__)
						ret=mkdir(filepath,S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH); //Permission of the directory set to 755
				#else
						ret=mkdir(filepath);
				#endif
				if(ret!=0 && errno!=EEXIST) {
				   return -1;
				} else if (ret!=0 && errno==EEXIST) {
					//Check that what exists is a directory and not a file
					stat(filepath, &path_stat);
					if (!S_ISDIR(path_stat.st_mode)) {
					   return -1;
					}
				}

				filepath[i] = slash;
		#if defined (__WIN32__) || (defined __CYGWIN__)
			} else if (filepath[i] == ':' && i==1) {
				colon=1;
		#endif
			}
	}
	if(badDir==1) {
		//In Windows, directory starts with backslash, which is illegal
		for(i=1;i<len-1; i++) {
			if (filepath[i] == '\\') {
				filepath[i] = '\0';
				return -1;
			}
		}
	}
	return 0;
}

/*****************************************************************************
 * Name        : InitRangeList
 * Description : Initialize a TRangeList structure
 * Parameters  :
 * Name                            |Da|Unit|Description
 * TRangeList *List                 O  N/A  Structure with the list of satellite ranges
 *****************************************************************************/
void InitRangeList (TRangeList *List) {

    List->size=1;
    List->listSatGNSS=NULL;
    List->listSatPRN=NULL;
    List->numJumpslist=NULL;
    List->listSatGNSS=malloc(sizeof(enum GNSSystem*));
    List->listSatGNSS[0]=malloc(sizeof(enum GNSSystem*));
    List->listSatGNSS[0][0]=malloc(sizeof(enum GNSSystem)*2);
    List->listSatPRN=malloc(sizeof(int*));
    List->listSatPRN[0]=malloc(sizeof(int*));
    List->listSatPRN[0][0]=malloc(sizeof(int)*2);
    List->numJumpslist=malloc(sizeof(int));
    List->listSatPRN[0][0][0]=1;
    List->listSatPRN[0][0][1]=999; //This is for the last range, which will not have end value
    List->listSatGNSS[0][0][0]=GPS;
    List->listSatGNSS[0][0][1]=IRNSS; //This is for the last range, which will not have end value
    List->numJumpslist[0]=1;
}

/*****************************************************************************
 * Name        : freeRangeList
 * Description : Free memory of a TRangeList structure
 * Parameters  :
 * Name                            |Da|Unit|Description
 * TRangeList *List                 O  N/A  Structure with the list of satellite ranges
 *****************************************************************************/
void freeRangeList (TRangeList *List) {

    int i,j;

    for(i=0;i<List->size;i++) {
        for(j=0;j<List->numJumpslist[i];j++) {
            free(List->listSatGNSS[i][j]);
            free(List->listSatPRN[i][j]);
        }
        free(List->listSatGNSS[i]);
        free(List->listSatPRN[i]);
    }
    free(List->listSatGNSS);
    free(List->listSatPRN);
    free(List->numJumpslist);
    List->listSatGNSS=NULL;
    List->listSatPRN=NULL;
    List->numJumpslist=NULL;
    List->size=1;
}

/*****************************************************************************
 * Name        : AddRangeList
 * Description : Add a new block of ranges in the TRangeList structure
 * Parameters  :
 * Name                            |Da|Unit|Description
 * enum GNSSystem GNSS              I  N/A  Constellation of the first satellite in the first range
 * int PRN                          I  N/A  PRN  of the first satellite in the first range
 * TRangeList *List                 O  N/A  Structure with the list of satellite ranges
 *****************************************************************************/
void AddRangeList (enum GNSSystem GNSS, int PRN, TRangeList *List) {

	int i;
	
	i=List->size;
	List->size++;
	List->listSatGNSS=realloc(List->listSatGNSS,sizeof(enum GNSSystem*)*List->size);
	List->listSatGNSS[i]=malloc(sizeof(enum GNSSystem*));
	List->listSatGNSS[i][0]=malloc(sizeof(enum GNSSystem)*2);
	List->listSatPRN=realloc(List->listSatPRN,sizeof(int*)*List->size);
	List->listSatPRN[i]=malloc(sizeof(int*));
	List->listSatPRN[i][0]=malloc(sizeof(int)*2);
	List->numJumpslist=realloc(List->numJumpslist,sizeof(int)*List->size);

	List->listSatGNSS[i][0][0]=GNSS;
	List->listSatPRN[i][0][0]=PRN;
	List->listSatGNSS[i][0][1]=IRNSS; //This is the last constellation, due to the last range will not have an end
	List->listSatPRN[i][0][1]=999; //Value to see that no end range value was set
	List->numJumpslist[i]=1;
}

/*****************************************************************************
 * Name        : ExtendRangeList
 * Description : Add a new range in an existing block of ranges of a TRangeList structure
 * Parameters  :
 * Name                            |Da|Unit|Description
 * enum GNSSystem GNSS              I  N/A  Constellation of the first satellite in the range
 * int PRN                          I  N/A  PRN of the first satellite in the range
 * int pos                          I  N/A  Position of the block where to add the new range
 * TRangeList *List                 O  N/A  Structure with the list of satellite ranges
 *****************************************************************************/
void ExtendRangeList (enum GNSSystem GNSS, int PRN, int pos, TRangeList *List) {
	
	List->listSatGNSS[pos]=realloc(List->listSatGNSS[pos],sizeof(enum GNSSystem*)*(List->numJumpslist[pos]+1));
	List->listSatGNSS[pos][List->numJumpslist[pos]]=malloc(sizeof(enum GNSSystem)*2);
	List->listSatPRN[pos]=realloc(List->listSatPRN[pos],sizeof(int*)*(List->numJumpslist[pos]+1));
	List->listSatPRN[pos][List->numJumpslist[pos]]=malloc(sizeof(int)*2);
	List->listSatGNSS[pos][List->numJumpslist[pos]][0]=GNSS;
	List->listSatPRN[pos][List->numJumpslist[pos]][0]=PRN;
	List->listSatGNSS[pos][List->numJumpslist[pos]][1]=IRNSS; //This is the last constellation, due to the last range will not have an end value set
	List->listSatPRN[pos][List->numJumpslist[pos]][1]=999; //Value to see that no end range value was set
	List->numJumpslist[pos]++;
}

/*****************************************************************************
 * Name        : SatRangeList2String
 * Description : Get the list of ranges and transform them to a string. The
 *                 ranges will be grouped by satellite constellations
 *                 a string for printing an INFO message
 * Parameters  :
 * Name                            |Da|Unit|Description
 * int i                            I  N/A  Position of the current range list
 * TRangeList *List                 I  N/A  Structure with the list of satellite ranges
 * char *auxstr                     O  N/A  Output string with the range list
 *****************************************************************************/
void SatRangeList2String (int i, TRangeList *List,  char *auxstr) {

	int 		j,k;
	static int	listMaxSatGNSS[MAX_GNSS]={MAX_SAT_GPS,MAX_SAT_GAL,MAX_SAT_GLO,MAX_SAT_GEO,MAX_SAT_BDS,MAX_SAT_QZS,MAX_SAT_IRN};
	char 		auxstr2[200];

    auxstr[0]='\0';
	for(j=0;j<List->numJumpslist[i];j++) {
		if(List->listSatGNSS[i][j][0]==List->listSatGNSS[i][j][1] && List->listSatPRN[i][j][0]==List->listSatPRN[i][j][1]) {
			//Range of only one satellite
			sprintf(auxstr2,"%s %c%02d",auxstr,gnsstype2char(List->listSatGNSS[i][j][0]),List->listSatPRN[i][j][0]);
			sprintf(auxstr,"%s",auxstr2);
		} else if (List->listSatGNSS[i][j][0]!=List->listSatGNSS[i][j][1]) {
			//Constellation changed
			if (List->listSatGNSS[i][j][1]-List->listSatGNSS[i][j][0]==1) {
				//One constllation change only
				if (List->listSatPRN[i][j][1]==999) {
					sprintf(auxstr2,"%s %c%02d-%02d %c01-%02d",auxstr,gnsstype2char(List->listSatGNSS[i][j][0]),List->listSatPRN[i][j][0],listMaxSatGNSS[List->listSatGNSS[i][j][0]],gnsstype2char(List->listSatGNSS[i][j][1]),listMaxSatGNSS[List->listSatGNSS[i][j][1]]);
				} else {
					sprintf(auxstr2,"%s %c%02d-%02d %c01-%02d",auxstr,gnsstype2char(List->listSatGNSS[i][j][0]),List->listSatPRN[i][j][0],listMaxSatGNSS[List->listSatGNSS[i][j][0]],gnsstype2char(List->listSatGNSS[i][j][1]),List->listSatPRN[i][j][1]);
				}
				sprintf(auxstr,"%s",auxstr2);
			} else {
				//Multiple constellation change
				//First constellation change is printed outside of the for
				sprintf(auxstr2,"%s %c%02d-%02d",auxstr,gnsstype2char(List->listSatGNSS[i][j][0]),List->listSatPRN[i][j][0],listMaxSatGNSS[List->listSatGNSS[i][j][0]]);
				sprintf(auxstr,"%s",auxstr2);
				for(k=1;k<(List->listSatGNSS[i][j][1]-List->listSatGNSS[i][j][0]);k++) {
					//Intermiadte constellation changes
					sprintf(auxstr2,"%s %c01-%02d",auxstr,gnsstype2char(List->listSatGNSS[i][j][0]+k),listMaxSatGNSS[List->listSatGNSS[i][j][0]+k]);
					sprintf(auxstr,"%s",auxstr2);
				}
				//Last constellation change
				if (List->listSatPRN[i][j][1]==999) {
					sprintf(auxstr2,"%s %c01-%02d",auxstr,gnsstype2char(List->listSatGNSS[i][j][1]),listMaxSatGNSS[List->listSatGNSS[i][j][1]]);
				} else {
					sprintf(auxstr2,"%s %c01-%02d",auxstr,gnsstype2char(List->listSatGNSS[i][j][1]),List->listSatPRN[i][j][1]);
				}
			}
		} else if (List->listSatPRN[i][j][1]==999) {
			sprintf(auxstr2,"%s %c%02d-%02d",auxstr,gnsstype2char(List->listSatGNSS[i][j][0]),List->listSatPRN[i][j][0],listMaxSatGNSS[List->listSatGNSS[i][j][1]]);
			sprintf(auxstr,"%s",auxstr2);
		} else {
			sprintf(auxstr2,"%s %c%02d-%02d",auxstr,gnsstype2char(List->listSatGNSS[i][j][0]),List->listSatPRN[i][j][0],List->listSatPRN[i][j][1]);
			sprintf(auxstr,"%s",auxstr2);
		}
	}
}

/*****************************************************************************
 * Name        : WeightType2String
 * Description : Create as string with the weight type and their values for
 *                 printing an INFO message with the user selected weights
 *               
 * Parameters  :
 * Name                           |Da|Unit|Description
 * enum GNSSystem GNSS             I  N/A  Constellation
 * int PRN                         I  N/A  PRN number
 * int NumMeas                     I  N/A  Number of measurement in the filter
 * int *SNRWeightused              O  N/A  Flag to indicate if a SNR weight is used
 * char *str                       O  N/A  String to be printed
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void WeightType2String (enum GNSSystem GNSS, int PRN, int NumMeas, int *SNRWeightused, char *str, TOptions *options) {
	
	char ConstantVal[20];
	if (options->WeightConstantsValues[GNSS][PRN][NumMeas][0]==-2) {
		strcpy(ConstantVal,"URA");
	} else {
		sprintf(ConstantVal,"%.6g",options->WeightConstantsValues[GNSS][PRN][NumMeas][0]);
	}

	switch(options->weightMode[GNSS][PRN][NumMeas]) {
		case SBASOnlyWeight:
			sprintf(str,"StdDev^2: SBAS variance");
			break;
		case DGNSSOnlyWeight:
			sprintf(str,"StdDev^2: DGNSS variance");
			break;
		case FixedWeight:
			sprintf(str,"StdDev: %s",ConstantVal);
			break;
		case SBASFixedWeight: 
			sprintf(str,"StdDev^2: SBAS variance + (%s)^2",ConstantVal);
			break;
		case DGNSSFixedWeight:
			sprintf(str,"StdDev^2: DGNSS variance + (%s)^2",ConstantVal);
			break;
		case ElevationWeight:
			sprintf(str,"StdDev: %s + %.6g*e^(elev/%.6g)",ConstantVal,options->WeightConstantsValues[GNSS][PRN][NumMeas][1],options->WeightConstantsValues[GNSS][PRN][NumMeas][2]*r2d);
			break;
		case SBASElevWeight:
			sprintf(str,"StdDev^2: SBAS variance + (%s + %.6g*e^(elev/%.6g)^2",ConstantVal,options->WeightConstantsValues[GNSS][PRN][NumMeas][1],options->WeightConstantsValues[GNSS][PRN][NumMeas][2]*r2d);
			break;
		case DGNSSElevWeight:
			sprintf(str,"StdDev^2: DGNSS variance + (%s + %.6g*e^(elev/%.6g))^2",ConstantVal,options->WeightConstantsValues[GNSS][PRN][NumMeas][1],options->WeightConstantsValues[GNSS][PRN][NumMeas][2]*r2d);
			break;
		case Elevation2Weight:
			sprintf(str,"StdDev^2: %s + %.6g/(sin(elev)^2)",ConstantVal,options->WeightConstantsValues[GNSS][PRN][NumMeas][1]);
			break;
		case SBASElev2Weight:
			sprintf(str,"StdDev^2: SBAS variance + %s + %.6g/(sin(elev)^2)",ConstantVal,options->WeightConstantsValues[GNSS][PRN][NumMeas][1]);
			break;
		case DGNSSElev2Weight:
			sprintf(str,"StdDev^2: DGNSS variance + %s + %.6g/(sin(elev)^2)",ConstantVal,options->WeightConstantsValues[GNSS][PRN][NumMeas][1]);
			break;
		case SNRWeight:
			sprintf(str,"StdDev^2: %s + %.6g*10^(-SNR/10)",ConstantVal,options->WeightConstantsValues[GNSS][PRN][NumMeas][1]);
			*SNRWeightused=1;
			break;
		case SBASSNRWeight:
			sprintf(str,"StdDev^2: SBAS variance + %s + %.6g*10^(-SNR/10)",ConstantVal,options->WeightConstantsValues[GNSS][PRN][NumMeas][1]);
			*SNRWeightused=1;
			break;
		case DGNSSSNRWeight:
			sprintf(str,"StdDev^2: DGNSS variance + %s + %.6g*10^(-SNR/10)",ConstantVal,options->WeightConstantsValues[GNSS][PRN][NumMeas][1]);
			*SNRWeightused=1;
			break;
		case SNRElevWeight:
			sprintf(str,"StdDev^2: %s + %.6g*10^(-SNR/10)/(sin(elev)^2)",ConstantVal,options->WeightConstantsValues[GNSS][PRN][NumMeas][1]);
			*SNRWeightused=1;
			break;
		case SBASSNRElevWeight:
			sprintf(str,"StdDev^2: SBAS variance + %s + %.6g*10^(-SNR/10)/(sin(elev)^2)",ConstantVal,options->WeightConstantsValues[GNSS][PRN][NumMeas][1]);
			*SNRWeightused=1;
			break;
		case DGNSSSNRElevWeight:
			sprintf(str,"StdDev^2: DGNSS variance + %s + %.6g*10^(-SNR/10)/(sin(elev)^2)",ConstantVal,options->WeightConstantsValues[GNSS][PRN][NumMeas][1]);
			*SNRWeightused=1;
			break;
		default:
			//This the unknown weight, which is not possible. Leave the default just to avoid compiler warning
			str[0]='\0';
			break;
	}
}
/*****************************************************************************
 * Name        : SNRCombModeNum2String
 * Description : Transform from internal SNR combination weight mode type to
 *                 a string for printing an INFO message
 * Parameters  :
 * Name                            |Da|Unit|Description
 * enum SNRWeightComb SNRweightComb I  N/A  SNR Combination weight mode
 * double K1                        I  N/A  Combining factor for first frequency
 * double K2                        I  N/A  Combining factor for second frequency
 * Returned value (char*)           O  N/A  SNR Combination weight mode string
 *****************************************************************************/
char *SNRCombModeNum2String(enum SNRWeightComb SNRweightComb, double K1, double K2) {

    static char str[50];

    switch(SNRweightComb) {
        case SNRWeightCombi:
            strcpy(str,"Use SNR from measurement of first frequency");
            break;
        case SNRWeightCombj:
            strcpy(str,"Use SNR from measurement of second frequency");
            break;
        case SNRWeightCombMax:
            strcpy(str,"Use maximum SNR of both measurements");
            break;
        case SNRWeightCombMin:
            strcpy(str,"Use minimum SNR of both measurements");
            break;
        case SNRWeightCombMean:
            strcpy(str,"Use the mean SNR of both measurements");
            break;
        case SNRWeightCombUser:
            sprintf(str,"SNR = SNRi*%.3g + SNRj*%.3g",K1,K2);
            break;
        default:
            strcpy(str,"Unknown");
            break;
    }

    return str;
}

