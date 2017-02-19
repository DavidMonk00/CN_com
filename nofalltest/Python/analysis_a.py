
import numpy as np
import matplotlib.pyplot as plt
import os
import csv
import sys
from log_bin_CN_2016 import log_bin

class Avalanche:
    D = 2.2
    def __init__(self):
        f = [file for file in os.listdir("./data/") if file.endswith("avalanche.dat")]
        f.sort()
        self.filename = f[-1]
        print 'Loading data...'
        self.data = np.loadtxt('./data/'+self.filename)#np.array([[int(i) for i in line.strip().split(' ') if i] for line in open("./data/" + self.filename)])
        self.tc = 907302#np.loadtxt("temp",dtype=int)
        self.averaged = False
        self.collapsed = False
    def probability(self):
        bins = np.arange(0,max(self.data[self.tc[i]:])+1,1)
        dat = np.histogram(self.data[self.tc[i]:],bins)
        dat = dat[0]/float(len(self.data[self.tc[i]:]))
        #plt.scatter(bins[1:],dat,lw=0,color='green')#/pow(pow(2,i+3),1.95),dat)
        #plt.ylim([1,1.01])
        plt.xscale('log')
        plt.yscale('log')
        #plt.show()
    def logBin(self):
        print 'Binning data...'
        bins, dat = log_bin(self.data[self.tc:],a=1.25)
        #for j in range(len(bins)):
            #dat[j] = pow(bins[j],1.55)*dat[j]
        plt.plot(np.array(bins),dat,label='All avalanches')
        print 'Plotting...'
        #plt.legend(loc=0)
        #plt.ylabel(r'$P_{10^{7}} \left( s; L \right)$',fontsize=18)
        #plt.xlabel(r'$s$',fontsize=18)
        #plt.xscale('log')
        #plt.yscale('log')
        #plt.show()
    def moment(self):
        means = []
        offset = 100
        for i in range(1,7):
            mean = []
            for j in range(len(self.data)):
                mean.append(np.mean(np.power(self.data[j][self.tc[i]:],i, dtype='float128')))
            x = np.array([pow(2,j+3) for j in range(len(self.data))])
            plt.plot(x,np.array(mean), marker='o', label='k = %d'%i)
            means.append(mean)
        means = np.transpose(np.array(means))
        np.savetxt('./data/'+self.filename[:-4]+'_averaged.dat',means)
        plt.xscale('log')
        plt.yscale('log')
        plt.legend(loc=0)
        plt.xlabel(r'$L$', fontsize=18)
        plt.ylabel(r'$\langle s^{k} \rangle$', fontsize=18)
        plt.show()


class Avalanche_a:
    D = 2.2
    def __init__(self):
        f = [file for file in os.listdir("./data/") if file.endswith("avalanche_no_fall.dat")]
        f.sort()
        self.filename = f[-1]
        print 'Loading data...'
        self.data = np.loadtxt('./data/'+self.filename)#np.array([[int(i) for i in line.strip().split(' ') if i] for line in open("./data/" + self.filename)])
        self.tc = 907302#np.loadtxt("temp",dtype=int)
        self.averaged = False
        self.collapsed = False
    def probability(self):
        bins = np.arange(0,max(self.data[self.tc[i]:])+1,1)
        dat = np.histogram(self.data[self.tc[i]:],bins)
        dat = dat[0]/float(len(self.data[self.tc[i]:]))
        #plt.scatter(bins[1:],dat,lw=0,color='green')#/pow(pow(2,i+3),1.95),dat)
        #plt.ylim([1,1.01])
        plt.xscale('log')
        plt.yscale('log')
        #plt.show()
    def logBin(self):
        print 'Binning data...'
        bins, dat = log_bin(self.data[self.tc:],a=1.25)
        #for j in range(len(bins)):
            #dat[j] = pow(bins[j],1.55)*dat[j]
        plt.plot(np.array(bins),dat,label='No fall from system')
        print 'Plotting...'
        plt.legend(loc=0)
        plt.ylabel(r'$P_{10^{7}} \left( s; 1024\right)$',fontsize=18)
        plt.xlabel(r'$s$',fontsize=18)
        plt.xscale('log')
        plt.yscale('log')
        plt.show()
    def moment(self):
        means = []
        offset = 100
        for i in range(1,7):
            mean = []
            for j in range(len(self.data)):
                mean.append(np.mean(np.power(self.data[j][self.tc[i]:],i, dtype='float128')))
            x = np.array([pow(2,j+3) for j in range(len(self.data))])
            plt.plot(x,np.array(mean), marker='o', label='k = %d'%i)
            means.append(mean)
        means = np.transpose(np.array(means))
        np.savetxt('./data/'+self.filename[:-4]+'_averaged.dat',means)
        plt.xscale('log')
        plt.yscale('log')
        plt.legend(loc=0)
        plt.xlabel(r'$L$', fontsize=18)
        plt.ylabel(r'$\langle s^{k} \rangle$', fontsize=18)
        plt.show()

def main():
    a = Avalanche()
    a.logBin()
    a_a = Avalanche_a()
    #a.probability()
    a_a.logBin()
    #a.moment()

if (__name__=='__main__'):
    main()
