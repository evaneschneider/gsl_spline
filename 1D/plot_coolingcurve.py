import matplotlib.pyplot as plt
import numpy as np

f = open('coolingcurve_HM05_n0.txt', 'r')
f.readline()
lines1 = f.readlines()
f.close()

f = open('spline_coolingcurve.txt', 'r')
f.readline()
lines2 = f.readlines()
f.close()

x1_i = []
y1_i = []
x2_i = []
y2_i = []

for line in lines1:
  p = line.split()
  x1_i.append(float(p[0]))
  y1_i.append(float(p[1]))

for line in lines2:
  p = line.split()
  x2_i.append(float(p[0]))
  y2_i.append(float(p[1]))

x1 = np.array(x1_i)
y1 = np.array(y1_i)
x2 = np.array(x2_i)
y2 = np.array(y2_i)

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)
line1, = ax1.plot(x1, y1, 'ro', label="Cloudy data")
line2, = ax1.plot(x2, y2, color="blue", label="cubic spline")
plt.xlabel("log(T) [K]");
plt.ylabel("log($\Lambda$ / n$_{h}$$^{2}$) [erg cm$^{-3}$ s$^{-1}$]");
plt.legend(handles=[line1, line2], loc=2)
plt.savefig('spline_coolingcurve.png')
