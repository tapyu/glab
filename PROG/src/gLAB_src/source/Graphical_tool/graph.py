#!/usr/bin/python
# -*- coding: UTF-8 -*- 

#############################################################################
#  Copyright & License:
#  ====================
#   
#  Copyright 2009-2018 gAGE/UPC & ESA 
#   
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#   
#  http://www.apache.org/licenses/LICENSE-2.0
#   
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#############################################################################

#############################################################################
# Copyright: gAGE/UPC & ESA
# Project: EDUNAV GNSS Lab Tool
# Supervisor: Jaume Sanz Subirana (group of Astronomy and GEomatics - gAGE/UPC)
# Authors: Adria Rovira-Garcia (group of Astronomy and GEomatics - gAGE/UPC)
#          Pere Ramos-Bosch (group of Astronomy and GEomatics - gAGE/UPC)
# Curator: Adria Rovira-Garcia ( gAGE/UPC )
# Developer: Yixie Shao ( gAGE/UPC )
#            Deimos Ibanez Segura ( gAGE/UPC )
#          glab.gage @ upc.edu           
# File: graph.py
# Code Management Tool File Version: 5.2  Revision: 0
# Date: 2018/03/09
#############################################################################

#############################################################################
# MODULE DESCRIPTION
#
# Name: graph
# Language: python
#
# Purpose:
#  The purpose of this module is to generate a plot for a set of specified
#  input data.
#
# Function:
#  This program creates a window which will show a plot for the specified 
#  columns in a file. It allows to include conditions to select which files
#  to plot.
# 
# Dependencies:
#  None
#
# Files modified:
#  .plot.lock
#
# Files read:
#  None
#
# Resources usage:
#  See Design Document
#############################################################################

#############################################################################
#       RELEASE_HISTORY
# -------------
#          gLAB v1.3.0
# Release: 2009/12/10
# Change Log: First public version.
# -------------
#          gLAB v1.4.0
# Release: 2010/06/21
# Change Log: Save figure function added.
# -------------
#          gLAB v1.4.1
# Release: 2010/07/09
# Change Log: No changes in this file.
# -------------
#          gLAB v1.4.2
# Release: 2010/07/31
# Change Log: No changes in this file.
# -------------
#          gLAB v1.4.3
# Release: 2010/08/31
# Change Log: No changes in this file.
# -------------
#          gLAB v1.4.4
# Release: 2010/09/22
# Change Log: No changes in this file.
# -------------
#          gLAB v1.4.5
# Release: 2010/10/31
# Change Log: Minor Changes in help 
# -------------
#          gLAB v2.0.0
# Release: 2012/12/31
# Change Log: gLAB version released together with the Educational Book:
#             "GNSS Data Processing" (Vol. 1 and Vol. 2). ESA TM-23.
#             Authors: J. Sanz Subirana, J.M. Juan Zornoza and M. Hernandez-Pajares
#             ISBN: 978-92-9221-885-0 (two volumes)
#             ISSN: 1013-7076
#             December 2012.
# -------------
#          gLAB v2.2.0
# Release: 2014/09/22
# Change Log: No changes in this file.
# -------------
#          gLAB v2.2.1
# Release: 2014/12/23
# Change Log: No changes in this file.
# -------------
#          gLAB v2.2.2
# Release: 2015/03/02
# Change Log: No changes in this file.
# -------------
#          gLAB v2.2.3
# Release: 2015/05/28
# Change Log: No changes in this file.
# -------------
#          gLAB v2.2.4
# Release: 2015/07/01
# Change Log: No changes in this file.
# -------------
#          gLAB v2.2.5
# Release: 2015/10/20
# Change Log: When plot fails due to non-decimal values, the file .plot.lock is erased,
#               so gLAB_GUI.py "Plot" button doesn't get locked during 60 seconds. Also,
#               the error message has been clarified
#             In the Windows version (.exe binary), stdout has been redirected to stderr
#               so the help message is not lost
# -------------
#          gLAB v3.0.0
# Release: 2016/09/05
# Change Log: Added stanford plots and stanford-ESA plots
#             Added worst integrity ratio plots
#             Display environment in linux is not necessary when plot is saved to a file
#             It is now compatible with python 3
#             NOTE: The new plots (stanford and worst integrity ratio) need additional 
#                   python libraries (numpy and basemap), but they are not mandatory 
#                   if these plots are not used (for compatibility with previous versions)
# -------------
#          gLAB v3.1.0
# Release: 2016/09/26
# Change Log: Fixed a bug with input parameters due to bad space indentation 
# -----------
#          gLAB v3.1.1
# Release: 2016/10/21
# Change Log: Changed title name in Stanford-ESA plots from '# epochs' to '# samples'.
#             Fixed Stanford-ESA plots, which was horizontal protection levels from vertical plots and viceversa.
#             Added quantization check in Stanford plots generation for points greater than the
#                maximum X and Y. For example, (60,100) and (100,60) with a max X and Y of 50, 
#                would both result in the plot in the point (50,50) or (Xmax,Ymax), which made
#                it impossible to distinguish the MI from the non-MI. Now, MI points will result
#                in (Xmax,Ymax) while non MI will result in (Xmax-1,Ymax)
# -----------
#          gLAB v4.0.0
# Release: 2017/03/03
# Change Log: Added SBAS plots.
#             Added option to make a map with the station names in WIR maps mode.
#             Added many checks to prevent errors from user input.
#             Added check of X Display in Linux when not saving picture to file.
#             Added option to change the number of points shown in the label.
#             Added option to change the label position.
#             Added option to show number of MIs in worst integrity plot with coloured rings, 
#               using parameters '--mih' and --miv'.
#             Added new plot: World maps. Worst Integrity Plots are now a special case for world maps.
#             Added option for plotting user defined watermark in all plots.
#             Changed Worst Integrity Ratio colourbar and scale to a fixed one.
#             Parameter '-z' from worst integrity ratio plot has changes to '--rh' and '--rv', so
#               in one call to the program both horizontal and vertical ratio plots can be shown.
#             Changed default alarm limit in Stanford plots from 35 to 40 metres.
#             Changed default both X and Y axis maximum to 60 metres in Stanford plots
#             Changed default horizontal label in Stanford-ESA plots from "HPE","VPE" to 
#               "Horizontal Positioning Error (metres)","Vertical Positioning Error (metres)" respectively.
#             Changed default vertical label in Stanford-ESA plots from "HPL","VPL" to 
#               "Horizontal Protection Level (metres)","Vertical Protection Level (metres)" respectively.
#             Changed default title in Stanford-ESA plots from "StanfordESA" to "Stanford-ESA".
#             Changed reading of Stanford-ESA files in order to skip comment headers.
#             Fixed Stanford plots bug that always set maximum values to 50 metres.
#             Updated help messages.
# -----------
#          gLAB v4.1.0
# Release: 2017/04/07
# Change Log: Added option to set user defined ticks (for both X and Y) in standard plots.
#             Added option to adjust figure to margin, so there is the minimum white space margin left. 
#               This option applies to all modes except for world maps or integrity ratio maps.
#             Fixed all errors when executing graph.py with python3.
# -----------
#          gLAB v4.2.0
# Release: 2017/05/22
# Change Log: Changed default title of SBAS iono map from 'SBAS Iono Correction Map' to 
#                 'SBAS Iono Correction Availability Map'.
#             Added unicode text transformation in WaterMark text input when running under Python 2.
# -----------
#          gLAB v5.0.0
# Release: 2017/06/30
# Change Log:   Added two new modes for setting ticks in the plots: 
#                 With parameters '--XticksStep' and '--YticksStep', the ticks are set at the rate given by the user.
#                 With parameters '--XticksList' and '--YticksList', the user set the ticks by giving a list of ticks.
#               Added options '--percentileX' and '--percentileY' in Stanford Plots mode for setting ticks when the
#                 68%, 95% and 99.9% of the values are reached in each axe.
#               Added option '--CbarLabel' in SBAS Availability map plots for setting a label next to the colorbar.
#               Added option '--NoCbarPercent' n SBAS Availability map plots for not printing the '%' on top of the colorbar.
#               Setting ticks manually now work in all plot modes.
#               Vertical and horizontal label can now be set in World maps, Worst Integrity Ratio maps and SBAS maps.
#               Colorbar in SBAS Availability plots now has the same height as the plot.
# -----------
#          gLAB v5.1.0
# Release: 2017/11/24
# Change Log:   In Mac and Linux, if the ".plot.lock" cannot be created in the current directory,
#                 then this file will be created in the home directory. This is to make graph
#                 work in Mac when gLAB is opened by double clicking in the gLAB logo after
#                 opening the ".dmg" file (i.e. without installing gLAB). In this case, gLAB
#                 files were mounted on a read-only filesystem.
#               Changed title name in Stanford-ESA plots from '# samples' to '# geometries'.
#               Disabled warning deprecated messages in windows and Mac.
#               Removed the "Qt: Untested Windows version 6.2 detected!" warning message
#                 in Windows 10 from the Qt4 library used by python.
#               Fixed watermark being printed over the colorbarlabels in SBAS plots mode.
#               Fixed error in Stanford plots mode which made the image title get erased 
#                 when the user provided a title which had a newline in the middle of the text.
# -----------
#          gLAB v5.1.1
# Release: 2017/12/22
# Change Log: No changes in this file.
# -----------
#          gLAB v5.1.2
# Release: 2018/01/12
# Change Log: No changes in this file.
# -----------
#          gLAB v5.1.3
# Release: 2018/01/19
# Change Log: Removed text "PRN 0" in default ionosphere availability maps title when GEO PRN was 0
#               (PRN 0 means data was read from several GEOs).
# -----------
#          gLAB v5.2.0
# Release: 2018/03/09
# Change Log: The "os.remove(LockFile)" instruction is now inside a try/catch. This is to avoid a
#               rare race condition that occurs when multiple instances of "graph.py" are executed 
#               in parallel and one of them erases the "LockFile" (.plot.lock) after the check that
#               the "LockFile" exists but before the "os.remove(LockFile)" instruction is executed.
#               When this race condition ocurred, the program crashed before creating the plot.
#             Added option '--no-lock-file' for not creating the ".plot.lock" file.
#             Added option '--SBASSystemname' (or '--sbassystemname') for changing the "SBAS" word
#               in the SBAS maps default title for any user defined SBAS system name.
#             Added option '--PRNtext' (or '--prntext') for changing the text "PRN #" in the 
#               SBAS maps default title. This is useful when multiple GEO were used and the PRN in
#               the file header is 0.
#             Added option '--PRNtextnewline' (or '--prntextnewline') for moving the the text "PRN #"
#               in the SBAS maps default title to the line below. Useful when many GEO were used.
#             Added option '--wmc' (or '--watermarkcolor') for changing the colour of the watermark.
#             Added option '--wms' (or '--watermarksize') for changing the size of the watermark.
#             Added option '--wmp' (or '--watermarkposition') for changing the position of the watermark.
#             Changed default position of the watermark in SBAS maps. Now it will situated in the
#               top right side of the image (outside the plot and over the colourbar) instead of the bottom
#               right side of the plot.
#             Changed default size of the watermark in SBAS maps. The size has been changed from 8 to 15.
# -----------
#       END_RELEASE_HISTORY
#############################################################################

import sys,os,matplotlib,math,optparse,re,warnings
from matplotlib.ticker import MultipleLocator, FormatStrFormatter
from optparse import OptionParser
if (sys.platform[:3].lower() == "win"):
    sys.stdout=sys.stderr

global PythonVersion
global legend
global LockFile
global CreateLockFile

legend=False
PythonVersion=sys.version_info[0]
LockFile=".plot.lock"
CreateLockFile=True

class Plot:
    def __init__(self):
        self.FileName = ""
        self.ColX = "var[0]"
        self.ColY = "var[1]"
        self.Cond = ""
        self.Label = ""
        self.Xvar = []
        self.Yvar = []
        self.Style = "."
        self.MarkerSize = 5
        self.LineWidth = 0
        self.PlotColor = ""
        self.PlotColorAuto = True
        
        
class Graphic:
    def __init__(self):
        self.PlotList=[]
        self.PlotCounter = 0
        self.Title = ""
        self.Xlabel = ""
        self.Ylabel = ""
        self.FractionalTitle = ""
        self.WaterMark = ""
        self.WaterMarkColour = 'k'
        self.WaterMarkSize = 8
        self.WaterMarkSizeSetbyUser = 0
        self.WaterMarkPositionX = -999
        self.WaterMarkPositionY = -999
        self.WaterMarkPositionSetbyUser = 0
        self.Cbarlabel = ""

        self.ColXUser = False
        self.ColYUser = False

        self.Xmin = 0.0
        self.Xmax = 0.0
        self.Ymin = 0.0
        self.Ymax = 0.0
        
        self.XminAuto = True
        self.XmaxAuto = True
        self.YminAuto = True
        self.YmaxAuto = True
        
        self.XTicsUser = False
        self.YTicsUser = False
        self.XTicsStepUser = False
        self.YTicsStepUser = False
        self.XTicsListUser = False
        self.YTicsListUser = False

        self.XTicsMax = 0.0
        self.XTicsMin = 0.0
        self.XTicsNum = 0
        self.YTicsMax = 0.0
        self.YTicsMin = 0.0
        self.YTicsNum = 0
        self.XTicsStep = 0.0
        self.YTicsStep = 0.0
        self.XTicksList = []
        self.YTicksList = []

        self.AdjustToMargin = False

        self.SaveFigure = False
        self.SaveFigurePath = []
        
        self.grid = True
        
        self.NumPointsLabel = 2
        self.LabelPosition = 1
        self.LabelPositionX = ""
        self.LabelPositionY = ""

        self.stanford = False
        self.ALAuto = True 
        
        self.stanfordESA = False
        self.resolution_x_auto = True
        self.resolution_y_auto = True
        self.maxpoints_auto = True
        self.worstIntegrityRatio = False
        self.worstIntegrityRatioColorbar = False
        self.SBASmaps = False
        self.ColName = ""
        self.ColRatioV = ""
        self.ColRatioH = ""
        self.ColMIsV = ""
        self.ColMIsH = ""
        self.projection = "cyl"
        self.cbarAutoMin = True
        self.cbarAutoMax = True
        self.cbarAutoN = True

        self.continentColor = ""
        self.lakeColor = ""
        self.boundaryColor = ""
        self.MapResolution = "l"

        self.contourlines = True
        self.CbarPercentage = True
        self.SBASsystemName = ""
        self.PRNtext = ""
        self.PRNtextNewline = False

###########################################################################
# This part makes the Stanford Plot
# It is inspired by the code from http://kom.aau.dk/~borre/easy2/easy14/
#    Copyright c 1998 The board of trustees of the Leland Stanford     
#    Junior University. All rights reserved. 
#    This script file may be distributed and used freely, provided     
#     this copyright notice is always kept with it.                     
#                                                                       
#     Questions and comments should be directed to Todd Walter at:      
#     walter@relgyro.stanford.edu                                                   
###########################################################################
class stanford:
    def __init__(self):
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot(111)
        if Graph.AdjustToMargin == True:
            self.fig.tight_layout()
            self.fig.subplots_adjust(top=.94,bottom=0.1,left=0.09,right=1.01)
        self.AL = 40
        self.PL = []
        self.PE = []
        self.zMax = 0
        self.myPointPatch = []
        self.myPointColors = []
        self.n_fail1 = 0
        self.n_fail2 = 0
        self.n_fail3 = 0
        self.n_alarm = 0
        self.n_avail = 0
        self.n_total = 0
        self.Xmin = 0.0
        self.Xmax = 60.0
        self.Ymin = 0.0
        self.Ymax = 60.0
        self.resolution_x = 0.5
        self.resolution_y = 0.5
        self.Xlabel = 'Positioning Error (metres)'
        self.Ylabel = 'Protection Level (metres)'
        self.Title = 'Stanford Plot' 
        self.fColor=['r','pink','m','y']
        self.grid = True
        self.sigmaX = False
        self.sigmaY = False
        self.SaveFigure = False
        self.SaveFigurePath = ""
        self.cm = 'jet'

    def dealData(self):
        self.n_total=len(self.PL)
        newPE = []
        newPL = []
        self.intervalNo_x = self.Xmax/self.resolution_x
        self.intervalNo_y = self.Ymax/self.resolution_y
        self.data = np.zeros((int(self.intervalNo_x),int(self.intervalNo_y)))
        self.err_bin = np.linspace(self.resolution_x/2, (self.Xmax-self.resolution_x/2), self.intervalNo_x)
        self.sig_bin = np.linspace(self.resolution_y/2, (self.Ymax-self.resolution_y/2), self.intervalNo_y)
        for idx in range(self.n_total):
            j = self.PE[idx]
            k = self.PL[idx]
            diff = abs(k)-abs(j)
            j = int(abs(j)/self.resolution_x)
            k = int(abs(k)/self.resolution_y)
            if j >=(self.intervalNo_x-1):
                #When values are over maximum plot area, we need to check if they are MI.
                #This is because a value of (100,60) will have the same position in grid that (60,100),
                #making both values counted as MI epochs when there is only one.
                #Therefore, values over maximum over plot area which are not MI will be set in position self.intervalNo_x-2
                if diff>0:
                    j = self.intervalNo_x-2
                else:
                    j = self.intervalNo_x-1
            newPE.append(j)
            if k >(self.intervalNo_y-1):
                k = self.intervalNo_y-1
            newPL.append(k)     
        for idx in range(self.n_total):
            self.data[int(newPE[idx]),int(newPL[idx])] = self.data[int(newPE[idx]),int(newPL[idx])] + 1
        
        return self
    
    def getPoints(self):
        self.zMax = math.ceil(math.log10(np.max(self.data)))
        aa,bb = np.nonzero(self.data)
        self.x = self.err_bin[aa]
        self.y = self.sig_bin[bb]
        
        delta_x = 0.5 * np.ones(len(aa)) * self.resolution_x
        delta_y = 0.5 * np.ones(len(bb)) * self.resolution_y
        x = self.x - delta_x
        y = self.y - delta_y
        wx = 2 * delta_x
        wy = 2 * delta_y
        mypatch = []
        mycolors = []
        for x1,y1,w,l in zip(x, y, wx, wy):
            rectangle = Rectangle((x1,y1), w, l, linewidth=0)
            mypatch.append(rectangle)
        for idx in range(len(aa)):
            z = math.log10(self.data[aa[idx],bb[idx]])
            c_idx = math.ceil(255*z/self.zMax)
            mycolors.append(c_idx)
        self.myPointPatch = mypatch
        self.myPointColors = np.array(mycolors)
        i_fails = np.where(self.x / self.y >= 1.0)
        i_fails = i_fails[0]
        for idx in i_fails:
            if self.x[idx] < self.AL:
                self.n_fail2 = self.n_fail2 + self.data[aa[idx],bb[idx]]
            elif self.y[idx] >= self.AL:
                self.n_fail3 = self.n_fail3 + self.data[aa[idx],bb[idx]]
            else:
                self.n_fail1 = self.n_fail1 + self.data[aa[idx],bb[idx]]
                
        i_alarm = np.where(self.y >= self.AL)
        i_alarm = i_alarm[0]
        self.n_alarm = sum(self.data[aa[i_alarm],bb[i_alarm]])
        self.n_avail = self.n_total - self.n_alarm - self.n_fail1 - self.n_fail2 
        return self
    
    def getPercentileCount(self):  
        text_style1 = dict(horizontalalignment='right', verticalalignment='top',
                  fontsize=12, fontdict={'family': 'monospace'})
        text_style2 = dict(horizontalalignment='center', verticalalignment='center',
                  fontsize=12, fontdict={'family': 'monospace'}, rotation=90)
        percentPoint = np.array([0.68, 0.95,0.999])
        percentIndex=percentPoint*len(self.PE)
        self.xPoint=np.zeros(3)
        self.yPoint=np.zeros(3)
        x=sorted(self.PE)
        y=sorted(self.PL)
        for i in range(3):
            self.xPoint[i]=round(x[int(round(percentIndex[i]))],2)
            self.yPoint[i]=round(y[int(round(percentIndex[i]))],2)

        if Graph.sigmaX:
            self.ax.plot(self.xPoint,np.array([self.Ymax,self.Ymax,self.Ymax]),'v',markersize=10)
            for per, xp in zip(percentPoint,self.xPoint):
                self.ax.text(xp+.07,(0.9*self.Ymax+0.1*self.Ymin),'{percent:.1%}'.format(percent=per),**text_style2)     
        if Graph.sigmaY:
            self.ax.plot(np.array([self.Xmax,self.Xmax,self.Xmax]),self.yPoint,'<',markersize=10)
            for per, yp in zip(percentPoint,self.yPoint):
                self.ax.text((0.97*self.Xmax+0.03*self.Xmin),yp,'{percent:.1%}'.format(percent=per),**text_style1) 
        return self    
        
    def plotPoints(self):     
        p = PatchCollection(self.myPointPatch, cmap=plt.get_cmap(self.cm), linewidth=0)       
        p.set_array(self.myPointColors)
        self.ax.add_collection(p)
        m = self.zMax + 1
        cbarTicks = np.linspace(0, 255, m)
        cbarLabel = np.linspace(0, m-1, m)
        
       
        if Graph.sigmaY:
            pCbar = plt.colorbar(mappable=p, ticks=cbarTicks,pad=0.1)
        else:
            pCbar = plt.colorbar(mappable=p, ticks=cbarTicks)
        pCbar.ax.set_yticklabels(cbarLabel) 
        pCbar.ax.set_ylabel('Number of Points per Pixel (logarithmic)')
        self.ax.text(self.AL/5, 6*self.AL/7, 'Normal Operation \nEpochs: %d' %self.n_avail, style='italic')
        self.ax.text(self.AL/5, 5.5*self.AL/7, '{percent:.3%}'.format(percent=self.n_avail / float(self.n_total)), style='italic')
        return self
    
    def plotPatch(self):        
        
        fail1=Rectangle((self.AL, self.Ymin), (self.Xmax - self.AL), self.AL, lw=1, facecolor=self.fColor[0], alpha=0.2 )
        self.ax.add_patch(fail1)
        if self.AL<=45:
           self.ax.text(8*self.AL/7, 1*self.AL/7, 'HMI \nEpochs: %d' %self.n_fail1 , style='italic')
        else:
           self.ax.text(7*self.AL/7, 1*self.AL/7, 'HMI \nEpochs: %d' %self.n_fail1 , style='italic')
        
        vert2 = [(self.Xmin, self.Ymin), (self.AL, self.AL),(self.AL, self.Ymin), (self.Xmin,self.Ymin),]
        code2 = [Path.MOVETO, Path.LINETO, Path.LINETO, Path.CLOSEPOLY,]
        path2 = Path(vert2, code2)
        fail2=PathPatch(path2, facecolor=self.fColor[1], lw=1, alpha=0.2)
        self.ax.add_patch(fail2)
        self.ax.text(2*self.AL/5, 1*self.AL/7, 'MI \nEpochs: %d' %self.n_fail2 , style='italic')
        
        vert3 = [(self.AL, self.AL), (self.Xmax, self.Ymax), (self.Xmax, self.AL), (self.AL, self.AL),]
        code3 = [Path.MOVETO, Path.LINETO, Path.LINETO, Path.CLOSEPOLY,]
        path3 = Path(vert3, code3)
        fail3=PathPatch(path3, facecolor=self.fColor[2], lw=1, alpha=0.2)
        self.ax.add_patch(fail3)
        if self.AL<=45:
            self.ax.text(8*self.AL/7, 17*self.AL/16, 'MI \nEpochs: %d' %self.n_fail3 , style='italic')
        else:
            MItext="MI"
            self.ax.text(7*self.AL/7, 16.2*self.AL/16, '%8s \nEpochs: %d' %(MItext,self.n_fail3) , style='italic')
        
        vert1 = [(self.Xmin, self.AL), (self.Xmin, self.Ymax), (self.Xmax, self.Ymax), (self.AL, self.AL), (self.Xmin, self.AL),]
        code1 = [Path.MOVETO, Path.LINETO, Path.LINETO, Path.LINETO, Path.CLOSEPOLY,]
        path1 = Path(vert1, code1)
        alarm=PathPatch(path1, facecolor=self.fColor[3], lw=1, alpha=0.2)
        self.ax.add_patch(alarm)
        if self.AL<=45:
            self.ax.text(2*self.AL/5, 8*self.AL/7, 'System Unavailable \nAlarm Epochs: %d' %self.n_alarm , style='italic')
        else:
            self.ax.text(2*self.AL/5, 7.5*self.AL/7, 'System Unavailable \nAlarm Epochs: %d' %self.n_alarm , style='italic')
        return self
    
    def plotShow(self):
        plt.axis([self.Xmin, self.Xmax, self.Ymin, self.Ymax])
        #There is a bug in Python 2 and 3 that makes only showing one axe ticks when ticks are set in right or top sides (twinx() or twiny() functions)
        #To get around it, the extra ticks for sigma will be made with horizontal and vertical lines and text annotations for the labels
        if self.sigmaY:
            bias=0.1
            #To set the labels in the correct position, we use the function matplotlib.transforms.blended_transform_factory to get the coordinate
            #system in the bottom right corner. Coordinates are from(0,0) to (1,1). The (self.ax.transAxes,self.ax.transData) means that the first
            #item is a coordinate in normalized X (0,1), and the second is a coordinate according to data max and min values
            trans = matplotlib.transforms.blended_transform_factory(self.ax.transAxes,self.ax.transData)
            for elem in self.yPoint:
                plt.axhline(elem, linestyle='dotted',color='black',linewidth=.9)
                self.ax.annotate(elem, xy=(1.01, elem), xycoords=trans, clip_on=False, va='center')
        if self.sigmaX:
            bias=0
            #The transform is the same as before,but now X is data and Y is normalized
            #The annotation in Y axis does not get perfect, we have to hardcode some correction 
            trans = matplotlib.transforms.blended_transform_factory(self.ax.transData,self.ax.transAxes)
            for elem in self.xPoint:
                plt.axvline(elem, linestyle='dotted',color='black',linewidth=.9)
                self.ax.annotate(elem, xy=(elem-.07,1.07), xycoords=trans, clip_on=False,rotation=90)

        #Set sigma ticks. Set user defined ticks if user has set any
        if Graph.XTicsUser == True:
            self.ax.set_xticks(np.linspace(Graph.XTicsMin,Graph.XTicsMax,Graph.XTicsNum))
        elif Graph.XTicsStepUser == True:
            self.ax.set_xticks(np.linspace(self.Xmin,self.Xmax,abs(int((self.Xmax-self.Xmin)/Graph.XTicsStep))+1))
        elif Graph.XTicsListUser == True:
            self.ax.set_xticks(Graph.XTicksList)

        if Graph.YTicsUser == True:
            self.ax.set_yticks(np.linspace(Graph.YTicsMin,Graph.YTicsMax,Graph.YTicsNum))
        elif Graph.YTicsStepUser == True:
            self.ax.set_yticks(np.linspace(self.Ymin,self.Ymax,abs(int((self.Ymax-self.Ymin)/Graph.YTicsStep))+1))
        elif Graph.YTicsListUser == True:
            self.ax.set_yticks(Graph.YTicksList)

        self.ax.set_xlabel(self.Xlabel)
        self.ax.set_ylabel(self.Ylabel)

        NumNewlines=self.Title.count('\n')
        if Graph.AdjustToMargin == True:
            #Add space to fit multiline title
            if NumNewlines == 1:
                self.fig.subplots_adjust(top=.9)
            elif NumNewlines == 2:
                self.fig.subplots_adjust(top=.87)
            elif NumNewlines > 2:
                self.fig.subplots_adjust(top=.83)
            elif self.sigmaX:
                self.fig.subplots_adjust(top=(1-bias))

        #Check if Newline are at the end. In that case, we need to add the number of epochs before the newlines
        if NumNewlines>0:
            NumNewlinesEnd = 0
            for i in range(NumNewlines):
                if (self.Title[len(self.Title)-1-i]=='\n'):
                    NumNewlinesEnd = NumNewlinesEnd + 1
                    if Graph.AdjustToMargin == False:
                        #Add space to fit multiline title if option to adjust to margin is not enabled
                        if self.sigmaX:
                            bias = bias + .06
                else:
                    break
            if Graph.AdjustToMargin == False and self.sigmaX:
                self.fig.subplots_adjust(top=(1-bias))
            if NumNewlinesEnd>0:
                self.Title = self.Title[:-NumNewlinesEnd] + ' (%d epochs)' %self.n_total
            else:
                self.Title = self.Title + ' (%d epochs)' %self.n_total
            for i in range(NumNewlinesEnd):
                self.Title = self.Title +'\n'
            self.ax.set_title(self.Title)
        else:
            self.ax.set_title(self.Title + ' (%d epochs)' %self.n_total )
        if Graph.WaterMark != "":
            if Graph.WaterMarkPositionSetbyUser == 1:
                self.ax.text(Graph.WaterMarkPositionX, Graph.WaterMarkPositionY, Graph.WaterMark, style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
            else:
                self.ax.text(17*self.Xmax/20, self.Ymax/40, Graph.WaterMark, style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
        if self.grid:                 
            plt.grid(True)
        if self.SaveFigure:
            try:
                plt.savefig(self.SaveFigurePath)
            except:
                print ("ERROR: %s" %(sys.exc_info()[1]))
        else:
            plt.show()
        
###########################################################################
# This part makes the Stanford-ESA Plot
###########################################################################
class stanfordESA:
    def __init__(self):
        self.zMax = 0
        self.f = ""
        self.myPointPatch = []
        self.myPointColors = []
        self.Xmin = 0.0
        self.Xmax = 60.0
        self.Ymin = 0.0
        self.Ymax = 60.0
        self.resolution_x = 0.1
        self.resolution_y = 0.1
        self.Xlabel = "" 
        self.Ylabel = ""
        self.Title = 'Stanford-ESA Plot' 
        self.grid = True
        self.sigmaX = False
        self.sigmaY = False
        self.SaveFigure = False
        self.SaveFigurePath = ""
        self.cm = 'jet'
        self.maxpoints=500000
    def readData(self):
        try:
            f = open(self.f,'r')
        except:
            print ("ERROR Reading file '" + self.f + "'")
            removeLockFile()
            sys.exit()
        self.x = []
        self.y = []
        self.verticalNo = []
        self.horizontalNo = []
        i = 0
        for line in f:
            var=line.split()
            i = i + 1
            if var != []: 
                match_result = re.match(r'^#',var[0])
                if match_result == None:
                    if i == 2:
                        self.resolution_x = float(var[0])
                        self.resolution_y = float(var[1])
                        self.Xmax = float(var[2])
                        self.Ymax = float(var[3])
                        number_pixel=(self.Xmax*self.Ymax)/(self.resolution_x*self.resolution_y)
                        if number_pixel> self.maxpoints:
                            print ("ERROR: Number of pixels in plot (%d) is over limit (%d).\nReduce the pixel resolution, or reduce x&y range or increase the maximum number of pixels." %(number_pixel, self.maxpoints))
                            print ("To increase the maximum number of pixels, use the parameter '--maxpoints <value>'.\nWarning: If maximum number of pixels is too large, the system may run out of memory.")
                            sys.exit()
                    elif i>3:
                       self.x.append(float(var[0]))
                       self.y.append(float(var[1]))
                       self.horizontalNo.append(float(var[2]))
                       self.verticalNo.append(float(var[3]))
        f.close()
        return self
        
    
    def getPoints(self,x,y,z):
        self.n_total = sum(z)
        self.n_fail = 0
        x = np.array(x)
        y = np.array(y)
        z = np.array(z)
        idx_nonzero = np.nonzero(z)
        x=x[idx_nonzero]
        y=y[idx_nonzero]
        z=z[idx_nonzero]
        self.zMax = math.ceil(math.log10(np.max(z)))

        mypatch = []
        mycolors = []
        for x1,y1 in zip(x, y):
            rectangle = Rectangle((x1,y1), self.resolution_x, self.resolution_y, linewidth=0)
            mypatch.append(rectangle)
        for number in z:
            c_idx = math.ceil(255*math.log10(number)/self.zMax)
            mycolors.append(c_idx)
        self.myPointPatch = mypatch
        self.myPointColors = np.array(mycolors)
        i_fails = np.where(x / y >= 1.0)[0]
        for idx in i_fails:
            self.n_fail = self.n_fail + z[idx] 
        return self
       
    def plotPoints(self, ax):     
        p = PatchCollection(self.myPointPatch, cmap=plt.get_cmap(self.cm), linewidth=0)       
        p.set_array(self.myPointColors)
        ax.add_collection(p)
        m = self.zMax + 1
        cbarTicks = np.linspace(0, 255, m)
        cbarLabel = np.linspace(0, m-1, m)
        pCbar = plt.colorbar(mappable=p, ticks=cbarTicks)
        pCbar.ax.set_yticklabels(cbarLabel) 
        pCbar.ax.set_ylabel('Number of Points per Pixel (logarithmic)')
        x = [self.Xmin, self.Xmax]
        y = x
        plt.plot(x,y,'black')
        if Graph.WaterMark != "":
            if Graph.WaterMarkPositionSetbyUser == 1:
                ax.text(Graph.WaterMarkPositionX, Graph.WaterMarkPositionY, Graph.WaterMark, style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
            else:
                ax.text(17*self.Xmax/20, self.Ymax/40, Graph.WaterMark, style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
        plt.axis([self.Xmin, self.Xmax, self.Ymin, self.Ymax])
        #Set user defined ticks if user has set any
        if Graph.XTicsUser == True:
            ax.set_xticks(np.linspace(Graph.XTicsMin,Graph.XTicsMax,Graph.XTicsNum))
        elif Graph.XTicsStepUser == True:
            ax.set_xticks(np.linspace(self.Xmin,self.Xmax,abs(int((self.Xmax-self.Xmin)/Graph.XTicsStep))+1))
        elif Graph.XTicsListUser == True:
            ax.set_xticks(Graph.XTicksList)

        if Graph.YTicsUser == True:
            ax.set_yticks(np.linspace(Graph.YTicsMin,Graph.YTicsMax,Graph.YTicsNum))
        elif Graph.YTicsStepUser == True:
            ax.set_yticks(np.linspace(self.Ymin,self.Ymax,abs(int((self.Ymax-self.Ymin)/Graph.YTicsStep))+1))
        elif Graph.YTicsListUser == True:
            ax.set_yticks(Graph.YTicksList)

        ax.set_xlabel(self.Xlabel)
        ax.set_ylabel(self.Ylabel)
        ax.set_title(self.Title + ' (%d geometries)' %self.n_total )
        if self.grid:                 
            plt.grid(True)
        return 
    

##########################################################################
# This part makes the worst integrity ratio plot
##########################################################################
class WIRmap:
    def __init__(self):
        self.grid = True
        self.projection = 'cyl'
        self.Xmin = -180
        self.Xmax = 180
        self.Ymin = -90
        self.Ymax = 90
        self.continentColor = 'y'
        self.lakeColor = 'w'
        self.boundaryColor = 'w'
        self.f = ""
        #self.myColorMap = 'jet'
        self.SaveFigure = False
        self.SaveFigurePath = ""
        self.Title = "Default title"
        self.Xlabel = "" 
        self.Ylabel = ""
        self.cbarMin = 0.0
        self.cbarMax = 2.0
        self.cbarMaxDef = 2.0
        self.cbarInterval = 8.0
        self.colName = ""
        self.colX = ""
        self.colY = ""
        self.colRatioV = ""
        self.colRatioH = ""
        self.colMIsV = ""
        self.colMIsH = ""
        self.txt_show = False
        self.ms = 150
    def readData(self):
        try:
            f = open(self.f,'r')
        except:
            print ("ERROR Reading file '" + self.f + "'")
            removeLockFile()
            sys.exit()
        self.StaName = []
        self.longitude = []
        self.latitude = []
        self.ratioV = []
        self.ratioH = []
        self.MIsV = []
        self.MIsH = []
        i = 0
        for line in f:
            var = line.split()
            if var != []: 
                match_result = re.match(r'^#',var[0])
                if match_result == None:
                    j = 0
                    for ele in var:
                        try:
                            auxEle = float(ele)
                            var[j] = auxEle
                            j += 1
                        except:
                            j += 1
                    self.longitude.append(eval(self.colX))
                    self.latitude.append(eval(self.colY))
                    if self.colName != "": self.StaName.append(eval(self.colName))
                    if self.colRatioV != "": self.ratioV.append(eval(self.colRatioV))
                    if self.colRatioH != "": self.ratioH.append(eval(self.colRatioH))
                    if self.colMIsV != "": self.MIsV.append(eval(self.colMIsV))
                    if self.colMIsH != "": self.MIsH.append(eval(self.colMIsH))
        f.close()
        self.ratios = [self.ratioV,self.ratioH]
        self.mis = [self.MIsV,self.MIsH]
        return self
    def drawMap(self):
        idx_sv = 0
        if self.cbarMax != "":
            self.cbarMaxDef = "User"
        for i in range(2):
            ratio = self.ratios[i]
            MIs = self.mis[i]
            if ratio != []:
                fig = plt.figure() 
                if (Graph.cbarAutoMax == True):
                    self.cbarMax = int(max(ratio)) + 1
                ax1 = fig.add_axes([0.1,0.2,0.8,0.7])
                if self.Title == "Default title":
                    if MIs != []:
                        title = "Worst Integrity Ratio" + ' / Number of MIs'
                    else:
                        title = "Worst Integrity Ratio"
                else:
                    title = self.Title
                if (i == 0 and self.ratios[0] != [] and self.ratios[1] != []): title = 'Vertical ' + title
                elif (i == 1 and self.ratios[0] != [] and self.ratios[1] != []): title = 'Horizontal ' + title
                ax1.set_title(title) 
                if Graph.WaterMark != "":
                    if Graph.WaterMarkPositionSetbyUser == 1:
                        plt.annotate(Graph.WaterMark, xy=(Graph.WaterMarkPositionX,Graph.WaterMarkPositionY), xycoords='axes fraction',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
                    else:
                        plt.annotate(Graph.WaterMark, xy=(.87,.03), xycoords='axes fraction',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
                if self.projection == 'cyl':
                    baseM = Basemap(projection='cyl',llcrnrlat=self.Ymin,urcrnrlat=self.Ymax,\
                            llcrnrlon=self.Xmin,urcrnrlon=self.Xmax,resolution=Graph.MapResolution,fix_aspect=True)
                    if (Graph.XminAuto == False or Graph.XmaxAuto == False or Graph.YminAuto == False or Graph.YmaxAuto == False):
                        parallel = np.arange(self.Ymin,self.Ymax+1.,5.)
                        meridian = np.arange(self.Xmin,self.Xmax+1.,5.)  
                    else:
                        parallel = np.arange(self.Ymin,self.Ymax+1.,20.)
                        meridian = np.arange(self.Xmin,self.Xmax+1.,40.)  

                elif self.projection == 'lcc':
                    baseM = Basemap(width=12000000,height=9000000,projection='lcc',\
                                resolution=Graph.MapResolution,lat_1=45.,lat_0=50,lon_0=10.)
                    self.Title = "Lambert Conformal Projection"
                    parallel = np.arange(0.,81.,10.)
                    meridian = np.arange(10,351.,20.)  

                if (Graph.XTicsStepUser == True):
                    meridian = np.linspace(self.Xmin,self.Xmax,1 + abs(int(self.Xmax-self.Xmin)/Graph.XTicsStep))
                elif Graph.XTicsUser == True:
                    meridian = np.linspace(Graph.XTicsMin,Graph.XTicsMax,Graph.XTicsNum)
                elif Graph.XTicsListUser == True:
                    meridian = Graph.XTicksList

                if (Graph.YTicsStepUser == True):
                    parallel = np.linspace(self.Ymin,self.Ymax,1 + abs(int((self.Ymax-self.Ymin)/Graph.YTicsStep)))
                elif Graph.YTicsUser == True:
                    parallel = np.linspace(Graph.YTicsMin,Graph.YTicsMax,Graph.YTicsNum)
                elif Graph.YTicsListUser == True:
                    parallel = Graph.YTicksList

                baseM.drawcoastlines()
                baseM.fillcontinents(color=self.continentColor,lake_color=self.lakeColor,alpha=0.5,zorder=0)
                if self.grid:
                    w_line = 1.0
                else: 
                    w_line = 0.0
                baseM.drawparallels(parallel,labels=[1,0,0,0],fontsize=10,linewidth=w_line)
                baseM.drawmeridians(meridian,labels=[0,0,0,1],fontsize=10,linewidth=w_line)
                baseM.drawmapboundary(fill_color=self.boundaryColor)
                if MIs != []:
                    w_border = 3.0
                    c_border = []
                    for j in range(len(MIs)):
                        if MIs[j] == 0: c_border.append('white')
                        if MIs[j] == 1: c_border.append('silver')
                        if MIs[j] >= 2: c_border.append('black')
                else:
                    w_border = 0 
                    c_border = 'none'
                if Graph.worstIntegrityRatioColorbar == True:
                    self.cbarMax = 2.0
                    self.cbarMin = 0.0
                    self.cbarInterval = 8
                bin_size = (self.cbarMax-self.cbarMin)/self.cbarInterval
                c_ratio = np.array(ratio)/bin_size
                c_ratio = c_ratio.astype(int)*bin_size
                bounds = np.linspace(self.cbarMin, self.cbarMax, self.cbarInterval+1)
                xpt,ypt = baseM(self.longitude,self.latitude)
                if Graph.worstIntegrityRatioColorbar == True:
                    #cm = matplotlib.colors.ListedColormap(['#0080FF', '#40E0FF', '#00FF00', '#FFFF00', '#FF0000', '#FF00C8','#FF64FF','#FFA0FF'])
                    cm = matplotlib.colors.ListedColormap(['#0080FF', '#40E0FF', '#00FF00', '#FFFF00', '#FF0000', '#B22222','#B30000','#800000']) 
                    norm_border = matplotlib.colors.BoundaryNorm(boundaries=bounds, ncolors=cm.N)
                    self.cs = baseM.scatter(xpt,ypt,c=c_ratio,norm=norm_border,s=self.ms,edgecolor =c_border,linewidth=w_border,cmap=cm)
                else:
                    norm = matplotlib.colors.BoundaryNorm(boundaries=bounds, ncolors=256)
                    self.cs = baseM.scatter(xpt,ypt,c=c_ratio,norm=norm,s=self.ms,edgecolor =c_border,linewidth=w_border,cmap='jet')
                if self.txt_show == True:
                    for j in range(len(ratio)):
                        txt_ratio = str(round(ratio[j],1))
                        ax1.annotate(txt_ratio, (xpt[j], ypt[j]),ha='center', va='center', fontsize=7, color='w')

                #cbar1 = baseM.colorbar(self.cs,location='bottom',pad="10%")
                if (Graph.XminAuto == False or Graph.XmaxAuto == False or Graph.YminAuto == False or Graph.YmaxAuto == False):
                    cbaxes1 = fig.add_axes([0.18,0.08,0.64,0.04])
                else:
                    cbaxes1 = fig.add_axes([0.18,0.11,0.64,0.04])
                if Graph.worstIntegrityRatioColorbar == True:
                    cbar1 =  matplotlib.colorbar.ColorbarBase(cbaxes1,cmap=cm,norm=norm_border, boundaries=bounds,spacing='proportional', orientation='horizontal')
                else:
                    cbar1 = plt.colorbar(self.cs,cax=cbaxes1,orientation='horizontal')
                cbar1.ax.xaxis.set_ticks_position('top')
                if w_border != 0:
                    if (Graph.XminAuto == False or Graph.XmaxAuto == False or Graph.YminAuto == False or Graph.YmaxAuto == False):
                        cbaxes2 = fig.add_axes([0.18,0.04,0.64,0.04])
                    else:
                        cbaxes2 = fig.add_axes([0.18,0.07,0.64,0.04])
                    cmap_border = matplotlib.colors.ListedColormap(['white', 'silver', 'black'])
                    bounds_border = [1,2,3,4]
                    norm_border = matplotlib.colors.BoundaryNorm(boundaries=bounds_border, ncolors=cmap_border.N)
                    cbar2 = matplotlib.colorbar.ColorbarBase(cbaxes2, cmap=cmap_border, norm=norm_border, boundaries=bounds_border,spacing='proportional', orientation='horizontal')
                    cbar2.ax.set_xticklabels(['0','1','2','>2'])
                    #cbar2.set_label('Number of')
                    #cbar2.ax.set_ytickposition('right')
                    #if (idx_sv ==0):
                    #    cbar2.set_label('Number of vertical MIs')
                    #elif (idx_sv ==1):
                    #    cbar2.set_label('Number of horizontal MIs')

                if (self.Xlabel!= ""):
                    ax1.set_xlabel("\n" + self.Xlabel) #The \n is to void the Xlabel overlap with the degree ticks
                if (self.Ylabel!= ""):
                    ax1.set_ylabel(self.Ylabel)
                    ax1.yaxis.labelpad = 37 #This is an offset to vertical label so it does not overlap with the degrees ticks

                if (self.SaveFigure == True): 
                    try:
                        if(len(self.SaveFigurePath)>=idx_sv+1):
                            plt.savefig(self.SaveFigurePath[idx_sv])
                    except:
                        print ("ERROR: %s" %(sys.exc_info()[1]))
                idx_sv = idx_sv + 1

        if self.StaName != []:
            #Plot with the station names
            fig, ax1 = plt.subplots()
            if Graph.AdjustToMargin == True:
                fig.tight_layout() #This is to adjust plot to margins
            if self.Title == "Default title":
                title = "Station Map Distribution"
            else:
                if Graph.AdjustToMargin == True:
                    #Add margin on top to fit title with multiple lines (if necessary)
                    NumNewlines=self.Title.count('\n')
                    if NumNewlines == 1:
                        plt.subplots_adjust(top=.9)
                    elif NumNewlines == 2:
                        plt.subplots_adjust(top=.87)
                    elif NumNewlines > 2:
                        plt.subplots_adjust(top=.83)
                title = self.Title
            ax1.set_title(title) 
            if (self.Xlabel!= ""):
                ax1.set_xlabel("\n" + self.Xlabel) #The \n is to void the Xlabel overlap with the degree ticks
            if (self.Ylabel!= ""):
                ax1.set_ylabel(self.Ylabel)
                ax1.yaxis.labelpad = 37 #This is an offset to vertical label so it does not overlap with the degrees ticks

            if Graph.WaterMark != "":
                if Graph.WaterMarkPositionSetbyUser == 1:
                    plt.annotate(Graph.WaterMark, xy=(Graph.WaterMarkPositionX,Graph.WaterMarkPositionY), xycoords='axes fraction',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
                else:
                    plt.annotate(Graph.WaterMark, xy=(.87,.03), xycoords='axes fraction',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
            if self.projection == 'cyl':
                baseM = Basemap(projection='cyl',llcrnrlat=self.Ymin,urcrnrlat=self.Ymax,\
                        llcrnrlon=self.Xmin,urcrnrlon=self.Xmax,resolution=Graph.MapResolution,fix_aspect=True)
                if (Graph.XminAuto == False or Graph.XmaxAuto == False or Graph.YminAuto == False or Graph.YmaxAuto == False):
                    parallel = np.arange(self.Ymin,self.Ymax+1.,5.)
                    meridian = np.arange(self.Xmin,self.Xmax+1.,5.)  
                else:
                    parallel = np.arange(self.Ymin,self.Ymax+1.,20.)
                    meridian = np.arange(self.Xmin,self.Xmax+1.,40.)  
            elif self.projection == 'lcc':
                baseM = Basemap(width=12000000,height=9000000,projection='lcc',\
                            resolution=Graph.MapResolution,lat_1=45.,lat_0=50,lon_0=10.)
                self.Title = "Lambert Conformal Projection"
                parallel = np.arange(0.,81.,10.)
                meridian = np.arange(10,351.,20.)  

            if (Graph.XTicsStepUser == True):
                meridian = np.linspace(self.Xmin,self.Xmax,1 + abs(int(self.Xmax-self.Xmin)/Graph.XTicsStep))
            elif Graph.XTicsUser == True:
                meridian = np.linspace(Graph.XTicsMin,Graph.XTicsMax,Graph.XTicsNum)
            elif Graph.XTicsListUser == True:
                meridian = Graph.XTicksList

            if (Graph.YTicsStepUser == True):
                parallel = np.linspace(self.Ymin,self.Ymax,1 + abs(int((self.Ymax-self.Ymin)/Graph.YTicsStep)))
            elif Graph.YTicsUser == True:
                parallel = np.linspace(Graph.YTicsMin,Graph.YTicsMax,Graph.YTicsNum)
            elif Graph.YTicsListUser == True:
                parallel = Graph.YTicksList

            baseM.drawcoastlines()
            baseM.fillcontinents(color=self.continentColor,lake_color=self.lakeColor,alpha=0.5,zorder=0)
            xpt,ypt = baseM(self.longitude,self.latitude)
            if self.grid:
                w_line = 1.0
            else: 
                w_line = 0.0
            baseM.drawparallels(parallel,labels=[1,0,0,0],fontsize=10,linewidth=w_line)
            baseM.drawmeridians(meridian,labels=[0,0,0,1],fontsize=10,linewidth=w_line)
            baseM.drawmapboundary(fill_color=self.boundaryColor)
            for j in range(len(self.StaName)):
                ax1.annotate(self.StaName[j], (xpt[j], ypt[j]),ha='center', va='center', fontsize=9, color='b')
            if (self.SaveFigure == True): 
                try:
                    if(len(self.SaveFigurePath)>=idx_sv+1):
                        plt.savefig(self.SaveFigurePath[idx_sv])
                except:
                    print ("ERROR: %s" %(sys.exc_info()[1]))

        if (self.SaveFigure == False): plt.show()
                
        return self

##########################################################################
# This part makes the SBAS Availability maps
##########################################################################
class SBASmaps:
    def __init__(self):
        self.grid = True
        self.contourlines = True
        self.projection = 'cyl'
        self.continentColor = 'y'
        self.lakeColor = 'w'
        self.boundaryColor = 'w'
        self.f = ""
        self.SaveFigure = False
        self.SaveFigurePath = ""
        self.cm = 'jet'
        self.Title = "Equidistant Cylindrical Projection"
        self.Xlabel = "" 
        self.Ylabel = ""
        self.Cbarlabel = ""
        self.cbarMin = 0.0
        self.cbarMax = 2.0
        self.cbarInterval = 8.0
        self.txt_show = False
        self.map_type = ''
        self.hour = -1
        self.SBASsystemName = ""
        self.PRNtext = ""
        self.PRNtextNewline = False

    def readData(self):
        try:
             f = open(self.f,'r')
        except:
            print ("ERROR Reading file '" + self.f + "'")
            removeLockFile()
            sys.exit()
        self.longitude = []
        self.latitude = []
        self.percentile = []
        i = 0
        hour=0
        PRNtextNewline = ""
        if ( self.SBASsystemName == "" ):
            self.SBASsystemName="SBAS"
        for line in f:
            var = line.split()
            i = i + 1
            if var != []: 
                match_result = re.match(r'^#',var[0])
                if (match_result != None and i==1):
                    if(var[len(var)-1] == "HOUR"):
                        hour=1
                if match_result == None:
                    if i == 2:
                        self.Xmin = float(var[2])
                        self.Xmax = float(var[3])
                        self.Ymin = float(var[0])
                        self.Ymax = float(var[1])
                        self.resolution = float(var[4])
                        if len(var) == 13:
                            #Availability map without hour
                            self.hal = float(var[6])
                            self.val = float(var[7])
                            self.doy = int(var[8])
                            self.year = int(var[9])
                            self.epochs = int(var[10])
                            self.prn = int(var[11])
                            if (self.PRNtext != "" ):
                                PRNtext = self.PRNtext
                            else:
                                if (self.prn == 0):
                                    PRNtext = ""
                                else:
                                    PRNtext = "PRN " + str(self.prn)

                            if (self.PRNtextNewline == True):
                                PRNtextNewline = "\n" + PRNtext
                                PRNtext = ""
                            elif (PRNtext  != ""):
                                 PRNtext = PRNtext + " "

                        elif len(var) == 14:
                            if hour==1:
                                #Availability map with hour
                                self.hal = float(var[6])
                                self.val = float(var[7])
                                self.doy = int(var[8])
                                self.year = int(var[9])
                                self.epochs = int(var[10])
                                self.prn = int(var[11])
                                self.hour = int(var[13])
                                if (self.PRNtext != "" ):
                                    PRNtext = self.PRNtext
                                else:
                                    if (self.prn == 0):
                                        PRNtext = ""
                                    else:
                                        PRNtext = "PRN " + str(self.prn)

                                if (self.PRNtextNewline == True):
                                    PRNtextNewline = "\n" + PRNtext
                                    PRNtext = ""
                                elif (PRNtext  != ""):
                                     PRNtext = PRNtext + " "

                            else:
                                #Cont-Risk Map with no hour
                                self.hal = float(var[6])
                                self.val = float(var[7])
                                self.doy = int(var[8])
                                self.year = int(var[9])
                                self.epochs = int(var[10])
                                self.prn = int(var[11])
                                self.winsize = int(var[13])
                                if (self.PRNtext != "" ):
                                    PRNtext = self.PRNtext
                                else:
                                    if (self.prn == 0):
                                        PRNtext = ""
                                    else:
                                        PRNtext = "PRN " + str(self.prn)

                                if (self.PRNtextNewline == True):
                                    PRNtextNewline = "\n" + PRNtext
                                    PRNtext = ""
                                elif (PRNtext  != ""):
                                     PRNtext = PRNtext + " "

                        elif len(var) == 15:
                            #Cont-Risk Map with hour
                            self.hal = float(var[6])
                            self.val = float(var[7])
                            self.doy = int(var[8])
                            self.year = int(var[9])
                            self.epochs = int(var[10])
                            self.prn = int(var[11])
                            self.winsize = int(var[13])
                            self.hour = int(var[14])
                            if (self.PRNtext != "" ):
                                PRNtext = self.PRNtext
                            else:
                                if (self.prn == 0):
                                    PRNtext = ""
                                else:
                                    PRNtext = "PRN " + str(self.prn)

                            if (self.PRNtextNewline == True):
                                PRNtextNewline = "\n" + PRNtext
                                PRNtext = ""
                            elif (PRNtext  != ""):
                                PRNtext = PRNtext + " "

                        elif (len(var) == 9 or len(var) == 10):
                            #Iono map with or without hour
                            self.doy = int(var[5])
                            self.year = int(var[6])
                            self.epochs = int(var[7])
                            self.prn = int(var[8])
                            self.map_type = 'ionoCorrection'
                            if (self.PRNtext != "" ):
                                PRNtext = self.PRNtext
                            else:
                                if (self.prn == 0):
                                    PRNtext = ""
                                else:
                                    PRNtext = "PRN " + str(self.prn)
    
                            if (self.PRNtextNewline == True):
                                PRNtextNewline = "\n" + PRNtext
                                PRNtext = ""
                            elif (PRNtext  != ""):
                                PRNtext = PRNtext + " "

                            if (len(var) == 10):
                                self.hour = int(var[9])
                                self.Title = self.SBASsystemName +" Iono Correction Availability Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " Hour " + str(self.hour) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + "(Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                            else:
                                self.Title = self.SBASsystemName + " Iono Correction Availability Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + "(Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                    else:
                        self.latitude.append(float(var[0]))
                        self.longitude.append(float(var[1]))
                        self.percentile.append(float(var[2]))
                elif i == 3:
                    if self.map_type != 'ionoCorrection':
                        if var[3] == 'AVAIL%':
                            #self.map_type = re.split(r'\%',var[3])[0]
                            self.map_type = 'availability'
                            if (self.hour == -1):
                                self.Title = self.SBASsystemName + " Availability Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + "HAL " + str(self.hal) + "m VAL " + str(self.val) + "m (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                            else:
                                self.Title = self.SBASsystemName + " Availability Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " Hour " + str(self. hour) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + "HAL " + str(self.hal) + "m VAL " + str(self.val) + "m (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                        elif var[3] == 'CONT-RISK':
                            self.map_type = 'continuity'
                            if (self.hour == -1):
                                self.Title = self.SBASsystemName + " Continuity Risk Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + "HAL " + str(self.hal) + "m VAL " + str(self.val) + "m (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
                            else:
                                self.Title = self.SBASsystemName + " Continuity Risk Map\nDoY " + str(self.doy) + " Year " + str(self.year) + " Hour " + str(self. hour) + " NumEpochs " + str(self.epochs) + "\n" + PRNtext + "HAL " + str(self.hal) + "m VAL " + str(self.val) + "m (Pixel " + str(self.resolution) + u'\N{DEGREE SIGN}' + "x" + str(self.resolution) + u'\N{DEGREE SIGN}' + ")" + PRNtextNewline
        f.close()
        return self
    def drawMap(self):
        fig = plt.figure()
        #fig = plt.figure(figsize=(15,15)) #This is to change the initial figure size
        ax = fig.add_subplot(111,aspect = 'equal')
        leftmargin=0.07
        if (self.map_type == 'continuity'):
            rightmargin=.89
        else:
            rightmargin=.92
        if (self.Xlabel!= ""):
            ax.set_xlabel("\n" + self.Xlabel) #The \n is to void the Xlabel overlap with the degree ticks
        if (self.Ylabel!= ""):
            ax.set_ylabel(self.Ylabel)
            ax.yaxis.labelpad = 37 #This is an offset to vertical label so it does not overlap with the degrees ticks
            leftmargin=0.1
        if (self.Cbarlabel != ""):
            if (self.map_type == 'continuity'):
                rightmargin=.86
            else:
                rightmargin=.9

        plt.subplots_adjust(left=leftmargin, right=rightmargin,  wspace=0, hspace=0,bottom=0,top=1) #This is to adjust figure to margin with ithgt_layout function

        ax.set_title(self.Title) 
        baseM = Basemap(projection='cyl',llcrnrlat=self.Ymin,urcrnrlat=self.Ymax,llcrnrlon=self.Xmin,urcrnrlon=self.Xmax,resolution='l')
        #Set ticks according to user to automatic
        if Graph.XTicsStepUser == True:
            meridian = np.linspace(self.Xmin,self.Xmax,1 + abs(int(self.Xmax-self.Xmin)/Graph.XTicsStep))
        elif Graph.XTicsUser == True:
            meridian = np.linspace(Graph.XTicsMin,Graph.XTicsMax,Graph.XTicsNum)
        elif Graph.XTicsListUser == True:
            meridian = Graph.XTicksList
        else:
            meridian = np.linspace(self.Xmin,self.Xmax,15.)

        if (Graph.YTicsStepUser == True):
            parallel = np.linspace(self.Ymin,self.Ymax,1 + abs(int((self.Ymax-self.Ymin)/Graph.YTicsStep)))
        elif Graph.YTicsUser == True:
            parallel = np.linspace(Graph.YTicsMin,Graph.YTicsMax,Graph.YTicsNum)
        elif Graph.YTicsListUser == True:
            parallel = Graph.YTicksList
        else:
            parallel = np.linspace(self.Ymin,self.Ymax,10.)

        baseM.drawcoastlines()
        baseM.fillcontinents(color=self.continentColor,lake_color=self.lakeColor,alpha=0.5,zorder=0)
        if self.grid:
            w_line = 1.0
        else: 
            w_line = 0.0
        baseM.drawparallels(parallel,labels=[1,0,0,0],fontsize=10,linewidth=w_line)
        baseM.drawmeridians(meridian,labels=[0,0,0,1],fontsize=10,linewidth=w_line)
        baseM.drawmapboundary(fill_color=self.boundaryColor)
        mypatch = []
        mycolors = []
        if self.map_type == 'continuity':
            percentile_bin = np.array([1e-2,7.5e-3,5e-3,2.5e-3,1e-3,7.5e-4,5e-4,2.5e-4,1e-4,1e-5])
        else:
            percentile_bin = np.array([10.0,20.0,50.0,75.0,90.0,95.0,97.5,99.0,99.5,99.9])
        for x,y,z in zip(self.longitude,self.latitude,self.percentile):
            rectangle = Rectangle((x,y), self.resolution, self.resolution, linewidth=0)
            mypatch.append(rectangle)
            if self.map_type == 'continuity':
                i = 0
                c_ratio = 0
                while (i < 10 and ((z-percentile_bin[i]) <= 0)):
                    i = i + 1
                    c_ratio = i - 1
            else:
                i = 10
                c_ratio = 10
                while (((z-percentile_bin[i-1]) < 0) and i > 0):
                    i = i - 1
                    c_ratio = i - 1
            mycolors.append(c_ratio)
        bounds = np.linspace(0, 10,11)
        norm = matplotlib.colors.BoundaryNorm(boundaries=bounds, ncolors=235)
        self.myPointPatch = mypatch
        self.myPointColors = np.array(mycolors)
        p = PatchCollection(self.myPointPatch, norm=norm, cmap=plt.get_cmap(self.cm), linewidth=0)       
        p.set_array(self.myPointColors)
        p.set_alpha(0.8)
        if (self.map_type != 'ionoCorrection' and self.contourlines == True):
            X = np.linspace(self.Xmin,self.Xmax,1+int((self.Xmax-self.Xmin)/self.resolution))
            Y = np.linspace(self.Ymin,self.Ymax,1+int((self.Ymax-self.Ymin)/self.resolution))
            Z = np.reshape(mycolors,(len(Y),len(X)))
            if (self.map_type == 'continuity'):
                levels = [4,7]  #4,7 are the index of c_ratio that correspond to the positions in percentile_bin containing the values "1E-3","5E-4"
            else:
                levels = [4,5,7] #4,5,7 are the index of c_ratio that correspond to the positions in percentile_bin containing the values "99.0","99.5","99.9"
            CS = plt.contour(X, Y, Z, levels=levels,colors='k')
            if (self.map_type == 'continuity'):
                CS.levels = ["1E-3","5E-4"]
            else:
                CS.levels = ["99.0","99.5","99.9"]
            plt.clabel(CS,CS.levels,inline=1, fontsize=10,linewidths=3)
        ax.add_collection(p)
        cbarTicks = np.linspace(0.5, 9.5, 10)
        cbarLabel = []
        for percent in percentile_bin:
            if self.map_type == 'continuity':
                cbarLabel.append('<%.1e'%percent)
            else:
                cbarLabel.append('>%.1f'%percent)

        if Graph.WaterMark != "":
            if Graph.WaterMarkSizeSetbyUser == 0:
                #For SBAS maps, the default size is 15 instead of 8
                Graph.WaterMarkSize = 15
            if Graph.WaterMarkPositionSetbyUser == 1:
                plt.annotate(Graph.WaterMark, xy=(Graph.WaterMarkPositionX,Graph.WaterMarkPositionY), xycoords='axes fraction',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
            else:
                if self.map_type == 'continuity':
                    #Continuity maps need to move watermark a bit to the right to set the watermark in the same position as in other SBAS maps
                    plt.annotate(Graph.WaterMark, xy=(.985,1.1), xycoords='axes fraction',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
                else:
                    plt.annotate(Graph.WaterMark, xy=(.95,1.1), xycoords='axes fraction',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)

        ax = plt.gca()
        im = ax.imshow(np.arange(100).reshape((10,10)))
    
        divider = make_axes_locatable(ax)
        cax = divider.append_axes("right", size=0.2, pad=0.05)
        pCbar = plt.colorbar(mappable=p, cax=cax, ticks=cbarTicks)

        pCbar.ax.set_yticklabels(cbarLabel) 
        if (self.Cbarlabel != ""):
            pCbar.ax.set_ylabel(self.Cbarlabel)

        if (self.map_type == 'availability' or self.map_type == 'ionoCorrection'):
            if (Graph.CbarPercentage == True):
                pCbar.ax.set_title('%')
        if (self.SaveFigure == True): 
            try:
                plt.savefig(self.SaveFigurePath)
            except:
                print ("ERROR: %s" %(sys.exc_info()[1]))
        else:
            plt.show()
        return self
##########################################################################
# Name        : Parse
# Description : This function reads from the command line all the 
#               options, and assigns them into the variables.
##########################################################################  
def Parse(value):
    auxValue=""
    mode=0
    try:
        number = str(int(value)-1)
        auxValue = "var["+number+"]"
    except:
        for element in value:
            if (mode==1):
                try:
                    number = str(int(element))
                    #auxValue=auxValue+number
                    n=n+number
                except:
                    mode=0
                    auxValue=auxValue+str(int(n)-1)+"]"
                    #auxValue=auxValue+"]"
            if (mode==0):
                if (element=="$"):
                    auxValue=auxValue+"var["
                    mode=1
                    n=""
                else:
                    auxValue=auxValue+element
        if (mode==1):
            auxValue=auxValue+str(int(n)-1)+"]"
    return auxValue
    
##########################################################################
# Name        : ParseCallback
# Description : When a new option for the graphic is introduced, this 
#               callback is called for storing the new parameter
##########################################################################   
def ParseCallback(option, opt_str, value, parser, Graph):

    if (option.dest=="Title"):
        if PythonVersion == 2:
            Graph.Title = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.Title = value

    if (option.dest=="FractionalTitle"):
        if PythonVersion == 2:
            Graph.FractionalTitle = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.FractionalTitle = value

    if (option.dest=="Xlabel"):
        if PythonVersion == 2:
            Graph.Xlabel = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.Xlabel = value
    
    if (option.dest=="Ylabel"):
        if PythonVersion == 2:
            Graph.Ylabel = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.Ylabel = value
    
    if (option.dest=="filename"):
        Graph.PlotCounter += 1
        Graph.PlotList.append(Plot())
        Graph.PlotList[Graph.PlotCounter-1].FileName = value
    
    if (option.dest=="ColX"):
        if(Graph.PlotCounter==0):
            print ("ERROR: Filename must be given (with '-f' or '--file') before applying specific plot options")
            removeLockFile()
            sys.exit()
        value = Parse(value)
        Graph.PlotList[Graph.PlotCounter-1].ColX = value
        Graph.ColXUser = True
    
    if (option.dest=="ColY"):
        if(Graph.PlotCounter==0):
            print ("ERROR: Filename must be given (with '-f' or '--file') before applying specific plot options")
            removeLockFile()
            sys.exit()
        value = Parse(value)
        Graph.PlotList[Graph.PlotCounter-1].ColY = value
        Graph.ColYUser = True


    if (option.dest=="Cond"):
        if(Graph.PlotCounter==0):
            print ("ERROR: Filename must be given (with '-f' or '--file') before applying specific plot options")
            removeLockFile()
            sys.exit()
        value = Parse(value)
        Graph.PlotList[Graph.PlotCounter-1].Cond = value

    if (option.dest=="PlotLabel"):
        global legend
        legend=True 
        if(Graph.PlotCounter==0):
            print ("ERROR: Filename must be given (with '-f' or '--file') before applying specific plot options")
            removeLockFile()
            sys.exit()
        if PythonVersion == 2:
            Graph.PlotList[Graph.PlotCounter-1].Label = unicode(value, "utf-8", errors="ignore")        
        else:
            Graph.PlotList[Graph.PlotCounter-1].Label = value

    if (option.dest=="Style"):
        if(Graph.PlotCounter==0):
            print ("ERROR: Filename must be given (with '-f' or '--file') before applying specific plot options")
            removeLockFile()
            sys.exit()
        Graph.PlotList[Graph.PlotCounter-1].Style = value

        if (value.count('-')!= 0): 
            Graph.PlotList[Graph.PlotCounter-1].LineWidth = 1.0

    if (option.dest=="MarkerSize"):
        if(Graph.PlotCounter==0):
            print ("ERROR: Filename must be given (with '-f' or '--file') before applying specific plot options")
            removeLockFile()
            sys.exit()
        try:
            Graph.PlotList[Graph.PlotCounter-1].MarkerSize = float(value)
        except:
            print ("ERROR: Invalid value for line marker size")
            removeLockFile()
            sys.exit()

    if (option.dest=="LineWidth"):
        if(Graph.PlotCounter==0):
            print ("ERROR: Filename must be given (with '-f' or '--file') before applying specific plot options")
            removeLockFile()
            sys.exit()
        try:
            Graph.PlotList[Graph.PlotCounter-1].LineWidth = float(value)
        except:
            print ("ERROR: Invalid value for line width")
            removeLockFile()
            sys.exit()
        
    
    if (option.dest=="grid"):
        if (value == "off" or value == "no" ): Graph.grid = False   
        
    if (option.dest=="Xmin"):
        if (str(value) == '*' or value == "auto" ): Graph.XminAuto = True
        else:
            Graph.XminAuto = False
            try:
                Graph.Xmin = float(value)
            except:
                print ("ERROR: Invalid value for X min")
                removeLockFile()
                sys.exit()
                
    if (option.dest=="Xmax"):
        if (str(value) == '*' or value == "auto" ): Graph.XmaxAuto = True
        else:
            Graph.XmaxAuto = False
            try:
                Graph.Xmax = float(value)
            except:
                print ("ERROR: Invalid value for X max")
                removeLockFile()
                sys.exit()
        
    if (option.dest=="Ymin"):
        if (str(value) == '*' or value == "auto" ): Graph.YminAuto = True
        else:        
            Graph.YminAuto = False
            try:
                Graph.Ymin = float(value)
            except:
                print ("ERROR: Invalid value for Y min")
                removeLockFile()
                sys.exit()
    
    if (option.dest=="Ymax"):
        if (str(value) == '*' or value == "auto" ): Graph.YmaxAuto = True
        else:
            Graph.YmaxAuto = False
            try:
                Graph.Ymax = float(value)
            except:
                print( "ERROR: Invalid value for Y max")
                removeLockFile()
                sys.exit()

    if (option.dest=="NumPointsLabel"):
            try:
                Graph.NumPointsLabel = int(value)
                if (Graph.NumPointsLabel<1 or Graph.NumPointsLabel > 10):
                    print ("ERROR: Number of points in label should be a value between 1 and 10")
                    removeLockFile()
                    sys.exit()
            except:
                print ("ERROR: Invalid value for number of points in label")
                removeLockFile()
                sys.exit()

    if (option.dest=="LabelPosition"):
            if (str(value) == "tl" ):
                Graph.LabelPosition = 2
            elif (str(value) == "tc" ):
                Graph.LabelPosition = 9
            elif (str(value) == "tr" ):
                Graph.LabelPosition = 1
            elif (str(value) == "bl" ):
                Graph.LabelPosition = 3
            elif (str(value) == "bc" ):
                Graph.LabelPosition = 8
            elif (str(value) == "br" ):
                Graph.LabelPosition = 4
            elif (str(value) == "cl" ):
                Graph.LabelPosition = 6
            elif (str(value) == "c" ):
                Graph.LabelPosition = 10
            elif (str(value) == "cr" ):
                Graph.LabelPosition = 7
            else:
                Graph.LabelPosition = 11
                values = value.split(",")
                if (len(values) != 2):
                    print ("ERROR: Not a valid label position")
                    removeLockFile()
                    sys.exit()
                try:
                    Graph.LabelPositionX = float(values[0])
                except:
                    Graph.LabelPositionX = -1
                if (Graph.LabelPositionX < -0.05 or Graph.LabelPositionX > 1.3):
                    print ("ERROR: Position X for label must have values between -0.05 and 1.3")
                    removeLockFile()
                    sys.exit()
                try:
                    Graph.LabelPositionY = float(values[1])
                except:
                    Graph.LabelPositionY = -1
                if (Graph.LabelPositionY < -0.05 or Graph.LabelPositionY > 1.15):
                    print ("ERROR: Position Y for label must have values between -0.05 and 1.15")
                    removeLockFile()
                    sys.exit()

    if (option.dest=="PlotColor"):
        if(Graph.PlotCounter==0):
            print ("ERROR: Filename must be given (with '-f' or '--file') before applying specific plot options")
            removeLockFile()
            sys.exit()
        Graph.PlotList[Graph.PlotCounter-1].PlotColorAuto = False
        Graph.PlotList[Graph.PlotCounter-1].PlotColor = value
      
    if (option.dest=="SaveFigure"):
        Graph.SaveFigure = True 
        Graph.SaveFigurePath.append(str(value))

    if (option.dest=="AL"):
        if (str(value) == '*' or value == "auto" ): Graph.ALAuto = True
        else:
            Graph.ALAuto = False
            try:
                Graph.AL = float(value)
            except:
                print ("ERROR: Invalid value for Alarm Limit")
                removeLockFile()
                sys.exit()

    if (option.dest=="resolution_x"):
        if (str(value) == '*' or value == "auto" ): Graph.intervalNo_x_auto = True
        else:
            Graph.intervalNo_x_auto = False
            try:
                Graph.intervalNo_x = int(value)
            except:
                print ("ERROR: Invalid value for X resolution")
                removeLockFile()
                sys.exit()
    if (option.dest=="resolution_y"):
        if (str(value) == '*' or value == "auto" ): Graph.intervalNo_y_auto = True
        else:
            Graph.intervalNo_y_auto = False
            try:
                Graph.intervalNo_y = int(value)
            except:
                print ("ERROR: Invalid value for Y resolution")
                removeLockFile()
                sys.exit()
            
    if (option.dest=="maxpoints"):
        if (str(value) == '*' or value == "auto" ): Graph.maxpoints_auto = True
        else:
            Graph.maxpoints_auto = False
            try:
                Graph.maxpoints = int(value)
            except:
                print ("ERROR: Invalid value for maxpoints")
                removeLockFile()
                sys.exit()

    if (option.dest=="ColName"):
        value = Parse(value)
        Graph.ColName = value
    if (option.dest=="ColRatioV"):
        value = Parse(value)
        Graph.ColRatioV = value
    if (option.dest=="ColRatioH"):
        value = Parse(value)
        Graph.ColRatioH = value
    if (option.dest=="ColMIsV"):
        value = Parse(value)
        Graph.ColMIsV = value
    if (option.dest=="ColMIsH"):
        value = Parse(value)
        Graph.ColMIsH = value
    if (option.dest=="projection"):
       if (value == "lcc" or value == 'lambert'): Graph.projection = "lcc"               
    
    if (option.dest=="cbarMin"):
        Graph.cbarAutoMin = False
        try:
            Graph.cbarMin = float(value)
        except:
            print ("ERROR: Invalid value for cbarMin")
            removeLockFile()
            sys.exit()
    if (option.dest=="cbarMax"):
        Graph.cbarAutoMax = False
        try:
            Graph.cbarMax = float(value)
        except:
            print ("ERROR: Invalid value for cbarMax")
            removeLockFile()
            sys.exit()
    if (option.dest=="cbarInterval"):
        Graph.cbarAutoN = False
        try:
            Graph.cbarInterval = float(value)
        except:
            print ("ERROR: Invalid value for cbarInterval")
            removeLockFile()
            sys.exit()

    if (option.dest=="continentColor"):
        Graph.continentColor = value
    if (option.dest=="lakeColor"):
        Graph.lakeColor = value
    if (option.dest=="boundaryColor"):
        Graph.boundaryColor = value

    if (option.dest=="MapResolution"):
        if(value != "c" and value != "l" and value != "i" and value != "h" and value != "f"):
            print ("ERROR: Invalid Map Resolution. Valid resolutions are: 'c', 'l', 'i', 'h' or 'f'")
            removeLockFile()
            sys.exit()
        Graph.MapResolution = value

    if (option.dest=="WaterMark"):
        if PythonVersion == 2:
            Graph.WaterMark = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.WaterMark = str(value)

    if (option.dest=="WaterMarkColor"):
        Graph.WaterMarkColour = value

    if (option.dest=="WaterMarkSize"):
        Graph.WaterMarkSizeSetbyUser = 1
        Graph.WaterMarkSize = value

    if (option.dest=="WaterMarkPosition"):
        Graph.WaterMarkPositionSetbyUser=1
        values = value.split(",")
        if (len(values) != 2):
            print ("ERROR: WaterMark position parameter must be X,Y")
            removeLockFile()
            sys.exit()
        try:
            Graph.WaterMarkPositionX = float(values[0])
        except:
            print ("ERROR: Invalid value for WaterMark X position")
            removeLockFile()
            sys.exit()
        try:
            Graph.WaterMarkPositionY = float(values[1])
        except:
            print ("ERROR: Invalid value for WaterMark Y position")
            removeLockFile()
            sys.exit()
        

    if (option.dest=="ColourBarLabel"):
        if PythonVersion == 2:
            Graph.Cbarlabel = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.Cbarlabel = str(value)

    if (option.dest=="SBASsystemname"):
        if PythonVersion == 2:
            Graph.SBASsystemName = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.SBASsystemName = str(value)

    if (option.dest=="SBASPRNtext"):
        if PythonVersion == 2:
            Graph.PRNtext = unicode(value, "utf-8", errors="ignore")
        else:
            Graph.PRNtext = str(value)

    if (option.dest=="Xticks"):
        if (Graph.XTicsListUser == True and Graph.XTicsStep == True):
             print ("ERROR: ' --Xticks', '--XticksStep' and '--XticksList' cannot be all set")
             removeLockFile()
             sys.exit()

        if (Graph.XTicsListUser == True):
            print ("ERROR: '--Xticks' and '--XticksList' options cannot be both set")
            removeLockFile()
            sys.exit()

        if (Graph.XTicsStep == True):
            print ("ERROR: '--Xticks' and '--XticksStep' options cannot be both set")
            removeLockFile()
            sys.exit()

        Graph.XTicsUser = True
        values = value.split(",")
        if (len(values) != 3):
            print ("ERROR: X tick parameter must be Xmin,Xmax,NumberOfTicks")
            removeLockFile()
            sys.exit()
        try:
            Graph.XTicsMin = float(values[0])
        except:
            print ("ERROR: Invalid value for X ticks minimum")
            removeLockFile()
            sys.exit()
        try:
            Graph.XTicsMax = float(values[1])
        except:
            print ("ERROR: Invalid value for X ticks maximum")
            removeLockFile()
            sys.exit()
        try:
            Graph.XTicsNum = int(values[2])
        except:
            print ("ERROR: Invalid value for X ticks number")
            removeLockFile()
            sys.exit()
        if (Graph.XTicsMax <= Graph.XTicsMin):
            print ("ERROR: X ticks maximum must be greater than the X ticks minimum")
            removeLockFile()
            sys.exit()

    if (option.dest=="Yticks"):
        if (Graph.YTicsListUser == True and Graph.YTicsStep == True):
             print ("ERROR: ' --Yticks', '--YticksStep' and '--YticksList' cannot be all set")
             removeLockFile()
             sys.exit()

        if (Graph.YTicsListUser == True):
            print ("ERROR: '--Yticks' and '--YticksList' options cannot be both set")
            removeLockFile()
            sys.exit()

        if (Graph.YTicsStep == True):
            print ("ERROR: '--Yticks' and '--YticksStep' options cannot be both set")
            removeLockFile()
            sys.exit()

        Graph.YTicsUser = True
        values = value.split(",")
        if (len(values) != 3):
            print ("ERROR: Y tick parameter must be Ymin,Ymax,NumberOfTicks")
            removeLockFile()
            sys.exit()
        try:
            Graph.YTicsMin = float(values[0])
        except:
            print ("ERROR: Invalid value for Y ticks minimum")
            removeLockFile()
            sys.exit()
        try:
            Graph.YTicsMax = float(values[1])
        except:
            print ("ERROR: Invalid value for Y ticks maximum")
            removeLockFile()
            sys.exit()
        try:
            Graph.YTicsNum = int(values[2])
        except:
            print ("ERROR: Invalid value for Y ticks number")
            removeLockFile()
            sys.exit()
        if (Graph.YTicsMax <= Graph.YTicsMin):
            print ("ERROR: Y ticks maximum must be greater than the Y ticks minimum")
            removeLockFile()
            sys.exit()

    if (option.dest=="XticksStep"):
        if (Graph.XTicsListUser == True and Graph.XTicsUser == True):
            print ("ERROR: ' --XticksStep', '--Xticks' and '--XticksList' cannot be all set")
            removeLockFile()
            sys.exit()

        if (Graph.XTicsListUser == True):
            print ("ERROR: '--XticksStep' and '--XticksList' options cannot be both set")
            removeLockFile()
            sys.exit()

        if (Graph.XTicsUser == True):
            print ("ERROR: '--XticksStep' and '--Xticks' options cannot be both set")
            removeLockFile()
            sys.exit()

        Graph.XTicsStepUser = True
        try:
            Graph.XTicsStep = float(value)
        except:
            print ("ERROR: Invalid value for X ticks step")
            removeLockFile()
            sys.exit()

    if (option.dest=="YticksStep"):
        if (Graph.YTicsListUser == True and Graph.YTicsUser == True):
            print ("ERROR: ' --YticksStep', '--Yticks' and '--YticksList' cannot be all set")
            removeLockFile()
            sys.exit()

        elif (Graph.YTicsListUser == True):
            print ("ERROR: '--YticksStep' and '--YticksList' options cannot be both set")
            removeLockFile()
            sys.exit()

        elif (Graph.YTicsUser == True):
            print ("ERROR: '--YticksStep' and '--Yticks' options cannot be both set")
            removeLockFile()
            sys.exit()

        Graph.YTicsStepUser = True
        try:
            Graph.YTicsStep = float(value)
        except:
            print ("ERROR: Invalid value for Y ticks step")
            removeLockFile()
            sys.exit()


    if (option.dest=="XticksList"):
        if (Graph.XTicsStep == True and Graph.XTicsUser == True):
            print ("ERROR: ' --XticksList', '--Xticks' and '--XticksStep' cannot be all set")
            removeLockFile()
            sys.exit()

        elif (Graph.XTicsUser == True):
            print ("ERROR: '--XticksList' and '--Xticks' options cannot be both set")
            removeLockFile()
            sys.exit()

        elif (Graph.XTicsStepUser == True):
            print ("ERROR: '--XticksList' and '--XticksStep' options cannot be both set")
            removeLockFile()
            sys.exit()
        
        Graph.XTicsListUser = True
        values = value.split(",")
        if (len(values) <1):
            print ("ERROR: X tick list parameter must be comma separated list with at least one number")
            removeLockFile()
            sys.exit()
        else:
            for elem in values:
                try:
                    Graph.XTicksList.append(float(elem))
                except:
                    print ("ERROR: Invalid value '" + elem + "' for X ticks list")
                    removeLockFile()
                    sys.exit()

            Graph.XTicksList = sorted (Graph.XTicksList)

    if (option.dest=="YticksList"):
        if (Graph.YTicsStep == True and Graph.YTicsUser == True):
            print ("ERROR: ' --YticksList', '--Yticks' and '--YticksStep' cannot be all set")
            removeLockFile()
            sys.exit()

        elif (Graph.YTicsUser == True):
            print ("ERROR: '--YticksList' and '--Yticks' options cannot be both set")
            removeLockFile()
            sys.exit()

        elif (Graph.YTicsStepUser == True):
            print ("ERROR: '--YticksList' and '--YticksStep' options cannot be both set")
            removeLockFile()
            sys.exit()

        Graph.YTicsListUser = True
        values = value.split(",")
        if (len(values) <1):
            print ("ERROR: Y tick list parameter must be comma separated list with at least one number")
            removeLockFile()
            sys.exit()
        else:
            for elem in values:
                try:
                    Graph.YTicksList.append(float(elem))
                except:
                    print ("ERROR: Invalid value '" + elem + "' for Y ticks list")
                    removeLockFile()
                    sys.exit()
            Graph.YTicksList = sorted (Graph.YTicksList)


##########################################################################
# Name        : readFile
# Description : Read the input file, according to the plotting condition,  
#               assign the value to Xvar and Yvar
##########################################################################   
def readFile(fileN, cond, colX, colY):
    try:
        f = open(fileN,'r')
    except:
        print ("ERROR Reading file '" + fileN + "'")
        removeLockFile()
        sys.exit()
    Xvar = []
    Yvar = []
    for line in f:
        var=line.split()
        j=0
        for ele in var:
            try:
                auxEle = float(ele)
                var[j] = auxEle
                j += 1
            except:
                j += 1
        if (cond != ""):
            try:
                ret = eval(cond)
            except:
                ret = False
        else:
            ret = True
        if (ret==True):
            error = 0
            try:
                ret1 = eval(colX)
            except:
                error = 1
            
            try:
                ret2 = eval(colY)
            except:
                error = 1
            if (error==0):
                Xvar.append(ret1)
                Yvar.append(ret2)
    f.close()
    return Xvar, Yvar 

##########################################################################
# Name        : removeLockFile
# Description : Remove lockfile '.plot.lock' inside a try/catch in order
#                 to avoid race conditions
##########################################################################   
def removeLockFile():
    if (CreateLockFile==True):
        if (os.path.isfile(LockFile)==True): 
            try:
                os.remove(LockFile)
            except:
                #It will enter here if after checking that the LockFile exists,
                #this instance is stopped before removing the file and another
                #instance removes the file. As the file will be erased, we don't
                #need to do anything
                pass

    return
        
##########################################################################
# Name        : MakeGraph
# Description : This function makes the graphic, from the parameters
#               already parsed.
##########################################################################

        
def MakeGraph():
    i=0
    if Graph.stanford:
        sfp = stanford()
        sfp.PE, sfp.PL = readFile(Graph.PlotList[i].FileName, Graph.PlotList[i].Cond, Graph.PlotList[i].ColX, Graph.PlotList[i].ColY)
        if (Graph.ALAuto == False): sfp.AL = Graph.AL
        if (Graph.resolution_x_auto == False): sfp.resolution_x = Graph.resolution_x
        if (Graph.resolution_y_auto == False): sfp.resolution_y = Graph.resolution_y
        sfp.dealData()
        sfp.getPoints()
        sfp.plotPoints()
        if (Graph.XmaxAuto == False): sfp.Xmax = Graph.Xmax 
        if (Graph.XminAuto == False): sfp.Xmin = Graph.Xmin 
        if (Graph.YmaxAuto == False): sfp.Ymax = Graph.Ymax 
        if (Graph.YminAuto == False): sfp.Ymin = Graph.Ymin 
        if Graph.clean:
            x = [sfp.Xmin,sfp.Xmax]
            y = x
            plt.plot(x, y,'black')
        else:
            sfp.plotPatch()
        if (Graph.Xlabel != ""): sfp.Xlabel =Graph.Xlabel
        if (Graph.Ylabel != ""): sfp.Ylabel =Graph.Ylabel
        if (Graph.Title != ""): sfp.Title =Graph.Title
        if (Graph.sigmaX == True or Graph.sigmaY == True):
             sfp.sigmaX = Graph.sigmaX
             sfp.sigmaY = Graph.sigmaY
             sfp.getPercentileCount()
        sfp.grid = Graph.grid
        sfp.SaveFigure = Graph.SaveFigure
        if (sfp.SaveFigure == True):
            sfp.SaveFigurePath = Graph.SaveFigurePath[0]
        removeLockFile()
        sfp.plotShow()
    elif Graph.stanfordESA:
        sfESA = stanfordESA()
        sfESA.f = Graph.PlotList[i].FileName
        if (Graph.maxpoints_auto == False): sfESA.maxpoints = Graph.maxpoints
        sfESA.readData()
        if (Graph.resolution_x_auto == False): sfESA.resolution_x = Graph.resolution_x
        if (Graph.resolution_y_auto == False): sfESA.resolution_y = Graph.resolution_y
        if (Graph.XmaxAuto == False): sfESA.Xmax = Graph.Xmax 
        if (Graph.XminAuto == False): sfESA.Xmin = Graph.Xmin 
        if (Graph.YmaxAuto == False): sfESA.Ymax = Graph.Ymax 
        if (Graph.YminAuto == False): sfESA.Ymin = Graph.Ymin 
        if (Graph.Xlabel != ""): sfESA.Xlabel =Graph.Xlabel
        if (Graph.Ylabel != ""): sfESA.Ylabel =Graph.Ylabel
        if (Graph.Title != ""): sfESA.Title =Graph.Title
        sfESA.grid = Graph.grid
        sfESA.SaveFigure = Graph.SaveFigure
        if (sfESA.SaveFigure == True):
           sfESA.SaveFigurePath1 = Graph.SaveFigurePath[0]
        x = sfESA.x
        y = sfESA.y
        vertical = sfESA.verticalNo
        horizontal = sfESA.horizontalNo
        
        fig1 = plt.figure()
        ax1 = fig1.add_subplot(111)
        if Graph.AdjustToMargin == True:
            fig1.tight_layout() #This is to adjust plot to margins
            fig1.subplots_adjust(top=.94,bottom=0.1,left=0.09,right=1.01)
            #Add space to fit multiline title
            NumNewlines=sfESA.Title.count('\n')
            if NumNewlines == 1:
                fig1.subplots_adjust(top=.9)
            elif NumNewlines == 2:
                fig1.subplots_adjust(top=.87)
            elif NumNewlines > 2:
                fig1.subplots_adjust(top=.83)
        sfESA.getPoints(x,y,vertical)
        if (Graph.Xlabel == ""): sfESA.Xlabel = "Vertical Positioning Error (metres)"
        if (Graph.Ylabel == ""): sfESA.Ylabel = "Vertical Protection Level (metres)"
        ax1.text(2*sfESA.Xmax/5, sfESA.Ymax/5, 'N Geoms VPE>VPL: %d' %sfESA.n_fail , style='italic')
        sfESA.plotPoints(ax1)
        if (sfESA.SaveFigure == True):
            try:
                plt.savefig(Graph.SaveFigurePath[0])
            except:
                print ("ERROR: %s" %(sys.exc_info()[1]))
        fig2 = plt.figure()
        ax2 = fig2.add_subplot(111)
        if Graph.AdjustToMargin == True:
            fig2.tight_layout() #This is to adjust plot to margins
            fig2.subplots_adjust(top=.94,bottom=0.1,left=0.09,right=1.01)
            #Add space to fit multiline title
            NumNewlines=sfESA.Title.count('\n')
            if NumNewlines == 1:
                 fig2.subplots_adjust(top=.9)
            elif NumNewlines == 2:
                fig2.subplots_adjust(top=.87)
            elif NumNewlines > 2:
                fig2.subplots_adjust(top=.83)
        sfESA.getPoints(x,y,horizontal)
        if (Graph.Xlabel == ""): sfESA.Xlabel = "Horizontal Positioning Error (metres)"
        if (Graph.Ylabel == ""): sfESA.Ylabel = "Horizontal Protection Level (metres)"
        ax2.text(2*sfESA.Xmax/5, sfESA.Ymax/5, 'N Geoms HPE>HPL: %d' %sfESA.n_fail , style='italic')
        sfESA.plotPoints(ax2)

        removeLockFile()
        if (sfESA.SaveFigure ==True) and (len(Graph.SaveFigurePath) > 1):
            try:
                plt.savefig(Graph.SaveFigurePath[1])
            except:
                print ("ERROR: %s" %(sys.exc_info()[1]))
        if (sfESA.SaveFigure == False):
            plt.show()
    elif Graph.worstIntegrityRatio:
        wir = WIRmap()
        wir.f = Graph.PlotList[i].FileName
        wir.colName = Graph.ColName
        wir.colX = Graph.PlotList[i].ColX
        wir.colY = Graph.PlotList[i].ColY
        wir.colRatioV = Graph.ColRatioV
        wir.colRatioH = Graph.ColRatioH
        wir.colMIsV = Graph.ColMIsV
        wir.colMIsH = Graph.ColMIsH
        wir.grid = Graph.grid
        wir.readData()
        wir.projection = Graph.projection
        wir.ms = 30*Graph.PlotList[i].MarkerSize
        if (Graph.XmaxAuto == False): wir.Xmax = Graph.Xmax 
        if (Graph.XminAuto == False): wir.Xmin = Graph.Xmin 
        if (Graph.YmaxAuto == False): wir.Ymax = Graph.Ymax 
        if (Graph.YminAuto == False): wir.Ymin = Graph.Ymin 
        if (Graph.Title != ""): wir.Title =Graph.Title
        if (Graph.Xlabel != ""): wir.Xlabel =Graph.Xlabel
        if (Graph.Ylabel != ""): wir.Ylabel =Graph.Ylabel
        if (Graph.cbarAutoMin == False): wir.cbarMin = Graph.cbarMin
        if (Graph.cbarAutoMax == False): wir.cbarMax = Graph.cbarMax
        if (Graph.cbarAutoN == False): wir.cbarInterval = Graph.cbarInterval
        if (Graph.continentColor != ""): wir.continentColor = Graph.continentColor
        if (Graph.lakeColor != ""): wir.lakeColor = Graph.lakeColor
        if (Graph.boundaryColor != ""): wir.boundaryColor = Graph.boundaryColor
        wir.SaveFigure = Graph.SaveFigure
        if(wir.SaveFigure==True):
            wir.SaveFigurePath = Graph.SaveFigurePath
        removeLockFile()
        wir.drawMap()
    elif Graph.SBASmaps:
        sbas = SBASmaps()
        sbas.f = Graph.PlotList[i].FileName
        sbas.grid = Graph.grid
        sbas.contourlines = Graph.contourlines
        if (Graph.SBASsystemName != ""): sbas.SBASsystemName = Graph.SBASsystemName
        if (Graph.PRNtext != ""): sbas.PRNtext = Graph.PRNtext
        if (Graph.PRNtextNewline == True ): sbas.PRNtextNewline = True
        sbas.readData()
        if (Graph.Title != ""): sbas.Title =Graph.Title
        if (Graph.Xlabel != ""): sbas.Xlabel =Graph.Xlabel
        if (Graph.Ylabel != ""): sbas.Ylabel =Graph.Ylabel
        if (Graph.Cbarlabel != ""): sbas.Cbarlabel =Graph.Cbarlabel
        if (Graph.continentColor != ""): sbas.continentColor = Graph.continentColor
        if (Graph.lakeColor != ""): sbas.lakeColor = Graph.lakeColor
        if (Graph.boundaryColor != ""): sbas.boundaryColor = Graph.boundaryColor
        sbas.SaveFigure = Graph.SaveFigure
        if(sbas.SaveFigure==True):
            sbas.SaveFigurePath = Graph.SaveFigurePath[0]
        removeLockFile()
        sbas.drawMap()
    else:
        ax1 = pylab.subplot(111)
        while i<Graph.PlotCounter:
            Graph.PlotList[i].Xvar, Graph.PlotList[i].Yvar = readFile(Graph.PlotList[i].FileName, Graph.PlotList[i].Cond, Graph.PlotList[i].ColX, Graph.PlotList[i].ColY)
            try:
                if (Graph.PlotList[i].PlotColorAuto == False):
                    pylab.plot(Graph.PlotList[i].Xvar,Graph.PlotList[i].Yvar,Graph.PlotList[i].Style,label=Graph.PlotList[i].Label,color=Graph.PlotList[i].PlotColor,markersize=Graph.PlotList[i].MarkerSize,linewidth=Graph.PlotList[i].LineWidth)
                else:
                    pylab.plot(Graph.PlotList[i].Xvar,Graph.PlotList[i].Yvar,Graph.PlotList[i].Style,label=Graph.PlotList[i].Label,markersize=Graph.PlotList[i].MarkerSize,linewidth=Graph.PlotList[i].LineWidth)
            except:
                removeLockFile()
                print (sys.exc_info()[1])
                sys.exit()
    
            i+=1
        
        #Set Max and min values for plots, retrieving this values if they are automatically set
        if (Graph.XmaxAuto == False): 
            pylab.xlim( xmax=Graph.Xmax )
            MaxXtick = Graph.Xmax
        else:
            Tmptick = ax1.get_xlim()
            MaxXtick = Tmptick[1]

        if (Graph.XminAuto == False): 
            pylab.xlim( xmin=Graph.Xmin )
            MinXtick = Graph.Xmin
        else:
            Tmptick = ax1.get_xlim()
            MinXtick = Tmptick[0] 

        if (Graph.YmaxAuto == False): 
            pylab.ylim( ymax=Graph.Ymax )
            MaxYtick = Graph.Ymax
        else:
            Tmptick = ax1.get_ylim()
            MaxYtick = Tmptick[1]

        if (Graph.YminAuto == False): 
            pylab.ylim( ymin=Graph.Ymin )
            MinYtick = Graph.Ymin
        else:
            Tmptick = ax1.get_ylim()
            MinYtick = Tmptick[0] 

        #Set manual ticks if user set them
        if Graph.XTicsUser == True:
            ax1.set_xticks(pylab.linspace(Graph.XTicsMin,Graph.XTicsMax,Graph.XTicsNum))
        elif Graph.XTicsStepUser == True:
            ax1.set_xticks(pylab.linspace(MinXtick,MaxXtick,abs(int((MaxXtick-MinXtick)/Graph.XTicsStep))+1))
        elif Graph.XTicsListUser == True:
            ax1.set_xticks(Graph.XTicksList)

        if Graph.YTicsUser == True:
            ax1.set_yticks(pylab.linspace(Graph.YTicsMin,Graph.YTicsMax,Graph.YTicsNum))
        elif Graph.YTicsStepUser == True:
            ax1.set_yticks(pylab.linspace(MinYtick,MaxYtick,abs(int((MaxYtick-MinYtick)/Graph.YTicsStep))+1))
        elif Graph.YTicsListUser == True:
            ax1.set_yticks(Graph.YTicksList)

        pylab.xlabel(Graph.Xlabel)
        pylab.ylabel(Graph.Ylabel)
        pylab.title(Graph.Title)
        if Graph.AdjustToMargin == True:
            pylab.tight_layout() #Adjust plot to margins
            #Add margin on top to fit title with multiple lines (if necessary)
            NumNewlines=Graph.Title.count('\n')
            if NumNewlines == 1:
                pylab.subplots_adjust(top=.9)
            elif NumNewlines == 2:
                pylab.subplots_adjust(top=.87)
            elif NumNewlines > 2:
                pylab.subplots_adjust(top=.83)


        if Graph.WaterMark != "":
            if Graph.AdjustToMargin == True:
                if Graph.WaterMarkPositionSetbyUser == 1:
                    pylab.annotate(Graph.WaterMark, xy=(Graph.WaterMarkPositionX,Graph.WaterMarkPositionY), xycoords='figure fraction', horizontalalignment='right', verticalalignment='bottom',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
                else:
                    pylab.annotate(Graph.WaterMark, xy=(.96, .11), xycoords='figure fraction', horizontalalignment='right', verticalalignment='bottom',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
            else:
                if Graph.WaterMarkPositionSetbyUser == 1:
                    pylab.annotate(Graph.WaterMark, xy=(Graph.WaterMarkPositionX,Graph.WaterMarkPositionY), xycoords='figure fraction', horizontalalignment='right', verticalalignment='bottom',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
                else:
                    pylab.annotate(Graph.WaterMark, xy=(.89, .11), xycoords='figure fraction', horizontalalignment='right', verticalalignment='bottom',style='italic', fontsize = Graph.WaterMarkSize, color=Graph.WaterMarkColour)
        if (Graph.FractionalTitle != ""):
            if Graph.AdjustToMargin == True:
                #Add margin for fractional title if none set
                if NumNewlines == 0:
                    pylab.subplots_adjust(top=.9)
            pylab.annotate(Graph.FractionalTitle, xy=(.025, .975), xycoords='figure fraction', horizontalalignment='left', verticalalignment='top')
    
        if Graph.grid:
            pylab.grid(True)
        
    
    #######        pylab.legend(numpoints=1, borderpad=0.25,handlelength=20,columnspacing=1,ncol=2)
    # ok    pylab.legend(numpoints=1, handlelength=0.2) 
    #        pylab.legend(numpoints=1,  borderpad=0.2)
    #DEF:
    #       pylab.legend(numpoints=1, borderpad=0.2,bbox_to_anchor=(0.85, 1), lo    c=2, ncol=1)
    #       pylab.legend(numpoints=1, borderpad=0.2,bbox_to_anchor=(-0.08, 0.975    ), loc=2, ncol=6, handlelength=-0.0, columnspacing=0.50)
    
        if (legend==True):
            if (Graph.LabelPosition == 11):
                pylab.legend(numpoints=Graph.NumPointsLabel,bbox_to_anchor=(Graph.LabelPositionX,Graph.LabelPositionY))
            else: 
                pylab.legend(numpoints=Graph.NumPointsLabel,loc=Graph.LabelPosition) 
            #pylab.legend(numpoints=1,bbox_to_anchor=(1.12, 1)) #Use this to align the label to the upper right corner (outside the plot)
            #pylab.legend(numpoints=1,bbox_to_anchor=(1, 1)) #Use this to align the label to the upper right corner (inside the plot)
            #pylab.legend(numpoints=1,bbox_to_anchor=(0.32, 1)) #Use this to align the label to the upper left corner (after the scale)
            #pylab.legend(numpoints=1,bbox_to_anchor=(0.32, .22)) #Use this to align the label to the bottom left corner (after the scale)
            #pylab.legend(numpoints=1,bbox_to_anchor=(.42,1)) 
            #pylab.legend(numpoints=1,bbox_to_anchor=(1, .22)) #Use this to align the label to the bottom right corner (inside the plot)
            #pylab.legend(numpoints=1,bbox_to_anchor=(1.12, .22)) #Use this to align the label to the bottom right corner (outside the plot)
        
        removeLockFile()
            
        if (Graph.SaveFigure==True):
            try:
                pylab.savefig(Graph.SaveFigurePath[0])
            except:
                print ("ERROR: %s" %(sys.exc_info()[1]))
        else:   
            pylab.show()
        
        
        
        

        
##########################################################################
# Name        : 
# Description : Main execution thread
##########################################################################
  
Graph = Graphic()


HelpHeader = """
#############################################################################
# Copyright: gAGE/UPC & ESA
# Project: EDUNAV GNSS Lab Tool
# Authors: Adria Rovira-Garcia (group of Astronomy and GEomatics - gAGE/UPC)
#          Pere Ramos-Bosch (group of Astronomy and GEomatics - gAGE/UPC)
# Curator: Adria Rovira-Garcia ( gAGE/UPC )
# Developer: Yixie Shao ( gAGE/UPC )
#            Deimos Ibanez Segura ( gAGE/UPC )
#          glab.gage @ upc.edu           
# File: graph.py
# Code Management Tool File Version: 5.2  Revision: 0
# Date: 2018/03/09
#############################################################################


GRAPHIC GENERAL OPTIONS (default options):

  The General Options are the ones that can be specified once per graphic,
  and will affect the entire graphic window:
  
  -h, --help                    Show this help message and exit
  
  -t, --title, --tit            Set the title of the Graphic
  
  --Xlabel, --xlab, --xl        Set the x-axis label
  
  --Ylabel, --ylab, --yl        Set the y-axis label
  
  --Xmin, --xmin, --xn          The minimum value for the x axis to be plot, if 
                                no value is provided, automatic limits are set.  
                                
  --Xmax, --xmax, --xx          The maximum value for the x axis to be plot, if 
                                no value is provided, automatic limits are set.
                                
  --Ymin, --ymin, --yn          The minimum value for the y axis to be plot, if 
                                no value is provided, automatic limits are set.
                                
  --Ymax, --ymax, --yx          The maximum value for the y axis to be plot, if 
                                no value is provided, automatic limits are set. 

  --Xticks, --xticks, --xt      Set the ticks for x axis. The values must be 
                                given in this format: Xmin,Xmax,NumberOfTicks
                                (this parameter is incompatible with --XticksStep
                                and --XTicksList). See note below.

  --Yticks, --yticks, --yt      Set the ticks for y axis. The values must be 
                                given in this format: Ymin,Ymax,NumberOfTicks
                                (this parameter is incompatible with --YticksStep
                                and --YTicksList). See note below


  --XticksStep, --xticksstep,   Set the ticks step for x axis (this parameter
  --xts                         is incompatible with --Xticks and --XTicksList).

  --YticksStep, --yticksstep,   Set the ticks step for y axis (this parameter
  --yts                         is incompatible with --Yticks and --YTicksList).

  --XTicksList, --xtickslist,   Set the list of ticks for x axis. The list does
  --xtl                         not to be ordered and must be comma (',') separated. 
                                (this parameter is incompatible --Xticks and --XticksStep).

  --YTicksList, --ytickslist,   Set the list of ticks for y axis. The list does
  --ytl                         not to be ordered and must be comma (',') separated. 
                                (this parameter is incompatible --Yticks and --YticksStep).

  --Ftitle, --ftitle, --ft      Add a fractional title to the upper left corner.

  --wm, --watermark             Add a watermark with the given label.

  --wmc, --watermarkcolor       Sets the watermark colour.
                                The following colours are supported:
                                'b'     blue
                                'g'     green
                                'r'     red
                                'c'     cyan
                                'm'     magenta
                                'y'     yellow
                                'k'     black [DEFAULT]
                                'w'     white

  --wms, --watermarksize        Set the size of the watermark (default is 8)

  --wmp,--watermarkposition     Set the X and Y position of the watermark. The position
                                must be given relative to the lower left corner of the plot,
                                and  with the X and Y values given a comma separated string.
                                For example, to set the default position of the watermark in
                                SBAS plots (lower right corner), the parameter should be
                                provided as ".87,.03"


  --AdjustToMargin, --atm,      Expand the figure to fit the image margin.
  --adjusttomargin

  --no-lock-file                Do not create the ".plot.lock" file. This file is necessary
                                to synchronize graph.py with the GUI, but not in command line.
  

  NOTE:  In '--Xticks' or '--Yticks' options, the maximum and minimum can be different from
         the plot range (it is an independent range). The number of ticks (NumberOfTicks)
         should be computed with the following formula:

         NumberOfTicks = 1 + ToInteger((MaxTick-MinTick)/TickResolution)


 
  Example:
       graph.py -t "Graphic title" --xl "time (s)" --yl "Altitude [m]"
      --xmin -3.0 --ymax 5.0 --xticks 0,24,7


PLOT DEPENDENT OPTIONS (default options):

  The Plot Dependent Options are specific to each plot.
  One new plot is considered from the point that a '-f' or '--file' is found. 
  All the options coming after this parameter belong to that specific plot.
  
  -f, --file                    Set the input file name for the specific plot.
  
  -x, -X, --Xcol                Set the source of the x axis: 
                                -x 4 or -x '$4' : will take as x axis the 4th
                                column of the input file.
                                
                                Operations can be done in this parameter, such as:
                                -x '($4-$5)': This will take the difference between
                                the 4th and the 5th column 
                                
                                Mathematical functions and constants are supported:
                                -x '(math.sin($12*math.pi/180)'
                                
  -y, -Y, --Ycol                Set the source of the y axis
                                Identical properties as x column

                                
  -c, --cond                    Specify the plotting condition:
                                -c '($6>=10)' Include the 6th column if it is 
                                equal or greater than 10
                                
                                -c '($1==\"OUTPUT\")' Include the 1st column by a specific
                                string: surrounding the string by \"  
                                
                                Mathematical functions, booleans and constants are supported:
                                -c '($1==\"POSTFIT\")&(math.e($12+$5)>5.0)'

                                NOTE: Windows users have to exchange the ' for \" and the \" for '
                                      when specifying a condition. For example, the following
                                      condition: 
                                            -c '($1==\"POSTFIT\")&(math.e($12+$5)>5.0)'
                                      is valid in Linux, but in Windows it shall be written like this:
                                            -c \"($1=='POSTFIT')&(math.e($12+$5)>5.0)\"
                                              
                                
  -l, --label, --plotlabel      Enables the label for the current plot

  --npl, --numpointslabel       Set the number of points to be shown in the label.
                                If no value is provided, it is set to 2 [DEFAULT]

  --lp, --labelpos, --labelPos  Set the position of the label in the plot.
                                The following values are supported:
                                'tl'             top    left
                                'tc'             top    center
                                'tr'             top    right [DEFAULT]
                                'bl'             bottom left
                                'bc'             bottom center
                                'br'             bottom right
                                'cl'             center left
                                'c'              center
                                'cr'             center right
                                'coordX,coordY'  user defined position 
                                                  coordX values must be between [-0.05,1.3]
                                                  coordY values must be between [-0.05,1.15]

  -s, --style                   Sets the style for the current plot  
                                The following styles are supported:
                                '.'     circle marker [DEFAULT]
                                '-'     solid line style
                                '--'    dashed line style
                                '-.'    dash-dot line style
                                '.-'    dots joined with lines
                                'o'     point marker
                                's'     square marker
                                'p'     pentagon marker
                                '+'     plus marker
                                'x'     x marker
                                
    For a full list of styles, see http://matplotlib.org/api/pyplot_api.html#matplotlib.pyplot.plot
                                
  --color, --cl                 Sets the colour for the current plot
                                The following colours are supported:
                                'b'     blue [DEFAULT]
                                'g'     green
                                'r'     red
                                'c'     cyan
                                'm'     magenta
                                'y'     yellow
                                'k'     black
                                'w'     white

  --markersize, --ms            Sets the plot maker size 5 by [DEFAULT]

  --linewidth, --lw             Sets the plot maker size 0 by [DEFAULT]
  
  -g, --grid                    Set the plot with grid by [DEFAULT]
                                It could be turn off by 'off' or 'no'

  Example:
       graph.py -f /home/gLAB/Example -x '(math.sin($1*math.pi/180))' -y 2 
       -l "Plot Label" --style p --color cyan   
                                   

                                

MULTIPLE PLOTS:

  Each graphic window can contain several plots. One new plot is considered 
  from the point that a '-f' or '--file' is found:
      Graphic General Options: will apply to all the plots present
      Plot Dependent options: parameters specific to each plot.
  
  Example:
       graph.py -f /home/gLAB/Example -x '1' -y '2' -f /home/gLAB/Example -x '2' -y '1'


SAVE CURRENT GRAPHIC:

  User can save the entire graphic window into the path specified. If no path 
  is specified, it will be allocated in the current working directory.
  The graphic output format is deduced from the extension of the file name, if no
  extension is provided a 'png' extension type will be used: 
                         
  
  --save, --sv                  Stores the graphic window given a file name. The graphic
                                output format is deduced from the extension of the file name.
                                Supported formats are: 
                                emf, eps, jpeg, jpg, pdf, png [DEFAULT], ps, raw, rgba, svg, svgz.
                                
  Example:
       graph.py -f /home/gLAB/Example -x 1 -y 2 --save Figure_Example
       graph.py -f /home/gLAB/Example -x 1 -y 2 --sv /home/Desktop/Figure_Example.eps



       
STANFORD PLOT:

  In this mode: 
  
  For GRAPHIC GENERAL OPTIONS, all the options work the same way as in the default plots,
                               except the options "--Ftitle" (add a fractional title), "--xt" and "--yt" (for setting ticks) which are disabled. 
                               
  For PLOT DEPENDENT OPTIONS, the options "-f", "-x", "-y", "-c", "-g" work the same way as in the default plots,
                              while the other options in this part are disabled in this mode.
                              "-x" and "-y" options can also be written as "--error" and "--pl" respectively.
                              
  MULTIPLE PLOTS are disabled in this mode.
  
  For SAVE CURRENT GRAPHIC, it works the same way as for the other kind of plots.
  
  --stanford, --sf, --sp        Make a stanford plot.
                                
  --AL, --al                    Set the alarm limit for the protection level, if 
                                no value is provided, AL is set to 40 [DEFAULT].                                              

  --clean                       Make a stanford Plot without failure patches.

  --xr,   --xresolution         Set the resolution in x-direction of the plot. 
                                If no value is provided, it is set to 0.5 [DEFAULT].

  --yr,   --yresolution         Set the resolution in y-direction of the plot. 
                                If no value is provided, it is set to 0.5 [DEFAULT].

  --percentileX, --percentilex  Show ticks where the percentiles 68, 95 and 99.9
                                of the points are reached in the horizontal axis.

  --percentileY, --percentiley  Show ticks where the percentiles 68, 95 and 99.9
                                of the points are reached in the vertical axis.

 Example:
        graph.py -f /home/gLAB/Example -x 1 -y 2 --sf
        

STANFORD-ESA PLOT:

  In this mode: 
  
  The input file should have this fixed format (this is gLAB's output format):

  The first three lines have the header with this format (numerical values can vary according to the plot):
  
  #XSTEP  YSTEP  XMAX  YMAX
   0.100  0.100  50.0  50.0
  # XPOS   YPOS  NUM_HOR  NUM_VER

  Since the fourth row, each row should provide the values: positioning error, protection level, 
    number of horizontal values (at the given coordinate), number of vertical values

  For GRAPHIC GENERAL OPTIONS, all the options work the same way as in the default plots
                               except the option "--Ftitle" (add a fractional title),  "--xt" and "--yt" (for setting ticks) which are disabled.
                               
  For PLOT DEPENDENT OPTIONS, the options "-f" works the same way as in the default plots,
                              while the other options in this part are disabled in this mode.
                              
  MULTIPLE PLOTS are disabled in this mode.
  
  For SAVE CURRENT GRAPHIC, since it has two plots, then two save paths should be provided. If only one path is provided,
                            only the vertical plot will be saved.

  --stanfordESA, --sfesa, --spesa        Make a stanford-ESA plot.

 Examples: 
       graph.py -f /home/gLAB/Example --sfesa --sv /home/Desktop/Figure_Vertical.eps --sv /home/Desktop/Figure_Horizontal.eps
                                
       graph.py -f /home/gLAB/Example --sfesa


WORLD MAP / STATION NAME MAP / WORST INTEGRITY RATIO PLOTS:
  In this mode: One, two or three plots can be generated depending on the input.

  The input file should contain the following fields: station name, geodetic coordinates (in degrees) and the values to be plotted.
  Parameter "-x": longitude (degrees)
  Parameter "-y": latitude (degrees)

  For GRAPHIC GENERAL OPTIONS, all the options work as in the default plots
                               except:
                                     the setting of "--xmax","--xmin","--ymax","--ymin"  only works 
                                     properly with the 'Equidistant Cylindrical Projection'.

                                     the option "--Ftitle", add a fractional title, is disabled. 
                                    
                                     the options "--xt" and "--yt" (for setting ticks) which are disabled.

                                     the option "--AdjustToMargin" will only take effect on station maps.
                                 
  For PLOT DEPENDENT OPTIONS, the options "-f", "-x", "-y", "--ms" work as in the default plots,
                              while the other options in this part are blocked in this mode.
  
  For SAVE CURRENT GRAPHIC:
                               In the case of one plot, it works the same way as for default plots
                               In the case of two plots, two save paths should be provided. If only one path is provided,
                               only the vertical map will be saved.
                               In the case of three plots, three save paths should be provided. If only one path is provided,
                               only the vertical map will be saved. If only two path are provided, only the vertical and
                               horizontal maps will be saved.

       
  --map --Map                   Make a world map plot with the given values.
 
  --wir, --WIR                  Make a worst integrity ratio plot. This is a world map, but
                                sets a fixed scale (with a minimum of 0 and a maximum of 2 independently of user input), 
                                and a fixed set of colors for the colourbar.

  --rv, --ratioV, --RV          Set the source of the vertical values or worst integrity ratio.
                                Identical properties as x,y column in the default plots.

  --rh, --ratioH, --RH          Set the source of the horizontal values or worst integrity ratio.
                                Identical properties as x,y column in the default plots.

  --miv, --MIV                  Set the source of the vertical MIs.
                                Identical properties as x,y column in the default plots.

  --mih, --MIH                  Set the source of the horizontal MIs.
                                Identical properties as x,y column in the default plots.

  --sn, --staName, --SN         Set the source for the station name. Setting this value will make a new
                                  plot with the name of the stations in their coordinates.

  --projection, --pj            Set the projection of the map. 
                                'Equidistant Cylindrical Projection' is set as [DEFAULT]
                                User can set the value of projection as 'lcc' or 'lambert' 
                                to switch to "Lambert Conformal Projection".

  --cbarMin,--cbarmin,--cmin    The minimum value for the colourbar, if no value is provided,
                                automatic limits are set.  

  --cbarMax,--cbarmax,--cmax    The maximum value for the colourbar, if no value is provided,
                                automatic limits are set. 

  --cbarInterval,--cbarN,--cn   The value of interval for colourbar's tick, if no value is provided,
                                8 is set as [DEFAULT]

  --continentColor,--cc         The continent's colour, if no value is provided, 'yellow' is 
                                set as [DEFAULT]

  --lakeColor, --lc             The lake's colour, if no value is provided, 'white' is 
                                set as [DEFAULT]

  --boundaryColor,--bc          The continent's colour, if no value is provided, 'white' is 
                                set as [DEFAULT]

  --mapres, --MapResolution     Sets the world map resolution. Valid values are 'c', 'l' [DEFAULT],
                                  'i', 'h' or 'f' (ordered from lower to higher resolution).

 NOTES on World Maps / Worst Integrity Ratio Maps: 
    If only one of the parameters '--rh' or '--rv' is given, only the horizontal or vertical plots will be shown. 
    If both parameters '--rh' or '--rv' are given, two plots will be shown.
    If any of '--mih' or '--miv' parameters are given. a coloured ring around the coloured circles will appear on the corresponding plot.
    If only '--sn' parameter is given, a single plot with the station map will be shown.
    It is recommended to save station name maps in pdf format, as station names will be searchable inside the file.
    An horizontal label will only fit if no MIs are plotted, as the second colorbar for the MIs will occupy the free space.

 Example:
       Generate one plot:      graph.py -f /home/gLAB/Example --wir -x 5 -y 7 --rh 11 
       Generate two plots:     graph.py -f /home/gLAB/Example --wir -x 5 -y 7 --rh 11 --rv 13 --mih 17 --grid off
       Generate three plots:   graph.py -f /home/gLAB/Example --wir -x 5 -y 7 --rh 11 --rv 13 --sn 3 --mih 17 --miv 19 

 Example for saving the plots: 
       graph.py -f /home/gLAB/Example --wir  -x 5 -y 7 --rv 13 --miv 19 --rh 11 --mih 17 --xmin -30 --xmax 40 --ymin 25 --ymax 75  --sv /home/Desktop/Figure_V.eps --sv /home/Desktop/Figure_H.eps --sv /home/Desktop/Figure_Station_Map.pdf

SBAS AVAILABILITY AND CONTINUITY PLOT:

  In this mode: 
  
  The input file should have this fixed format (this is gLAB's output format):
  
  The first three lines have the header with this format (numerical values can vary according to the plot):
    For SBAS Availability map:
       #MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK
         25.00  70.00  -30.00   40.00       1.00       0.00  40.00  50.00 315 2016     86400     120      5.00
       #  LAT     LON AVAIL%

    For SBAS Continuity Risk map:
       #MINLAT MAXLAT  MINLON  MAXLON RESOLUTION REC-HEIGHT    HAL    VAL DoY YEAR NUMEPOCHS GEO-PRN ELEV-MASK WINDOW_SIZE
         25.00  70.00  -30.00   40.00       1.00       0.00  40.00  50.00 315 2016     86400     120      5.00          15
       #  LAT     LON      CONT-RISK

    For SBAS Ionosphere Availability map:
       #MINLAT MAXLAT  MINLON  MAXLON RESOLUTION DoY YEAR NUMEPOCHS GEO-PRN
         65.00  73.00   30.00   40.00       0.10 255 2016       288     120
       #  LAT     LON AVAIL%
        
  Graph program will automatically detect which type of input file is given using the header, 
  and will read the map size from the header.

  Since the fourth row, each row should provide the following values: latitude, longitude, value

  For GRAPHIC GENERAL OPTIONS, only the option to set the title "--title" is enabled. If non set,
                               a title will be set automatically. The plot region will be
                               automatically set from the header values.
                               
  For PLOT DEPENDENT OPTIONS, the options "-f" works the same way as in the default plots,
                              while the other options in this part are disabled in this mode.
                              
  MULTIPLE PLOTS are disabled in this mode.
  
  For SAVE CURRENT GRAPHIC,   it works the same way as for the default plots.

  --sbas, --SBAS                      Make a SBAS map

  --nocontourlines, --NoContourLines  Do not show contour lines in Availability and Continuity Risk maps

  --nocbarpercent, --NoCbarPercent    Do not put the '%' sign in top of the colorbar

  --CbarLabel, --cbarlabel            Add a label next to the colorbar

  --SBASSystemname, --sbassystemname  Set the name of the SBAS system in the title, replacin the default
                                      "SBAS" text in the default title.

  --PRNtext, --prntext                Replace the "PRN <number>" text in the default title with the given
                                      text. This is useful when the plot is from multiple PRNs, where the
                                      default PRN is 0.

  --PRNtextnewline, --prntextnewline  Move the "PRN <number>" to a newline below (instead of being next to
                                        the alarm limits and the pixel resolution)

  NOTE: If user sets a vertical label, the '--atm' option (adjust to margin) will be disabled in order to
        fit the vertical label

 Examples: 
       graph.py -f /home/gLAB/Example --sbas --sv /home/Desktop/SBASAvailMap.eps
                                
       graph.py -f /home/gLAB/Example --SBAS
 
"""

GraphicParser = OptionParser(usage=HelpHeader) 

GraphicParser.add_option("--title","--tit","-t", type="string", dest="Title", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Ftitle","--ftitle","--ft", type="string", dest="FractionalTitle", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Xlabel","--xlab","--xl" ,type="string", dest="Xlabel", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Ylabel","--ylab","--yl" ,type="string", dest="Ylabel", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--file","-f" ,type="string", dest="filename", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Xcol","-x","-X", "--error",type="string", dest="ColX", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Ycol","-y","-Y", "--pl", type="string",dest="ColY", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--cond","-c", type="string",dest="Cond", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--label","--plotlabel","-l", type="string",dest="PlotLabel", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--style","-s", type="string",dest="Style", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP) 
GraphicParser.add_option("--grid","-g", type="string",dest="grid", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--wm","--watermark", type="string",dest="WaterMark", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--wmc","--watermarkcolor", type="string",dest="WaterMarkColor", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--wms","--watermarksize", type="string",dest="WaterMarkSize", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--wmp","--watermarkposition", type="string",dest="WaterMarkPosition", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Xticks","--xticks","--xt", type="string",dest="Xticks", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Yticks","--yticks","--yt", type="string",dest="Yticks", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--XticksStep","--xticksstep","--xts", type="string",dest="XticksStep", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--YticksStep","--yticksstep","--yts", type="string",dest="YticksStep", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--XticksList","--xtickslist","--xtl", type="string",dest="XticksList", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--YticksList","--ytickslist","--ytl", type="string",dest="YticksList", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--AdjustToMargin","--adjusttomargin","--atm",  dest="AdjustToMargin", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--no-lock-file", dest="NoLockFile", default=False,action='store_true',help=optparse.SUPPRESS_HELP)

GraphicParser.add_option("--numpointslabel","--NumPointsLabel","--npl", type="string",dest="NumPointsLabel", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--labelpos","--labelPos","--lp", type="string",dest="LabelPosition", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)

GraphicParser.add_option("--ms","--MarkerSize","--markersize",type="string",dest="MarkerSize", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP) 
GraphicParser.add_option("--lw","--LineWidth","--linewidth", type="string",dest="LineWidth", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP) 

GraphicParser.add_option("--save","--sv", type="string",dest="SaveFigure", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--color","--cl", type="string",dest="PlotColor", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Xmin","--xmin","--xn", type="string",dest="Xmin", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Xmax","--xmax","--xx", type="string",dest="Xmax", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Ymin","--ymin","--yn", type="string",dest="Ymin", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--Ymax","--ymax","--yx", type="string",dest="Ymax", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)




GraphicParser.add_option("--stanford","--sf","--sp", dest="stanford", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--clean",dest="clean", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--AL","--al",type="string",dest="AL", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--xr","--xresolution",type="string",dest="resolution_x", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--yr","--yresolution",type="string",dest="resolution_y", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--percentileX", "--percentilex", dest="sigmaX", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--percentileY", "--percentiley", dest="sigmaY", default=False,action='store_true',help=optparse.SUPPRESS_HELP)

GraphicParser.add_option("--stanfordESA","--sfesa","--spesa", dest="stanfordESA", default=False,action='store_true',help=optparse.SUPPRESS_HELP)

GraphicParser.add_option("--maxpoints",type="string",dest="maxpoints", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)

GraphicParser.add_option("--map","--Map", dest="wir", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--wir","--WIR", dest="wircolorbar", default=False,action='store_true',help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--sn","--staName","--SN", type="string",dest="ColName", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--rv","--ratioV","--RV", type="string",dest="ColRatioV", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--rh","--ratioH","--RH", type="string",dest="ColRatioH", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--miv","--MIV", type="string",dest="ColMIsV", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--mih","--MIH", type="string",dest="ColMIsH", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--projection","--pj", type="string",dest="projection", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--cbarMin","--cbarmin","--cmin", type="string",dest="cbarMin", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--cbarMax","--cbarmax","--cmax", type="string",dest="cbarMax", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--cbarInterval","--cbarN","--cn", type="string",dest="cbarInterval", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--continentColor","--cc", type="string",dest="continentColor", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--lakeColor","--lc", type="string",dest="lakeColor", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--boundaryColor","--bc", type="string",dest="boundaryColor", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--mapres","--MapRes","--MapResolution", type="string",dest="MapResolution", action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)

GraphicParser.add_option("--sbas","--SBAS", dest="sbas", default=False, action='store_true', help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--nocontourlines","--NoContourLines", dest="SBASNoContourLines", default=False, action='store_true', help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--nocbarpercent","--NoCbarPercent",dest="NoCbarPercentage",default=False, action='store_true', help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--CbarLabel","--cbarlabel",type="string",dest="ColourBarLabel",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--SBASSystemname","--sbassystemname",type="string",dest="SBASsystemname",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--PRNtext","--prntext",type="string",dest="SBASPRNtext",action="callback",callback=ParseCallback,callback_args=(Graph,),help=optparse.SUPPRESS_HELP)
GraphicParser.add_option("--PRNtextnewline","--prntextnewline", dest="SBASPRNtextNewline", default=False, action='store_true', help=optparse.SUPPRESS_HELP)


(opts,args)=GraphicParser.parse_args()

if (opts.NoLockFile==True):
    CreateLockFile=False

if (CreateLockFile==True):
    if (os.path.isfile(LockFile) != True) :
        try:
            PlotLockFile = open(LockFile, "w")   
        except:
            #In Mac, sys name is "Darwin". If fails to open in Mac, it may be de to
            #gLAB is launched without installing (gLAB mounted on a read-only filesystem)
            #Try the home folder instead
            if (sys.platform[:3].lower() != "win"):
                if (sys.version_info >= (3,4)):
                    #Python 3.4+
                    from pathlib import Path
                    LockFile=str(Path.home()) + "/.plot.lock"
                else:
                    #Python version <= 3.3
                    from os.path import expanduser
                    LockFile=expanduser("~") + "/.plot.lock"
           
                try:
                    PlotLockFile = open(LockFile, "w")
                except:
                    print ("ERROR: %s" %(sys.exc_info()[1]))
                    sys.exit()
            else:
                print ("ERROR: %s" %(sys.exc_info()[1]))
                sys.exit()

        PlotLockFile.close()

if (opts.wir):
    Graph.worstIntegrityRatio = True
if (opts.wircolorbar):
    opts.wir = True
    Graph.worstIntegrityRatio = True
    Graph.worstIntegrityRatioColorbar = True    

if(opts.stanford and opts.wir):
    print ("ERROR: stanford plots and worst integrity ratio plots cannot be both set")
    removeLockFile()
    sys.exit()

if(opts.stanford and opts.stanfordESA):
    print ("ERROR: stanford plots and stanford-ESA plots cannot be both set")
    removeLockFile()
    sys.exit()

if(opts.wir and opts.stanfordESA):
    print ("ERROR: stanford-ESA plots and worst integrity ratio plots cannot be both set")
    removeLockFile()
    sys.exit()

if(opts.sbas and opts.stanford):
    print ("ERROR: stanford plots and SBAS plots cannot be both set")
    removeLockFile()
    sys.exit()

if(opts.sbas and opts.stanfordESA):
    print ("ERROR: stanford-ESA plots and SBAS plots cannot be both set")
    removeLockFile()
    sys.exit()

if(opts.sbas and opts.wir):
    print ("ERROR: Worst integrity ratio plots and SBAS plots cannot be both set")
    removeLockFile()
    sys.exit()

if(opts.stanford and opts.stanfordESA and opts.wir):
    print ("ERROR: stanford plots, stanford-ESA plots and worst integrity ratio plots cannot be all set at once")
    removeLockFile()
    sys.exit()

if(opts.stanford and opts.stanfordESA and opts.sbas):
    print ("ERROR: stanford plots, stanford-ESA plots and SBAS plots cannot be all set at once")
    removeLockFile()
    sys.exit()

if(opts.wir and opts.stanfordESA and opts.sbas):
    print ("ERROR: stanford plots, worst integrity ratio plots and SBAS plots cannot be all set at once")
    removeLockFile()
    sys.exit()

if(opts.stanford and opts.wir and opts.sbas):
    print ("ERROR: stanford plots, worst integrity ratio plots and SBAS plots cannot be all set at once")
    removeLockFile()
    sys.exit()

if(opts.stanford and opts.stanfordESA and opts.wir and opts.sbas):
    print ("ERROR: stanford plots, stanford-ESA plots, worst integrity ratio plots or SBAS plots cannot be all set at once")
    removeLockFile()
    sys.exit()

if(opts.stanford or opts.wir or opts.stanfordESA or opts.sbas):
    if (Graph.PlotCounter>1):
        print ("ERROR: stanford plots or worst integrity ratio plots or stanford-ESA plots or SBAS plots only allow one plot per execution")
        removeLockFile()
        sys.exit()

if (opts.stanford):
    Graph.stanford = True 
    Graph.clean = False
    Graph.sigmaX = False
    Graph.sigmaY = False
if (opts.stanfordESA):
    Graph.stanfordESA = True 
   

if (opts.wir):
    Graph.worstIntegrityRatio = True
if (opts.wircolorbar):
    Graph.worstIntegrityRatio = True
    Graph.worstIntegrityRatioColorbar = True    
if (opts.sbas):
    Graph.SBASmaps = True
if (opts.clean):
    Graph.clean = True
if (opts.sigmaX):
    Graph.sigmaX = True
if (opts.sigmaY):
    Graph.sigmaY = True
if (opts.SBASNoContourLines):
    Graph.contourlines = False
if (opts.NoCbarPercentage):
    Graph.CbarPercentage = False
if (opts.SBASPRNtextNewline):
    Graph.PRNtextNewline = True

if (opts.AdjustToMargin):
    Graph.AdjustToMargin = True


if (Graph.PlotCounter==0 and opts.stanford):
    print ("ERROR: stanford plots selected, but no input files given. Use parameter '-f <file>'")
    removeLockFile()
    sys.exit()
elif (Graph.PlotCounter==0 and opts.stanfordESA):
    print ("ERROR: stanford-ESA plots selected, but no input files given. Use parameter '-f <file>'")
    removeLockFile()
    sys.exit()
elif (Graph.PlotCounter==0 and opts.wir):
    print ("ERROR: worst integrity ratio plots selected, but no input files given. Use parameter '-f <file>'")
    removeLockFile()
    sys.exit()
elif (Graph.PlotCounter==0 and opts.sbas):
    print ("ERROR: SBAS plots selected, but no input files given. Use parameter '-f <file>'")
    removeLockFile()
    sys.exit()

if (Graph.Xmin >= Graph.Xmax and Graph.XmaxAuto == False):
    print ("ERROR: X max must be greater than X min")
    removeLockFile()
    sys.exit()

if (Graph.Ymin >= Graph.Ymax and Graph.YmaxAuto == False):
    print ("ERROR: Y max must be greater than Y min")
    removeLockFile()
    sys.exit()

if (opts.wir and Graph.ColXUser == False):
    print ("ERROR: Longitude column in file for worst integrity ratio plots must be set. Use '-x <col>'")
    removeLockFile()
    sys.exit()

if (opts.wir and Graph.ColYUser == False):
    print ("ERROR: Latitude column in file for worst integrity ratio plots must be set. Use '-y <col>'")
    removeLockFile()
    sys.exit()

if (opts.wir and Graph.ColRatioH == "" and Graph.ColRatioV == "" and Graph.ColName == ""):
    print ("ERROR: Horizontal or Vertical integrity ratio column or Station Name column in file for worst integrity ratio plots must be set. Use '--rh <col>' for horizontal ratio column or '--rv <col>' for vertical ratio column or '--sn <col>' for station name column")
    removeLockFile()
    sys.exit()

if (opts.wir and Graph.ColRatioV == "" and Graph.ColMIsV != ""):
    print ("ERROR: Vertical MI column given, but no Vertical integrity ratio column given. Use '--rv <col>' to input vertical integrity ratio column")
    removeLockFile()
    sys.exit()

if (opts.wir and Graph.ColRatioH == "" and Graph.ColMIsH != ""):
    print ("ERROR: Horizontal MI column given, but no horizontal integrity ratio column given. Use '--rh <col>' to input horizontal ratio column")
    removeLockFile()
    sys.exit()


#matplot lib Agg does not use XDisplay, so if we are saving plot in a file, we will not need XDisplay in Linux
if Graph.SaveFigure:
    import matplotlib
    matplotlib.use('Agg')

#The imports are done after the parameters are read, so if no stanford or 
#worst integrity ratio plots are done, their libraries are not imported
if (Graph.worstIntegrityRatio or Graph.stanford or Graph.stanfordESA or Graph.SBASmaps):
    import numpy as np
    import matplotlib.pyplot as plt
    from matplotlib.path import Path
    from matplotlib.patches import Rectangle,PathPatch,Polygon
    from matplotlib.collections import PatchCollection
    from mpl_toolkits.axes_grid1 import make_axes_locatable
else:
    import pylab
if Graph.worstIntegrityRatio or Graph.SBASmaps:
    from mpl_toolkits.basemap import Basemap

#If we are not in Windows and we are not saving the plot in a file, check if we have a display available
if (sys.platform[:3].lower() != "win" and Graph.SaveFigure==False):
        try:
            if(Graph.worstIntegrityRatio or Graph.stanford or Graph.stanfordESA or Graph.SBASmaps):
                plt.figure()
                plt.close('all')
            else:
                pylab.xlabel("")
        except:
            print (sys.exc_info()[1])
            removeLockFile()
            sys.exit()

#This plt.close('all') is repeated due to sometimes a weird error of Tkinter appeared (can't invoke "event" command: application has been destroyed).
#Forcing again to close all plots is a workaround to the problem 
if(Graph.worstIntegrityRatio or Graph.stanford or Graph.stanfordESA or Graph.SBASmaps):
    plt.close('all')

if (sys.platform[:3].lower() == "win" or sys.platform[:3].lower() == "dar"):
        #Ignore all deprecated warnings for Windows and Darwin (Mac)
        warnings.filterwarnings("ignore");

#Make plot
MakeGraph()
