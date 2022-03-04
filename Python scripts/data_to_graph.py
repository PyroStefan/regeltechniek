import pandas as pd
import matplotlib.pyplot as plt

# change 100% to 50% in file name for 50% data and vice versa
# At 100% fan speed at row 648 seconds: 1381, which is used for the lambda function at line 10
# At 500% fan speed at row 255 seconds: 543
var = pd.read_excel("C:\\Users\\stefa\\OneDrive - Anton de Kom Universiteit van Suriname\\ADEK\\Vakken\\Semester 4\\Regeltechniek 1\\practicum\\nieuwe_sensor_data_50_en_100_procent_fanspeed.xlsx", '100%', skiprows=648)
var.columns = ['time', 'temperature']

var['time'] = var['time'].apply(lambda x: x - 1381)

x = var['time']
y = var['temperature']

plt.plot(x, y, '-', ms=0.5)

plt.title('Cooling: Fan Speed 100%')
plt.xlabel('Time (seconds)')
plt.ylabel('Temperature (Celsius)')

plt.grid()

plt.show()
