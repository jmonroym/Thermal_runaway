import pandas as pd
import sys, os, re, glob
import numpy as np

from scipy.interpolate import splev, splrep
from scipy.optimize import curve_fit

import matplotlib.pyplot as plt
import matplotlib as mpl
from scipy import stats
from matplotlib import pylab
import seaborn as sns

from lmfit import Model


# dataset corresponds to Heat (Q) as a function of temperature T
# the real dependentce is Q=Q_r*Exp(b*T)
# we want  to find 'Q_r' and 'b' from a fit


dataset = pd.read_csv("datafile.csv",sep=",", index_col=None) # read info from csv file

QT=pd.DataFrame()
QT=dataset

print(QT)

# define function to be used by lmfit package
def func(x, a, b):
    print(a*np.exp(-b*x))
    return a * np.exp(-b * x)


x1 = QT.Ts_ec
y1 = QT.Q2

gmodel = Model(func)
result = gmodel.fit(y1, x=x1, a=0.02, b=1)

print(result.fit_report())

plt.plot(x1, y1, 'bo')
plt.plot(x1, result.init_fit, 'k--', label='initial fit')
plt.plot(x1, result.best_fit, 'r-', label='best fit')
plt.legend(loc='best')
plt.show()

#------------ exponential fit using curve_fit

print('                                             ')
print('_____________________________________________')

print('exponential regresion over Q = a*exp(-b*T)  \n')


xdata = QT.Ts_e
ydata = QT.Q2

popt, pcov = curve_fit(func, xdata, ydata)
popt

plt.plot(xdata, func(xdata, *popt), 'r-',
         label='fit: a=%5.3f, b=%5.3f' % tuple(popt))

## Generated linear fit
print('                                             ')
print('_____________________________________________')

print('linear regresion over log(Q) = log(a) + bT  \n')

xdatal = QT.Ts_ec
ydatal = np.log(QT.Q2)

slope_Q_1_exp, intercept_Q_1_exp, r_value_Q_1_exp, p_value_Q_1_exp, std_err_Q_1_exp = stats.linregress(xdatal,ydatal)

print("b=", slope_Q_1_exp,' a=' , np.exp(intercept_Q_1_exp))

#fdata=[]
#for t in xdata:
#    fdata.append(np.exp(intercept_Q_1_exp + slope_Q_1_exp*t))
    
#plt.plot(xdata, Q_T.Q2, 'b', label='data')
#plt.plot(xdata, fdata, 'r--',label='Fit')

#plt.xlabel('x')
#plt.ylabel('y')
#plt.legend()
#plt.show()


#QT['Q_f']=fdata
#QT
