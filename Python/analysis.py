
import numpy as np
import matplotlib.pyplot as plt
import os
import csv
import sys
from log_bin_CN_2016 import log_bin

class Height:
    def __init__(self):
        f = [file for file in os.listdir("./data/") if file.endswith("height.dat")]
        f.sort()
        self.filename = f[-1]
        print 'Loading data...'
        self.data = np.loadtxt("./data/"+self.filename)
        self.averaged = False
        self.collapsed = False
    def average(self,w):
        self.w = w
        print 'Generating moving average...'
        l = len(self.data[0])
        self.data_average = np.zeros(len(self.data)*l/w).reshape(len(self.data),l/w)
        for i in range(len(self.data)):
            print "%0.0f%%"%(float(i)/(float(len(self.data)))*100)
            for j in xrange(w,l-w-1,w):
                self.data_average[i][j/w] = np.sum(self.data[i][j-w:j+w+1])/(2*w+1) #+1 to include fencepost
        self.averaged = True
        np.savetxt('./data/'+self.filename[:-4]+'_averaged.dat',np.transpose(self.data_average))
        print 'Averaged data generated.'
    def plot(self,data):
        if (data == 'raw'):
            y = self.data
        elif (data == 'average'):
            if (self.averaged == False):
                self.average(25)
            y = self.data_average
        elif (data == 'collapse'):
            if (self.collapsed == False):
                self.datacollapse(-0.52,1.95)
            y = self.data_collapsed
            print 'Plotting...'
            for i in range(len(y)):
                L = pow(2,i+3)
                x = self.w*np.arange(1,len(y[0])+1,1)/pow(L,self.D)
                plt.plot(x,y[i], label='L = %d'%L)
            plt.xscale('log')
            plt.yscale('log')
            plt.ylabel(r'$t^{-\tau_t}F\left(t/L^D\right)$')
            plt.xlabel(r"$t/L^D$")
            plt.legend(loc=0)
            plt.show()
            return None
        elif (data == 'mean'):
            y = self.mean
            print 'Plotting...'
            x = np.array([pow(2,i+3) for i in range(len(y))])
            plt.plot(x,y)
            plt.xscale('log')
            plt.yscale('log')
            plt.show()

        print 'Plotting...'
        for i in range(len(y)):
            plt.plot(y[i], label='L = %d'%(pow(2,i+3)))
        plt.xscale('log')
        plt.yscale('log')
        plt.legend(loc=0)
        plt.show()
    def datacollapse(self, tau, D):
        self.D = D
        self.tau = tau
        if (self.averaged == False):
                self.average(25)
        print 'Scaling...'
        l = len(self.data_average[0])
        self.data_collapsed = np.zeros(len(self.data_average)*l).reshape(len(self.data_average),l)
        for i in range(len(self.data_average)):
            print "%0.0f%%"%(float(i)/(float(len(self.data)))*100)
            for j in xrange(l):
                if (self.data_average[i][j] != 0):
                    self.data_collapsed[i][j] = pow(j,tau)*self.data_average[i][j]
    def averageheight(self):
        print 'Calculating mean...'
        mean = []
        if (self.collapsed == False):
            D = 1.95
        else:
            D = self.D
        l = len(self.data[0])
        offset = 100
        for i in range(len(self.data)):
            tc = int(pow(pow(2,i+3),D) + offset)
            #print np.mean(self.data[i][tc:]),np.std(self.data[i][tc:])
            mean.append(np.mean(self.data[i][tc:]))
        self.mean = np.array(mean)
    def bindata(self):
        if (self.collapsed == False):
            D = 1.95
        else:
            D = self.D
        offset = 0
        for i in range(len(self.data)):
            tc = int(pow(pow(2,i+3),D) + offset)
            bins = np.arange(min(self.data[i][tc:]),max(self.data[i][tc:])+1,1)
            dat = np.histogram(self.data[i],bins)
            dat = dat[0]/float(len(self.data[i][tc:]))
            for j in range(len(bins)-1):
                dat[j] = pow(bins[j],0.25)*dat[j]
            plt.plot(bins[1:]/pow(self.mean[i],1),dat)
        #plt.ylim([1,1.01])
        plt.xscale('log')
        plt.yscale('log')
        plt.show()

class Avalanche:
    D = 1.95
    def __init__(self):
        f = [file for file in os.listdir("./data/") if file.endswith("avalanche.dat")]
        f.sort()
        self.filename = f[-1]
        print 'Loading data...'
        self.data = np.loadtxt("./data/"+self.filename)
        self.averaged = False
        self.collapsed = False
    def probability(self):
        offset = 0
        for i in range(len(self.data)):
            tc = int(pow(pow(2,i+3),self.D) + offset)
            bins = np.arange(0,max(self.data[i][tc:])+1,1)
            dat = np.histogram(self.data[i],bins)
            dat = dat[0]/float(len(self.data[i][tc:]))
            for j in range(len(bins)-1):
               dat[j] = pow(bins[j],1.55)*dat[j]
            plt.plot(bins[1:]/pow(pow(2,i+3),1.95),dat)
        #plt.ylim([1,1.01])
        plt.xscale('log')
        plt.yscale('log')
        plt.show()
    def logBin(self):
        print 'Binning data...'
        offset = 0
        for i in range(len(self.data)):
            tc = int(pow(pow(2,i+3),self.D) + offset)
            bins, dat = log_bin(self.data[i],a=1.75)
            for j in range(len(bins)):
              dat[j] = pow(bins[j],1.55)*dat[j]
            plt.plot(np.array(bins)/pow(pow(2,i+3),2.2),dat)
        print 'Plotting...'
        plt.xscale('log')
        plt.yscale('log')
        plt.show()

def main():
    '''h = Height()
    #h.average(10)
    #h.datacollapse(-0.51,1.95)
    h.averageheight()
    h.bindata()
    #h.plot('collapse')'''
    a = Avalanche()
    a.logBin()

if (__name__=='__main__'):
    main()
