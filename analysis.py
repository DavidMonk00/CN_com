
import numpy as np
import matplotlib.pyplot as plt
import os
import csv
import sys

class Height:
    def __init__(self):
        f = [file for file in os.listdir("./data/") if file.endswith("height.dat")]
        f.sort()
        filename = f[-1]
        print 'Loading data...'
        self.data = np.loadtxt("./data/"+filename)
        self.averaged = False
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
        print 'Averaged data generated.'
    def plot(self,data):
        if (data == 'raw'):
            y = self.data
        elif (data == 'average'):
            if (self.averaged == False):
                self.average(25)
            y = self.data_average
        print 'Plotting...'
        for i in range(len(y)):
            plt.plot(y[i], label='L = %d'%(pow(2,i+3)))
        plt.xscale('log')
        plt.yscale('log')
        plt.legend(loc=0)
        plt.show()
    def datacollapse(self, t, D):
        if (self.averaged == False):
                self.average(25)
        print 'Scaling...'
        l = len(self.data_average[0])
        y = np.zeros(len(self.data_average)*l).reshape(len(self.data_average),l)
        for i in range(len(self.data_average)):
            print "%0.0f%%"%(float(i)/(float(len(self.data)))*100)
            for j in xrange(l):
                if (self.data_average[i][j] != 0):
                    y[i][j] = pow(j,t)*self.data_average[i][j]
        for i in range(len(y)):
            L = pow(2,i+3)
            x = self.w*np.arange(1,l+1,1)/pow(L,D)
            plt.plot(x,y[i], label='L = %d'%L)
        plt.xscale('log')
        plt.yscale('log')
        plt.ylabel('t^a F(t/(L^D)) - a=%0.2f, D=%0.2f'%(t,D))
        plt.xlabel('t/(L^D)')
        plt.legend(loc=0)
        plt.show()




def main():
    h = Height()
    h.average(25)
    h.datacollapse(-0.52,1.95)
    #h.plot('average')

if (__name__=='__main__'):
    main()
