import numpy as np
from matplotlib import pyplot as plt

class Grain():
    def __init__(self, p):
        self.h = 0
        self.z = 0
        self.p = p
        self.threshold = 1 if (np.random.random() < self.p) else 2

    def incrementSlope(self, amount):
        self.z += amount
    def decrementSlope(self, amount):
        self.z -= amount
    def printSlope(self):
        return self.z
    def printThreshold(self):
        return self.threshold
    def slopeTest(self):
        return self.z > self.threshold
    def resetThreshold(self):
        self.threshold = 1 if (np.random.random() < self.p) else 2

class System():
    def __init__(self, L, p):
        self.L = L
        self.p = p
        self.array = [Grain(self.p) for i in range(self.L)]
    def drive(self):
        self.array[0].incrementSlope(1)
    def relax(self):
        s = 0
        relaxed = False
        while(relaxed == False):
            relaxed = True
            i = 0
            while(i < self.L):
                if (i == 0):
                    if (self.array[0].slopeTest()):
                        self.array[0].decrementSlope(2)
                        self.array[1].incrementSlope(1)
                        self.array[0].resetThreshold()
                        relaxed = False
                        s += 1
                    i += 1
                elif (i == self.L-1):
                    if (self.array[-1].slopeTest()):
                        self.array[-1].decrementSlope(1)
                        self.array[-2].incrementSlope(1)
                        self.array[-1].resetThreshold()
                        relaxed = False
                        s += 1
                        i -= 1
                    else:
                        i += 1
                else:
                    if (self.array[i].slopeTest()):
                        self.array[i].decrementSlope(2)
                        self.array[i+1].incrementSlope(1)
                        self.array[i-1].incrementSlope(1)
                        self.array[i].resetThreshold()
                        relaxed = False
                        s += 1
                        i -= 1
                    else:
                        i += 1
        return s
    def run(self, count):
        h = []
        s = []
        for i in range(int(count)):
            if (i % (count/100) == 0):
                print float(i)/count*100
            self.drive()
            s.append(self.relax())
            h.append(self.printH())
        return h,s
    def printSystem(self):
        return [i.printSlope() for i in self.array]
    def printH(self):
        return sum([i.printSlope() for i in self.array])

def main():
    L = 256
    p = 0.5
    system = System(L,p)
    h,s = system.run(1e5)
    plt.plot(s)
    plt.show()

if __name__ == '__main__':
    main()
