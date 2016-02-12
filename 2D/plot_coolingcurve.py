import matplotlib.pyplot as plt
import numpy as np

x_i = []
y_i = []
z_i = []
f = open('cloudy_coolingcurve_n0_HM05.txt', 'r')
f.readline()
lines = f.readlines()
f.close()
for line in lines:
  p = line.split()
  x_i.append(float(p[1]))
  y_i.append(float(p[2]))
  z_i.append(float(p[3]))
x = np.array(x_i)
y = np.array(y_i)
z = np.array(z_i)

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)
line1, = ax1.plot(x, y, 'bo', label="Cloudy data")
line2, = ax1.plot(x, z, 'ro', label="Cloudy data")
plt.xlabel("log(T) [K]");
plt.ylabel("log($\Lambda$ / n$_{h}$$^{2}$) [erg cm$^{-3}$ s$^{-1}$]");

x_i = []
y_i = []
z_i = []
f = open('cloudy_coolingcurve_nm3_HM05.txt', 'r')
f.readline()
lines = f.readlines()
f.close()
for line in lines:
  p = line.split()
  x_i.append(float(p[1]))
  y_i.append(float(p[2]))
  z_i.append(float(p[3]))
x = np.array(x_i)
y = np.array(y_i)
z = np.array(z_i)
line3, = ax1.plot(x, y, 'bo')
line4, = ax1.plot(x, z, 'ro')


x_i = []
y_i = []
z_i = []
f = open('cloudy_coolingcurve_n3_HM05.txt', 'r')
f.readline()
lines = f.readlines()
f.close()
for line in lines:
  p = line.split()
  x_i.append(float(p[1]))
  y_i.append(float(p[2]))
  z_i.append(float(p[3]))
x = np.array(x_i)
y = np.array(y_i)
z = np.array(z_i)
line5, = ax1.plot(x, y, 'bo')
line6, = ax1.plot(x, z, 'ro')


x_i = []
y_i = []
z_i = []
f = open('spline_coolingcurve_n0.txt', 'r')
f.readline()
lines = f.readlines()
f.close()
for line in lines:
  p = line.split()
  x_i.append(float(p[0]))
  y_i.append(float(p[1]))
  z_i.append(float(p[2]))
x = np.array(x_i)
y = np.array(y_i)
z = np.array(z_i)

line7, = ax1.plot(x, y, color="green", label="2D interpolation")
line8, = ax1.plot(x, z, color="green")


f = open('spline_coolingcurve_nm3.txt', 'r')
f.readline()
lines = f.readlines()
f.close()
x_i = []
y_i = []
z_i = []

for line in lines:
  p = line.split()
  x_i.append(float(p[0]))
  y_i.append(float(p[1]))
  z_i.append(float(p[2]))

x = np.array(x_i)
y = np.array(y_i)
z = np.array(z_i)

line9, = ax1.plot(x, y, color="green")
line10, = ax1.plot(x, z, color="green")


f = open('spline_coolingcurve_n3.txt', 'r')
f.readline()
lines = f.readlines()
f.close()
x_i = []
y_i = []
z_i = []

for line in lines:
  p = line.split()
  x_i.append(float(p[0]))
  y_i.append(float(p[1]))
  z_i.append(float(p[2]))

x = np.array(x_i)
y = np.array(y_i)
z = np.array(z_i)

line11, = ax1.plot(x, y, color="green")
line12, = ax1.plot(x, z, color="green")



plt.legend(handles=[line1, line7], loc=2)
plt.show()
fig.savefig('spline_coolingcurve.png')
