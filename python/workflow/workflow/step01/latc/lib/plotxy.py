#!/usr/bin/env python
# author:   zhanghongda
# date:     Jan 17, 2020
# version:  2.0
# function: draw x-y chart by csv dat file

##########################
## data file format (csv):
##########################
# head_x, head_y1, head_y2, head_y3
# 12, 33, 34, 55
# 17, 13, 24, 57

import csv
from datetime import datetime
import matplotlib.pyplot as plt
import numpy as np
import os
import sys


class DrawGraph(object):
    def __init__(self, dat_file, skip_rows=0, show_cnt=-1):
        """at least one argument is needed
        1. filename required
        2. first row is header, not contains in skip_rows
        3. default show to end"""
        # internal variable
        self.dat_file = dat_file
        self.skip_rows = 1 + skip_rows
        self.show_cnt = show_cnt
        self.plt = False

        # default options
        self.expected_hz = 10.0
        self.statinfo_on = False
        self.parse_x_t = True
        self.set_labels()

        # init procedures
        self._read_data()

    def _read_data(self):
        """read data, limit range
        cols as data; csv format
        first line as the header line"""
        with open(self.dat_file) as f:
            reader = csv.reader(f)
            self.header = next(reader)
        # read the data lines
        self.dat = np.loadtxt(self.dat_file, unpack=True, delimiter=',', skiprows=self.skip_rows)
        # show only points, if given by args
        if self.show_cnt != -1:
            for col in self.dat:
                col = col[:self.show_cnt]
    
    def _set_plt_data(self):
        """pour data to pyplot"""
        cols = self.dat
        plt.figure(num=None, figsize=(13, 5), dpi=96, facecolor='w', edgecolor='w')
        # cols[0] as X, other cols as Ys
        for i in range(1, len(cols)):
            plt.plot(cols[0], cols[i], '.-', label=self.header[i])
            if self.statinfo_on:
                # output statistics information
                print("[%s]\nmin: %f, average: %f, max: %f, median: %f, 99-percentile: %f" % (
                        self.header[i].strip(),
                        np.min(cols[i]),
                        np.average(cols[i]),
                        np.max(cols[i]),
                        np.median(cols[i]),
                        np.percentile(cols[i], 99)))
        
        t = cols[0]
        if self.statinfo_on:
            print("total frames: %d, duration: %.3fs, drop rate: %.2f%%" \
                % (t.size, t[-1]-t[0], 100.0-100.0*t.size/((t[-1]-t[0])*self.expected_hz)))
        
        # textures and styles
        plt.title("%s (total:%d)" % (self.title_prefix, len(cols[0])))
        plt.xlabel(self.xlabel)
        plt.ylabel(self.ylabel)
        plt.minorticks_on()
        plt.grid(True)
        plt.legend()
        # plt.ticklabel_format(style='sci', axis='x', scilimits=(20,30))
        plt.ticklabel_format(style='plain', useOffset=False)
        if self.parse_x_t:
            plt.gca().format_coord = self._custom_coord
        self.plt = plt

    def _custom_coord(self, x, y):
        if x > 1500000000:
            str_time = datetime.fromtimestamp(x).strftime('%Y-%m-%d %H:%M:%S')
            return "x={:f} (".format(x) + str_time + "), y={:f}".format(y)
        else:
            hh = int(x / 3600)
            mm = int((x - hh * 3600) / 60)
            ss = x - hh * 3600 - mm * 60
            hms = str(hh) + ":" + str(mm) + ":" + str(ss)
            return "x={:f} ({:02}:{:02}:{:06.3F}), y={:f}".format(x, hh, mm, ss, y)

    def set_x_start_zero(self, start_zero=True):
        """ajust cols data: let X begin from 0"""
        if start_zero:
            cols = self.dat
            cols[0][:] = [ x - cols[0][0] for x in cols[0]]
        
    def ajust_y(self, col_idx, add_val):
        """ajust data: add value to certain col values"""
        if col_idx < len(self.dat) and col_idx > 0:
            self.dat[col_idx][:] = [ x + add_val for x in self.dat[col_idx]]
        else:
            print("warning: ajust y data, invlid col_index: %d" % col_idx)
    
    def set_droprate_hz(self, hz): 
        self.expected_hz = hz

    def set_labels(self, x="x", y="y", title="X-Y chart"): 
        self.xlabel = x
        self.ylabel = y
        self.title_prefix = title

    def enable_parse_x_time(self, toggle=True):
        self.parse_x_t = toggle

    def enable_statinfo(self, toggle=True):
        self.statinfo_on = toggle

    def savefig(self, f_img):
        """must be called before show"""
        if not self.plt:
            self._set_plt_data()
        self.plt.savefig(f_img)

    def show(self):
        """open an window and draw"""
        if not self.plt:
            self._set_plt_data()
        self.plt.show()


def main():
    # parse data info from arguments
    if len(sys.argv) == 1:
        cmd = "pltxy"
        print("error: csv-format filename needed as the first argument!")
        print("usage: %s data.csv [skip_num] [show_num]" % cmd)
        print("e.g.:  %s a.csv" % cmd)
        print("       %s a.csv 3    # line [4, end]" % cmd)
        print("       %s a.csv 3 20 # line [4, 23]" % cmd)
        exit()
    # data filename
    fdat = sys.argv[1]
    skiprows = 0
    showcnt = -1
    pngfile = ""
    # skiped points
    if len(sys.argv) >= 3:
        skiprows = int(sys.argv[2])
    # used points count
    if len(sys.argv) >= 4:
        showcnt = int(sys.argv[3])

    # used png file
    if len(sys.argv) >= 5:
        pngfile = sys.argv[4]

    # setup draw options ans show
    graph = DrawGraph(fdat, skiprows, showcnt)
    # graph.set_x_start_zero()
    # graph.ajust_y(2, 200)
    # graph.enable_statinfo()
    # graph.set_droprate_hz(10)
    graph.enable_parse_x_time()
    graph.set_labels("time(s)", "lantency(ms)", "end2end lantency")
    if pngfile: 
#        graph.savefig("latc.png")
        graph.savefig(pngfile)
    else:
        graph.show()


if __name__ == '__main__':
    main()
