# importing the required module
from itertools import count
import random
import time
from timeit import repeat
import matplotlib.pyplot as plt
import matplotlib.animation as animation


    
with open('./points&indexes.txt') as f:
    lines = f.readlines()
    
points = [];
w=5;
h=5;
indexes = [[[0 for x in range(w)] for y in range(h)] for z in range (50)]; #create a matrix that contain 50 Journey. In each Journey, there will be a 5x5 matrix in which its row is a Path
countJourney=-1;
countPath=0;
for l in lines:
    line = l.split();
    if(len(line)>3): #if string has long length, it will be indexes. Therefore, add to indexes array
        for i in range(len(line)):
            line[i]=int(line[i]);
        indexes[countJourney][countPath]=line;
        countPath+=1;
    elif (len(line)==2): # else if the string has short length and not empty (not ""), it will be the points. Add to points array.
        points.append((line[0], line[1])); #points will be an array and contain the points in tuple. For example: [(10, 10), (1, 3), (1, 2), (5, 2)]
    elif (len(line)==0 and countJourney<=50):
        countJourney+=1;
        countPath=0;

#GRAPH
colors = ['green', 'red', 'blue', 'cyan', 'yellow', 'black', 'magenta'];
def get_Data(indexNumber, pathNumber):
    graphX=[];
    graphY=[];
    for path in indexes[indexNumber]:
        pathX=[];
        pathY=[];
        print("Index Order:", end=" ");
        print(path);
        for j in range(pathNumber+1):
            pathX.append(int(points[path.index(j)][0]));
            pathY.append(int(points[path.index(j)][1]));
        print("--- X: ", end="");
        print(pathX)
        print("--- Y: ", end="");
        print(pathY)
        graphX.append(pathX);
        graphY.append(pathY);
    print("\n");
    return (graphX, graphY);


print("GRAPH")

countJourney=0;
countPath=0;
fig = plt.figure("Ant Colony Optimization (ACO)", figsize=(10,7))
plt.xlim([0, 10])
plt.ylim([0, 10])
#creating a subplot 
ax1 = plt.subplot2grid(shape=(2,6), loc=(0,0), colspan=2)
ax2 = plt.subplot2grid((2,6), (0,2), colspan=2)
ax3 = plt.subplot2grid((2,6), (0,4), colspan=2)
ax4 = plt.subplot2grid((2,6), (1,1), colspan=2)
ax5 = plt.subplot2grid((2,6), (1,3), colspan=2)
ax1.title.set_text('Path 1');
ax2.title.set_text('Path 2');
ax3.title.set_text('Path 3');
ax4.title.set_text('Path 4');
ax5.title.set_text('Path 5');

def animate(i):
    ax1.clear();
    ax2.clear();
    ax3.clear();
    ax4.clear();
    ax5.clear();
    ax1.title.set_text('Path 1');
    ax2.title.set_text('Path 2');
    ax3.title.set_text('Path 3');
    ax4.title.set_text('Path 4');
    ax5.title.set_text('Path 5');
    global countPath;
    global countJourney;
    if (countPath == 4):
        countPath = 0;
        countJourney +=1;
    print("Journey:", end=" ");
    print(countJourney); 
    print("Points:", end=" ");
    print(points); 
    print("Path: 0-", end="")  
    print(countPath);
    
    (graphX, graphY)=get_Data(countJourney, countPath);
    ax1.plot(graphX[0], graphY[0], label = "line 1", color= "blue", linestyle='dashed', linewidth = 2,
            marker='o', markerfacecolor='red', markersize=12) 
    ax2.plot(graphX[1], graphY[1], label = "line 2", color= "black", linestyle='dashed', linewidth = 2,
            marker='o', markerfacecolor='red', markersize=12) 
    ax3.plot(graphX[2], graphY[2], label = "line 3", color= "magenta", linestyle='dashed', linewidth = 2,
            marker='o', markerfacecolor='red', markersize=12) 
    ax4.plot(graphX[3], graphY[3], label = "line 4", color= "yellow", linestyle='dashed', linewidth = 2,
            marker='o', markerfacecolor='red', markersize=12) 
    ax5.plot(graphX[4], graphY[4], label = "line 5", color= "green", linestyle='dashed', linewidth = 2,
            marker='o', markerfacecolor='red', markersize=12) 
    countPath+=1;
    

anim = animation.FuncAnimation(fig, animate, interval=2000)    
# giving a title to my graph
plt.show(); # function to show the plot

