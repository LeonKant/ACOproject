#%matplotlib widget #don't worry about this 
#jupyter nbextension enable --py --sys-prefix ipympl
import matplotlib.pyplot as plt
import csv
  
x = []
y = []
  
with open('points.csv','r') as csvfile:
    lines = csv.reader(csvfile, delimiter=',')
    for row in lines:
        x.append(int(row[0]))
        y.append(int(row[1]))
  
plt.scatter(x, y, color = 'g', #linestyle = 'dashed',
         marker = 'o')
  
plt.xlabel('X-values')
plt.ylabel('Y-values')
plt.title('TSP', fontsize = 20)
plt.grid()
#plt.legend()
plt.show()