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
 * File: gLAB.c
 * Code Management Tool File Version: 5.2  Revision: 0
 * Date: 2018/03/09
 ***************************************************************************/

/****************************************************************************
 * MODULE DESCRIPTION
 *
 * Name: gLAB
 * Language: C
 *
 * Purpose:
 *  The purpose of this module is to create the main executable and parse all the
 *  command-line options
 *
 * Function:
 *  This class is in charge of organising the rest of the modules, creating the 
 *  chain process, and to parse all the command-line options.
 *
 * Dependencies:
 *  dataHandling, input, preprocessing, model, filter, output
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
 * Release: 2010/02/02
 * Change Log: Corrected problem with the Orbit comparison
 *             Exported SATDIFF, SATSTAT and SATSTATTOT printing to output module
 *             For orbit comparison mode, it can now disconnect the satellite phase centre
 *             For orbit comparison mode, when satellite phase centre correction is active,
 *                  it will now require an ANTEX or Constellation file
 *             Included SHOWPRODUCT mode
 *             Added --output parameter
 *             Enhanced parsing of antenna in ANTEX file
 *             Included show product mode
 *             '-input:SP3' parameter can now be provided as '-input:sp3'
 *             Corrected some typos in the help
 *             Changed '-output' to '-output:file'
 *             Included the '--output:file' option to redirect to stdout 
 *             Changed the message help to be consistent with the new updates
 *             minArcLength changed from 3 to 4 to be sure that the Li cycle-slip detector 
 *                  has properly worked
 *             Included DCB data sources
 *             Forward/Backward processing included
 *             SATSTAT message will now provide the GNSS system it refers to
 *             '-pre:setrectype' option is added to force a specific receiver type
 * -------------
 *          gLAB v1.4.0
 * Release: 2010/06/21
 * Change Log: '-pre:flexibleC1P1' option is added to allow flexible handling of C1 and P1
 *             '-pre:prealign' option to set/unset carrier-phase prealignment
 *             Cycle-slip detector changed to specify when it does not have enough measurements
 *             Added a check to see if the RINEX observation file has times inside the products
 *                  file provided
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
 * --------------
 *          gLAB v1.4.4
 * Release: 2010/09/22
 * Change Log: Included new DCB management parsing options.
 * -------------
 *          gLAB v1.4.5
 * Release: 2010/10/31
 * Change Log: Tropospheric correction '-model:trop' option is extended to '-model:trop' to activate/deactivate
 *             '-model:trop:nominal <nominal>' to select the nominal used '-model:trop:mapping <mapping>' to 
 *             select which mapping is used. This permits cross combinations among mappings and nominals.
 *             Default precise orbit interpolation degree changed from 9 to 10.
 *             Filter 'inf' value for clock and coordinates noise process and initial covariance substituted
 *                  to real floating quantities. SIGMA_INF splitted into different SIGMA_INF_DR and SIGMA_INF_DT.
 * -----------
 *          gLAB v2.0.0
 * Release: 2012/12/31
 * Change Log: gLAB version released together with the Educational Book:
 *             "GNSS Data Processing" (Vol. 1 and Vol. 2). ESA TM-23.
 *             Authors: J. Sanz Subirana, J.M. Juan Zornoza and M. Hernandez-Pajares
 *             ISBN: 978-92-9221-885-0 (two volumes)
 *             ISSN: 1013-7076
 *             December 2012.
 *
 *             SATSEL debugging message included in the help messages.
 * -----------
 *          gLAB v2.2.0
 * Release: 2014/09/22
 * Change Log: Added input parameters and options for BeiDou, IONEX, Fast-PPP and NeQuick ionosphere models.
 *         Added input parameters and options for Galileo troposphere model.
 *         Added input parameters and options for IONEX and Fast-PPP DCBs.
 *         Added input parameters and options for using standard deviation data from IONEX or FPPP.
 *         Added the capability to gather the full path of gLAB's executable (platform dependent).
 *          This is necessary because Galileo and NeQuick models require data files, and these files will
 *          be searched in the folders ./model_files/TropoGal or ./model_files/NeQuick, 
 *          where ./ is the directory of gLAB's executable (which may be different
 *          from the current user's directory).
 *         Added code for displaying correctly spanish characters.
 *         Help message has been updated with the new parameters.
 * -----------
 *          gLAB v2.2.1
 * Release: 2014/12/23
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.2.2
 * Release: 2015/03/02
 * Change Log: Locale selection eliminated in order to avoid problems with number (depending on the locale, 
 *               printf may use a comma instead of a dot for decimal separator)
 * -----------
 *          gLAB v2.2.3
 * Release: 2015/05/28
 * Change Log: Added parameter to select the correction of satellite phase variations.
 *             Added parameter to select the correction of receiver phase variations.
 *             Modified storage of antenna structure (before only saved the antenna phase center values).
 * -----------
 *          gLAB v2.2.4
 * Release: 2015/07/01
 * Change Log: gLAB version is now printed at the beginning of the INFO field.
 * -----------
 *          gLAB v2.2.5
 * Release: 2015/10/20
 * Change Log: Fixed incorrect backward processing when reading an observation file with Linux file ending in Windows.
 *             Added protection against buffer overflow in input parameters.
 * -----------
 *          gLAB v2.2.6
 * Release: 2015/11/25
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.2.7
 * Release: 2016/03/01
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v2.2.8
 * Release: 2016/04/12
 * Change Log: No changes in this file.
 * -----------
 *          gLAB v3.0.0
 * Release: 2016/09/05 
 * Change Log: Added SBAS processing.
 *             Added functions to add user-defined error to raw measurements.
 *             Configuration file now accepts paths and filenames with spaces.
 *             Modified structure definitions for handling cycle-slip and large SP3 files variables.
 *             Added check for time span in compareOrbits and showProduct functions (in some cases the broadcast files has data from many different days ago).
 * -----------
 *          gLAB v3.1.0
 * Release: 2016/09/26
 * Change Log: Added '-model:brdctranstime' input parameter.
 *             Added 'calculateRINEX' and 'calculateUSER' options for '-pre:setrecpos' input parameter.
 *             Added '-model:initcoordnpa' input parameter for SBAS.
 *             Slightly modified main loop to enable model recomputation after entering Kalman function.
 *             Updated 'MESSAGES FORMAT' help.
 * -----------
 *          gLAB v3.1.1
 * Release: 2016/10/21
 * Change Log: LLI cycle-slip detector is now enabled by default in PPP.
 *             L1C1 cycle-slip detector is now disabled by default in SPP.
 *             Transmission time of broadcast navigation messages check is now disabled by default in SBAS processing.
 *             Fixed wrong order of MEAS prints in SBAS mode.
 *             Parameter '-pre:cs:l1c1:init' is now shown in the help message.
 * -----------
 *          gLAB v4.0.0
 * Release: 2017/03/03
 * Change Log: Added DGNSS processing.
 *             Added DGNSS converter.
 *             Added SBAS plots mode.
 *             Added computation of SBAS summary when navigating with SBAS corrections, INFO message is active and receiver position is fixed.
 *             Added option to start computing SBAS summary and Stanford-ESA values at the beginning of the next day.
 *             Added option to generate a KML file from the output.
 *             Added option to generate a KML file from the output with height 0 (KML with the ground projection).
 *             Added options for adding timestamps in KML file. The timestamps can be decimated and also write at certain time regions (defined by the user).
 *             Added options to generate a SP3 file from the output.
 *             Added check for smoothing options. If number of smoothing options is given but not the carrier phase measurement
 *               to smooth with (or viceversa), it will show an error instead of continuing without any smoothing.
 *             Added option to disable check for pseudorange jumps.
 *             Added options for Stanford-ESA LOI (Loss of Integrity) data file (for its filename and the thresholds)
 *             Added parameter '-model:maintaingeo' for SBAS GEO switching.
 *             Added options for setting to zero SBAS corrections, sigmas and degradation terms.
 *             Added check for number of entries in SP3 header. If it is incorrect, it will print an error instead of crashing
 *               or showing incorrect values.
 *             Added check for number of entries in IONEX header. If it is incorrect, it will print an error instead of crashing
 *               or showing incorrect values.
 *             Added option to skip epoch or change processing mode when GDOP is over a given threshold.
 *             Added check for the number of measurements entered for the filter, to ensure they are not greater than the maximum.
 *             Added check for options '-input:sp3', '-input:orb' and '-input:clk'. When 'input:sp3' parameter is given along with
 *               'input:orb' or '-input:clk', it will show an ERROR message instead of just using the sp3 file for orbits and clocks.
 *             Added options for maximum data gap check between samples when using precise orbits and clocks.
 *             Added option to allow adding the user defined error after the preprocessing.
 *             When a SINEX file is given, the receiver position will automatically switch to SINEX mode (no need to put the
 *                '-pre:setrecpos SINEX' parameter like in previous versions).
 *             When a ionosphere file is given (with '-input:klb' or '-input:bds' or '-input:neq' or '-input:inx' or '-input:fppp' or
 *                '-input:sbasiono' it will automatically use the corresponding ionosphere model (no need to put the 'model:iono' parameter
 *                as in previous versions).
 *             Show products and compare orbit mode have been greatly improved. Now it is possible show or compare concatenated products files, and
 *               also to compare a concatenated file with a non concatenated file for a single day (this is useful to see the Runge interpolation effect
 *               with precise orbits).
 *             In navigation, show or compare orbits modes, if there is a SP3 concatenated file, gLAB will always try to have in memory orbits and clocks 
 *               from the three days (the previous day, the current day and the following day) in order to avoid Runge interpolation effect.
 *             Changed extension of generated Stanford-ESA files. Now by default they will have a ".txt" extension.
 *             Changed inital aproxPositionError for SINEX coordinates from 1 decimeter to 1 centimeter.
 *             When IONEX or F-PPP DCB source is selected, if no dcb file is given, it will use DCB data from the IONEX/F-PPP file
 *              for ionosphere data respectively (if DCB data is available from these files).
 *             When receiver position is set to 'calculateUSER' or 'calculateRINEX', initial coordinates no longer need to be 
 *              over the Earth Surface.
 *             Fixed a bug which made not to save DCB data when it was read from RINEX file with the option '-input:dcb'.
 *             Fixed MEAS message not being printed in the right order in SBAS mode.
 *             Fixed messages for deprecated options not being printed to output file when '-output:file' option was used.
 *             Fixed a bug reading user defined receiver coordinates when receiver position was set to 'calculateUSER'.
 *             Fixed a bug reading SNR threshold from parameters.
 *             MEAS message will be printed by default in 'SHOWINPUT' mode (when only an observation file is given).
 *             In SHOWINPUT mode (print only observation data), RINEX station coordinates will not be checked for consistency (as they are not used).
 *             Stanford-ESA initialization is now done outside of SBAS, so it can be used in normal SPP mode (only one measurement used by the filter).
 *             Transmission time of message check in broadcast ephemerides selection is disabled by default in PPP mode. 
 *             Taken out degree sign from output messages to avoid text encoding problems.
 *             Updated help messages.
 *             All input options are now case insensitive.
 *             Windows compiled gLAB executable is now optimized (built with '-O3' gcc option) and has the gAGE icon embedded.
 * -----------
 *          gLAB v4.1.0
 * Release: 2017/04/07
 * Change Log: Added parameters for prefit outlier detectors.
 *             Added 'RTCMRinexRover', 'RTCMUSER', 'RTCMUserbaseline', 'RTCMUserRinexRover' and 'RTCMRefRoverUSER' receiver position modes.
 *               'RTCMRinexRover' is for computing the solution error with respect to the coordinates from Rover RINEX file.
 *               'RTCMUSER' is for computing the solution error with respect to the user defined coordinates.
 *               'RTCMUserbaseline', 'RTCMUserRinexRover' and 'RTCMRefRoverUSER' are equivalent to 'RTCMbaseline', 'RTCMRinexRover' and 'RTCMUSER' but
 *                 reference station coordinates are user defined. These last three modes only work when reference station data is from a RINEX file.
 *             Added check for valid receiver position user setting. In SPP/PPP/SBAS it will show an error instead of continuing in 'calculate' mode,
 *               and in DGNSS it will show an error instead of continuing in SPP mode.
 *             If user forced NPA processing mode in parameters, gLAB will now enter the function to update values for SBAS summary, but all the values
 *               will be referred to NPA solution instead of PA.               
 *             Fixed bug where sometimes gLAB would crash or show an incorrect error message (depending if it were  in comparison or navigation mode)
 *               when an invalid RTCM file was given.
 *             Fixed reference station time synchronization bug when the Rover had a data rate of 1 second and its timestamps were not integer seconds.
 *             When comparing orbits with two SP3 or SP3+CLK files, gLAB will compute the max data gap for each precise product file instead of using 
 *               the value computed from the first precise product file read in both files.
 *             Updated help messages with new parameters and info about prefit outlier detection.
 * -----------
 *          gLAB v4.2.0
 * Release: 2017/05/22
 * Change Log:   Added option '-output:kml:refsta' for adding (or not) the reference station(s) used in DGNSS mode in 
 *                 the output KML files (default on).
 *               Added options '-model:nomt10' and '-model:nomt2728' to disable messages type 10, 27 and 28 for SBAS.
 *               Added option '-model:sbasmaritime' for SBAS maritime mode (which is a shortcut for providing
 *                 parameters '-model:nomt10' and '-model:nomt2728'.
 *               gLAB will now create all directories recursively (if needed) when opening an output file for writing.
 *               Decimation can be now a decimal number, with a maximum resolution of 0.0001 seconds (10000 Hz).
 *               Use of Klobuchar iono when SBAS iono is not available during the solution convergence is now also
 *                 permitted in receiver position modes 'calculateRINEX' or 'calculateUSER'.
 *               Added warning message when computing SBAS availability maps in order to advise user for the long
 *                 computation time needed (with default options it is around 2 hours).
 *               Added check of initial coordinates when receiver positioning is set to 'calculateRINEX' or
 *                 'calculateUSER'. If coordinates are (0,0,0), in the case of 'calculateRINEX' a warning will be
 *                 shown informing that these coordinates are invalid and that (6378137,0,0) will be used instead.
 *                 In the case of 'calculateUSER', an error will be shown.
 *               Fixed crash when SBAS iono was selected, Klobuchar iono was allowed during receiver convergence
 *                 and no navigation or Klobuchar file had been provided.
 *               Updated help messages.
 * -----------
 *          gLAB v5.0.0
 * Release: 2017/06/30
 * Change Log:   Added parameter '-pre:cs:l1c1:unconcheck:th' for L1C1 consistency check threshold.
 *               Added GEO switching in SBAS Availability maps (therefore, now it can do SBAS availability
 *                  maps with different SBAS providers in the same run).
 *               Added parameter '-sbasplots:hourlymaps' for writing hourly SBAS availability maps.
 *               Added parameter '-sbasplots:plotarea'. This parameter is a shorter way to provide the same values 
 *                 as in '-sbasplots:minlon' '-sbasplots:maxlon', '-sbasplots:minlat' and '-sbasplots:maxlat' parameters.
 *               Added parameter '-sbasplots:exclusionarea' for excluding areas in the SBAS availability maps processing.
 *                 This parameter can be passed as many times as exclusion areas needed to be defined.
 *                 This parameter will exclude all points which are inside any area defined with this parameter.
 *               Added parameter '-sbasplots:inclusionarea' for including areas in the SBAS availability maps processing.
 *                 This parameter can be passed as many times as exclusion areas needed to be defined.
 *                 This parameter will exclude all coordinates that are not inside any area defined with this parameter.
 *                 If parameter '-sbasplots:exclusionarea' is also provided, for a coordinate to be processed, it must be
 *                 inside any inclusion area and outside of all exclusion areas.
 *               Added parameter '-rtcmv2conversioninfo', which shows detailed info of the output files
 *                 generated when converting a RTCM v2.x file.
 *               Added parameter '-pre:cs:bw:siginit' for setting the initial sigma in the 
 *                 Melbourne-Wubbenna cycle-slip detector.
 *               When receiver position is set to 'RTCMUserBaseline', initial coordinates from rover will be
 *                 from the reference station coordinates instead of the Earth's surface.
 *               Changed parameter name from '-model:geoadqtime' to '-model:geoacqtime' (but the old name is
 *                 still accepted).
 *               Help parameters ('-help', '-examples', '-config', '-messages',  '-usererrorfile', '-sigmamultipathfile' 
 *                and '-rtcmv2conversioninfo') now also work with a double slash '--'.
 *               In Windows, now gLAB will have the 64 bit or 32 bit version depending on the OS version.
 *               Updated help messages.
 * -----------
 *          gLAB v5.1.0
 * Release: 2017/11/24
 * Change Log:   Added MAC support.
 *               Added progress bar in command line. In Linux, it will automatically disable if process 
 *                 is started in the background or moved to background or standard output is piped or
 *                 standard input is not a terminal. In Windows, it will automatically disabled if
 *                 standard input or output is not a terminal (In Windows and Mac it is not possible
 *                 to distinguish between output redirection to file or piped), but it is possible to
 *                 force the appearance of the progress bar with the parameter '-print:progress'. 
 *                 It can also be disabled by the user with parameter '--print:progress'.
 *               Added '-pre:starttime' and '-pre:endtime' for setting first and last epoch to be
 *                 processed of the observation file respectively. Four date formats supported:
 *                 'YYYYMMDD HH:MM:SS', 'YYYY/MM/DD HH:MM:SS', 'YYYY/DoY SoD' and 'GPSWeek SoW'.
 *               Added hidden parameter '-pre:guiprogress'. This parameter is given by the GUI to
 *                 the gLAB core in order to make the latter print the progress in a suitable format
 *                 to be read by the GUI.
 *               Added parameters '-dateconv:calendar', '-dateconv:doy', '-dateconv:gpsweek' and
 *                 '-dateconv:mjdn' for date conversion mode.
 *               Added parameters '-coordconv:cartesian', '-coordconv:geodetic' and 
 *                 '-coordconv:spherical' for coordinate conversion mode.
 *               Added parameter '-sbassummary:starttime' to allow a user defined start time
 *                 of the SBAS summary (if user also wants to set an end time, set the last
 *                 epoch to be processed with parameter '-pre:endtime').
 *               Added parameters '-output:sp3:dgnssonly' and '--output:sp3:dgnssonly' to enable
 *                 or disable writing SPP solution to output SP3 file in DGNSS mode.
 *               Added parameter '-input:refpos' for reading an input reference position file.
 *                 Input reference file can be a columnar text file, a SP3 file or a RTKlib
 *                 output file.
 *               Added parameter '-referenceposfile' for a description of the input reference file.
 *               Added parameter '-output:refpos' for writing an output reference position file.
 *               Added parameters '-output:refpos:doy', '-output:refpos:gpsweek' and 
 *                 '-output:refpos:caltime' to write the timestamps in "Year DoY SoD", or 
 *                 "GPSWeek/SoW" or "YYYY/MM/DD HH:MM:SS.zzz" formats respectively.
 *               Added parameters '-output:refpos:geodetic' and '--output:refpos:geodetic' to set or unset
 *                 to write the coordinates in geodetic system instead of cartesian mode.
 *               Added parameters '-output:refpos:dgnssonly' and '--output:refpos:dgnssonly' to enable
 *                 or disable writing SPP solution to output reference position file in DGNSS mode.
 *               Added parameter '--print:none'. It has the same effect as '-print:none'.
 *               Added parameter '-model:tropo'. It has the same effect as '-model:trop'.
 *               Added 'SetRef', 'calculateRef', 'calculateRINEXRef', 'calculateUSERRef',
 *                 'DGNSSRoverUSERRef' and 'DGNSSUserRoverRef' receiver positioning modes. This modes
 *                 are for using a reference file with the rover position.
 *               Added 'DGNSSRoverUSERGeod', 'DGNSSUserRoverRefGeod', 'DGNSSUserGeodbaseline', 
 *                 'DGNSSUserGeodRinexRover', 'DGNSSRefGeodRoverUSERGeod', 'DGNSSRefCarRoverUSERGeod'
 *                  and 'DGNSSRefGeodRoverUSERCar' receiver positioning modes for supporting
 *                  geodetic coordinates. Internally, it will convert the coordinates to cartesian
 *                  and switch to the equivalent cartesian mode.
 *               Added compilation date and time next to the "gLAB version" line.
 *               Added INFO message when SNR mask is disabled.
 *               Added INFO message about KML Timestamp options.
 *               Added INFO message for selected KML timestamp regions.
 *               Added INFO message for selected inclusion and exclusion areas in SBAS plots mode.
 *               Added INFO message with user defined geodetic coordinates (when provided).
 *               Changed SBAS and DGNSS defaults for Data Gap, SNR and N-consecutive. In both modes,
 *             	SNR mask is set to 33 dbHz, Data Gap to 10 seconds and N-consecutive is disabled.
 *               Changed parameters name from 'RTCMbaseline', 'RTCMRinexRover', 'RTCMRoverUSER',
 *                 'RTCMUserbaseline', 'RTCMUserRinexRover' and 'RTCMRefRoverUSER' to 'DGNSSbaseline',
 *                 'DGNSSRinexRover', 'DGNSSRoverUSER', 'DGNSSUserbaseline', 'DGNSSUserRinexRover'
 *                 and 'DGNSSRefRoverUSER' respectively. The old names can still be used in order to
 *                 maintain compatibility with older versions.
 *               Changed default standard deviation from 1 to 5 metres for single frequency code, from
 *                 1 to 3 metres for PC and from 0.01 to 0.03 metres for LC.
 *               If troposphere model is disabled, gLAB will automatically disable computation of wet
 *                 troposhere residual in the filter.
 *               In RTCM conversion mode, gLAB will automatically replace output files instead of exiting.
 *               Improved gLAB detection of executable directory detection for Mac compatibility.
 *               If receiver antenna phase center is set by user, then receiver antenna phase center
 *                 variation correction will be automatically disabled (previously it appeared as
 *                 enabled in the INFO messages, but during the modelled it was skipped).
 *               In orbit comparison or orbit show mode, gLAB will not always show the end time of
 *                 the comparison regardless of the number of concatenations of the input files
 *                 (previously it was not shown if file had more than three days concatenated).
 *               Tweaked the code to remove the different compiler warnings when compiling with flags 
 *                 '-pedantic', '-Wall' and '-std=gnu99' (without using the '-O' flag). In each
 *                 platform, the compiler issued different warnings.
 *               Fixed bug that made gLAB discard all satellites with reason "Arc too short"
 *                 even though the arc was very large.
 *               Fixed crash in SBAS plot mode when hourly maps were enabled and continuity risk
 *                 maps were disabled.
 *               Fixed bug incorrectly reading values for parameter '-output:kml:tstamprange' when
 *                 it was provided through a configuration file.
 *               Fixed bug that made the KML time ranges to be duplicated or triplicated in memory
 *                 due to user options are read several times.
 *               Fixed bug that made inclusion and exclusion areas for SBAS maps to be duplicated 
 *                 or triplicated in memory due to user options are read several times (in order to 
 *                 override defaults) This will slightly reduce SBAS maps computation time with 
 *                 maps including inclusion or exclusion areas.
 *               Fixed solution not converging in receiver positioning modes 'calculateRINEX' and
 *                 'calculateUser' when the initial position was very far from the real position.
 *                 This was due to gLAB believed initial coordinates were always close to the real ones,
 *                 therefore, satellite elevation filtering was enabled since the beginning instead
 *                 of waiting for the solution to converge for enabling this filter.
 *               Fixed bug not computing Stanford-ESA when SBAS summary was not enabled.
 *               Updated help messages.
 * -----------
 *          gLAB v5.1.1
 * Release: 2017/12/22
 * Change Log:   Added "Add User to RINEX" mode. In this mode, gLAB reads an observation file, an user added
 *                 error file and writes the a RINEX observation file with the same data but with the user 
 *                 added error in the measurements.
 *               Changed receiver ARP correction default option in SBAS and DGNSS. Now it will be enabled by
 *                 default in SBAS and DGNSS modes (before it was disabled).
 *               Changed detection method for detecting if standard output is piped. This method works in
 *                 Windows, Linux and Mac. This allows gLAB to behave the same way in Linux and Mac when
 *                 detecting if standard output is piped or if process is in background (in order to hide
 *                 the progress bar). In Windows, it cannot detect if process is run in background, so if
 *                 output is a pipe or is not a terminal by default it will hide the progress bar.
 *               Fixed DGNSS corrections not being updated during one epoch when a new header was found in
 *                 the rover observation file (only when rover file is concatenated). This ocurred only in the
 *                 first epoch after the new header.
 *               Updated help messages.
 * -----------
 *          gLAB v5.1.2
 * Release: 2018/01/12
 * Change Log:   Added OpenMP preprocessor directives for multithread processing for the modelling section and
 *                 for SBAS maps mode (gLAB needs to be rebuild with '-fopenmp' in order to enable multithreading).
 *               Added parameter '-numthreads' in order to set the maximum number of threads in multithread
 *                 processing. If this parameter is not set, it will use as many threads as available CPU.
 *                 (gLAB needs to be rebuild with '-fopenmp' in order to enable multithreading).
 *               If gLAB is build with multithreading, the INFO message with the gLAB version will show that
 *                 multithreading is enabled.
 *               Changed progress bar in SBAS plots mode. Now it will also show the current epoch and epochs
 *                 left in HH:MM:SS format.
 *               Progress bar in SBAS plots mode will now appear with 0.0% progress when the process starts.
 *                 Before it didn't appear until progress had advanced to 0.1%, which could take some long
 *                 time and therefore make the user think that the gLAB was not working.
 *               Updated help messages.
 * -----------
 *          gLAB v5.1.3
 * Release: 2018/01/19
 * Change Log:   Added a INFO message with the list of SBAS GEO satellites excluded (for SBAS plots mode).
 *               Concatenated IONEX files are now supported, for both ionsphere data and DCB data.
 *               Improved handling of concatenated files for Klobuchar/BeiDou ionosphere parameters. Now it will only read
 *                 new parameters from next day when the observation file changes day. Before it could read them when
 *                 the observation file changed day or when the broadcast orbits had expired.
 *               Changed OpenMP directives "#pragma omp critical" to "#pragma omp atomic". Atomic statements are faster
 *                 as they require less overhead, they don't block other threads operations (except for the current atomic
 *                 one) and do not require to be named in order to distinguish between the atomic sections (unnamed critical
 *                 sections block all threads accessing any unnamed critical section).
 *               Fixed bug that made gLAB show an error message and exit in positioning mode when a concatenated RINEX
 *                 navigation file was read.
 * -----------
 *          gLAB v5.2.0
 * Release: 2018/03/09
 * Change Log:   Added option '-model:maxurabrdc' for setting a maximum value for URA in the broadcast message.
 *               Added option '-model:udreithreshold' for setting a maximum value for UDREI in SBAS fast correction messages.
 *               Added option '-model:sigfltnomt10offset' for changing the offset added to fast and slow corrections sigma
 *                 when SBAS message type 10 is not used.
 *               Added option '-filter:fixedweightsat' for setting a custom fixed weight for each satellite.
 *               Added option '-filter:sinelevweightsat' for setting a weight dependent on the inverse of the elevation.
 *               Added option '-filter:sinelevweightsat' for setting a weight dependent on the inverse of the elevation for
 *                 each satellite.
 *               Added option '-filter:snrweight' for setting a weight dependent on the SNR.
 *               Added option '-filter:snrweightsat' for setting a weight dependent on the SNR for each satellite.
 *               Added option '-filter:snrelevweight' for setting a weight dependent on the inverse of the elevation and the SNR.
 *               Added option '-filter:snrelevweightsat' for setting a weight dependent on the inverse of the elevation and the SNR
 *                 for each satellite.
 *               Added the option to set the constant value of all filter weight to the URA value provided in the brodcast navigation
 *                 message. To set, instead of providing a fixed value, provide the text 'URA'.
 *               Added option '-filter:snrweight:comb' for setting how to compute the SNR value for combinations.
 *               Added option '-filter:snrweight:combsat' for setting how to compute the SNR value for combinations for each satellite.
 *               Added option '-filter:sbasdgnssweightmode' for setting how to compute the weight in SBAS and DGNSS modes.
 *               Added option '-filter:sbasdgnssweightmodesat' for setting how to compute the weight in SBAS and DGNSS modes for each satellite.
 *               Added option '-print:summary'. This make the summary no more being tied to '-print:info' option. Furthermore, the summary
 *                 will be also printed even if receiver position is not fixed (but error percentiles values will not be computed).
 *               Added messages (in command line only) at the start of the processing indicating which file is reading.
 *               Options '-pre:sat' and  -pre:snrsel' now accepts a range of satellites.
 *               Option '-pre:sat' now accepts an optional '+' or '-' sign to indicate whether to select or unselect the listed
 *                 satellite.
 *               All options for setting the filter weights now accept measurement number '0'. This value sets the given weight to all
 *                 measurements in the filter.
 *               Changed exit code of gLAB after correct execution from '1' to '0' in order to match linux standards.
 *               User defined SNR threshold now accepts decimal values.
 *               gLAB can now read configuration files with comments (starting with '#' symbol) next to the parameters.
 *               Removed units in GDOP parameter (GDOP is adimensional).
 *               If gLAB finishes processing and no epochs were processed, but no error will occur, gLAB will reenable the cursor before exiting if
 *                 progress is being printed.
 *               Fixed bug that made not to add a hash ('#') in the first line of a sigma multipath file, a reference file and to a user defined error
 *                 file (the line with the gLAB version).
 *               Updated help messages.
 *               
 * -----------
 *       END_RELEASE_HISTORY
 *****************************/


/* System modules */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#if !defined (__WIN32__)
	#include <signal.h>
#endif
#if defined _OPENMP
 #include <omp.h>
#endif

/* External classes */
#include "input.h"
#include "preprocessing.h"
#include "model.h"
#include "filter.h"
#include "dataHandling.h"
#include "output.h"


/* Internal types, constants and data */
#define VERSION "5.2.0"

// Global variables for printing MODEL buffer
char	printbufferMODEL[MAX_SATELLITES_VIEWED][MAX_INPUT_LINE];

// Global variables for printing SBASCORR buffer
char	printbufferSBASCORR[MAX_SATELLITES_VIEWED][MAX_INPUT_LINE];

// Global variables for printing SBASVAR buffer
char	printbufferSBASVAR[MAX_SATELLITES_VIEWED][MAX_INPUT_LINE];

// Global variables for printing SBASIONO buffer
char	printbufferSBASIONO[MAX_SATELLITES_VIEWED][MAX_INPUT_LINE];

// Global variables for printing MODEL buffer
char	printbufferSBASUNSEL[MAX_SATELLITES_VIEWED][MAX_INPUT_LINE];

// Global variables for printing DGNSS buffer
extern char	printbufferDGNSS[MAX_SATELLITES_VIEWED][MAX_INPUT_LINE];

// Global variables for printing SATSEL buffer
extern int	linesstoredSATSEL[MAX_SATELLITES_VIEWED];
extern char	printbufferSATSEL[MAX_SATELLITES_VIEWED][MAX_LINES_BUFFERED][MAX_INPUT_LINE];

// Global variables for printing PREFIT buffer
extern char	printbufferPREFIT[MAX_SATELLITES_VIEWED][MAX_INPUT_LINE];

// Global variables for printing POSTFIT buffer
extern char	printbufferPOSTFIT[MAX_SATELLITES_VIEWED][MAX_INPUT_LINE];

// Global variables for printing EPOCHSAT buffer
extern char	printbufferEPOCHSAT[MAX_INPUT_LINE];

// Global variables for printing FILTER buffer
extern char	printbufferFILTER[MAX_INPUT_LINE];

//Global variable for printing process (it might change with signals if process is in background)
int printProgress;		// 0 => Do not print current epoch being processed to terminal (auto disables if stdout is not a terminal)
						// 1 => Print current epoch being processed to terminal

int printProgressWasDisabled=0; //This variable is set to 1 if printProgress was set to 1 and then set to 0 due to process was moved to the background
int printProgressConvert=0;	//For file conversion mode only
							// 0 => Do not print current epoch being processed to terminal (auto disables if stdout is not a terminal)
							// 1 => Print current epoch being processed to terminal

int	ReadL1CAsItself=0; //Variable to enable/disable L1C to be read as itself or as L1P (to be erased when measurement management is finished)

#if !defined (__WIN32__)
	//Global variable for pid (used for signals and directory handling)
	pid_t	pid;

	//Global variables to disable/enable cursor in terminal when receving SIGNALS
	FILE 	*StdoutStream;
	char 	enableCursor[20];
	char 	disableCursor[20];

	//Define SIGINT handling function (Ctrl+C)
	void sigIntSignal (int p) {
		if (enableCursor[0]!='\0' && StdoutStream!=NULL) {
			fprintf(StdoutStream,"%s\n",enableCursor);
			//fflush(StdoutStream);
		}
	    exit(-1);
	}
	//Define SIGTSTP handling function (Ctrl+Z) (Do not confuse with SIGSTOP signal, which cannot be blocked)
	void sigStpSignal (int p) {
		if (enableCursor[0]!='\0' && StdoutStream!=NULL) {
			fprintf(StdoutStream,"%70s%s","",enableCursor);
			fflush(StdoutStream);
		}
	    kill(pid,SIGSTOP);
	}
	//Define SIGCONT handling function
	void sigContSignal (int p) {
		pid_t	fg;

		//Check if standard input is from a terminal (interactive). If it isn't, probably
		//or process in the background or from an automatic process. Disable progress bar
		if (!isatty(fileno(stdin))) {
			if (printProgress==1) {
				printProgressWasDisabled=1;
			}
			printProgress=0;
		} else {
			fg=tcgetpgrp(STDIN_FILENO);
			if (fg==-1) {
				//Stdin is a pipe. Disable progress print
				printProgress=0;
				if (printProgress==1) {
					printProgressWasDisabled=1;
				}
			} else if (fg!=getpgrp()) {
				//We are in the background. Disable progress print
				if (printProgress==1) {
					printProgressWasDisabled=1;
				}
				printProgress=0;
			} else {
				//We are in the foreground again. Disable cursor
				if (printProgressWasDisabled==1) {
					printProgress=1;
				}
				if (disableCursor[0]!='\0' && StdoutStream!=NULL && printProgress==1) {
					fprintf(StdoutStream,"%s",disableCursor);
					//fflush(StdoutStream);
				}
			}
		}
	}
#endif



// Enumerator for Navigation kinematics
enum NK {
	NKND,
	NKstatic,
	NKkinematic
};

// Enumerator for Navigation mode
enum NM {
	NMND,
	NMppp,
	NMstandalone
};

// Enumerator for Navigation measurements
enum NO {
	NOND,
	NOpseudorange,
	NOcarrierphase
};

// Struct for support options
typedef struct {
	enum	NK					navKinematics;
	enum	NM					navMode;
	enum	NO					navObservables;
	enum	IonoModel			ionoModel;
	enum	TropModelNominal	tropNominal; 
	enum	TropModelMapping	tropMapping;
	enum	P1C1DCBModel		p1c1dcbModel;
	enum	P1P2DCBModel		p1p2dcbModel;
	int							estimateTroposphere;
	int							troposphericCorrection;
	char						cfgFile[MAX_INPUT_LINE];
	char						obsFile[MAX_INPUT_LINE];
	char						navFile[2][MAX_INPUT_LINE];
	int							numNav;
	char						SP3File[2][MAX_INPUT_LINE];
	int							numSP3;
	char						orbFile[2][MAX_INPUT_LINE];
	int							numOrb;
	char						clkFile[2][MAX_INPUT_LINE];
	int							numClk;
	char						conFile[MAX_INPUT_LINE];
	char						outFile[MAX_INPUT_LINE];
	char						kmlFile[MAX_INPUT_LINE];
	char						kml0File[MAX_INPUT_LINE];
	char						SP3OutputFile[MAX_INPUT_LINE];
	char						RefPosOutputFile[MAX_INPUT_LINE];
	char						antFile[MAX_INPUT_LINE];
	char						klbFile[MAX_INPUT_LINE];
	char						beiFile[MAX_INPUT_LINE];
	char						inxFile[MAX_INPUT_LINE];
	char						GalFile[MAX_INPUT_LINE];
	char						fppFile[MAX_INPUT_LINE];
	char						neqFile[MAX_INPUT_LINE];
	char						tgdFile[2][MAX_INPUT_LINE];
	char						recFile[MAX_INPUT_LINE];
	char						snxFile[MAX_INPUT_LINE];
	char						sbasFile[MAX_INPUT_LINE];
	char						sbasAvailplotsFile[MAX_INPUT_LINE];
	char						sbasAvailplotsFileNoExtension[MAX_INPUT_LINE];
	char						sbasRiskplotsFile[MAX_INPUT_LINE];
	char						sbasRiskplotsFileNoExtension[MAX_INPUT_LINE];
	char						sbasDiscontinuityFile[MAX_INPUT_LINE];
	char						sbasDiscontinuityFileNoExtension[MAX_INPUT_LINE];
	char						sbasIonoplotsFile[MAX_INPUT_LINE];
	char						sbasIonoplotsFileNoExtension[MAX_INPUT_LINE];
	char						rnxFile[MAX_INPUT_LINE];
	char						dataASCIIFile[MAX_INPUT_LINE];
	char						antennaASCIIFile[MAX_INPUT_LINE];
	char						dgnssFile[MAX_INPUT_LINE];
	char						rtcmFile[MAX_INPUT_LINE];
	char						rtcm2File[MAX_INPUT_LINE];
	char						rtcm3File[MAX_INPUT_LINE];
	char						stanfordESAFile[MAX_INPUT_LINE];
	char						stanfordESALOIFile[MAX_INPUT_LINE];
	char						SBASIONOFile[MAX_INPUT_LINE];
	char						sigmamultipathFile[MAX_INPUT_LINE];
	char						addederrorFile[MAX_INPUT_LINE];
	char						posReferenceFile[MAX_INPUT_LINE];
	int							numTGD;
	int							numP1C1DCB;
	int							numP1P2DCB;
	int							numP1P2RINEX;
	int							numP1P2IONEX;
	int							numP1P2FPPP;
	int							csLLI;
	int							csLI;
	int							csBW;
	int							csL1C1;
	int							totalFilterMeasurements;
	int							numsmoothWith;
	enum MeasurementType		measurement[MAX_FILTER_MEASUREMENTS];
	enum MeasurementType		smoothWith[MAX_FILTER_MEASUREMENTS];
	enum CombineWeightsMode		CombineWeightMode[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS];  // Vector containing how to combine the weights
	enum SNRWeightComb			SNRweightComb[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS]; // Vector containing how to get the SNR when a weight with SNR is used
	enum WeightMode				weightMode[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS];	// Vector containing the type of weight applied to each satellite and measurement
	double 						SNRweightCombVal[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS][2]; // Vector containing the factors for combining the SNR
	double						WeightConstantsValues[MAX_GNSS][MAX_SATELLITES_PER_GNSS][MAX_FILTER_MEASUREMENTS][3];	// Vector containing the constants to compute the weights of the measurements
	double						filterParams[3][MAX_PAR];
	// filterParams is the data for Phi, Q and P0, the first dimension of the matrix
	// accounts for: 0->Phi,  1->Q  and  2->P0. To access it: PHI_PAR, Q_PAR and P0_PAR
	// The second dimension accounts for the unknown types, in particular, to access it
	// it should be used: DR_UNK, DT_UNK, TROP_UNK and BIAS_UNK
	int							discardEclipsedSatellites;
	enum ReceiverType			setRecType;
	double						stfdesaxmax;
	double						stfdesaymax;
	double						stfdesaxres;
	double						stfdesayres;
	char						deprecatedMessages[MAX_INPUT_LINE];	//String to save WARNING for deprecated options
	int							disableCursor;
	int							UserSetPrintProgress;
} TSupportOptions;

/**************************************
 * Declarations of internal operations
 **************************************/

/*****************************************************************************
 * Name        : initSupportOptions
 * Description : Initialises support options
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TSupportOptions  *sopt          IO N/A  TSupportOptions structure to initialise
 *****************************************************************************/
void initSupportOptions (TSupportOptions *sopt) {
	int	i,j,k;

	sopt->navKinematics = NKND;
	sopt->navMode = NMND;
	sopt->navObservables = NOND;
	sopt->cfgFile[0] = '\0';
	sopt->obsFile[0] = '\0';
	sopt->conFile[0] = '\0';
	sopt->recFile[0] = '\0';
	sopt->snxFile[0] = '\0';
	sopt->navFile[0][0] = '\0';
	sopt->SP3File[0][0] = '\0';
	sopt->orbFile[0][0] = '\0';
	sopt->clkFile[0][0] = '\0';
	sopt->navFile[1][0] = '\0';
	sopt->SP3File[1][0] = '\0';
	sopt->orbFile[1][0] = '\0';
	sopt->clkFile[1][0] = '\0';
	sopt->tgdFile[0][0] = '\0';
	sopt->tgdFile[1][0] = '\0';
	sopt->numNav = 0;
	sopt->numSP3 = 0;
	sopt->numOrb = 0;
	sopt->numClk = 0;
	sopt->numTGD = 0;
	sopt->numP1C1DCB = 0;
	sopt->numP1P2DCB = 0;
	sopt->numP1P2RINEX = 0;
	sopt->numP1P2IONEX = 0;
	sopt->numP1P2FPPP = 0;
	sopt->outFile[0] = '\0';
	sopt->kmlFile[0] = '\0';
	sopt->kml0File[0] = '\0';
	sopt->SP3OutputFile[0] = '\0';
	sopt->RefPosOutputFile[0] = '\0';
	sopt->antFile[0]= '\0';
	sopt->klbFile[0] = '\0';
	sopt->beiFile[0] = '\0';
	sopt->fppFile[0] = '\0';
	sopt->neqFile[0] = '\0';
	sopt->inxFile[0] = '\0';
	sopt->GalFile[0] = '\0';
	sopt->sbasFile[0] = '\0';
	sopt->sbasAvailplotsFile[0] = '\0';
	sopt->sbasAvailplotsFileNoExtension[0] = '\0';
	sopt->sbasRiskplotsFile[0] = '\0';
	sopt->sbasRiskplotsFileNoExtension[0] = '\0';
	sopt->sbasDiscontinuityFile[0] = '\0';
	sopt->sbasDiscontinuityFileNoExtension[0] = '\0';
	sopt->sbasIonoplotsFile[0] = '\0';
	sopt->sbasIonoplotsFileNoExtension[0] = '\0';
	sopt->rnxFile[0] = '\0';
	sopt->dataASCIIFile[0] = '\0';
	sopt->antennaASCIIFile[0] = '\0';
	sopt->dgnssFile[0] = '\0';
	sopt->rtcmFile[0] = '\0';
	sopt->rtcm2File[0] = '\0';
	sopt->rtcm3File[0] = '\0';
	sopt->stanfordESAFile[0] = '\0';
	sopt->stanfordESALOIFile[0] = '\0';
	sopt->SBASIONOFile[0]='\0';
	sopt->sigmamultipathFile[0]='\0';
	sopt->addederrorFile[0]='\0';
	sopt->posReferenceFile[0]='\0';
	sopt->ionoModel = UNKNOWN_IM;
	sopt->troposphericCorrection = -1;
	sopt->tropNominal = UNKNOWN_TMNominal; 
	sopt->tropMapping = UNKNOWN_TMMapping;
	sopt->p1c1dcbModel = p1c1UNKNOWN;
	sopt->p1p2dcbModel = p1p2UNKNOWN;
	sopt->csLI = -1;
	sopt->csBW = -1;
	sopt->csL1C1 = -1;
	sopt->csLLI = -1;
	sopt->estimateTroposphere = -1;
	sopt->totalFilterMeasurements = -1;
	sopt->discardEclipsedSatellites = -1;
	sopt->stfdesaxmax = 50;
	sopt->stfdesaymax = 50;
	sopt->stfdesaxres = 0.1;
	sopt->stfdesayres = 0.1;
	sopt->numsmoothWith = 0;
	for (i=0;i<MAX_FILTER_MEASUREMENTS;i++) {
		sopt->measurement[i] = NA;
		sopt->smoothWith[i] = NA;
	}
	for (i=0;i<3;i++) {
		for (j=0;j<MAX_PAR;j++) {
			sopt->filterParams[i][j] = -1;
		}
	}
	for(i=0;i<MAX_GNSS;i++) {
		for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
			for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
				sopt->weightMode[i][j][k]=UnknownWeight;
				sopt->CombineWeightMode[i][j][k]=CombineWeightUnknown;
				sopt->SNRweightComb[i][j][k]=SNRWeightUnknown;
			}
		}
	}
	
	sopt->setRecType = rtNA;
	sopt->deprecatedMessages[0] = '\0';
	sopt->disableCursor=1;
	sopt->UserSetPrintProgress=0;
}

/*****************************************************************************
 * Name        : showHelp
 * Description : Shows the program help in the standard output
 * Parameters  : None
 *****************************************************************************/
void showHelp () {

	#if defined _OPENMP
		printf("gLAB version v%s (with OpenMP multithread), built on %s %s\n",VERSION,__DATE__,__TIME__);
	#else
		printf("gLAB version v%s, built on %s %s\n",VERSION,__DATE__,__TIME__);
	#endif
	printf("GNSS LABORATORY. Tool to analyse GNSS data\n\n");
	printf("Supervisor:\n");
	printf("    Jaume Sanz Subirana     group of Astronomy and GEomatics (gAGE/UPC)\n\n");
	printf("Author:\n");
	printf("    Pere Ramos-Bosch        group of Astronomy and GEomatics (gAGE/UPC)\n\n");
	printf("Maintainer:\n");
	printf("    Adria Rovira-Garcia     group of Astronomy and GEomatics (gAGE/UPC)\n\n");
	printf("Developers:\n");
	printf("    Deimos Ibanez Segura    group of Astronomy and GEomatics (gAGE/UPC)\n\n");
	printf("    Jesus Romero Sanchez    group of Astronomy and GEomatics (gAGE/UPC)\n\n");
	printf("                            Please send any bugs/comments to:  glab.gage @ upc.edu   \n\n");
	printf("Website:\n");
	printf("    www.gage.es/gLAB\n\n");     
	printf("Usage:\n");
	printf("    gLAB [options]\n\n");
	printf("Options (all options are case insensitive):\n");
	printf("    -help                   Shows this help\n");
	printf("    -messages               Shows the fields of each output message (see below, 'VERBOSE OPTIONS')\n");
	printf("    -examples               Shows some examples to call the program\n");
	printf("    -config                 Shows some info on the configuration file\n");
	printf("    -usererrorfile          Shows an example of user-defined error configuration file\n");
	printf("    -sigmamultipathfile     Shows an example of user multipath model configuration file\n");
	printf("    -rtcmv2conversioninfo   Shows detailed information of the text files generated from a RTCM v2.x conversion\n");
	printf("    -referenceposfile       Shows an example of reference position file\n");
	#if defined _OPENMP
		printf("\n    -numthreads <num>     Sets the number of parallel threads to be used in the processing (multithread is only\n");
		printf("                             used in the cycle-slip detection and modelling sections). Multi-thread is only\n");
		printf("                             available if gLAB is compiled with '-fopenmp' flag (OpenMP threads)\n"); 
	#endif
	printf("\n  INPUT OPTIONS\n");
	printf("    -input:cfg <file>       Sets the input configuration file\n");
	printf("    -input:obs <file>       Sets the input RINEX observation file\n");
	printf("    -input:nav <file>       Sets the input RINEX navigation message file\n");
	printf("    -input:sp3 <file>       Sets the input SP3 orbits and clocks file\n");
	printf("    -input:orb <file>       Sets the input SP3 orbits\n");
	printf("    -input:clk <file>       Sets the input clock file\n");
	printf("    -input:con <file>       Sets the input constellation status file (default GPSConstellationStatus.txt)\n");
	printf("    -input:ant <file>       Sets the input ANTEX satellite/receiver antenna data file\n");
	printf("    -input:klb <file>       Sets the input RINEX navigation file for Klobuchar corrections, if this parameter\n");
	printf("                             is avoided, it is used the -input:nav file\n");
	printf("    -input:bds <file>       Sets the input RINEX navigation file for BeiDou corrections, if this parameter\n");
	printf("                             is avoided, it is used the -input:nav file\n");
	printf("    -input:inx  <file>      Sets the input IONEX file for ionospheric corrections\n");
	printf("    -input:fppp <file>      Sets the input FPPP file for ionospheric corrections\n");
	printf("    -input:sbasiono <file>  Sets the input RINEX-B or EMS SBAS file for ionospheric corrections\n");
	printf("    -input:dcb <file>       Sets the input DCB source as a .DCB file, a RINEX navigation file, a IONEX file or a FPPP file.\n");
	printf("                             If more than one file is given for the same model, the last one will be used \n");
	printf("    -input:rec <file>       Sets the input GPS receiver types file (default GPS_Receiver_Types) for DCB usage\n");
	printf("    -input:snx <file>       Sets the input SINEX file for receiver position\n");
	printf("    -input:sbas <file>      Sets the SBAS data file (RINEX-B v2.11 or EMS). Activates SBAS processing mode\n");
	printf("    -input:dgnss <file>     Sets the input RINEX observation file of the Reference Station for DGNSS\n");
	printf("    -input:rtcm <file>      Sets the input RTCM binary file, gLAB will automatically detect the RTCM version\n");
	printf("    -input:rtcm2 <file>     Sets the input RTCM v2.x binary file\n");
	printf("    -input:rtcm3 <file>     Sets the input RTCM v3.x binary file\n");
	printf("    -input:rtcm:initdate <date>     Sets the date when the record of the binary file RTCM began (YYYYMMDD), required only when processing or converting RTCM v2.x and RTCM v3.x\n");
	printf("    -input:rtcm:inithour <hour>     Sets the hour in GPST, when the record of the binary file RTCM began (HH 24-hour format), required when processing or converting RTCM v2.x\n");
	printf("    -input:sigmpath  <file> Sets the data file for user sigma multipath model for SBAS (execute 'gLAB -sigmamultipathfile' for details)\n");
	printf("    -input:usererror <file> Sets the data file for adding user defined error signal to raw measurements (execute 'gLAB -usererrorfile' for details)\n");
	printf("    -input:refpos    <file> Sets the reference position file. It can be a SP3 or a columnar text file (execute 'gLAB -referencefile' for details)\n");
	printf("                             This option will set receiver positioning mode to 'calculate' if non set. See '-pre:setrecpos' option below for details\n");
	printf("    The use of '-input:nav' file will preconfigure the parameters to work in the Standard Point Positioning (SPP).\n");
	printf("    The use of '-input:sp3'/'-input:orb'/'-input:clk' will preconfigure the parameters to work in the Precise Point\n");
	printf("      Positioning (PPP) approach. All the values can be overridden by specifying the parameters. See below for more details\n");
	printf("      on which are the defaults for each mode.\n");
	printf("    The use of '-input:sbas' will preconfigure the parameters to work in SBAS mode.\n");
	printf("    The use of any '-input:rtcm' without a '-input:obs' will result into converting the input RTCM to its corresponding output.\n");
	printf("\n  PREPROCESSING OPTIONS   (use -pre:... to activate, --pre:... to deactivate, when applicable)\n\n");
	printf("    -pre:starttime <date>   Set the start time for processing data. The following date formats are accepted:\n");
	printf("                              YYYYMMDD HH:MM:SS (HH in 24 hour format)\n");
	printf("                              YYYY/MM/DD HH:MM:SS (HH in 24 hour format)\n");
	printf("                              YYYY/DoY SoD\n");
	printf("                              GPSWeek SoW\n");
	printf("    -pre:endtime <date>     Set the end time for processing data. See '-pre:starttime' option above for date formats\n");
	printf("    -pre:dec #              # = number              Decimate input data by # seconds [default 300 for SPP/PPP, 1 for SBAS, 0 for DGNSS]\n");
	printf("                            In product comparison mode (see below, in 'WORK MODES'), it sets the time step of the\n");
	printf("                            comparisons\n");
	printf("    -pre:sat [+-]g#[-#]     Include/exclude satellites from processing\n");
	printf("                            [+-]   Optional symbols for selecting (with a plus '+') or unselecting (with a minus '-')\n");
	printf("                                    If no symbol is provided, the default behaviour is to unselect satellites\n");
	printf("                            g    = Character determining GNSS system (G->GPS)\n");
	printf("                            #    = PRN number (If #=0, all satellites of the selected GNSS system will be unselected)\n");
	printf("                            [-#] = Optionally, a minus sign ('-') and a second PRN number can be provided in order to set a range\n"); 
    printf("                                   of satellites (of the same constellation)\n");
	printf("    -pre:geoexclude #[,#..] Exclude GEO satellite for SBAS. Data from this GEO will be ignored for SBAS corrections\n");
	printf("                            # = PRN number\n");
	printf("                            [,#..] Optionally, a list of GEO can be provided by separating the numbers with commas (',')\n");
	printf("    -pre:geosel #           Select GEO satellite for SBAS corrections\n");
	printf("                            # = 0 => Use data from all GEO (all GEO mixed) [default in NPA if mixing GEO data is enabled]\n");
	printf("                            # = 1 => Use GEO from the first line of SBAS data read [default in PA]\n");
	printf("                            # = 2 => Use the GEO with highest elevation\n");
	printf("                            %3d <= # <= %3d => Use the GEO with the given PRN\n",MINGEOPRN,MAXGEOPRN);
	printf("    -pre:snr                Enable SNR (Signal to Noise Ratio) deselection. The SNR is read from the observation file. [default on only in SBAS and DGNSS]\n");
	printf("                            If no SNR is present in the observation file, no deselection is done. The default threshold is 33 dBHz\n");
	printf("    -pre:snrsel g#[-#] <val> Set a SNR threshold for a given satellite. If this option is given, SNR deselection will be activated\n");
	printf("                            g     = Character determining GNSS system (G->GPS)\n");
	printf("                            #     = PRN number. If #=0, then the threshold will be applied to all satellites of the selected GNSS system\n");
	printf("                            [-#]  = Optionally, a minus sign ('-') and a second PRN number can be provided in order to set a range\n"); 
    printf("                                      of satellites (of the same constellation)\n");
	printf("                            <val> = Value for SNR threshold in dBHz. This value is compared to the SNR obtained from the RINEX file in all\n");
	printf("                                     code and carrier phase measurements. If no SNR value is present in the RINEX file, this value will be omitted.\n");
	printf("    -pre:elevation <val>    Elevation mask. Satellites below this threshold will be discarded (in degrees) [default 5]\n");
	printf("    -pre:eclipse            Discard satellites under Earth eclipse [default: enabled for PPP, disabled for SPP]\n");
	printf("    -pre:availf g#          Mark frequencies available [default all]\n");
	printf("                            g = Character determining GNSS system (G->GPS)\n");
	printf("                            # = frequencies available\n");
	printf("                            Sample: '-pre:availf G12' Frequencies 1 and 2 of GPS available\n");
	printf("                                    '-pre:availf G1'  Frequency 1 of GPS available, 2 unavailable\n");
	printf("    -pre:smooth <val>       Number of epochs of smoothing [default 0 (disabled) for non SBAS processing, default 100 for SBAS processing]\n");
	printf("    -pre:smoothMeas <n> <meas>         Smooth measurement in filter <n> with measurement type <meas>\n");
	printf("                            In general, <n> is a pseudorange and <meas> a carrier phase, see option '-filter:select' for more\n");
	printf("                            information in the selection of measurements to be used in the filter.\n");
	printf("                            <meas> values for carrier phase smoothing are: L1P, L2P, IF (Iono-free) and DF (divergence-free)\n");
	printf("    -pre:smoothmin <val>    Number of epochs of continuous code smoothing before steady-state operation [default 0 for non SBAS processing, 360 for SBAS processing]\n");
	printf("                            Satellites will be excluded until reaching this steady-state\n");
	printf("    -pre:dgnss:excludeSmoothingConvergenceUser      Exclude satellites during the smoothing convergence in the User Station [default off]\n");
	printf("    --pre:dgnss:excludeSmoothingConvergenceUser     Do not exclude satellites during the smoothing convergence in the User Station\n");
	printf("    -pre:dgnss:excludeSmoothingConvergenceRef       Exclude satellites during the smoothing convergence in the Reference Station,\n");
	printf("                                                     it will be effective if at least one cycle-slip detector is activated [default on]\n");
	printf("    --pre:dgnss:excludeSmoothingConvergenceRef      Do not exclude satellites during the smoothing convergence in the Reference Station\n");
	printf("    -pre:dgnss:smoothmin <val>                      Number of seconds of continuous code smoothing before steady-state operation [default 360]\n");
	printf("    -pre:refpos:deg <val>   Set the interpolation degree for the reference position values [default 0]\n");
	printf("    -pre:setrecpos <val>    <val> = RINEX           Set the user receiver a priori position as the one specified in the RINEX observation file [default]\n");
	printf("                                                     RINEX position will be used for modelling and for NEU error.\n");
	printf("                            <val> = SINEX           Set the user receiver a priori position to be read from a SINEX file (to be\n");
	printf("                                                     specified by the '-input:snx' parameter)\n");
	printf("                                                     SINEX position will be used for modelling and for NEU error.\n");
	printf("                            <val> = <x> <y> <z>      \n");
	printf("                            <val> = Set <x> <y> <z>  Specify the receiver a priori position in metres\n");
	printf("                                                     Sample: '-pre:setrecpos 4789032.7143 176594.9690 4195013.2268'\n");
	printf("                                                     Specified position will be used for modelling and for NEU error.\n");
	printf("                            <val> = SetGeod <Lon> <Lat> <Height> Same as 'SetGeod', but the initial coordinates are given in\n");
	printf("                                                                 geodetic coordinates. Longitude and latitude are given in degrees, within the ranges\n");
	printf("                                                                 [-180..180] and [-90..90] respectively. The height is given in metres\n");
	printf("                            <val> = SetRef          Read reference position for each epoch from reference position file\n");
	printf("                                                     Specified position will be used for modelling and for NEU error.\n");
	printf("                                                     See parameters '-referenceposfile', '-input:refpos' and '-pre:refpos:deg' for help on the reference file\n");
	printf("                            <val> = calculate       The user receiver a priori position will be calculated by the program and used for modelling,\n"); 
	printf("                                                     starting from (%d,0,0).\n",(int)EARTH_RADIUS);
	printf("                                                     This is especially useful when processing moving receivers (trajectories)\n");
	printf("                                                     or when the approximate receiver position is not known. With this option\n");
	printf("                                                     activated, the differential fields of the OUTPUT message will be zero\n");
	printf("                            <val> = calculateRef    Same as 'calculate', but instead of printing (0,0,0) in the output NEU error,\n");
	printf("                                                     it will compute the NEU error using the coordinates from the reference file.\n");
	printf("                                                     See parameters '-referenceposfile', '-input:refpos' and '-pre:refpos:deg' for help on the reference file\n");
	printf("                            <val> = calculateRINEX  Same as calculate, but the initial coordinates will be the one read in the RINEX observation header.\n");
	printf("                                                     If RINEX coordinates are are (0,0,0), then Earth's surface will be used as initial coordinates\n");
	printf("                            <val> = calculateRINEXRef Same as 'calculateRINEX', but instead of printing (0,0,0) in the output NEU error,\n");
	printf("                                                        it will compute the NEU error using the coordinates from the reference file.\n");
	printf("                                                        See parameters '-referenceposfile', '-input:refpos' and '-pre:refpos:deg' for help on the reference file\n");
	printf("                            <val> = calculateUSER <x> <y> <z>  Same as 'calculate', but the initial coordinates will be the one\n");
	printf("                                                                given by the user in this parameter (in metres)\n");
	printf("                            <val> = calculateUSERGeod <Lon> <Lat> <Height>  Same as 'calculateUser', but the initial coordinates are given in\n");
	printf("                                                                geodetic coordinates. Longitude and latitude are given in degrees, within the ranges\n");
	printf("                                                                [-180..180] and [-90..90] respectively. The height is given in metres\n");
	printf("                            <val> = calculateUSERRef <x> <y> <z> Same as 'calculateUSER', but instead of printing (0,0,0) in the output NEU error,\n");
	printf("                                                                 it will compute the NEU error using the coordinates from the reference file.\n");
	printf("                                                                 See parameters '-referenceposfile', '-input:refpos' and '-pre:refpos:deg' for help on the reference file\n");
	printf("                            <val> = calculateUSERGeodRef <Lon> <Lat> <Height>  Same as 'calculateUSERRef', but the initial coordinates are given in\n");
	printf("                                                                geodetic coordinates. Longitude and latitude are given in degrees, within the ranges\n");
	printf("                                                                [-180..180] and [-90..90] respectively. The height is given in metres\n");
	printf("                            <val> = DGNSSbaseline    The user receiver (rover) a priori position will be calculated by the program as in option 'calculate',\n");
	printf("                                                     but the differential fields in the OUTPUT message will computed against the reference antenna position\n");
	printf("                                                     (baseline vector from user\n");
	printf("                                                     to reference station), and the reference station coordinates will be read from RINEX or RTCM input file.\n");
	printf("                            <val> = DGNSSRinexRover  Same as 'DGNSSbaseline', but instead of comparing with the reference station, it will compare the user receiver (rover)\n");
	printf("                                                     coordinates with the coordinates read from the rover RINEX observation file\n");
	printf("                            <val> = DGNSSRoverUSER <RoverX> <RoverY> <RoverZ>\n");
	printf("                                                     	  Same as 'DGNSSbaseline', but instead of comparing with the reference station, it will compare the user receiver\n");
	printf("                                                           (rover) with the position given in this parameter\n");
	printf("                            <val> = DGNSSRoverUSERGeod <RoverLon> <RoverLat> <RoverHeight>\n");
	printf("                                                          Same as 'DGNSSRoverUSER', but the rover coordinates are given in\n");
	printf("                                                          geodetic coordinates. Longitude and latitude are given in degrees, within the ranges\n");
	printf("                                                          [-180..180] and [-90..90] respectively. The height is given in metres\n");
	printf("                            <val> = DGNSSRoverUSERRef     Same as 'DGNSSbaseline', but instead of comparing with the reference station, it will compare the user receiver\n");
	printf("                                                           (rover) solution with the position given by the reference file.\n");
	printf("                                                           See parameters '-referenceposfile', '-input:refpos' and '-pre:refpos:deg' for help on the reference file\n");
	printf("                            <val> = DGNSSUserRoverRef <RefX> <RefY> <RefZ>\n");
	printf("                                                          Same as 'DGNSSRoverUSERRef', but the reference station coordinates will be provided in this parameter\n");
	printf("                                                           (this mode only works when computing DGNSS with a RINEX file)\n");
	printf("                            <val> = DGNSSUserGeodRoverRef <RefLon> <RefLat> <RefHeight>\n");
	printf("                                                          Same as 'DGNSSUserRoverRef', but the reference station coordinates are given in\n");
	printf("                                                          geodetic coordinates. Longitude and latitude are given in degrees, within the ranges\n");
	printf("                                                          [-180..180] and [-90..90] respectively. The height is given in metres\n");
	printf("                            <val> = DGNSSUserbaseline <RefX> <RefY> <RefZ>\n");
	printf("                                                          Same as 'DGNSSbaseline', but the reference station coordinates will be provided in this parameter\n");
	printf("                                                           (this mode only works when computing DGNSS with a RINEX file)\n");
	printf("                            <val> = DGNSSUserGeodbaseline <RefLon> <RefLat> <RefHeight>\n");
	printf("                                                          Same as 'DGNSSUserbaseline', but the reference station coordinates are given in\n");
	printf("                                                          geodetic coordinates. Longitude and latitude are given in degrees, within the ranges\n");
	printf("                                                          [-180..180] and [-90..90] respectively. The height is given in metres\n");
	printf("                            <val> = DGNSSUserRinexRover <RefX> <RefY> <RefZ>\n");
	printf("                                                          Same as 'DGNSSRinexRover', but the reference station coordinates will be provided in this parameter\n");
	printf("                                                           (this mode only works when computing DGNSS with a RINEX file)\n");
	printf("                            <val> = DGNSSUserGeodRinexRover <RefLon> <RefLat> <RefHeight>\n");
	printf("                                                          Same as 'DGNSSUserRinexRover', but the reference station coordinates are given in\n");
	printf("                                                          geodetic coordinates. Longitude and latitude are given in degrees, within the ranges\n");
	printf("                                                          [-180..180] and [-90..90] respectively. The height is given in metres\n");
	printf("                            <val> = DGNSSRefRoverUSER <RefX> <RefY> <RefZ> <RoverX> <RoverY> <RoverZ>\n");
	printf("                                                          Same as 'DGNSSRoverUSER', but the reference station coordinates will be provided in this parameter\n");
	printf("                                                           (this mode only works when computing DGNSS with a RINEX file)\n");
	printf("                            <val> = DGNSSRefGeodRoverUSERGeod <RefLon> <RefLat> <RefHeight> <RoverLon> <RoverLat> <RoverHeight>\n");
	printf("                                                          Same as 'DGNSSRefRoverUSER', but the rover and reference station coordinates are given in\n");
	printf("                                                          geodetic coordinates. Longitude and latitude are given in degrees, within the ranges\n");
	printf("                                                          [-180..180] and [-90..90] respectively. The height is given in metres\n");
	printf("                            <val> = DGNSSRefCarRoverUSERGeod <RefX> <RefY> <RefX> <RoverLon> <RoverLat> <RoverHeight>\n");
	printf("                                                          Same as 'DGNSSRefRoverUSER', but the rover coordinates are given in\n");
	printf("                                                          geodetic coordinates and the reference station in cartesian coordinates.\n"); 
	printf("                                                          Longitude and latitude are given in degrees, within the ranges\n");
	printf("                                                          [-180..180] and [-90..90] respectively. The height is given in metres\n");
	printf("                            <val> = DGNSSRefGeodRoverUSERCar <RefLon> <RefLat> <RefHeight> <RoverX> <RoverY> <RoverZ>\n");
	printf("                                                          Same as 'DGNSSRefRoverUSER', but the reference station coordinates are given in\n");
	printf("                                                          geodetic coordinates and the rover in cartesian coordinates.\n"); 
	printf("                                                          Longitude and latitude are given in degrees, within the ranges\n");
	printf("                                                          [-180..180] and [-90..90] respectively. The height is given in metres\n");
	printf("    -pre:setrectype <val>   <val> = gpsrt           Set the receiver type as the one specified in the GPS_Receiver_Types\n");
	printf("                                                     file (provided by '-input:rec') [default if '-input:rec' provided]\n");
	printf("                            <val> = 0               Set the receiver type as 'Unknown' [default]\n");
	printf("                            <val> = 1               Set the receiver type as 'Cross-correlated'\n");
	printf("                                                     In this mode, P2 will be corrected with the DCB of P1-C1\n");
	printf("                            <val> = 2               Set the receiver type as 'No P1'\n");
	printf("                                                     In this mode, C1 will be used instead of P1\n");
	printf("                            <val> = 3               Set the receiver type as 'Consistent measurements'\n");
	printf("    -pre:prealign           Prealign carrier phase measurements with its corresponding pseudorange [default on]\n");
	printf("    -pre:checkcodejumps     Check for pseudorange jumps and adjust the phase accordingly. See 'Notes for preprocessing' below [default on]\n");
	printf("    --pre:checkcodejumps    Do not check for pseudorange jumps\n");
	printf("    -pre:cs:datagap <val>   Data gap. Maximum period of time, without measurements, allowed before declaring cycle-slip (in seconds)\n");
	printf("                            	[default 40 in SPP/PPP, 10 in SBAS and DGNSS]\n");
	printf("                            NOTE: If <val> is shorter than the sampling rate, all measurements will be discarded\n");
	printf("    -pre:cs:lli             Use Loss of Lock Indicator for cycle-slip detection [default off]\n");
	printf("    --pre:cs:lli            Do not use Loss of Lock Indicator for cycle-slip detection [default off]\n");
	printf("    -pre:cs:ncon            Use N-consecutive epochs for cycle-slip detection [default on in SPP and PPP]\n");
	printf("    --pre:cs:ncon           Do not use N-consecutive epochs for cycle-slip detection [default off in SBAS and DGNSS}\n");
	printf("    -pre:cs:ncon:min <val>  After a short data gap (i.e., shorter than the value set in '-pre:cs:datagap' with default of 40 seconds)\n");
	printf("                             discard the first <val> epochs. NOTE: If sampling interval is greater than 15 seconds, gLAB will\n");
	printf("                             automatically disable this option [default 2]\n");
	printf("    -pre:cs:li              Use the carrier phase geometry-free combination (LI) for cycle-slip detection (2 frequencies) [default in PPP]\n");
	printf("    --pre:cs:li             Do not use carrier phase geometry-free combination (LI) for cycle-slip detection (2 frequencies) [default in SPP]\n");
	printf("                            Li combination is a slow varying function which only has ambiguity and ionosphere\n");
	printf("                            Each epoch and satellite an expected LI value is computed and compared against the\n");
	printf("                            measured one, if this difference is above a certain threshold, a cycle-slip is marked.\n");
	printf("                            This threshold is (max + (min-max)*exp(-dt/t)), being dt the time between epochs\n");
	printf("    -pre:cs:li:maxjump <val> Maximum jump threshold between two consecutive measured LI values [default 1]\n");
	printf("    -pre:cs:li:max <val>     Maximum threshold between estimated and measured LI values [default 0.08]\n");
	printf("    -pre:cs:li:t0 <val>      Time constant to set the threshold between maximum and minimum [default 60]\n");
	printf("    -pre:cs:li:samples <val> Minimum number of epochs needed to fit the second-degree polynomial [default 7]\n");
	printf("    -pre:cs:bw               Use Melbourne-Wubbena (BW) for cycle-slip detection (2 frequencies) [default in PPP]\n");
	printf("    --pre:cs:bw              Do not use Melbourne-Wubbenna (BW) for cycle-slip detection (2 frequencies) [default in SPP]\n");
	printf("                             BW combination is a mixed combination between carrier phase and pseudoranges.\n");
	printf("                             This combination is free of ionosphere and geometry, thence constant, but\n");
	printf("                             has a high noise (due to the pseudorange measurements used). If this noise is\n");
	printf("                             low enough, it is straightforward to detect cycle-slips, but in noisy environments\n");
	printf("                             BW is not able to detect cycle-slips. The algorithm using BW computes the mean and\n");
	printf("                             the standard deviation of the last epochs in order to obtain an estimated value\n"); 
	printf("                             and the noise level of the combination. The estimated value is compared against the\n");
	printf("                             measured value, and the noise level is used for the threshold of this difference.\n");
	printf("                             Difference must be lower than standard deviation multiplied by a number (k-factor).\n");
	printf("                             This threshold has minimum (min) and maximum (max) saturation values.\n");
	printf("    -pre:cs:bw:siginit <val>     Initial standard deviation (in metres) to use in BW after a cycle-slip [default 2]\n");
	printf("    -pre:cs:bw:sigmin <val>      Minimum threshold (in metres) between estimated and measured BW values in relation to its standard deviation [default 0.8]\n");
	printf("    -pre:cs:bw:timewindow <val>  Number of epochs to compute the mobile mean over the Hatch filter [default 300]\n");
	printf("    -pre:cs:bw:kfactor <val>     Relation between estimated and measured BW values in relation to its standard deviation [default 5]\n");
	printf("    -pre:cs:bw:samples <val>     Minimum number of epochs needed to stabilize the mean and sigma in the BW cycle-slip detector [default 2]\n");
	printf("    -pre:cs:l1c1                 Use the L1-C1 combination for cycle-slip detection (1 frequency) [default in PPP]\n");
	printf("    --pre:cs:l1c1                Do not use the L1-C1 combination for cycle-slip detection (1 frequency) [default in SPP]\n");
	printf("    -pre:cs:l1c1:unconcheck      Use the unconsistency check in L1-C1 cycle-slip detection (1 frequency) [default]\n");
	printf("    --pre:cs:l1c1:unconcheck     Do not use the unconsistency check in L1-C1 cycle-slip detection (1 frequency)\n");
	printf("    -pre:cs:l1c1:unconcheck:th  <val> Threshold (in metres) for the unconsistency check in L1-C1 cycle-slip detection (1 frequency) [default 20]\n");
	printf("                             The L1-C1 averages the difference between carrier phase and pseudorange measurements in F1 for several epochs.\n");
	printf("                             This cycle-slip detection method is very useful for single-frequency receivers, as it only requires\n");
	printf("                             measurements from one frequency. As a counterpart, the ionospheric term is different for C1 and L1\n");
	printf("                             thence, this combination will tend to diverge. It becomes necessary to set a smoothing window\n");
	printf("                             to limit this divergence (-pre:cs:l1c1:timewindow). This makes that this method becomes a bit limited\n");
	printf("                             with data rates too low. Ideally this method should be used with rates of 1 Hz\n");
	printf("    -pre:cs:l1c1:kfactor <val>     Relation between estimated and measured L1-C1 values in relation to its standard deviation [default 5]\n");
	printf("    -pre:cs:l1c1:timewindow <val>  Number of epochs to limit the L1-C1 ionosphere divergence [default 300]\n");
	printf("    -pre:cs:l1c1:samples <val>     Minimum number of epochs needed to stabilize the mean and sigma in the L1C1 cycle-slip detector [default 2]\n");
	printf("    -pre:cs:l1c1:init <val>        Initial standard deviation for the threshold calculation in the L1-C1 [default 3] (m) \n");
	printf("    -pre:usererrorafter     Add user defined error after prealigning, checking cycle-slips and smoothing [default off]\n");
	printf("\n  MODELLING OPTIONS   (use -model:... to activate, --model:... to deactivate)\n");
	printf("    -model:iono <val>       <val> = no              Do not correct ionosphere [default in PPP] (equivalent to '--model:iono')\n");
	printf("                                  = Klobuchar       Correct measurements with Klobuchar model [default in SPP]\n");
	printf("                                  = BeiDou          Correct measurements with BeiDou model\n");
	printf("                                  = IONEX           Correct measurements with IONEX file data\n");
	printf("                                  = FPPP            Correct measurements with FPPP file data\n");
	printf("                                  = NeQuick         Correct measurements with NeQuick model\n");
	printf("                                  = SBAS            Correct measurements with SBAS iono corrections (but do not apply any other SBAS correction)\n");
	printf("                            If more than one iono model option is given, the last one will be used\n");
	//printf("    -model:ionoRMS <val>    Maximum error in FPPP iono model correction [default 1] (m) \n");
	printf("    -model:trop             Correct troposphere delay [default on] \n");
	printf("    --model:trop            Do not correct troposphere delay \n");
	printf("    -model:trop:nominal <val>   <val> = Simple     Compute a simple tropospheric nominal depending on receiver's height over the sea level. [default in PPP]\n");
	printf("                                <val> = UNB3       Troposphere nominals are calculated from the receiver's height and estimates of five meteorological\n");
	printf("                                                   parameters: pressure, temperature, water vapour pressure, temperature lapse rate and water vapour lapse rate.\n");
	printf("                                                   It is adopted by SBAS systems (see RTCA-MOPS, 2006). [default in SPP]\n");
	printf("                                <val> = TropoGal   Use Galileo's tropospheric model\n");
	printf("    -model:trop:mapping <val>   <val> = Simple     Compute the mapping as the obliquity factor described in Black and Eisner, 1984. This mapping\n");
	printf("                                                   only depends on satellite elevation and it is common for wet and dry components.  [default in SPP]\n");
	printf("                                <val> = Niell      Compute the mapping described in  A.E. Niell, 1996. This mapping  considers different obliquity\n");
	printf("                                                   factors for the wet and dry components [default in PPP]\n");
	printf("    -model:satclocks        Correct the measurements with the satellite clock offsets estimations [default on]\n");
	printf("    -model:relclock         Correct the measurements with the relativistic clock model [default on]\n");
	printf("    -model:satmovinflight   Consider satellite movement during signal flight time [default on]\n");
	printf("    -model:earthrotinflight Consider Earth rotation during signal flight time [default on]\n");
	printf("    -model:satphasecenter   Correct satellite phase centre to mass centre corrections [default on in PPP, off in SPP]\n");
	printf("    -model:satphasevar      Correct satellite phase centre to mass centre corrections variations with zenital angle [default off for SPP, on for PPP]\n");
	printf("    -model:recphasecenter <val>    <val> = no                Do not correct antenna receiver phase centre [default in SPP]\n");
	printf("                            <val> = ANTEX                    Use the ANTEX file to correct the antenna phase center [default in PPP]\n");
	printf("                            <val> = <nfreq> <dN> <dE> <dU>   Set dN, dE, dU as the antenna phase centre for the frequency <nfreq>\n");
	printf("                                       <nfreq> = Frequency number (typical for GPS, 1 and 2)\n");
	printf("                                       <dN>    = North correction [in metres]\n");
	printf("                                       <dE>    = East correction [in metres]\n");
	printf("                                       <dU>    = Up correction [in metres]\n");
	printf("                            Sample: '-model:recphasecenter 1 0 0 0.11 -model:recphasecenter 2 0 0 0.128'\n");
	printf("                                    Typical AOAD/M_T antenna phase centre correction, 11 cm and 12.8 cm in the\n");
	printf("                                    Up component for frequencies 1 and 2\n");
	printf("    -model:recphasevar      Correct antenna receiver phase centre variations [default off in SPP, on in PPP]\n");
	printf("    -model:strictradome     When using ANTEX to correct the receiver phase centre, this option will force a perfect match between\n");
	printf("                            the antenna name and radome reported in the receiver RINEX file and the ones in the ANTEX file. If this option\n");
	printf("                            is disabled, and the radome is not found, the corrections will be used considering the radome \"NONE\" [default off]\n");   
	printf("    -model:arp <val>        <val> = no              Do not apply any Antenna Reference Point (ARP) correction [default in SPP] (equivalent to '--model:arp')\n");
	printf("                            <val> = RINEX           Use as ARP the information on the RINEX file (field 'ANTENNA: DELTA H/E/N') [default in SBAS, DGNSS and PPP]\n");
	printf("                            <val> = <dN> <dE> <dU>  Set dN, dE, dU as the ARP\n");
	printf("                                       <dN>    = North correction [in metres]\n");
	printf("                                       <dE>    = East correction [in metres]\n");
	printf("                                       <dU>    = Up correction [in metres]\n");
	printf("                                NOTE: In DGNSS mode, if ARP correction is enabled, reference station coordinates will be always be read from reference\n");
	printf("                                       RINEX or RTCM file, while rover ARP will be read from RINEX or set from user values.\n");
	printf("    -model:dcb:p1c1 <val>   <val> = no        Do not correct Differential Code Biases between P1 and C1 codes (equivalent to '--model:dcb:p1c1')\n");
	printf("                                              Do not identify C1 and P1 never\n");
	printf("                            <val> = flexible  Do not correct Differential Code Biases between P1 and C1 codes [default on]\n");
	printf("                                              Identify C1 and P1 when one of them is missing\n");
	printf("                            <val> = strict    Correct  Differential Code Biases between P1 and C1 codes\n");
	printf("                                              Identify C1 and P1 when applicable (defined by the receiver type)\n");
	printf("    -model:dcb:p1p2 <val>   <val> = no        Do not correct Differential Code Biases between codes P1 and P2 (equivalent to '--model:dcb:p1p2')\n");
	printf("                            <val> = RINEX     Correct Differential Code Biases between codes P1 and P2 using TGDs from the RINEX navigation file [default in SPP, off in PPP]\n");
	printf("                            <val> = DCB       Correct Differential Code Biases between codes P1 and P2 from a precise DCB file\n");
	printf("                                              Identify C1 and P1 when applicable (defined by the receiver type)\n");
	printf("                            <val> = IONEX     Correct Differential Code Biases between codes P1 and P2 using DCB from IONEX file\n");
	printf("                            <val> = FPPP      Correct Differential Code Biases between codes P1 and P2 using DCB from FPPP file\n");
	printf("    -model:windup           Correct the wind up term for carrier phase measurements [default]\n");
	printf("    -model:solidtides       Correct the Earth surface deformation due to solid tides [default in PPP, off in SPP]\n");
	printf("    -model:relpath          Correct the path range delay term due to the gravitational gradient between receiver and transmitter\n"); 
	printf("                            [default on in PPP, off in SPP]\n");
	printf("    -model:satellitehealth  Only valid when using broadcast products. Use the healthy flag of the navigation message [default on]\n");
	printf("    -model:brdctranstime    Only valid when using broadcast products. Check that transmission time of message is equal or before the current epoch\n");
	printf("                              of current time [default on for non SBAS processing, off for SBAS processing]\n");
	printf("    -model:maxurabrdc <val> Only valid when using broadcast products. Set the discard threshold for satellites which have an URA value\n");
	printf("                              equal or greater than this value (in metres) [default off]\n");
	printf("    -model:orbit:deg <val>  Precise orbit interpolation degree [default 10]\n");
	printf("    -model:clock:deg <val>  Precise clock interpolation degree [default 0 - no interpolation]\n");
	printf("    -model:orbmaxgaps <val> Set maximum number of gaps between samples used for precise orbit interpolation [default 8]\n");
	printf("    -model:clkmaxgaps <val> Set maximum number of gaps between samples used for precise clock interpolation [default 2]\n");
	printf("    -model:orbtotmaxgaps <val> Set the maximum number of gaps between all samples used for precise orbit interpolation [default 16]\n");
	printf("    -model:clktotmaxgaps <val> Set the maximum number of gaps between all samples used for precise clock interpolation [default 4]\n");
	printf("    -model:orbprevsample    When a concatenated SP3 file is read for orbit data, if the last epoch of the previous day is the same as the first epoch\n");
	printf("                              of the current day, use the last orbit sample of the previous day instead of the first sample of the current day [default off]\n");
	printf("                              This typically occurs with samples at epoch 0h 0m. This option will only have effect if both repeated samples have valid values.\n");
	printf("    -model:clkprevsample    When a concatenated SP3/Clock file is read for clock data, if the last epoch of the previous day is the same as the first epoch\n");
	printf("                              of the current day, use the last orbit sample of the previous day instead of the first sample of the current day [default off]\n");
	printf("                              This typically occurs with samples at epoch 0h 0m. This option will only have effect if both repeated samples have valid values.\n");
	printf("    -model:sbasmaritime     Configure SBAS parameters for SBAS maritime mode (see notes on SBAS maritime below) [default off]\n");
	printf("    -model:alarmmsgtype2    When reading an SBAS message type 0, parse it as type 2 (except if all bits are 0) [default off]\n");
	printf("    -model:ignoretype0      Ignore all SBAS messages type 0 [default off]\n");
	printf("    -model:udreithreshold # Set the UDREI threshold (from fast corrections) for discarding satellites. Satellites with UDREI equal or higher than\n");
	printf("                              this threshold will be discarded. Threshold values have to be in the range [1-13]	[default no threshold]\n");
	printf("    -model:sigfltnomt10offset #  When message type 10 is not available or disabled, the fast correction sigma is computed as UDRE sigma\n");
	printf("                              plus an offset of 8 metres. With this parameter the offset of 8 metres can be changed to any value (in metres)\n");
	printf("    -model:sbasmode <val>   Select navigation mode for SBAS processing:\n");
	printf("                            <val> = PA    Precision Approach [default]\n");
	printf("                            <val> = NPA   Non Precision Approach\n");
	printf("    -model:geoswitch        Enable GEO switch for SBAS processing. See 'Mode and GEO switch notes' below [default off]\n");
	printf("    -model:maintaingeo      If GEO switch for SBAS is enabled, maintain current GEO while possible independently if it is the GEO\n");
	printf("                              selected by the user or it has been selected due to a GEO switch [default on]\n");
	printf("    -model:geofallback      If GEO switch for SBAS is enabled, always try to return to the initial selected GEO [default off]\n");
	printf("    -model:sbasmodeswitch   Enable navigation mode switching for SBAS processing [default off]\n");
	printf("    -model:mixedgeo         Enable the usage of mixed GEO data (messages from all GEO are treated as if there were from an unique GEO) [default off]\n");
	printf("    -model:initcoordnpa     In SBAS mode, if receiver coordinates are to be calculated without giving any initial condition (parameter\n");
	printf("                            -pre:setrecpos calculate), compute the first epochs using Klobuchar until the receiver coordinates have converged.\n");
	printf("                            This is useful due to the initial gLAB coordinate may do that the IPPs (Ionospheric Pierce Point) fall outside the\n");
	printf("                            SBAS region, making all satellites unavailable due to the lack of ionosphere. This option only has effect if SBAS\n");
	printf("                            mode switch is disabled and receiver coordinates are set to 'calculate' [default on]\n");
	printf("    -model:sbasreceiver #   Set receiver class type for SBAS (for computing variance of the airborne receiver)\n");
	printf("                            # = 0 User defined receiver model (defined with parameters '-model:sigmpath', '-model:sigdiv', '-model:signoise' and '-input:sigmpath').\n");
	printf("                                  The receiver sigmas not defined by the user (with the previous parameters) will use the default values for class 2 receiver\n");
	printf("                            # = 1 Class 1 equipment\n");
	printf("                            # = 2,3,4 Class 2,3,4 equipment (all equivalent) [default 2]\n");
	printf("    -model:geoacqtime #     Set the minimum time (in seconds) to consider that gLAB has received enough SBAS corrections from a GEO\n"); 
	printf("                              counting from the first message received [default %d]\n",GEOACQUISIONTIME);
	printf("                              This timer is set to ensure that we have received enough corrections from the GEO we want to switch to.\n");
	printf("                              If this timer is set too low (few seconds), it may happen that we switch to a GEO with not enough data (due to\n");
	printf("                              we are in initialization or the GEO has received an alarm message\n");
	printf("                              gLAB will not switch to any GEO before this time, except for when an alarm message is received and there is no other GEO available\n"); 
	printf("    -model:switchtime #     Set the minimum time (in seconds) between a GEO or mode switch and the following one [default %d]\n",MINIMUMSWITCHTIME);
	printf("                              This timer is set to avoid continuous switching in the same epoch when all GEO do not have enough data.\n");
	printf("                              If this timer is set to zero, a maximum of %d switches per epoch (for both mode and GEO) will be done\n",MAXSWITCHPEREPOCH);
	printf("    -model:sbastmout    <n> <val> Set time out value for SBAS messages (except for fast and range rate corrections) in both modes, PA and NPA\n");
	printf("                            <n> is the message type number\n");
	printf("                            <val> is the time out value (in seconds)\n");
	printf("    -model:sbastmoutpa  <n> <val> Set time out value for SBAS messages (except for fast and range rate corrections) in PA mode\n");
	printf("                            <n> is the message type number\n");
	printf("                            <val> is the time out value (in seconds)\n");
	printf("    -model:sbastmoutnpa <n> <val> Set time out value for SBAS messages (except for fast and range rate corrections) in NPA mode\n");
	printf("                            <n> is the message type number\n");
	printf("                            <val> is the time out value (in seconds)\n");
	printf("    -model:sbastmoutfc      <val>  Set time out value for fast corrections in both modes, PA and NPA\n");
	printf("                              <val> is the time out value (in seconds)\n");
	printf("    -model:sbastmoutfcpa    <val>  Set time out value for fast corrections in PA mode\n");
	printf("                              <val> is the time out value (in seconds)\n");
	printf("    -model:sbastmoutfcnpa   <val>  Set time out value for fast corrections in NPA mode\n");
	printf("                              <val> is the time out value (in seconds)\n");
	printf("    -model:sbastmoutrrc     <val>  Set time out value for range rate corrections in both modes, PA and NPA\n");
	printf("                              <val> is the time out value (in seconds)\n");
	printf("    -model:sbastmoutrrcpa   <val>  Set time out value for range rate corrections in PA mode\n");
	printf("                              <val> is the time out value (in seconds)\n");
	printf("    -model:sbastmoutrrcnpa  <val>  Set time out value for range rate corrections in NPA mode\n");
	printf("                              <val> is the time out value (in seconds)\n");
	printf("    -model:sigmpath <val1> <val2>  Set parameters a,b for sigma multipath for SBAS airborne receiver, being sigma=a+b*e^(-satelevation/10) and satelevation in degrees.\n");
	printf("                              <val1> a value (in metres)\n");
	printf("                              <val1> b value (in metres)\n");
	printf("    -model:sigdiv   <val>   Set a fixed value (in metres) for sigma divergence for SBAS airborne receiver\n"); 
	printf("    -model:signoise <val>   Set a fixed value (in metres) for sigma noise for SBAS airborne receiver\n");
	printf("    -model:nofastcor        Set SBAS fast and RRC corrections values to 0 [default off]\n");
	printf("    -model:norrccor         Set SBAS RRC correction value to 0 [default off]\n");
	printf("    -model:noslowcor        Set SBAS slow corrections values to 0 [default off]\n");
	printf("    -model:noionocor        Set SBAS ionosphere correction value to 0 [default off]\n");
	printf("    -model:nofastsigma      Set SBAS fast and RRC sigmas (sigma UDRE and degradation terms) values to 0 [default off]\n");
	printf("    -model:nofastdeg        Set SBAS fast degradation term value to 0 [default off]\n");
	printf("    -model:norrcsigma       Set SBAS RRC degradation term value to 0 [default off]\n");
	printf("    -model:noslowsigma      Set SBAS slow correction degradation term to 0 [default off]\n");
	printf("    -model:noionosigma      Set SBAS ionosphere sigma to 0 [default off]\n");
	printf("    -model:notroposigma     Set SBAS troposphere sigma to 0 [default off]\n");
	printf("    -model:noenroutesigma   Set SBAS En Route Through NPA degradation term to 0 [default off]\n");
	printf("    -model:nodeltaudre      Set SBAS Delta UDRE factor to 1 [default off]\n");
	printf("    -model:nomt10           Disable use of message type 10 in all modes [default off]\n");
	printf("    -model:nomt2728         Disable use of messages type 27 and 28 in all modes (this is equivalent to parameter '-model:nodeltaudre') [default off]\n");
	printf("    -model:dgnss:sigmainflation   The sigma is inflated during the smoother convergence (see DGNSS notes at the end) [default on]\n");
	printf("    --model:dgnss:sigmainflation  Do not use the sigma inflation during the smoother convergence\n");
	printf("    -model:dgnss:maxage <val>     Set the maximum age value (in seconds) to stop applying DGNSS corrections [default 31]\n");
	printf("    -model:dgnss:maxcorrval <val> Set the maximum value for a DGNSS correction to be considered valid (in metres) [default 500]\n");
	printf("     NOTE: When setting any fast, slow, ionosphere correction or their sigmas to 0, gLAB will still check all the conditions\n");
	printf("             for the current mode. For example, if gLAB is in PA mode and the '-model:nofastcor' parameter is set, then it\n");
	printf("             will search for a fast correction, and if it is available, it will set the value to 0 instead of the one\n");
	printf("             given in the SBAS message. If there is no SBAS fast correction available, the satellite will not be used.\n");
	printf("     NOTE: The SBAS timeouts given by the user will override the defaults stated in MOPS-D.\n");
	printf("\n  FILTERING OPTIONS\n");
	printf("    -filter:stepdetector    Check for jumps in measurements using the prefits residuals (only for C1C measurement) [default off]\n");
	printf("                             Use '--filter:stepdetector' to disable it\n");
	printf("    -filter:prefitoutliers:median  <val> Check for outliers in the prefits residuals using the median, with <val> (in metres) as the threshold [default off]\n");
	printf("                             Use '--filter:prefitoutliers:median' or '-filter:prefitoutliers:median 0' to disable it. See notes on prefit outlier detectors below\n");
	printf("    -filter:prefitoutliers:abs  <val> Check for outliers in the prefits residuals comparing absolute values, with  <val> (in metres) as the threshold [default off]\n");
	printf("                             Use '--filter:prefitoutliers:abs' or '-filter:prefitoutliers:abs 0' to disable it. See notes on prefit outlier detectors below\n");
	printf("    -filter:trop            Estimate the troposphere of the station [default in PPP with carrier phase] ('--filter:trop' to disable it)\n");
	printf("    -filter:nav <nav>       <nav> = static          Process supposing a static receiver [default in PPP]\n");
	printf("                                  = kinematic       Process supposing a moving receiver [default in SPP]\n");
	printf("    -filter:meas <meas>     <meas> = pseudorange    Use only pseudorange for positioning\n");
	printf("                                   = carrierphase   Use pseudorange and carrier phase for positioning [default]\n");
	printf("    -filter:select <num> <meas1> <meas2> ...        Select the measurements or combinations to include in the filtering\n");
	printf("                            <num> = Number of measurements/combinations\n");
	printf("                            <measN> = List of measurements/combinations\n");
	printf("                            [Defaults]: PPP - Pseudorange      => 1 PC\n");
	printf("                            [Defaults]: PPP - Carrierphase     => 2 PC LC\n");
	printf("                            [Defaults]: SPP - Pseudorange      => 1 C1C\n");
	printf("                            [Defaults]: SPP - Carrierphase     => 2 C1C L1P\n");
	printf("    -filter:fixedweight <n>  <a>         Apply the specified standard deviation to the measurement 'n', to be used as weight in the filter.\n");
	printf("                            <n>    Measurement number. If <n> is 0, it will be applied to all measurements in the filter.\n");
	printf("                            <a>    = URA  Use the URA value from the broadcast message (not valid in PPP)\n");
	printf("                                   = #    Value for the standard deviation of the measurement (metres)\n");
	printf("                            The filter shall apply as weight = 1/(<a>^2)\n");
	printf("                            Sample: '-filter:fixedweight 1 2'    Set 2 metres of standard deviation to measurement 1 in filter\n");
	printf("                                    '-filter:fixedweight 2 0.01' Set 1 centimetre of standard deviation to measurement 2 in filter\n");
	printf("                            Defaults: PPP:         Pseudorange->1m  Carrierphase->0.01m\n");
	printf("                                      SPP:         Pseudorange->5m  Carrierphase->0.10m\n");
	printf("    -filter:fixedweightsat g#[-#] <n> <a>   Apply the specified standard deviation to a specific satellite of the measurement 'n'.\n");
	printf("                            g     Character determining GNSS system (G->GPS)\n");
	printf("                            #     PRN number. If #=0, it will be applied to all satellites of the selected GNSS system\n");
	printf("                            [-#]  Optionally, a minus sign ('-') and a second PRN number can be provided in order to set a range\n"); 
    printf("                                    of satellites (of the same constellation)\n");
	printf("                            <n>   Measurement number in the filter. If <n> is 0, it will be applied to all measurements in the filter.\n");
	printf("                            <a>   = URA  Use the URA value from the broadcast message (not valid in PPP)\n");
	printf("                                  = #    Value for the standard deviation (in metres).\n");
	printf("                            The filter shall apply as weight = 1/(<a>^2)\n");
	printf("                            NOTE: When this option is provided, it will override any other sigmas provided by '-filter:fixedweight' or\n");
	printf("                              '-filter:elevweight' or the sigmas provided by SBAS or DGNSS\n");
	printf("    -filter:elevweight <n> <a> <b> <c>    Apply the specified values to compute the standard deviation of the measurement 'n'\n");
	printf("                            std = a + b * e^(-elevation/c)\n");
	printf("                            <n>    Measurement number. If <n> is 0, it will be applied to all measurements in the filter.\n");
	printf("                            <a>    = URA  Use the URA value from the broadcast message (not valid in PPP)\n");
	printf("                                   = #    Value for minimum standard deviation of the measurement [weight at elevation 90 degrees] (metres)\n");
	printf("                            <b>    Multiplier to e [standard deviation at elevation 0 degrees] (metres)\n");
	printf("                            <c>    Elevation constant (degrees)\n");
	printf("                            The filter shall apply as weight = 1/(std^2)\n");
	printf("                            Sample (default values): '-filter:elevweight 1 0.13 0.53 10' Apply the standard deviation: 0.13+0.53*e^(-elevation/10)\n");
	printf("                            Note: '-filter:elevweight 1 x 0 y' equals to '-filter:fixedweight 1 x'\n");
	printf("    -filter:elevweightsat g#[-#] <n> <a> <b> <c>  Apply the specified values to a specific satellite to compute the standard deviation of measurement 'n'\n");
	printf("                            std = a + b * e^(-elevation/c)\n");
	printf("                            g      Character determining GNSS system (G->GPS)\n");
	printf("                            #      PRN number. If #=0, it will be applied to all satellites of the selected GNSS system\n");
	printf("                            [-#]   Optionally, a minus sign ('-') and a second PRN number can be provided in order to set a range\n"); 
    printf("                                     of satellites (of the same constellation)\n");
	printf("                            <n>    Measurement number. If <n> is 0, it will be applied to all measurements in the filter.\n");
	printf("                            <a>    = URA  Use the URA value from the broadcast message (not valid in PPP)\n");
	printf("                                   = #    Value for minimum standard deviation of the measurement [weight at elevation 90 degrees] (metres)\n");
	printf("                            <b>    Multiplier to e [standard deviation at elevation 0 degrees] (metres)\n");
	printf("                            <c>    Elevation constant (degrees)\n");
	printf("                            The filter shall apply as weight = 1/(std^2)\n");
	printf("                            Sample (default values): '-filter:elevweightsat G01 1 0.13 0.53 10' Apply the standard deviation: 0.13+0.53*e^(-elevation/10)\n");
	printf("                            Note: '-filter:elevweightsat g# 1 x 0 y' equals to '-filter:fixedweightsat g# 1 x'\n");
	printf("    -filter:sinelevweight <n> <a> <b>  Apply the specified values to compute the variance of the measurement 'n'\n");
	printf("                            std^2 = a + b/((sin(elevation))^2)\n");
	printf("                            <n>    Measurement number. If <n> is 0, it will be applied to all measurements in the filter.\n");
	printf("                            <a>    = URA  Use the URA value from the broadcast message (not valid in PPP)\n");
	printf("                                   = #    Value for minimum variance of the measurement (m^2)\n");
	printf("                            <b>    Multiplier to fraction (m^2)\n");
	printf("                            The filter shall apply as weight = 1/(std^2)\n");
	printf("                            Sample (default values): '-filter:sinelevweight 1 0 1' Apply the variance: 0+1/((sin(elevation))^2)\n");
	printf("    -filter:sinelevweightsat g#[-#] <n> <a> <b>  Apply the specified values to a specific satellite to compute the variance of the measurement 'n'\n");
	printf("                            std^2 = a + b/((sin(elevation))^2)\n");
	printf("                            g      Character determining GNSS system (G->GPS)\n");
	printf("                            #      PRN number. If #=0, it will be applied to all satellites of the selected GNSS system\n");
	printf("                            [-#]   Optionally, a minus sign ('-') and a second PRN number can be provided in order to set a range\n"); 
    printf("                                     of satellites (of the same constellation)\n");
	printf("                            <n>    Measurement number. If <n> is 0, it will be applied to all measurements in the filter.\n");
	printf("                            <a>    = URA  Use the URA value from the broadcast message (not valid in PPP)\n");
	printf("                                   = #    Value for minimum variance of the measurement (m^2)\n");
	printf("                            <b>    Multiplier to fraction (m^2)\n");
	printf("                            The filter shall apply as weight = 1/(std^2)\n");
	printf("                            Sample (default values): '-filter:sinelevweight 1 0 1' Apply the variance: 0+1/((sin(elevation))^2)\n");
	printf("    -filter:snrweight <n> <a> <b>   Apply the specified values to compute the variance of the measurement 'n'\n");
	printf("                            std^2 = a + b * 10^(-SNR/10)\n");
	printf("                            <n>    Measurement number. If <n> is 0, it will be applied to all measurements in the filter.\n");
	printf("                            <a>    = URA  Use the URA value from the broadcast message (not valid in PPP)\n");
	printf("                                   = #    Value for minimum variance of the measurement [weight at max SNR] (m^2)\n");
	printf("                            <b>    Multiplier to exponential [variance at SNR 0 dBHz] (m^2*Hz)\n");
	printf("                            The filter shall apply as weight = 1/(std^2)\n");
	printf("                            Sample (default L1): '-filter:snrweight 1 0 0.244'   Apply the variance: 0+0.244*10^(-SNR/10)\n");
	printf("                            Sample (default L2): '-filter:snrweight 1 0.88E-6 0.77E-3'   Apply the variance: 0.88E-6+0.77E-3*10^(-SNR/10)\n");
	printf("    -filter:snrweightsat g#[-#] <n> <a> <b>  Apply the specified values to a specific satellite to compute the variance of the measurement 'n'\n");
	printf("                            std^2 = a + b * 10^(-SNR/10)\n");
	printf("                            g      Character determining GNSS system (G->GPS)\n");
	printf("                            #      PRN number. If #=0, it will be applied to all satellites of the selected GNSS system\n");
	printf("                            [-#]   Optionally, a minus sign ('-') and a second PRN number can be provided in order to set a range\n"); 
    printf("                                      of satellites (of the same constellation)\n");
	printf("                            <n>    Measurement number. If <n> is 0, it will be applied to all measurements in the filter.\n");
	printf("                            <a>    = URA  Use the URA value from the broadcast message (not valid in PPP)\n");
	printf("                                   = #    Value for minimum variance of the measurement [weight at max SNR] (m^2)\n");
	printf("                            <b>    Multiplier to exponential [variance at SNR 0 dBHz] (m^2*Hz)\n");
	printf("                            The filter shall apply as weight = 1/(std^2)\n");
	printf("                            Sample (default L1): '-filter:snrweightsat G01 1 0 0.244'   Apply the variance: 0+0.244*10^(-SNR/10)\n");
	printf("                            Sample (default L2): '-filter:snrweightsat G01 1 0.88E-6 0.77E-3'  Apply the variance: 0.88E-6+0.77E-3*10^(-SNR/10)\n");
	printf("    -filter:snrelevweight <n>  <a> <b> Apply the specified values to compute the variance of the measurement 'n'\n");
	printf("                            std^2 = a + b * 10^(-SNR/10)/((sin(elevation)^2)\n");
	printf("                            <n>    Measurement number. If <n> is 0, it will be applied to all measurements in the filter.\n");
	printf("                            <a>    = URA  Use the URA value from the broadcast message (not valid in PPP)\n");
	printf("                                   = #    Value for minimum variance of the measurement [weight at max SNR] (m^2)\n");
	printf("                            <b>    Multiplier to exponential [variance at SNR 0 dBHz] (m^2*Hz)\n");
	printf("                            The filter shall apply as weight = 1/(std^2)\n");
	printf("                            Sample: '-filter:snrelevweight 1 0 1'   Apply the variance: 0 + 1*10^(-SNR/10)/((sin(elevation))^2)\n");
	printf("    -filter:snrelevweightsat g#[-#] <n> <a> <b> Apply the specified values to a specific satellite to compute the variance of the measurement 'n'\n");
	printf("                            std^2 = a + b * 10^(-SNR/10)/((sin(elevation)^2)\n");
	printf("                            g      Character determining GNSS system (G->GPS)\n");
	printf("                            #      PRN number. If #=0, it will be applied to all satellites of the selected GNSS system\n");
	printf("                            [-#]   Optionally, a minus sign ('-') and a second PRN number can be provided in order to set a range\n"); 
    printf("                                     of satellites (of the same constellation)\n");
	printf("                            <n>    Measurement number. If <n> is 0, it will be applied to all measurements in the filter.\n");
	printf("                            <a>    = URA  Use the URA value from the broadcast message (not valid in PPP)\n");
	printf("                                   = #    Value for minimum variance of the measurement [weight at max SNR] (m^2)\n");
	printf("                            <b>    Multiplier to exponential [variance at SNR 0 dBHz] (m^2*Hz)\n");
	printf("                            The filter shall apply as weight = 1/(std^2)\n");
	printf("                            Sample: '-filter:snrelevweightsat g# 1 0 1'   Apply the variance: 0 + 1*10^(-SNR/10)/((sin(elevation))^2)\n");
	printf("    -filter:snrweight:comb <n> <val> When the weight is computed using any method involving the SNR (options '-filter:snrweight' or '-filter:snrelevweight),\n");
	printf("                                   when computing the weight for combinations, select how to get the SNR value:\n");
	printf("                               <n>   Measurement number. If <n> is 0, it will be applied to all measurements (which are combinations) in the filter.\n");
    printf("                               <val> = SNRi    For a combination with frequencies ij, use SNR from measurement of frequency i\n");
    printf("                               <val> = SNRj    For a combination with frequencies ij, use SNR from measurement of frequency j\n");
    printf("                               <val> = MaxSNR  Use the highest SNR of the two measurements used in the combination\n");
    printf("                               <val> = MinSNR  Use the lowest SNR of the two measurements used in the combination\n");
    printf("                               <val> = MeanSNR Use the mean SNR value of the two measurements used in the combination [default]\n");
    printf("                               0 <= <val> <= 1 If <val> is a number between [0,1], combine the SNR with the following formula:\n");
	printf("                                                 SNR = SNRi*<val> + SNRj*(1-<val>)\n");
	printf("                NOTE: For a combination with frequencies 'i' and 'j', 'i' is always the smallest frequency number and 'j' the highest,\n");
	printf("                        except for frequency '0', which will be always the highest (it it treated as frequency number '10').\n");
	printf("                        For example, for combination PC12, i=1 and j=2. For combination LC10, i=1,j=0\n");
	printf("    -filter:snrweight:combsat g#[-#] <n> <val> When the weight is computed using any method involving the SNR (options '-filter:snrweight' or '-filter:snrelevweight),\n");
	printf("                                   when computing the weight for combinations for a specific satellite , select how to get the SNR value:\n");
	printf("                               g     Character determining GNSS system (G->GPS)\n");
	printf("                               #     PRN number. If #=0, it will be applied to all satellites of the selected GNSS system\n");
	printf("                               [-#]  Optionally, a minus sign ('-') and a second PRN number can be provided in order to set a range\n"); 
    printf("                                       of satellites (of the same constellation)\n");
	printf("                               <n>   Measurement number. If <n> is 0, it will be applied to all measurements (which are combinations) in the filter.\n");
    printf("                               <val> = SNRi    For a combination with frequencies ij, use SNR from measurement of frequency i\n");
    printf("                               <val> = SNRj    For a combination with frequencies ij, use SNR from measurement of frequency j\n");
    printf("                               <val> = MaxSNR  Use the highest SNR of the two measurements used in the combination\n");
    printf("                               <val> = MinSNR  Use the lowest SNR of the two measurements used in the combination\n");
    printf("                               <val> = MeanSNR Use the mean SNR value of the two measurements used in the combination [default]\n");
    printf("                               0 <= <val> <= 1 If <val> is a number between (0,1), combine the SNR with the following formula:\n");
	printf("                                                 SNR = SNRi*<val> + SNRj*(1-<val>)\n");
	printf("                NOTE: For a combination with frequencies 'i' and 'j', 'i' is always the smallest frequency number and 'j' the highest,\n");
	printf("                        except for frequency '0', which will be always the highest (it it treated as frequency number '10').\n");
	printf("                        For example, for combination PC12, i=1 and j=2. For combination LC10, i=1,j=0\n");
	printf("    -filter:sbasdgnssweightmode <n> <val> In SBAS and DGNSS modes, select how the provided sigma is combined with the user selected weight\n");
	printf("                                           computation mode (with options '-filter:fixedweight', '-filter:elevweight', '-filter:sinelevweight',\n");
	printf("                                           '-filter:snrweight' and '-filter:snrelevweight')\n");
	printf("                              <n>    Measurement number. If <n> is 0, it will be applied to all measurements in the filter.\n");
	printf("                              <val>  = ComputedOnly     Use only the variance computed with SBAS or DGNSS corrections [default if user does not select a weight method]\n"); 
	printf("                              <val>  = ComputedPlusUser Use the variance computed with SBAS or DGNSS corrections plus the sigma computed with the user selected weight method\n"); 
	printf("                              <val>  = UserOnly         Use only the variance computed with the user selected weight method [default if user selects a weight method]\n"); 
	printf("    -filter:sbasdgnssweightmodesat g#[-#] <n> <val> In SBAS and DGNSS modes, select how the provided sigma is combined with the user selected weight\n");
    printf("                                                computation mode (with options '-filter:fixedweight', '-filter:elevweight', '-filter:sinelevweight',\n");
	printf("                                                '-filter:snrweight' and '-filter:snrelevweight') to a specific satellite and measurement\n");
	printf("                              g      Character determining GNSS system (G->GPS)\n");
	printf("                              #      PRN number. If #=0, it will be applied to all satellites of the selected GNSS system\n");
	printf("                              [-#]   Optionally, a minus sign ('-') and a second PRN number can be provided in order to set a range\n"); 
    printf("                                       of satellites (of the same constellation)\n");
	printf("                              <n>    Measurement number. If <n> is 0, it will be applied to all measurements in the filter.\n");
	printf("                              <val>  = ComputedOnly     Use only the variance computed with SBAS or DGNSS corrections [default if user does not select a weight method]\n"); 
	printf("                              <val>  = ComputedPlusUser Use the variance computed with SBAS or DGNSS corrections plus the sigma computed with the user selected weight method\n"); 
	printf("                              <val>  = UserOnly         Use only the variance computed with the user selected weight method [default if user selects a weight method]\n"); 
	printf("    -filter:sigmaiono       Use standard deviation data from IONEX or FPPP or SBAS if these iono models are used [default on] ('--filter:sigmaiono' to disable it)\n");
	printf("                             The IONEX or F-PPP sigma will be added to the computed satellite standard deviation\n");
	printf("    -filter:phi:dr <val>    Specify the Phi value for position unknowns [defaults static:1 kinematic:0]\n");
	printf("    -filter:phi:clk <val>   Specify the Phi value for clock unknown [default 0]\n");
	printf("    -filter:phi:trop <val>  Specify the Phi value for troposphere unknown [default 1]\n");
	printf("    -filter:phi:amb <val>   Specify the Phi value for ambiguity unknowns [default 1]\n");
	printf("    -filter:q:dr <val>      Specify the Q noise value for position unknowns [defaults static:0 kinematic:1e8] (m^2)\n");
	printf("    -filter:q:clk <val>     Specify the Q noise value for clock unknown [default 9e10] (m^2)\n");
	printf("    -filter:q:trop <val>    Specify the Q noise variation value for troposphere unknown [default 1e-4] (m^2/h)\n");
	printf("    -filter:q:amb <val>     Specify the Q noise value for ambiguity unknowns [default 0] (m^2)\n");
	printf("    -filter:p0:dr <val>     Specify the P0 initial value for position unknowns [default 1e8] (m^2)\n");
	printf("    -filter:p0:clk <val>    Specify the P0 initial value for clock unknown [default 9e10] (m^2)\n");
	printf("    -filter:p0:trop <val>   Specify the P0 initial value for troposphere unknown [default 0.5^2] (m^2)\n");
	printf("    -filter:p0:amb <val>    Specify the P0 initial value for ambiguity unknowns (for prealigned carrier phases) [default 20^2] (m^2)\n");
	printf("    -filter:backward        Specify that the filter does a backward processing after the forward one is finished. This meas that it\n");
	printf("                            process the data backwards. The \"turn point\" is defined as the latest point where orbits and clocks\n");
	printf("                            are available or when the observation RINEX ends (whatever is first) ('--filter:backward' to disable it)\n");
	printf("                            [default disabled]\n");
	printf("    -filter:maxgdop <val>   Set the GDOP threshold which will make gLAB do the following when the threshold is exceeded:\n");
	printf("                              In SPP:   Skip the epoch [default disabled]\n");
	printf("                              In PPP:   Skip the epoch [default 30.0]\n");
	printf("                              In SBAS:	It will try to switch mode or GEO (if allowed), otherwise it will skip the epoch [default disabled]\n");
	printf("                              In DGNSS: Switch from DGNSS to SPP [default 30.0]\n");
	printf("                              Use '--filter:maxgdop' to disable it\n");
	printf("    -filter:stfdesa         Compute values for Stanford-ESA plot (only for SPP, SBAS and DGNSS) [default disabled]\n");
	printf("                              The output data is written in a separate file (which has to be processed with graph.py). See parameter '-output:stfdesa'\n");
	printf("    -filter:stfdesaloi      If Stanford-ESA computation is enabled, write to file all geometries which produce an integrity ratio equal or higher\n");
	printf("                              than the horizontal or vertical thresholds (any of them). See parameter '-output:stfdesaloi' [default enabled]\n");
	printf("    -filter:stfdesa:xmax <val>  Set the maximum value for the horizontal axis (error axis, in metres) for Stanford-ESA plot [default 50]\n");
	printf("    -filter:stfdesa:ymax <val>  Set the maximum value for the vertical axis (protection level axis, in metres) for Stanford-ESA plot [default 50]\n");
	printf("    -filter:stfdesa:xres <val>  Set the horizontal resolution (error axis,in metres) for Stanford-ESA plot [default 0.1]\n");
	printf("    -filter:stfdesa:yres <val>  Set the vertical resolution (protection level axis, in metres) for Stanford-ESA plot [default 0.1]\n");
	printf("    -filter:stfdesa:hwir <val>  Set the horizontal integrity ratio threshold for which the geometry info will be written to file [default 0.7]\n");
	printf("                                  See parameters '-filter:stfdesaloi' and '-output:stfdesaloi' for more details.\n");  
	printf("    -filter:stfdesa:vwir <val>  Set the vertical integrity ratio threshold for which the geometry info will be written to file [default 0.7]\n");
	printf("                                  See parameters '-filter:stfdesaloi' and '-output:stfdesaloi' for more details.\n");  
	printf("\n  OUTPUT OPTIONS\n");
	printf("    -output:file <file>     Sets the output file [default stdout]\n");
	printf("    --output:file           Sets the output to stdout [default]\n");
	printf("    -output:kml  <file>     Generate a KML file to be opened with Google Earth [default off]\n");
	printf("    -output:kml0 <file>     Generate a KML file with all height set to 0 (ground projection) to be opened with Google Earth [default off]\n");
	printf("    -output:kml:refsta      Add reference stations in KML file (in DGNSS mode only). Use '--output:kml:refsta' to disable it. [default on]\n");
	printf("    -output:kml:tstamp      Add time stamp in KML file [default off]\n");
    printf("    -output:kml:tstampdec   Decimation (in seconds) for time stamps in KML files [default 30]\n");
    printf("    -output:kml:tstamprange <val1> <val2>  Set a time range for time stamps. Only during this time range KML timestamps will be written [default off]\n");
	printf("                              <val1>  Start epoch (in seconds of day). If \"-\" is given, it will be intepreted as the beginning of the file.\n");
	printf("                              <val2>  Start epoch (in seconds of day). If \"-\" is given, it will be intepreted as the end of the file.\n");
	printf("                                 If the observation file spans for more than one day, add an offset of 86400 seconds to the start or end epoch.\n");
	printf("                                 To set multiple ranges, set this parameter as many times as the number of ranges needed (one for each range).\n");
	printf("                                 This parameter is combinable with '-output:kml:tstampdec' option\n");
	printf("    -output:sp3  <file>     Generate a SP3 file with the computed coordinates [default off]\n");
	printf("    -output:sp3:letter <val> Constellation letter to be written in the SP3 [default 'L']\n");
	printf("    -output:sp3:prn  <val>  PRN number to be written in the SP3 [default '9']\n");
	printf("    -output:sp3:dgnssonly    In DGNSS mode, do not write SPP solutions in the output SP3 file [default on]\n");
	printf("    --output:sp3:dgnssonly   In DGNSS mode, write SPP solutions in the output SP3 file [default off]\n");
	printf("    -output:refpos  <file>  Generate a columnar text file with the computed coordinates [default off]\n");
	printf("    -output:refpos:doy      Write timestamp as 'Year DoY SoD' in the output reference position text file [default on]\n");
	printf("    -output:refpos:gpsweek  Write timestamp as 'GPSWeek SoW' in the output reference position text file [default off]\n");
	printf("    -output:refpos:caltime  Write timestamp as 'Year/Month/Day HH:MM:SS.zzz' in the output reference position text file [default off]\n");
	printf("    -output:refpos:geodetic Write solution in WGS84 geodetic coordinates (Lon, Lat, Height), instead of WGS84 cartesian coordinates (X, Y, Z) [default off]\n");
	printf("    -output:refpos:dgnssonly  In DGNSS mode, do not write SPP solutions in the output reference position text file [default on]\n");
	printf("    --output:refpos:dgnssonly In DGNSS mode, write SPP solutions in the output reference position text file [default off]\n");
	printf("    -output:rinex <file>    Sets the RINEX observation output file name. In conversion mode, if this option is not specified, the default output filename\n");
	printf("                              will be <ssssddd0.YYo>, where 'ssss' are the first 4 characters of the filename, 'ddd' is the day of year with three digits\n");
	printf("                              and 'YY' is the last two digits of the year (from the RTCM file)\n");
	printf("                              In Add user error to RINEX mode, if this option is not specified, the default output filename will be <obsfilename>_usererror>\n");
	printf("    -output:rinexversion <val>      <val> = 2  Generates a RINEX v2.11 from the binary file RTCM v3.x\n");
	printf("                                    <val> = 3  Generates a RINEX v3.00 from the binary file RTCM v3.x [default]\n");
	printf("    -output:corrections <file>    Sets the ASCII Plain Text output file name for the corrections\n");
	printf("    -output:antenna <file>        Sets the ASCII Plain Text output file name for the antenna information\n");
	printf("    -output:satvel <val>    <val> = inertial  Prints the inertial velocity in the messages where satellite velocity is given\n");
	printf("                            <val> = ITRF (ECEF)  Prints the ECEF velocity in the messages where satellite velocity is given [default]\n");
	printf("    -output:rinexb          Generate a RINEX-B file from the SBAS data (only for SBAS) [default off]\n");
	printf("    -output:ems             Generate a EMS file from the SBAS data (only for SBAS) [default off]\n");
	printf("    -output:pegasus         Generate Pegasus file format from the SBAS data (only for SBAS). See notes on Pegasus format below. [default off]\n");
	printf("    -output:pegstrictrinex  When generating a RINEX-H file for Pegasus, follow the RINEX 2.11 rules for transmission time,\n");
	printf("                            health flag and URA (only active if -output:pegasus has been set) [default off]\n");
	printf("    -output:pegspace        Set the field separator in Pegasus files to space character (' ') instead of a semicolon (';') [default off]\n");
	printf("    -output:pegfilealign    Print Pegasus files with all columns aligned [default off]\n");
	printf("    -output:sbasdir <name>  Set the directory where to write the output SBAS files ('.' for current directory) [default \"SBAS\"]\n");
	printf("    -output:stfdesa <file>  Set the filename where to write the output data for Stanford-ESA plots [default \"observationfilename_stdESA.txt\"]\n");
	printf("                            The output file is a columnar text file to be processed with graph program (with '--sf' parameter) for generating the Stanford-ESA plots\n");
	printf("                            The first line of the output file contains, in this order the resolution in X axis (error), resolution in Y axis (protection level),\n");
	printf("                              maximum value in X axis and maximum value in Y axis. All the values are in metres.\n");
	printf("                            From the second line until then end, each line contains, in this order, the X coordinate, Y coordinate (both in metres), the number of\n");
	printf("                              points in the horizontal component in that coordinate and the number of points in the vertical component in that coordinate.\n");
	printf("                            See an example of the generated figures with graph program in the SBAS manual (file gLAB_SBAS_SUM.pdf)\n");
	printf("                            Setting this option enables Stanford-ESA computation.\n");
	printf("    -output:stfdesaloi <file> Set the filename where to write the geometries of Stanford-ESA whose integrity ratio are over the horizontal or vertical\n");
	printf("                                integrity ratio (any of them). [default \"observationfilename_stdESA_LOI.txt\"]\n");
	printf("                                This option sets enables the following parameter automatically: '-filter:stfdesaloi'.\n");
	printf("    -onlyconvert            Convert EMS or RINEX-B file to RINEX-B, EMS or Pegasus and exit without processing any GNSS data [default off]\n");
	printf("    Incorrect messages from RINEX-B or EMS files are messages which grant any of these conditions:\n");
	printf("      CRC mismatch, invalid header, unknown message type, invalid time of applicability (time is over 86400 seconds)\n");
	printf("    In case of not setting '-output:rinex', '-output:corrections' and/or '-output:antenna' gLAB will set automatically a name for the output file[s].\n");
	printf("      These previous options are effective only if an RTCM file is converted. Therefore, there will be no RTCM converted files if the input RTCM file is processed\n");
	printf("    NOTE: A KML with a 1 second rate data and 1 second timestamp rate may be too big for Google Earth\n");
	printf("\n  VERBOSE OPTIONS   (use -print:... to activate, --print:... to deactivate)\n");
	printf("    -print:info             Print INFO messages [default on]\n");
	printf("    -print:cycleslips       Print CS messages [default on]\n");
	printf("    -print:cs               Equivalent to parameter '-print:cycleslips'\n");
	printf("    -print:input            Print INPUT messages [default on for non SBAS processing, off for SBAS processing]\n");
	printf("    -print:meas             Print MEAS messages [default off]\n");
	printf("    -print:model            Print MODEL messages [default on for non SBAS processing, off for SBAS processing]\n");
	printf("    -print:satellites       Print EPOCHSAT messages [default on for non SBAS processing, off for SBAS processing]\n");
	printf("    -print:epochsat         Equivalent to parameter '-print:satellites'\n");
	printf("    -print:sat              Equivalent to parameter '-print:satellites'\n");
	printf("    -print:prefit           Print PREFIT messages [default on for non SBAS processing, off for SBAS processing]\n");
	printf("    -print:postfit          Print POSTFIT messages [default on for non SBAS processing, off for SBAS processing]\n");
	printf("    -print:filter           Print FILTER messages [default on for non SBAS processing, off for SBAS processing]\n");
	printf("    -print:output           Print OUTPUT messages [default on]\n");
	printf("    -print:satdiff          Print SATDIFF messages in comparison mode (see below) [default on]\n");
	printf("    -print:satstat          Print SATSTAT messages in comparison mode (see below) [default on]\n");
	printf("    -print:satstattot       Print SATSTATTOT messages in comparison mode (see below) [default on]\n");
	printf("    -print:satpvt           Print SATPVT messages in show product mode (see below) [default on]\n");
	printf("    -print:satsel           Print satellite selection information [default off for non SBAS processing, on for SBAS processing]\n");
	printf("    -print:sbascor          Print SBASCORR messages (only for SBAS) [default off]\n");
	printf("    -print:sbascorr         Equivalent to parameter '-print:sbascor'\n");
	printf("    -print:sbasvar          Print SBASVAR messages (only for SBAS) [default off]\n");
	printf("    -print:sbasiono         Print SBASIONO messages (only for SBAS) [default off]\n");
	printf("    -print:sbasout          Print SBASOUT messages (only for SBAS) [default on]\n");
	printf("    -print:sbasunsel        Print SBASUNSEL messages (only for SBAS) [default off]\n");
	printf("    -print:sbasunused       Print messages from discarded satellites due to SBAS GEO switch (only for SBAS) [default off]\n");
	printf("                                  The discarded messages are MODEL, SBASCORR, SBASVAR, SBASIONO and SBASUNSEL, but only the ones\n");
	printf("                                  selected from user parameters will be printed. Also, an asterisk '*' will be added at the end\n");
	printf("                                  of the first field to indicate that it is a discarded measurement\n");
	printf("    -print:usererror        Print user added error to raw measurements [default on]\n");
	printf("    -print:dgnss            Print DGNSS global information (only for DGNSS) [default on]\n");
	printf("    -print:dgnssunused      Print messages from discarded satellites due to GDOP switch (from DGNSS to SPP) [default off]\n");
	printf("                                  An asterisk '*' will be added at the end of the first field to indicate that it is a discarded measurement\n");
	printf("    -print:summary          Print a summary at the end of the files with the statistics of the processing [default on]\n");
	printf("    -print:progress         Print to terminal the current epoch being processed [default on]\n");
	printf("    -print:all              Print all messages\n");
	printf("    -print:none             Do not print anything ('--print:none' is also accepted)\n");
	printf("                            More information on print messages can be seen with the '-messages' option\n");
	printf("\n  SUMMARY OPTIONS\n");
	printf("      When processing in SPP/PPP/SBAS/DGNSS corrections, if summary enabled a statistical summary will be\n");
	printf("        printed at the end of the output file. If receiver position is not fixed, error percentiles messages will not be shown\n");
	printf("        The options for generating this summary are:\n");
	printf("    -summary:percentile <val>  Sets the value for computing the error percentile [default 95]\n"); 
	printf("    -summary:waitfordaystart   If the observation file starts at %d hours or later, gLAB will assume that from the first epoch\n",HOURSPREVDAYCONVERGENCE);
	printf("                                     until epoch 23 hours 59 minutes 59 seconds are given just to fill the messages buffer and wait for\n");
	printf("                                     the smoothing and filter to converge, and the following epochs from the next day are the ones of interest.\n");
	printf("                                     During this convergence period, Stanford-ESA values will not be computed and they will not be taken into\n");
	printf("                                     account for the summary. This option is useful to avoid high error epoch in the summary\n");
	printf("                                     during the convergence time. [default on]\n");
	printf("                                    This option can be disabled with '--summary:waitfordaystart'\n");
	printf("                                    If option will have no effect is '-summary:starttime' is set\n");
	printf("    -summary:starttime <date>  Set the first epoch to be used in the summary. See parameter '-pre:starttime' for details on date format\n");
	printf("      NOTE: The last line of the summary contains all the values of the previous lines along with the station coordinates.\n");
	printf("            	This line is useful for plotting world maps with data from each station.\n");
	printf("      NOTE: An example of a summary can be seen executing gLAB with '-messages' parameter\n");
	printf("   ADDITIONAL SUMMARY OPTIONS FOR SBAS\n");
	printf("      In SBAS mode, there are additional options for the summary:\n");
	printf("    -summary:hal        <val>  Sets the Horizontal Alarm Limit (in metres) for computing availability and continuity risk [default 40]\n");
	printf("    -summary:val        <val>  Sets the Vertical Alarm Limit (in metres) for computing availability and continuity risk [default 50]\n");
	printf("    -summary:windowsize <val>  Sets the sliding window size (in epochs) for computing the continuity risk [default 15]\n");
	printf("      NOTE: The computation of the continuity risk takes into account the sampling rate and data gaps in the observation file.\n");
	printf("\n  SBAS PLOTS OPTIONS\n");
	printf("      This mode is activated when only a navigation file and a SBAS file are given (see description below in WORK MODES).\n"); 
	printf("      The following options are specific for this mode:\n");
	printf("    -sbasplots:minlat    <val> Sets the minimum latitude (in degrees) for the SBAS plots. The minimum resolution is 0.01 [default 25.0]\n");
	printf("    -sbasplots:maxlat    <val> Sets the maximum latitude (in degrees) for the SBAS plots. The minimum resolution is 0.01 [default 70.0]\n");
	printf("    -sbasplots:minlon    <val> Sets the minimum longitude (in degrees) for the SBAS plots. The minimum resolution is 0.01 [default -30.0]\n");
	printf("    -sbasplots:maxlon    <val> Sets the maximum longitude (in degrees) for the SBAS plots. The minimum resolution is 0.01 [default 40.0]\n");
	printf("    -sbasplots:plotarea  <minlon> <maxlon> <minlat> <maxlat>\n");
	printf("                               This parameter is a shorter way to provide the same values as in '-sbasplots:minlon' '-sbasplots:maxlon', '-sbasplots:minlat'\n"); 
	printf("                                 and '-sbasplots:maxlat' parameters.\n");
	printf("    -sbasplots:recheight <val> Sets the receiver height (in metres) [default 0 (at sea level)]\n");
	printf("    -sbasplots:hal       <val> Sets the Horizontal Alarm Limit (in metres) for computing the Availability plots [default 40]\n");    
	printf("    -sbasplots:val       <val> Sets the Vertical Alarm Limit (in metres) for computing the Availability plots [default 50]\n");    
	printf("    -sbasplots:availstep <val> Sets the resolution (in degrees) for both longitude and latitude for Availability\n");
	printf("                                 and Continuity Risk maps. The minimum resolution is 0.01 [default 1.0]\n");
	printf("    -sbasplots:ionostep  <val> Sets the resolution (in degrees) for both longitude and latitude for Ionosphere\n");
	printf("                                 Corrections Availability map. The minimum resolution is 0.01 [default 0.3]\n");
	printf("    -sbasplots:ionotimestep <val>  Sets the time step (in seconds) for ionosphere availability plot [default 300]\n");
	printf("    -sbasplots:windowsize   <val>  Sets the sliding window size (in seconds) for computing the continuity risk [default 15]\n");
	printf("    -output:sbasavailplots  <file> Sets the output file for the SBAS Availability plots data. The output file is a\n");
	printf("                                 columnar text file to be processed by graph program (with '--sbas' parameter) [default \"SBASAvailPlots_sbasfilename.txt\"]\n");
	printf("    -output:sbasriskplots   <file> Sets the output file for the SBAS Continuity Risk plot data. The output file is a\n");
	printf("                                 columnar text file to be processed by graph program (with '--sbas' parameter) [default \"SBASRiskPlots_sbasfilename.txt\"]\n");
	printf("    -output:sbasionoplots   <file> Sets the output file for the SBAS Ionosphere availability plot data. The output file is a\n");
	printf("                                 columnar text file to be processed by graph program (with '--sbas' parameter) [default \"SBASIonoPlots_sbasfilename.txt\"]\n"); 
	printf("    -output:sbasriskdisc    <file> Sets the output file for the list of SBAS solution discontinuities found during the computation of SBAS Continuity Risk plot.\n");
	printf("                                 The output file is a columnar text file [default \"SBASRiskDisc_sbasfilename.txt\"]\n"); 
	printf("    -sbasplots:hourlymaps      Print the hourly availability maps. The files will have the same name as the daily maps, but with '_HHh' added\n");
	printf("                                 before the file extension (being HH the hour with two digits)\n");
	printf("    -sbasplots:noavailplot     Do not compute the SBAS Availability and Continuity Risk plots [default off]\n");
	printf("    -sbasplots:noriskplot      Do not compute the SBAS Continuity Risk plot [default off]\n");
	printf("    -sbasplots:noionoplot      Do not compute the SBAS Ionosphere corrections availability plot [default off]\n");
	printf("    -sbasplots:noionomodel     Do not use SBAS ionosphere during the computation of Availability and Continuity Risk plot [default off]\n");
	printf("                                 This parameter is equivalent to '-model:iono no'\n");
	printf("    -sbasplots:exclusionarea <minlon> <maxlon> <minlat> <maxlat>\n");
	printf("                               Set a square area where SBAS availability and SBAS iono availability will be set to 0 (the area is skipped during computation)\n"); 
	printf("                                 This is useful when processing large areas (e.g. areas with multiple SBAS and want to exclude the sea between them)\n");
	printf("                                 The user can set any number of exclusion area by providing this parameter as many times as necessary\n");
	printf("                                 The area must be given with these four values (in this order): minimum longitude, maximum longitude,\n");
	printf("                                 minimum latitude, maximum latitude. The four values must be in degrees, with the longitude between -180\n");
	printf("                                 and 180 degrees, and the latitude between -90 and 90 degrees\n");
	printf("    -sbasplots:inclusionarea <minlon> <maxlon> <minlat> <maxlat>\n");
	printf("                               Set a square area where SBAS availability and SBAS iono availability will be computed (the rest is skipped). This area must be\n"); 
	printf("                                 inside the region defined by parameters '-sbasplots:minlon', '-sbasplots:maxlon', '-sbasplots:minlat' and '-sbasplots:maxlat'.\n");
	printf("                                 The user can set any number of inclusion area by providing this parameter as many times as necessary\n");
	printf("                                 The area must be given with these four values (in this order): minimum longitude, maximum longitude,\n");
	printf("                                 minimum latitude, maximum latitude. The four values must be in degrees, with the longitude between -180\n");
	printf("                                 and 180 degrees, and the latitude between -90 and 90 degrees\n\n");
	printf("   If both inclusion and exclusion areas are provided, then an area which is processed must be inside of any inclusion area and outside of any exclusion area.\n");
	printf("   The default region defined in gLAB corresponds to EGNOS coverage area.\n");
	printf("   The available output messages in this mode are INFO [default on], SBASIONO [default off] and SBASUNSEL [default off]\n");
	printf("   Most of the options applied for normal SBAS processing can also be applied for this mode, except for those which apply to measurement corrections (due to\n");
	printf("     there are none in this mode) and the option to use Klobuchar while solution converges ('-model:initcoordNPA') as we consider we are always in strict PA mode.\n");
	printf("   An example of the generated figures with graph program is in the SBAS manual (file gLAB_SBAS_SUM.pdf)\n");
	printf("\n  DATE CONVERSION OPTIONS\n");
	printf("      This mode is for converting a date format to all other GNSS date formats and exit.\n");
	printf("      The accepted date formats are: YYYY/MM/DD HH:MM:SS.zzz ('zzz' are milliseconds), Year/DoY/SoD, GPSWeek/SoW, MJDN/SoD (MJDN is Modified Julian Day Number)\n");
	printf("      Minimum accepted date is 1980/01/06 (YYYY/MM/DD) or 1980/006 (Year/DoY) or 0/0 (GPSWeek/SoW) or 44244/0 (MJDN/SoD)\n");
	printf("      This mode is activated when any of the following parameter is provided:\n");
	printf("    -dateconv:calendar <year> <month_number> <day> <hour> <minute> <seconds>\n");
	printf("               <year> has to be equal or greater than 1980, <hour> is in 24 hour format and <seconds> can have decimal values.\n");
	printf("    -dateconv:doy <year> <DoY> <SoD>\n");
	printf("               <year> has to be equal or greater than 1980, <DoY> is in range 1 to 366.\n");
	printf("    -dateconv:gpsweek <GPSWeek> <SoW>\n");
	printf("    -dateconv:mjdn <MJDN> <SoD>\n");
	printf("               <MJDN> must be equal or greater than 44244.\n");
	printf("\n  COORDINATE CONVERSION OPTIONS\n");
	printf("      This mode is for converting a coordinate system to all supported coordinate systems (cartesian, geodetic -or ellipsoidal- and spherical) and exit.\n");
	printf("      This mode is activated when any of the following parameter is provided:\n");
	printf("    -coordconv:cartesian <x> <y> <z>\n");
	printf("               X, Y and Z coordinates unit is metres.\n");
	printf("    -coordconv:geodetic <lon> <lat> <height>\n");
	printf("               Longitude is in degrees (range [-180..180]), latitude is in degrees (range [-90..90]) and height is in metres.\n");
	printf("    -coordconv:spherical <lon> <lat> <radius>\n");
	printf("               Longitude is in degrees (range [-180..180]), latitude is in degrees (range [-90..90]) and radius is in metres.\n");
	printf("\n  WORK MODES\n");
	printf("    gLAB can work in nine different modes:\n");
	printf("        - Positioning Mode: 'Standard' mode, where all the processing is done, and a solution for a\n");
	printf("                       receiver is provided as OUTPUT messages. The minimum parameters required for this\n");
	printf("                       mode are an input observation file ('-input:obs') and orbit and clock products\n");
	printf("                       ('-input:nav', '-input:sp3' or '-input:orb'/'-input:clk'). Using precise products\n");
	printf("                       will also require the use of an ANTEX file ('-input:ant'). For SBAS processing, an\n");
	printf("                       additional input SBAS file ('-input:sbas') is needed. For DGNSS processing, an\n");
	printf("                       additional input file ('-input:dgnss' or '-input:rtcm') is needed\n\n");
	printf("        - Show Input Mode: This mode only reads an input RINEX observation file and print its measurements.\n");
	printf("                       The parameter required for this mode is '-input:obs', and specifically, no orbit and\n");
	printf("                       clock products should be provided (if provided, gLAB will switch to Positioning Mode)\n\n"); 
	printf("        - Product Comparison Mode: This mode reads and compares two different sources of orbit and clock products.\n");
	printf("                       In order to use this mode, '-input:obs' must be avoided, and two different orbit and clock\n");
	printf("                       products should be provided. This mode outputs the SATDIFF, SATSTAT and STASTATTOT messages\n\n");
	printf("        - Show Product Mode: This mode reads a single source of orbit and clock products.\n");
	printf("                       In order to use this mode, '-input:obs' must be avoided, and a single orbit and clock\n");
	printf("                       product should be provided. This mode output SAT messages\n\n"); 
	printf("        - Convert mode: Only for SBAS. If the parameter '-onlyconvert' is given, gLAB will just generate a RINEX-B 2.11 or EMS\n");
	printf("                       or Pegasus files (depending on the parameters) and it will not process any GNSS data.\n");
	printf("                       The minimum parameters for this mode are an SBAS file ('-input:sbas'), the '-onlyconvert' parameter\n");
	printf("                       and an output file format ('-output:rinexb', '-output:ems', '-output:pegasus')\n\n");
	printf("        - SBAS Plots Mode: This mode is activated when only a navigation file and a SBAS file are given. In this mode,\n");
	printf("                       three plots are computed: SBAS Availability, SBAS Continuity Risk and SBAS Ionosphere Corrections Availability.\n");
	printf("                       The three plots are computed in PA mode in the delimited (squared) region and resolution during one day (the Availability and\n");
	printf("                       Continuity Risk are computed at a one second rate, while the Ionosphere Corrections Availability is computed at a 300 seconds rate by default).\n");
	printf("                       For the three plots the values are computed for a Fault-Free receiver (no data gaps, no cycle-slips).\n");
	printf("                       For SBAS Availability plot, an epoch at a given latitude and longitude and height (by default is is sea level -0 metres-)\n");
	printf("                         is consired to be available when both the Horizontal and Vertical Protection Levels are below their respective thresholds.\n");
	printf("                       For SBAS Continuity Risk plot, it is computed the probability of having a discontinuity (i.e. no SBAS PA solution) during the\n");
	printf("                         next 15 seconds (i.e. using a sliding window of 15 seconds).\n");
	printf("                       For SBAS Ionosphere Corrections Availability plot, each coordinate in the map is considered as a pierce point at 350 km height,\n");
	printf("                         and it is considered as available when a SBAS ionosphere can be computed at the given pierce point.\n");
	printf("                       The minimum parameters to activate this mode are the input navigation file ('-input:nav') and the input SBAS message file ('-input:sbas').\n");
	printf("                       The output files have to be processed with graph program (with '--sbas' parameter) in order to generate the plots.\n");
	printf("                       The available output messages in this mode are INFO [default on], SBASIONO [default off] and SBASUNSEL [default off].\n");
	printf("                       NOTE: With the default configuration, the computation time is around 2 hours. Increasing resolution or map size will significantly increase computation time.\n\n");
	printf("        - Add User Error to RINEX: This mode reads a RINEX observation file, a user added error file and creates a new RINEX observation file, with the same header, version\n");
	printf("                       and number of measurements, but the measurements have the user error added into them.\n");
	printf("        - Date Conversion: When '-dateconv:calendar' or '-dateconv:doy' or '-dateconv:gpsweek' or '-dateconv:mjdn' are provided, gLAB will read the date\n");
	printf("                       from user input and convert it to all other date formats, print them in screen and exit.\n\n");  
	printf("        - Coordinate Conversion: When '-coordconv:cartesian' or '-coordconv:geodetic' or '-coordconv:spherical' are provided, gLAB will read the coordinates\n");
	printf("                       from user input and convert it to all other coordinate systems, print them in screen and exit.\n");  
	printf("\n  NOTES FOR PEGASUS OUTPUT FORMAT\n");
	printf("     Pegasus is GNSS data processing from Eurocontrol. Pegasus does not read the RINEX-B or EMS SBAS files, it converts them to columnar text files\n");
	printf("       and later processes with these text files. Each text file contains one message type -except for fast correction messages, which are all grouped\n");
	printf("       in the same file; and the GEO navigation data, which is RINEX 2 format-.\n");
	printf("       Each columnar text file has a header line with the name of each value, and the values are printed in decimal format.\n");
	printf("       A full explanation of the Pegasus format can be found in appendixes I.5-I.16 in their ICD at http://www.icao.int/Meetings/AMC/MA/2004/GNSS/icd.pdf\n");
	printf("\n  NOTES FOR PREPROCESSING\n");
	printf("     Pseudorange Jumps:\n");
	printf("       Some receivers, after updating the clock, they adjust the code but not the carrier phase measurement, producing a jump in the code\n");
	printf("         but not in the carrier phase. Therefore, code and carrier phase are not consistent (the difference between code and\n");
	printf("         carrier phase is not continuous). If the carrier phase is not adjusted, it will detected as a cycle-slip.\n");
	printf("\n  NOTES FOR SBAS PROCESSING\n");
	printf("    When processing with SBAS corrections, gLAB will use MOPS-D standard values and configuration by default.\n");
	printf("    Most of these parameters and configuration can be modified by the user, regardless if these parameters are MOPS compliant or not.\n");
	printf("    The specific SBAS parameters that can be modified by the user are:\n");
	printf("        Smoothing:       Can be disabled or changed the number of epochs [default 100 epochs]\n");
	printf("        Steady-state:    Can be disabled or changed the number of epochs [default 360 epochs]\n");
	printf("        Ionosphere:      Any ionosphere model available in gLAB (e.g. IONEX) can be applied instead of the SBAS ionosphere model.\n");
	printf("        Time outs:       Time outs for all corrections can be user defined\n");
	printf("        Mode switch:     Switching from PA to NPA can be enabled or disabled [default disabled]\n");
	printf("        GEO switch:      GEO switching can be enabled or disabled [default disabled]. Furthermore, after a GEO switch,\n");
	printf("                         the user can decide if to stay in the new GEO or try to fallback to the initial GEO when possible.\n");
	printf("        Decimation:      gLAB can process at any data rate. In order to keep integrity of results with 1Hz SBAS data rate,\n");
	printf("                            messages will be read every second, and special events will be handled every second.\n");
	printf("                            The special events are: receive an alarm message or an UDREI>=14, miss 4 consecutive messages\n");
	printf("                            or receive 4 consecutive messages with wrong CRC. Decimation is useful for studying slow\n");
	printf("                            varying corrections, such as long term corrections or ionosphere.\n");
	printf("        Navigation:      Both kinematic and static navigation mode can be selected. Default is kinematic.\n");
	printf("\n    Mode and GEO switch notes:\n");
	printf("      If both mode and GEO switch are enabled, GEO switch is tried first always, as switching GEO keeps PA mode.\n");
	printf("      If option '-model:geofallback' is enabled, gLAB will try to switch to the first GEO used in processing after\n");
	printf("        the time between switches (defined by parameter '-model:switchtime') after a GEO switch occurs.\n");
	printf("      If option '-model:maintaingeo' is enabled gLAB will maintain the current GEO (independently if it was selected\n");
	printf("        by the user or by a GEO switch) during all the processing while it can provide a PA solution.\n");
	printf("      If both options '-model:maintaingeo' and '-model:geofallback' are enabled, '-model:geofallback' option behaviour will prevail.\n");
	printf("      If both options '-model:maintaingeo' and '-model:geofallback' are disabled, after a GEO switch, gLAB will try to switch\n");
	printf("        to the previous GEO independently if it was the first one used or not. If there are only two GEOs available (and the use of mixed GEO\n");
	printf("        data is disabled), this behaviour is equivalent as in the '-model:geofallback' option, due to the previous GEO will be always the first GEO used.\n");
	printf("\n    SBAS Maritime mode:\n");
	printf("      Maritime mode is a special configuration for SBAS. In this configuration, message type 10 (degradation parameters), type 27 (service message)\n");
	printf("        and type 28 (clock ephemeris covariance matrix) are not used. Therefore, the sigma of fast and long term corrections is computed with the\n");
	printf("        following formula:\n");
	printf("                      Sigmaflt = SigmaUDRE + 8 [metres]\n");
	printf("      Maritime mode is configured with parameter '-model:sbasmaritime', which is a shortcut for providing these parameters: '-model:nomt10'\n");
	printf("        and '-model:nomt2728'.\n");
	printf("\n  NOTES FOR PREFIT OUTLIER DETECTION\n");
	printf("      There are two prefit outlier detectors in gLAB:\n");
	printf("       - Prefit outlier detector comparing against the median (by default disabled):\n");
	printf("          The procedure for this detector is:\n");
    printf("           Compute the median of all prefits\n");
    printf("           For each satellite:\n");
    printf("              Compute absolute value of the difference between the prefit and the median\n");
    printf("              If the difference is higher than the threshold, unselect the satellite\n\n");
	printf("       - Prefit outlier detector comparing the absolute values (by default disabled):\n");
	printf("          The procedure for this detector is:\n");
    printf("           For each satellite available:\n");
    printf("             Compute the absolute value of its prefit (ReferencePrefit)\n");
    printf("             Set a range for all other satellite prefits defined as:\n"); 
    printf("                Range=[abs(ReferencePrefit)-threshold,abs(ReferencePrefit)+threshold]\n");
    printf("                For each satellite (except the reference one):\n");
    printf("                  Check if prefits are inside the range\n");
    printf("                If half or more of the satellites are unvalid, then the current satellite is an outlier\n");
    printf("                Else discard the satellites with prefits outside the range.\n");
	printf("       If receiver position is fixed, gLAB will allow the outlier detector to discard all satellites in the current epoch\n");
	printf("       If receiver position is not fixed, if more than half of the available satellites are discarded, then, the prefit outlier detector\n");
	printf("          will not discard any satellite, as it will assume that the solution still has to converge\n");
	printf("       A recommended value for the thresholds of the prefit outlier detectors is 30 metres\n");
	printf("\n  NOTES FOR DGNSS PROCESSING\n");
	printf("    Sigma inflation: During the transient period until the smoother converges, the measurement noise sigma is inflated according\n");
	printf("                     to the next equation:\n");
	printf("                       Sigma_inflat= f(n)/f(Nstdy) * sigma\n");
	printf("                            n<N    f(n)=sqrt(1/n)\n");
	printf("                            n>=N   f(n)=sqrt(1/(2*N-1)*(1+((N-1)/N)^(2*(n-N)+1)))\n");
	printf("                          where:\n");
	printf("                            n:     number of processed samples\n");
	printf("                            N:     number of samples of the smoothing window\n");
	printf("	                        Nstdy: number of samples when reaching the steady state: In gLAB, Nstdy=(int)(3.6*N)\n");
	printf("	                  For instance, with 1 second sampling rate and N=100, the stationary state (Nstdy) is assumed to be reached after 360 seconds\n");
}

/*****************************************************************************
 * Name        : showExamples
 * Description : Shows the program examples in the standard output
 * Parameters  : None
 *****************************************************************************/
void showExamples () {
	#if defined _OPENMP
		printf("gLAB version v%s (with OpenMP multithread), built on %s %s\n",VERSION,__DATE__,__TIME__);
	#else
		printf("gLAB version v%s, built on %s %s\n",VERSION,__DATE__,__TIME__);
	#endif
	printf("GNSS LABORATORY. Tool to analyse GNSS data\n");
	printf("Write 'gLAB -help' for help on the options\n");
	printf("Usage:\n");
	printf("    gLAB [options]\n");
	printf("Examples:\n");
	printf("    o Typical PPP:\n");
	printf("        gLAB -input:obs madr2000.06o -input:sp3 igs13843.sp3 -input:ant igs_pre1400.atx -filter:meas carrierphase -filter:nav static\n");
	printf("    o Same as before using the defaults:\n");
	printf("        gLAB -input:obs madr2000.06o -input:sp3 igs13843.sp3 -input:ant igs_pre1400.atx\n");
	printf("    o Typical SPP:\n");
	printf("        gLAB -input:obs madr2000.06o -input:nav brdc2000.06n\n");
	printf("    o PPP in static mode with pseudorange only decimating to 900 seconds:\n");
	printf("        gLAB -input:obs madr2000.06o -input:sp3 igs13843.sp3 -input:ant igs_pre1400.atx -filter:meas pseudorange -filter:nav static -pre:dec 900\n");
	printf("    o Typical PPP without INFO messages:\n");
	printf("        gLAB -input:obs madr2000.06o -input:sp3 igs13843.sp3 -input:ant igs_pre1400.atx --print:info\n"); 
	printf("    o Typical PPP with some verbose options:\n");
	printf("        gLAB -input:obs madr2000.06o -input:sp3 igs13843.sp3 -input:ant igs_pre1400.atx -print:none -print:cycleslips -print:model -print:satellites\n");
	printf("    o Typical standalone using standard ionospheric model (Klobuchar) and not using it\n");
	printf("        gLAB -input:obs madr2000.06o -input:nav brdc2000.06n -filter:nav kinematic\n");
	printf("        gLAB -model:iono no -input:obs madr2000.06o -input:nav brdc2000.06n -filter:nav kinematic\n");
	printf("    o Typical standalone using SBAS ionosphere (without any other SBAS correction)\n");
	printf("        gLAB -input:obs madr2000.06o -input:nav brdc2000.06n -input:sbasiono M1202000.06b -model:iono SBAS\n");
	printf("    o Standard SBAS processing:\n");
	printf("        gLAB -input:obs madr2000.06o -input:nav brdc2000.06n -input:sbas M1202000.06b\n");
	printf("    o Standard SBAS processing with file conversion to Pegasus format:\n");
	printf("        gLAB -input:obs madr2000.06o -input:nav brdc2000.06n -input:sbas M1202000.06b -output:pegasus\n");
	printf("    o Standard DGNSS processing:\n");
	printf("        gLAB -input:obs madr2000.06o -input:nav brdc2000.06n -input:rtcm rtcm2000.06rtcm2 -input:rtcm:initdate 20060718 -input:rtcm:inithour 00\n");
	printf("    o Convert RINEX-B file to ems and Pegasus format and exit without processing:\n");
	printf("        gLAB -input:sbas M1202000.06b -output:ems -output:pegasus -onlyconvert\n");
	printf("    o Convert EMS file to Pegasus format (with columns aligned and the output files in current directory) and exit without processing:\n");
	printf("        gLAB -input:sbas M1202000.ems -output:pegasus -output:pegfilealign -output:sbasdir \".\" -onlyconvert\n");
	printf("    o Convert RTCM file to plain text ASCII or RINEX format:\n");
	printf("        gLAB -input:rtcm rtcm2000.06rtcm2 -input:rtcm:initdate 20060718 -input:rtcm:inithour 00\n");
	printf("    o Save output to a file:\n");
	printf("        gLAB [options] > outputfile\n");
	printf("        gLAB [options] -output:file outputfile\n");
	printf("    o Print only INPUT messages without any decimation, do not process:\n");
	printf("      (no -input:sp3 nor -input:nav nor -input:orb/-input:clk)\n");
	printf("        gLAB -input:obs madr2000.06o -pre:dec 0 -print:none -print:input\n");
	printf("    o Compute SBAS plots with the default configuration (EGNOS region):\n");
	printf("        gLAB -input:nav brdc2000.06n -input:sbas M1202000.06b\n");
	printf("    o Compute SBAS plots specifying the region and output file:\n");
	printf("        gLAB -input:nav brdc2000.06n -input:sbas M1202000.06b -sbasplots:minlat 25 -sbasplots:maxlat 70 -sbasplots:minlon -30 -sbasplots:maxlon 40 -output:sbasplots SBASplots_120_200_2016\n");
	printf("    o Compute SBAS plots specifying the resolution, vertical and horizontal alarm limits and resolution for availability and ionosphere plots:\n");
	printf("        gLAB -input:nav brdc2000.06n -input:sbas M1202000.06b -sbasplots:hal 30 -sbasplots:val 35 -sbasplots:availstep 1 -sbasplots:ionostep 1\n");

}

/*****************************************************************************
 * Name        : showConfig
 * Description : Shows information on the config file
 * Parameters  : None
 *****************************************************************************/
void showConfig () {
	#if defined _OPENMP
		printf("gLAB version v%s (with OpenMP multithread), built on %s %s\n",VERSION,__DATE__,__TIME__);
	#else
		printf("gLAB version v%s, built on %s %s\n",VERSION,__DATE__,__TIME__);
	#endif
	printf("GNSS LABORATORY. Tool to analyse GNSS data\n");
	printf("Write 'gLAB -help' for help on the options\n");
	printf("Usage:\n");
	printf("    gLAB [options]\n");
	printf("\n  CONFIG FILE\n");
	printf("    The config file can be specified by the '-input:cfg <file>' command-line parameter. This file is an alternative\n");
	printf("    way to configure the behaviour of the tool. In case that there are parameters in the config file and in the\n");
	printf("    command-line arguments, the command-line parameters will have priority over the config file ones. The order to\n");
	printf("    read the parameters is:\n");
	printf("        o Check if the '-input:cfg' parameter exist in the command-line arguments\n");
	printf("        o If it exists, parse config file parameters\n");
	printf("        o Parse command-line parameters\n");
	printf("    The config file is basically a mirror of the command-line parameters. The way to include an option is as follows:\n");
	printf("        <parameter> <options> of the parameter\n");
	printf("    For example, for the parameters '-input:obs upc42000_10s.06o' and '-filter:select 2 PC LC', the config file shall be:\n");
	printf("        -input:obs upc42000_10s.06o\n");
	printf("        -filter:select 2 PC LC\n");
	printf("    All lines beginning with # in the config file shall be interpreted as a comment, and ignored in the parsing process\n");
	printf("\n  SAMPLE CONFIG FILE\n");
	printf("        # INPUT\n");
	printf("        -input:obs madr2000.06o\n");
	printf("        -input:nav brdc2000.06n\n");
	printf("        -input:ant igs_pre1400.atx\n\n");
	printf("        # PREPROCESS\n");
	printf("        -pre:elevation 5\n\n");
	printf("        # MODEL\n");
	printf("        -model:recphasecenter ANTEX\n\n");
	printf("        # FILTER\n");
	printf("        -filter:meas carrierphase\n");
	printf("        -filter:nav kinematic\n\n");
	printf("        # OUTPUT\n");
	printf("        -print:all\n\n");
	printf("    This config file will be equivalent to the command-line execution:\n");
	printf("        gLAB -input:obs madr2000.06o -input:nav brdc2000.06n -input:ant igs_pre1400.atx -pre:elevation 5 -model:recphasecenter ANTEX -filter:meas carrierphase -filter:nav kinematic -print:all\n");
}

/*****************************************************************************
 * Name        : showMessages
 * Description : Shows the fields of each output message
 * Parameters  : None
 *****************************************************************************/
void showMessages () {
	#if defined _OPENMP
		printf("gLAB version v%s (with OpenMP multithread), built on %s %s\n",VERSION,__DATE__,__TIME__);
	#else
		printf("gLAB version v%s, built on %s %s\n",VERSION,__DATE__,__TIME__);
	#endif
	printf("GNSS LABORATORY. Tool to analyse GNSS data\n");
	printf("Write 'gLAB -help' for help on the options\n");
	printf("Usage:\n");
	printf("    gLAB [options]\n");
	printf("\n  MESSAGES FORMAT\n");
	printf("    INFO\n");
	printf("        INFO messages are shown at several points in the program and provide information on the\n");
	printf("          program configuration, events and problems it may encounter, which are:\n\n"); 
	printf("             At the start of the file, showing information about gLAB configuration.\n"); 
	printf("             An inconsistent clock update on the receiver.\n"); 
	printf("             In SBAS processing, a GEO or mode switch.\n"); 
	printf("             In DGNSS processing, a switch from DGNSS to SPP solution mode.\n"); 
	printf("             A change in the a priori receiver coordinates (only when receiver coordinates are computed by gLAB).\n");
	printf("             The new position to be used from the reference position file (only when a reference file is provided).\n");
	printf("             No solution was computed, along with the reason for not being able to compute the\n");
	printf("                 solution (not enough satellites available, singular geometry matrix or GDOP too high).\n"); 
	printf("\n    USERADDEDERROR [when user-defined error file is given]\n");
	printf("        User-defined error added to measurements before cycle-slip detection and smoothing.\n");
	printf("        Field 1:  'USERADDEDERROR'\n");
	printf("        Field 2:  Year\n");
	printf("        Field 3:  Doy\n");
	printf("        Field 4:  Seconds of day\n");
	printf("        Field 5:  GPS week\n");
	printf("        Field 6:  Time of week\n");
	printf("        Field 7:  GNSS System (GPS, GAL, GLO or GEO)\n");
	printf("        Field 8:  PRN satellite identifier\n");
	printf("        Field 9:  Measurement identifier (as string)\n");
	printf("        Field 10: Raw measurement (phase measurements are prealigned) [m]\n");
	printf("        Field 11: Raw measurement plus total user-defined error (phase measurements are prealigned) [m]\n");
	printf("        Field 12: Total number of active user-defined error functions\n");
	printf("        Field 13: Total user-defined error [m]\n");
	printf("        Field 14: Number of active Step function error\n");
	printf("        Field 15: Step function error value [m]\n");
	printf("        Field 16: Number of active Ramp function error\n");
	printf("        Field 17: Ramp function error value [m]\n");
	printf("        Field 18: Number of active Sinusoidal function error\n");
	printf("        Field 19: Sinusoidal function error value [m]\n");
	printf("        Field 20: Number of active AWGN (Additive White Gaussian Noise) function error\n");
	printf("        Field 21: AWGN function error value [m]\n");
	printf("        Sample:\n");
	printf("            USERADDEDERROR   2015 161     0.00 1848 259200.00 GPS   4 C1C  23140309.8200  23140314.8200  1         5.0000  1         5.0000  0         0.0000  0         0.0000  0         0.0000\n\n");
	printf("    CS\n");
	printf("        Cycle-slip message information. It is shown when a cycle-slip is found by any detector.\n");
	printf("        A line will be printed for each CS detector that has found a CS.\n");
	printf("        The first 6 fields are common, afterwards, there are five possible different CS messages depending on\n");
	printf("        the cycle-slip detector activated.\n");
	printf("        Field 1:  'CS' or 'CS_USER' for Rover Station (user)\n");
	printf("        Field 1:  'CS_REF' for Reference Station\n");
	printf("        Field 2:  Year\n");
	printf("        Field 3:  Doy\n");
	printf("        Field 4:  Seconds of day\n");
	printf("        Field 5:  GNSS System (GPS, GAL, GLO or GEO)\n");
	printf("        Field 6:  PRN satellite identifier\n");
	printf("        If cycle-slip detector is Data gap:\n");
	printf("            Field 7:  'DATA_GAP'\n");
	printf("            Field 8:  '='\n");
	printf("            Field 9:  Delta time between usable epochs\n");
	printf("            Field 10: 'THRESHOLD'\n");
	printf("            Field 11: '='\n");
	printf("            Field 12: Data gap threshold\n");
	printf("            Sample:\n");
	printf("                CS       2014 288 44997.00 GPS 32  DATA_GAP = 45.000000 THRESHOLD = 40.000000\n");
	printf("        If cycle-slip detector is Loss of Lock Indicator:\n");
	printf("            Field 7:  'LLI'\n");
	printf("            Sample:\n");
	printf("                CS       2014 288 44942.00 GPS 32  LLI\n");
	printf("        If cycle-slip detector is Geometry-free carrier phase:\n");
	printf("            Field 7:  'LI'\n");
	printf("            Field 8:  '='\n");
	printf("            Field 9:  LI value\n");
	printf("            Field 10: 'THRESHOLD'\n");
	printf("            Field 11: '='\n");
	printf("            Field 12: LI threshold\n");
	printf("            Sample:\n");
	printf("                CS       2014 288 42092.00 GPS  7  LI = 0.119386 THRESHOLD = 0.052861\n");
	printf("        If cycle-slip detector is Melbourne-Wubbena:\n");
	printf("            Field 7:  'LI'\n");
	printf("            Field 8:  '='\n");
	printf("            Field 9:  Bw value\n");
	printf("            Field 10: 'THRESHOLD'\n");
	printf("            Field 11: '='\n");
	printf("            Field 12: Bw threshold\n");
	printf("            Sample:\n");
	printf("                CS       2014 288 42092.00 GPS  7  Bw = 1.992188 THRESHOLD = 1.839927\n");
	printf("        If cycle-slip detector is L1-C1 difference:\n");
	printf("            Field 7:  'LI'\n");
	printf("            Field 8:  '='\n");
	printf("            Field 9:  L1C1 value\n");
	printf("            Field 10: 'THRESHOLD'\n");
	printf("            Field 11: '='\n");
	printf("            Field 12: L1C1 threshold\n");
	printf("            Sample:\n");
	printf("                CS       2014 365 55344.00 GPS  7  L1C1 = 747.078356 THRESHOLD = 0.876845\n\n");
	printf("    INPUT\n");
	printf("        Input data message. It is shown after an epoch is read, decimated and added user-defined error\n");
	printf("        It contains the measurements for each satellite for this epoch\n");
	printf("        Field 1:  'INPUT'\n");
	printf("        Field 2:  Year\n");
	printf("        Field 3:  Doy\n");
	printf("        Field 4:  Seconds of day\n");
	printf("        Field 5:  GNSS System (GPS, GAL, GLO or GEO)\n");
	printf("        Field 6:  PRN satellite identifier\n");
	printf("        Field 7:  Arc length (number of undecimated epochs after the last cycle-slip)\n");
	printf("        For GPS:\n");
	printf("            Field 8:  C1 [C1C]\n");
	printf("            Field 9:  P1 [C1P]\n");
	printf("            Field 10: P2 [C2P]\n");
	printf("            Field 11: L1 [L1P] (prealigned, in metres)\n");
	printf("            Field 12: L2 [L2P] (prealigned, in metres)\n");
	printf("        For Galileo (GAL):\n");
	printf("            Field 8:  C1A\n");
	printf("            Field 9:  C1B\n");
	printf("            Field 10: C1C\n");
	printf("            Field 11: C7Q\n");
	printf("            Field 12: C8Q\n");
	printf("            Field 13: L1A (prealigned, in metres)\n");
	printf("            Field 14: L1B (prealigned, in metres)\n");
	printf("            Field 15: L1C (prealigned, in metres)\n");
	printf("            Field 16: L7Q (prealigned, in metres)\n");
	printf("            Field 17: L8Q (prealigned, in metres)\n");
	printf("        For GLONASS (GLO):\n");
	printf("            Field 8:  C1 [C1C]\n");
	printf("            Field 9:  C2 [C2C]\n");
	printf("            Field 10: L1 [L1P](prealigned, in metres)\n");
	printf("            Field 11: L2 [L2P](prealigned, in metres)\n");
	printf("        For GEO:\n");
	printf("            Field 8:  C1 [C1C]\n");
	printf("        Sample:\n");
	printf("            INPUT     2006 200     0.00 GPS 19      1  23119003.9020  23119002.6110  23119004.0750  23119002.7507  23119004.0925\n\n");
	printf("    MEAS\n");
	printf("        Information of the input measurements in a variable format, and azimuth/elevation of the satellite.\n");
	printf("        It is written after modelling the message.\n");
	printf("        Field 1:   'MEAS'\n");
	printf("        Field 2:   Year\n");
	printf("        Field 3:   Doy\n");
	printf("        Field 4:   Seconds of day\n");
	printf("        Field 5:   GNSS System (GPS, GAL, GLO or GEO)\n");
	printf("        Field 6:   PRN satellite identifier\n");
	printf("        Field 7:   Elevation of the satellite [degrees]\n");
	printf("        Field 8:   Azimuth of the satellite [degrees]\n");
	printf("        Field 9:   Number of measurements\n");
	printf("        Field 10:  List of measurements included\n");
	printf("        Field 11-: Each following column is the value of the measurement specified in Field 10\n\n");
	printf("        If there is no data available on azimuth and elevation, the fields 7 and 8 will be fixed to zero.\n");
	printf("        Sample:\n");
	printf("            MEAS      2006 200     0.00 GPS 19   26.66  -79.62  6  C1C:L1C:C1P:L1P:C2P:L2P  23119003.9020         0.0000  23119002.6110  23119002.7507  23119004.0750  23119004.0925\n\n");
	printf("    MODEL\n");
	printf("        Model break down message. It is shown when a model can be fully computed for each measurement.\n");
	printf("        Field 1:  'MODEL' (if the satellite is used in the computation) or 'MODEL*' (if it is not)\n");
	printf("        Field 2:  Year\n");
	printf("        Field 3:  Doy\n");
	printf("        Field 4:  Seconds of day\n");
	printf("        Field 5:  GNSS System (GPS, GAL, GLO or GEO)\n");
	printf("        Field 6:  PRN satellite identifier\n");
	printf("        Field 7:  Measurement identifier (as string)\n");
	printf("        Field 8:  Signal flight time [sec]\n");
	printf("        Field 9:  Measured value [m]\n");
	printf("        Field 10: Full model value [m]\n");
	printf("        Field 11: Satellite X position [m]\n");
	printf("        Field 12: Satellite Y position [m]\n");
	printf("        Field 13: Satellite Z position [m]\n");
	printf("        Field 14: Satellite X velocity [m]\n");
	printf("        Field 15: Satellite Y velocity [m]\n");
	printf("        Field 16: Satellite Z velocity [m]\n");
	printf("        Field 17: Satellite-receiver geometric distance [m]\n");
	printf("        Field 18: Satellite clock correction [m]\n");
	printf("        Field 19: Satellite phase centre projection [m]\n");
	printf("        Field 20: Receiver phase centre projection [m]\n");
	printf("        Field 21: Receiver Antenna Reference Point (ARP) projection [m]\n");
	printf("        Field 22: Relativity correction [m]\n");
	printf("        Field 23: Wind-up correction [m] (for carrier phase measurements)\n");
	printf("        Field 24: Troposphere nominal correction [m]\n");
	printf("        Field 25: Ionosphere correction [m]\n");
	printf("        Field 26: Gravitational delay correction [m]\n");
	printf("        Field 27: Total Group Delay (TGD) correction [m]\n");
	printf("        Field 28: Solid tides correction [m]\n");
	printf("        Field 29: Satellite elevation [degrees]\n");
	printf("        Field 30: Satellite azimuth [degrees]\n");
	printf("        Field 31: Satellite SNR (Signal to Noise Ratio) [dbHz]\n\n");
	printf("        The satellite coordinates (fields 11-16) are given in the transmission epoch if the model of the\n");
 	printf("          signal transmission time is enabled (if it is disabled, they are given in the reception\n");
	printf("          time). The coordinates are relative to the antenna phase centre or satellite mass centre,\n");
	printf("          depending on the products input:\n");
	printf("            * Broadcast: Antenna Phase Centre\n");
	printf("            * Precise: Satellite Mass Centre\n");
	printf("        Field 9 is the direct measurement (as in the RINEX file), but scaled to metres for carrier phase\n");
	printf("          measurements. Field 10 is the model computed for this measurement. Field 10 is the direct sum\n");
	printf("          of fields 17 to 28.\n");
	printf("        When the '*' appears in field 1, it is due to smoothed code of the satellite has not reached steady-state, a SBAS processing mode switch\n");
	printf("          or SBAS GEO switch. When a mode or GEO switch occurs, the SBAS corrections have to be computed again.\n");
	printf("        The SNR value in field 31 may be any of these values (in this order): the \"S\" measurement in the\n");
	printf("          observation file, or if it is not present, it will be the SNR flag in the current measurement.\n");
	printf("          If no SNR is available, 999 will be printed in this field.\n");
	printf("        Sample:\n");
	printf("            MODEL     2006 200     0.00 GPS 19 L1P     0.07712  23119002.7507  23119008.7501   8811456.7780 -21033910.1687  13675922.8867      1828.7339      2353.7679      2467.3576  23119457.7652     -456.31787   0.00000  -0.04936  -0.01140   2.32333   0.10671   4.85412  -0.00000   0.01544   0.00000   0.06394   9.164  79.274\n\n");
	printf("    SATSEL\n");
	printf("        Message with debug information of the reason why a satellite has been discarded (or selected) for processing.\n");
	printf("        If multiple discard conditions are met in a single satellite, then a SATSEL message for each condition will be printed.\n");
	printf("        Field 1:  'SATSEL' (if navigation solution will be computed), 'SATSEL*' (if model parameters will be recomputed before the navigation solution, only in SBAS mode)\n");
	printf("        Field 2:  Year\n");
	printf("        Field 3:  Doy\n");
	printf("        Field 4:  Seconds of day\n");
	printf("        Field 5:  GNSS System (GPS, GAL, GLO or GEO)\n");
	printf("        Field 6:  PRN satellite identifier\n");
	printf("        Field 7:  'selected' if satellite is used or 'discarded:' if satellite is not used\n");
	printf("        Field 8:  Discard reason if satellite is not used\n");
	printf("        Sample:\n");
	printf("            SATSEL    2006 200     0.00 GPS 7 discarded: Elevation too low ( 3.04 )\n\n");
	printf("        The possible values for field 8 are:\n");
    printf("            - Arc too short (<arclength>)\n");
	printf("            - Pre-Check; measurements missing for CS detection\n");
	printf("            - Not enough consecutive samples (current <value>, minimum <value>)\n");
	printf("            - Unconsistency of measurements\n");
	printf("            - Outlier in LI detector\n");
	printf("            - Outlier in Bw detector\n");
	printf("            - Cycle-slip\n");
	printf("            - Measurement unavailable (<meas>)\n");
	printf("            - Deselection forced\n");
	printf("            - SNR too low (<value>)\n");
	printf("            - Steady-state operation not reached. <value> epochs passed, still <value> epochs to achieve <value>\n");
	printf("            - No code measurement available\n");
	printf("            - C1C measurement unavailable\n");
	printf("            - Ephemerides unavailable\n");
	printf("            - Satellite phase center corrections unavailable\n");
	printf("            - DCBs unavailable (strict TGD treatment)\n");
	printf("            - SBAS corrections unavailable\n");
	printf("            - Elevation too low (<value>)\n");
	printf("            - Satellite under eclipse\n");
	printf("            - Satellite was under eclipse <value> seconds ago\n");
	printf("            - URA value (<value>) is equal or greater than the threshold (<threshold>)\n");
	printf("            - Missing IONEX data\n");
	printf("            - Missing FPPP data\n");
	printf("            - SBAS iono unavailable\n");
	printf("            - STEP detected (jump of <value> greater than <threshold>)\n");
	printf("            - Prefit too high in comparation with other satellites\n");
	printf("            - Prefit too high in comparation with other satellites (threshold <threshold> metres)\n");
	printf("            - Prefit too different (<value>) with respect to the prefit median (<median>), threshold <threshold> metres\n");
	printf("            - No DGNSS corrections\n");
	printf("            - No DGNSS corrections: Time out\n");
	printf("            - No DGNSS corrections: Excluded during the smoother conversion in the Reference Station\n");
	printf("            - No DGNSS corrections: IODE from BRDC and RTCM do not match\n");
	printf("            - No DGNSS corrections: Excluded due to differential correction is too large\n");
	printf("            - Invalid GNSS System: <system>\n\n");
	printf("    PREFIT\n");
	printf("        Prefilter values message. It provides the measurement-model values. It is shown in each filter\n");
	printf("        execution.\n");
	printf("        Field 1:  'PREFIT' (if the satellite is used in the computation) or 'PREFIT*' (if it is not)\n");
	printf("        Field 2:  Year\n");
	printf("        Field 3:  Doy\n");
	printf("        Field 4:  Seconds of day\n");
	printf("        Field 5:  GNSS System (GPS, GAL, GLO or GEO)\n");
	printf("        Field 6:  PRN satellite identifier\n");
	printf("        Field 7:  Measurement identifier (as string)\n");
	printf("        Field 8:  Measurement-model value (prefit) [m]\n");
	printf("        Field 9:  Measurement value [m]\n");
	printf("        Field 10: Model value [m]\n");
	printf("        Field 11: X-partial derivative (-X component of the satellite line-of-sight vector)\n");
	printf("        Field 12: Y-partial derivative (-Y component of the satellite line-of-sight vector)\n");
	printf("        Field 13: Z-partial derivative (-Z component of the satellite line-of-sight vector)\n");
	printf("        Field 14: T-partial derivative \n");
	printf("        Field 15: Elevation of the satellite [degrees]\n");
	printf("        Field 16: Azimuth of the satellite [degrees]\n");
	printf("        Field 17: Standard deviation of the measurement  (for the filter) [m]\n");
	printf("        Field 18: Troposphere wet mapping\n");
	printf("        Field 19: Arc number\n\n");
	printf("        In general Field 8 = Field 9 - Field 10, but this is no longer true when using smoothing, as the\n");
	printf("          Field 9 is the raw measurement without smoothing, but the Field 8 computation takes smoothing into\n");
	printf("          account.\n");
	printf("        Sample:\n");
	printf("            PREFIT    2006 200   300.00 GPS 19  LC        -7.3029  22982271.7155  22982279.0184   28.28   0.3931  -0.4834   0.7822   1.0000   77.912   130.010    17.883     2\n\n");
	printf("    EPOCHSAT\n");
	printf("        Message with the satellites used to compute the solution. It is shown when the filter is run,\n");
	printf("        and is given for each measurement\n");
	printf("        Field 1:  'EPOCHSAT'\n");
	printf("        Field 2:  Year\n");
	printf("        Field 3:  Doy\n");
	printf("        Field 4:  Seconds of day\n");
	printf("        Field 5:  Measurement identifier (as string)\n");
	printf("        Field 6:  Number of satellites used in solution computation\n");
	printf("        Field 7-: Each following column is the identifier of a satellite\n");
	printf("        Sample:\n");
	printf("            EPOCHSAT  2006 200   300.00  PC  7 15  3 19 16 18 21 22\n\n");
	printf("    POSTFIT\n");
	printf("        Postfilter values message. It provides the corrected prefits with the filter estimation. It is\n");
	printf("        shown in each filter execution.\n");
	printf("        Field 1:  'POSTFIT'\n");
	printf("        Field 2:  Year\n");
	printf("        Field 3:  Doy\n");
	printf("        Field 4:  Seconds of day\n");
	printf("        Field 5:  GNSS System (GPS, GAL, GLO or GEO)\n");
	printf("        Field 6:  PRN satellite identifier\n");
	printf("        Field 7:  Measurement identifier (as string)\n");
	printf("        Field 8:  Measurement-corrected model value (postfit) [m]\n");
	printf("        Field 9:  Measurement value [m]\n");
	printf("        Field 10: Corrected model value with the filter estimations[m]\n");
	printf("        Field 11: Elevation of the satellite [degrees]\n");
	printf("        Field 12: Azimuth of the satellite [degrees]\n");
	printf("        Field 13: Only given for carrier phase measurements. It is the estimated carrier phase ambiguity. [m]\n\n");
	printf("        As with PREFIT messages, Field 8 is not necessary Field 9 - Field 10 when using smoothing.\n");
	printf("        Sample:\n");
	printf("            POSTFIT   2006 200   300.00 GPS 19  LC         0.0000  22982271.7155  22982271.7155   77.912   130.010   0.3029\n\n");
	printf("    FILTER\n");
	printf("        Filter solution message. This message provides direct information on the filter estimates. It is shown\n");
	printf("        in each filter execution.\n");
	printf("        Field 1:  'FILTER'\n");
	printf("        Field 2:  Year\n");
	printf("        Field 3:  Doy\n");
	printf("        Field 4:  Seconds of day\n");
	printf("        Field 5-: Filter estimates. The order is: 3D estimated position, clock, troposphere and ambiguities\n"); 
	printf("        The number of fields is variable in this message. With a full filter (troposphere and ambiguities\n");
	printf("        estimation), the fields are as follows:\n");
	printf("            Field 5:  Receiver X position [m]\n");
	printf("            Field 6:  Receiver Y position [m]\n");
	printf("            Field 7:  Receiver Z position [m]\n");
	printf("            Field 8:  Receiver clock [m]\n");
	printf("            Field 9:  Zenith Tropospheric Delay [m]\n");
	printf("            Field 10: Carrierphase ambiguities [m]\n");
	printf("        Sample:\n");
	printf("            FILTER    2006 200   300.00   4849203.0770   -360328.5730   4114913.9184        -7.4867         2.1946        -0.0001         1.1079        -1.1073         0.3029         0.4555         0.0897         0.0001         0.3845         0.2136\n\n");
	printf("    OUTPUT\n");
	printf("        Receiver solution message. This message provides the estimated receiver position. It is shown in\n");
	printf("        each filter execution.\n");
	printf("        Field 1:  'OUTPUT'\n");
	printf("        Field 2:  Year\n");
	printf("        Field 3:  Doy\n");
	printf("        Field 4:  Seconds of day\n");
	printf("        Field 5:  Square root of the sum of the covariance matrix. This is a measure of the convergence of the filter\n");
	printf("        Field 6:  Receiver X position [m]\n");
	printf("        Field 7:  Receiver Y position [m]\n");
	printf("        Field 8:  Receiver Z position [m]\n");
	printf("        Field 9:  Receiver X position - Nominal a priori X position [m]\n");
	printf("        Field 10: Receiver Y position - Nominal a priori Y position [m]\n");
	printf("        Field 11: Receiver Z position - Nominal a priori Z position [m]\n");
	printf("        Field 12: Receiver X formal error [m]\n");
	printf("        Field 13: Receiver Y formal error [m]\n");
	printf("        Field 14: Receiver Z formal error [m]\n");
	printf("        Field 15: Receiver latitude [degrees]\n");
	printf("        Field 16: Receiver longitude [degrees]\n");
	printf("        Field 17: Receiver height [m]\n");
	printf("        Field 18: Receiver North difference in relation to nominal a priori position [m]\n");
	printf("        Field 19: Receiver East difference in relation to nominal a priori position [m]\n");
	printf("        Field 20: Receiver Up difference in relation to nominal a priori position [m]\n");
	printf("        Field 21: Receiver formal error in North direction [m]\n");
	printf("        Field 22: Receiver formal error in East direction [m]\n");
	printf("        Field 23: Receiver formal error in Up direction [m]\n");
	printf("        Field 24: Geometric Dilution of Precision (GDOP)\n");
	printf("        Field 25: Positioning Dilution of Precision (PDOP)\n");
	printf("        Field 26: Time Dilution of Precision (TDOP)\n");
	printf("        Field 27: Horizontal Dilution of Precision (HDOP)\n");
	printf("        Field 28: Vertical Dilution of Precision (VDOP)\n");
	printf("        Field 29: Zenith Tropospheric Delay (including nominal value) [m]\n");
	printf("        Field 30: Zenith Tropospheric Delay (excluding nominal value) [m]\n");
	printf("        Field 31: Zenith Tropospheric Delay formal error [m]\n");
	printf("        Field 32: Number of satellites used in the navigation solution\n");
	printf("        Field 33: Processing mode indicator\n\n");
	printf("        The fields 29, 30 and 31 will be zero if troposphere is not estimated (only estimated in PPP mode)\n");
	printf("        Processing mode indicator in field 33 may have the following values:\n");
	printf("           0 -> SPP\n");
	printf("           1 -> PPP\n");
	printf("           2 -> SBAS\n");
	printf("           3 -> DGNSS\n");
	printf("        The nominal a priori position is a prerequisite of the processing, and can be specified or read from the RINEX\n");
	printf("        input file. See the option '-pre:setrecpos' in the help ('-help') for more details.\n");
	printf("        Sample:\n");
	printf("            OUTPUT    2006 200   300.00    2.6219   4849203.1236   -360328.5229   4114913.9535     0.7693     0.4145     0.7580     1.9353     0.6998     1.6246   40.429162956   -4.249653155  830.480629026     0.0993     0.4704     1.0522     1.1365     0.6772     2.2637     0.9572     12.2743     5.0975     7.2205     3.5866     3.0880     0.0097     0.4995 6 1\n\n");
	printf("    SBASCORR [SBAS processing mode]\n");
	printf("        SBAS corrections breakdown. It is shown when a model can be fully computed using SBAS corrections for GPS C1C measurement.\n");
	printf("        Field 1:   'SBASCORR' (if it is used in computation) or 'SBASCORR*' (if it is not)\n");
	printf("        Field 2:   Receiver id\n");
	printf("        Field 3:   SBAS processing mode (PA or NPA)\n");
	printf("        Field 4:   GNSS System (GPS, GAL, GLO or GEO)\n");
	printf("        Field 5:   PRN satellite identifier\n");
	printf("        Field 6:   Year\n");
	printf("        Field 7:   Doy\n");
	printf("        Field 8:   Seconds of day\n");
	printf("        Field 9:   GPS week\n");
	printf("        Field 10:  Time of week\n");
	printf("        Field 11:  GEO PRN from which SBAS corrections are used ('0' means all GEOs)\n");
	printf("        Field 12:  Measurement-model value (prefit) [m]\n");
	printf("        Field 13:  Measurement value without smoothing [m]\n");
	printf("        Field 14:  Measurement value with smoothing [m]\n");
	printf("        Field 15:  Satellite-receiver geometric distance (with SBAS corrections) [m]\n");
	printf("        Field 16:  Relativity correction (with SBAS corrections) [m]\n");
	printf("        Field 17:  Satellite clock correction (with SBAS corrections) [m]\n");
	printf("        Field 18:  Total Group Delay (TGD) correction [m]\n");
	printf("        Field 19:  Ionosphere pierce point latitude [-90..90 degrees]\n");
	printf("        Field 20:  Ionosphere pierce point longitude [0..360 degrees]\n");
	printf("        Field 21:  Ionosphere correction [m]\n");
	printf("        Field 22:  Troposphere nominal correction [m]\n");
	printf("        Field 23:  PRC (fast correction) applied to the satellite [m]\n");
	printf("        Field 24:  RRC (range-rate correction) applied to the satellite [m]\n");
	printf("        Field 25:  Fast correction degradation factor [m/s^2]\n");
	printf("        Field 26:  PRC time out [s]\n");
	printf("        Field 27:  RRC time out (smallest PRC time out for all satellites) [s]\n");
	printf("        Field 28:  Time (seconds of day) used for computing PRC timeout\n");
	printf("        Field 29:  Time (seconds of day) used for computing sigma UDRE (User Differential Range Error) timeout\n");
	printf("        Field 30:  Time (seconds of day) used for computing fast correction degradation\n");
	printf("        Field 31:  X component of the satellite position in WGS84 system at emission time with SBAS corrections [m]\n");
	printf("        Field 32:  Y component of the satellite position in WGS84 system at emission time with SBAS corrections [m]\n");
	printf("        Field 33:  Z component of the satellite position in WGS84 system at emission time with SBAS corrections [m]\n");
	printf("        Field 34:  Long term correction to be applied to the X component of the satellite [m]\n");
	printf("        Field 35:  Long term correction to be applied to the Y component of the satellite [m]\n");
	printf("        Field 36:  Long term correction to be applied to the Z component of the satellite [m]\n");
	printf("        Field 37:  Long term correction to be applied to the satellite clock [m]\n");
	printf("        Field 38:  IODP (Issue of Data PRN mask) used for fast corrections\n");
	printf("        Field 39:  IODF (Issue of Data Fast Correction) in messages type 2-5,24 for fast corrections\n");
	printf("        Field 40:  Satellite slot in the fast correction mask [1..51]\n");
	printf("        Field 41:  IODP used for long term corrections\n");
	printf("        Field 42:  Satellite slot in the long term correction mask [1..51]\n");
	printf("        Field 43:  IODE (Issue of Data Ephemeris) used for broadcast ephemeris\n");
	printf("        Field 44:  IODS (Service Issue of Data) used for service message\n");
	printf("        Field 45:  IODP used for covariance matrix\n");
	printf("        Field 46:  Satellite slot in the covariance mask [1..51]\n");
	printf("        Field 47:  Ionosphere model flag\n");
	printf("        Field 48:  Satellite elevation [degrees]\n");
	printf("        Field 49:  Satellite azimuth [degrees]\n\n");
	printf("        When the '*' appears in field 1, it is due to smoothed code of the satellite has not reached steady-state, a SBAS processing mode switch\n");
	printf("         or SBAS GEO switch. When a mode or GEO switch occurs, the SBAS corrections have to be computed again.\n");
	printf("        Field 43 is the IODE value from the broadcast message matched with the SBAS long term corrections. If the field value is negative,\n");
	printf("        it means that the IODE used does not match any SBAS long term correction messagea available (only in NPA mode). A value of 999 means\n");
	printf("        that no valid broadcast message was found for the current epoch.\n");
	printf("        Field 47 is a flag to indicate which ionosphere model is used. Its possible values are '-1' for no ionosphere model,\n");
	printf("         '0' for SBAS ionosphere model, '1' for Klobuchar ionosphere model and '2' for any other ionosphere model\n");
	printf("        Sample:\n");
	printf("            SBASCORR    vigo  PA GPS  23 2015 165  5088.00 1849   5088.00 120     60577.5787  20948474.4600  20948474.4600  20853522.4567        -4.3086     34379.4657        -6.0029        42.7112        -7.1281         2.3087         2.7117        -0.2500         0.0000 0.00580        12.0000        12.0000  5084.1  5084.1  5084.1  17496575.5944 5306168.63534 19563205.09708  -1.00000   0.62500   0.12500   0.69801  0  1 22  0 22  99  0 -1 -1  0   65.512   66.455\n\n");
	printf("    SBASVAR [SBAS processing mode]\n");
	printf("        SBAS variance contributions breakdown. It is shown when a model can be fully computed using SBAS corrections for GPS C1C measurement.\n");
	printf("        Field 1:   'SBASVAR' (if it is used in computation) or 'SBASVAR*' (if it is not)\n");
	printf("        Field 2:   Receiver id\n");
	printf("        Field 3:   SBAS processing mode (PA or NPA)\n");
	printf("        Field 4:   GNSS System (GPS, GAL, GLO or GEO)\n");
	printf("        Field 5:   PRN satellite identifier\n");
	printf("        Field 6:   Year\n");
	printf("        Field 7:   Doy\n");
	printf("        Field 8:   Seconds of day\n");
	printf("        Field 9:   GPS week\n");
	printf("        Field 10:  Time of week\n");
	printf("        Field 11:  GEO PRN from which SBAS corrections are used ('0' means all GEOs)\n");
	printf("        Field 12:  Sigma of the total residual error associated to the satellite [m]\n");
	printf("        Field 13:  Sigma of the residual error associated to the fast and long-term corrections [m]\n");
	printf("        Field 14:  Sigma of the UDRE [m]\n");
	printf("        Field 15:  Delta UDRE (User Differential Range Error) factor\n");
	printf("        Field 16:  Data source (SBAS message type number) for Delta UDRE\n");
	printf("        Field 17:  Degradation parameter for fast correction data [m]\n");
	printf("        Field 18:  Degradation parameter for range rate correction data [m]\n");
	printf("        Field 19:  Degradation parameter for long term correction data or GEO navigation message data [m]\n");
	printf("        Field 20:  Degradation parameter for en route through NPA applications [m]\n");
	printf("        Field 21:  RSS (Root-Sum-Square) flag in message type 10\n");
	printf("        Field 22:  Sigma of the residual error associated to the ionosheric corrections [m]\n");
	printf("        Field 23:  Sigma of the residual error associated to the tropospheric corrections [m]\n");
	printf("        Field 24:  Sigma of the total receiver error [m]\n");
	printf("        Field 25:  Sigma of the receiver noise [m]\n");
	printf("        Field 26:  Sigma of the receiver multipath [m]\n");
	printf("        Field 27:  Sigma of the receiver divergence [m]\n");
	printf("        Field 28:  Satellite elevation [degrees]\n");
	printf("        Field 29:  Satellite azimuth [degrees]\n\n");
	printf("        The data source indicator for Delta UDRE in field 16 may have the following values:\n"); 
	printf("          27 or 28 for their respective message type,\n");
	printf("          -27 or -28 if received any of these message types but there was missing data for current satellite or was timed out,\n");
	printf("          0 if no message type received or both received.\n");
	printf("        When the '*' appears in field 1, it is due to smoothed code of the satellite has not reached steady-state, a SBAS processing mode switch\n");
	printf("         or SBAS GEO switch. When a mode or GEO switch occurs, the SBAS corrections have to be computed again.\n");
	printf("        Sample:\n");
	printf("            SBASVAR     vigo  PA GPS  23 2015 165  5088.00 1849   5088.00 120         1.4270         1.0975         0.9119    1.000  27         0.1856         0.0000         0.0000         0.0000 0         0.8173         0.1318         0.3830    0.360    0.131    0.000   65.512   66.455\n\n");
	printf("    SBASIONO [SBAS processing mode]\n");
	printf("        SBAS ionosphere breakdown. It is shown when SBAS ionosphere can be computed.\n");
	printf("        Field 1:   'SBASIONO' (if it is used in computation) or 'SBASIONO*' (if it is not)\n");
	printf("        Field 2:   Receiver id\n");
	printf("        Field 3:   SBAS processing mode (PA or NPA)\n");
	printf("        Field 4:   GNSS System (GPS, GAL, GLO or GEO)\n");
	printf("        Field 5:   PRN satellite identifier\n");
	printf("        Field 6:   Year\n");
	printf("        Field 7:   Doy\n");
	printf("        Field 8:   Seconds of day\n");
	printf("        Field 9:   GPS week\n");
	printf("        Field 10:  Time of week\n");
	printf("        Field 11:  GEO PRN from which SBAS corrections are used ('0' means all GEOs)\n");
	printf("        Field 12:  Ionosphere pierce point latitude [-90..90 degrees]\n");
	printf("        Field 13:  Ionosphere pierce point longitude [0..360 degrees]\n");
	printf("        Field 14:  Interpolation mode. 0 for square interpolation, [1-4] indicates the vertex not used in triangle interpolation\n");
	printf("        Field 15:  IODI (Issue of Data Ionospheric) for vertex 1\n");
	printf("        Field 16:  Band Number for vertex 1\n");
	printf("        Field 17:  IGP Number for vertex 1\n");
	printf("        Field 18:  Time of reception of last bit of vertex 1 IGP [seconds of day]\n");
	printf("        Field 19:  Latitude of the IGP for vertex 1 [-90..90 degrees]\n");
	printf("        Field 20:  Longitude of the IGP for vertex 1 [0..360 degrees]\n");
	printf("        Field 21:  Ionosphere delay (raw value from MT26) for vertex 1 [L1 m]\n");
	printf("        Field 22:  Ionosphere variance (raw value from MT26) for vertex 1 [L1 m^2]\n");
	printf("        Field 23:  Degradation term for vertex 1 [L1 m]\n");
	printf("        Field 24:  Ionosphere delay after interpolation (if required) for vertex 1 [L1 m]\n");
	printf("        Field 25:  Ionosphere variance after applying degradation and interpolation (if required) for vertex 1 [L1 m^2]\n");
	printf("        Field 26:  Interpolation weight for vertex 1\n");
	printf("        Field 27:  IODI for vertex 2\n");
	printf("        Field 28:  Band Number for vertex 2\n");
	printf("        Field 29:  IGP Number for vertex 2\n");
	printf("        Field 30:  Time of reception of last bit of vertex 2 IGP [seconds of day]\n");
	printf("        Field 31:  Latitude of the IGP for vertex 2 [-90..90 degrees]\n");
	printf("        Field 32:  Longitude of the IGP for vertex 2 [0..360 degrees]\n");
	printf("        Field 33:  Ionosphere delay (raw value from MT26) for vertex 2 [L1 m]\n");
	printf("        Field 34:  Ionosphere variance (raw value from MT26) for vertex 2 [L1 m^2]\n");
	printf("        Field 35:  Degradation term for vertex 2 [L1 m]\n");
	printf("        Field 36:  Ionosphere delay after interpolation (if required) for vertex 2 [L1 m]\n");
	printf("        Field 37:  Ionosphere variance after applying degradation and interpolation (if required) for vertex 2 [L1 m^2]\n");
	printf("        Field 38:  Interpolation weight for vertex 2\n");
	printf("        Field 39:  IODI for vertex 3\n");
	printf("        Field 40:  Band Number for vertex 3\n");
	printf("        Field 41:  IGP Number for vertex 3\n");
	printf("        Field 42:  Time of reception of last bit of vertex 3 IGP [seconds of day]\n");
	printf("        Field 43:  Latitude of the IGP for vertex 3 [-90..90 degrees]\n");
	printf("        Field 44:  Longitude of the IGP for vertex 3 [0..360 degrees]\n");
	printf("        Field 45:  Ionosphere delay (raw value from MT26) for vertex 3 [L1 m]\n");
	printf("        Field 46:  Ionosphere variance (raw value from MT26) for vertex 3 [L1 m^2]\n");
	printf("        Field 47:  Degradation term for vertex 3 [L1 m]\n");
	printf("        Field 48:  Ionosphere delay after interpolation (if required) for vertex 3 [L1 m]\n");
	printf("        Field 49:  Ionosphere variance after applying degradation and interpolation (if required) for vertex 3 [L1 m^2]\n");
	printf("        Field 50:  Interpolation weight for vertex 3\n");
	printf("        Field 51:  IODI for vertex 4\n");
	printf("        Field 52:  Band Number for vertex 4\n");
	printf("        Field 53:  IGP Number for vertex 4\n");
	printf("        Field 54:  Time of reception of last bit of vertex 4 IGP [seconds of day]\n");
	printf("        Field 55:  Latitude of the IGP for vertex 4 [-90..90 degrees]\n");
	printf("        Field 56:  Longitude of the IGP for vertex 4 [0..360 degrees]\n");
	printf("        Field 57:  Ionosphere delay (raw value from MT26) for vertex 4 [L1 m]\n");
	printf("        Field 58:  Ionosphere variance (raw value from MT26) for vertex 4 [L1 m^2]\n");
	printf("        Field 59:  Degradation term for vertex 4 [L1 m]\n");
	printf("        Field 60:  Ionosphere delay after interpolation (if required) for vertex 4 [L1 m]\n");
	printf("        Field 61:  Ionosphere variance after applying degradation and interpolation (if required) for vertex 4 [L1 m^2]\n");
	printf("        Field 62:  Interpolation weight for vertex 4\n");
	printf("        Field 63:  Mapping function\n");
	printf("        Field 64:  Slant delay [L1 m]\n");
	printf("        Field 65:  Slant Sigma [L1 m]\n");
	printf("        Field 66:  Satellite elevation [degrees]\n");
	printf("        Field 67:  Satellite azimuth [degrees]\n\n");
	printf("        Vertex 1 is the IGP north east to IPP, vertex 2 is the IGP north west to IPP, vertex 3 is the IGP south west to IPP,\n");
	printf("        vertex 4 is the IGP south east to IPP. This order is shown in the following figure:\n");
	printf("                            NORTH\n");
	printf("                      v2..............v1\n");
	printf("                      .               .\n");
	printf("                      .               .\n");
	printf("                      .               .\n");
	printf("           WEST       .    IPP        .       EAST\n");
	printf("                      .     *         .\n");
	printf("                      .               .\n");
	printf("                      .               .\n");
	printf("                      v3..............v4\n");
	printf("                            SOUTH\n");
	printf("        When the '*' appears in field 1, it is due to smoothed code of the satellite has not reached steady-state, a SBAS processing mode switch\n");
	printf("         or SBAS GEO switch. When a mode or GEO switch occurs, the SBAS corrections have to be computed again.\n");
	printf("        Sample:\n");
	printf("            SBASIONO    vigo  PA GPS  23 2015 165  5088.00 1849   5088.00 120   42.711  352.872 0 0  4  98  4899.1  45 355  2.000   0.5322  0.000   2.0000   0.5322 0.3114 0  4  73  4963.1  45 350  2.000   0.6735  0.000   2.0000   0.6735 0.2308 0  4  72  4963.1  40 350  2.125   0.5322  0.000   2.1250   0.5322 0.1948 0  4  97  4899.1  40 355  2.375   0.5322  0.000   2.3750   0.5322 0.2629   1.0875   2.3087   0.8173 65.51 66.46\n\n");
	printf("    SBASUNSEL [SBAS processing mode]\n");
	printf("        SBAS satellite unselection message. When a satellite is discarded due to MOPS criteria, this message details the reason.\n");
	printf("        Field 1:   'SBASUNSEL' (if it is the definitive reason for discarding) or 'SBASUNSEL*' (if there has been a GEO or mode switch or not reached smoothed code steady-state operation)\n");
	printf("        Field 2:   Receiver id\n");
	printf("        Field 3:   SBAS processing mode (PA or NPA)\n");
	printf("        Field 4:   GNSS System (GPS, GAL, GLO or GEO)\n");
	printf("        Field 5:   PRN satellite identifier\n");
	printf("        Field 6:   Year\n");
	printf("        Field 7:   Doy\n");
	printf("        Field 8:   Seconds of day\n");
	printf("        Field 9:   GPS week\n");
	printf("        Field 10:  Time of week\n");
	printf("        Field 11:  GEO PRN from which SBAS corrections are used ('0' means all GEOs)\n");
	printf("        Field 12:  Error code\n");
	printf("        Field 13:  \"Discard reason\"\n");
	printf("        The error code in field 12 is a number which identifies the discard reason with a range from 1 to 48. Useful for parsing purposes.\n");
	printf("        Field 13 will be always between quotes in order to ease parsing purposes.\n");
	printf("        Fields 12 and 13 may have the following values:\n");
	printf("          1    \"No GEO satellites available\"\n");
	printf("          2    \"No data for user selected GEO\"\n");
	printf("          3    \"Not enough almanac or GEO navigation message to determine the GEO with highest elevation\n");
	printf("          4    \"Received alarm message for current GEO at epoch <YYYY DoY SoD>. Time remaining to finish alarm: <seconds> seconds\n");
	printf("          5    \"Received <value> consecutive messages with errors (UDREI data has been forced to timeout) [PA only]\n");
	printf("          6    \"Missed <value> consecutive messages\n");
	printf("          7    \"No PRN mask\"\n");
	printf("          8    \"PRN mask timed out\"\n");
	printf("          9    \"Satellite is not monitored in any of the PRN mask available\"\n");
	printf("          10   \"No message type 10 available [PA only]\"\n");
	printf("          11   \"Message type 10 timed out [PA only]\"\n");
	printf("          12   \"No fast correction data received for current PRN [PA only]\"\n");
	printf("          13   \"Sigma UDRE timed out [PA only]\"\n");
	printf("          14   \"Satellite flagged as 'Not monitored' (UDREI=14)\"\n");
	printf("          15   \"Satellite flagged as 'Do not use' (UDREI=15)\"\n");
	printf("          16   \"Satellite has an UDREI value of <value> [PA only]\n");
	printf("          17   \"No fast correction degradation data [PA only]\"\n");
	printf("          18   \"Fast correction degradation data timed out [PA only]\"\n");
	printf("          19   \"Last PRC received timed out [PA only]\"\n");
	printf("          20   \"Only one PRC received. RRC calculation not possible [PA only]\"\n");
	printf("          21   \"RRC timed out (under alarm condition) due to time difference between PRC used [PA only]\"\n");
	printf("          22   \"RRC timed out (under alarm condition) due to excessive PRC propagation in time [PA only]\"\n");
	printf("          23   \"RRC timed out due to time difference between PRC used [PA only]\"\n");
	printf("          24   \"RRC timed out due to excessive PRC propagation in time [PA only]\"\n");
	printf("          25   \"Service message timed out [PA only]\"\n");
	printf("          26   \"Not received a full set of service messages with the same IODS [PA only]\"\n");
	printf("          27   \"No clock-ephemeris covariance matrix data for current satellite [PA only]\"\n");
	printf("          28   \"Clock-ephemeris covariance matrix data timed out [PA only]\"\n");
	printf("          29   \"No navigation data for ranging GEO\"\n");
	printf("          30   \"Ranging GEO navigation data timed out\"\n");
	printf("          31   \"URA index value of <value> for ranging GEO satellite\"\n");
	printf("          32   \"No long term correction data for current satellite [PA only]\"\n");
	printf("          33   \"Long term correction data timed out [PA only]\"\n");
	printf("          34   \"No broadcast block with IOD <value> [PA only]\"\n");
	printf("          35   \"No broadcast block available for current satellite (regardless of SBAS IOD) [NPA only]\"\n");
	printf("          36   \"Could not compute transmission time for current PRN measurement\"\n");
	printf("          37   \"No ionospheric grid mask [PA only]\"\n");
	printf("          38   \"Ionospheric grid mask timed out [PA only]\"\n");
	printf("          39   \"IGPs around ionospheric pierce point not found in MOPS grid [PA only]\"\n");
	printf("          40   \"Not enough IGPs available in ionospheric grid mask [PA only]\"\n");
	printf("          41   \"One IGP is set as don't use [PA only]\"\n");
	printf("          42   \"One or more IGPs is set as not monitored or has timed out [PA only]\"\n");
	printf("          43   \"Data not available for one or more IGPs [PA only]\"\n");
	printf("          44   \"Ionospheric pierce point is outside triangle [PA only]\"\n");
	printf("          45   \"External ionosphere model not available\"\n");
	printf("          46   \"Satellite is not in view (elevation <value> degrees)\"\n");
	printf("          47   \"Satellite elevation (<value> degrees) is too low\"\n");
	printf("          48   \"Satellite has an UDREI value of <value> (user threshold is <value>)\"\n\n");
	printf("        Error code number 45 will only appear if user has selected another ionosphere model for SBAS processing\n");
	printf("        Error codes number 46 and 47 will only appear in SBAS plots mode\n");
	printf("        Sample:\n");
	printf("            SBASUNSEL   vigo  PA  31 2015 165   397.00 1849    397.00 120 16 \"Satellite has an UDREI value of 12 [PA only]\"\n\n");
	printf("    SBASOUT [SBAS processing mode]\n");
	printf("        Receiver solution message. This message provides the estimated receiver position, protection levels\n");
	printf("        and satellites used in solution computation.\n");
	printf("        Field 1:   'SBASOUT'\n");
	printf("        Field 2:   Receiver id\n");
	printf("        Field 3:   SBAS processing mode (PA or NPA)\n");
	printf("        Field 4:   Year\n");
	printf("        Field 5:   Doy\n");
	printf("        Field 6:   Seconds of day\n");
	printf("        Field 7:   GPS week\n");
	printf("        Field 8:   Time of week\n");
	printf("        Field 9:   GEO PRN from which SBAS corrections are used ('0' means all GEOs)\n");
	printf("        Field 10:  Receiver North difference in relation to nominal a priori position [m]\n");
	printf("        Field 11:  Receiver East difference in relation to nominal a priori position [m]\n");
	printf("        Field 12:  Receiver Up difference in relation to nominal a priori position [m]\n");
	printf("        Field 13:  Horizontal positioning error [m]\n");
	printf("        Field 14:  Horizontal protection level [m]\n");
	printf("        Field 15:  Vertical positioning error [m]\n");
	printf("        Field 16:  Vertical protection level [m]\n");
	printf("        Field 17:  Receiver clock offset [m]\n");
	printf("        Field 18:  Number of satellites in view suitable for SBAS\n");
	printf("        Field 19:  Number of satellites used in SBAS solution computation\n");
	printf("        Field 20-: Satellite list. Each following column is a '+' or '-' sign, the satellite system and the PRN identifier.\n");
	printf("                   The '+' sign indicates that the satellite has been used in the solution computation for SBAS.\n");
	printf("                   The '-' sign indicates that the satellite has not been used in the solution computation for SBAS.\n");
	printf("                   The satellite list will show first all the satellite with the '+' and after the ones with the '-' sign.\n");
	printf("        Sample:\n");
	printf("            SBASOUT     vigo  PA 2015 165   386.00 1849    386.00 120         0.3565         1.0723        -0.3439         1.1300        20.9835        21.8638    -94936.8124 11 10 +G23 +G17 +G01 +G04 +G10 +G11 +G03 +G06 +G31 +G32 -G09\n");
	printf("\n    SUMMARY\n");
	printf("          The processing summary is printed at the end of the output file if the summary option is enabled\n");
	printf("          The contents of the summary are:\n\n"); 
	printf("             Number of epochs processed, along with the number epochs that had a solution.\n");
	printf("             Number of epochs skipped (epochs without solution).\n");
	printf("             The epoch with highest errors and the epoch were it ocurred.\n");
	printf("             The 95 Percentile (or user defined percentile) of the errors.\n");
	printf("             A single line at the end with the previous info in columnar format. This is line is useful for doing plots.\n"); 
	printf("          Additionally, for SBAS processing, the following information is provided:\n");
	printf("             Number of epochs with solution under alarm limits.\n"); 
	printf("             Number of epochs with MIs.\n"); 
	printf("             The Worst Integrity Ratio (WIR) and the epoch were it ocurred.\n"); 
	printf("             The epoch with highest protection levels and the epoch were it ocurred.\n"); 
	printf("             The 95 Percentile (or user defined percentile) of the protection levels.\n"); 
	printf("\n    SPP/PPP SUMMARY [SPP or PPP processing modes]\n");
    printf("        SPP or PPP statiscal summary. It is printed at the end of the output file if summary is enabled.\n");
    printf("        Sample:\n");
    printf("          INFO --------------------- SPP/PPP Summary ---------------------\n");
    printf("          INFO GDOP Threshold: 100.00\n");
	printf("          INFO First epoch of summary: 27/10/2016 00:00:00.00 / 2016 301     0.00 / 1920 345600.00\n");
	printf("          INFO Last  epoch of summary: 27/10/2016 23:59:59.00 / 2016 301 86399.00 / 1920 431999.00\n");
    printf("          INFO Total epochs processed: 86293\n");
    printf("          INFO Total epochs processed with solution: 85932 ( 99.582%% )\n");
	printf("          INFO Total epochs processed with solution and position from reference file: 85932 ( 99.582%% )\n");
	printf("          INFO Total epochs omitted in summary due to no position from reference file: 0 ( 0.000%% )\n");
	printf("          INFO Total epochs skipped due to no position from reference file for modelling: 0 ( 0.000%% )\n");
    printf("          INFO Total epochs skipped due to less than 4 valid satellites available: 361 ( 0.418%% )\n");
    printf("          INFO Total epochs skipped due to singular geometry matrix: 0 ( 0.000%% )\n");
    printf("          INFO Total epochs skipped due to GDOP exceeding the threshold: 0 ( 0.000%% )\n");
    printf("          INFO Total epochs skipped (any reason): 361 ( 0.418%% )\n");
	printf("          INFO First epoch of summary for computing percentiles: 27/10/2016 00:00:00.00 / 2016 301     0.00 / 1920 345600.00\n");
	printf("          INFO Last  epoch of summary for computing percentiles: 27/10/2016 23:59:59.00 / 2016 301 86399.00 / 1920 431999.00\n");
    printf("          INFO Total samples in Stanford-ESA processed: 111056799\n");
    printf("          INFO Total samples in Stanford-ESA processed with solution: 111056798 ( 99.999%% )\n");
    printf("          INFO Total samples in Stanford-ESA skipped due to singular geometry matrix: 1 ( 9.004E-07%% )\n");
    printf("          INFO Horizontal  95 Positioning Error Percentile:   0.80 metres\n");
    printf("          INFO Vertical    95 Positioning Error Percentile:   1.73 metres\n");
    printf("          INFO Maximum Horizontal Positioning Error: 4.26 metres at epoch 27/10/2016 17:40:32.00 / 2016 301 63632.00 / 1920 409232.00\n");
    printf("          INFO Maximum Vertical   Positioning Error: 7.53 metres at epoch 27/10/2016 17:40:32.00 / 2016 301 63632.00 / 1920 409232.00\n");
    printf("          INFO Station: helg Lon:   7.89309376 Lat:   54.17448223 Height:   48.4689 HPE_Percentile:  95   0.80 VPE_Percentile:  95   1.73 MaxHPE:   0.00 MaxVPE:   0.00 Avail%%:   0.000\n");
    printf("        NOTES:\n");
    printf("          If observation file starts at 22 hours or later, gLAB will automatically assume that all the epochs until the start of the next day (midnight)\n");
    printf("            are for convergence time. During this convergence time, all the epochs computed will not be taken into account for the summary and\n");
    printf("            the Stanford-ESA computation will be skipped. This behaviour can be disabled with the parameter '--summary:waitfordaystart'.\n");
	printf("          If receiver position is not fixed or provided by a reference file, the percentile lines will not appear.\n");
	printf("          If user provides a reference file for comparing the solution and if at a certain epoch the reference file position is not available,\n");
	printf("            the epoch will be skipped from the summary.\n");
    printf("          The last line of the summary contains all the values of the previous lines along with the station coordinates.\n");
	printf("          If receiver position is not fixed, the station coordinates will be the solution from the last computed epoch.\n");
    printf("          The last line is useful for plotting world maps with data from each station.\n");
    printf("          Stanford-ESA messages will not appear if Stanford-ESA computation has not been enabled.\n");
    printf("          GDOP messages will not appear if GDOP threshold has not been enabled.\n");
	printf("          The lines referring to a reference file will only appear if a user sets a reference file. If user sets the reference file just for comparing\n");
	printf("            the solution, the line \"Total epochs omitted in ...\" will appear. Otherwise, if the reference file was set to be used as the a priori\n");
	printf("            position for the modelling computation, the line \"Total epochs skipped due to no position from reference file ...\" will appear.\n");
	printf("\n    SBAS SUMMARY [SBAS processing mode]\n");
	printf("        SBAS statiscal summary. It is printed at the end of the output file if summary is enabled.\n");
	printf("        Sample:\n");
	printf("          INFO --------------------- SBAS Summary ---------------------\n");
	printf("          INFO Horizontal Alarm limit:  40.00\n");
	printf("          INFO Vertical   Alarm limit:  50.00\n");
	printf("          INFO GDOP Threshold: 100.00\n");
	printf("          INFO First epoch of summary: 27/10/2016 00:00:00.00 / 2016 301     0.00 / 1920 345600.00\n");
	printf("          INFO Last  epoch of summary: 27/10/2016 23:59:59.00 / 2016 301 86399.00 / 1920 431999.00\n");
	printf("          INFO Total epochs processed: 86293\n");
	printf("          INFO Total epochs processed with PA solution: 85932 ( 99.582%% )\n");
	printf("          INFO Total epochs processed with PA solution under alarm limits: 85932 ( 99.582%% )\n");
	printf("          INFO Total epochs processed with PA solution and position from reference file: 0 ( 0.000%% )\n");
	printf("          INFO Total epochs processed with NPA solution: 0 ( 0.000%% )\n");
	printf("          INFO Total epochs omitted in summary due to no position from reference file: 0 ( 0.000%% )\n");
	printf("          INFO Total epochs skipped due to no position from reference file for modelling: 0 ( 0.000%% )\n");
	printf("          INFO Total epochs skipped due to less than 4 valid satellites available: 361 ( 0.418%% )\n");
	printf("          INFO Total epochs skipped due to singular geometry matrix: 0 ( 0.000%% )\n");
	printf("          INFO Total epochs skipped due to GDOP exceeding the threshold: 0 ( 0.000%% )\n");
    printf("          INFO Total epochs skipped (any reason): 361 ( 0.418%% )\n");
	printf("          INFO Continuity Risk (15 epochs sliding window): 1.7456E-04\n");
	printf("          INFO First epoch of summary for computing MIs and percentiles: 27/10/2016 00:00:00.00 / 2016 301     0.00 / 1920 345600.00\n");
	printf("          INFO Last  epoch of summary for computing MIs and percentiles: 27/10/2016 23:59:59.00 / 2016 301 86399.00 / 1920 431999.00\n");
	printf("          INFO Total epochs with MIs: 0 ( 0.000%% )\n");
	printf("          INFO Total epochs with Horizontal MIs: 0 ( 0.000%% )\n");
	printf("          INFO Total epochs with Vertical   MIs: 0 ( 0.000%% )\n");
	printf("          INFO Total samples in Stanford-ESA processed: 111056799\n");
	printf("          INFO Total samples in Stanford-ESA processed with solution: 111056798 ( 99.999%% )\n");
	printf("          INFO Total samples in Stanford-ESA skipped due to singular geometry matrix: 1 ( 9.004E-07%% )\n");
	printf("          INFO Total samples in Stanford-ESA with MIs: 219 ( 1.972E-04%% )\n");
	printf("          INFO Total samples in Stanford-ESA with Horizontal MIs: 157 ( 1.414E-04%% )\n");
	printf("          INFO Total samples in Stanford-ESA with Vertical   MIs: 139 ( 1.252E-04%% )\n");
	printf("          INFO Stanford-ESA Worst Horizontal Integrity Ratio: 1.6777\n");
	printf("          INFO Stanford-ESA Worst Vertical   Integrity Ratio: 1.9140\n");
	printf("          INFO Horizontal  95 Positioning Error Percentile:   0.80 metres\n");
	printf("          INFO Vertical    95 Positioning Error Percentile:   1.73 metres\n");
	printf("          INFO Horizontal  95 Protection  Level Percentile:  10.27 metres\n");
	printf("          INFO Vertical    95 Protection  Level Percentile:  16.50 metres\n");
    printf("          INFO Maximum Horizontal Positioning Error:   4.26 metres at epoch 27/10/2016 17:40:32.00 / 2016 301 63632.00 / 1920 409232.00\n");
    printf("          INFO Maximum Vertical   Positioning Error:   7.53 metres at epoch 27/10/2016 17:40:32.00 / 2016 301 63632.00 / 1920 409232.00\n");
    printf("          INFO Maximum Horizontal Protection  Level:  16.21 metres at epoch 27/10/2016 17:40:32.00 / 2016 301 63632.00 / 1920 409232.00\n");
    printf("          INFO Maximum Vertical   Protection  Level:  23.92 metres at epoch 27/10/2016 17:40:32.00 / 2016 301 63632.00 / 1920 409232.00\n");
	printf("          INFO Worst Horizontal Integrity Ratio: 0.5317 at epoch 27/10/2016 17:40:32.00 / 2016 301 63632.00 / 1920 409232.00\n");
	printf("          INFO Worst Vertical   Integrity Ratio: 0.4763 at epoch 27/10/2016 17:40:32.00 / 2016 301 63632.00 / 1920 409232.00\n");
	printf("          INFO Station: helg Lon:   7.89309376 Lat:   54.17448223 Height:   48.4689 HWIR:  0.5317 VWIR:  0.4763 MIs:   0 Hor_MIs:   0 Ver_MIs:   0 HPE_Percentile:  95   0.80 VPE_Percentile:  95   1.73 MaxHPE:   4.26 MaxVPE:   7.53 HPL_Percentile:  95  10.27 VPL_Percentile:  95  16.50 MaxHPL:  16.21 MaxVPL:  23.92 Avail%%:  99.582 Cont_Risk: 1.7456E-04 HWIR_ESA:  1.6777 VWIR_ESA:  1.9140 MIs_ESA:  219 Hor_MIs_ESA:  157 Ver_MIs_ESA:  139\n\n");
	printf("        NOTES:\n");
	printf("          If observation file starts at 22 hours or later, gLAB will automatically assume that all the epochs until the start of the next day (midnight\n");
	printf("          	are for convergence time. During this convergence time, all the epochs computed will not be taken into account for the SBAS summary and\n");
	printf("          	the Stanford-ESA computation will be skipped. This behaviour can be disabled with the parameter '--sbassummary:waitfordaystart'.\n");
	printf("          If receiver position is not fixed or provided by a reference file, the percentile lines will not appear.\n");
	printf("          If user provides a reference file for comparing the solution and if at a certain epoch the reference file position is not available,\n");
	printf("            the epoch will be skipped from the summary.\n");
	printf("          The last line of the SBAS summary contains all the values of the previous lines along with the station coordinates.\n");
	printf("          If receiver position is not fixed, the station coordinates will be the solution from the last computed epoch.\n");
	printf("          The last line is useful for plotting world maps with data from each station.\n");
	printf("          The fields at the end of the last line 'HWIR_ESA', 'VWIR_ESA', 'MIs_ESA', 'Hor_MIs_ESA' and 'Ver_MIs_ESA' correspond to the values computed in Stanford-ESA.\n");
	printf("            These fields will appear even if Stanford-ESA has not been enabled, but with a value of 0 (so its column number is fixed).\n");
	printf("          Stanford-ESA messages will not appear if Stanford-ESA computation has not been enabled.\n");
	printf("          GDOP messages will not appear if GDOP threshold has not been enabled.\n\n");
	printf("          Number of epochs with NPA epoch message will not appear if mode switching has not been enabled.\n\n");
	printf("          If user forced NPA processing through parameters, then all values in SBAS summary will be referred to NPA mode.\n");
	printf("          The lines referring to a reference file will only appear if a user sets a reference file. If user sets the reference file just for comparing\n");
	printf("            the solution, the line \"Total epochs omitted in ...\" will appear. Otherwise, if the reference file was set to be used as the a priori\n");
	printf("            position for the modelling computation, the line \"Total epochs skipped due to no position from reference file ...\" will appear.\n");
    printf("\n    DGNSS SUMMARY [DGNSS processing mode]\n");
    printf("        DGNSS statiscal summary. It is printed at the end of the output file if summary is enabled.\n");
    printf("        Sample:\n");
    printf("          INFO --------------------- DGNSS Summary ---------------------\n");
    printf("          INFO GDOP Threshold: 100.00\n");
	printf("          INFO First epoch of summary: 27/10/2016 00:00:00.00 / 2016 301     0.00 / 1920 345600.00\n");
	printf("          INFO Last  epoch of summary: 27/10/2016 23:59:59.00 / 2016 301 86399.00 / 1920 431999.00\n");
    printf("          INFO Total epochs processed: 86293\n");
    printf("          INFO Total epochs processed with DGNSS solution: 85932 ( 99.582%% )\n");
    printf("          INFO Total epochs processed with SPP solution: 0 ( 0.000%% )\n");
    printf("          INFO Total epochs processed with DGNSS solution and position from reference file: 85932 ( 99.582%% )\n");
    printf("          INFO Total epochs omitted in summary due to no position from reference file: 0 ( 0.000%% )\n");
    printf("          INFO Total epochs skipped due to less than 4 valid satellites available: 361 ( 0.418%% )\n");
    printf("          INFO Total epochs skipped due to singular geometry matrix: 0 ( 0.000%% )\n");
    printf("          INFO Total epochs skipped due to GDOP exceeding the threshold: 0 ( 0.000%% )\n");
    printf("          INFO Total epochs skipped (any reason): 361 ( 0.418%% )\n");
	printf("          INFO First epoch of summary for computing percentiles: 27/10/2016 00:00:00.00 / 2016 301     0.00 / 1920 345600.00\n");
	printf("          INFO Last  epoch of summary for computing percentiles: 27/10/2016 23:59:59.00 / 2016 301 86399.00 / 1920 431999.00\n");
    printf("          INFO Total samples in Stanford-ESA processed: 111056799\n");
    printf("          INFO Total samples in Stanford-ESA processed with solution: 111056798 ( 99.999%% )\n");
    printf("          INFO Total samples in Stanford-ESA skipped due to singular geometry matrix: 1 ( 9.004E-07%% )\n");
    printf("          INFO Horizontal  95 Positioning Error Percentile:   0.80 metres\n");
    printf("          INFO Vertical    95 Positioning Error Percentile:   1.73 metres\n");
    printf("          INFO Maximum Horizontal Positioning Error: 4.26 metres at epoch 27/10/2016 17:40:32.00 / 2016 301 63632.00 / 1920 409232.00\n");
    printf("          INFO Maximum Vertical   Positioning Error: 7.53 metres at epoch 27/10/2016 17:40:32.00 / 2016 301 63632.00 / 1920 409232.00\n");
    printf("          INFO Rover: helg Lon:   7.89309376 Lat:   54.17448223 Height:   48.4689 HPE_Percentile:  95   0.80 VPE_Percentile:  95   1.73 MaxHPE:   0.00 MaxVPE:   0.00 Avail%%:   0.000\n");
    printf("        NOTES:\n");
    printf("          If observation file starts at 22 hours or later, gLAB will automatically assume that all the epochs until the start of the next day (midnight)\n");
    printf("            are for convergence time. During this convergence time, all the epochs computed will not be taken into account for the summary and\n");
    printf("            the Stanford-ESA computation will be skipped. This behaviour can be disabled with the parameter '--summary:waitfordaystart'.\n");
    printf("          If rover position is not provided, the percentile lines will not appear.\n");
    printf("          If user provides a reference file for comparing the solution and if at a certain epoch the reference file position is not available,\n");
    printf("            the epoch will be skipped from the summary.\n");
    printf("          If rover position is not provided, the station coordinates will be the solution from the last computed epoch.\n");
    printf("          The last line of the summary contains all the values of the previous lines along with the station coordinates.\n");
    printf("          The last line is useful for plotting world maps with data from each station.\n");
    printf("          Stanford-ESA messages will not appear if Stanford-ESA computation has not been enabled.\n");
    printf("          GDOP messages will not appear if GDOP threshold has not been enabled.\n");
    printf("          The lines referring to a reference file will only appear if a user sets a reference file.\n");
	printf("\n    SATDIFF [orbit and clock comparison]\n");
	printf("        Satellite difference message for products comparison mode. This message shows the difference between\n");
	printf("        both orbit and clocks for two different OC products fonts for a specific time. It is shown each time step.\n");
	printf("        The SISRE fields are the Signal-in-Space Range Error, it is a measure of how the error impact a general\n");
	printf("        receiver found in the Earth's surface. It is computed as:\n");
	printf("            SISRE = sqrt((radDiff-clkDiff)^2 + 1/49*(ctDiff^2 + atDiff^2))\n");
	printf("        Being:\n");
	printf("            radDiff, the difference of satellite positions in the radial component\n");
	printf("            clkDiff, the difference of satellite clock offsets\n");
	printf("            ctDiff, the difference of satellite positions in the cross-track component\n");
	printf("            atDiff, the difference of satellite positions in the along-track component\n");
	printf("        Field 1:   'SATDIFF'\n");
	printf("        Field 2:   Year\n");
	printf("        Field 3:   Doy\n");
	printf("        Field 4:   Seconds of day\n");
	printf("        Field 5:   GNSS System (GPS, GAL, GLO or GEO)\n");
	printf("        Field 6:   PRN satellite identifier\n");
	printf("        Field 7:   SISRE difference\n");
	printf("        Field 8:   SISRE orbit-only difference\n");
	printf("        Field 9:   3D orbit difference\n");
	printf("        Field 10:  Clock difference\n");
	printf("        Field 11:  Radial position difference\n");
	printf("        Field 12:  Along-track position difference\n");
	printf("        Field 13:  Cross-track position difference\n");
	printf("        Field 14:  X position difference\n");
	printf("        Field 15:  Y position difference\n");
	printf("        Field 16:  Z position difference\n");
	printf("        Sample:\n");
	printf("            SATDIFF 2006 200     0.00 GPS  1     4.1082     0.5359     1.1019    -3.5883     0.5176     0.5497     0.8025      1.527     0.4156     3.7061\n\n");
	printf("    SATSTAT [orbit and clock comparison]\n");
	printf("        Satellite difference summary message for products comparison mode. This message shows the differences\n");
	printf("        between orbit and clocks for two different OC products fonts for a specific satellite. It is shown after\n");
	printf("        all the comparisons are done, and presents a summary for each satellite.\n");
	printf("        Field 1:      'SATSTAT'\n");
	printf("        Field 2:      GNSS System (GPS, GAL, GLO or GEO)\n");
	printf("        Field 3:      PRN satellite identifier\n");
	printf("        Field 4:      Number of samples\n");
	printf("        Field 5-7:    SISRE comparisons  [mean,RMS,stdDev]\n");
	printf("        Field 8-10:   SISRE orbit-only comparisons  [mean,RMS,stdDev]\n");
	printf("        Field 11-13:  3D orbit comparisons  [mean,RMS,stdDev]\n");
	printf("        Field 14-16:  Clock comparisons  [mean,RMS,stdDev]\n");
	printf("        Field 17-19:  Radial position comparisons  [mean,RMS,stdDev]\n");
	printf("        Field 20-22:  Along-track position comparisons  [mean,RMS,stdDev]\n");
	printf("        Field 23-25:  Cross-track position comparisons  [mean,RMS,stdDev]\n");
	printf("        Sample:\n");
	printf("            SATSTAT  1   95     1.5530     2.1112     1.4302     0.9279     1.0058     0.3881     1.4115     1.4714     0.4155    -0.3357     1.9280     1.8985     0.8988     0.9938     0.4239     0.6081     0.9604     0.7433     0.1717     0.5050     0.4750\n");
	printf("\n    SATSTATTOT [orbit and clock comparison]\n\n");
	printf("        Difference summary message for products comparison mode. This message shows the statistics of the\n");
	printf("        differences between orbit and clocks for two different OC products fonts. It is shown after all the\n");
	printf("        comparisons are done, and presents a summary for all of them.\n");
	printf("        Field 1:      'SATSTATTOT'\n");
	printf("        Field 2:      Number of samples\n");
	printf("        Field 3-5:    SISRE comparisons  [mean,RMS,stdDev]\n");
	printf("        Field 6-8:    SISRE orbit-only comparisons  [mean,RMS,stdDev]\n");
	printf("        Field 9-11:   3D orbit comparisons  [mean,RMS,stdDev]\n");
	printf("        Field 12-14:  Clock comparisons  [mean,RMS,stdDev]\n");
	printf("        Field 15-17:  Radial position comparisons  [mean,RMS,stdDev]\n");
	printf("        Field 18-20:  Along-track position comparisons  [mean,RMS,stdDev]\n");
	printf("        Field 21-23:  Cross-track position comparisons  [mean,RMS,stdDev]\n");
	printf("        Sample:\n");
	printf("            SATSTATTOT 2660     1.2971     1.6206     0.9714     1.0207     1.1478     0.5250     1.6623     1.7701     0.6083    -0.1909     1.3835     1.3702     0.9488     1.1312     0.6160     0.0514     1.1930     1.1918    -0.0345     0.6560     0.6551\n\n");
	printf("    SATPVT [show product mode]\n");
	printf("        Satellite data messages for show product mode. This message show the PVT data for a specific time\n");
	printf("        and satellite.\n");
	printf("        Field 1:      'SATPVT'\n");
	printf("        Field 2:      Year\n");
	printf("        Field 3:      Doy\n");
	printf("        Field 4:      Seconds of day\n");
	printf("        Field 5:      GNSS System (GPS, GAL, GLO or GEO)\n");
	printf("        Field 6:      PRN satellite identifier\n");
	printf("        Field 7:      Satellite X position [m]\n");
	printf("        Field 8:      Satellite Y position [m]\n");
	printf("        Field 9:      Satellite Z position [m]\n");
	printf("        Field 10:     Satellite X velocity [m/s]\n");
	printf("        Field 11:     Satellite Y velocity [m/s]\n");
	printf("        Field 12:     Satellite Z velocity [m/s]\n");
	printf("        Field 13:     Satellite clock offset [m]\n");
	printf("        Sample:\n");
	printf("            SATPVT 2006 199 79500.00 GPS  1  15340446.1662 -20066066.3778  -7929249.6479      1191.6479      2132.5615     -3023.0448     19826.4736\n\n");
	printf("    DGNSS [DGNSS processing mode]\n");
	printf("        DGNSS corrections breakdown. It is shown when a model can be fully computed using DGNSS corrections for GPS C1C measurement.\n");
	printf("        Field 1:      'DGNSS' (if it is used in computation) or 'DGNSS*' (if it is not, switched to SPP due to GDOP)\n");
	printf("        Field 2:      Year\n");
	printf("        Field 3:      Doy [days]\n");
	printf("        Field 4:      Seconds of day [s]\n");
	printf("        Field 5:      GNSS System (GPS, GAL, GLO or GEO)\n");
	printf("        Field 6:      PRN Satellite identifier\n");
	printf("        Field 7:      Pseudorange correction to be applied to the satellite [m]\n");
	printf("        Field 8:      Range rate correction to be applied to the satellite [m]\n");
	printf("        Field 9:      Seconds elapsed since the reception of the RRC correction [s]\n");
	printf("        Field 10:     Delta of PRC to be applied in case of change in case of a change in ephemeris [m]\n");
	printf("        Field 11:     Delta of RRC to be applied in case of change in case of a change in ephemeris [m]\n");
	printf("        Field 12:     Seconds elapsed since the reception of the delta RRC correction [s]\n");
	printf("        Field 13:     Sigma of the total residual error associated to the satellite [m]\n");
	printf("                        Sigma of the total residual error = sigma of the UDRE + sigma degradation + sigma air\n");
	printf("        Field 14:     Sigma of the UDRE (User Differential Range Error) [m]\n");
	printf("        Field 15:     Sigma degradation consists of the URA (User Range Accuracy) degradation factor (we assume epsURA = 1 cm/s), and the satellite elevation. It only applies for RTCM v3.x [m]\n");
	printf("                        Sigma degradation = (epsURA * dt) / tan(satellite elevation)\n");
	printf("        Field 16:     Sigma air consists of the sigma multipath, the sigma to noise GPS (we assume 0.25 m) and the sigma inflation (equal to 1 if deactivated) [m]\n");
	printf("                        Sigma air = ( sigma multipath + sigma to noise GPS ) * sigma inflation\n");
	printf("        Field 17:     Sigma multipath = 0.0625 / tan(elev) / tan(elev)\n");
	printf("        Field 18:     Sigma inflation during the convergence of the smoothing\n");
	printf("        Sample:\n");
	printf("            DGNSS     2016 294  5407.000 GPS  6  -4.1800   0.0000   1.5999   0.0000   0.0000   0.0000   0.6053   0.3000   0.0000   0.5257   0.0264   1.0000\n");
}

/*****************************************************************************
 * Name        : showsigmamultipathfile
 * Description : Shows an example of a sigma multipath configuration file
 * Parameters  : None
 *****************************************************************************/
void showsigmamultipathfile () {

	#if defined _OPENMP
		printf("#gLAB version v%s (with OpenMP multithread), built on %s %s\n",VERSION,__DATE__,__TIME__);
	#else
		printf("#gLAB version v%s, built on %s %s\n",VERSION,__DATE__,__TIME__);
	#endif
	printf("#Lines with comments start with a # at the beginning of line\n");
	printf("#If the symbol # is found in the middle of the line, the rest of the line will be omitted, as it will be considered a comment\n");
	printf("#Empty lines will be skipped\n");
	printf("#This is an example of user multipath model configuration file.\n");
	printf("#This file is for introducing a user defined model for sigma multipath model for a SBAS receiver, which can be elevation or SNR dependent.\n");
	printf("#By executing 'gLAB -sigmamultipathfile > usermultipathfile.txt' a valid user multipath model configuration file is created (this file).\n");
	printf("#\n");
	printf("#The following lines explain the rules for creating this configuration file:\n");
	printf("#First line (non empty or without '#') indicates if the following values are for an elevation or S/N ratio model\n");
	printf("#Values for first line are: 'Elevation' or 'SNR' (values are case insensitive)\n");
	printf("#For example:\n");
	printf("#Elevation\n");
	printf("#SNR\n");
	printf("#\n");
	printf("#Values will be given in the same manner for both cases:\n");
	printf("#For each line, the first column will be either the elevation or the SNR sample, the second column will be the relevant sigma value for the sample.\n");
	printf("#There will be as many lines as the number of available samples.\n");
	printf("#Lines must be sorted from lower to higher range values. If lines are not sorted, gLAB will show an error and exit.\n");
	printf("#The unit for the samples are:\n");
	printf("#  degrees for an elevation dependent model\n");
	printf("#  dBHz for a S/N ratio dependent model\n");
	printf("#The unit for the sigma values are metres\n");
	printf("#Sigma values between intervals will be linearly interpolated\n");
	printf("#If a value to be interpolated is below the minimum sample, the minimum sample value will be used. The same criteria will be used for values over the maximum sample.\n");
	printf("#Range step does not need to be constant.\n");
	printf("#\n");
	printf("#If SNR model is selected and no SNR from RINEX is available, the highest SNR sample will be used.\n");
	printf("#\n");
	printf("#Example for an elevation dependent model:\n");
	printf("#Elevation\n");
	printf("#20   0.7\n");
	printf("#30   0.6\n");
	printf("#40   0.5\n");
	printf("#60   0.3\n");
	printf("#78   0.2\n");
	printf("#80   0.1\n");
	printf("# \n");
	printf("#Example for a SNR dependent model:\n");
	printf("#SNR\n");
	printf("#30     0.6\n");
	printf("#40 0.5\n");
	printf("#56 0.4\n");
	printf("#60 0.3\n");
	printf("#\n");
	printf("#Data columns do not need to have a specific number of spaces between them, as well as leading and trailing spaces at the beginning or end of line respectively are ignored. Furthermore, leading zero for values lower than 1 is optional.\n");
	printf("#Data columns may have as column separator white spaces (' '), commas (',') or semicolon (';'). gLAB, internally, will replace all commas and semicolons by spaces, therefore, these column separators can be set combined in different or in the same line.\n");
	printf("#Numbers MUST have decimals with a dot ('.'), as commas are treated as a column separator\n");
	printf("#For example, this line:\n");
	printf("#20   0.5\n");
	printf("#Can also be written like this:\n");
	printf("#   20        .5\n");
	printf("#\n");
	printf("Elevation\n");
	printf("10  0.8\n");
	printf("20      0.7\n");
	printf("30  0.6\n");
	printf("40  0.5\n");
	printf("50  0.4\n");
	printf("60  0.3\n");
	printf("70  0.2\n");
	printf("80  0.1\n");
	printf("90  0.1\n");
}


/*****************************************************************************
 * Name        : showusererrorfile
 * Description : Shows an example of a user-defined error configuration file
 * Parameters  : None
 *****************************************************************************/
void showusererrorfile () {
	#if defined _OPENMP
		printf("#gLAB version v%s (with OpenMP multithread), built on %s %s\n",VERSION,__DATE__,__TIME__);
	#else
		printf("#gLAB version v%s, built on %s %s\n",VERSION,__DATE__,__TIME__);
	#endif
	printf("#This is an example of user-defined error configuration file\n");
	printf("#Lines with comments start with a # at the beginning of line\n");
	printf("#If the symbol # is found in the middle of the line, the rest of the line will be omitted, as it will be considered a comment\n");
	printf("#Empty lines will be skipped\n");
	printf("#By executing 'gLAB -usererrorfile > usererrorfile.txt' a valid user-defined error configuration file is created (this file). Only dates need to be adjusted by user\n");
	printf("#\n");
	printf("#The following lines explain the rules for creating a user defined error configuration file:\n");
	printf("#First line (non empty or without '#') will have two words:\n");
	printf("##The first word indicates if time is given in [GPS week and ToW (Time of Week)] or in [GPS Year, DoY (Day of Year) and SoD (Seconds of Day)]:\n");
	printf("## ToW        -> Time of week (case insensitive)\n");
	printf("## SoD        -> Seconds of Day (case insensitive)\n");
	printf("##The second word indicates if the user wants to indicate the duration of the user-defined error either by specifying the length (in seconds) with the word \"Length\" or by giving the date where the error ends (in the same time format as the initial time) with the word \"Time\".\n");
	printf("## Length     -> Length of user-defined error (case insensitive)\n");
	printf("## Time       -> End time (case insensitive)\n");
	printf("#\n");
	printf("#The second line indicates the seed (random function initial value) for the AWGN (Additive White Gaussian Noise) noise (applied just after being read). It can be the system time, specified with the word \"Time\" or by a number given by user. This line will start with the word \"Seed\" (or \"seed\") and then the word to specify the seed type:\n");
	printf("## CurrentTime -> Use current execution time (from system) as seed (case insensitive)\n");
	printf("## <number>    -> Use this number as seed. It must be a positive integer. Floating values will be truncated, but negative values will make gLAB show an error and exit. \n");
	printf("#\n");
	printf("#Each line will contain a type of user-defined error to be generated for a given time period.\n");
	printf("#The entries MUST be sorted by time (from earliest to latest). If entries are not sorted, user-defined errors from previous epochs will be ignored.\n");
	printf("#\n");
	printf("#The first word of each line will indicate the type of user-defined error to be generated\n");
	printf("#The type of user-defined error possible are:\n");
	printf("#  Step       -> for a step function\n");
	printf("#  Ramp       -> for a ramp function\n");
	printf("#  Sinu       -> for a sinusoidal function\n");
	printf("#  AWGN       -> for AWGN noise\n");
	printf("#The second word will be to indicate the constellation and PRN in which the error is added.\n");
	printf("##The constellation will be given with one the following letters:\n");
	printf("#  G -> GPS\n");
	printf("#  R -> GLONASS\n");
	printf("#  E -> Galileo\n");
	printf("#  S -> SBAS\n");
	printf("#  C -> BeiDou\n");
	printf("#  J -> QZSS\n");
	printf("##The PRN number is from 0 to 32. A PRN of 0 means that all satellites in the constellation will have this added noise.\n");
	printf("#The third word is to indicate the signal where to add the error. \n");
	printf("#The signal code must be one of the observation codes from RINEX version 3.03, (e.g. C1C, L1P, etc.).  For a full list of observation codes, refer to [RINEX, The Receiver Independent Exchange Format, Version 3.02, 14 July 2015].\n");
	printf("#\n");
	printf("#Step function definition:\n");
	printf("#       Step(t)=A*(u(t-t0)-u(t-t1))\n");
	printf("# Where:\n");
	printf("#    A is the amplitude of step, which is a constant value. It is defined by the user (in metres).\n");
	printf("#    t is the current epoch (in seconds of day).\n");
	printf("#    t0 is the epoch where the step function begins (in seconds of day). It is defined by the user.\n");
	printf("#    t1 is the epoch where the step function ends (in seconds of day). It is defined by the user.\n");
	printf("#    u(t) is the unit step or Heavyside function, defined as:\n");
	printf("#          t>=0 u(t)=1\n");
	printf("#          t<0  u(t)=0\n");
	printf("#    Step(t) is the added error to the measurement (in metres).\n");
	printf("#\n");
	printf("#Ramp function definition:\n");
	printf("#       Ramp(t)=B*(t-t0)*(u(t-t0)-u(t-t1))\n");
	printf("# Where:\n");
	printf("#    B is the amplitude of ramp, which is a constant value. It is defined by the user (in metres).\n");
	printf("#    t is the current epoch (in seconds of day).\n");
	printf("#    t0 is the epoch where the ramp function begins (in seconds of day). It is defined by the user.\n");
	printf("#    t1 is the epoch where the ramp function ends (in seconds of day). It is defined by the user.\n");
	printf("#    u(t) is the unit step or Heavyside function, defined as:\n");
	printf("#          t>=0 u(t)=1\n");
	printf("#          t<0  u(t)=0\n");
	printf("#    Ramp(t) is the added error to the measurement (in metres).\n");
	printf("#\n");
	printf("#Sinusoidal function definition:\n");
	printf("#       Sinusoidal(t)=C*sin(2*Pi*t/T + alpha)*(u(t-t0)-u(t-t1))\n");
	printf("# Where:\n");
	printf("#    C is the amplitude of sinusoidal, which is a constant value. It is defined by the user (in metres).\n");
	printf("#    T is the period of the sinusoidal, which is a constant value. It is defined by the user (in seconds).\n");
	printf("#    alpha is the offset of the sinusoidal, which is a constant value. It is defined by the user (in degrees).\n");
	printf("#    t is the current epoch (in seconds of day).\n");
	printf("#    t0 is the epoch where the sinusoidal function begins (in seconds of day). It is defined by the user.\n");
	printf("#    t1 is the epoch where the sinusoidal function ends (in seconds of day). It is defined by the user.\n");
	printf("#    u(t) is the unit step or Heavyside function, defined as:\n");
	printf("#          t>=0 u(t)=1\n");
	printf("#          t<0  u(t)=0\n");
	printf("#    sin(t) is the nominal sinusoidal function.\n");
	printf("#    Sinusoidal(t) is the added error to the measurement (in metres).\n");
	printf("#\n");
	printf("#AWGN function definition:\n");
	printf("#       AWGN(t)=w(t)*(u(t-t0)-u(t-t1))\n");
	printf("# Where:\n");
	printf("#    w(t) is an Additive White Gaussian Noise (AWGN) random process. In particular:\n");
	printf("#      w(t) samples has an associated sigma which can be defined by the user (in metres).\n");
	printf("#      The mean value of w(t) samples is zero.\n");
	printf("#    t is the current epoch (in seconds of day).\n");
	printf("#    t0 is the epoch where the ramp function begins (in seconds of day). It is defined by the user.\n");
	printf("#    t1 is the epoch where the ramp function ends (in seconds of day). It is defined by the user.\n");
	printf("#    u(t) is the unit step or Heavyside function, defined as:\n");
	printf("#          t>=0 u(t)=1\n");
	printf("#          t<0  u(t)=0\n");
	printf("#    AWGN(t) is the added error to the measurement (in metres).\n");
	printf("#\n");
	printf("#Example for Step function (using SoD and Length):\n");
	printf("#Step G3 C1C 5 2016 1 300 500\n");
	printf("# Where \"G3\" indicates satellite with PRN 3 from GPS constellation\n");
	printf("#       \"C1C\" is the observation code for GPS L1 frequency civil psudorange measurement\n");
	printf("#       \"5\" is the amplitude (in metres) of the step function\n");
	printf("#       \"2016\" is the year when the step starts\n");
	printf("#       \"1\" is the day of year when the step starts\n");
	printf("#       \"300\" is the seconds of day when the step starts\n");
	printf("#       \"500\" is the duration (in seconds) of the step\n");
	printf("#\n");
	printf("#Example for Ramp function (using SoD and Time):\n");
	printf("#Ramp G0 L1P 5 2016 1 300 2016 1 500\n");
	printf("# Where \"G0\" indicates all satellites from GPS constellation\n");
	printf("#       \"L1P\" is the observation code for GPS L1 frequency carrier phase measurement\n");
	printf("#       \"5\" is the amplitude (in metres/second) of the ramp function\n");
	printf("#       \"2016\" is the year when the ramp starts\n");
	printf("#       \"1\" is the day of year when the ramp starts\n");
	printf("#       \"300\" is seconds of day when the ramp starts\n");
	printf("#       \"2016\" is the year when the ramp ends\n");
	printf("#       \"1\" is the day of year when the ramp ends\n");
	printf("#       \"500\" is the seconds of day when the ramp ends\n");
	printf("#Example for Sinusoidal function (using ToW and Length):\n");
	printf("#Sinu G12 C1C 5 20E-6 90 1848 259200 500\n");
	printf("# Where \"G12\" indicates satellite with PRN 12 from GPS constellation\n");
	printf("#       \"C1C\" is the observation code for GPS L1 frequency civil psudorange measurement\n");
	printf("#       \"5\" is the amplitude (in metres) of the sinusoidal function\n");
	printf("#       \"20E-6\" is the period of the signal (in seconds). \n");
	printf("#       \"90\" is the offset (in degrees) to be added in the sinusoidal function\n");
	printf("#       \"1848\" is the GPS week when the sinusoidal starts\n");
	printf("#       \"259200\" is the seconds of week when the sinusoidal starts\n");
	printf("#       \"500\" is the duration (in seconds) of the sinusoidal\n");
	printf("#\n");
	printf("#Example for AWGN function (using ToW and Time):\n");
	printf("#AWGN G31 C1C 5 1848 259200 1848 259700\n");
	printf("# Where \"G31\" indicates satellite with PRN 31 from GPS constellation\n");
	printf("#       \"C1C\" is the observation code for GPS L1 frequency civil psudorange measurement\n");
	printf("#       \"5\" is the standard deviation (in metres) of the AWGN random process\n");
	printf("#       \"\"1848\" is the GPS week when the AWGN starts\n");
	printf("#       \"259200\" is the seconds of week when the AWGN starts\n");
	printf("#       \"1848\" is the GPS week when the AWGN ends\n");
	printf("#       \"259700\" is the seconds of week when the AWGN ends\n");
	printf("#\n");
	printf("#Data lines with wrong number of columns will be ignored (except for the initial two lines with time format and seed)\n");
	printf("#Data lines with a user-defined error model different from the ones listed above will be ignored\n");
	printf("#\n");
	printf("#Data columns do not need to have a specific number of spaces between them, as well as leading and trailing spaces at the beginning or end of line respectively are ignored. Furthermore, leading zero for values lower than 1 is optional.\n");
	printf("#Data columns may have as column separator white spaces (' '), commas (',') or semicolon (';'). gLAB, internally, will replace all commas and semicolons by spaces, therefore, these column separators can be set combined in different or in the same line.\n");
	printf("#Numbers MUST have decimals with a dot ('.'), as commas are treated as a column separator\n");
	printf("#For example, this line:\n");
	printf("#Step G10 C1C 5 2016 1 300 50\n");
	printf("#Can also be written like this:\n");
	printf("# Step   G10  C1C     5    2016    1 300        50   \n");
	printf("#\n");
	printf("#gLAB will print the user-defined error in the lines starting with 'USERADDEDERROR' (which are enabled by default). The description of each field in the message is shown by executing 'gLAB -messages'.\n");
	printf("#\n");
	printf("#For RINEX 2 files, the user must use the equivalent measurements for RINEX 3. The measurement conversion table is:\n");
	printf("#C1 -> C1C\n");
	printf("#P1 -> C1P\n");
	printf("#L1 -> L1P\n");
	printf("#D1 -> D1P\n");
	printf("#S1 -> S1P\n");
	printf("#\n");
	printf("#C2 -> C2C\n");
	printf("#P2 -> C2P\n");
	printf("#L2 -> L2P\n");
	printf("#D2 -> D2P\n");
	printf("#S2 -> S2P\n");
	printf("#\n");
	printf("#C5 -> C5X\n");
	printf("#L5 -> L5X\n");
	printf("#D5 -> D5X\n");
	printf("#S5 -> S5X\n");
	printf("#\n");
	printf("#C6 -> C6X\n");
	printf("#L6 -> L6X\n");
	printf("#D6 -> D6X\n");
	printf("#S6 -> S6X\n");
	printf("#\n");
	printf("#C7 -> C7X\n");
	printf("#L7 -> L7X\n");
	printf("#D7 -> D7X\n");
	printf("#S7 -> S7X\n");
	printf("#\n");
	printf("#C8 -> C8X\n");
	printf("#L8 -> L8X\n");
	printf("#D8 -> D8X\n");
	printf("#S8 -> S8X\n");
	printf("#\n");
	printf("#Usage Example:\n");
	printf("SoD Length\n");
	printf("Seed 10\n");
	printf("#Add all user-defined errors at the same time\n");
	printf("Step G10 C1C 5 2016 1 300 50\n");
	printf("Ramp G20 C1C 5 2016 1 300 500\n");
	printf("Sinu G15 L1P 5 20E-6 90 2016 1 300 500\n");
	printf("AWGN G10 C1C 5 2016 1 300 500\n");
	printf("#Add some more user-defined error later\n");
	printf("Ramp G0 C1C 5 2016 1 500 400\n");
	printf("Sinu G32 L1P 5 20E-6 90 2016 1 5000 300\n");
}

/*****************************************************************************
 * Name        : showRTCMv2ConversionInfo
 * Description : Shows an explanation of what fields are written in the
 *                 output files from a conversion fron RTCMv2
 * Parameters  : None
 *****************************************************************************/
void showRTCMv2ConversionInfo () {
	#if defined _OPENMP
		printf("gLAB version v%s (with OpenMP multithread), built on %s %s\n",VERSION,__DATE__,__TIME__);
	#else
		printf("gLAB version v%s, built on %s %s\n",VERSION,__DATE__,__TIME__);
	#endif
	printf("Here are detailed the contents of the two files generated when converting an RTCM v2.x\n");
	printf("  to text format. As there is no standard for converting to text files the RTCM v2.x files,\n");
	printf("  gLAB will create two files: the \"corrections\" file and the \"antenna\" file, which will\n");
	printf("  the following fields:\n\n");
	printf("Corrections File:\n");
	printf("Sets the ASCII Plain Text output file name for the corrections read from a RTCM v2.x file.\n");
	printf("The fields written in the output file are:\n\n");
	printf("    GPS_week: GPS week of the RTCM message.\n");
	printf("    SoW: Second of week of the RTCM message (the epoch is not given in the message except for the seconds of hour in Z-count value).\n");
	printf("    MSG_number: Message type number (appears in the header of all messages).\n");
	printf("    Station_ID: Station ID of the RTCM v2.x message (appears in the header of all messages).\n");
	printf("    Z-count: Seconds of hour (appears in the header of all messages). As this is only the time reference in RTCM v2.x messages,\n");
	printf("              the user must provide the inital date and hour to convert it to a normal date format.\n");
	printf("    SV_health: Station health status (appears in the header of all messages).\n");
	printf("        The values for the health status are a scale factor for the measurement UDRE,\n");
	printf("        with the following values:\n\n");
	printf("            0: UDRE scale factor = 1.\n");
	printf("            1: UDRE scale factor = 0.75.\n");
	printf("            2: UDRE scale factor = 0.5.\n");
	printf("            3: UDRE scale factor = 0.3.\n");
	printf("            4: UDRE scale factor = 0.2.\n");
	printf("            5: UDRE scale factor = 0.1.\n");
	printf("            6: Reference station transmission not monitored (a UDRE scale factor = 1 is applied if corrections are used).\n");
	printf("            7: Reference station not working (a UDRE scale factor = 1 is applied if corrections are used).\n\n");
	printf("    PRN: Satellite PRN to apply the corrections.\n");
	printf("    PRC: Pseudorange correction to be applied to the satellite (metres).\n");
	printf("    RRC: Range-rate corrections to be applied to the satellite (metres).\n");
	printf("    IOD: IOD (Issue of Data) of the navigation message used to compute the corrections.\n");
	printf("           The user must also use the same IOD when applying the corrections.\n");
	printf("    UDRE: UDRE (User Differential Range Error). Provides a rough estimation of the error in the measurements.\n");
	printf("           This estimation must be multiplied by the UDRE scale factor read in the message header.\n");
	printf("           The possible values for the UDRE are:\n\n");
	printf("             0: 1 metre.\n");
	printf("             1: 4 metres.\n");
	printf("             2: 8 metres.\n");
	printf("             3: 10 metres.\n");
	printf("\nAntenna File:\n");
	printf("Sets the ASCII Plain Text output file name for the antenna data read from a RTCM v2.x file.\n");
	printf("The fields written in the output file are:\n");
	printf("    Station_ID: Station ID of the RTCM v2.x message (appears in the header of all messages).\n");
	printf("    X_coordinate: X coordinate component of the reference antenna (metres).\n");
	printf("    Y_coordinate: Y coordinate component of the reference antenna (metres).\n");
	printf("    Z_coordinate: Z coordinate component of the reference antenna (metres).\n");
	printf("    MSG_number: Message type number (appears in the header of all messages).\n");
	printf("      The possible values of message type number in this file are:\n");
	printf("        MT03: In message type 3, reference station antenna coordinates are in GPS computed coordinates (in ECEF -Earth Centered Earth Fixed-)\n");
	printf("        MT24: In message type 24, reference station antenna coordinates are referred to the Antenna Reference Point (ARP) in (in ECEF)\n");
}


/*****************************************************************************
 * Name        : showReferencePositionFileInfo
 * Description : Shows an example of a reference position file
 * Parameters  : None
 *****************************************************************************/
void showReferencePositionFileInfo () {
	#if defined _OPENMP
		printf("#gLAB version v%s (with OpenMP multithread), built on %s %s\n",VERSION,__DATE__,__TIME__);
	#else
		printf("#gLAB version v%s, built on %s %s\n",VERSION,__DATE__,__TIME__);
	#endif
	printf("#This is an example of a reference position file\n");
	printf("#Lines with comments start with a '#' or '%%' at the beginning of line\n");
	printf("#If the symbol # is found in the middle of the line, the rest of the line will be omitted, as it will be considered a comment\n");
	printf("#Empty lines will be skipped\n");
	printf("#By executing 'gLAB -referenceposfile > referencepositionfile.txt' a valid reference position file is created (this file). Dates and positions have to be adjusted by user\n");
	printf("#\n");
	printf("#The following lines explain the rules for creating a reference position file:\n");
	printf("#Data columns do not need to have a specific number of spaces between them, as well as leading and trailing spaces at the beginning or end of line respectively are ignored. Furthermore, leading zero for values lower than 1 is optional.\n");
	printf("#Data columns may have as column separator white spaces (' '), commas (',') or semicolon (';'). gLAB, internally, will replace all commas and semicolons by spaces, therefore, these column separators can be set combined in different or in the same line.\n");
	printf("#Numbers MUST have decimals with a dot ('.'), as commas are treated as a column separator.\n");
	printf("#The first line of data (first line non empty or without a '#') must have the names of the elements of each column.\n");
	printf("#Names of columns are case insensitive, and must be given in the same order as the data (so gLAB what type of data has each column).\n");
	printf("#The order of the data is not important as long as the data type matches the position of the name of the data in the first line.\n");
	printf("#The accepted names of columns are:\n");
	printf("#Year      -> Year\n");
	printf("#DoY       -> Day of Year\n");
	printf("#SoD       -> Seconds of Day\n");
	printf("#GPSWeek   -> GPSWeek\n");
	printf("#SoW       -> Seconds of Day\n");
    printf("#Date      -> Date in calendar format (YYYY/MM/DD)\n");
	printf("#Time      -> Time in calendar format (HH:MM:SS.zzz). 'zzz' are milliseconds\n");
	printf("#X         -> X coordinate (metres)\n");
	printf("#Y         -> Y coordinate (metres)\n");
	printf("#Z         -> Z coordinate (metres)\n");
	printf("#Lon       -> Longitude (degrees). Range is [-180..180]. Values outside of this range will be rejected\n");
	printf("#Longitude -> Longitude (degrees). Range is [-180..180]. Values outside of this range will be rejected\n");
	printf("#Lat       -> Latitude (degrees). Range is [-90..90]. Values outside of this range will be rejected\n");
	printf("#Latitude  -> Latitude (degrees). Range is [-90..90]. Values outside of this range will be rejected\n");
	printf("#Height    -> Height (metres)\n");
	printf("#\n");
	printf("#X, Y and Z are in cartesian ECEF WGS84 reference frame.\n");
	printf("#Latitude, Longitude and Height are in geodetic ECEF WGS84 reference frame.\n");
	printf("#\n");
	printf("#The file must contain a full set of valid date and coordinates. That is, it must have at least the fields 'Year, DoY, SoD' or 'GPSWeek, SoW' or 'Date Time' for the date, and fields 'X, Y ,Z' or 'Lon, Lat, Height' for the coordinates\n");
	printf("#If file contains more than one date formats or both coordinate systems, gLAB will prefer 'Year, DoY, SoD' format for date and 'X, Y, Z' for coordinates (it has less computational cost)\n");
	printf("#All other columns that do not match any of the accepted names will be ignored.\n");
	printf("#\n");
	printf("#Furthermore, RTKlib output file is also supported (output must be in 'Lat/Lon/Height' or 'X/Y/Z-ECEF' formats).\n");
	printf("#\n");
	printf("#For example, the first line could be like the following samples (note that order and number of column separators is not important):\n");
	printf("#Year DoY SoD  X Y Z\n");
	printf("#Year, DoY, SoD,  X, Y, Z\n");
	printf("#GPSWeek  SoW    Y  X      Z\n");
	printf("#DoY   SoD   Year  Lon   Lat    Height\n");
	printf("#SoW    GPSWeek  Lat Lon Height\n");
	printf("#DoY  Year  Lon  Height  SoD  Lat\n");
	printf("#\n");
	printf("#The lines below are a valid set of data lines:\n");
	printf("Year DoY       SoD              X              Y              Z\n");
	printf("2014 067 21200.000   3219920.5954   4672079.7551   3465886.3080\n");
	printf("2014 067 21500.000   3219919.9508   4672079.7847   3465887.1434\n");
	printf("2014 067 21800.000   3219920.2422   4672080.7439   3465887.0480\n");
}

/*****************************************************************************
 * Name        : parseOption
 * Description : Parse an option from a vector of strings into the options or
 *               support options
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TSupportOptions  *sopt          O  N/A  TSupportOptions structure
 * TOptions  *options              O  N/A  TOptions structure
 * char  *argv[]                   I  N/A  Vector of strings to be parsed
 * Returned value (int)            O  N/A  Status of the function
 *                                         -4 => Parameter length too long
 *                                         -3 => Missing second parameter                                        
 *                                         -2 => Parameter value not valid
 *                                         -1 => Parameter name unknown
 *                                         0  => Help/examples message (end program)
 *                                         >0 => Number of strings parsed
 *****************************************************************************/
int parseOption (TSupportOptions *sopt, TOptions *options, char *argv[]) {
	int			aux1,aux2,aux3,aux4,aux5,aux6,aux7;
	double		auxd,auxd2,auxd3;
	double		auxdarea[4];
	int			i,j,k;
	char		c;
	char		*p,*p2;
	char		auxstr[10];
	char		auxstr2[MAX_MESSAGE_STR];
	struct tm   tm;

	if (strcasecmp(argv[0],"-help")==0 || strcasecmp(argv[0],"--help")==0) {
		showHelp();
		return 0;
	} else if (strcasecmp(argv[0],"-examples")==0 || strcasecmp(argv[0],"--examples")==0) {
		showExamples();
		return 0;
	} else if (strcasecmp(argv[0],"-config")==0 || strcasecmp(argv[0],"--config")==0) {
		showConfig();
		return 0;
	} else if (strcasecmp(argv[0],"-messages")==0 || strcasecmp(argv[0],"--messages")==0) {
		showMessages();
		return 0;
	} else if (strcasecmp(argv[0],"-usererrorfile")==0 || strcasecmp(argv[0],"--usererrorfile")==0) {
		showusererrorfile();
		return 0;
	} else if (strcasecmp(argv[0],"-sigmamultipathfile")==0 || strcasecmp(argv[0],"--sigmamultipathfile")==0) {
		showsigmamultipathfile();
		return 0;
	} else if (strcasecmp(argv[0],"-rtcmv2conversioninfo")==0 || strcasecmp(argv[0],"--rtcmv2conversioninfo")==0) {
		showRTCMv2ConversionInfo();
		return 0;
	} else if (strcasecmp(argv[0],"-referenceposfile")==0 || strcasecmp(argv[0],"--referenceposfile")==0) {
		showReferencePositionFileInfo();
		return 0;
	} else if (strcasecmp(argv[0],"-onlyconvert")==0 ) {
		options->onlyconvertSBAS=1;
		return 1;
	} else if (strcasecmp(argv[0],"-output:file")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->outFile,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"--output:file")==0) {
		sopt->outFile[0]='\0';
		return 1;
	} else if (strcasecmp(argv[0],"-output:kml")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->kmlFile,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-output:kml0")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->kml0File,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-output:kml:refsta")==0) {
		options->referenceStations=1;
		return 1;
	} else if (strcasecmp(argv[0],"--output:kml:refsta")==0) {
		options->referenceStations=0;
		return 1;
	} else if (strcasecmp(argv[0],"-output:kml:tstamp")==0) {
		options->KMLTimeStamps=1;
		return 1;
	} else if (strcasecmp(argv[0],"--output:kml:tstamp")==0) {
		options->KMLTimeStamps=0;
		return 1;
	} else if (strcasecmp(argv[0],"-output:kml:tstampdec")==0) {
		if (argv[1]==NULL) return -3;
		options->KMLTimeStamps=1;
		auxd=atof(argv[1]);
		if(auxd<0.) return -2;
		if(auxd>1.) auxd=(double)((int)(auxd)); //If decimation is greater than 1, eliminate decimals
		options->KMLTimeStampDec=auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-output:kml:tstamprange")==0) {
		if (argv[1]==NULL||argv[2]==NULL) return -3;
		options->KMLTimeStamps=1;
		if(strcmp(argv[1],"-")==0) {
			auxd3=1.; //Flag to indicate 'Start of file'
			auxd=0.;
		} else {
			auxd3=0.; 
			auxd=atof(argv[1]);
			if(auxd<0.) return -2;
		}
		if(strcmp(argv[2],"-")==0) {
			auxd2=9999999999999.;
		} else {
			auxd2=atof(argv[2]);
			if(auxd2<0.) return -2;
		}
		//Check if ranges already exist (this is because this function is called several times,
		//so we need to avoid loading the same ranges multiple times
		for(i=0;i<options->numKMLTimeRanges;i++) {
			if (options->KMLtimeranges[i][0]==auxd && options->KMLtimeranges[i][1]==auxd2 && options->KMLtimeranges[i][2]==auxd3) {
				//Range found
				return 3;
			}
		}
		options->KMLtimeranges=realloc(options->KMLtimeranges,sizeof(double*)*(options->numKMLTimeRanges+1));
		options->KMLtimeranges[options->numKMLTimeRanges]=malloc(sizeof(double)*3);
		options->KMLtimeranges[options->numKMLTimeRanges][0]=auxd;
		options->KMLtimeranges[options->numKMLTimeRanges][1]=auxd2;
		options->KMLtimeranges[options->numKMLTimeRanges][2]=auxd3; 
		options->numKMLTimeRanges++;
		return 3;
	} else if (strcasecmp(argv[0],"-output:sp3")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->SP3OutputFile,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-output:sp3:letter")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])!=1) return -2;
		options->SP3Letter=argv[1][0];
		return 2;
	} else if (strcasecmp(argv[0],"-output:sp3:prn")==0) {
		if (argv[1]==NULL) return -3;
		aux1=atoi(argv[1]);
		if(aux1<0 || aux1>=100 ) return -2;
		options->SP3PRN=aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-output:sp3:dgnssonly")==0) {
		options->WriteSPPsolInDGNSSmodeSP3=0;
		return 1;
	} else if (strcasecmp(argv[0],"--output:sp3:dgnssonly")==0) {
		options->WriteSPPsolInDGNSSmodeSP3=1;
		return 1;
	} else if (strcasecmp(argv[0],"-output:refpos")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->RefPosOutputFile,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-output:refpos:doy")==0) {
		options->YearSoDRefFile=1;
		options->GPSWeekRefFile=0;
		options->CalendarTimeRefFile=0;
		return 1;
	} else if (strcasecmp(argv[0],"-output:refpos:gpsweek")==0) {
		options->YearSoDRefFile=0;
		options->GPSWeekRefFile=1;
		options->CalendarTimeRefFile=0;
		return 1;
	} else if (strcasecmp(argv[0],"-output:refpos:caltime")==0) {
		options->YearSoDRefFile=0;
		options->GPSWeekRefFile=0;
		options->CalendarTimeRefFile=1;
		return 1;
	} else if (strcasecmp(argv[0],"-output:refpos:geodetic")==0) {
		options->GeodeticCoordRefFile=1;
		return 1;
	} else if (strcasecmp(argv[0],"--output:refpos:geodetic")==0) {
		options->GeodeticCoordRefFile=0;
		return 1;
	} else if (strcasecmp(argv[0],"-output:refpos:dgnssonly")==0) {
		options->WriteSPPsolInDGNSSmodeRefFile=0;
		return 1;
	} else if (strcasecmp(argv[0],"--output:refpos:dgnssonly")==0) {
		options->WriteSPPsolInDGNSSmodeRefFile=1;
		return 1;
	} else if (strcasecmp(argv[0],"-output:rinex")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-11) return -4; //The 10 extra characters are for the "_usererror" suffix
		strcpy(sopt->rnxFile,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-output:antenna")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->antennaASCIIFile,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-output:corrections")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->dataASCIIFile,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-output:rinexversion")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if ( aux1 != 2 && aux1 != 3 ) return -2;
		options->rinexVersion = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-output:satvel")==0) {
		if (argv[1]==NULL) return -3;
		if (strcasecmp(argv[1],"inertial")==0) {
			options->satVel = svINERTIAL;
			return 2;
		} else if (strcasecmp(argv[1],"itrf")==0) {
			options->satVel = svITRF;
			return 2;
		} else return -2;
	} else if (strcasecmp(argv[0],"-output:rinexb")==0) {
		options->writeRinexBfile=1;
		return 1;
	} else if (strcasecmp(argv[0],"-output:ems")==0) {
		options->writeEMSfile=1;
		return 1;
	} else if (strcasecmp(argv[0],"-output:pegasus")==0) {
		options->writePegasusfile=1;
		return 1;
	} else if (strcasecmp(argv[0],"-output:pegspace")==0) {
		options->pegasusfs=' ';
		return 1;
	} else if (strcasecmp(argv[0],"-output:sbasdir")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-50) return -4;
		strcpy(options->sbasdir,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-output:pegstrictrinex")==0) {
		options->pegasuspurerinex=1;
		return 1;
	} else if (strcasecmp(argv[0],"-output:pegfilealign")==0) {
		options->pegasusaligned=1;
		return 1;
	} else if (strcasecmp(argv[0],"-output:stfdesa")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->stanfordESAFile,argv[1]);
		options->stanfordesa=1;
		return 2;
	} else if (strcasecmp(argv[0],"-output:stfdesaLOI")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->stanfordESALOIFile,argv[1]);
		options->stanfordesa=1;
		options->stanfordesaLOI=1;
		return 2;
	} else if (strcasecmp(argv[0],"-input:cfg")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->cfgFile,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-input:obs")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->obsFile,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-input:nav")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		if(sopt->numNav<2) { 
			//Max navigation files is 2. Error will be shown later
			//We do not copy the name of the file when limit is surpassed to avoid buffer overflow
			strcpy(sopt->navFile[sopt->numNav],argv[1]);
		}
		sopt->numNav++;
		return 2;
	} else if (strcasecmp(argv[0],"-input:dgnss")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->dgnssFile,argv[1]);
		options->DGNSS = 1;
		options->RTCMmode = ProcessRINEX;
		return 2;
	} else if (strcasecmp(argv[0],"-input:rtcm")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-20) return -4;
		strcpy(sopt->rtcmFile,argv[1]);
		options->DGNSS = 1;
		return 2;
	} else if (strcasecmp(argv[0],"-input:rtcm2")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-20) return -4;
		strcpy(sopt->rtcm2File,argv[1]);
		options->DGNSS = 1;
		return 2;
	} else if (strcasecmp(argv[0],"-input:rtcm3")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-20) return -4;
		strcpy(sopt->rtcm3File,argv[1]);
		options->DGNSS = 1;
		return 2;
	} else if (strcasecmp(argv[0],"-input:rtcm:initdate")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		aux2 = (int)(aux1/10000);
		if ( aux2 < 1000 || aux2 > 9999 ) return -2;
		options->rtcmYear = aux2;
		aux6 = (int)(aux2/100);
		aux7 = (int)(aux2-aux6*100);
		options->rtcmYearShort = aux7;
		aux3 = (int)(aux1-aux2*10000);
		aux4 = (int)(aux3/100);
		if ( aux4 > 12 ) return -2;
		options->rtcmMonth = aux4;
		aux5 = (int)(aux3-aux4*100);
		if ( aux5 > 31 ) return -2;
		options->rtcmDay = aux5;
		return 2;
	} else if (strcasecmp(argv[0],"-input:rtcm:inithour")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if ( aux1 < 0 || aux1 > 23 ) return -2;
		options->rtcmHour = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-input:sp3")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		if(sopt->numSP3<2) {  
			//Max SP3 files is 2. Error will be shown later
			//We do not copy the name of the file when limit is surpassed to avoid buffer overflow
			strcpy(sopt->SP3File[sopt->numSP3],argv[1]);
		}
		sopt->numSP3++;
		return 2;
	} else if (strcasecmp(argv[0],"-input:con")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->conFile,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-input:orb")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		if(sopt->numOrb<2) { 
			//Max orbit files is 2. Error will be shown later
			//We do not copy the name of the file when limit is surpassed to avoid buffer overflow
			strcpy(sopt->orbFile[sopt->numOrb],argv[1]);
		}
		sopt->numOrb++;
		return 2;
	} else if (strcasecmp(argv[0],"-input:clk")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		if(sopt->numClk<2) {
			//Max clock files is 2. Error will be shown later
			//We do not copy the name of the file when limit is surpassed to avoid buffer overflow
			strcpy(sopt->clkFile[sopt->numClk],argv[1]);
		}
		sopt->numClk++;
		return 2;
	} else if (strcasecmp(argv[0],"-input:ant")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->antFile,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-input:klb")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->klbFile,argv[1]);
		sopt->ionoModel = Klobuchar;
		return 2;
	} else if (strcasecmp(argv[0],"-input:bei")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->beiFile,argv[1]);
		sopt->ionoModel = BeiDou;
		return 2;
	} else if (strcasecmp(argv[0],"-input:bds")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->beiFile,argv[1]);
		sopt->ionoModel = BeiDou;
		return 2;
	} else if (strcasecmp(argv[0],"-input:inx")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->inxFile,argv[1]);
		sopt->ionoModel = IONEX;
		return 2;
	} else if (strcasecmp(argv[0],"-input:fpp")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->fppFile,argv[1]);
		sopt->ionoModel = FPPP;
		return 2;
	} else if (strcasecmp(argv[0],"-input:fppp")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->fppFile,argv[1]);
		sopt->ionoModel = FPPP;
		return 2;
	} else if (strcasecmp(argv[0],"-input:SBASiono")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->SBASIONOFile,argv[1]);
		sopt->ionoModel = SBASiono;
		return 2;
	} else if (strcasecmp(argv[0],"-input:dcb")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		if(sopt->numTGD<2) {
			strcpy(sopt->tgdFile[sopt->numTGD],argv[1]);
		}
		sopt->numTGD++;
		return 2;
	} else if (strcasecmp(argv[0],"-input:rec")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->recFile,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-input:snx")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->snxFile,argv[1]);
		options->receiverPositionSource = rpSINEX;
		options->recPosProvided=1;
		return 2;
	} else if (strcasecmp(argv[0],"-input:sbas")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-20) return -4; //The 20 characters is because we will use this name to generate an automatic output filename
		strcpy(sopt->sbasFile,argv[1]);
		options->SBAScorrections=1;
		return 2;
	} else if (strcasecmp(argv[0],"-input:sigmpath")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->sigmamultipathFile,argv[1]);
		options->usersigmamultipath=1;
		options->airborneReceiverType=0;
		return 2;
	} else if (strcasecmp(argv[0],"-input:usererror")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->addederrorFile,argv[1]);
		options->useraddednoise=1;
		return 2;
	} else if (strcasecmp(argv[0],"-input:refpos")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->posReferenceFile,argv[1]);
		if (options->receiverPositionSource==rpUNKNOWN) {
			//User has not set any mode. Set the default mode with reference file
			options->receiverPositionSource = rpCALCULATEREF;
		}
		options->recPosProvided=1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:usererrorafter")==0) {
		options->useraddednoisepreprocess=1;
		return 1;
	} else if (strcasecmp(argv[0],"--pre:usererrorafter")==0) {
		options->useraddednoisepreprocess=0;
		return 1;
	} else if (strcasecmp(argv[0],"-pre:elevation")==0) {
		if (argv[1]==NULL) return -3;
		options->elevationMask = atof(argv[1])*d2r;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:eclipse")==0) {
		sopt->discardEclipsedSatellites = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--pre:eclipse")==0) {
		sopt->discardEclipsedSatellites = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-pre:dec")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if (auxd<0.) return -2;
		if (auxd>=1.) auxd=(double)((int)(auxd+.00005)); //If decimation is greater than 1, eliminate decimals
		options->decimate = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:prealign")==0) {
		options->prealignCP = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--pre:prealign")==0) {
		options->prealignCP = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-pre:checkcodejumps")==0) {
		options->checkPhaseCodeJumps = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--pre:checkcodejumps")==0) {
		options->checkPhaseCodeJumps = 0;
		return 1;
//	} else if (strcasecmp(argv[0],"-pre:flexibleC1P1")==0) {
//		options->flexibleC1P1 = 1;
//		return 1;
//	} else if (strcasecmp(argv[0],"--pre:flexibleC1P1")==0) {
//		options->flexibleC1P1 = 0;
//		return 1;
	} else if (strcasecmp(argv[0],"-pre:cs:datagap")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if ( auxd <= 0. ) return -2;
		if( auxd>=1.) auxd = (double)((int)(auxd));
		options->csDataGap = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:lli")==0) {
		sopt->csLLI = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--pre:cs:lli")==0) {
		sopt->csLLI = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-pre:cs:ncon")==0) {
	  options->csNcon = 1;
	  return 1;
   } else if (strcasecmp(argv[0],"--pre:cs:ncon")==0) {
	  options->csNcon = 0;
	  return 1;
   }  else if (strcasecmp(argv[0],"-pre:cs:ncon:min")==0) {
	  if (argv[1]==NULL) return -3;
	  aux1 = atoi(argv[1]);
	  if ( aux1 < 0 ) return -2;
	  else if ( aux1 < 2 ) {
		  options->csNcon = 0;
	  } else {
		  options->csNconMin = -1 * ( aux1 - 1 );
		  options->csNcon = 1;
	  }
	  return 2;
   } else if (strcasecmp(argv[0],"-pre:cs:li")==0) {
		sopt->csLI = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--pre:cs:li")==0) {
		sopt->csLI = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-pre:cs:li:min")==0) {
		if (argv[1]==NULL) return -3;
		sprintf(auxstr2,"%sINFO WARNING Cycle-slip option '-pre:cs:li:min' is deprecated\n",sopt->deprecatedMessages);
		sprintf(sopt->deprecatedMessages,"%s",auxstr2);
		options->deprecatedMode = 1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:li:maxjump")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if ( auxd <= 0. ) return -2;
		options->csLImaxjump = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:li:max")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if ( auxd <= 0. ) return -2;
		options->csLImax = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:li:t0")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if ( auxd <= 0. ) return -2;
		options->csLIt = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:li:samples")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if ( aux1 <= 0 ) return -2;
		options->csLIsamples = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:bw")==0) {
		sopt->csBW = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--pre:cs:bw")==0) {
		sopt->csBW = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-pre:cs:bw:min")==0) {
		if (argv[1]==NULL) return -3;
		sprintf(auxstr2,"%sINFO WARNING Cycle-slip option '-pre:cs:bw:min' is deprecated\n",sopt->deprecatedMessages);
		sprintf(sopt->deprecatedMessages,"%s",auxstr2);
		options->deprecatedMode = 1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:bw:max")==0) {
		if (argv[1]==NULL) return -3;
		sprintf(auxstr2,"%sINFO WARNING Cycle-slip option '-pre:cs:bw:max' is deprecated\n",sopt->deprecatedMessages);
		sprintf(sopt->deprecatedMessages,"%s",auxstr2);
		options->deprecatedMode = 1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:bw:siginit")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if ( auxd <= 0. ) return -2;
		options->csBWInitStd = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:bw:sigmin")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if ( auxd <= 0. ) return -2;
		options->csBWmin = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:bw:timewindow")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if ( aux1 <= 0 ) return -2;
		options->csBWwindow = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:bw:kfactor")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if ( auxd <= 0. ) return -2;
		options->csBWkfactor = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:bw:slope")==0) {
		if (argv[1]==NULL) return -3;
		sprintf(auxstr2,"%sINFO WARNING Cycle-slip option '-pre:cs:bw:slope' is deprecated, the updated one is '-pre:cs:bw:kfactor'. It has been set to its default value\n",sopt->deprecatedMessages);
		sprintf(sopt->deprecatedMessages,"%s",auxstr2);
		options->deprecatedMode = 1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:bw:samples")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if ( aux1 <= 0 ) return -2;
		options->csBWsamples = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:l1c1")==0) {
		sopt->csL1C1 = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--pre:cs:l1c1")==0) {
		sopt->csL1C1 = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-pre:cs:l1c1:unconcheck")==0) {
		options->csUnconsistencyCheck = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--pre:cs:l1c1:unconcheck")==0) {
		options->csUnconsistencyCheck = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-pre:cs:l1c1:kfactor")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if ( auxd <= 0. ) return -2;
		options->csL1C1kfactor = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:l1c1:unconcheck:th")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if (auxd <=0. ) return -2;
		options->csUnconsistencyCheck = 1;
		options->csUnconsistencyCheckThreshold = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:l1c1:slope")==0) {
		if (argv[1]==NULL) return -3;
		sprintf(auxstr2,"%sINFO WARNING Cycle-slip option '-pre:cs:l1c1:slope' is deprecated, the updated one is '-pre:cs:l1c1:kfactor'. It has been set to its default value\n",sopt->deprecatedMessages);
		sprintf(sopt->deprecatedMessages,"%s",auxstr2);
		options->deprecatedMode = 1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:l1c1:window")==0) {
		if (argv[1]==NULL) return -3;
		sprintf(auxstr2,"%sINFO WARNING Cycle-slip option '-pre:cs:l1c1:window' is deprecated, the updated one is '-pre:cs:l1c1:timewindow'. It has been set to its default value\n",sopt->deprecatedMessages);
		sprintf(sopt->deprecatedMessages,"%s",auxstr2);
		options->deprecatedMode = 1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:l1c1:max")==0) {
		if (argv[1]==NULL) return -3;
		sprintf(auxstr2,"%sINFO WARNING Cycle-slip option '-pre:cs:l1c1:max' is deprecated\n",sopt->deprecatedMessages);
		sprintf(sopt->deprecatedMessages,"%s",auxstr2);
		options->deprecatedMode = 1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:l1c1:timewindow")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if ( aux1 <= 0 ) return -2;
		options->csL1C1window = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:l1c1:init")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if ( auxd <= 0. ) return -2;
		options->csL1C1init = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:cs:l1c1:samples")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if ( aux1 <= 0 ) return -2;
		options->csL1C1samples = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:setrectype")==0) {
		if (argv[1]==NULL) return -3;
		if (strcasecmp(argv[1],"gpsrt")==0) {
			sopt->setRecType=rtNA;
		} else if (strcasecmp(argv[1],"0")==0) {
			sopt->setRecType=rtUNKNOWN;
		} else if (strcasecmp(argv[1],"1")==0) {
			sopt->setRecType=rtCROSS;
		} else if (strcasecmp(argv[1],"2")==0) {
			sopt->setRecType=rtNOP1;
		} else if (strcasecmp(argv[1],"3")==0) {
			sopt->setRecType=rtNOMINAL;
		} else return -2;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:meas")==0) {
		if (argv[1]==NULL) return -3;
		if (strcasecmp(argv[1],"pseudorange")==0) {
			sopt->navObservables = NOpseudorange;
		} else if (strcasecmp(argv[1],"carrierphase")==0) {
			sopt->navObservables = NOcarrierphase;
		} else return -2;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:select")==0) {
		if (argv[1]==NULL) return -3;
		sopt->totalFilterMeasurements = atoi(argv[1]);
		if (sopt->totalFilterMeasurements<=0) return -2;
		for (i=0;i<sopt->totalFilterMeasurements;i++) {
			if(i>=MAX_FILTER_MEASUREMENTS) break; //This is to avoid buffer overflow
			if (argv[2+i]==NULL) return -3;
			if(strlen(argv[2+i])>9) return -2; //Invalid measurement, as it has the name too long
			strcpy(auxstr,argv[2+i]);
			for(j=0;j<strlen(auxstr);j++) {
				c=toupper(auxstr[j]); //Transform to upper case characters
				auxstr[j]=c;
			}
			sopt->measurement[i] = measstr2meastype(auxstr);
			if (sopt->measurement[i] == NA) {
				if(strlen(argv[2+i])>MAX_INPUT_LINE-1) return -4;
				strcpy (argv[1],argv[2+i]); // This is for a proper error control
				return -2;
			}
			//sopt->smoothWith[i] = -1;
		}
		return 2+sopt->totalFilterMeasurements;
	} else if (strcasecmp(argv[0],"-pre:starttime")==0||strcasecmp(argv[0],"-pre:endtime")==0) {
		if (argv[1]==NULL||argv[2]==NULL) return -3;
		//Check date format
		if (strchr(argv[2],':')!=NULL) {
			//Time has ":" symbol. 
			if (strlen(argv[2])!=8) {
				strcpy (argv[1],argv[2]); // This is for a proper error control
				return -2;
			}
			//Check that input date has correct length
			if (strchr(argv[1],'/')!=NULL) {
				if (strlen(argv[1])!=10) return -2;
			} else {
				if (strlen(argv[1])!=8) return -2;
			}
			getstr(auxstr,argv[1],0,4);
			aux1 = atoi(auxstr);
			if (aux1<1970) return -2;
			tm.tm_year=aux1-1900;
			if (strchr(argv[1],'/')!=NULL) {
				//Date has "/" symbol. It is YYYY/MM/DD HH:MM:SS format
				getstr(auxstr,argv[1],5,2);
			} else {
				getstr(auxstr,argv[1],4,2);
			}
			aux1=atoi(auxstr);
			if (aux1<1|| aux1>12) return -2;
			tm.tm_mon=aux1-1;
			if (strchr(argv[1],'/')!=NULL) {
				//Date has "/" symbol. It is YYYY/MM/DD HH:MM:SS format
				getstr(auxstr,argv[1],8,2);
			} else {
				getstr(auxstr,argv[1],6,2);
			}
			aux1=atoi(auxstr);
			if (aux1<1|| aux1>31) return -2;
			tm.tm_mday = aux1;
			//Get hour in HH:MM:SS format
			getstr(auxstr,argv[2],0,2);
			aux1=atoi(auxstr);
			if (aux1<0|| aux1>24) {
				strcpy (argv[1],argv[2]); // This is for a proper error control
				return -2;
			}
			tm.tm_hour = aux1;
			getstr(auxstr,argv[2],3,2);
			aux1=atoi(auxstr);
			if (aux1<0|| aux1>60) {
				strcpy (argv[1],argv[2]); // This is for a proper error control
				return -2;
			}
			tm.tm_min  = aux1;
			getstr(auxstr,argv[2],6,2);
			aux1=atoi(auxstr);
			if (aux1<0|| aux1>60) {
				strcpy (argv[1],argv[2]); // This is for a proper error control
				return -2;
			}
			tm.tm_sec  = aux1;
			if (strcasecmp(argv[0],"-pre:starttime")==0) {
				options->StartEpoch.MJDN=MJDN(&tm);
				options->StartEpoch.SoD=(double)(tm.tm_hour*3600 + tm.tm_min*60 + tm.tm_sec);
				if(options->StartEpoch.SoD>=86400.) {
					options->StartEpoch.MJDN--;
					options->StartEpoch.SoD-=86400.;
				}
			} else {
				options->EndEpoch.MJDN=MJDN(&tm);
				options->EndEpoch.SoD=(double)(tm.tm_hour*3600 + tm.tm_min*60 + tm.tm_sec);
				if(options->EndEpoch.SoD>=86400.) {
					options->EndEpoch.MJDN--;
					options->EndEpoch.SoD-=86400.;
				}
			}
		} else {
			if (strchr(argv[1],'/')!=NULL) {
				//Time is in Year/DoY SoD format
				aux1=strlen(argv[1]);
				if (aux1<6 || aux1>8) return -2;
				getstr(auxstr,argv[1],0,4);
				aux1=atoi(auxstr);
				if(aux1<1970) return -2;
				aux2=atoi(&argv[1][5]);
				if(aux2<1||aux2>366) return -2;
				auxd=atof(argv[2]);
				if(auxd<0.||auxd>86400.) {
					strcpy (argv[1],argv[2]); // This is for a proper error control
					return -2;
				}
				if (strcasecmp(argv[0],"-pre:starttime")==0) {
					options->StartEpoch.MJDN=(int)yeardoy2MJDN(aux1,aux2,auxd);
					options->StartEpoch.SoD=auxd;
					if(options->StartEpoch.SoD>=86400.) {
						options->StartEpoch.MJDN--;
						options->StartEpoch.SoD-=86400.;
					}
				} else {
					options->EndEpoch.MJDN=(int)yeardoy2MJDN(aux1,aux2,auxd);
					options->EndEpoch.SoD=auxd;
					if(options->EndEpoch.SoD>=86400.) {
						options->EndEpoch.MJDN--;
						options->EndEpoch.SoD-=86400.;
					}
				}
			} else {
				//Time is in GPSWeek SoW format
				aux1=atoi(argv[1]);
				if(aux1<1) return -2;
				auxd=atof(argv[2]);
				if(auxd<0.||auxd>604800.) {
					strcpy (argv[1],argv[2]); // This is for a proper error control
					return -2;
				}
				if (strcasecmp(argv[0],"-pre:starttime")==0) {
					options->StartEpoch=gpsws2ttime(aux1,auxd);
				} else {
					options->EndEpoch=gpsws2ttime(aux1,auxd);
				}
			}
		}
		return 3;
	} else if (strcasecmp(argv[0],"-pre:sat")==0) {
		if (argv[1]==NULL) return -3;
		aux1=0;
		aux2=0;
		if (argv[1][0]=='+') {
			aux1=1;
			aux2=1;
		} else if (argv[1][0]=='-') {
			aux1=0;
			aux2=1;
		}
		if (checkConstellationChar(argv[1][aux2])==0) return -2;
		aux3=gnsschar2gnsstype(argv[1][aux2]);
		//Check if a range is given
		p=strchr(&argv[1][aux2+1],'-');
		if (p==NULL) {
			//No range given
			aux4 = atoi(&argv[1][aux2+1]);
			if (aux4<0 || aux4>=MAX_SATELLITES_PER_GNSS) return -2;
			aux5=-1;
		} else {
			//Range given
			*p='\0';//Temporary truncate argv[1] to get the first PRN number
			aux4 = atoi(&argv[1][aux2+1]);
			if (aux4<0 || aux4>=MAX_SATELLITES_PER_GNSS) return -2;
			*p='-';
			p++;
			aux5=atoi(p);
			if (aux5<=0 || aux5>=MAX_SATELLITES_PER_GNSS || aux5<aux4) return -2;
		}
		if(aux4==0) {
			for (i=0;i<MAX_SATELLITES_PER_GNSS;i++) {
				options->includeSatellite[aux3][i] = aux1;
			}
		} else if (aux5!=-1) {
			for (i=aux4;i<=aux5;i++) {
				options->includeSatellite[aux3][i] = aux1;
			}
		} else {
			options->includeSatellite[aux3][aux4] = aux1;
		}
		return 2;
	} else if (strcasecmp(argv[0],"-pre:GEOexclude")==0) {
		if (argv[1]==NULL) return -3;
		p2=argv[1];
		p=strchr(argv[1],',');
		while(p!=NULL) {
			*p='\0';
			aux1 = atoi(p2);
			if (aux1<MINGEOPRN || aux1>MAXGEOPRN) return -2;
			options->GEOPRNunsel[aux1]=1;
			*p=',';
			p2=p+1;
			p=strchr(p2,',');
		}
		aux1 = atoi(p2);
		if (aux1<MINGEOPRN || aux1>MAXGEOPRN) return -2;
		options->GEOPRNunsel[aux1]=1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:GEOsel")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<0) return -2;
		else if ( (aux1>2 && aux1<MINGEOPRN) || aux1>MAXGEOPRN) return -2;
		else options->GEOPRN=aux1;
		if(aux1==0)  options->mixedGEOdata=1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:SmoothMin")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<0) return -2;
		options->excludeSmoothingConvergence = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:dgnss:smoothMin")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<0) return -2;
		options->excludeSmoothingConvergenceTime = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:SNR")==0) {
		options->SNRfilter=1;
		return 1;
	} else if (strcasecmp(argv[0],"--pre:SNR")==0) {
		options->SNRfilter=0;
		return 1;
	} else if (strcasecmp(argv[0],"-pre:SNRsel")==0) {
		if (argv[1]==NULL || argv[2]==NULL) return -3;
		if (checkConstellationChar(argv[1][0])==0) return -2;
		aux1 = gnsschar2gnsstype(argv[1][0]);
		if(aux1<0||aux1>=MAX_GNSS) return -2;
		//Check if a range is given
		p=strchr(argv[1],'-');
		if (p==NULL) {
			//No range given
			aux2 = atoi(&argv[1][1]);
			if (aux2<0 || aux2>=MAX_SATELLITES_PER_GNSS) return -2;
			aux3=-1;
		} else {
			//Range given
			*p='\0';//Temporary truncate argv[1] to get the first PRN number
			aux2 = atoi(&argv[1][1]);
			if (aux2<0 || aux2>=MAX_SATELLITES_PER_GNSS) return -2;
			*p='-';
			p++;
			aux3=atoi(p);
			if (aux3<=0 || aux3>=MAX_SATELLITES_PER_GNSS) return -2;
		}
		
		auxd = atof(argv[2]);
		if(auxd<=0.) return -2;
		if(aux2==0) {
			for (i=0;i<MAX_SATELLITES_PER_GNSS;i++) {
				options->SNRvalues[aux1][i] = auxd;
			}
		} else if (aux3!=-1) {
			for (i=aux2;i<=aux3;i++) {
				options->SNRvalues[aux1][i] = auxd;
			}
		} else {
			options->SNRvalues[aux1][aux2] = auxd;
		}
		options->SNRfilter=1;
		return 3;
	} else if (strcasecmp(argv[0],"-pre:availf")==0) {
		if (argv[1]==NULL) return -3;
		if (argv[1][0]=='G') {
			aux1 = GPS;
			// If this option is set, only present frequencies will be set
			for (i=0;i<MAX_FREQUENCIES_PER_GNSS;i++) {
				options->usableFreq[aux1][i] = 0;
			}
			if (strlen(argv[1])<=1) return -2;
			for (i=1;i<strlen(argv[1]);i++) {
				auxstr[0] = argv[1][i];
				auxstr[1] = '\0';
				aux2 = atoi(auxstr);
				options->usableFreq[aux1][aux2] = 1;
			}
		} else return -2;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:smooth")==0) {
		if (argv[1]==NULL) return -3;
		options->smoothEpochs = atoi(argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"--pre:smooth")==0) {
		options->smoothEpochs = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-pre:smoothMeas")==0) {
		if (argv[1]==NULL) return -3;
		if (argv[2]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if (aux1<=0) {
			return -2;
		}
		if(aux1>MAX_FILTER_MEASUREMENTS) return -2;
		sopt->numsmoothWith++;
		sopt->smoothWith[aux1-1] = measstr2meastype(argv[2]);
		if (sopt->smoothWith[aux1-1] == NA) {
			if(strlen(argv[2])>MAX_INPUT_LINE-1) return -4;
			strcpy (argv[1],argv[2]); // This is for a proper error control
			return -2;
		}
		return 3;
	} else if (strcasecmp(argv[0],"-pre:setrecpos")==0) {
		if (argv[1]==NULL) return -3;
		if (strcasecmp(argv[1],"RINEX")==0) {
			options->receiverPositionSource = rpRINEX;
			options->recPosProvided=1;
			return 2;
		} else if (strcasecmp(argv[1],"SINEX")==0) {
			options->receiverPositionSource = rpSINEX;
			options->recPosProvided=1;
			return 2;
		} else if (strcasecmp(argv[1],"Set")==0||strcasecmp(argv[1],"SetCar")==0) {
			options->receiverPositionSource = rpSET;
			options->recPosProvided=1;
			for (i=0;i<3;i++) {
				if (argv[2+i]==NULL) return -3;
				auxd = atof(argv[2+i]);
				options->aprioriReceiverPosition[i] = auxd;
			}
			return 5;
		} else if (strcasecmp(argv[1],"SetGeod")==0) {
			options->receiverPositionSource = rpSET;
			options->recPosProvided=1;
			if (argv[2]==NULL||argv[3]==NULL||argv[4]==NULL) return -3;
			auxd = atof(argv[2]); //First value is longitude
			if(auxd<-180.||auxd>180.) {
				strcpy (argv[1],argv[2]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[1] = auxd*d2r;
			auxd = atof(argv[3]); //Second value is latitude
			if(auxd<-90.||auxd>90.) {
				strcpy (argv[1],argv[3]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[0] = auxd*d2r;
			auxd = atof(argv[4]); //Third value is height
			if(auxd<-10000) { //Height less than -10Km
				strcpy (argv[1],argv[4]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[2] = auxd;
			NEU2XYZ(options->aprioriReceiverPositionGeod,options->aprioriReceiverPosition);
			return 5;
		} else if (strcasecmp(argv[1],"SetRef")==0) {
			options->receiverPositionSource = rpSETREF;
			options->recPosProvided=1;
			return 2;
		} else if (strcasecmp(argv[1],"calculate")==0) {
			options->receiverPositionSource = rpCALCULATE;
			return 2;
		} else if (strcasecmp(argv[1],"calculateRINEX")==0) {
			options->receiverPositionSource = rpCALCULATERINEX;
			return 2;
		} else if (strcasecmp(argv[1],"calculateUSER")==0 || strcasecmp(argv[1],"calculateUSERCar")==0 ) {
			options->receiverPositionSource = rpCALCULATEUSER;
			for (i=0;i<3;i++) {
				if (argv[2+i]==NULL) return -3;
				auxd = atof(argv[2+i]);
				options->aprioriReceiverPosition[i] = auxd;
			}
			return 5;
		} else if (strcasecmp(argv[1],"calculateUSERGeod")==0) {
			options->receiverPositionSource = rpCALCULATEUSER;
			if (argv[2]==NULL||argv[3]==NULL||argv[4]==NULL) return -3;
			auxd = atof(argv[2]); //First value is longitude
			if(auxd<-180.||auxd>180.) {
				strcpy (argv[1],argv[2]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[1] = auxd*d2r;
			auxd = atof(argv[3]); ////Second value is latitude
			if(auxd<-90.||auxd>90.) {
				strcpy (argv[1],argv[3]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[0] = auxd*d2r;
			auxd = atof(argv[4]); //Third value is height
			if(auxd<-10000) { //Height less than -10Km
				strcpy (argv[1],argv[4]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[2] = auxd;
			NEU2XYZ(options->aprioriReceiverPositionGeod,options->aprioriReceiverPosition);
			return 5;
		} else if (strcasecmp(argv[1],"calculateRef")==0) {
			options->receiverPositionSource = rpCALCULATEREF;
			options->recPosProvided=1;
			return 2;
		} else if (strcasecmp(argv[1],"calculateRINEXRef")==0) {
			options->receiverPositionSource = rpCALCULATERINEXREF;
			options->recPosProvided=1;
			return 2;
		} else if (strcasecmp(argv[1],"calculateUSERRef")==0|| strcasecmp(argv[1],"calculateUSERCarRef")==0) {
			options->receiverPositionSource = rpCALCULATEUSERREF;
			options->recPosProvided=1;
			for (i=0;i<3;i++) {
				if (argv[2+i]==NULL) return -3;
				auxd = atof(argv[2+i]);
				options->aprioriReceiverPosition[i] = auxd;
			}
			return 5;
		} else if (strcasecmp(argv[1],"calculateUSERGeodRef")==0) {
			options->receiverPositionSource = rpCALCULATEUSERREF;
			options->recPosProvided=1;
			if (argv[2]==NULL||argv[3]==NULL||argv[4]==NULL) return -3;
			auxd = atof(argv[2]); //First value is longitude
			if(auxd<-180.||auxd>180.) {
				strcpy (argv[1],argv[2]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[1] = auxd*d2r;
			auxd = atof(argv[3]); //Second value is latitude
			if(auxd<-90.||auxd>90.) {
				strcpy (argv[1],argv[3]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[0] = auxd*d2r;
			auxd = atof(argv[4]); //Third value is height
			if(auxd<-10000) { //Height less than -10Km
				strcpy (argv[1],argv[4]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[2] = auxd;
			NEU2XYZ(options->aprioriReceiverPositionGeod,options->aprioriReceiverPosition);
			return 5;
		} else if (strcasecmp(argv[1],"RTCMbaseline")==0 || strcasecmp(argv[1],"DGNSSbaseline")==0) {
			options->receiverPositionSource = rpRTCMbaseline;
			return 2;
		} else if (strcasecmp(argv[1],"RTCMRinexRover")==0 || strcasecmp(argv[1],"DGNSSRinexRover")==0) {
			options->receiverPositionSource = rpRTCMRINEXROVER;
			options->recPosProvided=1;
			return 2;
		} else if (strcasecmp(argv[1],"RTCMRoverUSER")==0 || strcasecmp(argv[1],"DGNSSRoverUSER")==0 
				|| strcasecmp(argv[1],"RTCMRoverUSERCar")==0 || strcasecmp(argv[1],"DGNSSRoverUSERCar")==0) {
			options->receiverPositionSource = rpRTCMRoverUSER;
			options->recPosProvided=1;
			for (i=0;i<3;i++) {
				if (argv[2+i]==NULL) return -3;
				auxd = atof(argv[2+i]);
				options->aprioriReceiverPosition[i] = auxd;
			}
			return 5;
		} else if (strcasecmp(argv[1],"RTCMRoverUSERGeod")==0 || strcasecmp(argv[1],"DGNSSRoverUSERGeod")==0) {
			options->receiverPositionSource = rpRTCMRoverUSER;
			options->recPosProvided=1;
			if (argv[2]==NULL||argv[3]==NULL||argv[4]==NULL) return -3;
			auxd = atof(argv[2]); //First value is longitude
			if(auxd<-180.||auxd>180.) {
				strcpy (argv[1],argv[2]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[1] = auxd*d2r;
			auxd = atof(argv[3]); //Second value is latitude
			if(auxd<-90.||auxd>90.) {
				strcpy (argv[1],argv[3]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[0] = auxd*d2r;
			auxd = atof(argv[4]); //Third value is height
			if(auxd<-10000) { //Height less than -10Km
				strcpy (argv[1],argv[4]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[2] = auxd;
			NEU2XYZ(options->aprioriReceiverPositionGeod,options->aprioriReceiverPosition);
			return 5;
		} else if (strcasecmp(argv[1],"RTCMRoverUSERRef")==0 || strcasecmp(argv[1],"DGNSSRoverUSERRef")==0) {
			options->receiverPositionSource = rpRTCMRoverUSERREF;
			options->recPosProvided=1;
			return 2;
		} else if (strcasecmp(argv[1],"RTCMUserRoverRef")==0 || strcasecmp(argv[1],"DGNSSUserRoverRef")==0
				|| strcasecmp(argv[1],"RTCMUserCarRoverRef")==0 || strcasecmp(argv[1],"DGNSSUserCarRoverRef")==0) {
			options->receiverPositionSource = rpRTCMRefUSERRoverREF;
			options->recPosProvided=1;
			for (i=0;i<3;i++) {
				if (argv[2+i]==NULL) return -3;
				auxd = atof(argv[2+i]);
				options->ReferenceStationPosition[i] = auxd;
			}
			return 5;
		} else if (strcasecmp(argv[1],"RTCMUserGeodRoverRef")==0 || strcasecmp(argv[1],"DGNSSUserGeodRoverRef")==0) {
			options->receiverPositionSource = rpRTCMRefUSERRoverREF;
			options->recPosProvided=1;
			if (argv[2]==NULL||argv[3]==NULL||argv[4]==NULL) return -3;
			auxd = atof(argv[2]); //First value is longitude
			if(auxd<-180.||auxd>180.) {
				strcpy (argv[1],argv[2]); // This is for a proper error control
				return -2;
			}
			options->ReferenceStationPositionGeod[1] = auxd*d2r;
			auxd = atof(argv[3]); //Second value is latitude
			if(auxd<-90.||auxd>90.) {
				strcpy (argv[1],argv[3]); // This is for a proper error control
				return -2;
			}
			options->ReferenceStationPositionGeod[0] = auxd*d2r;
			auxd = atof(argv[4]); //Third value is height
			if(auxd<-10000) { //Height less than -10Km
				strcpy (argv[1],argv[4]); // This is for a proper error control
				return -2;
			}
			options->ReferenceStationPositionGeod[2] = auxd;
			NEU2XYZ(options->ReferenceStationPositionGeod,options->ReferenceStationPosition);
			return 5;
		} else if (strcasecmp(argv[1],"RTCMUserbaseline")==0 || strcasecmp(argv[1],"DGNSSUserbaseline")==0
				|| strcasecmp(argv[1],"RTCMUserCarbaseline")==0 || strcasecmp(argv[1],"DGNSSUserCarbaseline")==0) {
			options->receiverPositionSource = rpRTCMUserbaseline;
			for (i=0;i<3;i++) {
				if (argv[2+i]==NULL) return -3;
				auxd = atof(argv[2+i]);
				options->ReferenceStationPosition[i] = auxd;
			}
			return 5;
		} else if (strcasecmp(argv[1],"RTCMUserGeodbaseline")==0 || strcasecmp(argv[1],"DGNSSUserGeodbaseline")==0) {
			options->receiverPositionSource = rpRTCMUserbaseline;
			if (argv[2]==NULL||argv[3]==NULL||argv[4]==NULL) return -3;
			auxd = atof(argv[2]); //First value is longitude
			if(auxd<-180.||auxd>180.) {
				strcpy (argv[1],argv[2]); // This is for a proper error control
				return -2;
			}
			options->ReferenceStationPositionGeod[1] = auxd*d2r;
			auxd = atof(argv[3]); //Second value is latitude
			if(auxd<-90.||auxd>90.) {
				strcpy (argv[1],argv[3]); // This is for a proper error control
				return -2;
			}
			options->ReferenceStationPositionGeod[0] = auxd*d2r;
			auxd = atof(argv[4]); //Third value is height
			if(auxd<-10000) { //Height less than -10Km
				strcpy (argv[1],argv[4]); // This is for a proper error control
				return -2;
			}
			options->ReferenceStationPositionGeod[2] = auxd;
			NEU2XYZ(options->ReferenceStationPositionGeod,options->ReferenceStationPosition);
			return 5;
		} else if (strcasecmp(argv[1],"RTCMUserRinexRover")==0 || strcasecmp(argv[1],"DGNSSUserRinexRover")==0
				|| strcasecmp(argv[1],"RTCMUserCarRinexRover")==0 || strcasecmp(argv[1],"DGNSSUserCarRinexRover")==0) {
			options->receiverPositionSource = rpRTCMUserRINEXROVER;
			options->recPosProvided=1;
			for (i=0;i<3;i++) {
				if (argv[2+i]==NULL) return -3;
				auxd = atof(argv[2+i]);
				options->ReferenceStationPosition[i] = auxd;
			}
			return 5;
		} else if (strcasecmp(argv[1],"RTCMUserGeodRinexRover")==0 || strcasecmp(argv[1],"DGNSSUserGeodRinexRover")==0) {
			options->receiverPositionSource = rpRTCMUserRINEXROVER;
			options->recPosProvided=1;
			if (argv[2]==NULL||argv[3]==NULL||argv[4]==NULL) return -3;
			auxd = atof(argv[2]); //First value is longitude
			if(auxd<-180.||auxd>180.) {
				strcpy (argv[1],argv[2]); // This is for a proper error control
				return -2;
			}
			options->ReferenceStationPositionGeod[1] = auxd*d2r;
			auxd = atof(argv[3]); //Second value is latitude
			if(auxd<-90.||auxd>90.) {
				strcpy (argv[1],argv[3]); // This is for a proper error control
				return -2;
			}
			options->ReferenceStationPositionGeod[0] = auxd*d2r;
			auxd = atof(argv[4]); //Third value is height
			if(auxd<-10000) { //Height less than -10Km
				strcpy (argv[1],argv[4]); // This is for a proper error control
				return -2;
			}
			options->ReferenceStationPositionGeod[2] = auxd;
			NEU2XYZ(options->ReferenceStationPositionGeod,options->ReferenceStationPosition);
			return 5;
		} else if (strcasecmp(argv[1],"RTCMRefRoverUSER")==0 || strcasecmp(argv[1],"DGNSSRefRoverUSER")==0 
				|| strcasecmp(argv[1],"RTCMRefCarRoverUSERCar")==0 || strcasecmp(argv[1],"DGNSSRefCarRoverUSERCar")==0) {
			options->receiverPositionSource = rpRTCMRefRoverUSER;
			options->recPosProvided=1;
			for (i=0;i<3;i++) {
				if (argv[2+i]==NULL) return -3;
				auxd = atof(argv[2+i]);
				options->ReferenceStationPosition[i] = auxd;
			}
			for (i=0;i<3;i++) {
				if (argv[5+i]==NULL) return -3;
				auxd = atof(argv[5+i]);
				options->aprioriReceiverPosition[i] = auxd;
			}
			return 8;
		} else if (strcasecmp(argv[1],"RTCMRefGeodRoverUSERGeod")==0 || strcasecmp(argv[1],"DGNSSRefGeodRoverUSERGeod")==0) {
			options->receiverPositionSource = rpRTCMRefRoverUSER;
			options->recPosProvided=1;
			if (argv[2]==NULL||argv[3]==NULL||argv[4]==NULL) return -3;
			auxd = atof(argv[2]); //First value is longitude
			if(auxd<-180.||auxd>180.) {
				strcpy (argv[1],argv[2]); // This is for a proper error control
				return -2;
			}
			options->ReferenceStationPositionGeod[1] = auxd*d2r;
			auxd = atof(argv[3]); //Second value is latitude
			if(auxd<-90.||auxd>90.) {
				strcpy (argv[1],argv[3]); // This is for a proper error control
				return -2;
			}
			options->ReferenceStationPositionGeod[0] = auxd*d2r;
			auxd = atof(argv[4]); //Third value is height
			if(auxd<-10000) { //Height less than -10Km
				strcpy (argv[1],argv[4]); // This is for a proper error control
				return -2;
			}
			options->ReferenceStationPositionGeod[2] = auxd;
			NEU2XYZ(options->ReferenceStationPositionGeod,options->ReferenceStationPosition);
			if (argv[5]==NULL||argv[6]==NULL||argv[7]==NULL) return -3;
			auxd = atof(argv[5]); //First value is longitude
			if(auxd<-180.||auxd>180.) {
				strcpy (argv[1],argv[5]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[1] = auxd*d2r;
			auxd = atof(argv[6]); //Second value is latitude
			if(auxd<-90.||auxd>90.) {
				strcpy (argv[1],argv[6]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[0] = auxd*d2r;
			auxd = atof(argv[7]); //Third value is height
			if(auxd<-10000) { //Height less than -10Km
				strcpy (argv[1],argv[7]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[2] = auxd;
			NEU2XYZ(options->aprioriReceiverPositionGeod,options->aprioriReceiverPosition);
			return 8;
		} else if (strcasecmp(argv[1],"RTCMRefCarRoverUSERGeod")==0 || strcasecmp(argv[1],"DGNSSRefCarRoverUSERGeod")==0) {
			options->receiverPositionSource = rpRTCMRefRoverUSER;
			options->recPosProvided=1;
			for (i=0;i<3;i++) {
				if (argv[2+i]==NULL) return -3;
				auxd = atof(argv[2+i]);
				options->ReferenceStationPosition[i] = auxd;
			}
			if (argv[5]==NULL||argv[6]==NULL||argv[7]==NULL) return -3;
			auxd = atof(argv[5]); //First value is longitude
			if(auxd<-180.||auxd>180.) {
				strcpy (argv[1],argv[5]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[1] = auxd*d2r;
			auxd = atof(argv[6]); //Second value is latitude
			if(auxd<-90.||auxd>90.) {
				strcpy (argv[1],argv[6]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[0] = auxd*d2r;
			auxd = atof(argv[7]); //Third value is height
			if(auxd<-10000) { //Height less than -10Km
				strcpy (argv[1],argv[7]); // This is for a proper error control
				return -2;
			}
			options->aprioriReceiverPositionGeod[2] = auxd;
			NEU2XYZ(options->aprioriReceiverPositionGeod,options->aprioriReceiverPosition);
			return 8;
		} else if (strcasecmp(argv[1],"RTCMRefGeodRoverUSERCar")==0 || strcasecmp(argv[1],"DGNSSRefGeodRoverUSERCar")==0) {
			options->receiverPositionSource = rpRTCMRefRoverUSER;
			options->recPosProvided=1;
			if (argv[2]==NULL||argv[3]==NULL||argv[4]==NULL) return -3;
			auxd = atof(argv[2]); //First value is longitude
			if(auxd<-180.||auxd>180.) {
				strcpy (argv[1],argv[2]); // This is for a proper error control
				return -2;
			}
			options->ReferenceStationPositionGeod[1] = auxd*d2r;
			auxd = atof(argv[3]); //Second value is latitude
			if(auxd<-90.||auxd>90.) {
				strcpy (argv[1],argv[3]); // This is for a proper error control
				return -2;
			}
			options->ReferenceStationPositionGeod[0] = auxd*d2r;
			auxd = atof(argv[4]); //Third value is height
			if(auxd<-10000) { //Height less than -10Km
				strcpy (argv[1],argv[4]); // This is for a proper error control
				return -2;
			}
			options->ReferenceStationPositionGeod[2] = auxd;
			NEU2XYZ(options->ReferenceStationPositionGeod,options->ReferenceStationPosition);
			for (i=0;i<3;i++) {
				if (argv[5+i]==NULL) return -3;
				auxd = atof(argv[5+i]);
				options->aprioriReceiverPosition[i] = auxd;
			}
			return 8;
		} else {  // X Y Z (rpSET)
			options->receiverPositionSource = rpSET;
			options->recPosProvided=1;
			for (i=0;i<3;i++) {
				if (argv[1+i]==NULL) return -3;
				auxd = atof(argv[1+i]);
				options->aprioriReceiverPosition[i] = auxd;
			}
			return 4;
		}
	} else if (strcasecmp(argv[0],"-pre:refpos:deg")==0) {
		if (argv[1]==NULL) return -3;
		aux1=atoi(argv[1]);
		if (aux1<0) return -2;
		options->RefDegInterp=aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-pre:dgnss:excludeSmoothingConvergenceUser")==0) {
		options->excludeSmoothingConvergenceUser = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--pre:dgnss:excludeSmoothingConvergenceUser")==0) {
		options->excludeSmoothingConvergenceUser = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-pre:dgnss:excludeSmoothingConvergenceRef")==0) {
		options->excludeSmoothingConvergenceRef = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--pre:dgnss:excludeSmoothingConvergenceRef")==0) {
		options->excludeSmoothingConvergenceRef = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:iono")==0) {
		if (argv[1]==NULL) {return -3;}
		if (strcasecmp(argv[1],"no")==0) {
			sopt->ionoModel = NoIono;
		} else if (strcasecmp(argv[1],"Klobuchar")==0) {
			sopt->ionoModel = Klobuchar;
		} else if (strcasecmp(argv[1],"BeiDou")==0) {
			sopt->ionoModel = BeiDou;
		} else if (strcasecmp(argv[1],"IONEX")==0) {
			sopt->ionoModel = IONEX;
		} else if (strcasecmp(argv[1],"FPPP")==0) {
			sopt->ionoModel = FPPP;
		} else if (strcasecmp(argv[1],"NeQuick")==0) {
			sopt->ionoModel = neQuick;
		} else if (strcasecmp(argv[1],"SBAS")==0) {
			sopt->ionoModel = SBASiono;
		} else return -2;
		return 2;
	} else if (strcasecmp(argv[0],"--model:iono")==0) {
		sopt->ionoModel = NoIono;
		return 1;
	} else if (strcasecmp(argv[0],"-model:ionoRMS")==0) {
		if (argv[1]==NULL) {return -3;}
		options->ionoRMS = atof(argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-model:trop")==0||strcasecmp(argv[0],"-model:tropo")==0) {
		sopt->troposphericCorrection = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:trop")==0||strcasecmp(argv[0],"--model:tropo")==0) {
		sopt->troposphericCorrection = 0;
		return 1;

	} else if (strcasecmp(argv[0],"-model:trop:nominal")==0) {
		if (argv[1]==NULL) return -3;
		if (strcasecmp(argv[1],"Simple")==0) {
			sopt->tropNominal = SimpleNominal;
		} else if (strcasecmp(argv[1],"UNB3")==0) {
			sopt->tropNominal = UNB3Nominal;
		} else if (strcasecmp(argv[1],"TropoGal")==0) {
			sopt->tropNominal = TropoGalileo;
		} else return -2;
		return 2;

	} else if (strcasecmp(argv[0],"-model:trop:mapping")==0) {
		if (argv[1]==NULL) return -3;
		if (strcasecmp(argv[1],"Simple")==0) {
			sopt->tropMapping = SimpleMapping;
		} else if (strcasecmp(argv[1],"Niell")==0) {
			sopt->tropMapping = NiellMapping;
		} else return -2;
		return 2;

	} else if (strcasecmp(argv[0],"-model:satclocks")==0) {
		options->satelliteClockCorrection = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:satclocks")==0) {
		options->satelliteClockCorrection = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:relclock")==0) {
		options->relativisticCorrection = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:relclock")==0) {
		options->relativisticCorrection = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:satmovinflight")==0) {
		options->timeTrans = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:satmovinflight")==0) {
		options->timeTrans = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:earthrotinflight")==0) {
		options->earthRotation = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:earthrotinflight")==0) {
		options->earthRotation = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:satphasecenter")==0) {
		options->satellitePhaseCenter = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:satphasecenter")==0) {
		options->satellitePhaseCenter = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:satphasevar")==0) {
		options->satellitePhaseVar = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:satphasevar")==0) {
		options->satellitePhaseVar = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:recphasecenter")==0) {
		if (argv[1]==NULL) return -3;
		if (strcasecmp(argv[1],"no")==0) {
			options->antennaData = adNONE;
			return 2;
		} else if (strcasecmp(argv[1],"ANTEX")==0) {
			options->antennaData = adANTEX;
			return 2;
		} else {
			options->antennaData = adSET;
			aux1 = atoi(argv[1]);
			if (aux1==0) return -2;
			for (i=0;i<3;i++) {
				if (argv[2+i]==NULL) return -3;
				auxd = atof(argv[2+i]);
				if (auxd==0 && *argv[2+i]!='0') {
					if(strlen(argv[2+i])>MAX_INPUT_LINE-1) return -4;
					strcpy(argv[1],argv[2+i]);
					return -2;
				}
				options->receiverPCO[aux1][i] = auxd;
			}
			return 5;
		}
	} else if (strcasecmp(argv[0],"--model:recphasecenter")==0) {
		options->antennaData = adNONE;
		return 1;
	} else if (strcasecmp(argv[0],"-model:recphasevar")==0) {
		options->receiverPhaseVar = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:recphasevar")==0) {
		options->receiverPhaseVar = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:strictradome")==0 || strcasecmp(argv[0],"-model:radomestrict")==0) {
		options->strictradome = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:strictradome")==0 || strcasecmp(argv[0],"--model:radomestrict")==0) {
		options->strictradome = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:arp")==0) {
		if (argv[1]==NULL) return -3;
		if (strcasecmp(argv[1],"no")==0) {
			options->ARPData = arpNONE;
			return 2;
		} else if (strcasecmp(argv[1],"RINEX")==0) {
			options->ARPData = arpRINEX;
			return 2;
		} else {
			options->ARPData = arpSET;
			for (i=0;i<3;i++) {
				if (argv[1+i]==NULL) return -3;
				auxd = atof(argv[1+i]);
				options->receiverARP[i] = auxd;
			}
		}
		return 4;
	} else if (strcasecmp(argv[0],"--model:arp")==0) {
		options->ARPData = arpNONE;
		return 1;
	} else if (strcasecmp(argv[0],"-model:dcb:p1c1")==0) {
		if (argv[1]==NULL) return -3;
		if (strcasecmp(argv[1],"no")==0) {
			sopt->p1c1dcbModel = p1c1NONE;
			options->flexibleC1P1 = 0;
		} else if (strcasecmp(argv[1],"flexible")==0) {
			sopt->p1c1dcbModel = p1c1FLEXIBLE;
			options->flexibleC1P1 = 1;
		} else if (strcasecmp(argv[1],"strict")==0) {
			sopt->p1c1dcbModel = p1c1STRICT;
			options->flexibleC1P1 = 1;
		} else {
			return -2;
		}
		return 2;
	} else if (strcasecmp(argv[0],"--model:dcb:p1c1")==0) {
		sopt->p1c1dcbModel = p1c1NONE;
		options->flexibleC1P1 = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:dcb:p1p2")==0) {
		if (argv[1]==NULL) return -3;
		if (strcasecmp(argv[1],"no")==0) {
			sopt->p1p2dcbModel = p1p2NONE;
		} else if (strcasecmp(argv[1],"RINEX")==0) {
			sopt->p1p2dcbModel = p1p2RINEX;
		} else if (strcasecmp(argv[1],"DCB")==0) {
			sopt->p1p2dcbModel = p1p2DCB;
		} else if (strcasecmp(argv[1],"IONEX")==0) {
			sopt->p1p2dcbModel = p1p2IONEX;
		} else if (strcasecmp(argv[1],"FPPP")==0) {
			sopt->p1p2dcbModel = p1p2FPPP;
		} else {
			return -2;
		}
		return 2;
	} else if (strcasecmp(argv[0],"--model:dcb:p1p2")==0) {
		options->p1p2dcbModel = p1p2NONE;
		return 1;
	} else if (strcasecmp(argv[0],"-model:windup")==0) {
		options->windUpCorrection = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:windup")==0) {
		options->windUpCorrection = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:solidtides")==0) {
		options->solidTidesCorrection = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:solidtides")==0) {
		options->solidTidesCorrection = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:relpath")==0) {
		options->gravitationalCorrection = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:relpath")==0) {
		options->gravitationalCorrection = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:orbit:deg")==0 || strcasecmp(argv[0],"-model:orb:deg")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<=0) return -2;
		options->orbitInterpolationDegree = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-model:clock:deg")==0 || strcasecmp(argv[0],"-model:clk:deg")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<0) return -2;
		options->clockInterpolationDegree = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-model:orbmaxgaps")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<0) return -2;
		options->OrbitsMaxGaps = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"--model:orbmaxgaps")==0) {
		options->OrbitsMaxGaps = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:clkmaxgaps")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<0) return -2;
		options->ClocksMaxGaps = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"--model:clkmaxgaps")==0) {
		options->ClocksMaxGaps = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:orbtotmaxgaps")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<0) return -2;
		options->OrbitsToTMaxGaps = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"--model:orbtotmaxgaps")==0) {
		options->OrbitsToTMaxGaps = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:clktotmaxgaps")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<0) return -2;
		options->ClocksToTMaxGaps = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"--model:clktotmaxgaps")==0) {
		options->ClocksToTMaxGaps = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:orbprevsample")==0) {
		options->LastSamplePrevDayOrb = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:orbprevsample")==0) {
		options->LastSamplePrevDayOrb = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:clkprevsample")==0) {
		options->LastSamplePrevDayClk = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:clkprevsample")==0) {
		options->LastSamplePrevDayClk = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:satellitehealth")==0) {
		options->satelliteHealth = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:satellitehealth")==0) {
		options->satelliteHealth = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:brdctranstime")==0) {
		options->brdcBlockTransTime = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:brdctranstime")==0) {
		options->brdcBlockTransTime = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:maxurabrdc")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if(auxd<=0) return -2;
		options->MaxURABroadcast = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"--model:maxurabrdc")==0) {
		options->MaxURABroadcast = 9999999.;
		return 1;
	} else if (strcasecmp(argv[0],"-model:sbasmaritime")==0) {
		options->NoDeltaUDRE = 1;
		options->NoMT10 = 1;
		options->SBASmaritime=1;
		return 1;
	} else if (strcasecmp(argv[0],"-model:alarmmsgtype2")==0) {
		options->alarmmessageastype2 = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:alarmmsgtype2")==0) {
		options->alarmmessageastype2 = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:ignoretype0")==0) {
		options->usetype0messages = 0;
		return 1;
	} else if (strcasecmp(argv[0],"--model:ignoretype0")==0) {
		options->usetype0messages = 1;
		return 1;
	} else if (strcasecmp(argv[0],"-model:udreithreshold")==0) {
		if (argv[1]==NULL) return -3;
		aux1=atoi(argv[1]);
		if (aux1<1||aux1>13) return -2;
		options->UDREIthreshold=aux1;
		return 2;
	} else if (strcasecmp(argv[0],"--model:udreithreshold")==0) {
		options->UDREIthreshold = 999999;
		return 1;
	} else if (strcasecmp(argv[0],"-model:sigfltnomt10offset")==0) {
		if (argv[1]==NULL) return -3;
		auxd=atof(argv[1]);
		if (auxd<0.) return -2;
		options->SigmaOffsetNoMT10=auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-model:SBASmode")==0) {
		if (argv[1]==NULL) return -3;
		if (strcasecmp(argv[1],"PA")==0) {
			options->precisionapproach = PAMODE;
			options->UserForcedNPA=0;
		} else if (strcasecmp(argv[1],"NPA")==0) {
			options->precisionapproach = NPAMODE;
			options->UserForcedNPA=1;
		} else return -2;
		return 2;
	} else if (strcasecmp(argv[0],"-model:maintainGEO")==0) {
		options->MaintainGEO = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:maintainGEO")==0) {
		options->MaintainGEO = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:GEOswitch")==0) {
		options->switchGEO = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:GEOswitch")==0) {
		options->switchGEO = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:SBASmodeswitch")==0) {
		options->switchmode = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:SBASmodeswitch")==0) {
		options->switchmode = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:GEOfallback")==0) {
		options->GEOfallback = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:GEOfallback")==0) {
		options->GEOfallback = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:GEOacqtime")==0 || strcasecmp(argv[0],"-model:GEOadqtime")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<0) return -2;
		options->adquisitiontime = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-model:switchtime")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<0) return -2;
		options->minimumswitchtime = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-model:SBAStmoutPA")==0) {
		if (argv[1]==NULL || argv[2]==NULL ) return -3;
		aux1 = atoi(argv[1]);
		aux2 = atoi(argv[2]);
		if(aux1<0 || aux1>63) return -2;
		if(aux2<0) return -2;
		options->usertmout[PAMODE][aux1]=aux2;
		return 3;
	} else if (strcasecmp(argv[0],"-model:SBAStmoutNPA")==0) {
		if (argv[1]==NULL || argv[2]==NULL ) return -3;
		aux1 = atoi(argv[1]);
		aux2 = atoi(argv[2]);
		if(aux1<0 || aux1>63) return -2;
		if(aux2<0) return -2;
		options->usertmout[NPAMODE][aux1]=aux2;
		return 3;
	} else if (strcasecmp(argv[0],"-model:SBAStmout")==0) {
		if (argv[1]==NULL || argv[2]==NULL ) return -3;
		aux1 = atoi(argv[1]);
		aux2 = atoi(argv[2]);
		if(aux1<0 || aux1>63) return -2;
		if(aux2<0) return -2;
		options->usertmout[PAMODE][aux1]=aux2;
		options->usertmout[NPAMODE][aux1]=aux2;
		return 3;
	} else if (strcasecmp(argv[0],"-model:SBAStmoutFCPA")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<0) return -2;
		options->FCtmout[1]=aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-model:SBAStmoutFCNPA")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<0) return -2;
		options->FCtmout[0]=aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-model:SBAStmoutFC")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<0) return -2;
		options->FCtmout[0]=aux1;
		options->FCtmout[1]=aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-model:SBAStmoutRRCPA")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<0) return -2;
		options->RRCtmout[1]=aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-model:SBAStmoutRRCNPA")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<0) return -2;
		options->RRCtmout[0]=aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-model:SBAStmoutRRC")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<0) return -2;
		options->RRCtmout[0]=aux1;
		options->RRCtmout[1]=aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-model:mixedGEO")==0) {
		options->mixedGEOdata = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:mixedGEO")==0) {
		options->mixedGEOdata = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:initcoordNPA")==0) {
		options->initcoordNPA = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:initcoordNPA")==0) {
		options->initcoordNPA = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:SBASreceiver")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if(aux1<0 || aux1>4) return -2;
		options->airborneReceiverType = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-model:sigmpath")==0) {
		if (argv[1]==NULL||argv[2]==NULL) return -3;
		auxd = atof(argv[1]);
		if(auxd<0.) return -2;
		options->sigma2multipath[0]=auxd;
		auxd = atof(argv[2]);
		if(auxd<0.) return -2;
		options->sigma2multipath[1]=auxd;
		options->airborneReceiverType=0;
		return 3;
	} else if (strcasecmp(argv[0],"-model:sigdiv")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if(auxd<0.) return -2;
		options->sigma2divergence=auxd*auxd;
		options->airborneReceiverType=0;
		return 2;
	} else if (strcasecmp(argv[0],"-model:signoise")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if (auxd<0.) return -2;
		options->sigma2noise=auxd*auxd;
		options->airborneReceiverType=0;
		return 2;
	} else if (strcasecmp(argv[0],"-model:nofastcor")==0) {
		options->NoFastCorrection = 1;
		options->NoRRCCorrection = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:nofastcor")==0) {
		options->NoFastCorrection = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:norrccor")==0) {
		options->NoRRCCorrection = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:norrccor")==0) {
		options->NoRRCCorrection = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:noslowcor")==0) {
		options->NoSlowCorrection = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:noslowcor")==0) {
		options->NoSlowCorrection = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:noionocor")==0) {
		options->NoIonoCorrection = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:noionocor")==0) {
		options->NoIonoCorrection = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:nofastsigma")==0) {
		options->NoFastSigma = 1;
		options->NoFastDeg = 1;
		options->NoRRCSigma = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:nofastsigma")==0) {
		options->NoFastSigma = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:nofastdeg")==0) {
		options->NoFastDeg = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:nofastdeg")==0) {
		options->NoFastDeg = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:norrcsigma")==0) {
		options->NoRRCSigma = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:norrcsigma")==0) {
		options->NoRRCSigma= 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:noslowsigma")==0) {
		options->NoSlowSigma = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:noslowsigma")==0) {
		options->NoSlowSigma = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:noionosigma")==0) {
		options->NoIonoSigma = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:noionosigma")==0) {
		options->NoIonoSigma = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:notroposigma")==0) {
		options->NoTropoSigma = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:notroposigma")==0) {
		options->NoTropoSigma = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:noenroutesigma")==0) {
		options->NoEnRouteSigma = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:noenroutesigma")==0) {
		options->NoEnRouteSigma = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:nodeltaudre")==0 || strcasecmp(argv[0],"-model:nomt2728")==0) {
		options->NoDeltaUDRE = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:nodeltaudre")==0 || strcasecmp(argv[0],"--model:nomt2728")==0) {
		options->NoDeltaUDRE = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:nomt10")==0) {
		options->NoMT10 = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:nomt10")==0) {
		options->NoMT10 = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:dgnss:sigmainflation")==0) {
		options->sigmaInflation = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--model:dgnss:sigmainflation")==0) {
		options->sigmaInflation = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-model:dgnss:maxage")==0) {
		if ( argv[1] == NULL ) return -3;
		auxd = atof(argv[1]);
		if ( auxd < 0. ) return -2;
		options->maxAgeDGNSS = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-model:dgnss:maxcorrval")==0) {
		if ( argv[1] == NULL ) return -3;
		auxd = atof(argv[1]);
		if ( auxd < 0. ) return -2;
		options->maxDGNSSPRC = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:trop")==0||strcasecmp(argv[0],"-filter:tropo")==0) {
		sopt->estimateTroposphere = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--filter:trop")==0||strcasecmp(argv[0],"--filter:tropo")==0) {
		sopt->estimateTroposphere = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-filter:nav")==0) {
		if (argv[1]==NULL) return -3;
		if (strcasecmp(argv[1],"static")==0) {
			sopt->navKinematics = NKstatic;
		} else if (strcasecmp(argv[1],"kinematic")==0) {
			sopt->navKinematics = NKkinematic;
		} else return -2;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:fixedweight")==0) {
		if (argv[1]==NULL || argv[2]==NULL) return -3;
		aux1 = atoi(argv[1]);
		if (aux1<0 || aux1>MAX_FILTER_MEASUREMENTS) {
			return -2;
		}
		auxd = atof(argv[2]);
		if(strcasecmp(argv[2],"URA")==0) {
			auxd=-2;
		} else if (auxd<0) {
			if(strlen(argv[2])>MAX_INPUT_LINE-1) return -4;
			strcpy (argv[1],argv[2]);
			return -2;
		}
		if (aux1==0) {
			for(i=0;i<MAX_GNSS;i++) {
				for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
					for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
						sopt->weightMode[i][j][k]=FixedWeight;
						sopt->WeightConstantsValues[i][j][k][0] = auxd;
						sopt->WeightConstantsValues[i][j][k][1] = 0.;
						sopt->WeightConstantsValues[i][j][k][2] = 0.;
					}
				}
			}
		} else {
			for(i=0;i<MAX_GNSS;i++) {
				for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
					sopt->weightMode[i][j][aux1-1]=FixedWeight;
					sopt->WeightConstantsValues[i][j][aux1-1][0] = auxd;
					sopt->WeightConstantsValues[i][j][aux1-1][1] = 0.;
					sopt->WeightConstantsValues[i][j][aux1-1][2] = 0.;
				}
			}
		}
		return 3;
	} else if (strcasecmp(argv[0],"-filter:fixedweightsat")==0) {
		if (argv[1]==NULL || argv[2]==NULL||argv[3]==NULL) return -3;
		if (checkConstellationChar(argv[1][0])==0) return -2;
		aux1 = gnsschar2gnsstype(argv[1][0]);
		if(aux1<0||aux1>=MAX_GNSS) return -2;
		//Check if a range is given
		p=strchr(argv[1],'-');
		if (p==NULL) {
			//No range given
			aux2 = atoi(&argv[1][1]);
			if (aux2<0 || aux2>=MAX_SATELLITES_PER_GNSS) return -2;
			aux3=-1;
		} else {
			//Range given
			*p='\0';//Temporary truncate argv[1] to get the first PRN number
			aux2 = atoi(&argv[1][1]);
			if (aux2<0 || aux2>=MAX_SATELLITES_PER_GNSS) return -2;
			*p='-';
			p++;
			aux3=atoi(p);
			if (aux3<=0 || aux3>=MAX_SATELLITES_PER_GNSS || aux3<aux2 ) return -2;
		}
		aux4 = atoi(argv[2]);
		if (aux4<0 || aux4>MAX_FILTER_MEASUREMENTS) {
            if(strlen(argv[2])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[2]);
            return -2;
		}
		auxd=atof(argv[3]);
		if(strcasecmp(argv[3],"URA")==0) {
			auxd=-2;
		} else if (auxd<0) {
			if(strlen(argv[3])>MAX_INPUT_LINE-1) return -4;
			strcpy (argv[1],argv[3]);
			return -2;
		}
		if(aux2==0) {
			if (aux4==0) {
				for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
					for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
						sopt->weightMode[aux1][j][k]=FixedWeight;
						sopt->WeightConstantsValues[aux1][j][k][0] = auxd;
						sopt->WeightConstantsValues[aux1][j][k][1] = 0.;
						sopt->WeightConstantsValues[aux1][j][k][2] = 0.;
					}
				}
			} else {
				for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
					sopt->weightMode[aux1][j][aux4-1]=FixedWeight;
					sopt->WeightConstantsValues[aux1][j][aux4-1][0] = auxd;
					sopt->WeightConstantsValues[aux1][j][aux4-1][1] = 0.;
					sopt->WeightConstantsValues[aux1][j][aux4-1][2] = 0.;
				}
			}
		} else if (aux3!=-1) {
			for (j=aux2;j<=aux3;j++) {
				if (aux4==0) {
					for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
						sopt->weightMode[aux1][j][k]=FixedWeight;
						sopt->WeightConstantsValues[aux1][j][k][0] = auxd;
						sopt->WeightConstantsValues[aux1][j][k][1] = 0.;
						sopt->WeightConstantsValues[aux1][j][k][2] = 0.;
					}
				} else {
					sopt->weightMode[aux1][aux2][aux4-1]=FixedWeight;
					sopt->WeightConstantsValues[aux1][j][aux4-1][0] = auxd;
					sopt->WeightConstantsValues[aux1][j][aux4-1][1] = 0.;
					sopt->WeightConstantsValues[aux1][j][aux4-1][2] = 0.;
				}
			}
		} else {
			if (aux4==0) {
				for (j=0;j<MAX_FILTER_MEASUREMENTS;j++) {
					sopt->weightMode[aux1][aux2][j]=FixedWeight;
					sopt->WeightConstantsValues[aux1][aux2][j][0] = auxd;
					sopt->WeightConstantsValues[aux1][aux2][j][1] = 0.;
					sopt->WeightConstantsValues[aux1][aux2][j][2] = 0.;
				}
			} else {
				sopt->weightMode[aux1][aux2][aux4-1]=FixedWeight;
				sopt->WeightConstantsValues[aux1][aux2][aux4-1][0] = auxd;
				sopt->WeightConstantsValues[aux1][aux2][aux4-1][1] = 0.;
				sopt->WeightConstantsValues[aux1][aux2][aux4-1][2] = 0.;
			}
		}
		return 4;
    } else if (strcasecmp(argv[0],"-filter:elevweight")==0) {
        if (argv[1]==NULL || argv[2]==NULL||argv[3]==NULL||argv[4]==NULL) return -3;
        aux1 = atoi(argv[1]);
        if (aux1<0 || aux1>MAX_FILTER_MEASUREMENTS) {
            return -2;
        }
        auxd = atof(argv[2]);
		if(strcasecmp(argv[2],"URA")==0) {
			auxd=-2;
		} else if (auxd<0) {
            if(strlen(argv[2])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[2]);
            return -2;
        }
        auxd2 = atof(argv[3]);
        if (auxd2<0) {
            if(strlen(argv[3])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[3]);
            return -2;
        }
        auxd3 = atof(argv[4]);
        if (auxd3<=0) {
            if(strlen(argv[4])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[4]);
            return -2;
        }
        if (aux1==0) {
            for(i=0;i<MAX_GNSS;i++) {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
                        sopt->weightMode[i][j][k]=ElevationWeight;
                        sopt->WeightConstantsValues[i][j][k][0] = auxd;
                        sopt->WeightConstantsValues[i][j][k][1] = auxd2;
                        sopt->WeightConstantsValues[i][j][k][2] = auxd3*d2r; //Transform to radians
                    }
                }
            }
        } else {
            for(i=0;i<MAX_GNSS;i++) {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    sopt->weightMode[i][j][aux1-1]=ElevationWeight;
                    sopt->WeightConstantsValues[i][j][aux1-1][0] = auxd;
                    sopt->WeightConstantsValues[i][j][aux1-1][1] = auxd2;
                    sopt->WeightConstantsValues[i][j][aux1-1][2] = auxd3*d2r; //Transform to radians
                }
            }
        }
        return 5;
    } else if (strcasecmp(argv[0],"-filter:elevweightsat")==0) {
        if (argv[1]==NULL || argv[2]==NULL||argv[3]==NULL||argv[4]==NULL||argv[5]==NULL) return -3;
		if (checkConstellationChar(argv[1][0])==0) return -2;
        aux1 = gnsschar2gnsstype(argv[1][0]);
        if(aux1<0||aux1>=MAX_GNSS) return -2;
		//Check if a range is given
		p=strchr(argv[1],'-');
		if (p==NULL) {
			//No range given
			aux2 = atoi(&argv[1][1]);
			if (aux2<0 || aux2>=MAX_SATELLITES_PER_GNSS) return -2;
			aux3=-1;
		} else {
			//Range given
			*p='\0';//Temporary truncate argv[1] to get the first PRN number
			aux2 = atoi(&argv[1][1]);
			if (aux2<0 || aux2>=MAX_SATELLITES_PER_GNSS) return -2;
			*p='-';
			p++;
			aux3=atoi(p);
			if (aux3<=0 || aux3>=MAX_SATELLITES_PER_GNSS || aux3<aux2 ) return -2;
		}
        aux4 = atoi(argv[2]);
        if (aux4<0 || aux4>MAX_FILTER_MEASUREMENTS) {
            if(strlen(argv[2])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[2]);
            return -2;
		}
        auxd=atof(argv[3]);
		if(strcasecmp(argv[3],"URA")==0) {
			auxd=-2;
		} else if (auxd<0) {
            if(strlen(argv[3])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[3]);
            return -2;
        }
        auxd2 = atof(argv[4]);
        if (auxd2<0) {
            if(strlen(argv[4])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[4]);
            return -2;
        }
        auxd3 = atof(argv[5]);
        if (auxd3<=0) {
            if(strlen(argv[5])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[5]);
            return -2;
        }
        if(aux2==0) {
            if (aux4==0) {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
                        sopt->weightMode[aux1][j][k]=ElevationWeight;
                        sopt->WeightConstantsValues[aux1][j][k][0] = auxd;
                        sopt->WeightConstantsValues[aux1][j][k][1] = auxd2;
                        sopt->WeightConstantsValues[aux1][j][k][2] = auxd3*d2r; //Transform to radians
                    }
                }
            } else {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    sopt->weightMode[aux1][j][aux4-1]=ElevationWeight;
                    sopt->WeightConstantsValues[aux1][j][aux4-1][0] = auxd;
                    sopt->WeightConstantsValues[aux1][j][aux4-1][1] = auxd2;
                    sopt->WeightConstantsValues[aux1][j][aux4-1][2] = auxd3*d2r; //Transform to radians
                }
            }
		} else if (aux3!=-1) {
			for (j=aux2;j<=aux3;j++) {
				if (aux4==0) {
					for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
						sopt->weightMode[aux1][j][k]=ElevationWeight;
						sopt->WeightConstantsValues[aux1][j][k][0] = auxd;
						sopt->WeightConstantsValues[aux1][j][k][1] = auxd2;
						sopt->WeightConstantsValues[aux1][j][k][2] = auxd3*d2r; //Transform to radians
					}
				} else {
					sopt->weightMode[aux1][j][aux4-1]=ElevationWeight;
					sopt->WeightConstantsValues[aux1][j][aux4-1][0] = auxd;
					sopt->WeightConstantsValues[aux1][j][aux4-1][1] = auxd2;
					sopt->WeightConstantsValues[aux1][j][aux4-1][2] = auxd3*d2r; //Transform to radians
				}
			}
        } else {
            if (aux4==0) {
                for (j=0;j<MAX_FILTER_MEASUREMENTS;j++) {
                    sopt->weightMode[aux1][aux2][j]=ElevationWeight;
                    sopt->WeightConstantsValues[aux1][aux2][j][0] = auxd;
                    sopt->WeightConstantsValues[aux1][aux2][j][1] = auxd2;
                    sopt->WeightConstantsValues[aux1][aux2][j][2] = auxd3*d2r; //Transform to radians
                }
            } else {
                sopt->weightMode[aux1][aux2][aux4-1]=ElevationWeight;
                sopt->WeightConstantsValues[aux1][aux2][aux4-1][0] = auxd;
                sopt->WeightConstantsValues[aux1][aux2][aux4-1][1] = auxd2;
                sopt->WeightConstantsValues[aux1][aux2][aux4-1][2] = auxd3*d2r; //Transform to radians
            }
        }
        return 6;
    } else if (strcasecmp(argv[0],"-filter:sinelevweight")==0) {
        if (argv[1]==NULL || argv[2]==NULL||argv[3]==NULL) return -3;
        aux1 = atoi(argv[1]);
        if (aux1<0 || aux1>MAX_FILTER_MEASUREMENTS) {
            return -2;
        }
        auxd = atof(argv[2]);
		if(strcasecmp(argv[2],"URA")==0) {
			auxd=-2;
		} else if (auxd<0) {
            if(strlen(argv[2])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[2]);
            return -2;
        }
        auxd2 = atof(argv[3]);
        if (auxd2<0) {
            if(strlen(argv[3])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[3]);
            return -2;
        }
        if (aux1==0) {
            for(i=0;i<MAX_GNSS;i++) {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
                        sopt->weightMode[i][j][k]=Elevation2Weight;
                        sopt->WeightConstantsValues[i][j][k][0] = auxd;
                        sopt->WeightConstantsValues[i][j][k][1] = auxd2;
                        sopt->WeightConstantsValues[i][j][k][2] = 0.;
                    }
                }
            }
        } else {
            for(i=0;i<MAX_GNSS;i++) {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    sopt->weightMode[i][j][aux1-1]=Elevation2Weight;
                    sopt->WeightConstantsValues[i][j][aux1-1][0] = auxd;
                    sopt->WeightConstantsValues[i][j][aux1-1][1] = auxd2;
                    sopt->WeightConstantsValues[i][j][aux1-1][2] = 0.;
                }
            }
        }
        return 4;
    } else if (strcasecmp(argv[0],"-filter:sinelevweightsat")==0) {
        if (argv[1]==NULL || argv[2]==NULL||argv[3]==NULL||argv[4]==NULL) return -3;
		if (checkConstellationChar(argv[1][0])==0) return -2;
        aux1 = gnsschar2gnsstype(argv[1][0]);
        if(aux1<0||aux1>=MAX_GNSS) return -2;
		//Check if a range is given
		p=strchr(argv[1],'-');
		if (p==NULL) {
			//No range given
			aux2 = atoi(&argv[1][1]);
			if (aux2<0 || aux2>=MAX_SATELLITES_PER_GNSS) return -2;
			aux3=-1;
		} else {
			//Range given
			*p='\0';//Temporary truncate argv[1] to get the first PRN number
			aux2 = atoi(&argv[1][1]);
			if (aux2<0 || aux2>=MAX_SATELLITES_PER_GNSS) return -2;
			*p='-';
			p++;
			aux3=atoi(p);
			if (aux3<=0 || aux3>=MAX_SATELLITES_PER_GNSS || aux3<aux2 ) return -2;
		}
        aux4 = atoi(argv[2]);
        if (aux4<0 || aux4>MAX_FILTER_MEASUREMENTS) {
            if(strlen(argv[2])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[2]);
            return -2;
		}
        auxd=atof(argv[3]);
		if(strcasecmp(argv[3],"URA")==0) {
			auxd=-2;
		} else if (auxd<0) {
            if(strlen(argv[3])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[3]);
            return -2;
        }
        auxd2 = atof(argv[4]);
        if (auxd2<0) {
            if(strlen(argv[4])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[4]);
            return -2;
        }
        if(aux2==0) {
            if (aux4==0) {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
                        sopt->weightMode[aux1][j][k]=Elevation2Weight;
                        sopt->WeightConstantsValues[aux1][j][k][0] = auxd;
                        sopt->WeightConstantsValues[aux1][j][k][1] = auxd2;
                        sopt->WeightConstantsValues[aux1][j][k][2] = 0.;
                    }
                }
            } else {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    sopt->weightMode[aux1][j][aux4-1]=Elevation2Weight;
                    sopt->WeightConstantsValues[aux1][j][aux4-1][0] = auxd;
                    sopt->WeightConstantsValues[aux1][j][aux4-1][1] = auxd2;
                    sopt->WeightConstantsValues[aux1][j][aux4-1][2] = 0.;
                }
            }
		} else if (aux3!=-1) {
			for (j=aux2;j<=aux3;j++) {
				if (aux4==0) {
					for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
						sopt->weightMode[aux1][j][k]=Elevation2Weight;
						sopt->WeightConstantsValues[aux1][j][k][0] = auxd;
						sopt->WeightConstantsValues[aux1][j][k][1] = auxd2;
						sopt->WeightConstantsValues[aux1][j][k][2] = 0.;
					}
				} else {
					sopt->weightMode[aux1][j][aux4-1]=Elevation2Weight;
					sopt->WeightConstantsValues[aux1][j][aux4-1][0] = auxd;
					sopt->WeightConstantsValues[aux1][j][aux4-1][1] = auxd2;
					sopt->WeightConstantsValues[aux1][j][aux4-1][2] = 0.;
				}
			}
        } else {
            if (aux4==0) {
                for (j=0;j<MAX_FILTER_MEASUREMENTS;j++) {
                    sopt->weightMode[aux1][aux2][j]=Elevation2Weight;
                    sopt->WeightConstantsValues[aux1][aux2][j][0] = auxd;
                    sopt->WeightConstantsValues[aux1][aux2][j][1] = auxd2;
                    sopt->WeightConstantsValues[aux1][aux2][j][2] = 0.;
                }
            } else {
                sopt->weightMode[aux1][aux2][aux4-1]=Elevation2Weight;
                sopt->WeightConstantsValues[aux1][aux2][aux4-1][0] = auxd;
                sopt->WeightConstantsValues[aux1][aux2][aux4-1][1] = auxd2;
                sopt->WeightConstantsValues[aux1][aux2][aux4-1][2] = 0.;
            }
        }
        return 5;
    } else if (strcasecmp(argv[0],"-filter:snrweight")==0) {
        if (argv[1]==NULL || argv[2]==NULL||argv[3]==NULL) return -3;
        aux1 = atoi(argv[1]);
        if (aux1<0 || aux1>MAX_FILTER_MEASUREMENTS) {
            return -2;
        }
        auxd = atof(argv[2]);
		if(strcasecmp(argv[2],"URA")==0) {
			auxd=-2;
		} else if (auxd<0) {
            if(strlen(argv[2])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[2]);
            return -2;
        }
        auxd2 = atof(argv[3]);
        if (auxd2<0) {
            if(strlen(argv[3])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[3]);
            return -2;
        }
        if (aux1==0) {
            for(i=0;i<MAX_GNSS;i++) {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
                        sopt->weightMode[i][j][k]=SNRWeight;
                        sopt->WeightConstantsValues[i][j][k][0] = auxd;
                        sopt->WeightConstantsValues[i][j][k][1] = auxd2;
                        sopt->WeightConstantsValues[i][j][k][2] = 0.;
                    }
                }
            }
        } else {
            for(i=0;i<MAX_GNSS;i++) {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    sopt->weightMode[i][j][aux1-1]=SNRWeight;
                    sopt->WeightConstantsValues[i][j][aux1-1][0] = auxd;
                    sopt->WeightConstantsValues[i][j][aux1-1][1] = auxd2;
                    sopt->WeightConstantsValues[i][j][aux1-1][2] = 0.;
                }
            }
        }
        return 4;
    } else if (strcasecmp(argv[0],"-filter:snrweightsat")==0) {
        if (argv[1]==NULL || argv[2]==NULL||argv[3]==NULL||argv[4]==NULL) return -3;
		if (checkConstellationChar(argv[1][0])==0) return -2;
        aux1 = gnsschar2gnsstype(argv[1][0]);
        if(aux1<0||aux1>=MAX_GNSS) return -2;
		//Check if a range is given
		p=strchr(argv[1],'-');
		if (p==NULL) {
			//No range given
			aux2 = atoi(&argv[1][1]);
			if (aux2<0 || aux2>=MAX_SATELLITES_PER_GNSS) return -2;
			aux3=-1;
		} else {
			//Range given
			*p='\0';//Temporary truncate argv[1] to get the first PRN number
			aux2 = atoi(&argv[1][1]);
			if (aux2<0 || aux2>=MAX_SATELLITES_PER_GNSS) return -2;
			*p='-';
			p++;
			aux3=atoi(p);
			if (aux3<=0 || aux3>=MAX_SATELLITES_PER_GNSS || aux3<aux2 ) return -2;
		}
        aux4 = atoi(argv[2]);
        if (aux4<0 || aux4>MAX_FILTER_MEASUREMENTS) {
            if(strlen(argv[2])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[2]);
            return -2;
		}
        auxd=atof(argv[3]);
		if(strcasecmp(argv[3],"URA")==0) {
			auxd=-2;
		} else if (auxd<0) {
            if(strlen(argv[3])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[3]);
            return -2;
        }
        auxd2 = atof(argv[4]);
        if (auxd2<0) {
            if(strlen(argv[4])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[4]);
            return -2;
        }
        if(aux2==0) {
            if (aux4==0) {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
                        sopt->weightMode[aux1][j][k]=SNRWeight;
                        sopt->WeightConstantsValues[aux1][j][k][0] = auxd;
                        sopt->WeightConstantsValues[aux1][j][k][1] = auxd2;
                        sopt->WeightConstantsValues[aux1][j][k][2] = 0.;
                    }
                }
            } else {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    sopt->weightMode[aux1][j][aux4-1]=SNRWeight;
                    sopt->WeightConstantsValues[aux1][j][aux4-1][0] = auxd;
                    sopt->WeightConstantsValues[aux1][j][aux4-1][1] = auxd2;
                    sopt->WeightConstantsValues[aux1][j][aux4-1][2] = 0.;
                }
            }
		} else if (aux3!=-1) {
			for (j=aux2;j<=aux3;j++) {
				if (aux4==0) {
					for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
						sopt->weightMode[aux1][j][k]=SNRWeight;
						sopt->WeightConstantsValues[aux1][j][k][0] = auxd;
						sopt->WeightConstantsValues[aux1][j][k][1] = auxd2;
						sopt->WeightConstantsValues[aux1][j][k][2] = 0.;
					}
				} else {
					sopt->weightMode[aux1][j][aux4-1]=SNRWeight;
					sopt->WeightConstantsValues[aux1][j][aux4-1][0] = auxd;
					sopt->WeightConstantsValues[aux1][j][aux4-1][1] = auxd2;
					sopt->WeightConstantsValues[aux1][j][aux4-1][2] = 0.;
				}
			}
        } else {
            if (aux4==0) {
                for (j=0;j<MAX_FILTER_MEASUREMENTS;j++) {
                    sopt->weightMode[aux1][aux2][j]=SNRWeight;
                    sopt->WeightConstantsValues[aux1][aux2][j][0] = auxd;
                    sopt->WeightConstantsValues[aux1][aux2][j][1] = auxd2;
                    sopt->WeightConstantsValues[aux1][aux2][j][2] = 0.;
                }
            } else {
                sopt->weightMode[aux1][aux2][aux4-1]=SNRWeight;
                sopt->WeightConstantsValues[aux1][aux2][aux4-1][0] = auxd;
                sopt->WeightConstantsValues[aux1][aux2][aux4-1][1] = auxd2;
                sopt->WeightConstantsValues[aux1][aux2][aux4-1][2] = 0.;
            }
        }
        return 5;
    } else if (strcasecmp(argv[0],"-filter:snrelevweight")==0) {
        if (argv[1]==NULL || argv[2]==NULL||argv[3]==NULL) return -3;
        aux1 = atoi(argv[1]);
        if (aux1<0 || aux1>MAX_FILTER_MEASUREMENTS) {
            return -2;
        }
        auxd = atof(argv[2]);
		if(strcasecmp(argv[2],"URA")==0) {
			auxd=-2;
		} else if (auxd<0) {
            if(strlen(argv[2])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[2]);
            return -2;
        }
        auxd2 = atof(argv[3]);
        if (auxd2<0) {
            if(strlen(argv[3])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[3]);
            return -2;
        }
        if (aux1==0) {
            for(i=0;i<MAX_GNSS;i++) {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
                        sopt->weightMode[i][j][k]=SNRElevWeight;
                        sopt->WeightConstantsValues[i][j][k][0] = auxd;
                        sopt->WeightConstantsValues[i][j][k][1] = auxd2;
                        sopt->WeightConstantsValues[i][j][k][2] = 0.;
                    }
                }
            }
        } else {
            for(i=0;i<MAX_GNSS;i++) {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    sopt->weightMode[i][j][aux1-1]=SNRElevWeight;
                    sopt->WeightConstantsValues[i][j][aux1-1][0] = auxd;
                    sopt->WeightConstantsValues[i][j][aux1-1][1] = auxd2;
                    sopt->WeightConstantsValues[i][j][aux1-1][2] = 0.;
                }
            }
        }
        return 4;
    } else if (strcasecmp(argv[0],"-filter:snrelevweightsat")==0) {
        if (argv[1]==NULL || argv[2]==NULL||argv[3]==NULL||argv[4]==NULL) return -3;
		if (checkConstellationChar(argv[1][0])==0) return -2;
        aux1 = gnsschar2gnsstype(argv[1][0]);
        if(aux1<0||aux1>=MAX_GNSS) return -2;
		//Check if a range is given
		p=strchr(argv[1],'-');
		if (p==NULL) {
			//No range given
			aux2 = atoi(&argv[1][1]);
			if (aux2<0 || aux2>=MAX_SATELLITES_PER_GNSS) return -2;
			aux3=-1;
		} else {
			//Range given
			*p='\0';//Temporary truncate argv[1] to get the first PRN number
			aux2 = atoi(&argv[1][1]);
			if (aux2<0 || aux2>=MAX_SATELLITES_PER_GNSS) return -2;
			*p='-';
			p++;
			aux3=atoi(p);
			if (aux3<=0 || aux3>=MAX_SATELLITES_PER_GNSS || aux3<aux2 ) return -2;
		}
        aux4 = atoi(argv[2]);
        if (aux4<0 || aux4>MAX_FILTER_MEASUREMENTS) {
            if(strlen(argv[2])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[2]);
            return -2;
		}
        auxd=atof(argv[3]);
		if(strcasecmp(argv[3],"URA")==0) {
			auxd=-2;
		} else if (auxd<0) {
            if(strlen(argv[3])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[3]);
            return -2;
        }
        auxd2 = atof(argv[4]);
        if (auxd2<0) {
            if(strlen(argv[4])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[4]);
            return -2;
        }
        if(aux2==0) {
            if (aux3==0) {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
                        sopt->weightMode[aux1][j][k]=SNRElevWeight;
                        sopt->WeightConstantsValues[aux1][j][k][0] = auxd;
                        sopt->WeightConstantsValues[aux1][j][k][1] = auxd2;
                        sopt->WeightConstantsValues[aux1][j][k][2] = 0.;
                    }
                }
            } else {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    sopt->weightMode[aux1][j][aux4-1]=SNRElevWeight;
                    sopt->WeightConstantsValues[aux1][j][aux4-1][0] = auxd;
                    sopt->WeightConstantsValues[aux1][j][aux4-1][1] = auxd2;
                    sopt->WeightConstantsValues[aux1][j][aux4-1][2] = 0.;
                }
            }
		} else if (aux4!=-1) {
			for (j=aux2;j<=aux3;j++) {
				if (aux4==0) {
					for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
						sopt->weightMode[aux1][j][k]=SNRElevWeight;
						sopt->WeightConstantsValues[aux1][j][k][0] = auxd;
						sopt->WeightConstantsValues[aux1][j][k][1] = auxd2;
						sopt->WeightConstantsValues[aux1][j][k][2] = 0.;
					}
				} else {
					sopt->weightMode[aux1][j][aux4-1]=SNRElevWeight;
					sopt->WeightConstantsValues[aux1][j][aux4-1][0] = auxd;
					sopt->WeightConstantsValues[aux1][j][aux4-1][1] = auxd2;
					sopt->WeightConstantsValues[aux1][j][aux4-1][2] = 0.;
				}
			}
        } else {
            if (aux4==0) {
                for (j=0;j<MAX_FILTER_MEASUREMENTS;j++) {
                    sopt->weightMode[aux1][aux2][j]=SNRElevWeight;
                    sopt->WeightConstantsValues[aux1][aux2][j][0] = auxd;
                    sopt->WeightConstantsValues[aux1][aux2][j][1] = auxd2;
                    sopt->WeightConstantsValues[aux1][aux2][j][2] = 0.;
                }
            } else {
                sopt->weightMode[aux1][aux2][aux4-1]=SNRElevWeight;
                sopt->WeightConstantsValues[aux1][aux2][aux4-1][0] = auxd;
                sopt->WeightConstantsValues[aux1][aux2][aux4-1][1] = auxd2;
                sopt->WeightConstantsValues[aux1][aux2][aux4-1][2] = 0.;
            }
        }
        return 5;
    } else if (strcasecmp(argv[0],"-filter:snrweight:comb")==0) {
        if (argv[1]==NULL || argv[2]==NULL) return -3;
        aux1 = atoi(argv[1]);
        if (aux1<0 || aux1>MAX_FILTER_MEASUREMENTS) {
            return -2;
        }
		auxd=0.;
		auxd2=0.;
		if (strcasecmp(argv[2],"SNRi")==0) {
			aux2=SNRWeightCombi;
		} else if (strcasecmp(argv[2],"SNRj")==0) {
			aux2=SNRWeightCombj;
		} else if (strcasecmp(argv[2],"MaxSNR")==0) {
			aux2=SNRWeightCombMax;
		} else if (strcasecmp(argv[2],"MinSNR")==0) {
			aux2=SNRWeightCombMin;
		} else if (strcasecmp(argv[2],"MeanSNR")==0) {
			aux2=SNRWeightCombMean;
		} else {
			aux2=SNRWeightCombUser;
			auxd=atof(argv[2]);
			auxd2=1-auxd;
			if (auxd<0. || auxd>1.) {
	            if(strlen(argv[2])>MAX_INPUT_LINE-1) return -4;
    	        strcpy (argv[1],argv[2]);
	            return -2;
			} 
		}
        if(aux1==0) {
            for(i=0;i<MAX_GNSS;i++) {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
                        sopt->SNRweightComb[i][j][k]=aux2;
                        sopt->SNRweightCombVal[i][j][k][0]=auxd;
                        sopt->SNRweightCombVal[i][j][k][1]=auxd2;
                    }
                }
            }
        } else {
            for(i=0;i<MAX_GNSS;i++) {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    sopt->SNRweightComb[i][j][aux1-1]=aux2;
					sopt->SNRweightCombVal[i][j][aux1-1][0]=auxd;
					sopt->SNRweightCombVal[i][j][aux1-1][1]=auxd2;
                }
            }
        }
		return 3;
    } else if (strcasecmp(argv[0],"-filter:snrweight:combsat")==0) {
        if (argv[1]==NULL || argv[2]==NULL||argv[3]==NULL) return -3;
		if (checkConstellationChar(argv[1][0])==0) return -2;
        aux1 = gnsschar2gnsstype(argv[1][0]);
        if(aux1<0||aux1>=MAX_GNSS) return -2;
		//Check if a range is given
		p=strchr(argv[1],'-');
		if (p==NULL) {
			//No range given
			aux2 = atoi(&argv[1][1]);
			if (aux2<0 || aux2>=MAX_SATELLITES_PER_GNSS) return -2;
			aux3=-1;
		} else {
			//Range given
			*p='\0';//Temporary truncate argv[1] to get the first PRN number
			aux2 = atoi(&argv[1][1]);
			if (aux2<0 || aux2>=MAX_SATELLITES_PER_GNSS) return -2;
			*p='-';
			p++;
			aux3=atoi(p);
			if (aux3<=0 || aux3>=MAX_SATELLITES_PER_GNSS || aux3<aux2 ) return -2;
		}
        aux4 = atoi(argv[2]);
        if (aux4<0 || aux4>MAX_FILTER_MEASUREMENTS) {
            if(strlen(argv[2])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[2]);
            return -2;
        }
		auxd=0.;
		auxd2=0.;
		if (strcasecmp(argv[3],"SNRi")==0) {
			aux5=SNRWeightCombi;
		} else if (strcasecmp(argv[3],"SNRj")==0) {
			aux5=SNRWeightCombj;
		} else if (strcasecmp(argv[3],"MaxSNR")==0) {
			aux5=SNRWeightCombMax;
		} else if (strcasecmp(argv[3],"MinSNR")==0) {
			aux5=SNRWeightCombMin;
		} else if (strcasecmp(argv[3],"MeanSNR")==0) {
			aux5=SNRWeightCombMean;
        } else {
			auxd=atof(argv[3]);
			auxd2=1.-auxd;
			if (auxd<0. || auxd>1.) {
				if(strlen(argv[3])>MAX_INPUT_LINE-1) return -4;
				strcpy (argv[1],argv[3]);
				return -2;
			} 
        }
        if(aux2==0) {
            if (aux4==0) {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
                            sopt->SNRweightComb[aux1][j][k]=aux5;
							sopt->SNRweightCombVal[aux1][j][k][0]=auxd;
							sopt->SNRweightCombVal[aux1][j][k][1]=auxd2;
                    }
                }
            } else {
                for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
                    sopt->SNRweightComb[aux1][j][aux4-1]=aux5;
					sopt->SNRweightCombVal[aux1][j][aux4-1][0]=auxd;
					sopt->SNRweightCombVal[aux1][j][aux4-1][1]=auxd2;
                }
            }
		} else if (aux3!=-1) {
			for (j=aux2;j<=aux3;j++) {
				if(aux4==0) {
					for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
						sopt->SNRweightComb[aux1][j][k]=aux5;
						sopt->SNRweightCombVal[aux1][j][k][0]=auxd;
						sopt->SNRweightCombVal[aux1][j][k][1]=auxd2;
					}
				} else {
					sopt->SNRweightComb[aux1][j][aux4-1]=aux5;
					sopt->SNRweightCombVal[aux1][j][aux4-1][0]=auxd;
					sopt->SNRweightCombVal[aux1][j][aux4-1][1]=auxd2;
				}
			}
        } else {
            if(aux4==0) {
                for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
                    sopt->SNRweightComb[aux1][aux2][k]=aux5;
					sopt->SNRweightCombVal[aux1][aux2][k][0]=auxd;
					sopt->SNRweightCombVal[aux1][aux2][k][1]=auxd2;
                }
            } else {
                sopt->SNRweightComb[aux1][aux2][aux4-1]=aux5;
				sopt->SNRweightCombVal[aux1][aux2][aux4-1][0]=auxd;
				sopt->SNRweightCombVal[aux1][aux2][aux4-1][1]=auxd2;
            }
        }
        return 4;
	} else if (strcasecmp(argv[0],"-filter:sbasdgnssweightmode")==0) {
        if (argv[1]==NULL || argv[2]==NULL) return -3;
        aux1 = atoi(argv[1]);
        if (aux1<0 || aux1>MAX_FILTER_MEASUREMENTS) {
            return -2;
        }
		if (strcasecmp(argv[2],"ComputedOnly")==0) {
			aux2=ComputedOnly;
		} else if (strcasecmp(argv[2],"ComputedPlusUser")==0 || strcasecmp(argv[3],"Computed+User")==0) {
			aux2=ComputedPlusUser;
		} else if (strcasecmp(argv[2],"UserOnly")==0) {
			aux2=UserOnly;
		} else {
            if(strlen(argv[2])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[2]);
            return -2;
		}
		if(aux1==0) {
			for(i=0;i<MAX_GNSS;i++) {
				for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
					for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
						sopt->CombineWeightMode[i][j][k]=aux2;
					}
				}
			}
		} else {
			for(i=0;i<MAX_GNSS;i++) {
				for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
					sopt->CombineWeightMode[i][j][aux1-1]=aux2;
				}
			}
		}
		return 3;
    } else if (strcasecmp(argv[0],"-filter:sbasdgnssweightmodesat")==0) {
        if (argv[1]==NULL || argv[2]==NULL||argv[3]==NULL) return -3;
		if (checkConstellationChar(argv[1][0])==0) return -2;
        aux1 = gnsschar2gnsstype(argv[1][0]);
        if(aux1<0||aux1>=MAX_GNSS) return -2;
		//Check if a range is given
		p=strchr(argv[1],'-');
		if (p==NULL) {
			//No range given
			aux2 = atoi(&argv[1][1]);
			if (aux2<0 || aux2>=MAX_SATELLITES_PER_GNSS) return -2;
			aux3=-1;
		} else {
			//Range given
			*p='\0';//Temporary truncate argv[1] to get the first PRN number
			aux2 = atoi(&argv[1][1]);
			if (aux2<0 || aux2>=MAX_SATELLITES_PER_GNSS) return -2;
			*p='-';
			p++;
			aux3=atoi(p);
			if (aux3<=0 || aux3>=MAX_SATELLITES_PER_GNSS || aux3<aux2 ) return -2;
		}
        aux4 = atoi(argv[2]);
        if (aux4<0 || aux4>MAX_FILTER_MEASUREMENTS) {
            if(strlen(argv[2])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[2]);
            return -2;
		}
		if (strcasecmp(argv[3],"ComputedOnly")==0) {
			aux5=ComputedOnly;
		} else if (strcasecmp(argv[3],"ComputedPlusUser")==0 || strcasecmp(argv[3],"Computed+User")==0) {
			aux5=ComputedPlusUser;
		} else if (strcasecmp(argv[3],"UserOnly")==0) {
			aux5=UserOnly;
		} else {
            if(strlen(argv[3])>MAX_INPUT_LINE-1) return -4;
            strcpy (argv[1],argv[3]);
            return -2;
		}
		if(aux2==0) {
			if (aux4==0) {
				for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
					for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
							sopt->CombineWeightMode[aux1][j][k]=aux5;
					}
				}
			} else {
				for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
					sopt->CombineWeightMode[aux1][j][aux4-1]=aux5;
				}
			}
		} else if (aux3!=-1) {
			for (j=aux2;j<=aux3;j++) {
				if(aux4==0) {
					for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
						sopt->CombineWeightMode[aux1][j][k]=aux5;
					}
				} else {
					sopt->CombineWeightMode[aux1][j][aux4-1]=aux5;
				}
			}
		} else {
			if(aux4==0) {
				for (k=0;k<MAX_FILTER_MEASUREMENTS;k++) {
                	sopt->CombineWeightMode[aux1][aux2][k]=aux5;
                }
            } else {
                sopt->CombineWeightMode[aux1][aux2][aux4-1]=aux5;
			}
		}
		return 4;
	} else if (strcasecmp(argv[0],"-filter:phi:dr")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if(auxd<0.) return -2;
		sopt->filterParams[PHI_PAR][DR_UNK] = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:phi:clk")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if(auxd<0.) return -2;
		sopt->filterParams[PHI_PAR][DT_UNK] = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:phi:trop")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if(auxd<0.) return -2;
		sopt->filterParams[PHI_PAR][TROP_UNK] = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:phi:amb")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if(auxd<0.) return -2;
		sopt->filterParams[PHI_PAR][BIAS_UNK] = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:q:dr")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if(auxd<0.) return -2;
		sopt->filterParams[Q_PAR][DR_UNK] = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:q:clk")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if(auxd<0.) return -2;
		sopt->filterParams[Q_PAR][DT_UNK] = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:q:trop")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if(auxd<0.) return -2;
		sopt->filterParams[Q_PAR][TROP_UNK] = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:q:amb")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if(auxd<0.) return -2;
		sopt->filterParams[Q_PAR][BIAS_UNK] = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:p0:dr")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if(auxd<0.) return -2;
		sopt->filterParams[P0_PAR][DR_UNK] = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:p0:clk")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if(auxd<0.) return -2;
		sopt->filterParams[P0_PAR][DT_UNK] = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:p0:trop")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if(auxd<0.) return -2;
		sopt->filterParams[P0_PAR][TROP_UNK] = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:p0:amb")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if(auxd<0.) return -2;
		sopt->filterParams[P0_PAR][BIAS_UNK] = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:backward")==0) {
		options->filterIterations = 2;
		return 1;
	} else if (strcasecmp(argv[0],"--filter:backward")==0) {
		options->filterIterations = 1;
		return 1;
	} else if (strcasecmp(argv[0],"-filter:stfdesa")==0) {
		options->stanfordesa = 1;
		options->stanfordesaLOI = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--filter:stfdesa")==0) {
		options->stanfordesa = 0;
		options->stanfordesaLOI = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-filter:stfdesaLOI")==0) {
		options->stanfordesa = 1;
		options->stanfordesaLOI = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--filter:stfdesaLOI")==0) {
		options->stanfordesaLOI = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-filter:stfdesa:hwir")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		options->WIRHorThreshold = auxd;
		options->stanfordesa = 1;
		options->stanfordesaLOI = 1;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:stfdesa:vwir")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		options->WIRVerThreshold = auxd;
		options->stanfordesa = 1;
		options->stanfordesaLOI = 1;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:stfdesa:xmax")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if (auxd<=0) return -2;
		sopt->stfdesaxmax=auxd;
		options->stanfordesa = 1;
		options->stanfordesaLOI = 1;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:stfdesa:ymax")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if (auxd<=0) return -2;
		sopt->stfdesaymax=auxd;
		options->stanfordesa = 1;
		options->stanfordesaLOI = 1;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:stfdesa:xres")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if (auxd<=0) return -2;
		sopt->stfdesaxres=auxd;
		options->stanfordesa = 1;
		options->stanfordesaLOI = 1;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:stfdesa:yres")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if (auxd<=0) return -2;
		sopt->stfdesayres=auxd;
		options->stanfordesa = 1;
		options->stanfordesaLOI = 1;
		return 2;
	} else if (strcasecmp(argv[0],"-filter:maxgdop")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if (auxd<=0.) return -2;
		options->GDOPthreshold = 1;
		options->maxGDOP = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"--filter:maxgdop")==0) {
		options->GDOPthreshold = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-filter:SigmaIono")==0) {
		options->useSigmaIono = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--filter:SigmaIono")==0) {
		options->useSigmaIono = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-filter:StepDetector")==0) {
		options->stepdetector = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--filter:StepDetector")==0) {
		options->stepdetector = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-filter:prefitOutliers:Abs")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if (auxd<0) return -2;
		if (auxd==0.) {
			options->prefitOutlierDetectorAbs = 0;
		} else {
			options->prefitOutlierDetectorAbsThreshold=auxd;
			options->prefitOutlierDetectorAbs = 1;
		}
		return 2;
	} else if (strcasecmp(argv[0],"--filter:prefitOutliers:Abs")==0) {
		options->prefitOutlierDetectorAbs = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-filter:prefitOutliers:Median")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		if (auxd<0) return -2;
		if (auxd==0.) {
			options->prefitOutlierDetectorMedian = 0;
		} else {
			options->prefitOutlierDetectorMedianThreshold=auxd;
			options->prefitOutlierDetectorMedian = 1;
		}
		return 2;
	} else if (strcasecmp(argv[0],"--filter:prefitOutliers:Median")==0) {
		options->prefitOutlierDetectorMedian = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-sbasplots:minlat")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		options->minLatplots = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-sbasplots:maxlat")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		options->maxLatplots = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-sbasplots:minlon")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		options->minLonplots = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-sbasplots:maxlon")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		options->maxLonplots = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-sbasplots:plotarea")==0) {
		if (argv[1]==NULL||argv[2]==NULL||argv[3]==NULL||argv[4]==NULL) return -3;
		auxd = atof(argv[1]);
		options->minLonplots = auxd;
		auxd = atof(argv[2]);
		options->maxLonplots = auxd;
		auxd = atof(argv[3]);
		options->minLatplots = auxd;
		auxd = atof(argv[4]);
		options->maxLatplots = auxd;
		return 5;
	} else if (strcasecmp(argv[0],"-sbasplots:recheight")==0) {
		if (argv[1]==NULL) return -3;
		options->SBASPlotsRecHeight=atof(argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-sbasplots:VAL")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		options->VerAlarmLimit = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-sbasplots:HAL")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		options->HorAlarmLimit = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-sbasplots:AvailStep")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		options->AvailabilityPlotStep = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-sbasplots:IonoStep")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		options->IonoPlotStep = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-sbasplots:ionotimestep")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		options->IonoPlotTimeStep = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-sbasplots:windowsize")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		options->ContRiskWindowSize = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-sbasplots:hourlymaps")==0) {
		options->SBASHourlyMaps = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--sbasplots:hourlymaps")==0) {
		options->SBASHourlyMaps = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-output:sbasavailplots")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->sbasAvailplotsFile,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-output:sbasriskplots")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->sbasRiskplotsFile,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-output:sbasriskdisc")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->sbasDiscontinuityFile,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-output:sbasionoplots")==0) {
		if (argv[1]==NULL) return -3;
		if(strlen(argv[1])>MAX_INPUT_LINE-1) return -4;
		strcpy(sopt->sbasIonoplotsFile,argv[1]);
		return 2;
	} else if (strcasecmp(argv[0],"-sbasplots:noAvailPlot")==0) {
		options->NoAvailabilityPlot = 1;
		options->NoContRiskPlot = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--sbasplots:noAvailPlot")==0) {
		options->NoAvailabilityPlot = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-sbasplots:noRiskPlot")==0) {
		options->NoContRiskPlot = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--sbasplots:noRiskPlot")==0) {
		options->NoContRiskPlot = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-sbasplots:noIonoPlot")==0) {
		options->NoIonoPlot = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--sbasplots:noIonoPlot")==0) {
		options->NoIonoPlot = 0;
		return 1;
	} else if (strcasecmp(argv[0],"--sbasplots:noIonoModel")==0) {
		if (argv[1]==NULL) return -3;
		sopt->ionoModel = NoIono;
		return 2;
	} else if (strcasecmp(argv[0],"-sbasplots:inclusionarea")==0) {
		if (argv[1]==NULL||argv[2]==NULL||argv[3]==NULL||argv[4]==NULL) return -3;
		for(i=0;i<4;i++) {
			auxdarea[i]=atof(argv[i+1]);
		}
		//Check if area already exist (this is because this function is called several times,
		//so we need to avoid loading the same ranges multiple times
		for(i=0;i<options->NumSBASPlotsInclusionArea;i++) {
			if (options->SBASPlotsInclusionAreaDelimeters[i][0]==auxdarea[0] && options->SBASPlotsInclusionAreaDelimeters[i][1]==auxdarea[1] &&
					options->SBASPlotsInclusionAreaDelimeters[i][2]==auxdarea[2] && options->SBASPlotsInclusionAreaDelimeters[i][3]==auxdarea[3]) {
				//Area found
				return 5;
			}
		}
		options->SBASPlotsInclusionAreaDelimeters=realloc(options->SBASPlotsInclusionAreaDelimeters,sizeof(double*)*(options->NumSBASPlotsInclusionArea+1));
		options->SBASPlotsInclusionAreaDelimeters[options->NumSBASPlotsInclusionArea]=malloc(sizeof(double)*4);
		for(i=0;i<4;i++) {
			options->SBASPlotsInclusionAreaDelimeters[options->NumSBASPlotsInclusionArea][i]=auxdarea[i];
		}
		options->NumSBASPlotsInclusionArea++;
		return 5;
	} else if (strcasecmp(argv[0],"-sbasplots:exclusionarea")==0) {
		if (argv[1]==NULL||argv[2]==NULL||argv[3]==NULL||argv[4]==NULL) return -3;
		for(i=0;i<4;i++) {
			auxdarea[i]=atof(argv[i+1]);
		}
		//Check if area already exist (this is because this function is called several times,
		//so we need to avoid loading the same ranges multiple times
		for(i=0;i<options->NumSBASPlotsExclusionArea;i++) {
			if (options->SBASPlotsExclusionAreaDelimeters[i][0]==auxdarea[0] && options->SBASPlotsExclusionAreaDelimeters[i][1]==auxdarea[1] &&
					options->SBASPlotsExclusionAreaDelimeters[i][2]==auxdarea[2] && options->SBASPlotsExclusionAreaDelimeters[i][3]==auxdarea[3]) {
				//Area found
				return 5;
			}
		}
		options->SBASPlotsExclusionAreaDelimeters=realloc(options->SBASPlotsExclusionAreaDelimeters,sizeof(double*)*(options->NumSBASPlotsExclusionArea+1));
		options->SBASPlotsExclusionAreaDelimeters[options->NumSBASPlotsExclusionArea]=malloc(sizeof(double)*4);
		for(i=0;i<4;i++) {
			options->SBASPlotsExclusionAreaDelimeters[options->NumSBASPlotsExclusionArea][i]=auxdarea[i];
		}
		options->NumSBASPlotsExclusionArea++;
		return 5;
	} else if (strcasecmp(argv[0],"-sbassummary:VAL")==0||strcasecmp(argv[0],"-summary:VAL")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		options->VerAlarmLimit = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-sbassummary:HAL")==0||strcasecmp(argv[0],"-summary:HAL")==0) {
		if (argv[1]==NULL) return -3;
		auxd = atof(argv[1]);
		options->HorAlarmLimit = auxd;
		return 2;
	} else if (strcasecmp(argv[0],"-sbassummary:percentile")==0 || strcasecmp(argv[0],"-summary:percentile")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		options->percentile = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-sbassummary:windowsize")==0||strcasecmp(argv[0],"-summary:windowsize")==0) {
		if (argv[1]==NULL) return -3;
		aux1 = atoi(argv[1]);
		options->ContRiskWindowSize = aux1;
		return 2;
	} else if (strcasecmp(argv[0],"-sbassummary:waitfordaystart")==0||strcasecmp(argv[0],"-summary:waitfordaystart")==0) {
		options->waitForNextDay = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--sbassummary:waitfordaystart")==0||strcasecmp(argv[0],"--summary:waitfordaystart")==0) {
		options->waitForNextDay = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-sbassummary:starttime")==0 ||strcasecmp(argv[0],"-summary:starttime")==0 ) {
		if (argv[1]==NULL||argv[2]==NULL) return -3;
		//Check date format
		if (strchr(argv[2],':')!=NULL) {
			//Time has ":" symbol. 
			if (strlen(argv[2])!=8) {
				strcpy (argv[1],argv[2]); // This is for a proper error control
				return -2;
			}
			//Check that input date has correct length
			if (strchr(argv[1],'/')!=NULL) {
				if (strlen(argv[1])!=10) return -2;
			} else {
				if (strlen(argv[1])!=8) return -2;
			}
			getstr(auxstr,argv[1],0,4);
			aux1 = atoi(auxstr);
			if (aux1<1970) return -2;
			tm.tm_year=aux1-1900;
			if (strchr(argv[1],'/')!=NULL) {
				//Date has "/" symbol. It is YYYY/MM/DD HH:MM:SS format
				getstr(auxstr,argv[1],5,2);
			} else {
				getstr(auxstr,argv[1],4,2);
			}
			aux1=atoi(auxstr);
			if (aux1<1|| aux1>12) return -2;
			tm.tm_mon=aux1-1;
			if (strchr(argv[1],'/')!=NULL) {
				//Date has "/" symbol. It is YYYY/MM/DD HH:MM:SS format
				getstr(auxstr,argv[1],8,2);
			} else {
				getstr(auxstr,argv[1],6,2);
			}
			aux1=atoi(auxstr);
			if (aux1<1|| aux1>31) return -2;
			tm.tm_mday = aux1;
			//Get hour in HH:MM:SS format
			getstr(auxstr,argv[2],0,2);
			aux1=atoi(auxstr);
			if (aux1<0|| aux1>24) {
				strcpy (argv[1],argv[2]); // This is for a proper error control
				return -2;
			}
			tm.tm_hour = aux1;
			getstr(auxstr,argv[2],3,2);
			aux1=atoi(auxstr);
			if (aux1<0|| aux1>60) {
				strcpy (argv[1],argv[2]); // This is for a proper error control
				return -2;
			}
			tm.tm_min  = aux1;
			getstr(auxstr,argv[2],6,2);
			aux1=atoi(auxstr);
			if (aux1<0|| aux1>60) {
				strcpy (argv[1],argv[2]); // This is for a proper error control
				return -2;
			}
			tm.tm_sec  = aux1;
			options->firstEpochSummary.MJDN=MJDN(&tm);
			options->firstEpochSummary.SoD=(double)(tm.tm_hour*3600 + tm.tm_min*60 + tm.tm_sec);
			if(options->firstEpochSummary.SoD>=86400.) {
				options->firstEpochSummary.MJDN--;
				options->firstEpochSummary.SoD-=86400.;
			}
		} else {
			if (strchr(argv[1],'/')!=NULL) {
				//Time is in Year/DoY SoD format
				aux1=strlen(argv[1]);
				if (aux1<6 || aux1>8) return -2;
				getstr(auxstr,argv[1],0,4);
				aux1=atoi(auxstr);
				if(aux1<1970) return -2;
				aux2=atoi(&argv[1][5]);
				if(aux2<1||aux2>366) return -2;
				auxd=atof(argv[2]);
				if(auxd<0.||auxd>86400.) {
					strcpy (argv[1],argv[2]); // This is for a proper error control
					return -2;
				}
				options->firstEpochSummary.MJDN=(int)yeardoy2MJDN(aux1,aux2,auxd);
				options->firstEpochSummary.SoD=auxd;
				if(options->EndEpoch.SoD>=86400.) {
					options->firstEpochSummary.MJDN--;
					options->firstEpochSummary.SoD-=86400.;
				}
			} else {
				//Time is in GPSWeek SoW format
				aux1=atoi(argv[1]);
				if(aux1<1) return -2;
				auxd=atof(argv[2]);
				if(auxd<0.||auxd>604800.) {
					strcpy (argv[1],argv[2]); // This is for a proper error control
					return -2;
				}
				options->firstEpochSummary=gpsws2ttime(aux1,auxd);
			}
		}
		return 3;
	} else if (strcasecmp(argv[0],"-dateconv:calendar")==0) {
		if (argv[1]==NULL||argv[2]==NULL||argv[3]==NULL) return -3;
		if (argv[4]==NULL||argv[5]==NULL||argv[6]==NULL) return -3;
		aux1=atoi(argv[1]);
		aux2=atoi(argv[2]);
		if(aux2<1||aux2>12) {
			strcpy (argv[1],argv[2]); // This is for a proper error control
			return -2;
		}
		aux3=atoi(argv[3]);
		if(aux3<1||aux3>31) {
			strcpy (argv[1],argv[3]); // This is for a proper error control
			return -2;
		}
		aux4=atoi(argv[4]);
		if(aux4<0||aux4>23) {
			strcpy (argv[1],argv[4]); // This is for a proper error control
			return -2;
		}
		aux5=atoi(argv[5]);
		if(aux5<0||aux5>59) {
			strcpy (argv[1],argv[5]); // This is for a proper error control
			return -2;
		}
		auxd=atof(argv[6]);
		if(auxd<0.||aux2>=60.) {
			strcpy (argv[1],argv[6]); // This is for a proper error control
			return -2;
		}
		if (aux1<1980||(aux1==1980 && aux2==1 && aux3<6)) {
			//Date below /06/01/1980, where GPS time starts
			printf("ERROR Minimum accepted date is 1980/01/06 (YYYY/MM/DD) or 1980/006 (Year/DoY) or 0/0 (GPSWeek/SoW) or 44244/0 (MJDN/SoD)\n");
			exit(-1); 
		}
		ConvertCalendarDate(aux1,aux2,aux3,aux4,aux5,auxd);
		return 0;
	} else if (strcasecmp(argv[0],"-dateconv:doy")==0) {
		if (argv[1]==NULL||argv[2]==NULL||argv[3]==NULL) return -3;
		aux1=atoi(argv[1]);
		aux2=atoi(argv[2]);
		if(aux2<1||aux2>366) {
			strcpy (argv[1],argv[2]); // This is for a proper error control
			return -2;
		} 
		if (aux1<1980 || (aux1==1980 && aux2<6)) {
			//06/01/1980 or GPSWeek/DoW 0/0, the start of GPS time
			printf("ERROR Minimum accepted date is 1980/01/06 (YYYY/MM/DD) or 1980/006 (Year/DoY) or 0/0 (GPSWeek/SoW) or 44244/0 (MJDN/SoD)\n");
			exit(-1); 
		}
		auxd=atof(argv[3]);
		if(auxd<0.||auxd>=86400.) {
			strcpy (argv[1],argv[3]); // This is for a proper error control
			return -2;
		}
		ConvertDoYDate(aux1,aux2,auxd);
		return 0;
	} else if (strcasecmp(argv[0],"-dateconv:gpsweek")==0) {
		if (argv[1]==NULL||argv[2]==NULL) return -3;
		aux1=atoi(argv[1]);
		if(aux1<0) return -2;
		auxd=atof(argv[2]);
		if(auxd<0.||auxd>=604800.) {
			strcpy (argv[1],argv[2]); // This is for a proper error control
			return -2;
		}
		ConvertGPSWeekDate(aux1,auxd);
		return 0;
	} else if (strcasecmp(argv[0],"-dateconv:mjdn")==0) {
		if (argv[1]==NULL||argv[2]==NULL) return -3;
		aux1=atoi(argv[1]);
		if(aux1<44244) {
			//MJDN 44244 is 06/01/1980, or GPSWeek/DoW 0/0, the start of GPS time
			printf("ERROR Minimum accepted date is 1980/01/06 (YYYY/MM/DD) or 1980/006 (Year/DoY) or 0/0 (GPSWeek/SoW) or 44244/0 (MJDN/SoD)\n");
			exit(-1); 
		}
		auxd=atof(argv[2]);
		if(auxd<0.||auxd>=86400.) {
			strcpy (argv[1],argv[2]); // This is for a proper error control
			return -2;
		}
		ConvertMJDNDate(aux1,auxd);
		return 0;
	} else if (strcasecmp(argv[0],"-coordconv:cartesian")==0) {
		if (argv[1]==NULL||argv[2]==NULL||argv[3]==NULL) return -3;
		auxd=atof(argv[1]);
		auxd2=atof(argv[2]);
		auxd3=atof(argv[3]);
		ConvertCartesianCoord(auxd,auxd2,auxd3);
		return 0;
	} else if (strcasecmp(argv[0],"-coordconv:geodetic")==0) {
		if (argv[1]==NULL||argv[2]==NULL||argv[3]==NULL) return -3;
		auxd=atof(argv[1]);
		if(auxd<-180.||auxd>180.) return -2;
		auxd2=atof(argv[2]);
		if(auxd2<-90.||auxd2>90.) {
			strcpy (argv[1],argv[2]); // This is for a proper error control
			return -2;
		}
		auxd3=atof(argv[3]);
		if(auxd3<-10000) {
			strcpy (argv[1],argv[3]); // This is for a proper error control
			return -2;
		}
		ConvertGeodeticCoord(auxd,auxd2,auxd3);
		return 0;
	} else if (strcasecmp(argv[0],"-coordconv:spherical")==0) {
		if (argv[1]==NULL||argv[2]==NULL||argv[3]==NULL) return -3;
		auxd=atof(argv[1]);
		if(auxd<-180.||auxd>180.) return -2;
		auxd2=atof(argv[2]);
		if(auxd2<-90.||auxd2>90.) {
			strcpy (argv[1],argv[2]); // This is for a proper error control
			return -2;
		}
		auxd3=atof(argv[3]);
		if(auxd3<0.) {
			strcpy (argv[1],argv[3]); // This is for a proper error control
			return -2;
		}
		ConvertSphericalCoord(auxd,auxd2,auxd3);
		return 0;
	} else if (strcasecmp(argv[0],"-print:info")==0) {
		options->printInfo = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:info")==0) {
		options->printInfo = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:model")==0) {
		options->printModel = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:model")==0) {
		options->printModel = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:prefit")==0) {
		options->printPrefit = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:prefit")==0) {
		options->printPrefit = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:postfit")==0) {
		options->printPostfit = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:postfit")==0) {
		options->printPostfit = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:filter")==0) {
		options->printFilterSolution = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:filter")==0) {
		options->printFilterSolution = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:cycleslips")==0 || strcasecmp(argv[0],"-print:cs")==0) {
		options->printCycleslips = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:cycleslips")==0 || strcasecmp(argv[0],"--print:cs")==0) {
		options->printCycleslips = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:satellites")==0 || strcasecmp(argv[0],"-print:epochsat")==0 || strcasecmp(argv[0],"-print:sat")==0) {
		options->printSatellites = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:satellites")==0 || strcasecmp(argv[0],"--print:epochsat")==0 || strcasecmp(argv[0],"--print:sat")==0) {
		options->printSatellites = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:input")==0) {
		options->printInput = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:input")==0) {
		options->printInput = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:meas")==0) {
		options->printMeas = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:meas")==0) {
		options->printMeas = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:output")==0) {
		options->printOutput = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:output")==0) {
		options->printOutput = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:satsel")==0) {
		options->printSatSel = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:satsel")==0) {
		options->printSatSel = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:satdiff")==0) {
		options->printSatDiff = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:satdiff")==0) {
		options->printSatDiff = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:satstat")==0) {
		options->printSatStat = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:satstat")==0) {
		options->printSatStat = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:satstattot")==0) {
		options->printSatStatTot = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:satstattot")==0) {
		options->printSatStatTot = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:satpvt")==0) {
		options->printSatPvt = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:satpvt")==0) {
		options->printSatPvt = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:sbasout")==0) {
		options->printSBASOUT = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:sbasout")==0) {
		options->printSBASOUT = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:sbascor")==0 || strcasecmp(argv[0],"-print:sbascorr")==0) {
		options->printSBASCORR = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:sbascor")==0 || strcasecmp(argv[0],"--print:sbascorr")==0) {
		options->printSBASCORR = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:sbasvar")==0) {
		options->printSBASVAR = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:sbasvar")==0) {
		options->printSBASVAR = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:sbasiono")==0) {
		options->printSBASIONO = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:sbasiono")==0) {
		options->printSBASIONO = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:sbasunsel")==0) {
		options->printSBASUNSEL = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:sbasunsel")==0) {
		options->printSBASUNSEL = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:sbasunused")==0) {
		options->printSBASUNUSED = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:sbasunused")==0) {
		options->printSBASUNUSED = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:usererror")==0) {
		options->printUserError = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:usererror")==0) {
		options->printUserError = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:dgnss")==0) {
		options->printDGNSS = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:dgnss")==0) {
		options->printDGNSS = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:dgnssunused")==0) {
		options->printSBASUNUSED = 1;
		options->printDGNSSUNUSED = 1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:dgnssunused")==0) {
		options->printSBASUNUSED = 0;
		options->printDGNSSUNUSED = 0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:summary")==0) {
		options->printSummary=1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:summary")==0) {
		options->printSummary=0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:progress")==0) {
		printProgress=1;
		sopt->UserSetPrintProgress=1;
		return 1;
	} else if (strcasecmp(argv[0],"--print:progress")==0) {
		printProgress=0;
		sopt->UserSetPrintProgress=0;
		return 1;
	} else if (strcasecmp(argv[0],"-print:guiprogress")==0) {
		//Note: This is a hidden parameter passed by the GUI
		//It is to print only the progress when the integer part of the
		//percentage completed changes, and the end of line has a '\n',
		//so the GUI handles less messages and can read line by line
		printProgress=1;
		options->ProgressEndCharac='\n';
		sopt->UserSetPrintProgress=1;
		return 1;
	} else if (strcasecmp(argv[0],"-print:all")==0) {
		options->printInfo = 1;
		options->printInput = 1;
		options->printMeas = 1;
		options->printCycleslips = 1;
		options->printModel = 1;
		options->printSatellites = 1;
		options->printSatSel = 1;
		options->printPrefit = 1;
		options->printFilterSolution = 1;
		options->printPostfit = 1;
		options->printOutput = 1;
		options->printSatDiff = 1;
		options->printSatStat = 1;
		options->printSatStatTot = 1;
		options->printSatPvt = 1;
		options->printSBASOUT = 1;
		options->printSBASCORR = 1;
		options->printSBASVAR = 1;
		options->printSBASIONO = 1;
		options->printSBASUNSEL = 1;
		options->printSBASUNUSED = 1;
		options->printUserError = 1;
		options->printDGNSS = 1;
		options->printSummary = 1;
		return 1;
	} else if (strcasecmp(argv[0],"-print:none")==0||strcasecmp(argv[0],"--print:none")==0) {
		options->printInfo = 0;
		options->printInput = 0;
		options->printMeas = 0;
		options->printCycleslips = 0;
		options->printModel = 0;
		options->printSatellites = 0;
		options->printSatSel = 0;
		options->printPrefit = 0;
		options->printFilterSolution = 0;
		options->printPostfit = 0;
		options->printOutput = 0;
		options->printSatDiff = 0;
		options->printSatStat = 0;
		options->printSatStatTot = 0;
		options->printSatPvt = 0;
		options->printSBASOUT = 0;
		options->printSBASCORR = 0;
		options->printSBASVAR = 0;
		options->printSBASIONO = 0;
		options->printSBASUNSEL = 0;
		options->printSBASUNUSED = 0;
		options->printUserError = 0;
		options->printDGNSS = 0;
		options->printSummary = 0;
		return 1;
	#if defined _OPENMP
	} else if (strcasecmp(argv[0],"-numthreads")==0) {
		if (argv[1]==NULL) return -3;
		omp_set_dynamic(0);     // Explicitly disable dynamic teams
		aux1=atoi(argv[1]);
		if (aux1<=0 ) {
			return -2;
		} else if (aux1>omp_get_num_procs()) {
			printf("ERROR Maximum number of threads is the number of CPU cores (%d)\n",omp_get_num_procs());
			exit(-1); 
		}
		omp_set_num_threads(aux1);
		options->numthreads=aux1;
		return 2;
	#endif
	}

	return -1;
}

/*****************************************************************************
 * Name        : parseAllOptions
 * Description : Parse all options from a vector of strings into the options or 
 *               support options
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TSupportOptions  *sopt          O  N/A  TSupportOptions structure
 * TOptions  *options              O  N/A  TOptions structure
 * int  argc                       I  N/A  Number of strings in argv[]
 * char  *argv[]                   I  N/A  Vector of strings to be parsed
 * Returned value (int)            O  N/A  Status of the function
 *                                         0 => Required program stop 
 *                                              (error, showHelp or showExamples)                                        
 *                                         1 => Normal options lecture
 *****************************************************************************/
int parseAllOptions (TSupportOptions *sopt,TOptions *options, int argc, char *argv[]) {
	char	**ptr;
	int		i;
	int		res;

	i = 1;
	if (argc==1) {
		showHelp();
		return 0;
	}

	while (i<argc) {
		ptr = &argv[i];
		res = parseOption(sopt,options,ptr);
		if (res==-4) { 	// Input string too long (in order to avoid buffer overflow)
			sprintf(messagestr,"One of the parameters is larger than %d characters long. Use shorter paths or filenames.",MAX_INPUT_LINE-1);
			printError(messagestr,options);
			return 0;
		} else if (res==-3) { // Missing parameters
			sprintf(messagestr,"'%s' requires more parameters. Use '-help' for a set of valid options.",*ptr);
			printError(messagestr,options);
			return 0;
		} else if (res==-2) { // Value not valid
			sprintf(messagestr,"'%s' is not a valid value for '%s'. Use '-help' for a set of valid options.",ptr[1],*ptr);
			printError(messagestr,options);
			return 0;
		} else if (res==-1) { // Parameter unknown
			sprintf(messagestr,"'%s' option not recognised. Use '-help' for a set of valid options.",*ptr);
			printError(messagestr,options);
			return 0;
		} else if (res==0) { // Show help/examples/config/messages
			return 0;
		}
		// Increment by the number of parameters readed
		i+=res; 
	}
	return 1;
}

/*****************************************************************************
 * Name        : removeExtension
 * Description : Removes the filename extension
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char* mystr                     I  N/A  String with the filename with extension
 * char *retstr                    O  N/A  String with the filename without extension
 *****************************************************************************/
void removeExtension (char* mystr,char *retstr) {
	char 	*lastdot;
	int		len, lenmystr;

	if ( mystr == NULL ) {
		retstr = NULL;
		return;
	}

	lastdot = strrchr(mystr, '.');
	lenmystr = strlen(mystr);

	if ( lastdot != NULL ) {
		if ( lenmystr == 1 ) {
			strcpy(retstr, mystr);
		} else {
			len = lenmystr - strlen(lastdot);
			strncpy(retstr, mystr, len);
			retstr[len] = '\0';
		}
	} else {
		strcpy(retstr, mystr);
	}

	return;
}

/*****************************************************************************
 * Name        : getRTCMpath
 * Description : Gets the input binary RTCM path and returns the output path
 *               for the RINEX file with the first 4 characters according to
 *               the filename standard
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char* mystr                     I  N/A  String with the input binary RTCM
 * char *retstr                    O  N/A  String with the output RINEX file
 *****************************************************************************/
void getRTCMpath (char* mystr,char *retstr) {
	char	*lastslash;
	int		len, lenmystr;

	// Get the path
	if ( mystr == NULL ) {
		retstr = NULL;
		return;
	}

	#if defined (__WIN32__)
		lastslash = strrchr(mystr, '\\');
	#elif defined (__CYGWIN__)
		lastslash = strrchr(mystr, '/');
	// In cygwin, we may have linux or windows pathes
	if ( lastslash == NULL ) lastslash = strrchr(mystr, '\\');
	#else
		lastslash = strrchr(mystr, '/');
	#endif

	lenmystr = strlen(mystr);
	if ( lastslash != NULL ) {
		len = lenmystr - strlen(lastslash) + 5;
		if ( len > lenmystr ) len = lenmystr;
	} else {
		if ( lenmystr < 4 ) len = lenmystr;
		else len = 4;
	}
	strncpy(retstr, mystr, len);
	retstr[len] = '\0';

	return;
}

/*****************************************************************************
 * Name        : processOptions
 * Description : To be called after all the options have been parsed. Read 
 *               options from TSupportOptions and translates it to TOptions
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TSupportOptions  *sopt          I  N/A  TSupportOptions structure
 * TOptions  *options              IO N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         0 => Some problems with the options chosen
 *                                              (compatibility or missing critical
 *                                              options)
 *                                         1 => Processing properly done
 *****************************************************************************/
int processOptions (TSupportOptions *sopt, TOptions *options) {
	int				preciseProductsAvailable;
	int				broadcastProductsAvailable;
	int 			i,j,k;
	int				sources;
	int				nProd;
	int 			RTCMversion;
	int				r1,r2;
	enum fileType	auxft1;
	char			auxpathRTCMpointer[MAX_INPUT_LINE];
	char			pathRTCMpointer[MAX_INPUT_LINE];
	char   			*filepointer;
	char			auxstr[1000];
	TEpoch 			*epoch = NULL;
	FILE 			*fdRTCM = NULL;
	TRTCM2 			*rtcm2 = NULL;
	FILE 			*fdRTCM2 = NULL;
	int 			ret, doy;
	char 			*fileASCIIcorrections = NULL;
	char 			*fileASCIIantenna = NULL;
	FILE 			*fdRTCM3 = NULL;
	char 			fileRINEXpointer[MAX_INPUT_LINE];
	char 			strDoy[4];
	char 			strYear[3];
	TRTCM3 			*rtcm3 = NULL;
	struct 			stat stats_stdin,stats_stdout;

	#if !defined (__WIN32__)
	//Variables for non windows environments check
	pid_t 			fg;
	#endif


	// Number of GNSS product sources available
	nProd = sopt->numNav + sopt->numSP3 + sopt->numOrb;
	
	if (options->ProgressEndCharac=='\r') {
		//'\r' means that we print to terminal
		//Check if output has been redirected to a terminal
		//Look for properties of stdin and stdout
		r1 = fstat(fileno(stdin), &stats_stdin);
		r2 = fstat(fileno(stdout), &stats_stdout);

		if (r1<0 || r2<0) {
			//Stdin or stdout properties cannot be read.
			//Disable progress print as we cannot now if output is piped
			printProgress=0;
		} else {
			if (S_ISCHR(stats_stdout.st_mode)) {
				options->OutputToTerminal=1;
			} else {
				options->OutputToTerminal=0;
				#if defined (__WIN32__)
					//In Windows, we cannot distinguish if process is run in the background
					//Therefore, is user does provide parameter -print:progress,
					//disable print progress so it does not mess with terminal when process is in background
					if (sopt->UserSetPrintProgress!=1) {
						printProgress=0;
					}
				#endif
			}

			//Check if standard input is from a terminal (interactive). If it isn't, probably
			//or process in the background or from an automatic process. Disable progress bar
			//NOTE: S_ISCHR(stats_stdin.st_mode) can return true even if process is in background!
			if (!S_ISCHR(stats_stdin.st_mode)) {
				//Stdin not a terminal
				printProgress=0;
			} else {
			#if !defined (__WIN32__)
				if (S_ISFIFO(stats_stdout.st_mode)||S_ISSOCK(stats_stdout.st_mode) ) {
					//Output is a socket or a pipe. Disable print
					printProgress=0;
				} else {
					fg=tcgetpgrp(STDIN_FILENO);
					if (fg==-1) {
						//Stdin is a pipe. Disable progress print
						printProgress=0;
					} else if (fg!=getpgrp()) {
						//We are in the background. Disable progress print
						printProgress=0;
					}
				}
			#else
				if (S_ISFIFO(stats_stdout.st_mode)) {
					//Output is a pipe. Disable print
					printProgress=0;
				}
			#endif
			}
		}
	} else {
		//'\n' means that we print for the GUI
		options->OutputToTerminal=1;
		printProgress=1;
		sopt->disableCursor=0;
	}

	// Output redirection
	if ( sopt->outFile[0] != '\0' ) {
		//Create directory recursively if needed
		ret=mkdir_recursive(sopt->outFile);
		if(ret!=0) {
		   //Error when creating the directory, and it is not due to that the directory already exists
		   sprintf(messagestr,"When creating [%s] folder for writing the output file",sopt->outFile);
		   printError(messagestr,options);
		}
		options->outFileStream=fopen(sopt->outFile,"w");
		if (options->outFileStream==NULL) {
			sprintf(messagestr,"Problem with output file [%s] redirection",sopt->outFile);
			printError(messagestr,options);
		}
		if (printProgress!=0) {
			//User has not set anything about printing progress
			if (options->OutputToTerminal==1) {
				printProgress=1;
			} else {
				#if defined (__WIN32__)
					options->terminalStream=fopen("CON","w");
				#else
					options->terminalStream=fopen("/dev/tty","w");
				#endif
				if (options->terminalStream==NULL) {
					printProgress=0;
				} else {
					printProgress=1;
				}
			}
		}
	} else {
		if (printProgress!=0) {
			if (options->OutputToTerminal==1) {
				printProgress=1;
			} else {
				//User has not set anything about printing progress
				#if defined (__WIN32__)
					options->terminalStream=fopen("CON","w");
				#else
					options->terminalStream=fopen("/dev/tty","w");
				#endif
				if (options->terminalStream==NULL) {
					printProgress=0;
				} else {
					printProgress=1;
				}
			}
		}
	}
	#if !defined (__WIN32__)
		//Disable cursor in Linux to avoid cursor flickering in screen (really annoying!!)
		if (printProgress==1 && sopt->disableCursor==1) {
			fprintf(options->terminalStream,"\033[?25l");
			strcpy(enableCursor,"\033[?25h");
			strcpy(disableCursor,"\033[?25l");
			StdoutStream=options->terminalStream;
		}
	#endif

	// Print gLAB version in INFO field
	if ( options->onlyconvertSBAS == 0 ) {
		#if defined _OPENMP
			sprintf(messagestr,"gLAB version v%s (with OpenMP multithread), built on %s %s",VERSION,__DATE__,__TIME__);
		#else
			sprintf(messagestr,"gLAB version v%s, built on %s %s",VERSION,__DATE__,__TIME__);
		#endif
		printInfo(messagestr,options);
	} else {
		if (printProgress==1) {
			printProgressConvert=1;	
		}
	}

	//Check number of product sources available
	if ( sopt->numNav>2 ) {
		sprintf(messagestr,"Maximum navigation files is 2, but %d navigation files were given",sopt->numNav);
		printError(messagestr,options);
	} else if ( sopt->numSP3 >2 ) {
		sprintf(messagestr,"Maximum SP3 files is 2, but %d SP3 files were given",sopt->numSP3);
		printError(messagestr,options);
	} else if ( sopt->numOrb >2 ) {
		sprintf(messagestr,"Maximum SP3 orbit files is 2, but %d SP3 orbit files were given",sopt->numOrb);
		printError(messagestr,options);
	} else if ( sopt->numClk >2 ) {
		sprintf(messagestr,"Maximum clock files is 2, but %d clock files were given",sopt->numClk);
		printError(messagestr,options);
	} else if (sopt->numTGD >2) {
		sprintf(messagestr,"Maximum TGD files is 2, but %d TGD files were given",sopt->numTGD);
		printError(messagestr,options);
	}

	//Check if Start time is after End time in case both times are given by the user
	if (options->StartEpoch.MJDN!=-1 && options->EndEpoch.MJDN!=-1) {
		if(tdiff(&options->EndEpoch,&options->StartEpoch)<0.) {
			printError("Processing start time must be ahead of processing end time",options);
		}
	}


	// Check that SBAS and DGNSS are both activated
	if ( options->SBAScorrections == 1 && options->DGNSS == 1 ) {
		printError("SBAS and DGNSS cannot be both set",options);
	}

	// Check if user set a reference position file and a valid receiver position mode for DGNSS
	if (sopt->posReferenceFile[0]!='\0' && options->receiverPositionSource == rpCALCULATEREF && options->DGNSS == 1) {
		//Reference file provided and it is the default mode for a reference file and we are in DGNSS
		options->receiverPositionSource = rpRTCMRoverUSERREF;
	}
	
	// Check a priori position
	if ( options->receiverPositionSource == rpUNKNOWN) {
		if ( options->DGNSS == 1) options->receiverPositionSource = rpRTCMbaseline;
		else {
			options->receiverPositionSource = rpRINEX;
			options->recPosProvided=1;
		}
	} else {
		if (options->DGNSS == 1 && options->receiverPositionSource < rpRTCMbaseline) {
			printError("Receiver position modes in DGNSS must be one of these: 'DGNSSbaseline', 'DGNSSRinexRover', 'DGNSSRoverUSER', 'DGNSSRoverUSERGeod', 'DGNSSRoverUSERRef', 'DGNSSUserRoverRef', 'DGNSSUserRoverRefGeod', 'DGNSSUserbaseline', 'DGNSSUserGeodbaseline',  'DGNSSUserRinexRover', 'DGNSSUserGeodRinexRover', 'DGNSSRefRoverUSER', 'DGNSSRefGeodRoverUSERGeod', 'DGNSSRefCarRoverUSERGeod' or 'DGNSSRefGeodRoverUSERCar'",options);
		} else if ( options->DGNSS == 0 && options->receiverPositionSource > rpCALCULATEUSERREF) {
			printError("Receiver position modes in SPP, PPP or SBAS can only be: 'RINEX', 'SINEX', 'Set', 'SetGeod', 'SetRef', 'calculate', 'calculateRef', 'calculateRINEX', 'calculateRINEXRef', 'calculateUSER', 'calculateUSERGeod', 'calculateUSERRef' or 'calculateUSERGeodRef'",options);
		}
	}


	//Print messages for deprecated options
	if ( options->deprecatedMode == 1 && options->printInfo ==1 ) {
		printf("%s",sopt->deprecatedMessages);
	}

	//If summary is enabled, compute and show summary message at the end of file
	if ( sopt->obsFile[0] != '\0' && options->printSummary == 1 ) {
		options->useDatasummary=1;
		if(options->percentile<=0 || options->percentile>100 ) {
			printError("Percentile for summary must be greater than 0 and smaller or equal than 100",options);
		}
		if (options->SBAScorrections == 1 && options->onlySBASiono == 0 ) {
			//Check that Alarm limits given are valid
			if(options->HorAlarmLimit<=0.) {
				printError("Horizontal Alarm Limit for SBAS summary must be greater than 0",options);
			}
			if(options->VerAlarmLimit<=0.) {
				printError("Vertical Alarm Limit for SBAS summary must be greater than 0",options);
			}
			if(options->ContRiskWindowSize<=0 ) {
				printError("Continuity Risk Sliding Window epoch size for SBAS summary must be greater than 0",options);
			}
		}
	} else if ( options->stanfordesa==1 ) {
		//This is for the case that summary is not computed, but we want Stanford-ESA to be computed
		options->useDatasummary=2; 
	} else {
		options->useDatasummary=0;
	}


	// Check if gLAB has to convert SBAS data files and if doesn't have to do any computations
	if ( options->SBAScorrections == 1 ) {

		if ( sopt->navFile[0][0]=='\0' && options->onlyconvertSBAS == 0 ) {
			printError("SBAS navigation mode selected, but no navigation file available",options);
		}


		if ( options->onlyconvertSBAS == 1 ) {
			if (options->writeRinexBfile==0 && options->writeEMSfile==0 && options->writePegasusfile==0) {
				printError("SBAS file conversion only selected, but no file format given. Use '-output:rinexb' or '-output:ems' or '-output:pegasus' to select file formats",options);
			}
			return 1;
		}

		if ( options->filterIterations == 2 ) {
			printError("SBAS mode activated, which is incompatible with backward processing. Disable backward processing for SBAS mode",options);
		}

		if ( options->GEOPRN >= MINGEOPRN && options->GEOPRNunsel[options->GEOPRN] == 1 ) {
			sprintf(messagestr,"Selected GEO %d for SBAS processing, but this GEO has also been set as unselected",options->GEOPRN);
			printError(messagestr,options);
		}

		//If switch mode is enabled or initial mode is NPA or receiver position is set, then we don't need to use Klobuchar in PA in the first epochs
		if ( options->switchmode==1 || options->precisionapproach==NPAMODE || options->receiverPositionSource < rpCALCULATE ) {
			options->initcoordNPA=0;
		}

		if ( options->onlySBASiono == 0 ) {
			// Set L1C1 cycle-slip detector if not set
			if ( sopt->csL1C1 == -1 ) sopt->csL1C1 = 1;
			// Set default SBAS smoothing if non set
			if ( options->smoothEpochs == -1 ) options->smoothEpochs = 100;
			// Set kinematic navigation if non set
			if ( sopt->navKinematics == NKND ) sopt->navKinematics = NKkinematic;
			// Set 1 second decimation if non set
			if ( options->decimate == -1. ) options->decimate = 1.;
			// Set to do not indentify P1 as C1 if non set
			if ( sopt->p1c1dcbModel == p1c1UNKNOWN ) {
				sopt->p1c1dcbModel = p1c1NONE;
				options->flexibleC1P1 = 0;
			}
			// Unset GDOP threshold if non set
			if (options->GDOPthreshold == -1) options->GDOPthreshold = 0;
			// Set default SBAS smoothing convergence time if non set
			if ( options->excludeSmoothingConvergence == -1 ) options->excludeSmoothingConvergence = 360;
			//Enable SNR filter
			if ( options->SNRfilter == -1 ) {
				options->SNRfilter = 1;
			}
			//Disable Ncon for SBAS if not set
			if ( options->csNcon == -1 ) {
				options->csNcon = 0;
			}
			//Set default Data Gap to 10 seconds if not set
			if ( options->csDataGap == -1 ) {
				options->csDataGap = 10;
			}

			//Enable ARP correction if not set
			if (options->ARPData==arpUNKNOWN) {
				options->ARPData = arpRINEX;
			}

			//Disable check of transmission time in broadcast messages if user has not set anything
			if ( options->brdcBlockTransTime == -1 ) options->brdcBlockTransTime = 0;
	
			// Activate step detector if user has not enabled or disabled it
			// For now we will leave it by default disabled, as it has no real practical use
			// if(options->stepdetector==-1) options->stepdetector=1;


			//Check if RRC corrections are enabled but fast corrections are disabled
			if(options->NoRRCCorrection==0 && options->NoFastCorrection==1) {
				printError("SBAS Fast corrections must be enabled if RRC corrections are going to be used",options);
			}

			//Check if RRC degradation terms are enabled but fast corrections are disabled
			if(options->NoRRCSigma==0 && options->NoFastSigma==1) {
				printError("SBAS Fast corrections sigmas must be enabled if RRC degradation term is going to be used",options);
			}
			
			//Check if both fixed sigma multipath value and user defined sigma multipath model are given
			if(options->airborneReceiverType==0 && options->usersigmamultipath==1 && options->sigma2multipath[0]!=-99999.) {
				printError("SBAS Sigma multipath has been defined with a fixed value and a user defined model, but only one definition type can be selected at once",options);
			}

			// Set default prints
			if ( options->printInput == -1 )          options->printInput = 0;
			if ( options->printModel == -1 )          options->printModel = 0;
			if ( options->printPrefit == -1 )         options->printPrefit = 0;
			if ( options->printPostfit == -1 )        options->printPostfit = 0;
			if ( options->printFilterSolution == -1 ) options->printFilterSolution = 0;
			if ( options->printSatellites == -1 )     options->printSatellites = 0;
			if ( options->printSatSel == -1 )         options->printSatSel = 1;

		}
	}
	//Options for Stanford-ESA computation (it can be computed outside of SBAS mode)
	if ( options->stanfordesa == 1 ) {
		//Check that Worst Integrity threshold for printing Stanford-ESA iteration given is valid
		if(options->WIRHorThreshold<0.) {
			printError("Horizontal Worst Integrity Ratio threshold for printing solution in Stanford-ESA computation must be greater or equal than 0",options);
		}
		if(options->WIRVerThreshold<0.) {
			printError("Vertical Worst Integrity Ratio threshold for printing solution in Stanford-ESA computation must be greater or equal than 0",options);
		}

		// Check if a filename is given for stanford-ESA plot. If non given, use the observation filename with "_stdESA.txt" appended at the end
		if ( sopt->stanfordESAFile[0] == '\0' && sopt->obsFile[0] != '\0') {
			#if defined (__WIN32__)
				filepointer = strrchr(sopt->obsFile,'\\');
			#elif defined (__CYGWIN__)
				filepointer = strrchr(sopt->obsFile,'/');
				// In cygwin, we may have linux or windows pathes
				if ( filepointer == NULL ) {
					filepointer = strrchr(sopt->obsFile,'\\');
				}
			#else
				filepointer = strrchr(sopt->obsFile,'/');
			#endif
				if ( filepointer == NULL ) {
					// There is no directory path in the file
					sprintf(sopt->stanfordESAFile,"%s_stdESA.txt",sopt->obsFile);
				} else {
					// There is directory path in the file. Only use the filename so the file is created in the current directory
					sprintf(sopt->stanfordESAFile,"%s_stdESA.txt",(char *)(filepointer+sizeof(char)));
				}
		}

		// Check if a filename is given for stanford-ESA LOI data. If non given, use the observation filename with "_stdESA_LOI.txt" appended at the end
		if ( sopt->stanfordESALOIFile[0] == '\0' && sopt->obsFile[0] != '\0') {
			#if defined (__WIN32__)
				filepointer = strrchr(sopt->obsFile,'\\');
			#elif defined (__CYGWIN__)
				filepointer = strrchr(sopt->obsFile,'/');
				// In cygwin, we may have linux or windows pathes
				if ( filepointer == NULL ) {
					filepointer = strrchr(sopt->obsFile,'\\');
				}
			#else
				filepointer = strrchr(sopt->obsFile,'/');
			#endif
				if ( filepointer == NULL ) {
					// There is no directory path in the file
					sprintf(sopt->stanfordESALOIFile,"%s_stdESA_LOI.txt",sopt->obsFile);
				} else {
					// There is directory path in the file. Only use the filename so the file is created in the current directory
					sprintf(sopt->stanfordESALOIFile,"%s_stdESA_LOI.txt",(char *)(filepointer+sizeof(char)));
				}
		}
	}

	// Defaults for DGNSS
	if ( options->DGNSS == 1 ) {
	
		// Set L1-C1 cycle-slip detector if not set
		if ( sopt->csL1C1 == -1 ) sopt->csL1C1 = 1;
		// Set default DGNSS smoothing if non set
		if ( options->smoothEpochs == -1 ) options->smoothEpochs = 100;
		// If decimation not set and DGNSS mode, set it to 0 (no decimation)
		if ( options->decimate == -1. ) options->decimate = 0.;
		// Set GDOP threshold if non set
		if (options->GDOPthreshold == -1) options->GDOPthreshold = 1;
		//Enable SNR filter
		if ( options->SNRfilter == -1 ) {
			options->SNRfilter = 1;
		}
		//Disable Ncon for DGNSS if not set
		if ( options->csNcon == -1 ) {
			options->csNcon = 0;
		}
		//Set default Data Gap to 10 seconds if not set
		if ( options->csDataGap == -1 ) {
			options->csDataGap = 10;
		}

		//Enable ARP correction if not set
		if (options->ARPData==arpUNKNOWN) {
			options->ARPData = arpRINEX;
		}

		// Use the RTCM file path to output the converted RINEX
		if ( sopt->rtcmFile[0] != '\0' || sopt->rtcm2File[0] != '\0' || sopt->rtcm3File[0] != '\0' ) {
			if ( sopt->rtcmFile[0] != '\0' ) removeExtension(sopt->rtcmFile, auxpathRTCMpointer);
			else if ( sopt->rtcm2File[0] != '\0' ) removeExtension(sopt->rtcm2File, auxpathRTCMpointer);
			else removeExtension(sopt->rtcm3File, auxpathRTCMpointer);

			getRTCMpath(auxpathRTCMpointer, pathRTCMpointer);
		}

		if ( options->filterIterations == 2 ) {
			printError("DGNSS mode activated, which is incompatible with backward processing. Disable backward processing for DGNSS mode",options);
		}

		//Disable check of transmission time in broadcast messages if user has not set anything
		if ( options->brdcBlockTransTime == -1 ) options->brdcBlockTransTime = 0;
	}

	// If decimation not set, set it to 300
	if ( options->decimate == -1. ) options->decimate = 300.;

	// If smoothing not set, disable it
	if ( options->smoothEpochs == -1 ) options->smoothEpochs = 0;

	// Disable smoothing convergence time if non set
	if ( options->excludeSmoothingConvergence == -1 ) options->excludeSmoothingConvergence = 0;

	// If step detector not set, disable it
	if ( options->stepdetector == -1 ) options->stepdetector=0;

	//Disable SNR filter for SPP and PPP if not set
	if ( options->SNRfilter == -1 ) {
		options->SNRfilter = 0;
	}

	//Enable Ncon for SPP and PPP if not set
	if ( options->csNcon == -1 ) {
		options->csNcon = 1;
	}

	//Set default Data Gap to 40 seconds if not set
	if ( options->csDataGap == -1 ) {
		options->csDataGap = 40;
	}

	// Set default prints
	if ( options->printInput == -1 )          options->printInput = 1;
	if ( options->printModel == -1 )          options->printModel = 1;
	if ( options->printPrefit == -1 )         options->printPrefit = 1;
	if ( options->printPostfit == -1 )        options->printPostfit = 1;
	if ( options->printFilterSolution == -1 ) options->printFilterSolution = 1;
	if ( options->printSatellites == -1 )     options->printSatellites = 1;
	if ( options->printSatSel == -1 )         options->printSatSel = 0;

	// Products availability check
	if ( sopt->SP3File[0][0] == '\0' && (sopt->orbFile[0][0] == '\0' || sopt->clkFile[0][0] == '\0') ) {
		preciseProductsAvailable = 0;
	} else {
		preciseProductsAvailable = 1;
	}
	
	if ( sopt->navFile[0][0] == '\0' ) {
		broadcastProductsAvailable = 0;
	} else {
		broadcastProductsAvailable = 1;
	}
	
	// Sanity check
	if ( sopt->obsFile[0] != '\0' ) {
		options->workMode = wmDOPROCESSING;
		if ( broadcastProductsAvailable && sopt->navMode == NMND ) sopt->navMode = NMstandalone;
		if ( preciseProductsAvailable && sopt->navMode == NMND ) sopt->navMode = NMppp;
		if ( broadcastProductsAvailable && preciseProductsAvailable ) {
			printError("Cannot determine if processing Standalone or PPP. Please use only one source of GNSS products",options);
		} else if (sopt->navMode==NMppp && broadcastProductsAvailable) {
			printError("PPP and input:nav were set",options);
		} else if (sopt->navMode==NMstandalone && preciseProductsAvailable) {
			printError("Standalone and input:sp3/input:orb/input:clk were set",options);
		} else if (sopt->SP3File[0][0]!='\0' && sopt->orbFile[0][0]!='\0' && sopt->clkFile[0][0]!='\0') {
			printError("input:sp3, input:orb and input:clk cannot be all set",options);
		} else if (sopt->SP3File[0][0]!='\0' && sopt->orbFile[0][0]!='\0') {
			printError("input:sp3 and input:orb cannot be both set. Use '-input:sp3' to read orbit and clock products from a SP3 file, or use '-input:orb' to read only orbits from SP3 and '-input:clk' to read clocks from a CLK file",options);
		} else if (sopt->SP3File[0][0]!='\0' && sopt->clkFile[0][0]!='\0') {
			printError("input:sp3 and input:clk cannot be both set. Use '-input:sp3' to read orbit and clock products from a SP3 file, or use '-input:orb' to read only orbits from SP3 file and '-input:clk' to read clocks from a CLK file",options);
		} else if (!broadcastProductsAvailable && !preciseProductsAvailable) {
			if (sopt->addederrorFile[0]!='\0' && options->DGNSS==0 && options->SBAScorrections==0 ) {
				options->workMode = wmUSERERROR2RINEX;
				if (sopt->rnxFile[0]=='\0') {
					//If no output file is given, observation rinex filename will be used with suffix "_usererror"
					sprintf(sopt->rnxFile,"%s_usererror",sopt->obsFile);
				}
				//In this mode it will enter
				return 1;
			} else {
				printInfo("Disconnecting modelling and filtering (no GNSS products available)",options);
				options->workMode = wmSHOWINPUT;
				if ( options->printMeas == -1 ) options->printMeas = 1;
			}
		}
		if ( options->printMeas == -1 ) options->printMeas = 0;
		if ( options->receiverPositionSource == rpSINEX && sopt->snxFile[0] == '\0' ) {
			printError("Receiver position source set to SINEX, but no SINEX file has been included. Include one with the '-input:snx' option",options);
		}
		if ( options->receiverPositionSource >= rpRTCMbaseline && sopt->dgnssFile[0] == '\0' && sopt->rtcmFile[0] == '\0' && sopt->rtcm2File[0] == '\0' && sopt->rtcm3File[0] == '\0' ) {
			printError("Receiver position source set to RTCM, but no RTCM file has been included. Include one with the '-input:rtcm' option", options);
		}
		if( options->DGNSS ==1 ) {
			if ( sopt->navFile[0][0]=='\0' ) {
				printError("DGNSS mode activated, but no navigation file available",options);
			}
		}
	
	} else { // No observation file found
		if ( nProd == 1 && sopt->sbasFile[0] != '\0' ) {
			options->workMode = wmSBASPLOTS;
			options->onlySBASplots=1;
			if ( options->printMeas == -1 ) options->printMeas = 0;

			// SBAS plots and SBAS convert only cannot be both set
			if ( options->onlyconvertSBAS == 1 && options->onlySBASplots == 1 ) {
				printError("SBAS file conversion only and SBAS plot computation cannot be both set",options);
			}

			if ( options->NoAvailabilityPlot==1 && options->NoIonoPlot==1) {
				printError("SBAS plots mode selected, but both Availability and Iono maps are disabled. Disable just one of the plots",options);
			}
			if( options->NoAvailabilityPlot==1 && options->NoContRiskPlot == 0 ) {
				printError("SBAS Continuity plot cannot be computed without SBAS Availability plot. Both plots have to be activated in order to compute Continuity Risk plot",options);
			}
			if( options->GEOPRN==2 ) {
				printError("Selection of SBAS GEO with highest elevation is not available in SBAS plots mode. Use automatic GEO selection, or select GEO from first line data read ('-pre:geosel 1') or manually set a GEO ('-pre:geosel GEOPRN')",options);
			} 
			//Check that we have valid limits and steps for the plots
			if(options->minLatplots<-90. || options->maxLatplots>90.) {
				printError("SBAS plots latitude range must be between -90 and 90 degrees",options);
			}
			if(options->minLatplots>options->maxLatplots) {
				sprintf(messagestr,"SBAS plots latitude range is not valid. Maximum selected (%.2f) has to be greater or equal than the minimum latitude (%.2f)",options->maxLatplots,options->minLatplots);
				printError(messagestr,options);
			}
			if(options->minLonplots<-180. || options->maxLonplots>180.) {
				printError("SBAS plots longitude range must be between -180 and 180 degrees",options);
			}
			if(options->minLonplots>options->maxLonplots) {
				sprintf(messagestr,"SBAS plots longitude range is not valid. Maximum longitude (%.2f) has to be greater or equal than the minimum longitude (%.2f)",options->maxLonplots,options->minLonplots);
				printError(messagestr,options);
			}
			if(options->HorAlarmLimit<=0.) {
				printError("SBAS plots Horizontal Alarm Limit must be greater than 0",options);
			}
			if(options->VerAlarmLimit<=0.) {
				printError("SBAS plots Vertical Alarm Limit must be greater than 0",options);
			}
			if(options->AvailabilityPlotStep<0.01) {
				printError("SBAS plots Availability Step must be greater than 0 with a minimum resolution of 0.01 degrees",options);
			}
			if(options->IonoPlotStep<0.01) {
				printError("SBAS plots Iono Step must be greater than 0 with a minimum resolution of 0.01 degrees",options);
			}
			if(options->IonoPlotTimeStep<=0) {
				printError("SBAS plots Iono Time Step must be greater than 0",options);
			}
			if(options->ContRiskWindowSize<=0 ) {
				printError("Continuity Risk Sliding Window epoch size for SBAS plots must be greater than 0",options);
			}
			//To avoid problems if the user sets a value with more than 2 decimals, all decimals from the third one will be erased
			//Check minimum latitude
			sprintf(auxstr,"%.2f",options->minLatplots);
			options->minLatplots=atof(auxstr);
			//Check maximum latitude
			sprintf(auxstr,"%.2f",options->maxLatplots);
			options->maxLatplots=atof(auxstr);
			//Check minimum longitude
			sprintf(auxstr,"%.2f",options->minLonplots);
			options->minLonplots=atof(auxstr);
			//Check maximum longitude
			sprintf(auxstr,"%.2f",options->maxLonplots);
			options->maxLonplots=atof(auxstr);
			//Check Availability and Continuity plot step
			//In case of resolution higher or equal than 0.1º, we will only use one decimal for resolution (for avoiding values such as 0.17)
			//In case of resolution higher or equal than 1º, we will use no decimal resolution (for avoiding values such as 1.15)
			if(options->AvailabilityPlotStep<0.1) {
				sprintf(auxstr,"%.2f",options->AvailabilityPlotStep);
			} else if (options->AvailabilityPlotStep<1) {
				sprintf(auxstr,"%.1f",options->AvailabilityPlotStep);
			} else {
				sprintf(auxstr,"%.0f",options->AvailabilityPlotStep);
			}
			options->AvailabilityPlotStep=atof(auxstr);

			//Check Iono corrections availability plot step. We will use the same criteria as in Availability and Continuity plot step
			if(options->IonoPlotStep<0.1) {
				sprintf(auxstr,"%.2f",options->IonoPlotStep);
			} else if (options->IonoPlotStep<1) {
				sprintf(auxstr,"%.1f",options->IonoPlotStep);
			} else {
				sprintf(auxstr,"%.0f",options->IonoPlotStep);
			}
			options->IonoPlotStep=atof(auxstr);

			//Check exclusion areas
			if (options->NumSBASPlotsExclusionArea>0) {
				for(i=0;i<options->NumSBASPlotsExclusionArea;i++) {
					//Check minimum longitude is between -180 and 180
					if (options->SBASPlotsExclusionAreaDelimeters[i][0]<-180 || options->SBASPlotsExclusionAreaDelimeters[i][0]>180) {
						sprintf(messagestr,"Minimum longitude must be between -180 and 180 degrees in this exclusion area: %.2f, %.2f, %.2f, %.2f",options->SBASPlotsExclusionAreaDelimeters[i][0],options->SBASPlotsExclusionAreaDelimeters[i][1],options->SBASPlotsExclusionAreaDelimeters[i][2],options->SBASPlotsExclusionAreaDelimeters[i][3]);
						printError(messagestr,options);
					} else if (options->SBASPlotsExclusionAreaDelimeters[i][1]<-180 || options->SBASPlotsExclusionAreaDelimeters[i][1]>180) {
						sprintf(messagestr,"Maximum longitude must be between -180 and 180 degrees in this exclusion area: %.2f, %.2f, %.2f, %.2f",options->SBASPlotsExclusionAreaDelimeters[i][0],options->SBASPlotsExclusionAreaDelimeters[i][1],options->SBASPlotsExclusionAreaDelimeters[i][2],options->SBASPlotsExclusionAreaDelimeters[i][3]);
						printError(messagestr,options);
					} else if (options->SBASPlotsExclusionAreaDelimeters[i][0]>=options->SBASPlotsExclusionAreaDelimeters[i][1]) {
						sprintf(messagestr,"Maximum longitude must be greater than the minimum longitude in this exclusion area: %.2f, %.2f, %.2f, %.2f",options->SBASPlotsExclusionAreaDelimeters[i][0],options->SBASPlotsExclusionAreaDelimeters[i][1],options->SBASPlotsExclusionAreaDelimeters[i][2],options->SBASPlotsExclusionAreaDelimeters[i][3]);
						printError(messagestr,options);
					} else if (options->SBASPlotsExclusionAreaDelimeters[i][2]<-90 || options->SBASPlotsExclusionAreaDelimeters[i][2]>90) {
						sprintf(messagestr,"Minimum latitude must be between -90 and 90 degrees in this exclusion area: %.2f, %.2f, %.2f, %.2f",options->SBASPlotsExclusionAreaDelimeters[i][0],options->SBASPlotsExclusionAreaDelimeters[i][1],options->SBASPlotsExclusionAreaDelimeters[i][2],options->SBASPlotsExclusionAreaDelimeters[i][3]);
						printError(messagestr,options);
					} else if (options->SBASPlotsExclusionAreaDelimeters[i][3]<-90 || options->SBASPlotsExclusionAreaDelimeters[i][3]>90) {
						sprintf(messagestr,"Maximum latitude must be between -90 and 90 degrees in this exclusion area: %.2f, %.2f, %.2f, %.2f",options->SBASPlotsExclusionAreaDelimeters[i][0],options->SBASPlotsExclusionAreaDelimeters[i][1],options->SBASPlotsExclusionAreaDelimeters[i][2],options->SBASPlotsExclusionAreaDelimeters[i][3]);
						printError(messagestr,options);
					} else if (options->SBASPlotsExclusionAreaDelimeters[i][2]>=options->SBASPlotsExclusionAreaDelimeters[i][3]) {
						sprintf(messagestr,"Maximum latitude must be greater than the minimum latitude  in this exclusion area: %.2f, %.2f, %.2f, %.2f",options->SBASPlotsExclusionAreaDelimeters[i][0],options->SBASPlotsExclusionAreaDelimeters[i][1],options->SBASPlotsExclusionAreaDelimeters[i][2],options->SBASPlotsExclusionAreaDelimeters[i][3]);
						printError(messagestr,options);
					}
				}
			}

			//Enable SBAS corrections
			options->SBAScorrections=1;
			//Disable check of broadcast transmission time check if non set
			if ( options->brdcBlockTransTime == -1 ) options->brdcBlockTransTime = 0;
			// Disable excluding during smoothing convergence
			options->excludeSmoothingConvergence=0;
			//Stanford-ESA plots are disabled in this mode
			options->stanfordesa=0;
			//Disable transmission time of signal
			options->timeTrans=0;
			//Disable inital NPA mode for converging solution, so Klobuchar is not used for ionosphere
			options->initcoordNPA=0;
			//Disable mode switching
			options->switchmode = 0;
			//Set SBAS ionosphere if non set
			if(sopt->ionoModel==UNKNOWN_IM || sopt->ionoModel==SBASiono ) {
				options->ionoModel = SBASiono; 
			} else if (sopt->ionoModel==NoIono) {
				options->ionoModel = NoIono;
			} else {
				printError("In SBAS plots mode, only 'SBAS' or 'no' are valid options for '-model:iono' parameter",options);
			}

			//Set the output filename for availability file if non set
			if(sopt->sbasAvailplotsFile[0]=='\0'&& options->NoAvailabilityPlot==0) {
				//Extract the name of the file without the extension and the path
				#if defined (__WIN32__)
					filepointer=strrchr(sopt->sbasFile,'\\');
				#elif defined (__CYGWIN__)
					filepointer=strrchr(sopt->sbasFile,'/');
				   //In cygwin, we may have linux or windows pathes
					if(filepointer==NULL) {
						filepointer=strrchr(sopt->sbasFile,'\\');
					}
				#else
					filepointer=strrchr(sopt->sbasFile,'/');
				#endif

				if (filepointer==NULL) {
					//There is no directory path in the file
					sprintf(sopt->sbasAvailplotsFile,"SBASAvailPlots_%s.txt",sopt->sbasFile);
					sprintf(sopt->sbasAvailplotsFileNoExtension,"SBASAvailPlots_%s",sopt->sbasFile);
				} else {
					//There are directories in the path
					sprintf(sopt->sbasAvailplotsFile,"SBASAvailPlots_%s.txt",(char *)(filepointer+sizeof(char)));
					sprintf(sopt->sbasAvailplotsFileNoExtension,"SBASAvailPlots_%s",(char *)(filepointer+sizeof(char)));
				}
			} else if (sopt->sbasAvailplotsFile[0]!='\0'&& options->NoAvailabilityPlot==0) {
				removeExtension(sopt->sbasAvailplotsFile,sopt->sbasAvailplotsFileNoExtension);
			}


			//Set the output filename for continuity risk file if non set
			if(sopt->sbasRiskplotsFile[0]=='\0'&& options->NoContRiskPlot==0) {
				//Extract the name of the file without the extension and the path
				#if defined (__WIN32__)
					filepointer=strrchr(sopt->sbasFile,'\\');
				#elif defined (__CYGWIN__)
					filepointer=strrchr(sopt->sbasFile,'/');
				   //In cygwin, we may have linux or windows pathes
					if(filepointer==NULL) {
						filepointer=strrchr(sopt->sbasFile,'\\');
					}
				#else
					filepointer=strrchr(sopt->sbasFile,'/');
				#endif

				if (filepointer==NULL) {
					//There is no directory path in the file
					sprintf(sopt->sbasRiskplotsFile,"SBASRiskPlots_%s.txt",sopt->sbasFile);
					sprintf(sopt->sbasRiskplotsFileNoExtension,"SBASRiskPlots_%s",sopt->sbasFile);
				} else {
					//There are directories in the path
					sprintf(sopt->sbasRiskplotsFile,"SBASRiskPlots_%s.txt",(char *)(filepointer+sizeof(char)));
					sprintf(sopt->sbasRiskplotsFileNoExtension,"SBASRiskPlots_%s",(char *)(filepointer+sizeof(char)));
				}
			} else if (sopt->sbasRiskplotsFile[0]!='\0'&& options->NoContRiskPlot==0) {
				removeExtension(sopt->sbasRiskplotsFile,sopt->sbasRiskplotsFileNoExtension);
			}

			//Set the output filename for discontinuity file if non set
			if(sopt->sbasDiscontinuityFile[0]=='\0'&& options->NoContRiskPlot==0) {
				//Extract the name of the file without the extension and the path
				#if defined (__WIN32__)
					filepointer=strrchr(sopt->sbasFile,'\\');
				#elif defined (__CYGWIN__)
					filepointer=strrchr(sopt->sbasFile,'/');
				   //In cygwin, we may have linux or windows pathes
					if(filepointer==NULL) {
						filepointer=strrchr(sopt->sbasFile,'\\');
					}
				#else
					filepointer=strrchr(sopt->sbasFile,'/');
				#endif

				if (filepointer==NULL) {
					//There is no directory path in the file
					sprintf(sopt->sbasDiscontinuityFile,"SBASRiskDisc_%s.txt",sopt->sbasFile);
					sprintf(sopt->sbasDiscontinuityFileNoExtension,"SBASRiskDisc_%s",sopt->sbasFile);
				} else {
					//There are directories in the path
					sprintf(sopt->sbasDiscontinuityFile,"SBASRiskDisc_%s.txt",(char *)(filepointer+sizeof(char)));
					sprintf(sopt->sbasDiscontinuityFileNoExtension,"SBASRiskDisc_%s",(char *)(filepointer+sizeof(char)));
				}
			} else if (sopt->sbasDiscontinuityFile[0]!='\0'&& options->NoContRiskPlot==0) {
				removeExtension(sopt->sbasDiscontinuityFile,sopt->sbasDiscontinuityFileNoExtension);
			}



			//Set the output filename for ionosphere availability if non set
			if(sopt->sbasIonoplotsFile[0]=='\0' && options->NoIonoPlot==0) {
				//Extract the name of the file without the extension and the path
				#if defined (__WIN32__)
					filepointer=strrchr(sopt->sbasFile,'\\');
				#elif defined (__CYGWIN__)
					filepointer=strrchr(sopt->sbasFile,'/');
				   //In cygwin, we may have linux or windows pathes
					if(filepointer==NULL) {
						filepointer=strrchr(sopt->sbasFile,'\\');
					}
				#else
					filepointer=strrchr(sopt->sbasFile,'/');
				#endif

				if (filepointer==NULL) {
					//There is no directory path in the file
					sprintf(sopt->sbasIonoplotsFile,"SBASIonoPlots_%s.txt",sopt->sbasFile);
					sprintf(sopt->sbasIonoplotsFileNoExtension,"SBASIonoPlots_%s",sopt->sbasFile);
				} else {
					//There are directories in the path
					sprintf(sopt->sbasIonoplotsFile,"SBASIonoPlots_%s.txt",(char *)(filepointer+sizeof(char)));
					sprintf(sopt->sbasIonoplotsFileNoExtension,"SBASIonoPlots_%s",(char *)(filepointer+sizeof(char)));
				}
			} else if(sopt->sbasIonoplotsFile[0]!='\0' && options->NoIonoPlot==0) {
				removeExtension(sopt->sbasIonoplotsFile,sopt->sbasIonoplotsFileNoExtension);
			}

			//Print INFO Messages
			if (options->NoAvailabilityPlot==1) {
				printInfo("Compute Iono Corrections Availability plot for a Fault-Free Receiver",options);
			} else if (options->NoIonoPlot==1 && options->NoContRiskPlot==0) {
				printInfo("Compute SBAS PA Availability and Continuity Risk plots for a Fault-Free Receiver",options);
			} else if (options->NoIonoPlot==1 && options->NoContRiskPlot==1) {
				printInfo("Compute SBAS PA Availability plot for a Fault-Free Receiver",options);
			} else {
				printInfo("Compute SBAS PA Availability, Continuity Risk and Iono Corrections Availability plots for a Fault-Free Receiver",options);
			}
			if(options->SBASHourlyMaps==1) {
				printInfo("Hourly plots option is enabled. Each hour will be written in a separate file",options);
			}
			sprintf(messagestr,"Elevation mask: %.2f degrees",options->elevationMask/d2r);
			printInfo(messagestr,options);

			sprintf(messagestr,"Minimum latitude  for plots: %7.2f degrees",options->minLatplots);
			printInfo(messagestr,options);
			sprintf(messagestr,"Maximum latitude  for plots: %7.2f degrees",options->maxLatplots);
			printInfo(messagestr,options);
			sprintf(messagestr,"Minimum longitude for plots: %7.2f degrees",options->minLonplots);
			printInfo(messagestr,options);
			sprintf(messagestr,"Maximum longitude for plots: %7.2f degrees",options->maxLonplots);
			printInfo(messagestr,options);
			for(i=0;i<options->NumSBASPlotsInclusionArea;i++) {
				sprintf(messagestr,"Inclusion area #%d (MinLon, MaxLon, MinLat, MaxLat): %7.2f %7.2f %6.2f %6.2f (degrees)",i+1,options->SBASPlotsInclusionAreaDelimeters[i][0],options->SBASPlotsInclusionAreaDelimeters[i][1],options->SBASPlotsInclusionAreaDelimeters[i][2],options->SBASPlotsInclusionAreaDelimeters[i][3]);
				printInfo(messagestr,options);
			}
			for(i=0;i<options->NumSBASPlotsExclusionArea;i++) {
				sprintf(messagestr,"Exclusion area #%d (MinLon, MaxLon, MinLat, MaxLat): %7.2f %7.2f %6.2f %6.2f (degrees)",i+1,options->SBASPlotsExclusionAreaDelimeters[i][0],options->SBASPlotsExclusionAreaDelimeters[i][1],options->SBASPlotsExclusionAreaDelimeters[i][2],options->SBASPlotsExclusionAreaDelimeters[i][3]);
				printInfo(messagestr,options);
			}
			if(options->SBASPlotsRecHeight==0.) {
				sprintf(messagestr,"Receiver height for plots: %.2f metres (at sea level)",options->SBASPlotsRecHeight);
			} else {
				sprintf(messagestr,"Receiver height for plots: %.2f metres",options->SBASPlotsRecHeight);
			}
			printInfo(messagestr,options);
			if (options->NoAvailabilityPlot==0) {
				sprintf(messagestr,"Horizontal Alarm Limit: %3.2f metres",options->HorAlarmLimit);
				printInfo(messagestr,options);
				sprintf(messagestr,"Vertical   Alarm Limit: %3.2f metres",options->VerAlarmLimit);
				printInfo(messagestr,options);
			}
			if (options->NoAvailabilityPlot==0 && options->NoContRiskPlot==0) {
				sprintf(messagestr,"Step for SBAS Availability and Continuity Risk:    %2.2f degrees",options->AvailabilityPlotStep);
				printInfo(messagestr,options);
			} else if (options->NoAvailabilityPlot==0 && options->NoContRiskPlot==1) {
				sprintf(messagestr,"Step for SBAS Availability: %.2f degrees",options->AvailabilityPlotStep);
				printInfo(messagestr,options);
			}
			if (options->NoIonoPlot==0) {
				sprintf(messagestr,"Step for SBAS Ionosphere Corrections Availability: %2.2f degrees",options->IonoPlotStep);
				printInfo(messagestr,options);
			}

			if (options->ionoModel == NoIono) {
				if (options->NoAvailabilityPlot==0 && options->NoContRiskPlot==0) {
					printInfo("SBAS ionosphere is disabled in SBAS Availability and Continuity Risk plots",options);
				} else if (options->NoContRiskPlot==0) {
					printInfo("SBAS ionosphere is disabled in SBAS Availability plot",options);
				}
			}


			if (options->NoAvailabilityPlot==0) {
				sprintf(messagestr,"Output file for SBAS Availability plots:            %s",sopt->sbasAvailplotsFile);
				printInfo(messagestr,options);
			}
			if (options->NoContRiskPlot==0) {
				sprintf(messagestr,"Output file for SBAS Continuity Risk plots:         %s",sopt->sbasRiskplotsFile);
				printInfo(messagestr,options);
				sprintf(messagestr,"Output file for SBAS discontinuities:               %s",sopt->sbasDiscontinuityFile);
				printInfo(messagestr,options);
			}
			if (options->NoIonoPlot==0) {
				sprintf(messagestr,"Output file for SBAS Ionosphere Availability plots: %s",sopt->sbasIonoplotsFile);
				printInfo(messagestr,options);
			}
			return 1;
		} else if ( nProd == 1 ) {
			options->workMode = wmSHOWPRODUCT;
			if ( options->printMeas == -1 ) options->printMeas = 0;
			printInfo("Show satellite information mode", options);
		} else if ( nProd == 2 ) {
			options->workMode = wmCOMPAREORBITS;
			if ( options->printMeas == -1 ) options->printMeas = 0;
			printInfo("Compare orbits & clocks mode", options);
			if (sopt->numOrb!=sopt->numClk) {
				sprintf(messagestr, "Inconsistent number of orb and clk input files (%d vs %d)", sopt->numOrb, sopt->numClk);
				printError(messagestr,options);
			}
		} else {
			if (printProgress==1) {
				printProgressConvert=1;	
			}
			// RTCM unknown version
			RTCMversion = 0;
			if ( options->printMeas == -1 ) options->printMeas = 0;
			if ( sopt->rtcmFile[0] != '\0' ) {
				options->RTCMmode = RTCMCheckVersion; // Check what version of RTCM is the binary file
				if ( !(fdRTCM = fopen(sopt->rtcmFile, "rb")) ) {
					sprintf(messagestr, "Problem reading the RTCM binary file [%s]", sopt->rtcmFile);
					printError(messagestr, options);
				}
				rtcm2 = malloc(sizeof(TRTCM2));
				initRTCM2(rtcm2);
				rtcm3 = malloc(sizeof(TRTCM3));
				initRTCM3(rtcm3);
				RTCMversion = converterRTCM2(fdRTCM, rtcm2, NULL, NULL, NULL, NULL, options);
				if ( RTCMversion == 2 ) {
					strcpy(sopt->rtcm2File, sopt->rtcmFile);
					sprintf(messagestr, "Processing the RTCM v2.x binary file [%s] ...", sopt->rtcm2File);
					printInfo(messagestr, options);
				} else {
					RTCMversion = converterRTCM3(fdRTCM, rtcm3, NULL, NULL, epoch, options);
					strcpy(sopt->rtcm3File, sopt->rtcmFile);
					if ( RTCMversion == 3 ) {
						sprintf(messagestr, "Processing the RTCM v3.x binary file [%s] ...", sopt->rtcm3File);
						printInfo(messagestr, options);
					} else {
						fclose(fdRTCM);
						free(rtcm2);
						free(rtcm3);
						sprintf(messagestr, "File [%s] format unknown.", sopt->rtcm3File);
						printError(messagestr, options);
					}
				}
				fclose(fdRTCM);
				free(rtcm2);
				free(rtcm3);
				rtcm2 = NULL;
				rtcm3 = NULL;
			}
			// RTCM v2.x conversion 
			if ( sopt->rtcm2File[0] != '\0' || RTCMversion == 2 ) {
				if ( !(fdRTCM2 = fopen(sopt->rtcm2File, "rb")) ) {
					sprintf(messagestr,"Problem reading the RTCM binary file [%s]", sopt->rtcm2File);
					printError(messagestr, options);
				} else if ( options->rtcmYear == 0 || options->rtcmMonth == 0 || options->rtcmDay == 0 ) {
					sprintf(messagestr, "Option \"-input:rtcm:initdate\" must be set");
					printError(messagestr, options);
				} else if ( options->rtcmHour == -1 ) {
					sprintf(messagestr, "Option \"-input:rtcm:inithour\" must be set");
					printError(messagestr, options);
				} else {
					// Initialise
					rtcm2 = malloc(sizeof(TRTCM2));
					initRTCM2(rtcm2);

					// Check to ensure the format
					options->RTCMmode = RTCMCheckVersion;
					RTCMversion = converterRTCM2(fdRTCM2, rtcm2, NULL, NULL, NULL, NULL, options);
					if ( RTCMversion != 2 ) {
						fclose(fdRTCM2);
						free(rtcm2);
						sprintf(messagestr, "File [%s] does not have RTCM v2.x format.", sopt->rtcm2File);
						printError(messagestr, options);
					}

					options->RTCMmode = ConvertRTCM2;
					fileASCIIcorrections = malloc(sizeof(char) * MAX_INPUT_LINE);
					fileASCIIantenna = malloc(sizeof(char) * MAX_INPUT_LINE);
					doy = date2doy(options->rtcmYear, options->rtcmMonth, options->rtcmDay);

					if ( sopt->dataASCIIFile[0] == '\0' ) {
						// Build the full path and filename for output ASCII data file
						sprintf(fileASCIIcorrections,"%s%03d_corrections.asc", pathRTCMpointer, doy);
					} else strcpy(fileASCIIcorrections,sopt->dataASCIIFile);
					if ( sopt->antennaASCIIFile[0] == '\0' ) {
						// Build the full path and filename for output ASCII data file
						sprintf(fileASCIIantenna,"%s%03d_antenna.asc", pathRTCMpointer, doy);
					} else strcpy(fileASCIIantenna,sopt->antennaASCIIFile);

					// Check if file already exsits
					/*if ( access(fileASCIIcorrections,F_OK) != -1 ) {
						// File exists
						sprintf(messagestr, "The file [%s] already exist. Conversion stopped", fileASCIIcorrections);
						printError(messagestr, options);
					}*/
					
					// Check if file already exsits
					/*if ( access(fileASCIIantenna, F_OK) != -1 ) {
						// File exists
						sprintf(messagestr, "The file [%s] already exist. Conversion stopped", fileASCIIantenna);
						printError(messagestr, options);
					}*/

					//Create directory recursively if needed
					ret=mkdir_recursive(fileASCIIcorrections);
					if(ret!=0) {
					   //Error when creating the directory, and it is not due to that the directory already exists
					   sprintf(messagestr,"When creating [%s] folder for writing corrections",fileASCIIcorrections);
					   printError(messagestr,options);
					}

					//Create directory recursively if needed
					ret=mkdir_recursive(fileASCIIantenna);
					if(ret!=0) {
					   //Error when creating the directory, and it is not due to that the directory already exists
					   sprintf(messagestr,"When creating [%s] folder for writing antenna data",fileASCIIantenna);
					   printError(messagestr,options);
					}

					// Convert the binary file RTCM v2.x
					ret = converterRTCM2(fdRTCM2, rtcm2, fileASCIIcorrections, fileASCIIantenna, NULL, NULL, options);

					// Output message
					if ( ret == 1 ) {
						sprintf(messagestr, "RTCM binary file [%s] has been converted to files [%s] (antenna information) and [%s] (corrections)", sopt->rtcm2File, fileASCIIantenna, fileASCIIcorrections);
						printInfo(messagestr, options);
					}
					fclose(fdRTCM2);
					free(rtcm2);
					free(fileASCIIcorrections);
					free(fileASCIIantenna);
					if (printProgressConvert==1) {
						fprintf(options->terminalStream,"Percentage converted: %3d%%%10s%c",100,"",options->ProgressEndCharac);
						#if !defined(__WIN32__)
							//This is to clear terminal for characters after finishing (in Windows is not necessary as it adds a newline when the process finishes)
							if (options->ProgressEndCharac=='\r') {
								fprintf(options->terminalStream,"%60s%c","",options->ProgressEndCharac);
							}
							//Enable cursor again
							if (sopt->disableCursor==1) {
								fprintf(options->terminalStream,"%s",enableCursor);
							}
						#endif
						fflush(options->terminalStream);
					}
					exit(0);
				}
			}
			// RTCM v3.x conversion 
			if ( sopt->rtcm3File[0] != '\0' || RTCMversion == 3 ) {
				fdRTCM3 = fopen(sopt->rtcm3File, "rb");
				if ( fdRTCM3 == NULL ) {
					sprintf(messagestr, "Problem reading the RTCM binary file [%s]", sopt->rtcm3File);
					printError(messagestr, options);
				} else if ( options->rtcmYear == 0 || options->rtcmMonth == 0 || options->rtcmDay == 0 ) {
					sprintf(messagestr, "Option \"-input:rtcm:initdate\" must be set");
					printError(messagestr,options);
				} else {
					// Initialise
					rtcm3 = malloc(sizeof(TRTCM3));
					initRTCM3(rtcm3);

					// Check to ensure the format
					options->RTCMmode = RTCMCheckVersion;
					RTCMversion = converterRTCM3(fdRTCM3, rtcm3, NULL, NULL, epoch, options);
					if ( RTCMversion != 3 ) {
						fclose(fdRTCM3);
						free(rtcm3);
						sprintf(messagestr, "File [%s] does not have RTCM v3.x format.", sopt->rtcm3File);
						printError(messagestr, options);
					}

					// Continue with the normal procedure
					options->RTCMmode = ConvertRTCM3;

					// Get DoY from date for RINEX filename purposes
					doy = date2doy(options->rtcmYear,options->rtcmMonth,options->rtcmDay);
					options->rtcmDoy = doy;
					if ( doy == -1 ) {
						sprintf(messagestr,"Problem with the day of the year");
						printError(messagestr,options);
					} else {
						sprintf(strDoy,"%03d",doy);
					}

					if ( sopt->rnxFile[0] == '\0' ) {
						// Build the full path and filename for output RINEX file
						strcpy(fileRINEXpointer,pathRTCMpointer);
						strcat(fileRINEXpointer,strDoy);
						strcat(fileRINEXpointer,"0.");
						sprintf(strYear,"%02d",options->rtcmYearShort);
						strcat(fileRINEXpointer,strYear);
						strcat(fileRINEXpointer,"o");
					} else strcpy(fileRINEXpointer,sopt->rnxFile);

					// Check if file already exsits
					/*if ( access(fileRINEXpointer,F_OK) != -1 ) {
						// File exists
						sprintf(messagestr,"The file [%s] already exist. Conversion stopped",fileRINEXpointer);
						printError(messagestr,options);
					}*/

					//Create directory recursively if needed
					ret=mkdir_recursive(fileRINEXpointer);
					if(ret!=0) {
					   //Error when creating the directory, and it is not due to that the directory already exists
					   sprintf(messagestr,"When creating [%s] folder for writing corrections",fileRINEXpointer);
					   printError(messagestr,options);
					}
					//Init Epoch structure
					initEpoch(epoch,options);

					// Convert the binary file RTCM v3.x
					ret = converterRTCM3(fdRTCM3,rtcm3,fileRINEXpointer,NULL,epoch,options);
					if ( ret == -1 ) {
						sprintf(messagestr,"Problem reading the RTCM binary file [%s]",sopt->rtcm3File);
						printError(messagestr,options);
					}

					// Output message
					if ( ret ==1 || ret == 2 ) {
						if ( options->rinexVersion == 2 ) sprintf(messagestr,"RTCM binary file [%s] has been converted to file [%s], which is a RINEX version 2.11",sopt->rtcm3File,fileRINEXpointer);
						if ( options->rinexVersion == 3 ) sprintf(messagestr,"RTCM binary file [%s] has been converted to file [%s], which is a RINEX version 3.00",sopt->rtcm3File,fileRINEXpointer);
						printInfo(messagestr, options);
					}
					free(rtcm3);
				}
				fclose(fdRTCM3);
				if (printProgressConvert==1) {
					fprintf(options->terminalStream,"Percentage converted: %3d%%%10s%c",100,"",options->ProgressEndCharac);
					#if !defined(__WIN32__)
						//This is to clear terminal for characters after finishing (in Windows is not necessary as it adds a newline when the process finishes)
						if (options->ProgressEndCharac=='\r') {
							fprintf(options->terminalStream,"%60s%c","",options->ProgressEndCharac);
						}
						//Enable cursor again
						if (sopt->disableCursor==1) {
							fprintf(options->terminalStream,"%s",enableCursor);
						}
					#endif
					fflush(options->terminalStream);
				}
				exit(0);
			}
			if ( options->SBAScorrections == 1 ) {
				sprintf(messagestr,"SBAS input selected, but no GNSS sources given. For just converting SBAS files, use the '-onlyconvert' option");
			} else {
				sprintf(messagestr,"No observation file found, but there are %d different GNSS sources. To compare products, provide 2 different sources. To parse a products file, provide 1 single source",nProd);
			}
			printError(messagestr,options);
		} 
	}
	if ( sopt->antFile[0] != '\0' && sopt->conFile[0] != '\0' ) {
		printError("-input:ant and -input:con cannot be both set",options);
	}
	if ( preciseProductsAvailable ) {
		if ( options->workMode == wmDOPROCESSING ) {
			if (sopt->antFile[0]=='\0' && sopt->conFile[0]=='\0' && (options->satellitePhaseCenter || options->antennaData == adANTEX)) {
				printError("When positioning with precise products, an ANTEX or Constellation file is required (-input:ant or -input:con)",options);
			}	
		} else if (options->workMode==wmCOMPAREORBITS || options->workMode==wmSHOWPRODUCT) {
			if (sopt->antFile[0]=='\0' && sopt->conFile[0]=='\0' && options->satellitePhaseCenter) {
				printError("Precise orbits and 'Satellite Phase Centre' corrections are specified, but no ANTEX or Constellation file is found",options);
			}
		}
	}
		
	if (options->workMode == wmDOPROCESSING) {
		// Navigation mode and observables
		if (sopt->navMode==NMppp) {
			options->discardEclipsedSatellites = 1;
			options->csBW = 1;
			options->csLI = 1;
			options->csL1C1 = 0;
			options->csLLI = 1;
			options->ionoModel = NoIono;
			options->troposphericCorrection = 1;
			options->tropNominal = SimpleNominal; 
			options->tropMapping = NiellMapping;
			options->satellitePhaseCenter = 1;
			options->antennaData = adANTEX;
			if (options->ARPData==arpUNKNOWN) options->ARPData = arpRINEX;
			options->solidTidesCorrection = 1;
			options->gravitationalCorrection = 1;
			options->receiverPhaseVar=1;
			options->satellitePhaseVar=1;
			options->solutionMode = PPPMode;
			// Carrier phase + pseudorange by default
			if (sopt->navObservables==NOND) sopt->navObservables = NOcarrierphase;
			// Static by default
			if (sopt->navKinematics==NKND) sopt->navKinematics = NKstatic;
			// Disable check of transmission time in broadcast messages if user has not set anything and we are in PPP
			if ( options->brdcBlockTransTime == -1 ) options->brdcBlockTransTime = 0;
			// Set GDOP threshold if non set
			if (options->GDOPthreshold == -1) options->GDOPthreshold = 1;
			printInfo("Processing with precise products",options);
		} else if (sopt->navMode==NMstandalone) {
			options->discardEclipsedSatellites = 0;
			options->csBW = 0;
			options->csLI = 0;
			options->csL1C1 = 0;
			options->csLLI = 0;
			options->ionoModel = Klobuchar;
			// Adria P1P2 DCB source for SPP			
			options->p1p2dcbModel = p1p2RINEX;
			options->troposphericCorrection = 1;
			options->tropNominal = UNB3Nominal; 
			options->tropMapping = SimpleMapping;
			options->satellitePhaseCenter = 0;
			options->antennaData = adNONE;
			if (options->ARPData==arpUNKNOWN) options->ARPData = arpNONE;
			options->solidTidesCorrection = 0;
			options->gravitationalCorrection = 0;
			options->receiverPhaseVar=0;
			options->satellitePhaseVar=0;
			options->solutionMode = SPPMode;
			//options->usableFreq[GPS][2] = 0;
			// Pseudorange only
			if (sopt->navObservables==NOND) sopt->navObservables = NOpseudorange;
			// Dynamic by default
			if (sopt->navKinematics==NKND) sopt->navKinematics = NKkinematic;
			// Enable check of transmission time in broadcast messages if user has not set anything and we are not in SBAS
			if ( options->brdcBlockTransTime == -1 ) options->brdcBlockTransTime = 1;
			// Set GDOP threshold if non set
			if (options->GDOPthreshold == -1) options->GDOPthreshold = 0;
			printInfo("Processing with broadcast products",options);
		}
		if (sopt->navMode==NMppp && sopt->navObservables==NOpseudorange) {
			options->estimateTroposphere = 0;
			options->totalFilterMeasurements = 1;
			options->measurement[0] = PC;
			for(i=0;i<MAX_GNSS;i++) {
				for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
					options->weightMode[i][j][0]=FixedWeight;
					options->WeightConstantsValues[i][j][0][0] = 3.;
				}
			}
			options->usePhase = 0;
			options->windUpCorrection = 0;
		} else if (sopt->navMode==NMppp && sopt->navObservables==NOcarrierphase) {
			options->estimateTroposphere = 1;
			options->totalFilterMeasurements = 2;
			options->measurement[0] = PC;
			options->measurement[1] = LC;
			for(i=0;i<MAX_GNSS;i++) {
				for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
					options->weightMode[i][j][0]=FixedWeight;
					options->weightMode[i][j][1]=FixedWeight;
					options->WeightConstantsValues[i][j][0][0] = 3.;
					options->WeightConstantsValues[i][j][1][0] = 0.03;
				}
			}
			options->usePhase = 1;
			options->windUpCorrection = 1;
		} else if (sopt->navMode==NMstandalone && sopt->navObservables==NOpseudorange) { 
			options->estimateTroposphere = 0;
			options->totalFilterMeasurements = 1;
			options->measurement[0] = C1C;  // C/A
			options->usePhase = 0;
			for(i=0;i<MAX_GNSS;i++) {
				for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
					options->weightMode[i][j][0]=FixedWeight;
					options->WeightConstantsValues[i][j][0][0] = 1.;
				}
			}
			options->windUpCorrection = 0;
		} else if (sopt->navMode==NMstandalone && sopt->navObservables==NOcarrierphase) {
			options->estimateTroposphere = 0;
			options->totalFilterMeasurements = 2;
			options->measurement[0] = C1C;  // C/A
			options->measurement[1] = L1P;  // L1
			options->usePhase = 1;
			for(i=0;i<MAX_GNSS;i++) {
				for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
					options->weightMode[i][j][0]=FixedWeight;
					options->weightMode[i][j][1]=FixedWeight;
					options->WeightConstantsValues[i][j][0][0] = 1.;
					options->WeightConstantsValues[i][j][1][0] = 0.01;
				}
			}
			options->windUpCorrection = 1;
		}


		// Navigation kinematics
		if (sopt->navKinematics==NKstatic) {
			options->filterParams[PHI_PAR][DR_UNK] = 1;
			options->filterParams[Q_PAR][DR_UNK] = 0;
		} else if (sopt->navKinematics==NKkinematic) {
			options->filterParams[PHI_PAR][DR_UNK] = 0;
			options->filterParams[Q_PAR][DR_UNK] = SIGMA_INF_DR*SIGMA_INF_DR;
		}

		// Filter measurements
		if (sopt->totalFilterMeasurements!=-1) {
			options->totalFilterMeasurements = sopt->totalFilterMeasurements;
			options->usePhase = 0;
			options->estimateTroposphere = 0;
			auxstr[0]='\0';
			if(options->totalFilterMeasurements>MAX_FILTER_MEASUREMENTS) {
				sprintf(messagestr,"Maximum measurements for the filter are %d, but %d measurements were given",MAX_FILTER_MEASUREMENTS,options->totalFilterMeasurements);
				printError(messagestr,options);
			}
			for (i=0;i<options->totalFilterMeasurements;i++) {
				options->measurement[i] = sopt->measurement[i];
				if (whatIs(options->measurement[i]) == CarrierPhase) {
					options->usePhase = 1;
					options->estimateTroposphere = 1;
				}
			}
		}


		//In SBAS mode, force C1C measurement for navigation
		if (options->SBAScorrections==1) {
			options->estimateTroposphere = 0;
			options->totalFilterMeasurements = 1;
			options->measurement[0] = C1C;  // C/A
			options->usePhase = 0;
			for(i=0;i<MAX_GNSS;i++) {
				for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
					options->weightMode[i][j][0]=SBASOnlyWeight;
				}
			}
			options->windUpCorrection = 0;
			// Set SBAS processing mode for OUTPUT message
			options->solutionMode = SBASMode;
		} else if (options->DGNSS==1) {
			options->estimateTroposphere = 0;
			options->totalFilterMeasurements = 1;
			options->measurement[0] = C1C;  // C/A
			for(i=0;i<MAX_GNSS;i++) {
				for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
					options->weightMode[i][j][0]=DGNSSOnlyWeight;
					
				}
			}
			options->windUpCorrection = 0;
		}

		if (options->totalFilterMeasurements> 1 && options->stanfordesa==1) {
			printError("Stanford-ESA can not be enabled if filter measurements is greater than 1",options);
		}
		
		// Filter weights
		for (k=0;k<options->totalFilterMeasurements;k++) {
			for(i=0;i<MAX_GNSS;i++) {
				for(j=0;j<MAX_SATELLITES_PER_GNSS;j++) {
					if (sopt->weightMode[i][j][k]!=UnknownWeight) {
						//User provided a specific weight for this satellite
						if (sopt->CombineWeightMode[i][j][k]!=CombineWeightUnknown) {
							switch(sopt->CombineWeightMode[i][j][k]) {
								case ComputedOnly:
									//Default method when no weight method provided (use fixed weight for SPP,PPP or only SBAS or DGNSS computed sigma)
									break;
								case ComputedPlusUser:
									if (options->weightMode[i][j][k]==SBASOnlyWeight) {
										options->weightMode[i][j][k]=SBASFixedWeight+sopt->weightMode[i][j][k];
									} else if (options->weightMode[i][j][k]==DGNSSOnlyWeight) {
										options->weightMode[i][j][k]=DGNSSFixedWeight+sopt->weightMode[i][j][k];
									}
									break;
								case UserOnly:
									options->weightMode[i][j][k]=sopt->weightMode[i][j][k];	
									break;
								default:
									//UnknownWeight (not set). The default method will be used
									break;
							}
						} else {
							//No combine option provided. Use the provided weight mode
							options->weightMode[i][j][k]=sopt->weightMode[i][j][k];
						}

						if (sopt->WeightConstantsValues[i][j][k][0]==0.&& sopt->WeightConstantsValues[i][j][k][1]==0.) {
							if (j>0) { //Don't print error for PRN=0. The user can only set values for PRN=0 by setting the same value to all constellation
								sprintf(messagestr,"Constants 'a' and 'b' cannot be both 0 for '%s' weight mode, %s %d and filter measurement %d (%s)",WeightModeNum2WeightModestr(sopt->weightMode[i][j][k]),gnsstype2gnssstr(i),j,k+1,meastype2measstr(options->measurement[k]));
								printError(messagestr,options);
							}
						} else if (sopt->WeightConstantsValues[i][j][k][0]==-2 && sopt->navMode==NMppp) {
							sprintf(messagestr,"URA value for weights cannot be used in PPP mode for '%s' weight mode, %s %d and filter measurement %d (%s)",WeightModeNum2WeightModestr(sopt->weightMode[i][j][k]),gnsstype2gnssstr(i),j,k+1,meastype2measstr(options->measurement[k]));
								printError(messagestr,options);
						}
						options->WeightConstantsValues[i][j][k][0]=sopt->WeightConstantsValues[i][j][k][0];
						options->WeightConstantsValues[i][j][k][1]=sopt->WeightConstantsValues[i][j][k][1];
						options->WeightConstantsValues[i][j][k][2]=sopt->WeightConstantsValues[i][j][k][2];

					} else if (sopt->navMode==NMppp) {
						//If no weight is given, and is not a PC or LC combination, set default weights
						//to 1 and 0.01 instead of 3 and 0.03
						if (whatIs(options->measurement[k]) == CarrierPhase) {
							if (options->measurement[k]!=LC) {
								options->WeightConstantsValues[i][j][k][0]=0.01;
							}
						} else {
							if (options->measurement[k]!=PC) {
								options->WeightConstantsValues[i][j][k][0]=1.;
							}
						}
					}

					if (sopt->SNRweightComb[i][j][k]!=SNRWeightUnknown) {
						options->SNRweightComb[i][j][k]=sopt->SNRweightComb[i][j][k];
						options->SNRweightCombVal[i][j][k][0]=sopt->SNRweightCombVal[i][j][k][0];
						options->SNRweightCombVal[i][j][k][1]=sopt->SNRweightCombVal[i][j][k][1];
					}
				}
			}
		}
			
		// Filter parameters change
		for (i=0;i<3;i++) {
			for (j=0;j<MAX_PAR;j++) {
				if (sopt->filterParams[i][j]!=-1) {
					options->filterParams[i][j] = sopt->filterParams[i][j];
				}
			}
		}
	
		// Smoothing
		if (options->smoothEpochs!=0) {
			if (options->SBAScorrections==1 && options->onlySBASiono==0) {
				// If SBAS corrections are activated, only C1C will be used smoothed with L1P
				options->smoothMeas[0] = L1P;
				for (i=1;i<MAX_FILTER_MEASUREMENTS;i++) {
					options->smoothMeas[i] = NA;
				}
			 } else if ( options->DGNSS == 1 ) {
				if ( sopt->smoothWith[0] != NA ) {
					options->smoothMeas[0] = sopt->smoothWith[0];
					// Check if carrier phase is used to smooth the code
					if ( options->smoothMeas[0] == L1C || options->smoothMeas[0] == L1P ) {
						options->usePhase = 1;
					}
					if ( options->smoothMeas[0] == L2C || options->smoothMeas[0] == L2P ) {
						options->usePhase = 1;
					}
					if ( options->smoothMeas[0] == G1C || options->smoothMeas[0] == G1P ) {
						options->usePhase = 1;
					}
					if ( options->smoothMeas[0] == DF ) {
						options->usePhase = 1;
						options->DF = 1;
					}
				} else {
					options->smoothMeas[0] = L1P;
				}
				for ( i = 1; i < MAX_FILTER_MEASUREMENTS; i++ ) {
					options->smoothMeas[i] = NA;
				}
			} else {
				j=0;
				for (i=0;i<MAX_FILTER_MEASUREMENTS;i++) {
					if (sopt->smoothWith[i]!=NA) {
						if(whatIs(sopt->smoothWith[i])!=CarrierPhase) {
							sprintf(messagestr,"Measurement %s to smooth with is not a carrier phase",meastype2measstr(sopt->smoothWith[i]));
							printError(messagestr,options);
						}
						j++;
						options->smoothMeas[i] = sopt->smoothWith[i];
						// Check if carrier phase is used to smooth the code
						if ( options->smoothMeas[i] == L1C || options->smoothMeas[i] == L1P ) {
							options->usePhase = 1;
						}
						if ( options->smoothMeas[i] == L2C || options->smoothMeas[i] == L2P ) {
							options->usePhase = 1;
						}
						if ( options->smoothMeas[i] == G1C || options->smoothMeas[i] == G1P ) {
							options->usePhase = 1;
						}
						if ( options->smoothMeas[i] == DF ) {
							options->usePhase = 1;
							options->DF = 1;
						}
					} else {
						options->smoothMeas[i] = NA;
					}
				}
				if(j==0) {
					//Number of smoothing epochs set, but no measurement to smooth with
					sprintf(messagestr,"Number of smoothing epochs set to %d, but no measurement to smooth with has been set. Use parameter '-pre:smoothMeas' to set this measurement. For example, to process in SPP with C1C smoothed with L1P measurement, use parameter '-pre:smoothMeas 1 L1P'",options->smoothEpochs);
					printError(messagestr,options);
				}
			}
		} else if (options->smoothEpochs==0 && sopt->numsmoothWith>0) {
			sprintf(messagestr,"Number of smoothing epochs is 0, but a measurement to smooth with was given. Use parameter '-pre:smooth' to set the number of smoothing epochs");
			printError(messagestr,options);
		}
		
		// Ionospheric model 
		if (sopt->ionoModel!=UNKNOWN_IM) {
			options->ionoModel = sopt->ionoModel; 
			printInfo("Forcing ionospheric model for this processing",options);
		} else if (sopt->ionoModel==UNKNOWN_IM && options->SBAScorrections==1) {
			//If we have activated SBAS mode, but we have not set any ionosphere model, use SBAS iono. Else use the model given by parameters
			options->ionoModel = SBASiono; 
			printInfo("Forcing ionospheric model for this processing",options);
		}

		if (options->ionoModel==IONEX) {
			if (sopt->inxFile[0]=='\0') {  // No IONEX source
				printError("Unable to get ionospheric model from IONEX input file. Please use '-input:inx'",options);
				return 0;
			}
		} else if (options->ionoModel==FPPP) {
			if (sopt->fppFile[0]=='\0') {  // No FPPP source
				printError("Unable to get ionospheric model from FPPP input file. Please use '-input:fppp'",options);
				return 0;
			}
			if (options->ionoRMS <=0) {
				sprintf(messagestr,"Max RMS value is %2.2f, but it must be greater than zero",options->ionoRMS);
				printError(messagestr,options);
				return 0;
			}	
		} else if (options->ionoModel==Klobuchar) {
			if (sopt->numNav==0 && sopt->klbFile[0]=='\0') { // No Klobuchar source
				printError("Unable to get ionospheric Klobuchar model from input data. Please use '-input:nav' or '-input:klb'",options);
				return 0;
			}
		} else if (options->ionoModel==BeiDou) {
			if (sopt->numNav==0 && sopt->beiFile[0]=='\0') { // No Beidou source
				printError("Unable to get ionospheric BeiDou model from input data. Please use '-input:nav' or '-input:bds'",options);
				return 0;
			}
		} else if (options->ionoModel==neQuick) {
			if (sopt->numNav==0 && sopt->neqFile[0]=='\0') { // No NeQuick source
				printError("Unable to get ionospheric NeQuick model from input data. Please use '-input:nav' or '-input:neq'",options);
				return 0;
			}
		} else if (options->ionoModel==SBASiono) {
			if(options->SBAScorrections==0 && sopt->SBASIONOFile[0]=='\0') { // No SBAS source
				printError("Unable to get ionospheric SBAS model from input data. Please use '-input:sbasiono'",options);
				return 0;
			} else if (options->onlyconvertSBAS==1) {
				printError("SBAS file conversion only selected, which is not possible when processing standalone GPS with SBAS iono",options);
			} else {
				if(options->SBAScorrections==0) {
					options->onlySBASiono=1;
					strcpy(sopt->sbasFile,sopt->SBASIONOFile);
					if( options->GEOPRN==2 ) {
						printError("Selection of SBAS GEO with highest elevation is not available when using only SBAS ionosphere. Use automatic GEO selection, or select GEO from first line data read ('-pre:geosel 1') or manually set a GEO ('-pre:geosel GEOPRN')",options);
					}
					if ( options->filterIterations == 2 ) {
						printError("SBAS ionosphere selected, which is incompatible with backward processing. Disable backward processing for SBAS ionosphere model",options);
					}
					options->SBAScorrections=1;
				}
			}
		}
	
/*
		// Tropospheric model
		if (sopt->tropModel!=UNKNOWN_TM) {
			options->tropModel = sopt->tropModel;
			if (options->tropModel == NoTrop) {
				if (options->estimateTroposphere) {
					printInfo("Disconecting tropospheric estimation (no tropospheric nominal value computed)",options);
					options->estimateTroposphere = 0;
				}
			}
		}
*/

		// Tropospheric model: specific configuration check
		if (sopt->troposphericCorrection!=-1) options->troposphericCorrection = sopt->troposphericCorrection;

		// Tropospheric model: Nominal
		if (sopt->tropNominal!=UNKNOWN_TMNominal) {
			options->tropNominal = sopt->tropNominal;
			if (options->troposphericCorrection == 0) {
				printInfo("Warning: Tropospheric modelling is disabled although nominal values are given",options);
				if (options->estimateTroposphere) {
					printInfo("Disconnecting tropospheric estimation (no tropospheric nominal value computed)",options);
					options->estimateTroposphere = 0;
				}
			}
		}

		// Tropospheric model: Mapping
		if (sopt->tropMapping!=UNKNOWN_TMMapping) {
			options->tropMapping = sopt->tropMapping;
			if (options->troposphericCorrection == 0) {
				printInfo("Warning: Tropospheric modelling is disabled although a troposphere mapping is given",options);
			}
			else if (options->tropNominal==TropoGalileo && options->tropMapping!=NiellMapping) {
				printError("Galileo tropospheric modelling only accepts Niell mapping, but Simple mapping is selected",options);
			}
		} else {
			if (options->tropNominal==TropoGalileo) {
				options->tropMapping = NiellMapping;
				printInfo("Warning: Galileo tropospheric modelling selected, but no mapping is given. Niell mapping will be used",options);
			}
		}

		// Tropospheric estimation
		if (options->troposphericCorrection==0) {
			//As troposphere model is disabled, we will also disable tropo estimation
			//as the filter needs the tropo mappings provided by the tropo model
			options->estimateTroposphere = 0;
			printInfo("Forcing disabled tropospheric estimation due to troposphere model correction is disabled",options);
		} else if (sopt->estimateTroposphere==1) {
			options->estimateTroposphere = 1;
			printInfo("Forcing enabled tropospheric estimation for this processing",options);
		} else if (sopt->estimateTroposphere==0) {
			options->estimateTroposphere = 0;
			printInfo("Forcing disabled tropospheric estimation for this processing",options);
		}
	

		
		// TGD Source
		if (sopt->p1c1dcbModel!=p1c1UNKNOWN) {
			options->p1c1dcbModel = sopt->p1c1dcbModel;
		}
		if (sopt->p1p2dcbModel!=p1p2UNKNOWN) {
			options->p1p2dcbModel = sopt->p1p2dcbModel;
		}
		for (i=0;i<sopt->numTGD;i++) {
			auxft1 = whatFileTypeIs(sopt->tgdFile[i]);
			if (auxft1 == ftP1C1DCB) sopt->numP1C1DCB++;
			else if (auxft1 == ftP1P2DCB) sopt->numP1P2DCB++;
			else if (auxft1 == ftRINEXbroadcast) sopt->numP1P2RINEX++;
			else if (auxft1 == ftIONEX) sopt->numP1P2IONEX++;
			else if (auxft1 == ftFPPP) sopt->numP1P2FPPP++;
		}
		
		if (options->p1c1dcbModel == p1c1STRICT && sopt->numP1C1DCB>0 && sopt->recFile[0] != '\0') {
			if(options->printInput == 1 && options->printMeas == 1) {
				printInfo("INPUT and MEAS messages have the DCB P1-C1 correction applied on measurements",options);
			} else if (options->printInput == 1) {
				printInfo("INPUT message has the DCB P1-C1 correction applied on measurements",options);
			} else if (options->printMeas == 1) {
				printInfo("MEAS message has the DCB P1-C1 correction applied on measurements",options);
			}
		}
		
		// Orbit and clock interpolation degree
		if (options->orbitInterpolationDegree>MAX_INTERPOLATION_DEGREE) {
			sprintf(messagestr,"Max interpolation degree for orbits is %d (selected %d)",MAX_INTERPOLATION_DEGREE,options->orbitInterpolationDegree);
			printError(messagestr,options);
		}
		if (options->clockInterpolationDegree>MAX_INTERPOLATION_DEGREE) {
			sprintf(messagestr,"Max interpolation degree for clocks is %d (selected %d)",MAX_INTERPOLATION_DEGREE,options->clockInterpolationDegree);
			printError(messagestr,options);
		}

		// Cycle-slips depending on frequency availability
		if ( options->usableFreq[GPS][2] == 0 ) { // Unavailable GPS L2
			options->csL1C1 = 1;
		}
	
		// Usable frequency defaults
//		if (sopt->navMode==NMstandalone) {
//			options->usableFreq[GPS][2] = 0;
//			options->usableFreq[GPS][5] = 0;
//		}
	}

	// Enable check of transmission time in broadcast messages if user has not set anything and we are not in SBAS
	if ( options->brdcBlockTransTime == -1 ) options->brdcBlockTransTime = 1;
			
	// Check forcing a specific configuration for cycle-slips
	if ( sopt->csLI != -1 )   options->csLI   = sopt->csLI;
	if ( sopt->csBW != -1 )   options->csBW   = sopt->csBW;
	if ( sopt->csL1C1 != -1 ) options->csL1C1 = sopt->csL1C1;
	if ( sopt->csLLI != -1 )  options->csLLI  = sopt->csLLI;
		
	// Anyway if dual-frequency data is not available, it will NOT use Li and BW cycle slip detectors...
	if ( options->usableFreq[GPS][2] == 0 ) { // Unavailable GPS L2
		if ( options->csLI || options->csBW ) {
			printInfo("Forcing disconnection of LI and BW cycle-slip detectors. No dual-frequency data available...",options);
		}
		options->csLI = 0;
		options->csBW = 0;
	}

	// Warning gLAB is going to use carrier phase without any cycle-slip detector activated
	if ( options->csLI == 0 && options->csBW == 0 && options->csL1C1 == 0 && options->csLLI == 0 && options->usePhase == 1 ) {
		printInfo("WARNING Carrier phase is used but no cycle-slip detector is activated",options);
	}

	// Divergence-free requires a dual-frequency cycle-slip detector
	if ( options->csLI == 0 && options->csBW == 0 && options->DF == 1 ) {
		printInfo("Forcing connection of LI and BW cycle-slip detectors",options);
		options->csLI = 1;
		options->csBW = 1;
		options->csL1C1 = 0;
	}

	// Discard eclipse satellites
	if (sopt->discardEclipsedSatellites!=-1) {
		options->discardEclipsedSatellites = sopt->discardEclipsedSatellites;
	}
	
	// Printing
	if ( options->printInfo ) {
		if ( options->workMode == wmDOPROCESSING ) {
			sprintf(messagestr,"RINEX observation input file: %s",sopt->obsFile);
			printInfo(messagestr,options);
			if ( sopt->dgnssFile[0] != '\0' ) {
				sprintf(messagestr,"RINEX observation input file for reference station: %s",sopt->dgnssFile);
				printInfo(messagestr,options);
			}
			if ( sopt->rtcm3File[0] != '\0' ) {
				sprintf(messagestr,"RTCM v3.x binary input file for reference station: %s",sopt->rtcm3File);
				printInfo(messagestr,options);
			}
			if ( sopt->rtcm2File[0] != '\0' ) {
				sprintf(messagestr,"RTCM v2.x binary input file for reference station: %s",sopt->rtcm2File);
				printInfo(messagestr,options);
			}
			if (sopt->navMode==NMstandalone) {
				sprintf(messagestr,"RINEX navigation message input file: %s",sopt->navFile[0]);
				printInfo(messagestr,options);
			}
			if (sopt->navMode==NMppp) {
				if (sopt->SP3File[0][0]!='\0') {
					sprintf(messagestr,"SP3 products file: %s",sopt->SP3File[0]);
					printInfo(messagestr,options);
				} else {
					sprintf(messagestr,"SP3 orbits file: %s",sopt->orbFile[0]);
					printInfo(messagestr,options);
					sprintf(messagestr,"Clocks file:     %s",sopt->clkFile[0]);
					printInfo(messagestr,options);
				}
			}
			if ( options->SBAScorrections == 1 && options->onlySBASiono == 0 ) {
				sprintf(messagestr,"SBAS message data input file: %s",sopt->sbasFile);
				printInfo(messagestr,options);
			}
			if ( options->useraddednoise == 1 && sopt->addederrorFile[0] != '\0' ) {
				sprintf(messagestr,"User defined error input file: %s",sopt->addederrorFile);
				printInfo(messagestr,options);
				if (options->useraddednoisepreprocess==1) {
					printInfo("Adding user defined error after preprocessing",options);
				} else {
					printInfo("Adding user defined error before preprocessing",options);
				}
			}
			if (options->usersigmamultipath == 1 && sopt->sigmamultipathFile[0] != '\0') {
				sprintf(messagestr,"User defined sigma multipath file: %s",sopt->sigmamultipathFile);
				printInfo(messagestr,options);
			}

			if (options->ionoModel==IONEX) {
				if (sopt->inxFile[0]!='\0') {
					sprintf(messagestr,"IONEX file for ionospheric corrections: %s",sopt->inxFile);
					printInfo(messagestr,options);
				}
			}
			else if (options->ionoModel==FPPP) {
				if (sopt->fppFile[0]!='\0') {
					sprintf(messagestr,"FPPP file for ionospheric corrections: %s",sopt->fppFile);
					printInfo(messagestr,options);
				}
			}
			else if (options->ionoModel==Klobuchar) {
				if (sopt->klbFile[0]!='\0') {
					sprintf(messagestr,"RINEX navigation file for Klobuchar corrections: %s",sopt->klbFile);
					printInfo(messagestr,options);
				} else {
					printInfo("File for Klobuchar corrections same as for navigation",options); 
				}
			}
			else if (options->ionoModel==BeiDou) {
				if (sopt->beiFile[0]!='\0') {
					sprintf(messagestr,"RINEX navigation file for BeiDou corrections: %s",sopt->beiFile);
					printInfo(messagestr,options);
				} else {
					printInfo("File for BeiDou corrections same as for navigation",options); 
				}
			}
			else if (options->ionoModel==neQuick) {
				if (sopt->neqFile[0]!='\0') {
					sprintf(messagestr,"RINEX navigation file for NeQuick corrections: %s",sopt->neqFile);
					printInfo(messagestr,options);
				} else {
					printInfo("File for NeQuick corrections same as for navigation",options); 
				}
			}
			else if (options->ionoModel==SBASiono) {
				if (options->onlySBASiono==1 && sopt->SBASIONOFile[0]!='\0') {
					//Print this message only if we are using SBAS iono but no other SBAS corrections
					sprintf(messagestr,"SBAS data file for SBAS iono corrections: %s",sopt->SBASIONOFile);
					printInfo(messagestr,options);
				}
			}
			if (sopt->numP1P2RINEX==0 && (options->p1p2dcbModel==p1p2RINEX) && broadcastProductsAvailable) {
				printInfo("File for P1-P2 DCB corrections same as for navigation",options);
			}
			for (i=0;i<sopt->numTGD;i++) {
				sprintf(messagestr,"File for DCB corrections: %s",sopt->tgdFile[i]);
				printInfo(messagestr,options);
			}
			if (sopt->recFile[0]!='\0') {
				sprintf(messagestr,"GPS receiver types file: %s",sopt->recFile);
				printInfo(messagestr,options);
			}
			if (sopt->snxFile[0]!='\0') {
				sprintf(messagestr,"SINEX input file: %s",sopt->snxFile);
				printInfo(messagestr,options);
			}
		} else if (options->workMode==wmCOMPAREORBITS || options->workMode==wmSHOWPRODUCT) {
			sources = 0;
			for (i=0;i<sopt->numNav;i++) {
				sources++;
				sprintf(messagestr,"OC Product %d: RINEX navigation message input file: %s",sources,sopt->navFile[i]);
				printInfo(messagestr,options);
			}
			for (i=0;i<sopt->numSP3;i++) {
				sources++;
				sprintf(messagestr,"OC Product %d: SP3 products file: %s",sources,sopt->SP3File[i]);
				printInfo(messagestr,options);
			}
			for (i=0;i<sopt->numOrb;i++) {
				sources++;
				sprintf(messagestr,"OC Product %d: SP3 orbit file: %s",sources,sopt->orbFile[i]);
				printInfo(messagestr,options);
				sprintf(messagestr,"OC Product %d: clock file:     %s",sources,sopt->clkFile[i]);
				printInfo(messagestr,options);
			}
		} else if (options->workMode==wmSBASPLOTS ) {
			sprintf(messagestr,"RINEX navigation message input file: %s",sopt->navFile[0]);
			printInfo(messagestr,options);
			sprintf(messagestr,"SBAS message data input file: %s",sopt->sbasFile);
			printInfo(messagestr,options);
		}

		if (options->workMode==wmDOPROCESSING || options->workMode==wmCOMPAREORBITS || options->workMode==wmSHOWPRODUCT) {
			if (preciseProductsAvailable) {
				if (sopt->conFile[0]!='\0') {
					sprintf(messagestr,"Constellation status file: %s",sopt->conFile);
					printInfo(messagestr,options);
				}
				if (sopt->antFile[0]!='\0') {
					sprintf(messagestr,"ANTEX antenna input file: %s",sopt->antFile);
					printInfo(messagestr,options);
				}
			}
		}
		if (sopt->posReferenceFile[0]!='\0') {
			if ( options->receiverPositionSource == rpSETREF ) {
				sprintf(messagestr,"Reference position file for modelling and differential fields: %s",sopt->posReferenceFile);
				printInfo(messagestr,options);
				sprintf(messagestr,"Interpolation degree for reference position: %d",options->RefDegInterp);
				printInfo(messagestr,options);
			} else if ( options->receiverPositionSource == rpCALCULATEREF || options->receiverPositionSource == rpCALCULATERINEXREF
             	   || options->receiverPositionSource == rpCALCULATEUSERREF ||  options->receiverPositionSource == rpRTCMRoverUSERREF 
					||  options->receiverPositionSource == rpRTCMRefUSERRoverREF) {
				sprintf(messagestr,"Reference position file for differential fields: %s",sopt->posReferenceFile);
				printInfo(messagestr,options);
				sprintf(messagestr,"Interpolation degree for reference position: %d",options->RefDegInterp);
				printInfo(messagestr,options);
			}
		}
	}

	if (options->workMode != wmDOPROCESSING) {
		//If mode is not data processing, disable the summary
		options->printSummary=0;
		options->useDatasummary=0;
	}
	return 1;
}

/*****************************************************************************
 * Name        : readConfig
 * Description : Reads the input parameters from a FILE descriptor
 * Parameters  :
 * Name                           |Da|Unit|Description
 * FILE  *fd                       I  N/A  Input file descriptor
 * TSupportOptions  *sopt          IO N/A  TSupportOptions structure
 * TOptions  *options              IO N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         -1 => Some problems with the parameter
 *                                               parsing                                
 *                                         1  => Parsing properly done
 *****************************************************************************/
int readConfig (FILE *fd, TSupportOptions *sopt, TOptions *options) {
	char 		line[MAX_INPUT_LINE];
	char		word[MAX_INPUT_LINE];
	char		auxword[MAX_INPUT_LINE];
	char		*wordlst[MAX_WORDS];
	char		format[MAX_INPUT_LINE];
	char		format2[MAX_INPUT_LINE];
	char		formataux[MAX_INPUT_LINE];
	char		*pointer;
	int			len = 0;
	int			length;
	int			ret = 0;
	int			wordindex = 1;
	int			i;
	int			end;
	
	for (i=0;i<MAX_WORDS;i++) {
		wordlst[i] = NULL;
	}
	while (getLNoComments(line,&len,fd)!=-1) {
		word[0]='#';
		word[1]='\0';
		ret = sscanf(line,"%s",word);
		if (ret) {
			if (word[0]!='#') { // It is not a comment
				wordlst[wordindex] = malloc(sizeof(char)*(strlen(word)+2)); // +2 for the '\0' and the '-' char
				strcpy(wordlst[wordindex],word);
				wordindex++;
				strcpy(format,"%*s");
				sprintf(formataux,"%s %%s",format);
				if( (strstr(wordlst[wordindex-1],"-input:")!=NULL || strstr(wordlst[wordindex-1],"-output:")!=NULL) && strstr(wordlst[wordindex-1],"-input:rtcm:")==NULL  
						&& strstr(wordlst[wordindex-1],"--output:")==NULL && strstr(wordlst[wordindex-1],"-output:kml:")==NULL && strstr(wordlst[wordindex-1],"-output:sp3:")==NULL
						&& strstr(wordlst[wordindex-1],"-output:refpos:")==NULL && strstr(wordlst[wordindex-1],"-output:rinexversion")==NULL
						&& strstr(wordlst[wordindex-1],"-output:satvel")==NULL && strstr(wordlst[wordindex-1],"-output:peg")==NULL
						&& strstr(wordlst[wordindex-1],"-output:rinexb")==NULL && strstr(wordlst[wordindex-1],"-output:ems")==NULL ) {
					//-input:... or -output:file or -output:sbasdir or -output:stfdesa parameter found. If there are more than two parameters, means that the filename or path has spaces
					//Check first that there are more words to be read   
					//Also we have to exclude all '-input:' and '-output:' parameters that do not provide any filename or path for a proper error control
					if(sscanf(line,formataux,word)==1) {
						wordlst[wordindex] = malloc(sizeof(char)*MAX_INPUT_LINE);
						//Look for the length of the first parameter
						length=strlen(wordlst[wordindex-1]);
						//Look for the beginning of the first parameter (the line may contain spaces at the beginning)
						pointer=strstr(line,wordlst[wordindex-1]);
						//Copy from the end of the first parameter to the end of line
						strcpy(auxword,(char *)(pointer+length));
						//Take out white spaces and quotes from the beginning of the path
						i=0;
						end=0;
						while (end==0) {
							if (auxword[i]!=' ' && auxword[i]!='"' && auxword[i]!='\'') {
								//Beginning of path
								end=1;
							} else {
								//Blank space, single or double quote
								i++;
							}
						}
						strcpy(wordlst[wordindex],&auxword[i]);
						length=strlen(wordlst[wordindex]);
						//Search for spaces, quotes and newline at the end of the string
						i=length-1;
						end=0;
						while (end==0) {
							if(wordlst[wordindex][i]!=' ' && wordlst[wordindex][i]!='"' && wordlst[wordindex][i]!='\'' && wordlst[wordindex][i]!='\n' && wordlst[wordindex][i]!='\r') {
								//End of path
								end=1;
							} else {
								//Blank space, single or double quote, newline or carriage return
								i--;
							}
						}
						wordlst[wordindex][i+1]='\0';
						wordindex++;
					} else {
						//Filename missing
						return -1;
					}
				} else {
					while(sscanf(line,formataux,word)==1) {
						wordlst[wordindex] = malloc(sizeof(char)*(strlen(word)+1)); // +1 for the '\0'
						strcpy(wordlst[wordindex],word);
						wordindex++;
						sprintf(format2,"%s %%*s",format);
						sprintf(format,"%s",format2);
						sprintf(formataux,"%s %%s",format);
					}
				}
			}
		}
	}
	
	wordlst[wordindex] = NULL;
	
	// Parse options
	if ( !parseAllOptions(sopt,options, wordindex, wordlst) ) {
		return -1;
	}
	
	// Free memory
	for ( i = 0; i < wordindex; i++ ) {
		free(wordlst[i]);
	}
	
	return 1;
}

/*****************************************************************************
 * Name        : checkConfigFile
 * Description : Checks if a config file has been specified (cfgFile). If it has
 *               call readConfig function to parse the file
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TSupportOptions  *sopt          IO N/A  TSupportOptions structure
 * TOptions  *options              IO N/A  TOptions structure
 * Returned value (int)            O  N/A  Status of the function
 *                                         -1 => Some problems with the parameter
 *                                               parsing or file not found
 *                                         0  => Config file not used
 *                                         1  => Parsing properly done
 *****************************************************************************/
int checkConfigFile (TSupportOptions *sopt, TOptions *options) {
	FILE	*fd;
	int		ret;
	
	if (sopt->cfgFile[0]!='\0') {
		if ((fd = fopen(sopt->cfgFile,"r"))) {
			ret = readConfig (fd, sopt, options);
			fclose (fd);
			return ret;
		} else {
			// File does not exist
			return -1;
		}
	}
	return 0;
}

/*****************************************************************************
 * Name        : compareOrbits
 * Description : Perform an orbit comparison between two different products
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TGNSSproducts  **products       I  N/A  Products to be compared
 * TGNSSproducts  **pastProducts   I  N/A  Past products to be compared
 * TGNSSproducts  **nextProducts   I  N/A  Next products to be compared
 * FILE **fdRNXnav                 I  N/A  Vector with file descriptors for RINEX navigation
 * int  *retRNXnav                 I  N/A  Vector with the return of the opened RINEX navigation file
 * double  *rinexNavVersion        I  N/A  RINEX navigation version
 * FILE **fdSP3                    I  N/A  Vector with file descriptors for SP3 file (orbits + clocks)
 * int *retSP3                     I  N/A  Vector with the return of the opened SP3 file
 * FILE **fdSP3o                   I  N/A  Vector with file descriptors for SP3 file (orbits)
 * int  *retSP3o                   I  N/A  Vector with the return of the opened SP3 file
 * FILE **fdCLK                    I  N/A  Vector with file descriptors for RINEX clock file
 * int  *retCLK                    I  N/A  Vector with the return of the opened RINEX clock file
 * double *OrbitsMaxDistance       I  s    Vector with orbit max distance for precise each orbit files
 * double *OrbitsToTMaxDistance    I  s    Vector with total orbit max distance for each precise orbit files
 * double *ClocksMaxDistance       I  s    Vector with clock max distance for each precise clock files
 * double *ClocksToTMaxDistance    I  s    Vector with total clock max distance for each precise clock files
 * TConstellation  *constellation  I  N/A  Constellation information on the products
 * TTime startTime                 I  N/A  Start time of products
 * TTime endTime                   I  N/A  End time of products (may not be end of process if files are concatenated)
 * TTime endTimePercentage         I  N/A  End time of products for showing percentage
 * double numberEpochs             I  N/A  Number of epochs for comparing orbits 
 * int startTimeFromNav            I  N/A  0 -> Start Time of products is from a SP3 file
 *                                         1 -> Start Time of products is from a navigation file and only one day read in navigation file
 *                                         2 -> Start Time of products is from a navigation file and two days read in navigation file
 * TSupportOptions  *sopt          I  N/A  TSupportOptions structure
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void compareOrbits (TGNSSproducts **products, TGNSSproducts **pastProducts, TGNSSproducts **nextProducts, FILE **fdRNXnav, int *retRNXnav, double *rinexNavVersion, FILE **fdSP3, int *retSP3, FILE **fdSP3o, int *retSP3o, FILE **fdCLK, int *retCLK, double *OrbitsMaxDistance, double *OrbitsToTMaxDistance, double *ClocksMaxDistance, double *ClocksToTMaxDistance, TConstellation *constellation, TTime startTime, TTime endTime, TTime endTimePercentage, double numberEpochs, int startTimeFromNav, TOptions *options, TSupportOptions *sopt) {
	double			orientation[2][3][3];
	double			orientationACR[3][3];
	int				i, j, k, l;
	TTime			t;
	double			position[2][3];
	double			velocity[2][3];
	double			ITRFvelocity[2][3];
	double			posDiff[3];
	double			posDiffXYZ[3];
	double			clock[2];
	double			SISREDiff;
	double			Orb3DDiff;
	double			OrbDiff;
	double			ClkDiff;
	double			dr[3];
	int				available;
	double 			tIncrease = 30.;
	int				ret;
	double			sunPos[3];
	double			auxT;
	double			epochsProcessed=0.;
	double			CurrentPercentage=0.;
	double			seconds;
	double			PreviousPercentage=-1;
	int				DataAvailable[2];
	int				end=0;
	int				numReadNav,numReadSP3,numReadOrb;
	int				currentMJDN;
	TSatellite		sat;
	TStat			statSISRE[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	TStat			statSISRETot;
	TStat			stat3D[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	TStat			stat3DTot;
	TStat			statOrb[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	TStat			statOrbTot;
	TStat			statClk[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	TStat			statClkTot;
	TStat			statRadOrb[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	TStat			statRadOrbTot;
	TStat			statAloOrb[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	TStat			statAloOrbTot;
	TStat			statCroOrb[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	TStat			statCroOrbTot;
	TSatInfo		satInfo[MAX_GNSS][MAX_SATELLITES_PER_GNSS];
	int				bothSP3;
	int				SBASIOD = -1;	//SBAS not used here, so the IOD value for BRDC data is -1
	char			auxstr[100];
	struct tm 		tm;


	// Put this option to 2 so no print buffers are used
	options->printInBuffer = 2;

	for ( j = 0; j < MAX_GNSS; j++ ) {
		for ( i = 0; i < MAX_SATELLITES_PER_GNSS; i++ ) {
			satInfo[j][i].lastEclipse.SoD = 0;
			satInfo[j][i].lastEclipse.MJDN = 0;
		}
	}
	
	// Initialize stats
	initStat(&statSISRETot);
	initStat(&stat3DTot);
	initStat(&statOrbTot);
	initStat(&statClkTot);
	initStat(&statRadOrbTot);
	initStat(&statAloOrbTot);
	initStat(&statCroOrbTot);
	for ( k = 0; k < MAX_GNSS; k++ ) {
		for ( i = 0; i < MAX_SATELLITES_PER_GNSS; i++ ) {
			initStat(&statSISRE[k][i]);
			initStat(&stat3D[k][i]);
			initStat(&statOrb[k][i]);
			initStat(&statClk[k][i]);
			initStat(&statRadOrb[k][i]);
			initStat(&statAloOrb[k][i]);
			initStat(&statCroOrb[k][i]);
		}
	}
	
	// Use decimate option to choose increase interval
	if ( options->decimate != 0. ) {
		tIncrease = options->decimate;
	}
	
	//Compare clock message
	sprintf(messagestr, "MODELLING Comparison of satellite clock correction:    %3s", options->satelliteClockCorrection? "ON" : "OFF");
	printInfo(messagestr, options);
	
	//Eclipse condition message
	sprintf(messagestr, "MODELLING Discard satellites under eclipse condition:    %3s", options->discardEclipsedSatellites? "ON" : "OFF");
	printInfo(messagestr, options);

	if ( products[0]->type == SP3 && products[1]->type == SP3 ) bothSP3 = 1;
	else bothSP3 = 0;
	
	if ( bothSP3 && options->satellitePhaseCenter ) {
		printInfo("WARNING both input orbits are SP3, and the satellite phase centre corrections are active. These corrections will only be applied to the second SP3 product", options);
	}

	// Check if StartTime MJDN is many days before the EndTime MJDN.
	// This can happen if in the brodcast file some messages are very old.
	// This would make gLAB to do a very very long loop checking for broadcast data for so many days
	if (printProgress==1) {
		if ( ((endTime.MJDN - startTime.MJDN) > 10) && ((retRNXnav[0] * retSP3[0] * retSP3o[0] * retCLK[0] * retRNXnav[1] * retSP3[1] * retSP3o[1] * retCLK[1]) == 1) ) {
			sprintf(messagestr, "WARNING: StartTime day (%5d) is more than 10 days before of the EndTime day (%5d). Only the last 10 days will be shown", startTime.MJDN, endTime.MJDN);
			printInfo(messagestr, options);
			startTime.MJDN = endTime.MJDN - 10;
		}
		sprintf(auxstr,"%s",t2doystr(&endTimePercentage));
		sprintf(messagestr, "StartTime: %17s    EndTime: %17s    IntervalTime: %8.2f", t2doystr(&startTime), auxstr, tIncrease);
		printInfo(messagestr, options);
	} else if ( (retRNXnav[0] * retSP3[0] * retSP3o[0] * retCLK[0] * retRNXnav[1] * retSP3[1] * retSP3o[1] * retCLK[1]) == 1 ) { // Avoid this information if files are concatennated
		if ( (endTime.MJDN - startTime.MJDN) > 10 ) {
			sprintf(messagestr, "WARNING: StartTime day (%5d) is more than 10 days before of the EndTime day (%5d). Only the last 10 days will be shown", startTime.MJDN, endTime.MJDN);
			printInfo(messagestr, options);
			startTime.MJDN = endTime.MJDN - 10;
		}

		//sprintf(messagestr, "StartTime: %5d %8.2f    EndTime: %5d %8.2f    IntervalTime: %8.2f", startTime.MJDN, startTime.SoD, endTime.MJDN, endTime.SoD, tIncrease);
		sprintf(auxstr,"%s",t2doystr(&endTime));
		sprintf(messagestr, "StartTime: %17s    EndTime: %17s    IntervalTime: %8.2f", t2doystr(&startTime), auxstr, tIncrease);
		printInfo(messagestr, options);
	} else {
		if (endTimePercentage.MJDN!=-1) {
			sprintf(auxstr,"%s",t2doystr(&endTimePercentage));
			sprintf(messagestr, "StartTime: %17s    EndTime: %17s    IntervalTime: %8.2f", t2doystr(&startTime), auxstr, tIncrease);
		} else {
			sprintf(messagestr, "StartTime: %17s    EndTime: %-17s    IntervalTime: %8.2f", t2doystr(&startTime), "-", tIncrease);
		}
		printInfo(messagestr, options);
	}
	
	// Tune start time to start at least in an entire hour
	startTime.SoD -= modulo(startTime.SoD, 3600);

	currentMJDN=startTime.MJDN;

	if ( (sopt->numOrb == sopt->numSP3) && sopt->numOrb>0) {
		if ( retSP3[0] == 2 && retSP3o[0] == 2 ) {
			DataAvailable[0]=DataAvailable[1]=1;
		} else {
			DataAvailable[0]=DataAvailable[1]=0;
		}
	} else if ( (sopt->numNav == sopt->numSP3) && sopt->numNav>0) {
		if ( retSP3[0] == 2 && retRNXnav[0] == 2 ) {
			DataAvailable[0]=DataAvailable[1]=1;
		} else {
			DataAvailable[0]=DataAvailable[1]=0;
		}
	} else if ( (sopt->numNav == sopt->numOrb) && sopt->numNav>0) {
		if ( retSP3o[0] == 2 && retRNXnav[0] == 2 ) {
			DataAvailable[0]=DataAvailable[1]=1;
		} else {
			DataAvailable[0]=DataAvailable[1]=0;
		}
	} else {
		for(i=0;i<2;i++) {
			if (retRNXnav[i]==2 || retSP3[i] == 2 || retSP3o[i] == 2 ) {
				DataAvailable[i]=1;
			} else {
				DataAvailable[i]=0;
			}
		}
	}

	if (startTimeFromNav>0) {
		//Navigation file typically start at the end of the previous day
		//This is avoid reading the next with the condition 'currentMJDN!=t.MJDN' when we start computing position some epochs previous
		//to the current day, as the navigation data files are still valid
		if(startTime.SoD>=75000.) {
			currentMJDN++;
		}
		if(startTimeFromNav==2) {
			currentMJDN++;
		}
	}

	memcpy(&t, &startTime, sizeof(TTime));
	while ( end==0 ) {
		if (printProgress) {
			CurrentPercentage=100.*epochsProcessed/numberEpochs;
			if ((CurrentPercentage-PreviousPercentage)>=0.1) { //This is to avoid to many prints when percentages changed less than 0.1
				t2tmnolocal (&t, &tm, &seconds);
				if (options->ProgressEndCharac=='\r') {
					//Printing to a terminal
					fprintf(options->terminalStream,"Current epoch: %17s / %4d %02d %02d %02d:%02d:%04.1f (%5.1f%%)        %c",t2doystr(&t),tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,CurrentPercentage,options->ProgressEndCharac);
					//In Windows, cursor is not disabled
					fflush(options->terminalStream);
				} else {
					//Printing for the GUI. Only print if the integer of the percentage have changed (to avoid message spamming)
					if ((int)CurrentPercentage!=(int)PreviousPercentage) {
						fprintf(options->terminalStream,"Current epoch: %17s / %4d %02d %02d %02d:%02d:%04.1f (%5.1f%%)        %c",t2doystr(&t),tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,CurrentPercentage,options->ProgressEndCharac);
						fflush(options->terminalStream);
					}
				}
				PreviousPercentage=CurrentPercentage;
			}
		}
		// Check if concatenated files. If so and it is needed, read the next file
		if ( (tdiff(&t, &endTime)  >= 0 || currentMJDN<t.MJDN ) && (DataAvailable[0]==1 && DataAvailable[1]==1)  ) {
			currentMJDN=t.MJDN;
			for ( j = 0; j < 2; j++ ) {
				DataAvailable[j]=0;
				if(j==0) {
					numReadNav=numReadSP3=numReadOrb=1;
				}
				if(sopt->numOrb==2 || sopt->numNav==2 || sopt->numSP3==2) {
					l=j;
				} else {
					l=0;
				}
				if ( retRNXnav[l]==2 && (numReadNav<=sopt->numNav) ) {
					retRNXnav[l] = readRinexNav(fdRNXnav[l], products[j], &rinexNavVersion[l]);
					if (retRNXnav[l] == 2 ) DataAvailable[j]=1;
					endTime = getProductsLastEpoch(products[j]);
					numReadNav++;
					continue;
				}
				if ( retSP3[l]==2 && (numReadSP3<=sopt->numSP3) ) {
					freeSP3data(pastProducts[j]);
					memcpy(pastProducts[j], products[j], sizeof(TGNSSproducts));
					memcpy(products[j],nextProducts[j], sizeof(TGNSSproducts));
					retSP3[l] = readSP3(fdSP3[l], nextProducts[j], 1, 1, 0);
					if(retSP3[l]==-2) {
						sprintf(messagestr, "SP3 orbit and clock products file [%s] has incorrect number of entries in header", sopt->SP3File[l]);
						printError(messagestr, options);
					}
					if (retSP3[l]==2 ) {
						DataAvailable[j]=1;
						endTime = getProductsLastEpoch(products[j]);
					} else {
						endTime = getProductsLastEpoch(nextProducts[j]);
					}
					ConcatenateSP3(0,products[j],pastProducts[j],nextProducts[j],options);
					numReadSP3++;
					continue;
				}
				if ( retSP3o[l]==2 && (numReadOrb<=sopt->numOrb)) {
					// Sanity check
					if ( retCLK[l] != 2 ) {
						sprintf(messagestr,"Both SP3 orbit file [%s] and clock file [%s] must have the same length",sopt->orbFile[l],sopt->clkFile[l]);
						printError(messagestr, options);
					}
					freeSP3data(pastProducts[j]);
					memcpy(pastProducts[j], products[j], sizeof(TGNSSproducts));
					memcpy(products[j],nextProducts[j], sizeof(TGNSSproducts));
					retSP3o[l] = readSP3(fdSP3o[l], nextProducts[j], 1, 0, 0);
					if(retSP3o[l]==-2) {
						sprintf(messagestr, "SP3 orbit product file [%s] has incorrect number of entries in header", sopt->orbFile[l]);
						printError(messagestr, options);
					}
					retCLK[l] = readRinexClocks(fdCLK[l], nextProducts[j]);
					if (retSP3o[l]==2 && retCLK[l]==2 ) {
						DataAvailable[j]=1;
						endTime = getProductsLastEpoch(products[j]);
					} else {
						endTime = getProductsLastEpoch(nextProducts[j]);
					}
					ConcatenateSP3(0,products[j],pastProducts[j],nextProducts[j],options);
					numReadOrb++;
				}
			}
		} else if ( ( tdiff(&t, &endTime)  >= 0 || currentMJDN<t.MJDN  ) && sopt->numNav==1 && (retRNXnav[0]==2 && (retSP3[0]!=2 || retSP3o[0]!=2) ) )  {
			//For RINEX navigation vs SP3, the navigation file always goes one day behind to avoid Runge-Kutta effect on precise orbits.
			//Therefore, when we get to the last day concatenated, the SP3 file will have finished but there will be data to read in
			//the navigation file, for comparing the last day
			DataAvailable[0]=DataAvailable[1]=1;
			continue;
		} else if ( tdiff(&t, &endTime)  >= 0) {
			//Products finished
			end=1;
			continue;
		}

		if ( options->discardEclipsedSatellites ) {
			findSun(&t, sunPos);
		}
		for ( k = 0; k < MAX_GNSS; k++ ) {
			if(k==GLONASS && bothSP3==0 ) continue; //Skip GLONASS for navigation files
			for ( i = 0; i < MAX_SATELLITES_PER_GNSS; i++ ) {
				available = 1;
				for ( j = 0; j < 2; j++ ) {
					//Set values for orbit and clk max gaps in options struc
					options->OrbitsMaxDistance=OrbitsMaxDistance[j];
					options->OrbitsToTMaxDistance=OrbitsToTMaxDistance[j];
					options->ClocksMaxDistance=ClocksMaxDistance[j];
					options->ClocksToTMaxDistance=ClocksToTMaxDistance[j];
					// Check if satellite has been deselected
					if ( !options->includeSatellite[k][i] ) available = 0;
					// Satellite positions and velocities
					ret = getSatellitePVT(products[j], &t, 0.0, k, i, position[j], velocity[j], ITRFvelocity[j], NULL, SBASIOD, options);
					if ( !ret ) {
						available = 0;
					} else {
						// Eclipsed satellite check
						memcpy(sat.position, position[j], 3 * sizeof(double));
						memcpy(sat.velocity, velocity[j], 3 * sizeof(double));
						sat.hasOrbitsAndClocks = 1;
						if ( options->discardEclipsedSatellites ) {
							if ( isEclipsed(&t, &sat, &satInfo[k][i], sunPos, &auxT) ) {
								if ( auxT == 0 ) {
									printSatSel(0, i, "Satellite under eclipse", 0, options);
								} else {
									sprintf(messagestr, "Satellite was under eclipse %4.0f seconds ago", auxT);
									printSatSel(0, i, messagestr, 0, options);
								}
								available = 0;
							}
						}
					}
					// Satellite clock
					if ( options->satelliteClockCorrection ) {
						ret = getSatellitePVT(products[j], &t, 0.0, k, i, NULL, NULL, NULL, &clock[j], SBASIOD, options);
						if ( !ret ) {
							available = 0;
						}
					}
					// Satellite orientation
					getSatelliteOrientation(&t, position[j], orientation[j]);
					// Satellite phase center correction
					if ( products[j]->type == SP3 && options->satellitePhaseCenter ) {
						if ( !bothSP3 || j == 1 ) { // The contrary, will mean both SP3 input files, and first product
							ret = satellitePhaseCenterCorrection3D(&t, k, i, C1C, orientation[j], constellation, dr);
							if ( !ret ) {
								available = 0;
							}
							// Coordinate correction
							position[j][0] += dr[0];
							position[j][1] += dr[1];
							position[j][2] += dr[2];
						}
					}
				}
				if ( available ) {
					for ( j = 0; j < 3; j++ ) posDiff[j] = position[1][j] - position[0][j];
	
					memcpy(posDiffXYZ,posDiff,sizeof(posDiff));
					// Satellite orientation in the ACR system (along, cross, radial)
					getSatelliteOrientationACR(position[1], velocity[1], orientationACR);
					changeBase(orientationACR, posDiff);
	
					// Compute orbit and clock differences
					if ( options->satelliteClockCorrection ) {
						ClkDiff = clock[1] - clock[0];
						SISREDiff = sqrt((posDiff[2] - ClkDiff) * (posDiff[2] - ClkDiff) + (posDiff[0] * posDiff[0] + posDiff[1] * posDiff[1]) / 49);
					} else {
						ClkDiff = 0;
						SISREDiff = 0;
					}
					OrbDiff = sqrt(posDiff[2] * posDiff[2] + (posDiff[0] * posDiff[0] + posDiff[1] * posDiff[1]) / 49);
					Orb3DDiff = sqrt(posDiff[0] * posDiff[0] + posDiff[1] * posDiff[1] + posDiff[2] * posDiff[2]);
					
					addStat(&statSISRE[k][i], SISREDiff);
					addStat(&statSISRETot, SISREDiff);
					addStat(&statOrb[k][i], OrbDiff);
					addStat(&statOrbTot, OrbDiff);
					addStat(&stat3D[k][i], Orb3DDiff);
					addStat(&stat3DTot, Orb3DDiff);
					addStat(&statClk[k][i], ClkDiff);
					addStat(&statClkTot, ClkDiff);
					addStat(&statRadOrb[k][i], posDiff[2]);
					addStat(&statRadOrbTot, posDiff[2]);
					addStat(&statAloOrb[k][i], posDiff[0]);
					addStat(&statAloOrbTot, posDiff[0]);
					addStat(&statCroOrb[k][i], posDiff[1]);
					addStat(&statCroOrbTot, posDiff[1]);
					
					printSatDiff(&t, k, i, SISREDiff, OrbDiff, Orb3DDiff, ClkDiff, posDiff, posDiffXYZ, options);
				}
			}
		}
		t = tdadd(&t,tIncrease);
		epochsProcessed++;
	}
	// Close opened files
	for(i=0;i<2;i++) {
		if ( fdRNXnav[i] != NULL)	fclose(fdRNXnav[i]);
		if ( fdSP3[i] != NULL )		fclose(fdSP3[i]);
		if ( fdSP3o[i] != NULL )	fclose(fdSP3o[i]);
		if ( fdCLK[i] != NULL )		fclose(fdCLK[i]);
	}
	
	if ( options->printSatStat ) {
		for ( k = 0; k < MAX_GNSS; k++ ) {
			for ( i = 0; i < MAX_SATELLITES_PER_GNSS; i++ ) {
				printSatStat(k, i, statSISRE[k][i], statOrb[k][i], stat3D[k][i], statClk[k][i], statRadOrb[k][i], statAloOrb[k][i], statCroOrb[k][i], options);
			}
		}
	}
	
	printSatStatTot(statSISRETot, statOrbTot, stat3DTot, statClkTot, statRadOrbTot, statAloOrbTot, statCroOrbTot, options);
}

/*****************************************************************************
 * Name        : showProduct
 * Description : Read a product file and show SAT messages 
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TGNSSproducts  *products        I  N/A  Products to be shown
 * TGNSSproducts  *pastProduct     I  N/A  past products to be shown
 * TGNSSproducts  *nextProduct     I  N/A  Next products to be shown
 * FILE  *fdRNXnav                 I  N/A  File descriptor for RINEX navigation
 * int  retRNXnav                  I  N/A  Return of the opened RINEX navigation file
 * double  rinexNavVersion         I  N/A  RINEX navigation version
 * FILE  *fdSP3                    I  N/A  File descriptor for SP3 file (orbits + clocks)
 * int  retSP3                     I  N/A  Return of the opened SP3 file
 * FILE  *fdSP3o                   I  N/A  File descriptor for SP3 file (orbits)
 * int  retSP3o                    I  N/A  Return of the opened SP3 file
 * FILE  *fdCLK                    I  N/A  File descriptor for RINEX clock file
 * int  retCLK                     I  N/A  Return of the opened RINEX clock file
 * TConstellation  *constellation  I  N/A  Constellation information on the products
 * TTime startTime                 I  N/A  Start time of products
 * TTime endTime                   I  N/A  End time of products (may not be end of process if files are concatenated)
 * TTime endTimePercentage         I  N/A  End time of products for showing percentage
 * double numberEpochs             I  N/A  Number of epochs for comparing orbits 
 * TOptions  *options              I  N/A  TOptions structure
 * TSupportOptions  *sopt          I  N/A  TSupportOptions structure
 *****************************************************************************/
void showProduct (TGNSSproducts *products, TGNSSproducts *pastProducts, TGNSSproducts *nextProducts, FILE *fdRNXnav, int retRNXnav, double rinexNavVersion, FILE *fdSP3, int retSP3, FILE *fdSP3o, int retSP3o, FILE *fdCLK, int retCLK, TConstellation *constellation, TTime startTime, TTime endTime, TTime endTimePercentage, double numberEpochs, TOptions *options, TSupportOptions *sopt) {
	double			tIncrease = 30.;
	TTime			t;
	int				i, k;
	int				currentMJDN;
	int				available;
	int				ret;
	int				DataAvailable;
	int				end=0;
	double			position[3];
	double			velocity[3];
	double			ITRFvelocity[3];
	double			clock;
	double			dr[3];
	double			orientation[3][3];
	char			auxstr[100];
	int				SBASIOD = -1;	// SBAS not used here, so the IOD value for BRDC data is -1
	double			epochsProcessed=0.;
	double			CurrentPercentage=0.;
	double			seconds;
	double			PreviousPercentage=-1;
	struct tm       tm;


	// Clock message
	sprintf(messagestr, "MODELLING Clock correction computation:    %3s", options->satelliteClockCorrection? "ON" : "OFF");
	printInfo(messagestr, options);

	// Get start and end times
	sprintf(messagestr, "OUTPUT Satellite Velocity:     %s", options->satVel == svINERTIAL? "Inertial" : "ITRF");
	printInfo(messagestr, options);
	
	// Use decimate option to choose increase interval
	if ( options->decimate != 0. ) {
		tIncrease = options->decimate;
	}
	
	// Tune start time to start at least in an entire hour
	startTime.SoD -= modulo(startTime.SoD, 3600);

	// Check if StartTime MJDN is many days before the EndTime MJDN.
	// This can happen if in the brodcast file some messages are very old.
	// This would make gLAB to do a very very long loop checking for broadcast data for so many days
	if (printProgress==1) {
		if ( ((endTime.MJDN - startTime.MJDN) > 10) && ((retRNXnav * retSP3 * retSP3o * retCLK) == 1) ) {
			sprintf(messagestr, "WARNING: StartTime day (%5d) is more than 10 days before of the EndTime day (%5d). Only the last 10 days will be shown", startTime.MJDN, endTime.MJDN);
			printInfo(messagestr, options);
			startTime.MJDN = endTime.MJDN - 10;
		}
		sprintf(auxstr,"%s",t2doystr(&endTimePercentage));
		sprintf(messagestr, "StartTime: %17s    EndTime: %17s    IntervalTime: %8.2f", t2doystr(&startTime), auxstr, tIncrease);
		printInfo(messagestr, options);
	} else if ( (retRNXnav * retSP3 * retSP3o * retCLK) == 1 ) { // Avoid this information if files are concatennated
		if ( (endTime.MJDN - startTime.MJDN) > 10 ) {
			sprintf(messagestr, "WARNING: StartTime day (%5d) is more than 10 days before of the EndTime day (%5d). Only the last 10 days will be shown", startTime.MJDN, endTime.MJDN);
			printInfo(messagestr, options);
			startTime.MJDN = endTime.MJDN - 10;
		}
		
		sprintf(auxstr,"%s",t2doystr(&endTime));
		sprintf(messagestr, "StartTime: %17s    EndTime: %17s    IntervalTime: %8.2f", t2doystr(&startTime), auxstr, tIncrease);
		printInfo(messagestr, options);
	} else {
		if (endTimePercentage.MJDN!=-1) {
			sprintf(auxstr,"%s",t2doystr(&endTimePercentage));
			sprintf(messagestr, "StartTime: %17s    EndTime: %17s    IntervalTime: %8.2f", t2doystr(&startTime), auxstr, tIncrease);
		} else {
			sprintf(messagestr, "StartTime: %17s    EndTime: %-17s    IntervalTime: %8.2f", t2doystr(&startTime), "-", tIncrease);
		}
		printInfo(messagestr, options);
	}


	if (retRNXnav==2 || retSP3 == 2 || retSP3o == 2 ) {
		DataAvailable=1;
	} else {
		DataAvailable=0;
	}

	memcpy(&t, &startTime, sizeof(TTime));
	currentMJDN=startTime.MJDN;
	if(sopt->numNav==1) {
		//Navigation file typically start at the end of the previous day
		//This is avoid reading the next with the condition 'currentMJDN!=t.MJDN' when we start computing position some epochs previous
		//to the current day, as the navigation data files are still valid
		if(startTime.SoD>=75000.) {
			currentMJDN++;
		}
	}
	while(end==0) {
		if (printProgress) {
			CurrentPercentage=100.*epochsProcessed/numberEpochs;
			if ((CurrentPercentage-PreviousPercentage)>=0.1) { //This is to avoid to many prints when percentages changed less than 0.1
				t2tmnolocal (&t, &tm, &seconds);
				if (options->ProgressEndCharac=='\r') {
					//Printing to a terminal
					fprintf(options->terminalStream,"Current epoch: %17s / %4d %02d %02d %02d:%02d:%04.1f (%5.1f%%)        %c",t2doystr(&t),tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,CurrentPercentage,options->ProgressEndCharac);
					fflush(options->terminalStream);
				} else {
					//Printing for the GUI. Only print if the integer of the percentage have changed (to avoid message spamming)
					if ((int)CurrentPercentage!=(int)PreviousPercentage) {
						fprintf(options->terminalStream,"Current epoch: %17s / %4d %02d %02d %02d:%02d:%04.1f (%5.1f%%)        %c",t2doystr(&t),tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,seconds,CurrentPercentage,options->ProgressEndCharac);
						fflush(options->terminalStream);
					}
				}
				PreviousPercentage=CurrentPercentage;
			}
		}
		if ( (tdiff(&t, &endTime) >= 0 || currentMJDN<t.MJDN ) && DataAvailable==1 ) {
			// Check if concatennated files. If so and it is needed, read the next file
			DataAvailable=0;
			currentMJDN=t.MJDN;
			if ( retRNXnav == 2 ) {
				retRNXnav = readRinexNav(fdRNXnav, products, &rinexNavVersion);
				if (retRNXnav == 2 ) DataAvailable=1;
				endTime = getProductsLastEpoch(products);
			}
			if ( retSP3 == 2 ) {
				options->concatenSP3 = 1;
				options->numPreciseFiles = 1;
				freeSP3data(pastProducts);
				memcpy(pastProducts, products, sizeof(TGNSSproducts));
				memcpy(products,nextProducts, sizeof(TGNSSproducts));
				retSP3 = readSP3(fdSP3, nextProducts, 1, 1, 0);
				if(retSP3==-2) {
					sprintf(messagestr, "SP3 orbit and clock products file [%s] has incorrect number of entries in header", sopt->SP3File[0]);
					printError(messagestr, options);
				}
				if (retSP3 == 2 ) {
					DataAvailable=1;
					endTime = getProductsLastEpoch(products);
				} else {
					endTime = getProductsLastEpoch(nextProducts);
				}
				ConcatenateSP3(0,products,pastProducts,nextProducts,options);	
			}
			if ( retSP3o == 2 ) {
				// Sanity check
				if ( retCLK != 2 ) {
					sprintf(messagestr,"Both SP3 orbit file [%s] and clock file [%s] must have the same length",sopt->orbFile[0],sopt->clkFile[0]);
					printError(messagestr, options);
				}
				options->concatenSP3 = 1;
				options->numPreciseFiles = 2;
				freeSP3data(pastProducts);
				memcpy(pastProducts, products, sizeof(TGNSSproducts));
				memcpy(products,nextProducts, sizeof(TGNSSproducts));
				retSP3o = readSP3(fdSP3o, nextProducts, 1, 0, 0);
				if(retSP3o==-2) {
					sprintf(messagestr, "SP3 orbit products file [%s] has incorrect number of entries in header", sopt->orbFile[0]);
					printError(messagestr, options);
				}
				retCLK = readRinexClocks(fdCLK, nextProducts);
				if (retSP3o == 2 && retCLK==2 ) {
					DataAvailable=1;
					endTime = getProductsLastEpoch(products);
				} else if ( (retSP3o==2 && retCLK!=2) || (retSP3o!= 2 && retCLK==2) ) {
					printError("Both SP3 orbit and clock products files must have the same length", options);
				} else {
					endTime = getProductsLastEpoch(nextProducts);
				}
				ConcatenateSP3(0,products,pastProducts,nextProducts,options);	
			}
		} else if ( tdiff(&t, &endTime) >= 0 ) {
			//Products finished
			end=1;
			continue;
		}

		for ( k = 0; k < MAX_GNSS; k++ ) {
			if(k==GLONASS && sopt->numNav>0 ) continue; //Skip GLONASS for navigation files
			for ( i = 0; i < MAX_SATELLITES_PER_GNSS; i++ ) {
				available = 1;
				// Check if satellite has been deselected
				if ( !options->includeSatellite[k][i] ) available = 0;
				// Satellite positions and velocities
				ret = getSatellitePVT(products, &t, 0.0, k, i, position, velocity, ITRFvelocity, NULL, SBASIOD, options);
				if (!ret) available = 0;
				// Satellite clock
				if ( options->satelliteClockCorrection ) {
					ret = getSatellitePVT(products, &t, 0.0, k, i, NULL, NULL, NULL, &clock, SBASIOD, options);
				} else {
					clock=0;
				}
				// Satellite phase center correction
				if ( products->type == SP3 && options->satellitePhaseCenter ) {
					// Satellite orientation
					getSatelliteOrientation(&t, position, orientation);
					ret = satellitePhaseCenterCorrection3D(&t, k, i, C1C, orientation, constellation, dr);
					if ( !ret ) available = 0;
					// Coordinate correction
					position[0] += dr[0];
					position[1] += dr[1];
					position[2] += dr[2];
				}
				if ( available ) {
					if ( options->satVel == svINERTIAL ) {
						printSatPvt(&t, k, i, position, velocity, clock, options);
					} else {
						printSatPvt(&t, k, i, position, ITRFvelocity, clock, options);
					}
				}
			}
		}
		t = tdadd(&t, tIncrease);
		epochsProcessed++;
	}

	if ( fdRNXnav != NULL)	fclose(fdRNXnav);
	if ( fdSP3 != NULL )	fclose(fdSP3);
	if ( fdSP3o != NULL )	fclose(fdSP3o);
	if ( fdCLK != NULL )	fclose(fdCLK);
}

/*****************************************************************************
 * Name        : productsProcessing
 * Description : Do the two different kind of processes, depending on TOptions:
 *                 + Performing an orbit comparison between two different products
 *                 + Parse a single product file
 * Parameters  :
 * Name                           |Da|Unit|Description
 * TSupportOptions  *sopt          I  N/A  TSupportOptions structure
 * TOptions  *options              I  N/A  TOptions structure
 * TConstellation  *constellation  I  N/A  TConstellation structure
 *****************************************************************************/
void productsProcessing (TOptions *options, TSupportOptions *sopt, TConstellation *constellation) {
	int				sources;
	int				i;
	int				retRNXnav[2];
	int				retSP3[2];
	int				retSP3o[2];
	int				retCLK[2];
	int				numConcatSP3[2];
	int				numConcatSP3o[2];
	int				numConcatCLK[2];
	int				startTimeFromNav=0;
	int				ret;
	double			rinexNavVersion[2];
	double			OrbitsMaxDistance[2];
	double			OrbitsToTMaxDistance[2];
	double			ClocksMaxDistance[2];
	double			ClocksToTMaxDistance[2];
	double			tIncrease = 30.;
	double			numberEpochs;
	FILE			*fdRNXnav[2];
	FILE			*fdSP3[2];
	FILE			*fdSP3o[2];
	FILE			*fdCLK[2];
	TGNSSproducts	*products[2];
	TGNSSproducts	*pastProducts[2];
	TGNSSproducts	*nextProducts[2];
	TTime			startTime;
	TTime			startTimeRound;
	TTime			endTime;
	TTime			endTimeFile1,endTimeFile2;
	TTime			endTimePercentage;

	//Init file descriptor variables
	for(i=0;i<2;i++) {
		fdRNXnav[i]=NULL;
		fdSP3[i]=NULL;
		fdSP3o[i]=NULL;
		fdCLK[i]=NULL;
		retRNXnav[i]=1;
		retSP3[i]=1;
		retSP3o[i]=1;
		retCLK[i]=1;
		numConcatSP3o[i]=0;
		numConcatCLK[i]=0;
		rinexNavVersion[i]=0.;
		products[i]     = malloc(sizeof(TGNSSproducts));
		pastProducts[i] = malloc(sizeof(TGNSSproducts));
		nextProducts[i] = malloc(sizeof(TGNSSproducts));
		initGNSSproducts(products[i]);
		initGNSSproducts(pastProducts[i]);
		initGNSSproducts(nextProducts[i]);
		products[i]->SP3 = malloc(sizeof(TSP3products));
		pastProducts[i]->SP3 = malloc(sizeof(TSP3products));
		nextProducts[i]->SP3 = malloc(sizeof(TSP3products));
		initSP3products(products[i]->SP3);
		initSP3products(pastProducts[i]->SP3);
		initSP3products(nextProducts[i]->SP3);
		products[i]->BRDC = malloc(sizeof(TBRDCproducts));
		pastProducts[i]->BRDC = malloc(sizeof(TBRDCproducts));
		nextProducts[i]->BRDC = malloc(sizeof(TBRDCproducts));
		initBRDCproducts(products[i]->BRDC);
		initBRDCproducts(pastProducts[i]->BRDC);
		initBRDCproducts(nextProducts[i]->BRDC);
	}

	// Body: open the files and call the required function
	sources = 0;
	for ( i = 0; i < sopt->numNav; i++ ) {
		// Open and read the RINEX navigation file
		if ( whatFileTypeIs( sopt->navFile[i]) != ftRINEXbroadcast ) retRNXnav[i] = 0;
		if ( (fdRNXnav[i] = fopen(sopt->navFile[i], "rb")) ) {
			if (printProgress==1) {	
				if (options->ProgressEndCharac=='\r') {
					//Printing to a terminal
					fprintf(options->terminalStream,"Reading navigation file%50s%c","",options->ProgressEndCharac);
					fflush(options->terminalStream);
				}
			}
			retRNXnav[i] = readRinexNav(fdRNXnav[i], products[sources], &rinexNavVersion[i]);
		}
		else retRNXnav[i] = -1;

		// Check errors
		if ( retRNXnav[i] < 1 ) {
			if ( (int)rinexNavVersion[i] > 3 && rinexNavVersion[i] != 0 ) {
				sprintf(messagestr, "RINEX navigation version %1.2f from file [%s] is not supported. Supported versions are 2 and 3", rinexNavVersion[i],sopt->navFile[i]);
				printError(messagestr, options);
			} else {
				sprintf(messagestr, "Reading RINEX navigation message file [%s]", sopt->navFile[i]);
				printError(messagestr, options);
			}
		}
		sources++;
	}
	for ( i = 0; i < sopt->numSP3; i++ ) {
		// Open and read the SP3 file
		if ( whatFileTypeIs(sopt->SP3File[i]) != ftSP3 ) retSP3[i] = 0;
		if ( (fdSP3[i] = fopen(sopt->SP3File[i], "rb")) ) retSP3[i] = readSP3(fdSP3[i], pastProducts[sources], 1, 1, 0);
		else retSP3[i] = -1;

		// Check errors
		if ( retSP3[i] < 1 ) {
			if(retSP3[i]==-2) {
				sprintf(messagestr, "SP3 orbit and clock products file [%s] has incorrect number of entries in header", sopt->SP3File[i]);
				printError(messagestr, options);
			} else {
				sprintf(messagestr, "Reading SP3 orbit and clock products file [%s]", sopt->SP3File[i]);
				printError(messagestr, options);
			}
		} else if (retSP3[i]==2) {
			//File concatenaded. read next day
			retSP3[i] = readSP3(fdSP3[i], products[sources], 1, 1, 0);
			if ( retSP3[i]==-2 ) {
				sprintf(messagestr, "SP3 orbit and clock products file [%s] has incorrect number of entries in header", sopt->SP3File[i]);
				printError(messagestr, options);
			} else if (retSP3[i]==2) {
				//Read third day
				retSP3[i] = readSP3(fdSP3[i], nextProducts[sources], 1, 1, 0);
				if ( retSP3[i]==-2 ) {
					sprintf(messagestr, "SP3 orbit and clock products file [%s] has incorrect number of entries in header", sopt->SP3File[i]);
					printError(messagestr, options);
				}
				numConcatSP3[i]=3;
			} else {
				numConcatSP3[i]=2;
				memcpy(nextProducts[sources]->SP3,products[sources]->SP3,sizeof(TSP3products));
				nextProducts[sources]->type=SP3;
			}

		} else {
			//Not concatenated file
			numConcatSP3[i]=1;
			memcpy(products[sources]->SP3,pastProducts[sources]->SP3,sizeof(TSP3products));
			memcpy(nextProducts[sources]->SP3,pastProducts[sources]->SP3,sizeof(TSP3products));
			products[sources]->type=SP3;
			nextProducts[sources]->type=SP3;
		}

		sources++;
	}
	for (i=0;i<sopt->numOrb;i++) {
		// Open and read the SP3 file
		if ( whatFileTypeIs(sopt->orbFile[i]) != ftSP3 ) retSP3o[i] = 0;
		if ( (fdSP3o[i] = fopen(sopt->orbFile[i], "rb")) ) {
			if (printProgress==1) {	
				if (options->ProgressEndCharac=='\r') {
					//Printing to a terminal
					fprintf(options->terminalStream,"Reading SP3 file%50s%c","",options->ProgressEndCharac);
					fflush(options->terminalStream);
				}
			}
			retSP3o[i] = readSP3(fdSP3o[i], pastProducts[sources], 1, 0, 0);
		}
		else retSP3o[i] = -1;

		// Check errors
		if ( retSP3o[i] < 1 ) {
			if(retSP3o[i]==-2) {
				sprintf(messagestr, "SP3 orbit product file [%s] has incorrect number of entries in header", sopt->orbFile[i]);
				printError(messagestr, options);
			} else {
				sprintf(messagestr, "Reading SP3 orbit product file [%s]", sopt->orbFile[i]);
				printError(messagestr, options);
			}
		} else if (retSP3o[i]==2) {
			//File concatenaded. read next day
			retSP3o[i] = readSP3(fdSP3o[i], products[sources], 1, 0, 0);
			if ( retSP3o[i]==-2 ) {
				sprintf(messagestr, "SP3 orbit product file [%s] has incorrect number of entries in header", sopt->orbFile[i]);
				printError(messagestr, options);
			} else if (retSP3o[i]==2) {
				//Read third day
				retSP3o[i] = readSP3(fdSP3o[i], nextProducts[sources], 1, 0, 0);
				if ( retSP3o[i]==-2 ) {
					sprintf(messagestr, "SP3 orbit product file [%s] has incorrect number of entries in header", sopt->orbFile[i]);
					printError(messagestr, options);
				}
				numConcatSP3o[i]=3;
			} else {
				numConcatSP3o[i]=2;
				memcpy(&nextProducts[sources]->SP3->orbits,&products[sources]->SP3->orbits,sizeof(TSP3orbits));
				nextProducts[sources]->type=SP3;
			}
		} else {
			//Not concatenated file
			numConcatSP3o[i]=1;
			memcpy(&products[sources]->SP3->orbits,&pastProducts[sources]->SP3->orbits,sizeof(TSP3orbits));
			memcpy(&nextProducts[sources]->SP3->orbits,&pastProducts[sources]->SP3->orbits,sizeof(TSP3orbits));
			products[sources]->type=SP3;
			nextProducts[sources]->type=SP3;
		}

		// Clock
		if ( whatFileTypeIs(sopt->clkFile[i]) != ftRINEXclocks ) retCLK[i] = 0;
		if ( (fdCLK[i] = fopen(sopt->clkFile[i], "r")) ) {
			if (printProgress==1) {	
				if (options->ProgressEndCharac=='\r') {
					//Printing to a terminal
					fprintf(options->terminalStream,"Reading precise clocks file%50s%c","",options->ProgressEndCharac);
					fflush(options->terminalStream);
				}
			}
			retCLK[i] = readRinexClocks(fdCLK[i], pastProducts[sources]);
		}
		else retCLK[i] = -1;

		// Check errors
		if ( retCLK[i] < 1 ) {
			sprintf(messagestr, "Reading clock products file [%s]", sopt->clkFile[i]);
			printError(messagestr, options);
		} else if (retCLK[i]==2) {
			//File concatenaded. read next day
			retCLK[i] = readRinexClocks(fdCLK[i], products[sources]);
			if (retCLK[i]==2) {
				//Read third day
				retCLK[i] = readRinexClocks(fdCLK[i], nextProducts[sources]);
				numConcatCLK[i]=3;
			} else {
				numConcatCLK[i]=2;
				memcpy(&nextProducts[sources]->SP3->clocks,&products[sources]->SP3->clocks,sizeof(TSP3clocks));
				nextProducts[sources]->type=SP3;
			}
		} else {
			//Not concatenated file
			numConcatCLK[i]=1;
			memcpy(&products[sources]->SP3->clocks,&pastProducts[sources]->SP3->clocks,sizeof(TSP3clocks));
			memcpy(&nextProducts[sources]->SP3->clocks,&pastProducts[sources]->SP3->clocks,sizeof(TSP3clocks));
			products[sources]->type=SP3;
			nextProducts[sources]->type=SP3;
		}

		//Check if both SP3 and CLK are concatenated with the same length
		if ( numConcatCLK[i] != numConcatSP3o[i] ) {
			sprintf(messagestr,"Clock file [%s] has not the same concatenation length as the SP3 file [%s]. Both files must be concatenated with the same length",sopt->clkFile[i],sopt->orbFile[i]);
			printError(messagestr,options);
		}
		sources++;
	}

	//Compare concatenation for both sources
	if ( (sopt->numOrb == sopt->numSP3) && sopt->numOrb>0) {
		//We have an SP3 and a SP3+CLK
		if (numConcatSP3[0]==1 && numConcatSP3o[0]>1 ) {
			//Orbits file is concatenated but SP3 file is not
			sprintf(messagestr,"WARNING: SP3 file for orbit product [%s] is concatenated, but SP3 file for orbit and clock products [%s] is not. Time range will be defined by the latter products file",sopt->orbFile[0],sopt->SP3File[0]);
			printInfo(messagestr,options);
			// Get start and end times from the non concatened SP3 file
			startTime = getProductsFirstEpoch(products[0]);
			endTime = getProductsLastEpoch(products[0]);
			memcpy(&endTimePercentage,&endTime,sizeof(TTime));

		} else if (numConcatSP3[0]>1 && numConcatSP3o[0]==1) {
			//SP3 is concatenated but orb file not
			sprintf(messagestr,"WARNING: SP3 file for orbit and clock products [%s] is concatenated, but SP3 file for orbit product [%s] is not. Time range will be defined by the latter products file",sopt->SP3File[0],sopt->orbFile[0]);
			printInfo(messagestr,options);
			// Get start and end times from the non concatened SP3 file
			startTime = getProductsFirstEpoch(products[1]);
			endTime = getProductsLastEpoch(products[1]);
			memcpy(&endTimePercentage,&endTime,sizeof(TTime));

		} else if ( numConcatSP3[0]!=numConcatSP3o[0]) {
			sprintf(messagestr,"SP3 file for orbit and clock products [%s] has a different concatenation length than SP3 file for orbit product [%s]. Both files must have the same concatenation length, or, for a single day, one file can be concantenated and the other one cannot",sopt->SP3File[0],sopt->orbFile[0]);
			printError(messagestr,options);

		} else {
			//Both files are concatenated (or not) with the same length
			if(retSP3[0]==2 && retSP3o[0]==2) {
				// Get start and end times from the first file
				startTime = getProductsFirstEpoch(pastProducts[0]);
				endTime = getProductsLastEpoch(products[0]);
				//Get file endTime from first SP3 file
				ret=readSP3LastEpoch(fdSP3[0],&endTimePercentage);
				if (ret==0) {
					printProgress=0;
					endTimePercentage.MJDN=-1;
				}
			} else {
				// Get start and end times from the first file
				startTime = getProductsFirstEpoch(pastProducts[0]);
				endTime = getProductsLastEpoch(nextProducts[0]);
				memcpy(&endTimePercentage,&endTime,sizeof(TTime));
			}
		}

		ConcatenateSP3(0,products[0],pastProducts[0],nextProducts[0],options);	
		ConcatenateSP3(0,products[1],pastProducts[1],nextProducts[1],options);	

	} else if (sopt->numSP3==2) {
		//We have two SP3 for orbits and products
		if (numConcatSP3[0]==1 && numConcatSP3[1]>1 ) {
			//Second SP3 is concatenated but first SP3 file is not
			sprintf(messagestr,"WARNING: SP3 file for orbit and clock products [%s] is concatenated, but SP3 file for orbit and clock products [%s] is not. Time range will be defined by the latter products file",sopt->SP3File[1],sopt->SP3File[0]);
			printInfo(messagestr,options);
			// Get start and end times from the non concatened SP3 file
			startTime = getProductsFirstEpoch(products[0]);
			endTime = getProductsLastEpoch(products[0]);
			memcpy(&endTimePercentage,&endTime,sizeof(TTime));

		} else if (numConcatSP3[0]>1 && numConcatSP3[1]==1) {
			//First SP3 is concatenated but second SP3 file is not
			sprintf(messagestr,"WARNING: SP3 file for orbit and clock products [%s] is concatenated, but SP3 file for orbit and clock products [%s] is not. Time range will be defined by the latter products file",sopt->SP3File[0],sopt->SP3File[1]);
			printInfo(messagestr,options);
			// Get start and end times from the non concatened SP3 file
			startTime = getProductsFirstEpoch(products[1]);
			endTime = getProductsLastEpoch(products[1]);
			memcpy(&endTimePercentage,&endTime,sizeof(TTime));

		} else if ( numConcatSP3[0]!=numConcatSP3[1]) {
			sprintf(messagestr,"SP3 file for orbit and clock products [%s] has a different concatenation length than SP3 file for orbit and clock products [%s]. Both files must have the same concatenation length, or, for a single day, one file can be concantenated and the other one cannot",sopt->SP3File[0],sopt->SP3File[1]);
			printError(messagestr,options);
		} else {
			//Both files are concatenated with the same length
			if(retSP3[0]==2 && retSP3[1]==2) {
				// Get start and end times from the first file
				startTime = getProductsFirstEpoch(pastProducts[0]);
				endTime = getProductsLastEpoch(products[0]);
				ret=readSP3LastEpoch(fdSP3[0],&endTimePercentage);
				if (ret==0) {
					printProgress=0;
					endTimePercentage.MJDN=-1;
				}
			} else {
				// Get start and end times from the first file
				startTime = getProductsFirstEpoch(pastProducts[0]);
				endTime = getProductsLastEpoch(nextProducts[0]);
				memcpy(&endTimePercentage,&endTime,sizeof(TTime));
			}
		}

		ConcatenateSP3(0,products[0],pastProducts[0],nextProducts[0],options);	
		ConcatenateSP3(0,products[1],pastProducts[1],nextProducts[1],options);	

	} else if (sopt->numOrb==2) {
		//We have two SP3 for orbits and two CLK for clocks
		if (numConcatSP3o[0]==1 && numConcatSP3o[1]>1 ) {
			//Second SP3 is concatenated but first SP3 file is not
			sprintf(messagestr,"WARNING: SP3 file for orbit product [%s] is concatenated, but SP3 file for orbit product [%s] is not. Time range will be defined by the latter product file",sopt->orbFile[1],sopt->orbFile[0]);
			printInfo(messagestr,options);
			// Get start and end times from the non concatened SP3 file
			startTime = getProductsFirstEpoch(products[0]);
			endTime = getProductsLastEpoch(products[0]);
			memcpy(&endTimePercentage,&endTime,sizeof(TTime));

		} else if (numConcatSP3o[0]>1 && numConcatSP3o[1]==1) {
			//First SP3 is concatenated but second SP3 file is not
			sprintf(messagestr,"WARNING: SP3 file for orbit product [%s] is concatenated, but SP3 file for orbit product [%s] is not. Time range will be defined by the latter product file",sopt->orbFile[0],sopt->orbFile[1]);
			printInfo(messagestr,options);
			// Get start and end times from the non concatened SP3 file
			startTime = getProductsFirstEpoch(products[1]);
			endTime = getProductsLastEpoch(products[1]);
			memcpy(&endTimePercentage,&endTime,sizeof(TTime));

		} else if ( numConcatSP3o[0]!=numConcatSP3o[1]) {
			sprintf(messagestr,"SP3 file for orbit product [%s] has a different concatenation length than SP3 file for orbit product [%s]. Both files must have the same concatenation length, or, for a single day, one file can be concantenated and the other one cannot",sopt->orbFile[0],sopt->orbFile[1]);
			printError(messagestr,options);
		} else {
			//Both files are concatenated or not with the same length
			if(retSP3o[0]==2 && retSP3o[1]==2) {
				// Get start and end times from the first file
				startTime = getProductsFirstEpoch(pastProducts[0]);
				endTime = getProductsLastEpoch(products[0]);
				ret=readSP3LastEpoch(fdSP3o[0],&endTimePercentage);
				if (ret==0) {
					printProgress=0;
					endTimePercentage.MJDN=-1;
				}
			} else {
				// Get start and end times from the first file
				startTime = getProductsFirstEpoch(pastProducts[0]);
				endTime = getProductsLastEpoch(nextProducts[0]);
				memcpy(&endTimePercentage,&endTime,sizeof(TTime));
			}
		}

		ConcatenateSP3(0,products[0],pastProducts[0],nextProducts[0],options);	
		ConcatenateSP3(0,products[1],pastProducts[1],nextProducts[1],options);	

	} else if (sopt->numNav==1 && (sopt->numOrb>0 || sopt->numSP3>0) ) {
		//We have a navigation file and a SP3 file
		if(retRNXnav[0]!=2 && ( (numConcatSP3[0]>1 && sopt->numSP3>0) || (numConcatSP3o[0]>1 && sopt->numOrb>0) ) ) {
			//Navigation file is not concatenated and SP3 are concatenated
			if(sopt->numSP3>0) {
				sprintf(messagestr,"WARNING: SP3 file for orbit and clock products [%s] is concatenated, but navigation file [%s] is not. Time range will be defined by the latter product file",sopt->SP3File[0],sopt->navFile[0]);
			} else {
				sprintf(messagestr,"WARNING: SP3 file for orbit product [%s] is concatenated, but navigation file [%s] is not. Time range will be defined by the latter product file",sopt->orbFile[0],sopt->navFile[0]);
			}
			printInfo(messagestr,options);
			// Get start and end times from navigation file
			startTimeFromNav=1;
			startTime = getProductsFirstEpoch(products[0]);
			endTime = getProductsLastEpoch(products[0]);
			memcpy(&endTimePercentage,&endTime,sizeof(TTime));

		} else if (retRNXnav[0]==2 && ( (numConcatSP3[0]==1 && sopt->numSP3>0) || (numConcatSP3o[0]==1 && sopt->numOrb>0) ) ) {
			//Navigation file concatenated but not SP3 file
			//Read the next or two next days available for the navigation file
			retRNXnav[0] = readRinexNav(fdRNXnav[0], products[0], &rinexNavVersion[0]);
			if(retRNXnav[0]==2) {
				retRNXnav[0] = readRinexNav(fdRNXnav[0], products[0], &rinexNavVersion[0]);
			}
			if(sopt->numSP3>0) {
				sprintf(messagestr,"WARNING: Navigation file [%s] is concatenated, but SP3 for orbit and clock products file [%s] is not. Time range will be defined by the latter product file",sopt->navFile[0],sopt->SP3File[0]);
			} else {
				sprintf(messagestr,"WARNING: Navigation file [%s] is concatenated, but SP3 for orbit product file [%s] is not. Time range will be defined by the latter product file",sopt->navFile[0],sopt->orbFile[0]);
			}
			printInfo(messagestr,options);
			// Get start and end times from non concatenated SP3 file
			startTime = getProductsFirstEpoch(products[1]);
			endTime = getProductsLastEpoch(nextProducts[1]);
			memcpy(&endTimePercentage,&endTime,sizeof(TTime));

		} else if (retRNXnav[0]==2 && ( (numConcatSP3[0]>1 && sopt->numSP3>0) || (numConcatSP3o[0]>1 && sopt->numOrb>0) ) ) {
			//Navigation file is concatenated and SP3 are concatenated
			//Get start time from navigation file before reading the next day (if done later, the start time would be from the second day, not the first day read)
			startTime = getProductsFirstEpoch(products[0]);
			retRNXnav[0] = readRinexNav(fdRNXnav[0], products[0], &rinexNavVersion[0]);
			if (retRNXnav[0]==2 && ( (numConcatSP3[0]<3 && sopt->numSP3>0) || (numConcatSP3o[0]<3 && sopt->numOrb>0) ) ) {
				//Three days for navigation files but only two days for SP3 files
				if(sopt->numSP3>0) {
					sprintf(messagestr,"SP3 file for orbit and clocks products [%s] has a different concatenation length than navigation file [%s]. Both files must have the same concatenation length, or, for a single day, one file can be concantenated and the other one cannot",sopt->SP3File[0],sopt->navFile[0]);
				} else {
					sprintf(messagestr,"SP3 file for orbit product [%s] has a different concatenation length than navigation file [%s]. Both files must have the same concatenation length, or, for a single day, one file can be concantenated and the other one cannot",sopt->orbFile[0],sopt->navFile[0]);
				}
				printError(messagestr,options);

			} else if (retRNXnav[0]!=2 && ( (numConcatSP3[0]==3 && sopt->numSP3>0) || (numConcatSP3o[0]==3 && sopt->numOrb>0)) ) {
				//Only two days for navigation files but three days for SP3 files
				if(sopt->numSP3>0) {
					sprintf(messagestr,"SP3 file for orbit and clocks products [%s] has a different concatenation length than navigation file [%s]. Both files must have the same concatenation length, or, for a single day, one file can be concantenated and the other one cannot",sopt->SP3File[0],sopt->navFile[0]);
				} else {
					sprintf(messagestr,"SP3 file for orbit product [%s] has a different concatenation length than navigation file [%s]. Both files must have the same concatenation length, or, for a single day, one file can be concantenated and the other one cannot",sopt->orbFile[0],sopt->navFile[0]);
				}
				printError(messagestr,options);

			} else {
				//Concatenation length matches for both files
				//We will not read the third day (if it is available) on the navigation file, so
				// the following days when navigation data ends, but the SP3 file will still have date from the following day
				//Get end time from navigation file
				endTime = getProductsLastEpoch(products[0]);
				startTimeFromNav=2;
				//Get last epoch of file from SP3 file (which can orbit+clock or only orbit)
				if (sopt->numSP3>0 && retSP3[0]==2) {
					//SP3 orbit+clock concatenated
					ret=readSP3LastEpoch(fdSP3[0],&endTimePercentage);
					if (ret==0) {
						printProgress=0;
						endTimePercentage.MJDN=-1;
					}
				} else if (sopt->numOrb>0 && retSP3o[0]==2) {
					//SP3 orbit concatenated
					ret=readSP3LastEpoch(fdSP3o[0],&endTimePercentage);
					if (ret==0) {
						printProgress=0;
						endTimePercentage.MJDN=-1;
					}
				} else {
					//SP3 of any time not concatenated more than 3 days
					endTimePercentage=getProductsLastEpoch(nextProducts[1]);
				}
			}
		} else {
			//Navigation and SP3 files are not concatenated
			//Get start and end times from SP3 file
			startTime = getProductsFirstEpoch(products[1]);
			endTime = getProductsLastEpoch(nextProducts[1]);
			memcpy(&endTimePercentage,&endTime,sizeof(TTime));
		}

		ConcatenateSP3(0,products[1],pastProducts[1],nextProducts[1],options);	

	} else if (sopt->numNav==2) {
		//Two navigation files
		if (retRNXnav[0]==2 && retRNXnav[1]!=2) {
			//First navigation file is concatenated but not the second
			sprintf(messagestr,"Navigation file [%s] is concatenated, but navigation file [%s] is not. Both navigation files must have the same concatenation length",sopt->navFile[0],sopt->navFile[1]);
			printError(messagestr,options);
		} else if (retRNXnav[0]!=2 && retRNXnav[1]==2) {
			//Second navigation file is concatenated but not the first
			sprintf(messagestr,"Navigation file [%s] is concatenated, but navigation file [%s] is not. Both navigation files must have the same concatenation length",sopt->navFile[1],sopt->navFile[0]);
			printError(messagestr,options);
		} else if (retRNXnav[0]==2 && retRNXnav[1]==2) {
			//Both files have the same concatenated length
			//Get start and end times from the first navigation file
			startTime = getProductsFirstEpoch(products[0]);
			endTime = getProductsLastEpoch(products[0]);
			//Search for last epoch in RINEX navigation files
			ret=readRinexNavLastEpoch(fdRNXnav[0],&endTimeFile1);
			if (ret==0) {
				printProgress=0;
				endTimePercentage.MJDN=-1;
			} else {
				ret=readRinexNavLastEpoch(fdRNXnav[1],&endTimeFile2);
				if (ret==0) {
					printProgress=0;
					endTimePercentage.MJDN=-1;
				} else {
					if (tdiff(&endTimeFile1,&endTimeFile2)<0.) {
						//endTimeFile1 is before endTimeFile2. Last epoch will be endTimeFile1
						memcpy(&endTimePercentage,&endTimeFile1,sizeof(TTime));
					} else {
						memcpy(&endTimePercentage,&endTimeFile2,sizeof(TTime));
					}
				}
			}
		} else {
			//Both files are not concatenated
			//Get start and end times from the first navigation file
			startTime = getProductsFirstEpoch(products[0]);
			endTime = getProductsLastEpoch(products[0]);
			memcpy(&endTimePercentage,&endTime,sizeof(TTime));
		}
		startTimeFromNav=1;
	} else {
		//Only have product file
		if (sopt->numNav==1) {
			//One navigation file
			//Get start and end times
			startTime = getProductsFirstEpoch(products[0]);
			endTime = getProductsLastEpoch(products[0]);
			if (retRNXnav[0]==2) {
				ret=readRinexNavLastEpoch(fdRNXnav[0],&endTimePercentage);
				if (ret==0) {
					printProgress=0;
					endTimePercentage.MJDN=-1;
				}
			} else {
				memcpy(&endTimePercentage,&endTime,sizeof(TTime));
			}
		} else if (sopt->numSP3==1) {
			//One SP3 file for orbits and clocks
			if(retSP3[0]==2) {
				//Get start and end times 
				startTime = getProductsFirstEpoch(pastProducts[0]);
				endTime = getProductsLastEpoch(products[0]);
				ret=readSP3LastEpoch(fdSP3[0],&endTimePercentage);
				if (ret==0) {
					printProgress=0;
					endTimePercentage.MJDN=-1;
				}
			} else {
				//Get start and end times 
				startTime = getProductsFirstEpoch(pastProducts[0]);
				endTime = getProductsLastEpoch(nextProducts[0]);
				memcpy(&endTimePercentage,&endTime,sizeof(TTime));
			}

			ConcatenateSP3(0,products[0],pastProducts[0],nextProducts[0],options);	

		} else {
			//One SP3 file for orbits and one for clocks
			if(retSP3o[0]==2) {
				//Get start and end times 
				startTime = getProductsFirstEpoch(pastProducts[0]);
				endTime = getProductsLastEpoch(products[0]);
				ret=readSP3LastEpoch(fdSP3o[0],&endTimePercentage);
				if (ret==0) {
					printProgress=0;
					endTimePercentage.MJDN=-1;
				}
			} else {
				//Get start and end times 
				startTime = getProductsFirstEpoch(pastProducts[0]);
				endTime = getProductsLastEpoch(nextProducts[0]);
				memcpy(&endTimePercentage,&endTime,sizeof(TTime));
			}

			ConcatenateSP3(0,products[0],pastProducts[0],nextProducts[0],options);	
		}
	}

	if ( sopt->numSP3>0 || sopt->numOrb >0 ) {	

		//Compute Max total distance between interpolation samples for orbits
		if(options->OrbitsMaxGaps==-1) {
			options->OrbitsMaxGaps=8;
		} 
		if(options->OrbitsMaxGaps!=0 && options->orbitInterpolationDegree!=0) {
			if (sopt->numNav==0) {
				options->OrbitsMaxDistance=OrbitsMaxDistance[0]=(double)(options->OrbitsMaxGaps*products[0]->SP3->orbits.interval);
				if ( sopt->numSP3==2 || sopt->numOrb ==2 ) {
					OrbitsMaxDistance[1]=(double)(options->OrbitsMaxGaps*products[1]->SP3->orbits.interval);
				}
			} else {
				OrbitsMaxDistance[1]=(double)(options->OrbitsMaxGaps*products[1]->SP3->orbits.interval);
			}
		} else {
			options->OrbitsMaxDistance=0.;
			OrbitsMaxDistance[0]=OrbitsMaxDistance[1]=0.;
		}

		//Compute Max total distance between first and last interpolation samples for orbits
		if(options->OrbitsToTMaxGaps==-1) {
			options->OrbitsToTMaxGaps=16;
		}
		if (options->OrbitsToTMaxGaps!=0) {
			if (sopt->numNav==0) {
				options->OrbitsToTMaxDistance=OrbitsToTMaxDistance[0]=(double)(options->orbitInterpolationDegree*products[0]->SP3->orbits.interval+options->OrbitsToTMaxGaps*products[0]->SP3->orbits.interval);
				if ( sopt->numSP3==2 || sopt->numOrb ==2 ) {
					OrbitsToTMaxDistance[1]=(double)(options->orbitInterpolationDegree*products[1]->SP3->orbits.interval+options->OrbitsToTMaxGaps*products[1]->SP3->orbits.interval);
				}
			} else {
				OrbitsToTMaxDistance[1]=(double)(options->orbitInterpolationDegree*products[1]->SP3->orbits.interval+options->OrbitsToTMaxGaps*products[1]->SP3->orbits.interval);
			}
		} else {
			options->OrbitsToTMaxDistance=0.;
			OrbitsToTMaxDistance[0]=OrbitsToTMaxDistance[1]=0.;
		}

		//Compute Max total distance between interpolation samples for clocks
		if(options->ClocksMaxGaps==-1) {
			options->ClocksMaxGaps=4;
		} 
		if(options->ClocksMaxGaps!=0) {
			if (sopt->numNav==0) {
				options->ClocksMaxDistance=ClocksMaxDistance[0]=(double)(options->ClocksMaxGaps*products[0]->SP3->clocks.interval);
				if ( sopt->numSP3==2 || sopt->numOrb ==2 ) {
					ClocksMaxDistance[1]=(double)(options->ClocksMaxGaps*products[1]->SP3->clocks.interval);
				}
			} else {
				ClocksMaxDistance[1]=(double)(options->ClocksMaxGaps*products[1]->SP3->clocks.interval);
			}
		} else {
			options->ClocksMaxDistance=0.;
			ClocksMaxDistance[0]=ClocksMaxDistance[1]=0.;
		}

		//Compute Max total distance between first and last interpolation samples for clocks
		if(options->ClocksToTMaxGaps==-1) {
			options->ClocksToTMaxGaps=8;
		}
		if(options->ClocksToTMaxGaps!=0 && options->clockInterpolationDegree!=0) {
			if (sopt->numNav==0) {
				options->ClocksToTMaxDistance=ClocksToTMaxDistance[0]=(double)(options->clockInterpolationDegree*products[0]->SP3->clocks.interval+options->ClocksToTMaxGaps*products[0]->SP3->clocks.interval);
				if ( sopt->numSP3==2 || sopt->numOrb ==2 ) {
					ClocksToTMaxDistance[1]=(double)(options->clockInterpolationDegree*products[1]->SP3->clocks.interval+options->ClocksToTMaxGaps*products[1]->SP3->clocks.interval);
				}
			} else {
				ClocksToTMaxDistance[1]=(double)(options->clockInterpolationDegree*products[1]->SP3->clocks.interval+options->ClocksToTMaxGaps*products[1]->SP3->clocks.interval);
			}
		} else {
			options->ClocksToTMaxDistance=0.;
			ClocksToTMaxDistance[0]=ClocksToTMaxDistance[1]=0.;
		}

		if(options->OrbitsToTMaxGaps<options->OrbitsMaxGaps) {
			sprintf(messagestr,"Maximum total number of data gaps in orbit interpolation given (%d) has to be equal or greater than the maximum number of data gaps between samples (%d)",options->OrbitsToTMaxGaps,options->OrbitsMaxGaps);
			printError(messagestr,options);
		}

		//Print messages for specific for SP3 products

		sprintf(messagestr,"MODELLING Orbit interpolation degree: %2d", options->orbitInterpolationDegree);
		printInfo(messagestr,options);
		sprintf(messagestr,"MODELLING Clock interpolation degree: %2d", options->clockInterpolationDegree);
		printInfo(messagestr,options);

		if(options->OrbitsMaxGaps!=0) {
			if ( sopt->numSP3==2 || sopt->numOrb==2 ) {
				if (OrbitsMaxDistance[0]==OrbitsMaxDistance[1]) {
					sprintf(messagestr,"MODELLING Max data gaps between orbit interpolation samples (both files):  %2d (%d seconds)",options->OrbitsMaxGaps,(int)OrbitsMaxDistance[0]);
					printInfo(messagestr, options);
				} else {
					sprintf(messagestr,"MODELLING Max data gaps between orbit interpolation samples (File 1):  %2d (%d seconds)",options->OrbitsMaxGaps,(int)OrbitsMaxDistance[0]);
					printInfo(messagestr, options);
					sprintf(messagestr,"MODELLING Max data gaps between orbit interpolation samples (File 2):  %2d (%d seconds)",options->OrbitsMaxGaps,(int)OrbitsMaxDistance[1]);
					printInfo(messagestr, options);
				}
			} else if ( sopt->numNav==0) {
				sprintf(messagestr,"MODELLING Max data gaps between orbit interpolation samples:  %2d (%d seconds)",options->OrbitsMaxGaps,(int)OrbitsMaxDistance[0]);
				printInfo(messagestr, options);
			} else {
				sprintf(messagestr,"MODELLING Max data gaps between orbit interpolation samples:  %2d (%d seconds)",options->OrbitsMaxGaps,(int)OrbitsMaxDistance[1]);
				printInfo(messagestr, options);
			}
		} else {
			sprintf(messagestr,"MODELLING Max data gaps between orbit interpolation samples: Unlimited");
			printInfo(messagestr, options);
		}
		if (options->OrbitsToTMaxGaps!=0) {
			if ( sopt->numSP3==2 || sopt->numOrb==2 ) {
				if (OrbitsToTMaxDistance[0]==OrbitsToTMaxDistance[1]) {
					sprintf(messagestr,"MODELLING Max data gaps in all  orbit interpolation samples (both files):  %2d (%d seconds)",options->OrbitsToTMaxGaps,(int)OrbitsToTMaxDistance[0]);
					printInfo(messagestr, options);
				} else {
					sprintf(messagestr,"MODELLING Max data gaps in all  orbit interpolation samples (File 1):  %2d (%d seconds)",options->OrbitsToTMaxGaps,(int)OrbitsToTMaxDistance[0]);
					printInfo(messagestr, options);
					sprintf(messagestr,"MODELLING Max data gaps in all  orbit interpolation samples (File 2):  %2d (%d seconds)",options->OrbitsToTMaxGaps,(int)OrbitsToTMaxDistance[1]);
					printInfo(messagestr, options);
				}
			} else if ( sopt->numNav==0) {
				sprintf(messagestr,"MODELLING Max data gaps in all  orbit interpolation samples:  %2d (%d seconds)",options->OrbitsToTMaxGaps,(int)OrbitsToTMaxDistance[0]);
				printInfo(messagestr, options);
			} else {
				sprintf(messagestr,"MODELLING Max data gaps in all  orbit interpolation samples:  %2d (%d seconds)",options->OrbitsToTMaxGaps,(int)OrbitsToTMaxDistance[1]);
				printInfo(messagestr, options);
			}
		} else {
			sprintf(messagestr,"MODELLING Max data gaps in all  orbit interpolation samples: Unlimited");
			printInfo(messagestr, options);
		}
		if (options->clockInterpolationDegree!=0) {
			if (options->ClocksToTMaxGaps!=0) {
				if ( sopt->numSP3==2 || sopt->numOrb==2 ) {
					if (ClocksMaxDistance[0]==ClocksMaxDistance[1]) {
						sprintf(messagestr,"MODELLING Max data gaps between clock interpolation samples (both files):  %2d (%d seconds)",options->ClocksMaxGaps,(int)ClocksMaxDistance[0]);
						printInfo(messagestr, options);
					} else {
						sprintf(messagestr,"MODELLING Max data gaps between clock interpolation samples (File 1):  %2d (%d seconds)",options->ClocksMaxGaps,(int)ClocksMaxDistance[0]);
						printInfo(messagestr, options);
						sprintf(messagestr,"MODELLING Max data gaps between clock interpolation samples (File 2):  %2d (%d seconds)",options->ClocksMaxGaps,(int)ClocksMaxDistance[1]);
						printInfo(messagestr, options);
					}
				} else if ( sopt->numNav==0) {
					sprintf(messagestr,"MODELLING Max data gaps between clock interpolation samples:  %2d (%d seconds)",options->ClocksMaxGaps,(int)ClocksMaxDistance[0]);
					printInfo(messagestr, options);
				} else {
					sprintf(messagestr,"MODELLING Max data gaps between clock interpolation samples:  %2d (%d seconds)",options->ClocksMaxGaps,(int)ClocksMaxDistance[1]);
					printInfo(messagestr, options);
				}
			} else {
				sprintf(messagestr,"MODELLING Max data gaps between clock interpolation samples: Unlimited");
				printInfo(messagestr, options);
			}
			if (options->ClocksToTMaxGaps!=0) {
				if ( sopt->numSP3==2 || sopt->numOrb==2 ) {
					if ( ClocksToTMaxDistance[0]==ClocksToTMaxDistance[1]) {
						sprintf(messagestr,"MODELLING Max data gaps in all  clock interpolation samples (both files):  %2d (%d seconds)",options->ClocksToTMaxGaps,(int)ClocksToTMaxDistance[0]);
						printInfo(messagestr, options);
					} else {
						sprintf(messagestr,"MODELLING Max data gaps in all  clock interpolation samples (File 1):  %2d (%d seconds)",options->ClocksToTMaxGaps,(int)ClocksToTMaxDistance[0]);
						printInfo(messagestr, options);
						sprintf(messagestr,"MODELLING Max data gaps in all  clock interpolation samples (File 2):  %2d (%d seconds)",options->ClocksToTMaxGaps,(int)ClocksToTMaxDistance[1]);
						printInfo(messagestr, options);
					}
				} else if ( sopt->numNav==0) {
					sprintf(messagestr,"MODELLING Max data gaps in all  clock interpolation samples:  %2d (%d seconds)",options->ClocksToTMaxGaps,(int)ClocksToTMaxDistance[0]);
					printInfo(messagestr, options);
				} else {
					sprintf(messagestr,"MODELLING Max data gaps in all  clock interpolation samples:  %2d (%d seconds)",options->ClocksToTMaxGaps,(int)ClocksToTMaxDistance[1]);
					printInfo(messagestr, options);
				}
			} else {
				sprintf(messagestr,"MODELLING Max data gaps in all  clock interpolation samples: Unlimited");
				printInfo(messagestr, options);
			}
		}
		sprintf(messagestr, "MODELLING Satellite Phase Centre Modelling:     %3s",options->satellitePhaseCenter? "YES" : "NO");
		printInfo(messagestr, options);
	}
		
	if ( sopt->numNav>=1 ) {
		sprintf(messagestr,"INFO MODELLING Check transmission time of navigation message is behind current epoch: %s",options->timeTrans?"ON":"OFF");
		printInfo(messagestr, options);

		sprintf(messagestr,"INFO MODELLING Use satellite 'SV Health' flag of navigation message: %s",options->satelliteHealth?"ON":"OFF");
		printInfo(messagestr, options);
	}

	//Compute number of epochs to be processed
	if (printProgress==1) {
		if ( options->decimate != 0. ) {
			tIncrease = options->decimate;
		}
		// Tune start time to start at least in an entire hour
		memcpy(&startTimeRound,&startTime,sizeof(TTime));
		startTimeRound.SoD -= modulo(startTimeRound.SoD, 3600);
		numberEpochs=tdiff(&endTimePercentage,&startTimeRound)/tIncrease;
	}

	if ( options->workMode == wmCOMPAREORBITS ) {
		compareOrbits(products, pastProducts, nextProducts, fdRNXnav, retRNXnav, rinexNavVersion, fdSP3, retSP3, fdSP3o, retSP3o, fdCLK, retCLK, OrbitsMaxDistance, OrbitsToTMaxDistance, ClocksMaxDistance, ClocksToTMaxDistance, constellation, startTime, endTime, endTimePercentage, numberEpochs, startTimeFromNav, options, sopt);
	} else if ( options->workMode == wmSHOWPRODUCT ) {
		showProduct(products[0], pastProducts[0], nextProducts[0], fdRNXnav[0], retRNXnav[0], rinexNavVersion[0], fdSP3[0], retSP3[0], fdSP3o[0], retSP3o[0], fdCLK[0], retCLK[0], constellation, startTime, endTime, endTimePercentage, numberEpochs, options, sopt);
	}
}

/*****************************************************************************
 * Name        : AddUserError2RINEX
 * Description : Read an observation file epoch by epoch, add user defined
 *                 error to measurements and write a new RINEX observation
 *                 file (the same version as the input observation file)
 * Parameters  :
 * Name                           |Da|Unit|Description
 * char *ObsFilename               I  N/A  Input observation file name
 * char *UserErrorFilename         I  N/A  Input user added error file name
 * char *OutputObsFile             I  N/A  Output observation file name
 * TEpoch  *epoch                  O  N/A  Structure to save the data
 * TUserError *UserError           O  N/A  TUserError structure
 * TOptions  *options              I  N/A  TOptions structure
 *****************************************************************************/
void AddUserError2RINEX (char *ObsFilename, char *UserErrorFilename, char *OutputObsFile, TEpoch *epoch, TUserError *UserError, TOptions *options) {

    //int i;
	int 		ret;
	FILE		*fdRNX = NULL;
	FILE		*fdNoise = NULL;
	FILE		*fdRNXoAddedError = NULL;
	char		Epochstr[80];

	ReadL1CAsItself=1;

	//Open Observation file
	fdRNX = fopen(ObsFilename,"rb");
	if ( fdRNX == NULL) {
		sprintf(messagestr,"Opening RINEX observation file [%s]",ObsFilename);
		printError(messagestr,options);
	} else if ( whatFileTypeIs(ObsFilename)!=ftRINEXobservation) {
		sprintf(messagestr,"Reading RINEX observation file [%s]",ObsFilename);
		printError(messagestr,options);
	}
	//Open user adder error file
	fdNoise = fopen(UserErrorFilename,"rb");
	if ( fdNoise == NULL ) {
		sprintf(messagestr,"Opening file [%s] for user added error to measurements",UserErrorFilename);
		printError(messagestr,options);
	}
	//Create directories for output file
	ret=mkdir_recursive(OutputObsFile);
	if(ret!=0) {
	   //Error when creating the directory, and it is not due to that the directory already exists
	   sprintf(messagestr,"When creating [%s] folder for writing corrections",OutputObsFile);
	   printError(messagestr,options);
	}
	fdRNXoAddedError = fopen(OutputObsFile,"w");
	if ( fdRNXoAddedError == NULL) {
		sprintf(messagestr,"When creating [%s] file for output RINEX observation file",OutputObsFile);
		printError(messagestr,options);
	}

	ret = readRinexObsHeader(fdRNX,fdRNXoAddedError,epoch,options);

	if (ret==0) {
		sprintf(messagestr,"Reading observation file [%s] header",ObsFilename);
		printError(messagestr,options);
	}

	//Read first epoch
	ret = readRinexObsEpoch(fdRNX,epoch,NULL,pFORWARD,Epochstr,options);

	while ( ret ) {

		//Update progress
		if (epoch->NewPercentage) { 
			epoch->NewPercentage=0;
			if (options->ProgressEndCharac=='\r') {
				//Printing to a terminal
				fprintf(options->terminalStream,"%s%c",Epochstr,options->ProgressEndCharac);
				fflush(options->terminalStream);
			} else {
				//Printing for the GUI. Only print if the integer of the percentage have changed (to avoid message spamming)
				if ((int)epoch->CurrentPercentage!=(int)epoch->PreviousPercentage) {
					fprintf(options->terminalStream,"%s%c",Epochstr,options->ProgressEndCharac);
					fflush(options->terminalStream);
				}
			}
			epoch->PreviousPercentage=epoch->CurrentPercentage;
		}
		//Add Error
		addUserError(fdNoise,UserErrorFilename,epoch,UserError,options);
		//Write output RINEX file
		writeObsRinexEpochUserAddedError(fdRNX,fdRNXoAddedError,epoch,options);

		//Read next epoch (it is done at the end so when end of file is reached the while ends,
		//whilst if it was at the beginning the last epoch would be done twice
		ret = readRinexObsEpoch(fdRNX,epoch,NULL,pFORWARD,Epochstr,options);
		if (ret==2) {
			// Read the RINEX header (if header is found, readRinexObsEpoch function does not read any data!)
			ret = readRinexObsHeader(fdRNX,fdRNXoAddedError,epoch,options);
			//If header is found, readRinexObsEpoch function does not read any data!
			//Therefore, we need to read the new header and the next epoch
			if (ret==0) {
				sprintf(messagestr,"Reading observation file [%s] header",ObsFilename);
				printError(messagestr,options);
			} else {
				ret = readRinexObsEpoch(fdRNX,epoch,NULL,pFORWARD,Epochstr,options);
			}
		}
	}

	fclose(fdRNX);
	fclose(fdNoise);
	fclose(fdRNXoAddedError);
	free(epoch);

}


/*****************************************************************************
 * Name        : main
 * Description : Main executable function
 *****************************************************************************/
int main (int argc, char* argv[]) {
	TOptions					options;
	TSupportOptions				sopt;
	TConstellation				constellation;
	TAntennaList				antennaList;
	TStationList				stationList;
	TReceiverList 				recList;
	TAntenna					*ant;
	TReceiverData				*recD;
	TStation					*station;
	TGNSSproducts				products;
	TGNSSproducts				nextSP3Prod;
	TGNSSproducts				pastSP3Prod;
	TGNSSproducts				productsKlb;
	TGNSSproducts				productsBei;
	TGNSSproducts				productsNeq;
	TGNSSproducts				productsTgd;
	TGNSSproducts				ReferencePos;
	TIONEX						ionex;
	TIONEX						productsIonex;
	TFPPPIONEX					fppp;
	TFPPPIONEX					productsFppp;
	TTROPOGal					tropoGal;
	TSBASdatabox				SBASdatabox;
	TTGDdata					tgdData;
	TEpoch						*epoch = NULL;
	TEpoch						*epochDGNSS = NULL;
	TUserError					UserError;
	TStdESA						StdESA;
	FILE						*fdRNX = NULL;
	FILE						*fdRNXnav = NULL;
	FILE						*fdRNXKlb = NULL;
	FILE						*fdRNXBei = NULL;
	FILE						*fdRNXNeq = NULL;
	FILE						*fdIONEX = NULL;
	FILE						*fdSP3 = NULL;			// Full file (orbits plus clocks)
	FILE						*fdSP3o = NULL;			// Read only orbits
	FILE						*fdOutSP3 = NULL;		// Output SP3 file
	FILE						*fdOutRefFile = NULL;	// Output reference file
	FILE						*fdCLK = NULL;
	FILE						*fdNoise = NULL;
	FILE						*fdstdESA = NULL;
	FILE						*fdRNXdgnss = NULL;
	FILE						*fdRTCM = NULL;
	FILE						*fdRTCM2 = NULL;
	FILE						*fdRTCM3 = NULL;
	FILE						*fdTGD[2];
	int							ret, ret1, ret2, retDGNSS = 1;
	int							retsbas, retPosFile;
	int							i,j,k,l;
	double						r;
	double						ionexVersion = 0;
	double						rinexBVersion = 0;
	double						rinexNavVersion = 0;
	double						fpppVersion = 0;
	int							kalmanRes;
	int							numsatellites;
	enum fileType				auxft1;
	int							processedEpochs;
	enum ProcessingDirection	direction;
	int							filterIterations;
	TTime						endProductsTime;
	TTime						startProductsTime;
	int							anyInsideProducts = 0;
	int							kalmanIterations;
	int							chdirret;
	double						deltaTime;
	int							computeDGNSScor;
	TRTCM2						*rtcm2 = NULL;
	TRTCM3						*rtcm3 = NULL;
	char						*fileRINEXpointer = NULL;
	int							concatCount = 1;
	int							Measprinted;
	int							RTCMversion;
	int							UseReferenceFile=0;
	int							DoY,MJDN,MJDNEpoch=-1;
	int							Summary=0;
	int							firstEpoch=1;
	int							OrbInterpDegree;
	int							nextNav=0;
	int							retTGD[2];
	
	// Filter
	TFilterSolution				solution;
	TUnkinfo					prevUnkinfo;
	int							PRNlist[MAX_SATELLITES_VIEWED];  // Only GPS!

	//Variables for SBAS plot mode
	int							GEOused;
	int							currenttime;
	int							currenthour;
	int							ionoerror;
	int							latPos;
	int							lonPos;
	int							totalAvailabilityEpochs;
	int							totalAvailabilityEpochsHourly;
	int							totalIonoEpochs;
	int							totalIonoEpochsHourly;
	int							InitialSBASPlotsEpoch;
	int    					    SBASPlotYear;
	int							InsideInclusionArea;
	int							InsideExclusionArea;
	int							Epochsleft;
	int							excludedGEOs=0;
	double				 	    SBASPlotDoY;
	double						latitude,longitude;
	FILE						*fdSBASAvail = NULL;
	FILE						*fdSBASAvailHour[24];
	FILE						*fdSBASRisk = NULL;
	FILE						*fdSBASRiskHour[24];
	FILE						*fdSBASDiscont = NULL;
	FILE						*fdSBASDiscontHour[24];
	FILE						*fdSBASIono = NULL;
	FILE						*fdSBASIonoHour[24];
	TSBAScorr 					SBAScorr;
	TSBASPlots 					*SBASplots = NULL;
	char						HourFileName[MAX_OUTPUT_FILENAME];
	char						Epochstr[80];
	char						auxstr[400];

	// IMPORTANT NOTE: TEpoch structures have been declared as pointers and initialized to NULL. 
	// Later they will have memory allocated in the heap using the malloc function.
	// If they had not been declared as pointers, but as local variables, the memory for the structures
	// would have been allocated in the stack. The difference between the stack and the heap is that
	// the stack has a fixed size, which depends on the OS (normally around 10MB). If we try
	// to allocate too much memory in the stack, a stack overflow will occur, resulting in a
	// segmentation fault. When a segmentation fault occurs due to a stack overflow, any debugger
	// will point that the segmentation fault has been produced just when entering the function
	// that has produced the stack overflow (but without saying explicitly that it was a stack
	// overflow). For example, if the structures epoch and DGNSS had been declared as local variables,
	// a segmentation fault would have been produced just when entering the main function.

	// Variables for paths
	char	path_save[1000];
	char	*p;

	 #if !defined __WIN32__ && !defined __APPLE__
	// Variables for gathering linux or Cygwin path
	char	path[1000];
	int		execlength,pathlen;
	#endif

	// Auxiliary variables for gathering path in linux and signal handling
	#if !defined (__WIN32__)
		enableCursor[0]='\0';
		disableCursor[0]='\0';
		StdoutStream=NULL;
		pid = getpid();
		//Set signal functions
		if (signal(SIGINT, &sigIntSignal) == SIG_ERR) {
			//If signals are not caught, do not disable cursor
			sopt.disableCursor=0;
		}
		if (signal(SIGTSTP, &sigStpSignal) == SIG_ERR) {
			//If signals are not caught, do not disable cursor
			sopt.disableCursor=0;
		}
		if (signal(SIGCONT, &sigContSignal) == SIG_ERR) {
			//If signals are not caught, do not disable cursor
			sopt.disableCursor=0;
		}
	#else
		sopt.disableCursor=0; //In Windows, do not disable cursor
	#endif

	// Save absolute path of the executable, not the actual path. Needed for reading Galileo troposphere and NeQuick model files
	#if defined __WIN32__
		if ( !(p = strrchr(argv[0],'\\')) ) {
			//No backslashes in path
			p = getcwd(options.abs_exe_path,sizeof(options.abs_exe_path));
	#elif defined __CYGWIN__
		if ( (!(p = strrchr(argv[0],'\\'))) && (!(p = strrchr(argv[0],'/'))) ) {
			//No backslashes or slahes in path
			//In Cygwin (like in Linux), the executable path is in the softlink /proc/<pid>/exe
			sprintf(path,"/proc/%d/exe",pid);
			if ( readlink(path,options.abs_exe_path,sizeof(path)) == -1) {
				sprintf(messagestr,"When reading gLAB executable folder through the softlink [%s]",path);
				printError(messagestr,&options);
			}
			//Readlink returns the path with the executable, the name of the executable must be taken out from the path
			pathlen = strlen(options.abs_exe_path);
			execlength = strlen(strrchr(options.abs_exe_path,'/'));
			options.abs_exe_path[pathlen-execlength] = '\0';
	#elif defined __APPLE__
		//Apple has no /proc folder
		if ( !(p = strrchr(argv[0],'/')) ) {
			//No slashes in path
			p = getcwd(options.abs_exe_path,sizeof(options.abs_exe_path));
	#else
		if ( !(p = strrchr(argv[0],'/')) ) {
			//No slashes in path
			//In Linux, the executable path is in the softlink /proc/<pid>/exe
			sprintf(path,"/proc/%d/exe",pid);
			if ( readlink(path,options.abs_exe_path,sizeof(path)) == -1) {
				sprintf(messagestr,"When reading gLAB executable folder through the softlink [%s]",path);
				printError(messagestr,&options);
			}
			//Readlink returns the path with the executable, the name of the executable must be taken out from the path
			pathlen = strlen(options.abs_exe_path);
			execlength = strlen(strrchr(options.abs_exe_path,'/'));
			options.abs_exe_path[pathlen-execlength] = '\0';
	#endif
		} else {
			*p = '\0';
			p = getcwd(path_save, sizeof(path_save));
			chdirret = chdir(argv[0]);
			if ( chdirret==-1) {
				printError("When accessing gLAB executable folder",&options);
			}
			p = getcwd(options.abs_exe_path, sizeof(options.abs_exe_path));
			chdirret = chdir(path_save);
		}



	// Initialise
	epoch = malloc(sizeof(TEpoch));
	rtcm2 = malloc(sizeof(TRTCM2));
	rtcm3 = malloc(sizeof(TRTCM3));

	Epochstr[0]='\0';
	printProgress=-1;

	for ( i = 0; i < MAX_SATELLITES_VIEWED; i++ ) {
		for ( j = 0; j < MAX_LINES_BUFFERED; j++ ) {
			printbufferSATSEL[i][j][0] = '\0';
		}
		linesstoredSATSEL[i] = 0;
		printbufferPREFIT[i][0] = '\0';
		printbufferPOSTFIT[i][0] = '\0';
		printbufferMODEL[i][0] = '\0';
		printbufferSBASCORR[i][0] = '\0';
		printbufferSBASVAR[i][0] = '\0';
		printbufferSBASIONO[i][0] = '\0';
		printbufferSBASUNSEL[i][0] = '\0';

	}
	printbufferEPOCHSAT[0] = '\0';
	printbufferFILTER[0] = '\0';

	// Initialise
	initSupportOptions(&sopt);
	initOptions(&options);
	initGNSSproducts(&products);
	initGNSSproducts(&nextSP3Prod);
	initGNSSproducts(&pastSP3Prod);
	initGNSSproducts(&productsTgd);
	initGNSSproducts(&productsKlb);
	initGNSSproducts(&productsBei);
	initGNSSproducts(&productsNeq);
	initGNSSproducts(&ReferencePos);
	initConstellation(&constellation);
	initFilterSolution(&solution);
	initAntennaList(&antennaList);
	initTGD(&tgdData,p1c1NONE,p1p2NONE);
	initReceiverList(&recList);
	initStationList(&stationList);
	initIONEX(&ionex);
	initIONEX(&productsIonex);
	initFPPPIONEX(&fppp);
	initFPPPIONEX(&productsFppp);
	initSBASdatabox(&SBASdatabox);
	initTropoGalData(&tropoGal);
	initSBASdata(SBASdatabox.SBASdata,0);
	initUserError(&UserError);
	initRTCM2(rtcm2);
	initRTCM3(rtcm3);

	// Copy tmout values to options storage. Therefore, initially it will have the default values
	memcpy(options.usertmout, SBASdatabox.SBASdata[0].timeoutmessages, sizeof(options.usertmout));
	
	// Parse options
	if ( !parseAllOptions(&sopt, &options, argc, argv) ) {
		exit(-1);
	}
	for ( i = 0; i < 2; i++ ) {
		// This loop is done twice in order to override defaults of PPP and 
		// standalone once options are processed
		sopt.numNav = 0;
		sopt.numSP3 = 0;
		sopt.numOrb = 0;
		sopt.numClk = 0;
		sopt.numTGD = 0;
		sopt.deprecatedMessages[0] = '\0';
		fdTGD[i]=NULL;
		retTGD[i]=0;
		
		// Check if configuration file parameter exists
		ret = checkConfigFile(&sopt, &options);
		if ( ret == -1 ) {
			sprintf(messagestr, "Problems with config file [%s]", sopt.cfgFile);
			printError(messagestr, &options);
		} else { // Configuration file parameter found and file parsed properly
			// Parse all command-line options again
			if ( !parseAllOptions(&sopt, &options, argc, argv) ) {
				exit(-1);
			}
		}
		// Process options
		if ( i == 0 ) {
			if ( !processOptions(&sopt, &options) ) {
				exit(-1);
			}
		}
	}

	//Init epoch after reading options
	initEpoch(epoch,&options);

	//Add User Error to RINEX measurements
	if (options.workMode == wmUSERERROR2RINEX) {
		sprintf(messagestr,"Input RINEX observation file: %s",sopt.obsFile);
		printInfo(messagestr,&options);
		sprintf(messagestr,"User defined error input file: %s",sopt.addederrorFile);
		printInfo(messagestr,&options);
		sprintf(messagestr,"Output RINEX observation file: %s",sopt.rnxFile);
		printInfo(messagestr,&options);
		
		AddUserError2RINEX(sopt.obsFile,sopt.addederrorFile,sopt.rnxFile,epoch,&UserError,&options);
		//Enable cursor
		if (printProgress) {
			fprintf(options.terminalStream,"%.56s (100%%)%10s%c",Epochstr,"",options.ProgressEndCharac);
			//The fflush of the terminal is to avoid flickering of the cursor due to the high output write rate
			fflush(options.terminalStream);
			#if !defined (__WIN32__)
				//This is to clear terminal for characters after finishing (in Windows is not necessary as it adds a newline when the process finishes)
				fprintf(options.terminalStream,"%70s%c","",options.ProgressEndCharac); 
				//Enable cursor if necessary
				if (sopt.disableCursor==1) {
					fprintf(options.terminalStream,"%s",enableCursor);
				}
				fflush(options.terminalStream);
			#endif
		}
		exit(0);
	}
	
	// SBAS data. It must be at the beginning because we can do only file format conversion
	if ( options.SBAScorrections == 1 ) {

		// If the option of using Klobuchar in first epochs is enabled, set the receiver solution to not converged
		if ( options.initcoordNPA == 1 && options.receiverPositionSource >= rpCALCULATE ) epoch->receiver.receiverSolConverged = 0;

		// Save user tmout values
		memcpy(SBASdatabox.SBASdata[0].timeoutmessages,options.usertmout,sizeof(options.usertmout));

		epoch->t.MJDN = -1;
		epoch->t.SoD = 0.0;
		if ( sopt.sbasFile[0] != '\0' ) {
			if (printProgress==1) {	
				if (options.ProgressEndCharac=='\r') {
					//Printing to a terminal
					fprintf(options.terminalStream,"Reading SBAS data%50s%c","",options.ProgressEndCharac);
					fflush(options.terminalStream);
				}
			}
			if ( readSBASFile(sopt.sbasFile, &SBASdatabox, &rinexBVersion, &epoch->t, &options) != 1 ) {
				if ( (int)rinexBVersion > 2 && rinexBVersion != 0 ) {
					sprintf(messagestr, "RINEX-B version %1.2f from file [%s] not supported. Supported version is 2", rinexBVersion, sopt.sbasFile);
					printError(messagestr, &options);
				} else {
					sprintf(messagestr, "Reading SBAS input file [%s]", sopt.sbasFile);
					printError(messagestr, &options);
				}
			}
		} else {
			printError("No SBAS file provided, but SBAS corrections are selected", &options);
		}
		if ( options.onlyconvertSBAS == 1 ) {
			if (printProgressConvert==1 ) {
				fprintf(options.terminalStream,"Percentage converted: %5d%%%10s%c",100,"",options.ProgressEndCharac);
				#if !defined (__WIN32__)
					if (sopt.disableCursor==1) {
						//Enable cursor again
						fprintf(options.terminalStream,"%s",enableCursor);
					}
				#endif
				fflush(options.terminalStream);
			}
			exit(0);
		}

		// Check if there is a user sigma multipath model to be read
		if ( options.usersigmamultipath == 1 ) {
			if ( sopt.sigmamultipathFile[0] != '\0' )	 {
				if ( readsigmamultipathFile(sopt.sigmamultipathFile,SBASdatabox.SBASdata,&options) != 1 ) {
					sprintf(messagestr,"Reading SBAS sigma multipath file [%s]",sopt.sigmamultipathFile);
					printError(messagestr,&options);
				}
			} else {
				printError("No user defined sigma multipath model file provided, but user defined sigma multipath model is selected",&options);
			}
		}
	} 

	if(options.useDatasummary == 1) {
		Summary=1;
	} else {
		Summary=0;
	}

	// If Stanford-ESA plot is selected, compute the number of pixels and give size to StdEsa.count matrix
	if ( options.stanfordesa == 1 ) {
		// Open file for writing Stanford-ESA plot data
		//Create directory recursively if needed
		ret=mkdir_recursive(sopt.stanfordESAFile);
		if(ret!=0) {
		   //Error when creating the directory, and it is not due to that the directory already exists
		   sprintf(messagestr,"When creating [%s] folder for writing Stanford-ESA plot data",sopt.stanfordESAFile);
		   printError(messagestr,&options);
		}

		fdstdESA = fopen(sopt.stanfordESAFile,"w");
		if ( fdstdESA == NULL ) {
			sprintf(messagestr,"Opening [%s] file for writing Stanford-ESA plot data",sopt.stanfordESAFile);
			printError(messagestr,&options);
		}

		if (options.stanfordesaLOI == 1) {
			// Open file for writing Stanford-ESA plot data
			//Create directory recursively if needed
			ret=mkdir_recursive(sopt.stanfordESALOIFile);
			if(ret!=0) {
			   //Error when creating the directory, and it is not due to that the directory already exists
			   sprintf(messagestr,"When creating [%s] folder for writing Stanford-ESA LOI data",sopt.stanfordESALOIFile);
			   printError(messagestr,&options);
			}
			options.fdstdESALOI = fopen(sopt.stanfordESALOIFile,"w");
			if ( options.fdstdESALOI == NULL ) {
				sprintf(messagestr,"Opening [%s] file for writing Stanford-ESA LOI data",sopt.stanfordESALOIFile);
				printError(messagestr,&options);
			}
			//Write header to file
			fprintf(options.fdstdESALOI,"#YEAR DoY      SoD GPSWeek       SoW HIR_THR VIR_THR    HPE    VPE    HPL    VPL     HIR     VIR TOTALSAT USEDSAT LISTSAT\n");
		}

		// Copy values from sopt structure
		StdESA.xmax = sopt.stfdesaxmax;
		StdESA.ymax = sopt.stfdesaymax;
		StdESA.xstep = sopt.stfdesaxres;
		StdESA.ystep = sopt.stfdesayres;

		// Initialize StdESA structure
		initStfdESA(&StdESA);
	}

	// Set Minimum Arc Length for Cycle Slip Detectors
	options.minArcLength = max(options.csL1C1samples*options.csL1C1,max(options.csLIsamples*options.csLI,options.csBWsamples*options.csBW));
	//options.minArcLength = max(options.minArcLength,options.csLCsamples*options.csLC);

	// Read files
	if ( sopt.obsFile[0] != '\0' ) {
		// Note that the file is opened in "rb" mode, "r" is for readonly, and "b" is for binary mode. In Linux, the "b" flag is ignored,
		// but, in Windows it will make to not merge multibyte character into a single one (for example the windows newline \r\n to a \n)
		// This is important if you are going to use the fseek function with this file, because if you are reading a text file with a
		// Linux end of file ("\n") in Windows, fseek will not work well unless the file is opened with binary mode (due to fseek expects
		// the Windows end of line ("\r\n") when opening the file in normal mode.
		// The only downside of opening a file in binary mode is that you can't use the fseek function with the "SEEK_END" flag, because
		// it may have undefined behaviour (according to C Standard "because of possible trailing null characters")
		// In gLAB, the fseek function is only used in the getLback function
		fdRNX = fopen(sopt.obsFile,"rb");
		if ( fdRNX == NULL) {
			sprintf(messagestr,"Opening RINEX observation file [%s]",sopt.obsFile);
			printError(messagestr,&options);
		} else if (whatFileTypeIs(sopt.obsFile)!=ftRINEXobservation) {
			sprintf(messagestr,"Reading RINEX observation file [%s]",sopt.obsFile);
			printError(messagestr,&options);
		}
	}
	

	if ( sopt.dgnssFile[0] != '\0' ) {
		fdRNXdgnss = fopen(sopt.dgnssFile,"rb");
		if ( fdRNXdgnss == NULL) {
			sprintf(messagestr, "Opening RINEX observation file [%s] for reference station in DGNSS mode", sopt.dgnssFile);
			printError(messagestr, &options);
		} else if ( whatFileTypeIs(sopt.dgnssFile)!=ftRINEXobservation) {
			sprintf(messagestr, "Reading RINEX observation file [%s] for reference station in DGNSS mode", sopt.dgnssFile);
			printError(messagestr, &options);
		} else {
			sprintf(messagestr, "RINEX observation input file as reference station: %s", sopt.dgnssFile);
			printInfo(messagestr, &options);
		}
	}

	// RTCM unknown version
	RTCMversion = 0;
	if ( sopt.rtcmFile[0] != '\0' ) {
		options.RTCMmode = RTCMCheckVersion; // Check what version of RTCM is the binary file
		if ( !(fdRTCM = fopen(sopt.rtcmFile, "rb")) ) {
			sprintf(messagestr, "Opening the RTCM binary file [%s]", sopt.rtcmFile);
			printError(messagestr, &options);
		}
		RTCMversion = converterRTCM2(fdRTCM, rtcm2, NULL, NULL, NULL, NULL, &options);
		if ( RTCMversion == 2 ) strcpy(sopt.rtcm2File, sopt.rtcmFile);
		else {
			RTCMversion = converterRTCM3(fdRTCM, rtcm3, NULL, NULL, epoch, &options);
			if ( RTCMversion != 3 ) {
				fclose(fdRTCM);
				free(rtcm2);
				free(rtcm3);
				sprintf(messagestr, "File [%s] format unknown.", sopt.rtcmFile);
				printError(messagestr, &options);
			} else strcpy(sopt.rtcm3File, sopt.rtcmFile);
		}
	}
	// RTCM v2.x
	if ( sopt.rtcm2File[0] != '\0' ) {
		if ( !(fdRTCM2 = fopen(sopt.rtcm2File, "rb")) ) {
			sprintf(messagestr, "Opening RTCM v2.x binary file [%s] for reference station in DGNSS mode", sopt.rtcm2File);
			printError(messagestr, &options);
		} else if ( options.rtcmYear == 0 || options.rtcmMonth == 0 || options.rtcmDay == 0 ) {
			sprintf(messagestr, "Option \"-input:rtcm:initdate\" must be set");
			printError(messagestr, &options);
		} else if ( options.rtcmHour == -1 ) {
			sprintf(messagestr, "Option \"-input:rtcm:inithour\" must be set");
			printError(messagestr, &options);
		} else {
			options.RTCMmode = RTCMCheckVersion;
			RTCMversion = converterRTCM2(fdRTCM2, rtcm2, NULL, NULL, NULL, NULL, &options);
			if ( RTCMversion != 2 ) {
				fclose(fdRTCM2);
				free(rtcm2);
				free(rtcm3);
				sprintf(messagestr, "File [%s] does not have RTCM v2.x format.", sopt.rtcm2File);
				printError(messagestr, &options);
			}
			sprintf(messagestr, "RTCM v2.x as reference station input file: %s", sopt.rtcm2File);
			printInfo(messagestr, &options);
			options.RTCMmode = ProcessRTCM2;
		}
	}
	// RTCM v3.x
	if ( sopt.rtcm3File[0] != '\0' ) {
		if ( !(fdRTCM3 = fopen(sopt.rtcm3File, "rb")) ) {
			sprintf(messagestr, "Opening RTCM v3.x binary file [%s] for reference station in DGNSS mode", sopt.rtcm3File);
			printError(messagestr,&options);
		} else if ( options.rtcmYear == 0 || options.rtcmMonth == 0 || options.rtcmDay == 0 ) {
			sprintf(messagestr, "Option \"-input:rtcm:initdate\" must be set");
			printError(messagestr, &options);
		} else {
			options.RTCMmode = RTCMCheckVersion;
			RTCMversion = converterRTCM3(fdRTCM3, rtcm3, NULL, NULL, epoch, &options);
			if ( RTCMversion != 3 ) {
				fclose(fdRTCM3);
				free(rtcm2);
				free(rtcm3);
				sprintf(messagestr, "File [%s] does not have RTCM v3.x format.", sopt.rtcm3File);
				printError(messagestr, &options);
			}
			sprintf(messagestr, "RTCM v3.x as reference station input file: %s", sopt.rtcm3File);
			printInfo(messagestr, &options);
			options.RTCMmode = ProcessRTCM3;
		}
	}
	// Actions in case of DGNSS mode
	if ( options.DGNSS ) {
		epochDGNSS = malloc(sizeof(TEpoch));
		initEpoch(epochDGNSS,&options);
		epochDGNSS->DGNSSstruct=1;
		// Check if S/A was enabled or not
		if ( options.RTCMmode > ConvertRTCM3 && options.RTCMmode < ProcessRINEX ) {
			DoY = date2doy((int)options.rtcmYear, (int)options.rtcmMonth, (int)options.rtcmDay);
			MJDN = (int)yeardoy2MJDN((int)options.rtcmYear, DoY, 0);
			// We do not apply Range Rate Corrections because we assume S/A disabled.
			// In case of S/A enabled, the maximum age is set to 1 seconds
			if ( MJDN < 51665 /*May 1st, 2000*/ ) {
				options.maxAgeDGNSS = 1;
				printInfo("WARNING the maximum age to apply DGNSS corrections is forced to 1 seconds due to S/A", &options);
			}
		}

		//Check receiver position mode in DGNSS is valid (user defined reference station is only allowed with RINEX files)
		if ( options.receiverPositionSource >= rpRTCMUserbaseline && ( sopt.rtcmFile[0] != '\0' || sopt.rtcm3File[0] != '\0' || sopt.rtcm3File[0] != '\0' ) ) {
			printError("Receiver position modes 'DGNSSUserRoverRef', 'DGNSSUserRoverRefGeod', 'DGNSSUserbaseline', 'DGNSSUserGeodbaseline',  'DGNSSUserRinexRover', 'DGNSSUserGeodRinexRover', 'DGNSSRefRoverUSER', 'DGNSSRefGeodRoverUSERGeod', 'DGNSSRefCarRoverUSERGeod' or 'DGNSSRefGeodRoverUSERCar' are only allowed when the reference station data is from a RINEX file. Convert the RTCM file to RINEX and process with the converted RINEX file",&options);
		}
	}
	if ( sopt.navFile[0][0] != '\0' ) {
		fdRNXnav = fopen(sopt.navFile[0],"rb");
		if (fdRNXnav == NULL) {
			sprintf(messagestr,"Opening RINEX navigation file [%s]",sopt.navFile[0]);
			printError(messagestr,&options);
		} else if (whatFileTypeIs(sopt.navFile[0])!=ftRINEXbroadcast) {
			sprintf(messagestr,"Reading RINEX navigation file [%s]",sopt.navFile[0]);
			printError(messagestr,&options);
		}
	}
	if ( sopt.klbFile[0] != '\0' ) {
		fdRNXKlb = fopen(sopt.klbFile,"rb");
		if (fdRNXKlb == NULL) {
			sprintf(messagestr,"Opening RINEX navigation file [%s]",sopt.klbFile);
			printError(messagestr,&options);
		} else if (whatFileTypeIs(sopt.klbFile)!=ftRINEXbroadcast) {
			sprintf(messagestr,"Reading RINEX navigation file [%s]",sopt.klbFile);
			printError(messagestr,&options);
		}
	}
	if ( sopt.beiFile[0] != '\0' ) {
		fdRNXBei = fopen(sopt.beiFile,"rb");
		if ( fdRNXBei == NULL) {
			sprintf(messagestr,"Opening RINEX navigation file [%s]",sopt.beiFile);
			printError(messagestr,&options);
		} else if (whatFileTypeIs(sopt.beiFile)!=ftRINEXbroadcast) {
			sprintf(messagestr,"Reading RINEX navigation file [%s]",sopt.beiFile);
			printError(messagestr,&options);
		}
	}
	if ( sopt.neqFile[0] != '\0' ) {
		fdRNXNeq = fopen(sopt.neqFile,"rb");
		if ( fdRNXNeq == NULL ) {
			sprintf(messagestr,"Opening RINEX navigation file [%s]",sopt.neqFile);
			printError(messagestr,&options);
		} else if (whatFileTypeIs(sopt.neqFile)!=ftRINEXbroadcast) {
			sprintf(messagestr,"Reading RINEX navigation file [%s]",sopt.neqFile);
			printError(messagestr,&options);
		}
	}
	if ( sopt.inxFile[0] != '\0' ) {
		fdIONEX = fopen(sopt.inxFile,"rb");
		if ( fdIONEX == NULL ) {
			sprintf(messagestr,"Opening IONEX file [%s]",sopt.inxFile);
			printError(messagestr,&options);
		} else if (whatFileTypeIs(sopt.inxFile)!=ftIONEX) {
			sprintf(messagestr,"Reading IONEX file [%s]",sopt.inxFile);
			printError(messagestr,&options);
		}
	}
	if ( options.workMode == wmDOPROCESSING || options.workMode == wmSHOWINPUT ) {
		if ( sopt.SP3File[0][0] != '\0' ) {
			if (!(fdSP3 = fopen(sopt.SP3File[0],"rb"))) {
				sprintf(messagestr,"Opening SP3 orbit products file [%s]",sopt.SP3File[0]);
				printError(messagestr,&options);
			}
		}
		if ( sopt.orbFile[0][0] != '\0' ) {
			if (!(fdSP3o = fopen(sopt.orbFile[0],"rb"))) {
				sprintf(messagestr,"Opening SP3 orbit products file [%s]",sopt.orbFile[0]);
				printError(messagestr,&options);
			}
		}
		if ( sopt.clkFile[0][0] != '\0' ) {
			if (!(fdCLK = fopen(sopt.clkFile[0],"rb"))) {
				sprintf(messagestr,"Opening clock products file [%s]",sopt.clkFile[0]);
				printError(messagestr,&options);
			}
		}
	}

	// Open output KML, KML0 SP3 and reference files
	if ( options.workMode == wmDOPROCESSING ) {
		if ( sopt.kmlFile[0] != '\0' && sopt.kml0File[0] != '\0' && strcmp(sopt.kmlFile,sopt.kml0File)==0) {
			sprintf(messagestr,"KML files with the solution and the ground projection cannot have the same filename");
			printError(messagestr,&options);
		}
		if ( sopt.kmlFile[0] != '\0' ) {
			//Create directory recursively if needed
			ret=mkdir_recursive(sopt.kmlFile);
			if(ret!=0) {
			   //Error when creating the directory, and it is not due to that the directory already exists
			   sprintf(messagestr,"When creating [%s] folder for writing KML file",sopt.kmlFile);
			   printError(messagestr,&options);
			}
			options.fdkml=fopen(sopt.kmlFile,"w");
			if (options.fdkml==NULL) {
				sprintf(messagestr,"Opening KML output file [%s]",sopt.kmlFile);
				printError(messagestr,&options);
			} else {
				//Insert XML opening tags
				writeKMLtags(options.fdkml,epoch,sopt.obsFile,0,0,VERSION,&options);
			}
		}
		if ( sopt.kml0File[0] != '\0' ) {
			//Create directory recursively if needed
			ret=mkdir_recursive(sopt.kml0File);
			if(ret!=0) {
			   //Error when creating the directory, and it is not due to that the directory already exists
			   sprintf(messagestr,"When creating [%s] folder for writing KML (ground projection) file",sopt.kml0File);
			   printError(messagestr,&options);
			}
			options.fdkml0=fopen(sopt.kml0File,"w");
			if (options.fdkml0==NULL) {
				sprintf(messagestr,"Opening KML (ground projection) output file [%s]",sopt.kml0File);
				printError(messagestr,&options);
			} else {
				//Insert XML opening tags
				writeKMLtags(options.fdkml0,epoch,sopt.obsFile,0,1,VERSION,&options);
			}
		}

		if ( sopt.SP3OutputFile[0] != '\0' ) {
			//Create directory recursively if needed
			ret=mkdir_recursive(sopt.SP3OutputFile);
			if(ret!=0) {
			   //Error when creating the directory, and it is not due to that the directory already exists
			   sprintf(messagestr,"When creating [%s] folder for writing SP3 file",sopt.SP3OutputFile);
			   printError(messagestr,&options);
			}
			fdOutSP3=fopen(sopt.SP3OutputFile,"w");
			if (fdOutSP3==NULL) {
				sprintf(messagestr,"Opening SP3 output file [%s]",sopt.SP3OutputFile);
				printError(messagestr,&options);
			} 
		}
		if ( sopt.RefPosOutputFile[0] != '\0' ) {
			//Create directory recursively if needed
			ret=mkdir_recursive(sopt.RefPosOutputFile);
			if(ret!=0) {
			   //Error when creating the directory, and it is not due to that the directory already exists
			   sprintf(messagestr,"When creating [%s] folder for writing reference file",sopt.RefPosOutputFile);
			   printError(messagestr,&options);
			}
			fdOutRefFile=fopen(sopt.RefPosOutputFile,"w");
			if (fdOutRefFile==NULL) {
				sprintf(messagestr,"Opening reference position output file [%s]",sopt.RefPosOutputFile);
				printError(messagestr,&options);
			} 
			#if defined _OPENMP
				fprintf(fdOutRefFile,"#gLAB version v%s (with OpenMP multithread), built on %s %s\n",VERSION,__DATE__,__TIME__);
			#else
				fprintf(fdOutRefFile,"#gLAB version v%s, built on %s %s\n",VERSION,__DATE__,__TIME__);
			#endif
			fprintf(fdOutRefFile,"#Solution in %s mode for file %s\n",SolutionModeNum2SolutionModeChar(options.solutionMode),sopt.obsFile);
			if (options.DGNSS) {
				fprintf(fdOutRefFile,"#Solutions in SPP are%s included\n",options.WriteSPPsolInDGNSSmodeRefFile?"":" not");
			}
			if (options.GPSWeekRefFile==1) {
				if (options.GeodeticCoordRefFile==1) {
				 	fprintf(fdOutRefFile,"#Geodetic coordinates are in WGS84 datum\n#Latitude is in degrees [-90º..90º]\n#Longitude is in degrees [-180º..180º]\n#Height is in metres\n");
					fprintf(fdOutRefFile,"GPSWeek    SoW      Longitude       Latitude         Height\n");
				} else {
					fprintf(fdOutRefFile,"#Cartesian coordinates are in WGS84 datum\n#X, Y and Z are in metres\n");
					fprintf(fdOutRefFile,"GPSWeek    SoW              X              Y              Z\n");
				}
			} else if (options.CalendarTimeRefFile==1) {
				if (options.GeodeticCoordRefFile==1) {
				 	fprintf(fdOutRefFile,"#Geodetic coordinates are in WGS84 datum\n#Latitude is in degrees [-90º..90º]\n#Longitude is in degrees [-180º..180º]\n#Height is in metres\n");
					fprintf(fdOutRefFile,"Date               Time      Longitude       Latitude         Height\n");
				} else {
					fprintf(fdOutRefFile,"#Cartesian coordinates are in WGS84 datum\n#X, Y and Z are in metres\n");
					fprintf(fdOutRefFile,"Date               Time              X              Y              Z\n");
				}
			} else {
				if (options.GeodeticCoordRefFile==1) {
					fprintf(fdOutRefFile,"#Geodetic coordinates are in WGS84 datum\n#Latitude is in degrees [-90º..90º]\n#Longitude is in degrees [-180º..180º]\n#Height is in metres\n");
					fprintf(fdOutRefFile,"Year DoY       SoD      Longitude       Latitude         Height\n");
				} else {
					fprintf(fdOutRefFile,"#Cartesian coordinates are in WGS84 datum\n#X, Y and Z are in metres\n");
					fprintf(fdOutRefFile,"Year DoY       SoD              X              Y              Z\n");
				}
			}
		}
	}

	// Initialise sigma from user options
	for ( i=0;i<MAX_SATELLITES_VIEWED;i++ ) {
		epoch->cycleslip.L1C1sigma[i] = pow(options.csL1C1init,2);
		if ( options.DGNSS == 1 ) epochDGNSS->cycleslip.L1C1sigma[i] = pow(options.csL1C1init, 2);
	}
	
	// Satellite Constellation Data
	// Priority is given to the ANTEX file
	if ( sopt.antFile[0] != '\0' ) { // ANTEX file
		if (printProgress==1) {	
			if (options.ProgressEndCharac=='\r') {
				//Printing to a terminal
				fprintf(options.terminalStream,"Reading ANTEX file%50s%c","",options.ProgressEndCharac);
				fflush(options.terminalStream);
			}
		}
		if ( readAntexFile(sopt.antFile,&constellation,&antennaList) != 1 ) {
			sprintf(messagestr,"Reading ANTEX file [%s]",sopt.antFile);
			printError(messagestr,&options);
		}
	} else if ( sopt.conFile[0] != '\0' ) { // Constellation Status file
		if ( readConstellationFile(sopt.conFile,&constellation) != 1 ) {
			sprintf(messagestr,"Reading constellation file [%s]",sopt.conFile);
			printError(messagestr,&options);
		}
	} 

	// Processing data
	if ( options.workMode == wmCOMPAREORBITS || options.workMode == wmSHOWPRODUCT ) {
		productsProcessing(&options,&sopt,&constellation);
	} else if ( options.workMode == wmDOPROCESSING || options.workMode == wmSHOWINPUT ) {
		if ( fdRNXnav != NULL ) {
			if (printProgress==1) {	
				if (options.ProgressEndCharac=='\r') {
					//Printing to a terminal
					fprintf(options.terminalStream,"Reading navigation file%50s%c","",options.ProgressEndCharac);
					fflush(options.terminalStream);
				}
			}
			ret=readRinexNav(fdRNXnav, &products,&rinexNavVersion);
			if ( ret < 1 ) {
				if ( (int)rinexNavVersion > 3 && rinexNavVersion != 0 ) {
					sprintf(messagestr,"RINEX navigation version %1.2f from file [%s] is not supported. Supported versions are 2 and 3",rinexNavVersion,sopt.navFile[0]);
					printError(messagestr,&options);
				} else {
					sprintf(messagestr,"Reading RINEX navigation message file [%s]",sopt.navFile[0]);
					printError(messagestr,&options);
				}
			} else if (ret==2) {
				nextNav=1;
			} else {
				nextNav=0;
				fclose(fdRNXnav);
				fdRNXnav=NULL;
			}
			// Set products end time
			if ( options.workMode == wmDOPROCESSING ) {
				startProductsTime = getProductsFirstEpoch(&products);
				endProductsTime = getProductsLastEpoch(&products);
			}
		}
		// SP3 with orbits and clocks
		if ( fdSP3 != NULL ) {
			if (printProgress==1) {	
				if (options.ProgressEndCharac=='\r') {
					//Printing to a terminal
					fprintf(options.terminalStream,"Reading SP3 file%50s%c","",options.ProgressEndCharac);
					fflush(options.terminalStream);
				}
			}
			ret = readSP3(fdSP3,&pastSP3Prod,1,1,0);
			//memcpy(&pastSP3Prod,&products,sizeof(TGNSSproducts));
			if ( ret == 2 ) { // Large SP3, so read next products
				options.concatenSP3 = 1;
				options.numPreciseFiles = 1;
				ret = readSP3(fdSP3,&products,1,1,0);
				if ( ret == 2 ) {
					options.NextSP3 = 1;
					options.concatenSP3 = 1;
					options.numPreciseFiles = 1;
					ret = readSP3(fdSP3,&nextSP3Prod,1,1,0);
					if ( ret == 2 ) {
						options.NextSP3 = 1;
						// Set products end time
						if ( options.workMode == wmDOPROCESSING ) {
							startProductsTime = getProductsFirstEpoch(&pastSP3Prod);
							endProductsTime = getProductsLastEpoch(&products);
						}
					} else if(ret == -2) {
						sprintf(messagestr, "SP3 orbit and clock products file [%s] has incorrect number of entries in header", sopt.SP3File[0]);
						printError(messagestr, &options);
					} else {
						options.NextSP3 = 0;
						// Set products end time
						if ( options.workMode == wmDOPROCESSING ) {
							startProductsTime = getProductsFirstEpoch(&pastSP3Prod);
							endProductsTime = getProductsLastEpoch(&nextSP3Prod);
						}
					}
				} else {
					memcpy(&nextSP3Prod,&products,sizeof(TGNSSproducts));
					options.NextSP3 = 0;
					// Set products end time
					if ( options.workMode == wmDOPROCESSING ) {
						startProductsTime = getProductsFirstEpoch(&pastSP3Prod);
						endProductsTime = getProductsLastEpoch(&products);
					}
				}
			} else if ( ret < 1 ) {
				if(ret==-2) {
					sprintf(messagestr, "SP3 orbit and clock products file [%s] has incorrect number of entries in header", sopt.SP3File[0]);
					printError(messagestr, &options);
				} else {
					sprintf(messagestr,"Reading SP3 orbit and clock products file [%s]",sopt.SP3File[0]);
					printError(messagestr,&options);
				}
			} else {
				options.NextSP3 = 0;
				memcpy(&products,&pastSP3Prod,sizeof(TGNSSproducts));
				memcpy(&nextSP3Prod,&products,sizeof(TGNSSproducts));
				// Set products end time
				if ( options.workMode == wmDOPROCESSING ) {
					startProductsTime = getProductsFirstEpoch(&pastSP3Prod);
					endProductsTime = getProductsLastEpoch(&pastSP3Prod);
				}
			}

		}
		// SP3 and CLK
		if ( fdSP3o != NULL && fdCLK != NULL ) {
			if (printProgress==1) {	
				if (options.ProgressEndCharac=='\r') {
					//Printing to a terminal
					fprintf(options.terminalStream,"Reading SP3 file%50s%c","",options.ProgressEndCharac);
					fflush(options.terminalStream);
				}
			}
			ret1 = readSP3(fdSP3o,&pastSP3Prod,1,0,0);
			if ( ret1 < 1 ) {
				if(ret1==-2) {
					sprintf(messagestr, "SP3 orbit product file [%s] has incorrect number of entries in header", sopt.orbFile[0]);
					printError(messagestr, &options);
				} else {
					sprintf(messagestr,"Reading SP3 orbit product file [%s]",sopt.orbFile[0]);
					printError(messagestr,&options);
				}
			}
			if (printProgress==1) {	
				if (options.ProgressEndCharac=='\r') {
					//Printing to a terminal
					fprintf(options.terminalStream,"Reading precise clocks file%50s%c","",options.ProgressEndCharac);
					fflush(options.terminalStream);
				}
			}
			ret2 = readRinexClocks(fdCLK,&pastSP3Prod);
			if ( ret2 < 1 ) {
				sprintf(messagestr,"Reading clock products file [%s]",sopt.clkFile[0]);
				printError(messagestr,&options);
			}
			if ( ret1 == 2 && ret2 ==2 ) { // Large SP3 and clocks, so read next products
				options.concatenSP3 = 1;
				options.numPreciseFiles = 2;
				ret1 = readSP3(fdSP3o,&products,1,0,0);
				ret2 = readRinexClocks(fdCLK,&products);
				if(ret1==-2) {
					sprintf(messagestr, "SP3 orbit product file [%s] has incorrect number of entries in header", sopt.orbFile[0]);
					printError(messagestr, &options);
				} else if ( ret1 == 2 && ret2 == 2 ) {
					options.NextSP3 = 1;
					ret1 = readSP3(fdSP3o,&nextSP3Prod,1,0,0);
					ret2 = readRinexClocks(fdCLK,&nextSP3Prod);
					if(ret1==-2) {
						sprintf(messagestr, "SP3 orbit product file [%s] has incorrect number of entries in header", sopt.orbFile[0]);
						printError(messagestr, &options);
					} else if (ret1==2 && ret2==2) {
						options.NextSP3 = 1;
						// Set products end time
						if ( options.workMode == wmDOPROCESSING ) {
							startProductsTime = getProductsFirstEpoch(&pastSP3Prod);
							endProductsTime = getProductsLastEpoch(&products);
						}
					} else {
						options.NextSP3 = 0;
						// Set products end time
						if ( options.workMode == wmDOPROCESSING ) {
							startProductsTime = getProductsFirstEpoch(&pastSP3Prod);
							endProductsTime = getProductsLastEpoch(&nextSP3Prod);
						}
					}
				} else {
					options.NextSP3 = 0;	
					memcpy(&nextSP3Prod,&products,sizeof(TGNSSproducts));
					// Set products end time
					if ( options.workMode == wmDOPROCESSING ) {
						startProductsTime = getProductsFirstEpoch(&pastSP3Prod);
						endProductsTime = getProductsLastEpoch(&nextSP3Prod);
					}
				}
				if(ret2 < 1 ) {
					options.NextSP3 = 0;	
					sprintf(messagestr,"Reading clock products file [%s]",sopt.clkFile[0]);
					printError(messagestr,&options);
				}
			} else if ( ret1 == 2 ) {
				//Only SP3 concatenated
				options.concatenSP3 = 1;
				ret1 = readSP3(fdSP3o,&products,1,0,0);
				if(ret1==-2) {
					sprintf(messagestr, "SP3 orbit product file [%s] has incorrect number of entries in header", sopt.orbFile[0]);
					printError(messagestr, &options);
				} else if (ret1==2) {
					ret1 = readSP3(fdSP3o,&nextSP3Prod,1,0,0);
					if(ret1==-2) {
						sprintf(messagestr, "SP3 orbit product file [%s] has incorrect number of entries in header", sopt.orbFile[0]);
						printError(messagestr, &options);
					}
				} else {
					memcpy(&nextSP3Prod.SP3->orbits,&products.SP3->orbits,sizeof(TSP3orbits));
				}
				printInfo("WARNING: SP3 orbit file is concatenated, but CLK file is not. Assuming it is to avoid Runge-Kutta interpolation effect for a single day observation file",&options);
				options.NextSP3 = 0;	
				memcpy(&products.SP3->clocks,&pastSP3Prod.SP3->clocks,sizeof(TSP3clocks));
				memcpy(&nextSP3Prod.SP3->clocks,&products.SP3->clocks,sizeof(TSP3clocks));
				// Set products end time
				if ( options.workMode == wmDOPROCESSING ) {
					startProductsTime = getProductsFirstEpoch(&products);
					endProductsTime = getProductsLastEpoch(&products);
				}
			} else {
				if ( ret2 ==2 ) {
					printError("Clock file is concatenated, but SP3 file is not. Both files must be concatenated or at least the SP3 file",&options);
				}
				options.NextSP3 = 0;
				memcpy(&products,&pastSP3Prod,sizeof(TGNSSproducts));
				memcpy(&nextSP3Prod,&products,sizeof(TGNSSproducts));
				// Set products end time
				if ( options.workMode == wmDOPROCESSING ) {
					startProductsTime = getProductsFirstEpoch(&pastSP3Prod);
					endProductsTime = getProductsLastEpoch(&nextSP3Prod);
				}
			}
		}

		//Concatenate SP3 and clocks
		if( fdSP3 != NULL || (fdSP3o != NULL && fdCLK != NULL)) {
			ConcatenateSP3(0,&products,&pastSP3Prod,&nextSP3Prod,&options);	

			//Compute Max total distance between interpolation samples for orbits
			if(options.OrbitsMaxGaps==-1) {
				options.OrbitsMaxGaps=8;
			} 
			if(options.OrbitsMaxGaps!=0 && options.orbitInterpolationDegree!=0) {
				options.OrbitsMaxDistance=(double)(options.OrbitsMaxGaps*products.SP3->orbits.interval);
			} else {
				options.OrbitsMaxDistance=0.;
			}

			//Compute Max total distance between first and last interpolation samples for orbits
			if(options.OrbitsToTMaxGaps==-1) {
				options.OrbitsToTMaxGaps=16;
			}
			if (options.OrbitsToTMaxGaps!=0) {
				options.OrbitsToTMaxDistance=(double)(options.orbitInterpolationDegree*products.SP3->orbits.interval+options.OrbitsToTMaxGaps*products.SP3->orbits.interval);
			} else {
				options.OrbitsToTMaxDistance=0.;
			}

			//Compute Max total distance between interpolation samples for clocks
			if(options.ClocksMaxGaps==-1) {
				options.ClocksMaxGaps=4;
			} 
			if(options.ClocksMaxGaps!=0) {
				options.ClocksMaxDistance=(double)(options.ClocksMaxGaps*products.SP3->clocks.interval);
			} else {
				options.ClocksMaxDistance=0.;
			}

			//Compute Max total distance between first and last interpolation samples for clocks
			if(options.ClocksToTMaxGaps==-1) {
				options.ClocksToTMaxGaps=8;
			}
			if(options.ClocksToTMaxGaps!=0 && options.clockInterpolationDegree!=0) {
				options.ClocksToTMaxDistance=(double)(options.clockInterpolationDegree*products.SP3->clocks.interval+options.ClocksToTMaxGaps*products.SP3->clocks.interval);
			} else {
				options.ClocksToTMaxDistance=0.;
			}

			if(options.OrbitsToTMaxGaps<options.OrbitsMaxGaps) {
				sprintf(messagestr,"Maximum total number of data gaps in orbit interpolation given (%d) has to be equal or greater than the maximum number of data gaps between samples (%d)",options.OrbitsToTMaxGaps,options.OrbitsMaxGaps);
				printError(messagestr,&options);
			}
		}

		if(options.ClocksToTMaxGaps<options.ClocksMaxGaps && options.clockInterpolationDegree!=0) {
			sprintf(messagestr,"Maximum total number of data gaps in clock interpolation given (%d) has to be equal or greater than the maximum number of data gaps between samples (%d)",options.ClocksToTMaxGaps,options.ClocksMaxGaps);
			printError(messagestr,&options);
		}

		if(options.filterIterations==2 && (options.concatenSP3==1||nextNav==1)) {
			printError("Concatening product files is incompatible with backward processing",&options);
		}

		if ( options.useraddednoise == 1 ) {
			if ( sopt.addederrorFile[0] == '\0' ) {
				printError("User added error option selected, but no filename given",&options);
			}
			fdNoise = fopen(sopt.addederrorFile,"rb");
			if ( fdNoise == NULL ) {
				sprintf(messagestr,"Reading file [%s] for user added error to measurements",sopt.addederrorFile);
				printError(messagestr,&options);
			}
			if (options.useraddednoisepreprocess==1) {
				options.useraddednoise = 2;
			}
		}

		// Ionosphere data
		if ( options.ionoModel == IONEX ) {
			if ( fdIONEX != NULL ) {
				if (printProgress==1) {	
					if (options.ProgressEndCharac=='\r') {
						//Printing to a terminal
						fprintf(options.terminalStream,"Reading IONEX file%50s%c","",options.ProgressEndCharac);
						fflush(options.terminalStream);
					}
				}
				ret = readIONEX(fdIONEX,&ionex,&ionexVersion);
				if ( ret < 1 ) {
					if ( (int)ionexVersion != 1 && ionexVersion != 0 ) {
						sprintf(messagestr,"IONEX version %1.2f from file [%s] is not supported. Supported version is 1",ionexVersion,sopt.inxFile);
						printError(messagestr,&options);
					} else if (ret==-2) {
						sprintf(messagestr,"Number of records in IONEX header in file [%s] does not match the number of records read",sopt.inxFile);
						printError(messagestr,&options);
					} else if (ret==-3) {
						sprintf(messagestr,"IONEX header in file [%s] is incorrect or there are missing records",sopt.inxFile);
						printError(messagestr,&options);
					} else {
						sprintf(messagestr,"Reading IONEX file [%s] for ionospheric data" ,sopt.inxFile);
						printError(messagestr,&options);
					}
				} else if ( ret == 2 ) {
					sprintf(messagestr,"WARNING: IONEX file [%s] has no 'END OF FILE' line. File may not be complete",sopt.inxFile);
					printInfo(messagestr,&options);
					fclose(fdIONEX);
					fdIONEX=NULL;
				} else if ( ret == 4 ) {
					sprintf(messagestr,"WARNING: IONEX file [%s] is concatenated, but has no 'END OF FILE' line. File may not be complete",sopt.inxFile);
					printInfo(messagestr,&options);
				} else if ( ret != 3 ) {
					fclose(fdIONEX);
					fdIONEX=NULL;
				}
				
				// If there is no RMS data in IONEX file, do not use this data even though it is indicated in gLAB parameters.
				if ( ionex.RMSavailable == 0 ) {
					if (options.useSigmaIono ==1) {
						sprintf(messagestr,"WARNING: IONEX file [%s] has no RMS values. Disconnecting sigma iono in filter",sopt.inxFile);
						printInfo(messagestr,&options);
						options.useSigmaIono = 0;
					}
				}
			}
		} else if ( options.ionoModel == FPPP ) {
			if ( sopt.fppFile[0] != '\0' ) {
				if ( readFPPPFile(sopt.fppFile,&fppp,&fpppVersion) != 1 ) {
					if ( (int)fpppVersion != 1 && fpppVersion != 0 ) {
						sprintf(messagestr,"FPPP version %1.2f from file [%s] is not supported. Supported version is 1",fpppVersion,sopt.fppFile);
						printError(messagestr,&options);
					} else {
						sprintf(messagestr,"Reading FPPP file [%s] for ionospheric data",sopt.fppFile);
						printError(messagestr,&options);
					}
				}
			}
		} else if ( options.ionoModel == Klobuchar ) {
			if ( fdRNXKlb != NULL ) {
				if (printProgress==1) {	
					if (options.ProgressEndCharac=='\r') {
						//Printing to a terminal
						fprintf(options.terminalStream,"Reading navigation file for Klobuchar%50s%c","",options.ProgressEndCharac);
						fflush(options.terminalStream);
					}
				}
				ret=readRinexNav(fdRNXKlb,&productsKlb,&rinexNavVersion);
				if ( ret < 1 ) {
					if ( (int)rinexNavVersion > 3 && rinexNavVersion != 0 ) {
						sprintf(messagestr,"RINEX navigation version %1.2f from file [%s] is not supported. Supported versions are 2 and 3",rinexNavVersion,sopt.klbFile);
						printError(messagestr,&options);
					} else {
						sprintf(messagestr,"Reading RINEX navigation message file [%s] for Klobuchar data",sopt.klbFile);
						printError(messagestr,&options);
					}
				} else if (ret!=2) {
					fclose(fdRNXKlb);
					fdRNXKlb=NULL;
				}
			} else if ( products.type == BRDC ) {
				productsKlb.BRDC = products.BRDC;
			} else {
				printError("Klobuchar model selected for ionospheric corrections, but no source is found",&options);
			}
		} else if ( options.ionoModel == BeiDou ) {
			if ( fdRNXBei != NULL ) {
				if (printProgress==1) {	
					if (options.ProgressEndCharac=='\r') {
						//Printing to a terminal
						fprintf(options.terminalStream,"Reading navigation file for BeiDou%50s%c","",options.ProgressEndCharac);
						fflush(options.terminalStream);
					}
				}
				ret=readRinexNav(fdRNXBei,&productsBei,&rinexNavVersion);
				if ( ret < 1 ) {
					if ( (int)rinexNavVersion > 3 && rinexNavVersion != 0 ) {
						sprintf(messagestr,"RINEX navigation version %1.2f from file [%s] is not supported. Supported versions are 2 and 3",rinexNavVersion,sopt.beiFile);
						printError(messagestr,&options);
					} else {
						sprintf(messagestr,"Reading RINEX navigation message file [%s] for BeiDou data",sopt.beiFile);
						printError(messagestr,&options);
					}
				} else if (ret!=2) {
					fclose(fdRNXBei);
					fdRNXBei=NULL;
				}
			} else if ( products.type == BRDC ) {
				productsBei.BRDC = products.BRDC;
			} else {
				printError("BeiDou model selected for ionospheric corrections, but no source is found",&options);
			}

		} else if ( options.ionoModel == neQuick ) {
			if ( fdRNXNeq != NULL ) {
				if (printProgress==1) {	
					if (options.ProgressEndCharac=='\r') {
						//Printing to a terminal
						fprintf(options.terminalStream,"Reading navigation file for NeQuick%50s%c","",options.ProgressEndCharac);
						fflush(options.terminalStream);
					}
				}
				ret=readRinexNav(fdRNXNeq,&productsNeq,&rinexNavVersion);
					if ( ret < 1 ) {
						if ( (int)rinexNavVersion > 3 && rinexNavVersion != 0 ) {
							sprintf(messagestr,"RINEX navigation version %1.2f from file [%s] is not supported. Supported versions are 2 and 3",rinexNavVersion,sopt.neqFile);
							printError(messagestr,&options);
						} else {
							sprintf(messagestr,"Reading RINEX navigation message file [%s] for NeQuick data",sopt.neqFile);
							printError(messagestr,&options);
						}
					} else if ( (int)rinexNavVersion < 3 ) {
						sprintf(messagestr,"RINEX navigation version %1.2f from file [%s] is below 3. This version does not contain NeQuick data",rinexNavVersion,sopt.neqFile);
						printError(messagestr,&options);
					} else if (ret!=2) {
						fclose(fdRNXNeq);
						fdRNXNeq=NULL;
					}
				} else if ( products.type == BRDC && (int)rinexNavVersion < 3 ) {
					sprintf(messagestr,"RINEX navigation version %1.2f from file [%s] is below 3. This version does not contain NeQuick data",rinexNavVersion,sopt.navFile[0]);
					printError(messagestr,&options);
				} else if ( products.type == BRDC ) {
					productsNeq.BRDC = products.BRDC;
				} else {
					printError("NeQuick model selected for ionospheric corrections, but no source is found",&options);
				}
		} else if ( options.ionoModel == SBASiono ) {
			// If we are processing with SBAS, we need to copy Klobuchar parameters to its structure
			if (products.BRDC==NULL) {
				//If we have not read any product type, allocate memory and initialize to 0 the productsKlb structure
				productsKlb.BRDC = malloc(sizeof(TBRDCproducts));
				initBRDCproducts(productsKlb.BRDC);
			} else {
				productsKlb.BRDC = products.BRDC;
			}
		}

		// Troposphere data, only in case Galielo model is selected
		if ( options.tropNominal == TropoGalileo ) {
			if ( readGalileoTroposphericData(&tropoGal,sopt.GalFile,&options) != 1 ) {
				sprintf(messagestr,"Reading Galileo Tropospheric data file [%s]",sopt.GalFile);
				printError(messagestr,&options);
			}
		}

		// TGD file management
		initTGD(&tgdData,options.p1c1dcbModel,options.p1p2dcbModel);
		if ( options.p1c1dcbModel == p1c1STRICT ) {
			if ( sopt.numP1C1DCB == 0 ) {
				printError("No P1-C1 DCB file provided, but P1-C1 model set to strict",&options);
			}
			if ( sopt.recFile[0] == '\0' && sopt.setRecType == rtNA ) {
				printError("No 'GPS_Receiver_Types' file provided or no receiver set by the user, but P1-C1 model set to strict. Include a 'GPS_Receiver_Types' with '-input:rec' or set a receiver type with '-pre:setrectype'",&options);
			}
		}
		
		if ( options.p1p2dcbModel == p1p2RINEX ) {
			if ( sopt.numP1P2RINEX == 0 ) {
				if ( products.type != BRDC ) {
					printError("Navigation message is selected for P1-P2 DCB corrections, but no source is found, include it with '-input:dcb'",&options);
				} else {
					tgdData.BRDC = products.BRDC;
				}
			}
		} else if ( options.p1p2dcbModel == p1p2DCB ) {
			if ( sopt.numP1P2DCB == 0 ) {
				printError("No P1-P2 DCB file provided, but P1-P2 model set to DCB",&options);
			}

		} else if ( options.p1p2dcbModel == p1p2IONEX ) {
			if ( sopt.numP1P2IONEX == 0 ) {
				if(sopt.inxFile[0] != '\0' && options.ionoModel == IONEX) {
					if(ionex.ionexDCB.DCBavailable==0) {
						sprintf(messagestr,"IONEX file [%s] selected for P1-P2 DCB corrections, but no DCB data was found in the file",sopt.inxFile);
						printError(messagestr,&options);
					} else {
						tgdData.ionexDCB = ionex.ionexDCB;
					}
				} else {
					printError("No IONEX file provided, but P1-P2 model set to IONEX",&options);
				}
			}
		} else if ( options.p1p2dcbModel == p1p2FPPP ) {
			if ( sopt.numP1P2FPPP == 0 ) {
				if(sopt.fppFile[0] != '\0' && options.ionoModel == FPPP) {
					if(fppp.fpppDCB.DCBavailable==0) {
						sprintf(messagestr,"FPPP file [%s] selected for P1-P2 DCB corrections, but no DCB data was found in the file",sopt.fppFile);
						printError(messagestr,&options);
					} else {
						tgdData.fpppDCB = fppp.fpppDCB;
					}
				} else {
					printError("No FPPP file provided, but P1-P2 model set to FPPP",&options);
				}
			}
		}			
		
		for (i=0;i<sopt.numTGD;i++) {
			auxft1 = whatFileTypeIs(sopt.tgdFile[i]);
			if ( (auxft1 == ftP1C1DCB && options.p1c1dcbModel == p1c1STRICT) || (auxft1 == ftP1P2DCB && options.p1p2dcbModel == p1p2DCB) ) {
				//DCB files for GPS only
				if (printProgress==1) {	
					if (options.ProgressEndCharac=='\r') {
						//Printing to a terminal
						fprintf(options.terminalStream,"Reading GPS DCB file%50s%c","",options.ProgressEndCharac);
						fflush(options.terminalStream);
					}
				}
				retTGD[i]=readDCBFile(sopt.tgdFile[i],tgdData.DCB);
				if ( retTGD[i] != 1 ) {
					if (retTGD[i]==-2) {
						sprintf(messagestr,"DCB file [%s] header not recognized. It may be due to an unsupported DCB file type, or for P1-C1 and P1-P2 files, because the header line has changed its format",sopt.tgdFile[i]);
						printError(messagestr,&options);
					} else {
						sprintf(messagestr,"Reading DCB file for TGD data [%s]",sopt.tgdFile[i]);
						printError(messagestr,&options);
					}
				}
			} else if ( auxft1 == ftRINEXbroadcast && options.p1p2dcbModel == p1p2RINEX ) {
				if (strcmp(sopt.tgdFile[i],sopt.navFile[0])!=0) {
					if (printProgress==1) {	
						if (options.ProgressEndCharac=='\r') {
							//Printing to a terminal
							fprintf(options.terminalStream,"Reading navigation file for DCB%50s%c","",options.ProgressEndCharac);
							fflush(options.terminalStream);
						}
					}
					if(!(fdTGD[i]=fopen(sopt.tgdFile[i],"rb"))) {
						sprintf(messagestr,"Reading RINEX navigation message file for TGD data [%s]",sopt.tgdFile[i]);
						printError(messagestr,&options);
					} else {
						retTGD[i]=readRinexNav(fdTGD[i],&productsTgd,&rinexNavVersion);
						if ( retTGD[i]<1 ) {
							if ( (int)rinexNavVersion > 3 && rinexNavVersion != 0 ) {
								sprintf(messagestr,"RINEX navigation version %1.2f from file [%s] is not supported. Supported versions are 2 and 3",rinexNavVersion,sopt.tgdFile[i]); 	
								printError(messagestr,&options);
							} else {
								sprintf(messagestr,"Reading RINEX navigation message file for TGD data [%s]",sopt.tgdFile[i]);
								printError(messagestr,&options);
							}
						} else if (retTGD[i]!=2) {
							fclose(fdTGD[i]);
							fdTGD[i]=NULL;
						}
					}
					tgdData.BRDC = productsTgd.BRDC;
				} else {
					tgdData.BRDC = products.BRDC;
				}
			} else if ( auxft1 == ftIONEX && options.p1p2dcbModel == p1p2IONEX ) {
				if (printProgress==1) {	
					if (options.ProgressEndCharac=='\r') {
						//Printing to a terminal
						fprintf(options.terminalStream,"Reading IONEX for DCB%50s%c","",options.ProgressEndCharac);
						fflush(options.terminalStream);
					}
				}
				if(!(fdTGD[i]=fopen(sopt.tgdFile[i],"rb"))) {
					sprintf(messagestr,"Reading IONEX file for TGD data [%s]",sopt.tgdFile[i]);
					printError(messagestr,&options);
				} else {
					retTGD[i]=readIONEX(fdTGD[i],&productsIonex,&ionexVersion);
					if ( retTGD[i] < 1 ) {
						if ((int)ionexVersion!=1 && ionexVersion!=0){
							sprintf(messagestr,"IONEX version %1.2f from file [%s] is not supported. Supported version is 1",ionexVersion,sopt.tgdFile[i]);
							printError(messagestr,&options);
						} else if (retTGD[i]==-2) {
							sprintf(messagestr,"Number of records in IONEX header in file [%s] does not match the number of records read",sopt.tgdFile[i]);
							printError(messagestr,&options);
						} else {
							sprintf(messagestr,"Reading IONEX file [%s] for DCB data" ,sopt.tgdFile[i]);
							printError(messagestr,&options);
						}
					} else if ( productsIonex.ionexDCB.DCBavailable == 0 ) {
						sprintf(messagestr,"IONEX file [%s] selected for P1-P2 DCB corrections, but no DCB data was found in the file",sopt.tgdFile[i]);
						printError(messagestr,&options);
					} else {
						tgdData.ionexDCB = productsIonex.ionexDCB;
						if ( retTGD[i] == 2 ) {
							sprintf(messagestr,"WARNING: IONEX file [%s] for DCB data has no 'END OF FILE' line. File may not be complete",sopt.tgdFile[i]);
							printInfo(messagestr,&options);
						} else if ( retTGD[i] == 4 ) {
							sprintf(messagestr,"WARNING: IONEX file [%s] for DCB data is concatenated, but has no 'END OF FILE' line. File may not be complete",sopt.tgdFile[i]);
							printInfo(messagestr,&options);
						} else {
							fclose(fdTGD[i]);
							fdTGD[i]=NULL;
						}
					}
				}
			} else if ( auxft1 == ftFPPP && options.p1p2dcbModel == p1p2FPPP ) {
				if ( readFPPPFile(sopt.tgdFile[i],&productsFppp,&fpppVersion) != 1 ) {
					if ( (int)fpppVersion != 1 && fpppVersion != 0 ) {
						sprintf(messagestr,"FPPP version %1.2f from file [%s] is not supported. Supported version is 1",fpppVersion,sopt.tgdFile[i]);
						printError(messagestr,&options);
					} else {
						sprintf(messagestr,"Reading FPPP file [%s] for DCB data" ,sopt.tgdFile[i]);
						printError(messagestr,&options);
					}
				} else if ( productsFppp.fpppDCB.DCBavailable == 0 ) {
					sprintf(messagestr,"FPPP file [%s] selected for P1-P2 DCB corrections, but no data was found in the file",sopt.tgdFile[i]);
					printError(messagestr,&options);
				} else {
					tgdData.fpppDCB = productsFppp.fpppDCB;
				}
			}

		}

		// GPS Receiver type file
		if ( sopt.recFile[0] != '\0' ) {
			if ( sopt.setRecType == rtNA ) {
				if (printProgress==1) {	
					if (options.ProgressEndCharac=='\r') {
						//Printing to a terminal
						fprintf(options.terminalStream,"Reading receiver type file%50s%c","",options.ProgressEndCharac);
						fflush(options.terminalStream);
					}
				}
				if ( readRecTypeFile(sopt.recFile,&recList) != 1 ) {
					sprintf(messagestr,"Reading GPS Receiver type file [%s]",sopt.recFile);
					printError(messagestr,&options);
				}
			} else {
				sprintf(messagestr,"WARNING setrectype specified, ignoring GPS receiver types file (%s)",sopt.recFile);
				printInfo(messagestr,&options);
			}
		}
		
		// SINEX file
		if ( sopt.snxFile[0] != '\0' ) {
			if (printProgress==1) {	
				if (options.ProgressEndCharac=='\r') {
					//Printing to a terminal
					fprintf(options.terminalStream,"Reading SINEX file%50s%c","",options.ProgressEndCharac);
					fflush(options.terminalStream);
				}
			}
			if (readSINEXFile(sopt.snxFile,&stationList)!=1) {
				sprintf(messagestr,"Reading SINEX input file [%s]",sopt.snxFile);
				printError(messagestr,&options);
			}
		}
		
		// If receiver antenna phase centre is set, dump it to the antenna structure
		if ( options.antennaData == adSET ) {
			options.receiverPhaseVar = 0;
			for (j=0;j<MAX_FREQUENCIES_PER_GNSS;j++) {
				for (i=0;i<3;i++) {
					epoch->receiver.antenna.PCO[j][i] = options.receiverPCO[j][i];
				}
			}
		}
		
		// If receiver antenna reference point is set, dump it to the receiver structure
		if ( options.ARPData == arpSET ) {
			for (i=0;i<3;i++) {
				epoch->receiver.ARP[i] = options.receiverARP[i];
			}
		}
				
		// Read RINEX Observation header
		ret = readRinexObsHeader(fdRNX,NULL,epoch,&options);
		if (printProgress==1) {	
			if (options.ProgressEndCharac=='\r') {
				//Printing to a terminal
				fprintf(options.terminalStream,"Reading rover observation header file%50s%c","",options.ProgressEndCharac);
				fflush(options.terminalStream);
			}
		}
		if ( options.DGNSS == 1 ) {
			if ( options.RTCMmode == ProcessRTCM3 ) {
				// Process the binary RTCM v3.x
				ret = converterRTCM3(fdRTCM3,rtcm3,fileRINEXpointer,epoch,epochDGNSS,&options);
			} else if ( options.RTCMmode == ProcessRINEX ) {
				// Read the RINEX header
				ret = readRinexObsHeader(fdRNXdgnss,NULL,epochDGNSS,&options);
				if (printProgress==1) {	
					if (options.ProgressEndCharac=='\r') {
						//Printing to a terminal
						fprintf(options.terminalStream,"Reading reference observation header file%50s%c","",options.ProgressEndCharac);
						fflush(options.terminalStream);
					}
				}
				if ( options.receiverPositionSource >= rpRTCMbaseline ) {
					for ( i = 0; i < 3; i++ ) epoch->receiver.aproxPosition[i] = epochDGNSS->receiver.aproxPosition[i];
				}
				epoch->receiver.numRecStation=epochDGNSS->receiver.numRecStation;
				epoch->receiver.RecStationCoord=epochDGNSS->receiver.RecStationCoord;
				epoch->receiver.ChangedStaEpoch=epochDGNSS->receiver.ChangedStaEpoch;
			}
		}
		

		// If position receiver is set, dump it to the receiver structure 
		if ( options.receiverPositionSource == rpSET || options.receiverPositionSource == rpCALCULATEUSER || options.receiverPositionSource == rpCALCULATEUSERREF ) {
			for (i=0;i<3;i++) {
				epoch->receiver.aproxPosition[i] = options.aprioriReceiverPosition[i];
			}
			epoch->receiver.aproxPositionError = 1e4; // 10 Km
		} else if ( options.receiverPositionSource == rpSINEX ) { // If the position is read from SINEX, get it
			station = getStation(epoch->receiver.name,&stationList);
			if ( station == NULL ) {
				sprintf(messagestr,"Receiver marker name '%s' not found in SINEX file [%s]. Use '-pre:setrecpos x y z' to set it",epoch->receiver.name,sopt.snxFile);
				printError(messagestr,&options);
			} else {
				for (i=0;i<3;i++) {
					epoch->receiver.aproxPosition[i] = station->pos[i];
				}
				epoch->receiver.aproxPositionError = 0.01; // 1 cm
			}
		} else if ( options.receiverPositionSource == rpRTCMRoverUSER ) {
			for (i=0;i<3;i++) {
				epoch->receiver.aproxPositionRover[i] = options.aprioriReceiverPosition[i];
				epoch->receiver.aproxPosition[i] = options.aprioriReceiverPosition[i];
			}
		} else if ( options.receiverPositionSource == rpRTCMUserbaseline ) {
			for (i=0;i<3;i++) {
				epochDGNSS->receiver.aproxPosition[i] = options.ReferenceStationPosition[i];
				epoch->receiver.aproxPosition[i] = options.ReferenceStationPosition[i];
			}
		} else if ( options.receiverPositionSource == rpRTCMUserRINEXROVER ) {
			for (i=0;i<3;i++) {
				epochDGNSS->receiver.aproxPosition[i] = options.ReferenceStationPosition[i];
			}
		} else if (options.receiverPositionSource == rpRTCMRefRoverUSER ) {
			for (i=0;i<3;i++) {
				epoch->receiver.aproxPositionRover[i] = options.aprioriReceiverPosition[i];
				epochDGNSS->receiver.aproxPosition[i] = options.ReferenceStationPosition[i];
				epoch->receiver.aproxPosition[i] = options.aprioriReceiverPosition[i];
			}
		} else if ( options.receiverPositionSource == rpRTCMRefUSERRoverREF ) {
			for (i=0;i<3;i++) {
				epochDGNSS->receiver.aproxPosition[i] = options.ReferenceStationPosition[i];
			}
		}
		if (options.workMode == wmDOPROCESSING) {
			//Only read reference file if we are in processing mode
			if ( options.receiverPositionSource == rpSETREF || options.receiverPositionSource == rpCALCULATEREF || options.receiverPositionSource == rpCALCULATERINEXREF 
					|| options.receiverPositionSource == rpCALCULATEUSERREF ||  options.receiverPositionSource == rpRTCMRoverUSERREF ||  options.receiverPositionSource == rpRTCMRefUSERRoverREF) {
				//Rover position read by reference file
				UseReferenceFile=1;
				OrbInterpDegree=options.orbitInterpolationDegree;
				epoch->receiver.aproxPositionError = 0.1; // 10 cm
				if (sopt.posReferenceFile[0]=='\0') {
					printError("Receiver position set to be read from reference file, but no reference file given. Use option '-input:refpos' to set one.",&options);
				}
				if (printProgress==1) {	
					if (options.ProgressEndCharac=='\r') {
						//Printing to a terminal
						fprintf(options.terminalStream,"Reading reference position file%50s%c","",options.ProgressEndCharac);
						fflush(options.terminalStream);
					}
				}
				ret = readReferenceFile(sopt.posReferenceFile,&ReferencePos,&options);
				if (ret == -1) {
					sprintf(messagestr,"Opening reference file [%s]",sopt.posReferenceFile);
					printError(messagestr,&options);
				} else if (ret ==-2) {
					sprintf(messagestr,"Reference file [%s] must be a SP3 file or a columnar text file. See option '-referenceposfile' for help on the columnar text file format",sopt.posReferenceFile);
					printError(messagestr,&options);
				} else if (ret ==-3) {
					sprintf(messagestr,"Reference SP3 file [%s] has an incorrect number of entries in the header",sopt.posReferenceFile);
					printError(messagestr,&options);
				} else if (ret ==-4) {
					sprintf(messagestr,"Reference SP3 file [%s] cannot be concatenated. Data may be from several days, but it must contain only one header",sopt.posReferenceFile);
					printError(messagestr,&options);
				} else if (ret ==-5) {
					sprintf(messagestr,"Reference SP3 file [%s] cannot contain more than one satellite",sopt.posReferenceFile);
					printError(messagestr,&options);
				} else if (ret ==-6) {
					sprintf(messagestr,"Reading reference SP3 file [%s]",sopt.posReferenceFile);
					printError(messagestr,&options);
				}
			}
		}
		if (options.receiverPositionSource == rpRTCMRINEXROVER || options.receiverPositionSource == rpRTCMUserRINEXROVER ) {
			//Use Rover Rinex position as a priori
			for (i=0;i<3;i++) {
				epoch->receiver.aproxPosition[i] = epoch->receiver.aproxPositionRover[i];
			}
		}
		if ( options.receiverPositionSource >= rpCALCULATE && options.receiverPositionSource < rpCALCULATEREF ) {
			//Set OUTPUT differential fields to 0
			epoch->receiver.RefPositionAvail=0;
		}
		if ( options.receiverPositionSource >= rpCALCULATE && options.receiverPositionSource <= rpCALCULATEUSERREF ) {
			//When coordinates are set to calculate, do not believe any coordinate, even if it is from user or RINEX file
			//Setting a error higher than 1e5 makes gLAB not discard satellites by elevation
			epoch->receiver.aproxPositionError = 1e10; 
		}
		//Set differential OUTPUT fields computation mode
		if ( options.receiverPositionSource == rpRTCMbaseline || options.receiverPositionSource == rpRTCMUserbaseline ) {
			epoch->receiver.OUTPUTDiffFieldsMode=RTCMBaseline;
		} else if ( options.receiverPositionSource == rpCALCULATEREF || options.receiverPositionSource == rpCALCULATERINEXREF || options.receiverPositionSource == rpCALCULATEUSERREF) {
			epoch->receiver.OUTPUTDiffFieldsMode=CalculateWithRefFile;
		} else if ( options.receiverPositionSource >= rpRTCMRINEXROVER && options.receiverPositionSource != rpRTCMUserbaseline ) {	
			epoch->receiver.OUTPUTDiffFieldsMode=RTCMNoBaseline;
		} else {
			epoch->receiver.OUTPUTDiffFieldsMode=FromAPriori;
		}
		
		// Abnormal a priori receiver position
		// Check if station is at least above than -1 km from the earth surface 
		if ( options.workMode != wmSHOWINPUT ) {
			if ( options.receiverPositionSource <= rpSET) {
				r = sqrt(epoch->receiver.aproxPosition[0]*epoch->receiver.aproxPosition[0] + 
						 epoch->receiver.aproxPosition[1]*epoch->receiver.aproxPosition[1] + 
						 epoch->receiver.aproxPosition[2]*epoch->receiver.aproxPosition[2]);
				if ( r < (MIN_EARTH_RADIUS-1000.) ) {
					sprintf(messagestr,"Receiver a priori position must be above Earth surface (%.2f vs %.2f).",r,MIN_EARTH_RADIUS-1000.0);
					printError(messagestr,&options);
				} 
			} else if ( options.receiverPositionSource >= rpRTCMRINEXROVER && options.receiverPositionSource != rpRTCMUserbaseline && options.receiverPositionSource != rpRTCMRoverUSERREF && options.receiverPositionSource != rpRTCMRefUSERRoverREF) {
				r = sqrt(epoch->receiver.aproxPositionRover[0]*epoch->receiver.aproxPositionRover[0] + 
						 epoch->receiver.aproxPositionRover[1]*epoch->receiver.aproxPositionRover[1] + 
						 epoch->receiver.aproxPositionRover[2]*epoch->receiver.aproxPositionRover[2]);
				if ( r < (MIN_EARTH_RADIUS-1000.) ) {
					sprintf(messagestr,"Rover a priori position must be above Earth surface (%.2f vs %.2f).",r,MIN_EARTH_RADIUS-1000.0);
					printError(messagestr,&options);
				} 
			} else if ( (options.receiverPositionSource >= rpCALCULATERINEX && options.receiverPositionSource <=rpCALCULATEUSER) ||
				  (options.receiverPositionSource >= rpCALCULATERINEXREF && options.receiverPositionSource <=rpCALCULATEUSERREF)	) {
				//Check initial coordinates are not 0,0,0
				if (epoch->receiver.aproxPosition[0]==0. && epoch->receiver.aproxPosition[1]==0. && epoch->receiver.aproxPosition[2]==0.) {
					if (options.receiverPositionSource ==rpCALCULATEUSER || options.receiverPositionSource ==rpCALCULATEUSERREF) {
						sprintf(messagestr,"Initial coordinates for computing solution cannot be (0,0,0)");
						printError(messagestr,&options);
					} else {
						sprintf(messagestr,"WARNING RINEX a priori coordinates are (0,0,0), which are not allowed as a initial position. (%d,0,0) coordinates will be used instead",(int)EARTH_RADIUS);
						printInfo(messagestr,&options);
						epoch->receiver.aproxPosition[0]=EARTH_RADIUS;
						epoch->receiver.aproxPosition[1]=0.;
						epoch->receiver.aproxPosition[2]=0.;
					}
				}	
			}
			//Check reference station coordinates
			if ( options.receiverPositionSource >= rpRTCMUserbaseline && options.receiverPositionSource!= rpRTCMRefUSERRoverREF) {
				r = sqrt(epochDGNSS->receiver.aproxPosition[0]*epochDGNSS->receiver.aproxPosition[0] + 
						 epochDGNSS->receiver.aproxPosition[1]*epochDGNSS->receiver.aproxPosition[1] + 
						 epochDGNSS->receiver.aproxPosition[2]*epochDGNSS->receiver.aproxPosition[2]);
				if ( r < (MIN_EARTH_RADIUS-1000.) ) {
					sprintf(messagestr,"Reference station position must be above Earth surface (%.2f vs %.2f).",r,MIN_EARTH_RADIUS-1000.0);
					printError(messagestr,&options);
				} 
			}
		}
		
		
		// If receiver antenna phase centre is from ANTEX file, look for it
		if ( options.antennaData == adANTEX ) {
			ant = getAntenna(epoch->receiver.antenna.type,&antennaList,&options);
			if ( ant == NULL ) {
				sprintf(messagestr,"Receiver antenna phase centre not found in ANTEX file [%s]. Use '-model:recphasecenter no' to disable it",epoch->receiver.antenna.type);
				printError(messagestr,&options);
			} else {
				memcpy(&epoch->receiver.antenna,ant,sizeof(TAntenna));
			}
		}
		
		// If GPS Receiver types file was available, classify the receiver
		if ( sopt.setRecType == rtNA ) {
			if ( sopt.recFile[0] != '\0' ) {
				recD = getReceiverType(epoch->receiver.type,&recList);
				if ( recD == NULL ) {
					// Added a further Check: Only print error if strict option enabled!
					if ( options.p1c1dcbModel == p1c1STRICT ) {
						sprintf(messagestr,"Strict P1-C1 DCB option enabled, but receiver type not found in GPS Receiver type file [%s]",epoch->receiver.type);
						printError(messagestr,&options); 
					}
				} else {
					epoch->receiver.recType = recD->type;
				}
			} 
		} else {
			epoch->receiver.recType = sopt.setRecType;
		}
		if ( epoch->receiver.recType == rtUNKNOWN ) {
			if ( sopt.recFile[0] == '\0' ) {
				printInfo("WARNING Receiver type is unknown (no GPS_Receiver_type file provided). Assuming nominal behaviour",&options);
			} else {
				printInfo("WARNING Receiver type is unknown. Assuming nominal behaviour",&options);
			}
		}
		
		// Flexible C1/P1 (C1C/C1P) handling
		if ( options.flexibleC1P1 ) {
			if ( (epoch->measOrder[GPS].meas2Ind[C1C] == -1 && epoch->measOrder[GPS].meas2Ind[C1P] != -1) || 
				 (epoch->measOrder[GPS].meas2Ind[C1C] != -1 && epoch->measOrder[GPS].meas2Ind[C1P] == -1) ) {
				epoch->receiver.equivalentC1P1 = 1;
				printInfo("Making equivalence: P1 == C1",&options);
			}
			if ( options.DGNSS == 1 ) {
				if ( (epochDGNSS->measOrder[GPS].meas2Ind[C1C] == -1 && epochDGNSS->measOrder[GPS].meas2Ind[C1P] != -1) || 
					 (epochDGNSS->measOrder[GPS].meas2Ind[C1C] != -1 && epochDGNSS->measOrder[GPS].meas2Ind[C1P] == -1) ) {
					epochDGNSS->receiver.equivalentC1P1 = 1;
					printInfo("Making equivalence: P1 == C1 for Reference Station",&options);
				}
			}
		}
		
		// Print input parameters
		printParameters(&options,epoch,&products,sopt.stanfordESAFile,sopt.stanfordESALOIFile,sopt.kmlFile,sopt.kml0File,sopt.SP3OutputFile,sopt.RefPosOutputFile);

		processedEpochs = 0;
		direction = pFORWARD;
		filterIterations = 1;
		while ( ret ) {
			// Determination of Backward/Forward
			if ( filterIterations%2 == 1 ) direction = pFORWARD;
			else direction = pBACKWARD;
			ret = readRinexObsEpoch(fdRNX,epoch,&constellation,direction,Epochstr,&options);
			// ret == 2 means that RINEX observables is "large/concatenated", so we need to read
			// the new header and the next epoch (if header is found, readRinexObsEpoch function does not read any data!)
			if ( ret == 2 ) {
				ret = readRinexObsHeader(fdRNX,NULL,epoch, &options);
				// If receiver antenna phase centre is from ANTEX file, look for it
				if ( options.antennaData == adANTEX ) {
					ant = getAntenna(epoch->receiver.antenna.type,&antennaList,&options);
					if ( ant == NULL ) {
						sprintf(messagestr,"Receiver antenna phase centre not found in ANTEX file [%s]. Use '-model:recphasecenter no' to disable it",epoch->receiver.antenna.type);
						printError(messagestr,&options);
					} else {
						memcpy(&epoch->receiver.antenna,ant,sizeof(TAntenna));
					}
				}
				
				// If GPS Receiver types file was available, classify the receiver
				if ( sopt.setRecType == rtNA ) {
					if ( sopt.recFile[0] != '\0' ) {
						recD = getReceiverType(epoch->receiver.type,&recList);
						if ( recD == NULL ) {
							// Added a further Check: Only print error if strict option enabled!
							if ( options.p1c1dcbModel == p1c1STRICT ) {
								sprintf(messagestr,"Strict P1-C1 DCB option enabled, but receiver type not found in GPS Receiver type file [%s]",epoch->receiver.type);
								printError(messagestr,&options); 
							}
						} else {
							epoch->receiver.recType = recD->type;
						}
					} 
				} else {
					epoch->receiver.recType = sopt.setRecType;
				}
				//Read the next epoch
				if ( ret == 1 ) {
					ret = readRinexObsEpoch(fdRNX, epoch, &constellation, direction, Epochstr, &options);
				}
			}
			//This is to avoid reading the next day of ephemeris data when the observation file starts at the end of the previous day (for converging values)
			if (MJDNEpoch==-1) {
				MJDNEpoch=epoch->t.MJDN;
				if(epoch->t.SoD>=75000.) {
						MJDNEpoch++;
				}
			}

			//// DGNSS
			//// Adjust time between Reference Station and Rover Station (user) in DGNSS mode
			//// It is just done to speed up the software and make it work as in real-time behaviour
			if ( options.DGNSS == 1 ) {
				computeDGNSScor = 1;
				if ( deltaTime == 0.0 && retDGNSS == 1 ) { // Normal procedure (read both Rover and Reference Stations)
					if ( options.RTCMmode == ProcessRTCM2 ) {
						// Process the binary RTCM v2.x
						retDGNSS = converterRTCM2(fdRTCM2, rtcm2, NULL, NULL, epoch, epochDGNSS, &options);
					} else if ( options.RTCMmode == ProcessRTCM3 ) {
						// Process the binary RTCM v3.x
						retDGNSS = converterRTCM3(fdRTCM3, rtcm3, NULL, epoch, epochDGNSS, &options);
					} else {
						// Read the RINEX observables
						retDGNSS = readRinexObsEpoch(fdRNXdgnss,epochDGNSS,&constellation,pFORWARD,Epochstr,&options);
						if(retDGNSS==2) {
							// Read the RINEX header and next epoch (if header is found, readRinexObsEpoch function does not read any data!)
							retDGNSS = readRinexObsHeader(fdRNXdgnss,NULL,epochDGNSS,&options);
							retDGNSS = readRinexObsEpoch(fdRNXdgnss,epochDGNSS,&constellation,pFORWARD,Epochstr,&options);
							retDGNSS=1;
						}
						epoch->receiver.numRecStation=epochDGNSS->receiver.numRecStation;
						epoch->receiver.RecStationCoord=epochDGNSS->receiver.RecStationCoord;
						epoch->receiver.ChangedStaEpoch=epochDGNSS->receiver.ChangedStaEpoch;
					}
				} else if ( deltaTime > 0.0 && retDGNSS == 1 ) {
					// Advance the Reference Station corrections; Rover Station (user) has data gap
					while ( deltaTime >= 1.0 && retDGNSS == 1 ) {
						if ( options.RTCMmode == ProcessRTCM2 ) {
							// Process the binary RTCM v2.x
							retDGNSS = converterRTCM2(fdRTCM2, rtcm2, NULL, NULL, epoch, epochDGNSS, &options);
						} else if ( options.RTCMmode == ProcessRTCM3 ) {
							// Process the binary RTCM v3.x
							retDGNSS = converterRTCM3(fdRTCM3, rtcm3, NULL, epoch, epochDGNSS, &options);
						} else {
							// Read the RINEX observables
							retDGNSS = readRinexObsEpoch(fdRNXdgnss, epochDGNSS, &constellation, pFORWARD, Epochstr,&options);
							if(retDGNSS==2) {
								// Read the RINEX header and next epoch (if header is found, readRinexObsEpoch function does not read any data!)
								retDGNSS = readRinexObsHeader(fdRNXdgnss,NULL,epochDGNSS,&options);
								retDGNSS = readRinexObsEpoch(fdRNXdgnss, epochDGNSS, &constellation, pFORWARD, Epochstr,&options);
								retDGNSS=1;
							}
							epoch->receiver.numRecStation=epochDGNSS->receiver.numRecStation;
							epoch->receiver.RecStationCoord=epochDGNSS->receiver.RecStationCoord;
							epoch->receiver.ChangedStaEpoch=epochDGNSS->receiver.ChangedStaEpoch;
						}
						deltaTime = tdiff(&epoch->t, &epochDGNSS->t);
					}
				}
				deltaTime = tdiff(&epoch->t, &epochDGNSS->t);
				//Check for the case that Rover is advanced to Reference station due to Rover has decimal in the epoch (e.g 1.001. 1.1)
				if ( deltaTime >= 1.0 && retDGNSS == 1 ) { 
					if ( options.RTCMmode == ProcessRTCM2 ) {
						// Process the binary RTCM v2.x
						retDGNSS = converterRTCM2(fdRTCM2, rtcm2, NULL, NULL, epoch, epochDGNSS, &options);
					} else if ( options.RTCMmode == ProcessRTCM3 ) {
						// Process the binary RTCM v3.x
						retDGNSS = converterRTCM3(fdRTCM3, rtcm3, NULL, epoch, epochDGNSS, &options);
					} else {
						// Read the RINEX observables
						retDGNSS = readRinexObsEpoch(fdRNXdgnss, epochDGNSS, &constellation, pFORWARD, Epochstr, &options);
						if(retDGNSS==2) {
							// Read the RINEX header and next epoch (if header is found, readRinexObsEpoch function does not read any data!)
							retDGNSS = readRinexObsHeader(fdRNXdgnss,NULL,epochDGNSS,&options);
							retDGNSS = readRinexObsEpoch(fdRNXdgnss, epochDGNSS, &constellation, pFORWARD, Epochstr, &options);
							retDGNSS=1;
						}
						epoch->receiver.numRecStation=epochDGNSS->receiver.numRecStation;
						epoch->receiver.RecStationCoord=epochDGNSS->receiver.RecStationCoord;
						epoch->receiver.ChangedStaEpoch=epochDGNSS->receiver.ChangedStaEpoch;
					}
					deltaTime = tdiff(&epoch->t, &epochDGNSS->t);
				}
				// Base Station is advanced with respect to the Rover
				// Therefore, do not compute corrections
				if ( deltaTime < 0 && retDGNSS == 1 ) computeDGNSScor = 0;

				// In case of S/A enabled, the maximum age is set to 1 seconds
				if ( processedEpochs == 0 && options.RTCMmode == ProcessRINEX ) {
					if ( epoch->t.MJDN < 51665 /*May 1st, 2000*/ ) {
						options.maxAgeDGNSS = 1;
						printInfo("WARNING the maximum age to apply DGNSS corrections is forced to 1 seconds due to S/A", &options);
					}
				}
			}
			//// End of Adjust time between Reference Station and Rover Station (user) in DGNSS mode

			if ( ret ) {
				//Check if first epoch set by user is reached
				if (options.StartEpoch.MJDN!=-1) {
					if(tdiff(&epoch->t,&options.StartEpoch)<0.) {
						//Not arrived to first epoch set by user
						continue;
					} else {
						//Set MJDN to -1 to stop checking the condition
						options.StartEpoch.MJDN=-1;
					}
				} else if (options.EndEpoch.MJDN!=-1) {
					if(tdiff(&epoch->t,&options.EndEpoch)>1E-4) { //The 1E-4 is to avoid problems with decimals
						//Last epoch set by user reached
						break;
					}
				}
				//Check the first epoch of the RINEX. If it is greater-equal than HOURSPREVDAYCONVERGENCE we have to wait 
				//for the next day until we use results for the SBAS summary
				if(Summary) {
					if (options.firstEpochSummary.MJDN!=-1) {
						if (tdiff(&epoch->t,&options.firstEpochSummary)>=0.) {
							options.useDatasummary=1;
							//Save first epoch of summary 
							memcpy(&epoch->StartSummaryEpoch,&epoch->t,sizeof(TTime));
							//Turn off Summary to avoid continously checking this condition
							Summary=0;
						} else {
							options.useDatasummary=0;
						}
					} else if (firstEpoch) {
						//First epoch read
						firstEpoch=0;
						if(options.waitForNextDay==1 && epoch->t.SoD>=(double)HOURSPREVDAYCONVERGENCE*3600.) {
							options.useDatasummary=0;
						} else {
							options.useDatasummary=1;
							//Save first epoch of summary 
							memcpy(&epoch->StartSummaryEpoch,&epoch->t,sizeof(TTime));
							//Turn off Summary to avoid continously checking this condition
							Summary=0;
						}
					} else if (options.useDatasummary==0) {
						//The 3600 seconds is an arbitrary value just to make sure that at the start of the next day,
						//even though there may be epochs missing at the beginning of the observation file, 
						//the first epoch at the beginning of the observation file will make this condition true
						if(epoch->t.SoD<3600.) {
							options.useDatasummary=1;
							//Save first epoch of summary 
							memcpy(&epoch->StartSummaryEpoch,&epoch->t,sizeof(TTime));
							//Turn off Summary to avoid continously checking this condition
							Summary=0;
						}
					}
				}
					
				if ( tdiff(&epoch->t,&endProductsTime) > 0 && options.filterIterations > 1 ) ret = 0;
			}
			if ( ret ) {
				if ( tdiff(&epoch->t,&endProductsTime) > 0 && options.filterIterations > 1 ) {
					ret = 0;
				//} else if ( tdiff(&epoch->t,&endProductsTime) > 0 ) {
				} else if (tdiff(&epoch->t,&endProductsTime) > 0 || MJDNEpoch<epoch->t.MJDN ) {
					// Read the following day of the RINEX navigation file
					ret2=1;
						
					if ( fdRNXnav != NULL) {
						if(nextNav==1) {
							ret1 = readRinexNav(fdRNXnav,&products,&rinexNavVersion);
							// Set products end time
							if ( options.workMode == wmDOPROCESSING ) {
								endProductsTime = getProductsLastEpoch(&products);
							}
							if ( ret1 < 1 ) {
								if ( (int)rinexNavVersion > 3 && rinexNavVersion != 0 ) {
									sprintf(messagestr,"RINEX navigation version %1.2f from file [%s] is not supported. Supported versions are 2 and 3",rinexNavVersion,sopt.navFile[0]);
									printError(messagestr,&options);
								} else {
									sprintf(messagestr,"Reading RINEX navigation message file [%s]",sopt.navFile[0]);
									printError(messagestr,&options);
								}
							} else if (ret1==2) {
								nextNav=1;
							} else {
								nextNav=0;
								fclose(fdRNXnav);
								fdRNXnav=NULL;
							}
						} else {
							ret1=0;
						}
						if ( ret1 >= 1 ) concatCount++;
					}
					if ( options.NextSP3 ) {
						freeSP3data(&pastSP3Prod);
						memcpy(&pastSP3Prod,&products,sizeof(TGNSSproducts));
						memcpy(&products,&nextSP3Prod,sizeof(TGNSSproducts));
						if ( fdSP3 != NULL )	ret1 = readSP3(fdSP3,&nextSP3Prod,1,1,0);
						if ( ret1 == -2 ) {
							sprintf(messagestr, "SP3 orbit and clock products file [%s] has incorrect number of entries in header", sopt.SP3File[0]);
							printError(messagestr, &options);
						}
						if ( fdSP3o != NULL )	ret1 = readSP3(fdSP3o,&nextSP3Prod,1,0,0);
						if ( ret1 == -2 ) {
							sprintf(messagestr, "SP3 orbit product file [%s] has incorrect number of entries in header", sopt.orbFile[0]);
							printError(messagestr, &options);
						}
						if ( fdCLK != NULL )	ret2 = readRinexClocks(fdCLK,&nextSP3Prod);
						if ( ret1 != 2 ) 		options.NextSP3 = 0;
						if ( fdCLK != NULL && ret2 != 2 ) 	options.NextSP3 = 0; //Both SP3 and CLK must be equal length, otherwise do not concatenate more

						if(options.NextSP3==0) {
							// Set products end time
							if ( options.workMode == wmDOPROCESSING ) {
								endProductsTime = getProductsLastEpoch(&nextSP3Prod);
							}
						} else {
							// Set products end time
							if ( options.workMode == wmDOPROCESSING ) {
								endProductsTime = getProductsLastEpoch(&products);
							}
						}

						//Concatenate SP3 and clocks
						ConcatenateSP3(0,&products,&pastSP3Prod,&nextSP3Prod,&options);	
					} else if (fdSP3 != NULL || fdSP3o != NULL) {
						endProductsTime = getProductsLastEpoch(&nextSP3Prod);
					}
					// End gLAB because no products are available
					if ( ret1 == 0 && ret2==0 ) {
						if ( concatCount == 1 ) {
							if (printProgress==1) {
								fprintf(options.terminalStream,"Percentage converted: %3d%%%10s%c",100,"",options.ProgressEndCharac);
								#if !defined(__WIN32__)
									if (options.ProgressEndCharac=='\r') {
										fprintf(options.terminalStream,"%60s%c","",options.ProgressEndCharac);
									}
									//Enable cursor again
									if (sopt.disableCursor==1) {
										fprintf(options.terminalStream,"%s",enableCursor);
									}
								#endif
								fflush(options.terminalStream);
							}
							printError("Orbit and clock products are of a different time than the observation RINEX",&options);
						}
						return 1;
					}

					// Check DCB
					for (i=0;i<sopt.numTGD;i++) {
						auxft1 = whatFileTypeIs(sopt.tgdFile[i]);
						if ( auxft1 == ftRINEXbroadcast && options.p1p2dcbModel == p1p2RINEX ) {
							if ( fdTGD[i]!=NULL ) {
								retTGD[i]=readRinexNav(fdTGD[i],&productsTgd,&rinexNavVersion);
								if ( retTGD[i] < 1 ) {
									if ((int)rinexNavVersion>3 && rinexNavVersion!=0) {
										sprintf(messagestr,"RINEX navigation version %1.2f from file '%s' is not supported. Supported versions are 2 and 3",rinexNavVersion,sopt.tgdFile[i]); 	
										printError(messagestr,&options);
									} else {
										sprintf(messagestr,"Reading RINEX navigation message file for TGD data '%s'",sopt.tgdFile[i]);
										printError(messagestr,&options);
									}
								} else if (retTGD[i]!=2) {
									fclose(fdTGD[i]);
									fdTGD[i]=NULL;
								}
								tgdData.BRDC = productsTgd.BRDC;
							} else {
								tgdData.BRDC = products.BRDC;
							}
						} else if ( auxft1 == ftIONEX && options.p1p2dcbModel == p1p2IONEX && MJDNEpoch<epoch->t.MJDN) {
							//Read new DCB parameters only if we have changed day
							if (fdTGD[i]!=NULL ) { 
								retTGD[i]=readIONEX(fdTGD[i],&productsIonex,&ionexVersion);
								if ( retTGD[i] < 1 ) {
									if ((int)ionexVersion!=1 && ionexVersion!=0){
										sprintf(messagestr,"IONEX version %1.2f from file [%s] is not supported. Supported version is 1",ionexVersion,sopt.tgdFile[i]);
										printError(messagestr,&options);
									} else if (retTGD[i]==-2) {
										sprintf(messagestr,"Number of records in IONEX header in file [%s] does not match the number of records read",sopt.tgdFile[i]);
										printError(messagestr,&options);
									} else {
										sprintf(messagestr,"Reading IONEX file [%s] for DCB data" ,sopt.tgdFile[i]);
										printError(messagestr,&options);
									}
								} else if ( productsIonex.ionexDCB.DCBavailable == 0 ) {
									sprintf(messagestr,"IONEX file [%s] selected for P1-P2 DCB corrections, but no DCB data was found in the file",sopt.tgdFile[i]);
									printError(messagestr,&options);
								} else {
									tgdData.ionexDCB = productsIonex.ionexDCB;
									if ( retTGD[i] == 2 ) {
										sprintf(messagestr,"WARNING: IONEX file [%s] for DCB data has no 'END OF FILE' line. File may not be complete",sopt.tgdFile[i]);
										printInfo(messagestr,&options);
										fclose(fdTGD[i]);
										fdTGD[i]=NULL;
									} else if ( retTGD[i] == 4 ) {
										sprintf(messagestr,"WARNING: IONEX file [%s] for DCB data is concatenated, but has no 'END OF FILE' line. File may not be complete",sopt.tgdFile[i]);
										printInfo(messagestr,&options);
									} else if (retTGD[i] != 3 ) {
										fclose(fdTGD[i]);
										fdTGD[i]=NULL;
									}
								}
							}
						}
					}
					// Check if Klobuchar 
					if ( options.ionoModel == Klobuchar && MJDNEpoch<epoch->t.MJDN ) {
						//Read new Klobuchar parameters only if we have changed day
						if ( fdRNXKlb != NULL ) {
							ret1=readRinexNav(fdRNXKlb,&productsKlb,&rinexNavVersion);
							if ( ret1 < 1 ) {
								if ( (int)rinexNavVersion > 3 && rinexNavVersion != 0 ) {
									sprintf(messagestr,"RINEX navigation version %1.2f from file '%s' is not supported. Supported versions are 2 and 3",rinexNavVersion,sopt.klbFile);
									printError(messagestr,&options);
								} else {
									sprintf(messagestr,"Reading RINEX navigation message file '%s'",sopt.klbFile);
									printError(messagestr,&options);
								}
							} else if (ret1!=2) {
								fclose(fdRNXKlb);
								fdRNXKlb=NULL;
							}
						} else if ( products.type == BRDC ) {
							productsKlb.BRDC = products.BRDC;
						}
					}
					// Check if BeiDou
					else if ( options.ionoModel == BeiDou && MJDNEpoch<epoch->t.MJDN ) {
						//Read new BeiDou parameters only if we have changed day
						if ( fdRNXBei != NULL ) {
							ret1=readRinexNav(fdRNXBei,&productsBei,&rinexNavVersion);
							if ( ret1 < 1 ) {
								if ( (int)rinexNavVersion > 3 && rinexNavVersion != 0 ) {
									sprintf(messagestr,"RINEX navigation version %1.2f from file '%s' is not supported. Supported versions are 2 and 3",rinexNavVersion,sopt.beiFile);
									printError(messagestr,&options);
								} else {
									sprintf(messagestr,"Reading RINEX navigation message file '%s'",sopt.beiFile);
									printError(messagestr,&options);
								}
							} else if (ret1!=2) {
								fclose(fdRNXBei);
								fdRNXBei=NULL;
							}
						} else if ( products.type == BRDC ) {
							productsBei.BRDC = products.BRDC;
						}
					}
					// Check if NeQuick
					else if ( options.ionoModel == neQuick && MJDNEpoch<epoch->t.MJDN ) {
						//Read new NeQuick parameters only if we have changed day
						if ( fdRNXNeq != NULL ) {
							ret1=readRinexNav(fdRNXNeq,&productsNeq,&rinexNavVersion);
							if ( ret1 < 1 ) {
								if ( (int)rinexNavVersion > 3 && rinexNavVersion != 0 ) {
									sprintf(messagestr,"RINEX navigation version %1.2f from file '%s' is not supported. Supported versions are 2 and 3",rinexNavVersion,sopt.neqFile);
									printError(messagestr,&options);
								} else {
									sprintf(messagestr,"Reading RINEX navigation message file '%s' for NeQuick data",sopt.neqFile);
									printError(messagestr,&options);
								}
							} else if ( (int)rinexNavVersion < 3 ) {
								sprintf(messagestr,"RINEX navigation version %1.2f from file '%s' is below 3. This version does not contain NeQuick data",rinexNavVersion,sopt.neqFile);
								printError(messagestr,&options);
							} else if (ret1!=2) {
								fclose(fdRNXNeq);
								fdRNXNeq=NULL;
							}
						} else if ( products.type == BRDC && (int)rinexNavVersion < 3 ) {
							sprintf(messagestr,"RINEX navigation version %1.2f from file '%s' is below 3. This version does not contain NeQuick data",rinexNavVersion,sopt.navFile[0]);
							printError(messagestr,&options);
						} else if ( products.type == BRDC ) {
							productsNeq.BRDC = products.BRDC;
						}
					}
					// Check if IONEX
					else if ( options.ionoModel == IONEX && MJDNEpoch<epoch->t.MJDN ) {
						//Read new IONEX only if we have changed day
						if ( fdIONEX != NULL ) {
							ret1 = readIONEX(fdIONEX,&ionex,&ionexVersion);
							if ( ret1 < 1 ) {
								if ( (int)ionexVersion != 1 && ionexVersion != 0 ) {
									sprintf(messagestr,"IONEX version %1.2f from file [%s] is not supported. Supported version is 1",ionexVersion,sopt.inxFile);
									printError(messagestr,&options);
								} else if (ret1==-2) {
									sprintf(messagestr,"Number of records in IONEX header in file [%s] does not match the number of records read",sopt.inxFile);
									printError(messagestr,&options);
								} else if (ret1==-3) {
									sprintf(messagestr,"IONEX header in file [%s] is incorrect or there are missing records",sopt.inxFile);
									printError(messagestr,&options);
								} else {
									sprintf(messagestr,"Reading IONEX file [%s] for ionospheric data" ,sopt.inxFile);
									printError(messagestr,&options);
								}
							} else if ( ret1 == 2 ) {
								sprintf(messagestr,"WARNING: IONEX file [%s] has no 'END OF FILE' line. File may not be complete",sopt.inxFile);
								printInfo(messagestr,&options);
								fclose(fdIONEX);
								fdIONEX=NULL;
							} else if ( ret1 == 4 ) {
								sprintf(messagestr,"WARNING: IONEX file [%s] is concatenated, but has no 'END OF FILE' line. File may not be complete",sopt.inxFile);
								printInfo(messagestr,&options);
							} else if ( ret1 != 3 ) {
								fclose(fdIONEX);
								fdIONEX=NULL;
							}
							
							// If there is no RMS data in IONEX file, do not use this data even though it is indicated in gLAB parameters.
							if ( ionex.RMSavailable == 0 ) {
								if (options.useSigmaIono ==1) {
									sprintf(messagestr,"WARNING: IONEX file [%s] has no RMS values. Disconnecting sigma iono in filter",sopt.inxFile);
									printInfo(messagestr,&options);
									options.useSigmaIono = 0;
								}
							}
						}
					}
					else if ( options.ionoModel == SBASiono && MJDNEpoch<epoch->t.MJDN ) {
						//Read new Klobuchar parameters only if we have changed day
						// If we are processing with SBAS, we need to copy Klobuchar parameters to its struct
						if (products.BRDC==NULL) {
							//If we have not read any product type, allocate memory and initialize to 0 the productsKlb structure (only if before had not been done)
							if (productsKlb.BRDC==NULL) {
								productsKlb.BRDC = malloc(sizeof(TBRDCproducts));
								initBRDCproducts(productsKlb.BRDC);
							}
						} else {
							productsKlb.BRDC = products.BRDC;
						}
					}

					//Only update last day read if we have changed day
					if (MJDNEpoch<epoch->t.MJDN ) {
						MJDNEpoch=epoch->t.MJDN;
					}
				}
			}

			// Check if SBAS mode has been selected
			if ( options.SBAScorrections == 1 ) {
				// Read SBAS data until current epoch	
				retsbas = readSBASFile(sopt.sbasFile,&SBASdatabox,&rinexBVersion,&epoch->t,&options);
			}
			if ( options.useraddednoise == 1) {
				addUserError(fdNoise,sopt.addederrorFile,epoch,&UserError,&options);
			}
			//Update progress
			if (epoch->NewPercentage) { 
				epoch->NewPercentage=0;
				if (options.ProgressEndCharac=='\r') {
					//Printing to a terminal
					fprintf(options.terminalStream,"%s%c",Epochstr,options.ProgressEndCharac);
					fflush(options.terminalStream);
				} else {
					//Printing for the GUI. Only print if the integer of the percentage have changed (to avoid message spamming)
					if ((int)epoch->CurrentPercentage!=(int)epoch->PreviousPercentage) {
						fprintf(options.terminalStream,"%s%c",Epochstr,options.ProgressEndCharac);
						fflush(options.terminalStream);
					}
				}
				epoch->PreviousPercentage=epoch->CurrentPercentage;
			}

			if ( ret ) {
				if ( options.DGNSS == 1 ) { // DGNSS mode
					preprocess(epoch, &options, 1);
					if ( computeDGNSScor == 1 && ( options.RTCMmode == ProcessRINEX || options.RTCMmode == ProcessRTCM3 ) ) {
						// The cycle slips were calculated before
						preprocess(epochDGNSS,&options,2);
					} else for ( i = 0; i < epochDGNSS->numSatellites; i++ ) epochDGNSS->cycleslip.arcLength[i]++;
				} else {
					preprocess(epoch, &options, 0);
					if ( options.useraddednoise == 2) {
						addUserError(fdNoise,sopt.addederrorFile,epoch,&UserError,&options);
					}
				}
				if ( !anyInsideProducts ) {
					if ( tdiff(&epoch->t,&startProductsTime) >= 0 && tdiff(&epoch->t,&endProductsTime) <= 0 ) anyInsideProducts = 1;
				}
				if ( !isEpochDecimated(epoch, &options) ) {
					printInput(epoch, &tgdData,&options);
					if ( options.workMode == wmDOPROCESSING ) {

						if (options.useDatasummary == 1) {
							epoch->TotalEpochs++;	//Add 1 to total epochs processed for summary
							//Save last epoch of summary 
							memcpy(&epoch->LastSummaryEpoch,&epoch->t,sizeof(TTime));
						}
						//Get reference coordinates if they are read from file	
						if (UseReferenceFile==1) {
							//Orbit SP3 uses orbit interpolation degree, change it temporary to reference interpolation degree
							if (options.stanfordesa==4) {
								//Reenable Stanford-ESA if in previous epoch there was no position from reference file
								options.stanfordesa=1;
							}
							epoch->receiver.RefPositionAvail=1;
							options.orbitInterpolationDegree=options.RefDegInterp;
							retPosFile=getPositionSP3(&ReferencePos,&epoch->t,0,0,epoch->receiver.aproxPositionRef,&options);
							options.orbitInterpolationDegree=OrbInterpDegree;
							if(retPosFile==0) {
								//Reference position could not be computed
								if (options.receiverPositionSource == rpSETREF) {
									//A priori position is used for modelling, As no position is available, skip epoch
									if (options.useDatasummary == 1) epoch->NumNoRefSolSkipped++;
									sprintf(messagestr,"%17s A priori position for modelling and differential OUTPUT fields could not be computed. Epoch skipped",t2doystr(&epoch->t));
									printInfo(messagestr,&options);
									continue;
								} else {
									if (options.stanfordesa==1) {
										//Disable temporary Stanford-ESA when no reference position is available
										options.stanfordesa=4;
									}
									epoch->receiver.RefPositionAvail=0;
									sprintf(messagestr,"%17s Reference position could not be computed. Differential OUTPUT fields for this epoch will be 0",t2doystr(&epoch->t));
									printInfo(messagestr,&options);
								}
							} else {
								//Compute reference position orientation (necessary for the summary)
								XYZ2NEU(epoch->receiver.aproxPositionRef,epoch->receiver.aproxPositionNEURef);
								getGroundStationOrientation(epoch->receiver.aproxPositionNEURef,epoch->receiver.orientationRef);
								if (options.receiverPositionSource == rpSETREF) {
									memcpy(epoch->receiver.aproxPosition,epoch->receiver.aproxPositionRef,sizeof(double)*3);
									sprintf(messagestr,"%17s A priori position for modelling and differential OUTPUT fields updated to %13.4f %13.4f %13.4f",t2doystr(&epoch->t),epoch->receiver.aproxPosition[0],epoch->receiver.aproxPosition[1],epoch->receiver.aproxPosition[2]);
									printInfo(messagestr,&options);
								} else {
									sprintf(messagestr,"%17s Reference position for differential OUTPUT fields updated to %13.4f %13.4f %13.4f",t2doystr(&epoch->t),epoch->receiver.aproxPositionRef[0],epoch->receiver.aproxPositionRef[1],epoch->receiver.aproxPositionRef[2]);
									printInfo(messagestr,&options);
									//Copy coordinates to aproxPositionRover in DGNSS mode
									if ( options.receiverPositionSource == rpRTCMRoverUSERREF ||  options.receiverPositionSource == rpRTCMRefUSERRoverREF) {
										memcpy(epoch->receiver.aproxPositionRover,epoch->receiver.aproxPositionRef,sizeof(double)*3);
									}
								}
							}
						}

						kalmanRes = 2;
						kalmanIterations = 0;
						Measprinted = 0;
						epoch->SwitchPossible=1;	//Enable switches in current epoch (only applicable if mode or GEO switch is enabled)
						epoch->overMaxGDOP=0;		//Reset flag for GDOP threshold
						while ( kalmanRes >= 2 ) {
							if( kalmanRes == 2 ) {
								kalmanIterations++;
								if ( kalmanIterations > options.maxKalmanIterations ) {
									if (printProgress==1 && options.ProgressEndCharac=='\r') {
										//This for cleaning the screen of the progress bar
										fprintf(options.terminalStream,"%80s%c","",options.ProgressEndCharac); 
									}
									printError("No convergence to solution",&options);
								}
							}
							modelEpoch(epoch,&options);
							if ( options.SBAScorrections == 1 && options.onlySBASiono == 0 ) {
								retsbas=1;
								if ( kalmanRes == 3 ) {
									if (messagestrSwitchGEO[0]!='\0') {
										printInfo(messagestrSwitchGEO,&options);
									}
									if (messagestrSwitchMode[0]!='\0') {
										printInfo(messagestrSwitchMode,&options);
									}
									retsbas = SwitchSBASGEOMode(epoch,epoch->usableSatellites,epoch->numsatdiscardedSBAS,SBASdatabox.SBASdata,&options);
								}
								while ( retsbas >= 1 ) {
									numsatellites = 0;
									epoch->numsatdiscardedSBAS = 0;
									if(options.GEOindex!=-1) {
										epoch->SBASUsedGEO=SBASdatabox.SBASdata[options.GEOindex].PRN;
									}
									epoch->SBASUsedMode=options.precisionapproach;
									#pragma omp parallel for private(ret1)
									for ( i = 0; i < epoch->numSatellites; i++ ) {
										ret1 = modelSatellite(epoch,NULL,i,&products,&productsKlb,&productsBei,&productsNeq,&ionex,&fppp,&tropoGal,&tgdData,&constellation,SBASdatabox.SBASdata,&options);
										if ( ret1 == 1 ) {
											#pragma omp atomic
											numsatellites++;
										} else {
											if ( epoch->sat[i].hasSBAScor == 0 && epoch->sat[i].GNSS == GPS ) {
												// We need to check that the satellite has been discarded due to SBAS corrections
												// and not due to other reasons. This is important because if satellites are discarded
												// for other reasons, changing GEO will be useless
												#pragma omp atomic
												epoch->numsatdiscardedSBAS++;
											}
										}
									}
									// When computing with SBAS, if there are not 4 satellites available, we should try to change GEO or mode if we can
									if ( Measprinted == 0 ) {
										printMeas(epoch,&tgdData,&options);
										Measprinted=1;
									}
									retsbas = SwitchSBASGEOMode(epoch,numsatellites,epoch->numsatdiscardedSBAS,SBASdatabox.SBASdata,&options);
								} 
							} else if ( options.DGNSS == 1 ) {
								// DGNSS mode
								//Note for multithreading with openmp: It is slower with multithreading than single thread due to
								//the overhead for creating multiple threads
								if( kalmanRes != 3 ) {
									if (options.stanfordesa==3) {
										//Enable again Stanford-ESA if it had been disabled in DGNSS mode when solution is in SPP
										options.stanfordesa=1;
									}
									if ( computeDGNSScor == 1 ) {
										// options.RTCMmode == ProcessRINEX => processing two RINEXs files in DGNSS (RTCM v3.x)
										// options.RTCMmode ==  ProcessRTCM3 => processing the RTCM v3.x directly
										if ( options.RTCMmode == ProcessRINEX || options.RTCMmode == ProcessRTCM3 ) computeDGNSScorrections(epoch,epochDGNSS,&products,&options); // RTCM v3.x
										else if ( options.RTCMmode == ProcessRTCM2 ) prepareDGNSScorrections(epoch,epochDGNSS,&products,&options); // RTCM v2.x
									}
									preFillUsableSatellites(epoch,epochDGNSS,&products,&options);
									for ( i=0;i<epoch->numSatellites;i++ ) {
										modelSatellite(epoch,epochDGNSS,i,&products,&productsKlb,&productsBei,&productsNeq,&ionex,&fppp,&tropoGal,&tgdData,&constellation,SBASdatabox.SBASdata,&options);
									}
								} else {
									//Solution moved to SPP
									for ( i=0;i<epoch->numSatellites;i++ ) {
										epoch->sat[i].hasDGNSScor = 1;
										modelSatellite(epoch, epochDGNSS, i, &products, &productsKlb, &productsBei, &productsNeq, &ionex, &fppp, &tropoGal, &tgdData, &constellation, SBASdatabox.SBASdata, &options);
									}
								}
							} else {
								// Normal processing mode
								#pragma omp parallel for
								for ( i=0;i<epoch->numSatellites;i++ ) {
									modelSatellite(epoch,epochDGNSS,i,&products,&productsKlb,&productsBei,&productsNeq,&ionex,&fppp,&tropoGal,&tgdData,&constellation,SBASdatabox.SBASdata,&options);
								}
							}
							if ( Measprinted == 0 ) {
								printMeas(epoch, &tgdData,&options);
								Measprinted = 1;
							}
							kalmanRes = Kalman(epoch,&solution,PRNlist,&prevUnkinfo,&StdESA,&options);
							if ( kalmanRes == 1 ) {
								processedEpochs++;
								if(options.DGNSS == 1 ) {
									printOutput(epoch, epochDGNSS, &solution, &options, &prevUnkinfo,sopt.obsFile,VERSION);
									//In DGNSS mode, we can choose wheter to write SPP solution or not
									if ((options.solutionMode==SPPMode && options.WriteSPPsolInDGNSSmodeSP3==1) || options.solutionMode==DGNSSMode) {
										//Write SP3 file if needed
										if(fdOutSP3!=NULL) {
											writeSP3file(fdOutSP3,epoch, &solution,&prevUnkinfo,0,VERSION,&options);
										}
									}
									if ((options.solutionMode==SPPMode && options.WriteSPPsolInDGNSSmodeRefFile==1) || options.solutionMode==DGNSSMode) {
										//Write Reference file if needed
										if(fdOutRefFile!=NULL) {
											writeReffile(fdOutRefFile,epoch, &solution,&prevUnkinfo,&options);
										}
									}
									if (options.useDatasummary == 1) {
										DGNSSSummaryDataUpdate(UseReferenceFile,epoch, &solution, &options, &prevUnkinfo);
									}
								} else {
									printOutput(epoch, NULL, &solution, &options, &prevUnkinfo,sopt.obsFile,VERSION);
								
									if ( options.SBAScorrections == 1 && options.onlySBASiono == 0 ) {
										printSBASOUT(epoch, &solution, SBASdatabox.SBASdata, &options, &prevUnkinfo);
										// Compute SBAS summary
										if (options.useDatasummary == 1) {
											//Only update variables if we are navigating in PA or we are always in NPA forced by user parameters
											if (options.precisionapproach==PAMODE || options.UserForcedNPA==1) {
												SBASSummaryDataUpdate(UseReferenceFile,epoch, &solution, &SBASdatabox, &options, &prevUnkinfo);	
											} else if ( options.precisionapproach==NPAMODE && options.UserForcedNPA==0) {
												SBASdatabox.TotalNPAEpochs++;
											}
										}
									} else if (options.useDatasummary == 1) {
										SummaryDataUpdate(UseReferenceFile,epoch, &solution, &options, &prevUnkinfo);
									}
									//Write SP3 file if needed
									if(fdOutSP3!=NULL) {
										writeSP3file(fdOutSP3,epoch, &solution,&prevUnkinfo,0,VERSION,&options);
									}
									//Write Reference file if needed
									if(fdOutRefFile!=NULL) {
										writeReffile(fdOutRefFile,epoch, &solution,&prevUnkinfo,&options);
									}
								}
								//Print GEO or mode fallback INFO message after the OUTPUT and SBASOUT message
								if (messagestrSwitchGEO[0]!='\0') {
									printInfo(messagestrSwitchGEO,&options);
								}
								if (messagestrSwitchMode[0]!='\0') {
									printInfo(messagestrSwitchMode,&options);
								}
							} else if (kalmanRes == 0 ) {
								//No solution due to lack of satellites
								if (options.useDatasummary == 1) {
									epoch->NumNoSatSkipped++;
								}
							} else if (kalmanRes == -1 ) {
								//No solution due to geometry matrix is singular
								if (options.useDatasummary == 1) {
									epoch->NumSingularMatrixSkipped++;
								}
							} else if (kalmanRes == -2 ) {
								//No solution due to bad GDOP
								if (options.useDatasummary == 1) {
									epoch->NumGDOPSkipped++;
								}
							}
						}
					} else if ( options.workMode == wmSHOWINPUT ) {
						printMeas(epoch, &tgdData,&options);
					}
				}
			} else { // ret == 0
				if ( options.filterIterations >= ( filterIterations + 1 ) ) {
					filterIterations++;
					if ( filterIterations%2 == 0 ) { // Backward direction
						rewindEpochRinexObs(fdRNX, epoch->source);
					}
					ret = 1;
				}
			}
		}
		if ( !anyInsideProducts && options.workMode == wmDOPROCESSING )  {
			if (printProgress==1) {
				fprintf(options.terminalStream,"Percentage converted: %3d%%%10s%c",100,"",options.ProgressEndCharac);
				#if !defined(__WIN32__)
					//This is to clear terminal for characters after finishing (in Windows is not necessary as it adds a newline when the process finishes)
					if (options.ProgressEndCharac=='\r') {
						fprintf(options.terminalStream,"%60s%c","",options.ProgressEndCharac);
					}
					//Enable cursor again
					if (sopt.disableCursor==1) {
						fprintf(options.terminalStream,"%s",enableCursor);
					}
				#endif
				fflush(options.terminalStream);
			}
			if (epoch->t.MJDN==-1) {
				printError("Observation file only has header data (no epochs)",&options);
			} else if(tdiff(&epoch->t,&options.StartEpoch)<0.) {
				printError("Start epoch provided by user is ahead of all observation file records",&options);
			} else {
				printError("Orbit and clock products are of a different time than the observation RINEX",&options);
			}
		}
	} else if (options.workMode == wmSBASPLOTS ) {
		//////////////////////////
		///SBAS Plots mode
		/////////////////////////

		HourFileName[0]='\0';

		//Select GEO and print it
		if(options.GEOindex==-1) {
			if(SBASdatabox.SBASdata[0].numSBASsatellites==0) {
				//No GEO available. Print Error
				sprintf(messagestr,"No SBAS GEO satellite found in file [%s]",sopt.sbasFile);
				printError(messagestr,&options);
			} else if(options.GEOPRN==-1) {
				//User didn't provide any input. Use the first GEO read as default
				options.GEOindex=1;
				options.GEOPRN=SBASdatabox.SBASdata[options.GEOindex].PRN;
			} else if (options.GEOPRN==0) {
				//Use data from all GEO
				options.GEOindex=0;
				options.GEOPRN=SBASdatabox.SBASdata[options.GEOindex].PRN;
			} else if (options.GEOPRN==1) {
				//Use the GEO PRN from the first SBAS data read, which will be in position one of the SBASdata vector
				options.GEOindex=1;
				options.GEOPRN=SBASdatabox.SBASdata[options.GEOindex].PRN;
			} else { //MINGEOPRN<=options->GEOPRN<=MAXGEOPRN
				//The user has given the GEO PRN
				options.GEOindex=SBASdatabox.SBASdata[0].GEOPRN2pos[options.GEOPRN];
				if(options.GEOindex==-1) {
					//We have no data from this satellite. Print Error
					sprintf(messagestr,"SBAS GEO PRN %3d not found in file [%s]",options.GEOPRN,sopt.sbasFile);
					printError(messagestr,&options);
				}
			}
		}
		if(options.switchGEO==1) {
			sprintf(messagestr,"Initial GEO-PRN selected for SBAS corrections: %3d (it may change during processing)",options.GEOPRN);
		} else {
			sprintf(messagestr,"GEO-PRN for SBAS corrections: %3d",options.GEOPRN);
		}
		printInfo(messagestr,&options);

		messagestr[0]='\0';
		auxstr[0]='\0';
		for(i=MINGEOPRN;i<=MAXGEOPRN;i++) {
			if (options.GEOPRNunsel[i]==1) {
				sprintf(messagestr,"%s %3d",auxstr,i);
				sprintf(auxstr,"%s",messagestr);
				excludedGEOs=1;
			}
		}
		if (excludedGEOs==1) {
			sprintf(messagestr,"GEO-PRN excluded:%s",auxstr);
			printInfo(messagestr,&options);
		}

		sprintf(messagestr,"SBAS GEO switching: %3s",options.switchGEO==1?"ON":"OFF");
		printInfo(messagestr,&options);
		#if defined _OPENMP
			sprintf(messagestr,"Number of threads used: %d",options.numthreads);
			printInfo(messagestr,&options);
		#endif

		//Open output files
		if(options.NoAvailabilityPlot==0) {
			//Show warning message to advert users of the long computation time needed
			sprintf(messagestr,"WARNING: SBAS Availability plots requires a lot of computation time. With the default options it takes around 2 hours");
			printInfo(messagestr,&options);

			//Create directory recursively if needed
			ret=mkdir_recursive(sopt.sbasAvailplotsFile);
			if(ret!=0) {
			   //Error when creating the directory, and it is not due to that the directory already exists
			   sprintf(messagestr,"When creating [%s] folder for writing SBAS availability plot file",sopt.sbasAvailplotsFile);
			   printError(messagestr,&options);
			}
			fdSBASAvail=fopen(sopt.sbasAvailplotsFile,"w");
			if(fdSBASAvail==NULL) {
				sprintf(messagestr,"Opening output file [%s] for SBAS availability plot",sopt.sbasAvailplotsFile);
				printError(messagestr,&options);
			}
			//Open 24 hours availability plot files if necessary
			if(options.SBASHourlyMaps==1) {
				for(i=0;i<24;i++) {
					fdSBASAvailHour[i]=NULL;
					sprintf(HourFileName,"%s_%02dh.txt",sopt.sbasAvailplotsFileNoExtension,i);
					fdSBASAvailHour[i]=fopen(HourFileName,"w");
					if(fdSBASAvailHour[i]==NULL) {
						sprintf(messagestr,"Opening output file [%s] for SBAS availability plot for hour %02d",HourFileName,i);
						printError(messagestr,&options);
					}
				}
			}
		}

		if(options.NoContRiskPlot==0) {
			//Create directory recursively if needed
			ret=mkdir_recursive(sopt.sbasRiskplotsFile);
			if(ret!=0) {
			   //Error when creating the directory, and it is not due to that the directory already exists
			   sprintf(messagestr,"When creating [%s] folder for writing SBAS continuity risk plot file",sopt.sbasRiskplotsFile);
			   printError(messagestr,&options);
			}
			fdSBASRisk=fopen(sopt.sbasRiskplotsFile,"w");
			if(fdSBASRisk==NULL) {
				sprintf(messagestr,"Opening output file [%s] for SBAS continuity risk plots",sopt.sbasRiskplotsFile);
				printError(messagestr,&options);
			}
			//Open 24 hours continuity risk plot files if necessary
			if(options.SBASHourlyMaps==1) {
				for(i=0;i<24;i++) {
					fdSBASRiskHour[i]=NULL;
					sprintf(HourFileName,"%s_%02dh.txt",sopt.sbasRiskplotsFileNoExtension,i);
					fdSBASRiskHour[i]=fopen(HourFileName,"w");
					if(fdSBASRiskHour[i]==NULL) {
						sprintf(messagestr,"Opening output file [%s] for SBAS continuity risk plot for hour %02d",HourFileName,i);
						printError(messagestr,&options);
					}
				}
			}

			//Create directory recursively if needed
			ret=mkdir_recursive(sopt.sbasDiscontinuityFile);
			if(ret!=0) {
			   //Error when creating the directory, and it is not due to that the directory already exists
			   sprintf(messagestr,"When creating [%s] folder for writing SBAS solution discontinuities file",sopt.sbasDiscontinuityFile);
			   printError(messagestr,&options);
			}
			fdSBASDiscont=fopen(sopt.sbasDiscontinuityFile,"w");
			if(fdSBASDiscont==NULL) {
				sprintf(messagestr,"Opening output file [%s] for SBAS solution discontinuities",sopt.sbasDiscontinuityFile);
				printError(messagestr,&options);
			} else {
				t2doy(&epoch->t,&SBASPlotYear,&SBASPlotDoY);
				//Write file header file.
				if (options.switchGEO==1) {
					GEOused=0;
				} else {
					GEOused=options.GEOPRN;
				}
				fprintf(fdSBASDiscont,"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR GEO-PRN ELEV-MASK\n");
				fprintf(fdSBASDiscont," %6.2f %6.2f %7.2f %7.2f %10.2f %10.2f %6.2f %6.2f %03d %4d %7d %9.2f\n",options.minLatplots,options.maxLatplots,options.minLonplots,options.maxLonplots,options.AvailabilityPlotStep,options.SBASPlotsRecHeight,options.HorAlarmLimit,options.VerAlarmLimit,(int)SBASPlotDoY,SBASPlotYear,GEOused,options.elevationMask*r2d);
				fprintf(fdSBASDiscont,"#  LAT     LON INIT-EPOCH END-EPOCH DURATION STABLE-PERIOD\n"); 
			}
			//Open 24 hours discontinuity files if necessary
			if(options.SBASHourlyMaps==1) {
				for(i=0;i<24;i++) {
					fdSBASDiscontHour[i]=NULL;
					sprintf(HourFileName,"%s_%02dh.txt",sopt.sbasDiscontinuityFileNoExtension,i);
					fdSBASDiscontHour[i]=fopen(HourFileName,"w");
					if(fdSBASDiscontHour[i]==NULL) {
						sprintf(messagestr,"Opening output file [%s] for SBAS solution discontinuities for hour %02d",HourFileName,i);
						printError(messagestr,&options);
					} else {
						t2doy(&epoch->t,&SBASPlotYear,&SBASPlotDoY);
						//Write file header file.
						fprintf(fdSBASDiscontHour[i],"#MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR GEO-PRN ELEV-MASK HOUR\n");
						fprintf(fdSBASDiscontHour[i]," %6.2f %6.2f %7.2f %7.2f %10.2f %10.2f %6.2f %6.2f %03d %4d %7d %9.2f   %02d\n",options.minLatplots,options.maxLatplots,options.minLonplots,options.maxLonplots,options.AvailabilityPlotStep,options.SBASPlotsRecHeight,options.HorAlarmLimit,options.VerAlarmLimit,(int)SBASPlotDoY,SBASPlotYear,options.GEOPRN,options.elevationMask*r2d,i);
						fprintf(fdSBASDiscontHour[i],"#  LAT     LON INIT-EPOCH END-EPOCH DURATION STABLE-PERIOD\n"); 
					
					}
				}
			}
		}

		if(options.NoIonoPlot==0) {
			//Create directory recursively if needed
			ret=mkdir_recursive(sopt.sbasIonoplotsFile);
			if(ret!=0) {
			   //Error when creating the directory, and it is not due to that the directory already exists
			   sprintf(messagestr,"When creating [%s] folder for writing SBAS ionosphere correction availability plot file",sopt.sbasIonoplotsFile);
			   printError(messagestr,&options);
			}
			fdSBASIono=fopen(sopt.sbasIonoplotsFile,"w");
			if(fdSBASIono==NULL) {
				sprintf(messagestr,"Opening output file [%s] for SBAS ionosphere correction availability plots",sopt.sbasIonoplotsFile);
				printError(messagestr,&options);
			}
			//Open 24 hours iono plot files if necessary
			if(options.SBASHourlyMaps==1) {
				for(i=0;i<24;i++) {
					fdSBASIonoHour[i]=NULL;
					sprintf(HourFileName,"%s_%02dh.txt",sopt.sbasIonoplotsFileNoExtension,i);
					fdSBASIonoHour[i]=fopen(HourFileName,"w");
					if(fdSBASIonoHour[i]==NULL) {
						sprintf(messagestr,"Opening output file [%s] for SBAS continuity risk plot for hour %02d",HourFileName,i);
						printError(messagestr,&options);
					}
				}
			}
		}
		
		//Read RINEX navigation data
		if ( readRinexNav(fdRNXnav,&products,&rinexNavVersion) != 1 ) {
			if ( (int)rinexNavVersion > 3 && rinexNavVersion != 0 ) {
				sprintf(messagestr,"RINEX navigation version %1.2f from file [%s] is not supported. Supported versions are 2 and 3",rinexNavVersion,sopt.navFile[0]);
				printError(messagestr,&options);
			} else {
				sprintf(messagestr,"Reading RINEX navigation message file [%s]",sopt.navFile[0]);
				printError(messagestr,&options);
			}
		}


		//Allocate memory for TSBASplots and initialize this structure and also TEpoch for this mode
		SBASplots=malloc(sizeof(TSBASPlots));
		initSBASPlotsMode(epoch,SBASplots,&options,&ret1);
		if(ret1==-1) {
			if(options.NoAvailabilityPlot==0 && options.NoIonoPlot==0) {				
				if (options.SBASHourlyMaps==1) {
					printError("Not enough memory available for SBAS plots. Try disabling hourly maps, reducing resolution, map size or just doing only one plot a time",&options);
				} else {
					printError("Not enough memory available for SBAS plots. Try reducing resolution, map size or just doing only one plot a time",&options);
				}
			} else {
				if (options.SBASHourlyMaps==1) {
					printError("Not enough memory available for SBAS plots. Try disabling hourly maps, reducing resolution or map size",&options);
				} else {
					printError("Not enough memory available for SBAS plots. Try reducing resolution or map size",&options);
				}
			}
		}

		//Initialize counter for number of epochs
		InitialSBASPlotsEpoch=(int)epoch->t.SoD;
		totalAvailabilityEpochs=0;
		totalAvailabilityEpochsHourly=0;
		totalIonoEpochs=0;
		totalIonoEpochsHourly=0;
		epoch->SwitchPossible=0; //Set by default no GEO switching (user input will be checked later)

		//Compute number of loops to compute percentage
		epoch->numEpochsfile=(86400-InitialSBASPlotsEpoch);
		epoch->numEpochsprocessed=-1;
		epoch->CurrentPercentage=0.;
		epoch->PreviousPercentage=-0.2; //This is to make percentage appear with 0.0%, as it takes some time to get to 0.1%

		//Compute SBAS plots. We need to do three loops: one for the time, one for the latitude and another for the longitude
		//Loop for time. From second 0 if SBAS file started at second 0 or at the end of the previous day, or otherwise from the first epoch of the SBAS data file.
		//The final epoch wiil be always the end of the day (second of day 86399)
		for(currenttime=InitialSBASPlotsEpoch;currenttime<86400;currenttime++) {
			//Update current time
			epoch->t.SoD=(double)currenttime;
			//Update progress bar
			if (printProgress) { 
				epoch->numEpochsprocessed++;
				epoch->CurrentPercentage=100.*epoch->numEpochsprocessed/epoch->numEpochsfile;
				if ((epoch->CurrentPercentage-epoch->PreviousPercentage)>=0.1) {
					Epochsleft=86400-currenttime;
					if (options.ProgressEndCharac=='\r') {
						//Printing to a terminal
						fprintf(options.terminalStream,"Current Epoch: %d (%d epochs left) / %02d:%02d:%02d (%02d:%02d:%02d left) (%.1f%%)%10s%c",currenttime,Epochsleft,(int)(currenttime/3600.),(int)(currenttime/60.)%60,currenttime%60,(int)(Epochsleft/3600.),(int)(Epochsleft/60)%60,Epochsleft%60,epoch->CurrentPercentage,"",options.ProgressEndCharac);
						fflush(options.terminalStream);
					} else {
						//Printing for the GUI. Only print if the integer of the percentage have changed (to avoid message spamming)
						if ((int)epoch->CurrentPercentage!=(int)epoch->PreviousPercentage) {
							fprintf(options.terminalStream,"Current Epoch: %5d (%5d epochs left) / %02d:%02d:%02d (%02d:%02d:%02d left) (%5.1f%%)%10s%c",currenttime,Epochsleft,(int)(currenttime/3600.),(int)(currenttime/60.)%60,currenttime%60,(int)(Epochsleft/3600.),(int)(Epochsleft/60)%60,Epochsleft%60,epoch->CurrentPercentage,"",options.ProgressEndCharac);
							fflush(options.terminalStream);
						}
					}
					epoch->PreviousPercentage=epoch->CurrentPercentage;
				}
			}
			
			// Read SBAS data until current epoch	
			retsbas = readSBASFile(sopt.sbasFile,&SBASdatabox,&rinexBVersion,&epoch->t,&options);
			if(retsbas==-2) {
				//Reached End of file before getting to current epoch
				if(currenttime<86399) {
					//If it not the last epoch stop processing
					epoch->t.SoD=(double)(currenttime-1);
					break;
				}
			}
			if(options.SBASHourlyMaps==1) {
				if(options.NoAvailabilityPlot==0) {
					if (currenttime%3600==0) {
						//We are the beginning of the hour
						if (currenttime!=InitialSBASPlotsEpoch) {
							//It is not the first epoch
							currenthour=(int)((double)(currenttime)/3600.)-1;
							writeSBASAvailFile(fdSBASAvailHour[currenthour],fdSBASRiskHour[currenthour],fdSBASDiscontHour[currenthour],epoch,SBASplots,totalAvailabilityEpochsHourly,currenthour,&options);
							fclose(fdSBASAvailHour[currenthour]);
							if (options.NoContRiskPlot==0) {
								fclose(fdSBASRiskHour[currenthour]);
								fclose(fdSBASDiscontHour[currenthour]);
							}
							for(k=0;k<SBASplots->AvailabilityLatSize;k++) {
								for(l=0;l<SBASplots->AvailabilityLonSize;l++) {
									SBASplots->SBASNumEpochsAvailHourly[k][l]=0;
									if(options.NoContRiskPlot==0) {
										SBASplots->SBASNumEpochsRiskHourly[k][l]=0;
										SBASplots->FirstEpochAvailAfterPrevDiscHourly[k][l]=0;
										SBASplots->LastEpochAvailPrevCurrDiscHourly[k][l]=0;
									}
								}
							}
							totalAvailabilityEpochsHourly=0;
						}
					}
				}
			}
			totalAvailabilityEpochsHourly++;

			totalAvailabilityEpochs++;
			if(options.NoAvailabilityPlot==0) {
				//Loop for latitude
				latPos=-1;
				for(latitude=options.minLatplots;latitude<=options.maxLatplots;latitude+=options.AvailabilityPlotStep) {
					//Compute latitude vector position
					latPos++;

					//Loop for longitude
					lonPos=-1;
					for(longitude=options.minLonplots;longitude<=options.maxLonplots;longitude+=options.AvailabilityPlotStep) {
						//Compute longitude vector position
						lonPos++;
						//Check inclusion and exclusion area
						if (options.NumSBASPlotsExclusionArea>0 && options.NumSBASPlotsInclusionArea>0) {
							//Inclusion area. Only do areas inside the given region
							InsideInclusionArea=0;
							for(k=0;k<options.NumSBASPlotsInclusionArea;k++) {
								if (longitude>=options.SBASPlotsInclusionAreaDelimeters[k][0] && longitude<=options.SBASPlotsInclusionAreaDelimeters[k][1]) {
									if (latitude>=options.SBASPlotsInclusionAreaDelimeters[k][2] && latitude<=options.SBASPlotsInclusionAreaDelimeters[k][3]) {
										InsideInclusionArea=1;
										break;
									}
								}
							}
							if (InsideInclusionArea==0) continue;
							//Exclusion area. Do not process area inside exclusion area
							InsideExclusionArea=0;
							for(k=0;k<options.NumSBASPlotsExclusionArea;k++) {
								if (longitude>=options.SBASPlotsExclusionAreaDelimeters[k][0] && longitude<=options.SBASPlotsExclusionAreaDelimeters[k][1]) {
									if (latitude>=options.SBASPlotsExclusionAreaDelimeters[k][2] && latitude<=options.SBASPlotsExclusionAreaDelimeters[k][3]) {
										InsideExclusionArea=1;
										break;
									}
								}
							}
							if (InsideExclusionArea==1) continue;
						} else if (options.NumSBASPlotsExclusionArea>0) {
							//Exclusion area. Do not process area inside exclusion area
							InsideExclusionArea=0;
							for(k=0;k<options.NumSBASPlotsExclusionArea;k++) {
								if (longitude>=options.SBASPlotsExclusionAreaDelimeters[k][0] && longitude<=options.SBASPlotsExclusionAreaDelimeters[k][1]) {
									if (latitude>=options.SBASPlotsExclusionAreaDelimeters[k][2] && latitude<=options.SBASPlotsExclusionAreaDelimeters[k][3]) {
										InsideExclusionArea=1;
										break;
									}
								}
							}
							if (InsideExclusionArea==1) continue;
						} else if (options.NumSBASPlotsInclusionArea>0) {
							//Inclusion area. Only do areas inside the given region
							InsideInclusionArea=0;
							for(k=0;k<options.NumSBASPlotsInclusionArea;k++) {
								if (longitude>=options.SBASPlotsInclusionAreaDelimeters[k][0] && longitude<=options.SBASPlotsInclusionAreaDelimeters[k][1]) {
									if (latitude>=options.SBASPlotsInclusionAreaDelimeters[k][2] && latitude<=options.SBASPlotsInclusionAreaDelimeters[k][3]) {
										InsideInclusionArea=1;
										break;
									}
								}
							}
							if (InsideInclusionArea==0) continue;
						}
					
						//Reset number of switches (in normal positioning mode, num switches is tied to epoch, not to latitude and longitude)
						epoch->ResetNumSwitch=1;

						//If print SBASUNSEL message is activated, print an INFO message showing the current latitude and longitude
						if ( options.printSBASUNSEL == 1 ) {
							printf("INFO Latitude %6.2f Longitude %7.2f\n",latitude,longitude);
						}

						//Set available satellites to 0
						epoch->usableSatellites=0;
						epoch->numsatdiscardedSBAS=0;
						
						//Transform from latitude, longitude, height to XYZ. If non height value set, we will assume we are on height 0 (sea level)
						epoch->receiver.aproxPositionNEU[0]=latitude*d2r;
						epoch->receiver.aproxPositionNEU[1]=longitude*d2r;
						epoch->receiver.aproxPositionNEU[2]=options.SBASPlotsRecHeight;
						NEU2XYZ(epoch->receiver.aproxPositionNEU,epoch->receiver.aproxPosition);
						fillGroundStationOrientation(epoch);

						if (options.switchGEO == 1) epoch->SwitchPossible=1;	//Enable switches in current epoch (only applicable if mode or GEO switch is enabled)
						//Do While loop to allow switching GEO in processing
						do {
							//Model each satellite. Unselect it if it is not in view or below the elevation mask
							#pragma omp parallel for private(ret1,SBAScorr)
							for(i=0;i<epoch->numSatellites;i++) {
								// Check if satellite has been deselected
								if (!options.includeSatellite[epoch->sat[i].GNSS][epoch->sat[i].PRN]) {
									epoch->sat[i].available=0;
									continue;
								}
								//Initialize SBAScorr struct
								initSBAScorrections(&SBAScorr);	

								epoch->sat[i].available=1; //Set the satellite as available
								ret1 = computeSBAS(epoch,&products,NULL,NULL,NULL,NULL,NULL,i,C1C,0,SBASdatabox.SBASdata,&SBAScorr,&options);
								if ( ret1 <= 0 ) {
									epoch->sat[i].available=0;
									if (ret1!=-46 && ret1!=-47) { //Return -46 and -47 are discarded satellites due to elevation mask or not visible
										#pragma omp atomic
										epoch->numsatdiscardedSBAS++;
									}
								} else {
									//Save SBAS sigma in epoch structure
									//Sanity check for the case all the sigmas are set to 0
									if(SBAScorr.SBASsatsigma2==0.) {
										//Set a sigma of 1 mm to avoid dividing by 0
										SBAScorr.SBASsatsigma2=0.001*0.001;
									}
									epoch->sat[i].measurementWeights[0]=sqrt(SBAScorr.SBASsatsigma2);
									#pragma omp atomic
									epoch->usableSatellites++;
								}

								if ( options.printSBASUNSEL == 1 ) {
									if(ret1==1) ret1=0;
									printSBASUNSEL(epoch,i,ret1,SBASdatabox.SBASdata,&SBAScorr,&options);
								}
							}

							if(epoch->usableSatellites>=4) {
								currenthour=(int)((double)(currenttime)/3600.);
								calculateSBASAvailability(fdSBASDiscont,fdSBASDiscontHour[currenthour],latPos,lonPos,latitude,longitude,epoch,SBASplots,&options);
								retsbas=0;
								break; //Get out of the do while loop
							} else if (epoch->SwitchPossible==1) {
								retsbas = SwitchSBASGEOMode(epoch,epoch->usableSatellites,epoch->numsatdiscardedSBAS,SBASdatabox.SBASdata,&options);
							} else {
								retsbas=0;
								break;
							}
						 } while (retsbas==1); //Repeat loop only if GEO has changed
					}
				}
			}
			//Compute SBAS iono corrections availability every 5 minutes (300 seconds)
			if(options.NoIonoPlot==0) {
				if(currenttime%options.IonoPlotTimeStep==0) {
					totalIonoEpochs++;
					if(options.SBASHourlyMaps==1) {
						if (currenttime%3600==0) {
							//We are the beginning of the hour
							if (currenttime!=InitialSBASPlotsEpoch) {
								//It is not the first epoch
								currenthour=(int)((double)(currenttime)/3600.)-1;
								writeSBASIonoAvailFile(fdSBASIonoHour[currenthour],epoch,SBASplots,totalIonoEpochsHourly,currenthour,&options);
								fclose(fdSBASIonoHour[currenthour]);
								for(k=0;k<SBASplots->IonoLatSize;k++) {
									for(l=0;l<SBASplots->IonoLonSize;l++) {
										SBASplots->IonoNumEpochsAvailHourly[k][l]=0;
									}
								}
								totalIonoEpochsHourly=0;
							}
						}
					}
					totalIonoEpochsHourly++;
					//Loop for latitude
					latPos=-1;
					for(latitude=options.minLatplots;latitude<=options.maxLatplots;latitude+=options.IonoPlotStep) {
						latPos++;

						//Loop for longitude
						lonPos=-1;
						for(longitude=options.minLonplots;longitude<=options.maxLonplots;longitude+=options.IonoPlotStep) {
							lonPos++;
							if (options.NumSBASPlotsExclusionArea>0 && options.NumSBASPlotsInclusionArea>0) {
								//Inclusion area. Only do areas inside the given region
								InsideInclusionArea=0;
								for(k=0;k<options.NumSBASPlotsInclusionArea;k++) {
									if (longitude>=options.SBASPlotsInclusionAreaDelimeters[k][0] && longitude<=options.SBASPlotsInclusionAreaDelimeters[k][1]) {
										if (latitude>=options.SBASPlotsInclusionAreaDelimeters[k][2] && latitude<=options.SBASPlotsInclusionAreaDelimeters[k][3]) {
											InsideInclusionArea=1;
											break;
										}
									}
								}
								if (InsideInclusionArea==0) continue;
								//Exclusion area. Do not process area inside exclusion area
								InsideExclusionArea=0;
								for(k=0;k<options.NumSBASPlotsExclusionArea;k++) {
									if (longitude>=options.SBASPlotsExclusionAreaDelimeters[k][0] && longitude<=options.SBASPlotsExclusionAreaDelimeters[k][1]) {
										if (latitude>=options.SBASPlotsExclusionAreaDelimeters[k][2] && latitude<=options.SBASPlotsExclusionAreaDelimeters[k][3]) {
											InsideExclusionArea=1;
											break;
										}
									}
								}
								if (InsideExclusionArea==1) continue;
							} else if (options.NumSBASPlotsExclusionArea>0) {
								//Exclusion area. Do not process area inside exclusion area
								InsideExclusionArea=0;
								for(k=0;k<options.NumSBASPlotsExclusionArea;k++) {
									if (longitude>=options.SBASPlotsExclusionAreaDelimeters[k][0] && longitude<=options.SBASPlotsExclusionAreaDelimeters[k][1]) {
										if (latitude>=options.SBASPlotsExclusionAreaDelimeters[k][2] && latitude<=options.SBASPlotsExclusionAreaDelimeters[k][3]) {
											InsideExclusionArea=1;
											break;
										}
									}
								}
								if (InsideExclusionArea==1) continue;
							} else if (options.NumSBASPlotsInclusionArea>0) {
								//Inclusion area. Only do areas inside the given region
								InsideInclusionArea=0;
								for(k=0;k<options.NumSBASPlotsInclusionArea;k++) {
									if (longitude>=options.SBASPlotsInclusionAreaDelimeters[k][0] && longitude<=options.SBASPlotsInclusionAreaDelimeters[k][1]) {
										if (latitude>=options.SBASPlotsInclusionAreaDelimeters[k][2] && latitude<=options.SBASPlotsInclusionAreaDelimeters[k][3]) {
											InsideInclusionArea=1;
											break;
										}
									}
								}
								if (InsideInclusionArea==0) continue;
							}
							//Initialize SBAScorr struct
							initSBAScorrections(&SBAScorr);	
							//Set flag to indicate that we are just computing SBAS iono availability
							//In this case, the Pierce Point is given by our current latitude and longitude
							SBAScorr.SBASplotIonoAvail=1;
							//Reset number of switches (in normal positioning mode, num switches is tied to epoch, not to latitude and longitude)
							epoch->ResetNumSwitch=1;
							if (options.switchGEO == 1) epoch->SwitchPossible=1;	//Enable switches in current epoch (only applicable if mode or GEO switch is enabled)
							//Save Pierce Point in epoch structure
							epoch->IPPlat=latitude;
							epoch->IPPlon=longitude;
							//Do While loop to allow switching GEO in processing
							do {
								//Compute Iono availability. As we are fixing the Pierce Point, we only need to do it for one satellite
								ret1 = SBASIonoModel(epoch,&products,0,&ionoerror,&SBAScorr,SBASdatabox.SBASdata,&options);	
								//Save result
								if(ret1!=9999 && ionoerror==1) {
									//Ionosphere available
									SBASplots->IonoNumEpochsAvail[latPos][lonPos]++;
									if(options.SBASHourlyMaps==1) {
										SBASplots->IonoNumEpochsAvailHourly[latPos][lonPos]++;
									}
									retsbas=0;
									break;
								} else if (epoch->SwitchPossible==1) {
									//Set 100 satellites discarded by SBAS to let know the function SwitchSBASGEOMode
									//that we want to change GEO in the computation of SBAS Iono availability
									retsbas = SwitchSBASGEOMode(epoch,3,100,SBASdatabox.SBASdata,&options); 
								} else {
									retsbas=0;
									break;
								}
							} while (retsbas==1); //Repeat loop only if GEO has changed
						}
					}
				}
			}
		} //End for loop of time

		//Write files and close them
		if(options.NoAvailabilityPlot==0) {
			writeSBASAvailFile(fdSBASAvail,fdSBASRisk,fdSBASDiscont,epoch,SBASplots,totalAvailabilityEpochs,-1,&options);
			fclose(fdSBASAvail);
			if(options.NoContRiskPlot==0) {
				fclose(fdSBASRisk);
				fclose(fdSBASDiscont);
			}
			if(options.SBASHourlyMaps==1) {
				writeSBASAvailFile(fdSBASAvailHour[23],fdSBASRiskHour[23],fdSBASDiscontHour[23],epoch,SBASplots,totalAvailabilityEpochsHourly,23,&options);
				fclose(fdSBASAvailHour[23]);
				if(options.NoContRiskPlot==0) {
					fclose(fdSBASRiskHour[23]);
					fclose(fdSBASDiscontHour[23]);
				}
			}

		}
		if(options.NoIonoPlot==0) {
			writeSBASIonoAvailFile(fdSBASIono,epoch,SBASplots,totalIonoEpochs,-1,&options);
			fclose(fdSBASIono);
			if(options.SBASHourlyMaps==1) {
				//Write the remaining file of hour 23
				writeSBASIonoAvailFile(fdSBASIonoHour[23],epoch,SBASplots,totalIonoEpochsHourly,23,&options);
				fclose(fdSBASIonoHour[23]);
			}

		}

		//Free memory
		if(options.NoAvailabilityPlot==0) {
			for(i=0;i<SBASplots->AvailabilityLatSize;i++) {
				free(SBASplots->SBASNumEpochsAvail[i]);
				if (options.SBASHourlyMaps==1) {
					free(SBASplots->SBASNumEpochsAvailHourly[i]);
				}
			}
			free(SBASplots->SBASNumEpochsAvail);
			if (options.SBASHourlyMaps==1) {
				free(SBASplots->SBASNumEpochsAvailHourly);
			}
			if(options.NoContRiskPlot==0) {
				for(i=0;i<SBASplots->AvailabilityLatSize;i++) {
					free(SBASplots->SBASNumEpochsRisk[i]);
					free(SBASplots->LastEpochAvailPrevCurrDisc[i]);
					free(SBASplots->FirstEpochAvailAfterPrevDisc[i]);
					if (options.SBASHourlyMaps==1) {
						free(SBASplots->SBASNumEpochsRiskHourly[i]);
						free(SBASplots->LastEpochAvailPrevCurrDiscHourly[i]);
						free(SBASplots->FirstEpochAvailAfterPrevDiscHourly[i]);
					}
				}
				free(SBASplots->SBASNumEpochsRisk);
				free(SBASplots->LastEpochAvailPrevCurrDisc);
				free(SBASplots->FirstEpochAvailAfterPrevDisc);
				if (options.SBASHourlyMaps==1) {
					free(SBASplots->SBASNumEpochsRiskHourly);
					free(SBASplots->LastEpochAvailPrevCurrDiscHourly);
					free(SBASplots->FirstEpochAvailAfterPrevDiscHourly);
				}
			}
		}
		if(options.NoIonoPlot==0) {
			for(i=0;i<SBASplots->IonoLatSize;i++) {
				free(SBASplots->IonoNumEpochsAvail[i]);
				if (options.SBASHourlyMaps==1) {
					free(SBASplots->IonoNumEpochsAvailHourly[i]);
				}
			}
			free(SBASplots->IonoNumEpochsAvail);
			if (options.SBASHourlyMaps==1) {
				free(SBASplots->IonoNumEpochsAvailHourly);
			}
		}
		free(SBASplots);

	} //End if (options.workMode == wmSBASPLOTS )

	if (printProgress) {
		if (options.workMode == wmSBASPLOTS ) {
			if (options.ProgressEndCharac=='\r') {
				fprintf(options.terminalStream,"Current Epoch: %d (0 epochs left) / %02d:%02d:%02d (00:00:00 left) (100%%)%10s%c",currenttime,(int)(currenttime/3600.),(int)(currenttime/60.)%60,currenttime%60,"",options.ProgressEndCharac);
			} else {
				fprintf(options.terminalStream,"Current Epoch: %5d (%5d epochs left) / %02d:%02d:%02d (00:00:00 left) (%5.1f)%10s%c",currenttime,0,(int)(currenttime/3600.),(int)(currenttime/60.)%60,currenttime%60,100.0,"",options.ProgressEndCharac);
			}
		} else if ( options.workMode != wmCOMPAREORBITS && options.workMode != wmSHOWPRODUCT ) {
			fprintf(options.terminalStream,"%.56s (100%%)%10s%c",Epochstr,"",options.ProgressEndCharac);
		}
		//The fflush of the terminal is to avoid flickering of the cursor due to the high output write rate
		fflush(options.terminalStream);
		#if !defined (__WIN32__)
			//This is to clear terminal for characters after finishing (in Windows is not necessary as it adds a newline when the process finishes)
			fprintf(options.terminalStream,"%70s%c","",options.ProgressEndCharac); 
			//Enable cursor if necessary
			if (sopt.disableCursor==1) {
				fprintf(options.terminalStream,"%s",enableCursor);
			}
			fflush(options.terminalStream);
		#endif
	}

	// We might have the case that the observation file has been processed but there is still data in the SBAS file.
	// If we have to print a RINEXB, or EMS or Pegasus file, then we have to read the rest of the file
	if ( options.SBAScorrections == 1 && (options.writeRinexBfile || options.writeEMSfile || options.writePegasusfile) ) {
		epoch->t.MJDN = -2;
		epoch->t.SoD  = 0.0;
		readSBASFile(sopt.sbasFile,&SBASdatabox,&rinexBVersion,&epoch->t,&options);
	}

	// Close files
	if ( fdRNX != NULL)		fclose(fdRNX);
	if ( fdRNXnav != NULL)	fclose(fdRNXnav);
	if ( fdRNXNeq != NULL )	fclose(fdRNXNeq);
	if ( fdRNXKlb != NULL )	fclose(fdRNXKlb);
	if ( fdRNXBei != NULL)	fclose(fdRNXBei);
	if ( fdSP3 != NULL )	fclose(fdSP3);
	if ( fdSP3o != NULL )	fclose(fdSP3o);
	if ( fdCLK != NULL )	fclose(fdCLK);
	if ( fdRTCM != NULL )	fclose(fdRTCM);
	if ( fdRTCM2 != NULL )	fclose(fdRTCM2);
	if ( fdRTCM3 != NULL )	fclose(fdRTCM3);
	if ( options.DGNSS ) {
		free(epochDGNSS);
	}

	if (options.stanfordesa>=3) {
		//Enable again Stanford-ESA if it had been disabled in DGNSS mode when solution is in SPP or due to no position from reference file
		options.stanfordesa=1;
	}

	if ( options.stanfordesa == 1 ) {

		// Write Stanford-ESA values
		writeStdESA(fdstdESA,&StdESA,&options);

		fclose(fdstdESA);
		if (options.stanfordesaLOI == 1) {
			fclose(options.fdstdESALOI);
		}

		for ( i = 0; i < StdESA.numpixelver; i++ ) {
			free(StdESA.counthor[i]);
			free(StdESA.countver[i]);
		}
		free(StdESA.counthor);
		free(StdESA.countver);
	}

	if(options.fdkml!=NULL) {
		//Insert XML closing tags and close file
		writeKMLtags(options.fdkml,epoch,sopt.obsFile,1,0,VERSION,&options);
	}

	if(options.fdkml0!=NULL) {
		//Insert XML closing tags and close file
		writeKMLtags(options.fdkml0,epoch,sopt.obsFile,1,1,VERSION,&options);
	}


	//Free memory for KML data
	if (options.fdkml!=NULL || options.fdkml0!=NULL) {
		for(i=0;i<epoch->numKMLData;i++) {
			free(epoch->KMLData[i]);
		}

		for(i=0;i<options.numKMLTimeRanges;i++) {
			free(options.KMLtimeranges[i]);
		}
		free(options.KMLtimeranges);

		free(epoch->KMLData);
		free(epoch->KMLTime);

		if(options.fdkml!=NULL) {
			fclose(options.fdkml);
		}
		if(options.fdkml0!=NULL) {
			fclose(options.fdkml0);
		}
	}

	if(fdOutSP3!=NULL) {
		//Insert EOF at the end and close file
		writeSP3file(fdOutSP3,epoch, &solution,&prevUnkinfo,1,VERSION,&options);
		fclose(fdOutSP3);
	}

	// Print SBAS summary
	if (options.useDatasummary == 1 || (options.printSummary==1 && Summary==1)) {
	   	if (options.SBAScorrections == 1 && options.onlySBASiono == 0) {
			printSBASSummary(UseReferenceFile,epoch,&SBASdatabox,&StdESA,&options);
		} else if (options.DGNSS==1) {
			printDGNSSSummary(UseReferenceFile,epoch,&StdESA,&options);
		} else {
			printSummary(UseReferenceFile,epoch,&StdESA,&options);
		}
		//Free memory
		if (options.recPosProvided==1) {
			free(epoch->HError);
			free(epoch->VError);
		}
	}
	free(SBASdatabox.SBASdata);
	free(epoch);

	return 0;
}
