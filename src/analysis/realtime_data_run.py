import serial 
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import csv
import time
from datetime import datetime


# In[48]:


########## Properties applicable to both Pr and Angle graphs
numPoints = 100
y_range = [0, 100]      # Angle Range (degrees)
Angle_range = [0, 100]      # Angle Range (degrees)
x_len = numPoints  


# In[49]:


# Creating figure properties for both graphs
fig, (ax1, ax2) = plt.subplots(2, facecolor=(.18, .31, .31))  #ax is the axes
xs = list(range(0, numPoints))   #xs is a range from 0 to 99
xVec = [0] * x_len               #xVec and yVec are a set of 0s indicating vector origin location
yVec = [0] * x_len
xVec2 = [0] * x_len
yVec2 = [0] * x_len

xVec_p = [0] * x_len               #xVec and yVec are a set of 0s indicating vector origin location
yVec_p = [0] * x_len
xVec_p2 = [0] * x_len
yVec_p2 = [0] * x_len

ax1.set_ylim(y_range)
ax2.set_ylim(y_range)


# In[42]:


# get the arduino data


# In[50]:


line1, = ax1.plot(xs, xVec_p, c='b', label='thumb', linewidth=2.0)
line2, = ax1.plot(xs, yVec_p, c='r', label='index', linewidth=2.0)
line3, = ax1.plot(xs, xVec_p2, c='c', label='middle', linewidth=2.0, linestyle='dashed')
line4, = ax1.plot(xs, yVec_p2, c='m', label='ring', linewidth=2.0, linestyle='dashed')
########
line5, = ax2.plot(xs, xVec, c='b', label='thumb', linewidth=2.0)
line6, = ax2.plot(xs, yVec, c='r', label='index', linewidth=2.0)
line7, = ax2.plot(xs, xVec2, c='c', label='middle', linewidth=2.0, linestyle='dashed')
line8, = ax2.plot(xs, yVec2, c='m', label='ring', linewidth=2.0, linestyle='dashed')


# In[51]:


plt.legend(loc='upper left')
leg = ax1.legend()
leg.get_frame().set_edgecolor('b')
ax1.set_facecolor('#E56B51')
ax1.set_ylabel('Pressure (V)', color='peachpuff')
ax1.set_xlabel('Last 100 readings', color='peachpuff')
ax1.set_title('Live Servo Pressure Data', color='peachpuff')
ax1.tick_params(labelcolor='linen')
ax1.grid(which='both', axis='both', color='b',ls='--', lw=0.5)
print("Waiting for Signal...")
plt.show()

plt.legend(loc='upper left')
leg2 = ax2.legend()
leg2.get_frame().set_edgecolor('b')
ax2.set_facecolor('#eafff5')
ax2.set_ylabel('Angle (deg)', color='peachpuff')
ax2.set_xlabel('Last 100 readings', color='peachpuff')
ax2.set_title('Live Servo Rotation Data', color='peachpuff')
ax2.tick_params(labelcolor='linen')
ax2.grid(which='both', axis='both', color='b',ls='--', lw=0.5)
print("Waiting for Signal...")
plt.show()


# In[54]:


def animate(i, xVec, yVec, xVec2, yVec2, xVec_p, yVec_p, xVec_p2, yVec_p2):
    while(arduinoData.in_waiting==0): #Wait until there is data
        pass 
    arduinoString = arduinoData.readline()
    arduinoString = str(arduinoString, 'utf-8')

    dataArray = arduinoString.split(',')
    
    ## New code to split pressure and angle values
    dataArray2 = [ArrayItem.split(' -> ') for ArrayItem in dataArray]
    print(dataArray2)                # for testing
    List_values = [Array2Item for eachSet in dataArray2 for Array2Item in eachSet]
    print(List_values)                # for testing
    
    # Pressure values
    xPressComp = float(List_values[0])
    yPressComp = float(List_values[2])
    xPressKalman = float(List_values[4])
    yPressKalman = float(List_values[6])
    
    print("X Pressure = ", xPressComp, "   Y Pressure = ", yPressComp) # use for testing purposes
    
    xVec_p.append(xPressComp)
    yVec_p.append(yPressComp)
    xVec_p2.append(xPressKalman)
    yVec_p2.append(yPressKalman)

    
    ## Angle Values
    xAngleComp = float(List_values[1])
    yAngleComp = float(List_values[3])
    xAngleKalman = float(List_values[5])
    yAngleKalman = float(List_values[7])
    
    print("X Angle = ", xAngleComp, "   Y Angle = ", yAngleComp) # use for testing purposes
    
    xVec.append(xAngleComp)
    yVec.append(yAngleComp)
    xVec2.append(xAngleKalman)
    yVec2.append(yAngleKalman)
    
    xVec_p = xVec_p[-x_len:]
    yVec_p = yVec_p[-x_len:]
    xVec_p2 = xVec_p2[-x_len:]
    yVec_p2 = yVec_p2[-x_len:]
    
    xVec = xVec[-x_len:]
    yVec = yVec[-x_len:]
    xVec2 = xVec2[-x_len:]
    yVec2 = yVec2[-x_len:]
    
    line1.set_ydata(xVec_p)   # get new pressure data/update for x angle
    line2.set_ydata(yVec_p)   # get new pressure data/update for y angle
    line3.set_ydata(xVec_p2)   # get new pressure data/update for x angle
    line4.set_ydata(yVec_p2)   # get new pressure data/update for y angle
    
    line5.set_ydata(xVec)   # get new angle data/update for x angle
    line6.set_ydata(yVec)   # get new angle data/update for y angle
    line7.set_ydata(xVec2)   # get new angle data/update for x angle
    line8.set_ydata(yVec2)   # get new angle data/update for y angle
    return line1, line2, line3, line4, line5, line6, line7, line8


# In[55]:


ani = animation.FuncAnimation(fig,
    animate,
    fargs=(xVec, yVec, xVec2, yVec2, xVec_p, yVec_p, xVec_p2, yVec_p2),
    interval=50,
    blit=True)
plt.show()

