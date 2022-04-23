# importing the required module
from cgi import print_form
from itertools import count
import matplotlib.pyplot as plt
import matplotlib.animation as animation

    
with open('./points&indexes50p-25a-5000j.txt') as f:
    lines = f.readlines()
    
points = [];
indexes = []; #create a matrix that contain 50 Journey. In each Journey, there will be a 5x5 matrix in which its row is a Path
countJourney=-1;
countPath=0;
maxNumberPath=0;
max=0;
for l in lines:
    line = l.split();
    if(len(line)>3): #if string has long length, it will be indexes. Therefore, add to indexes array
        indexes[countJourney].append([]);
        numberOfWay=0;
        for i in range(len(line)):
            line[i]=int(line[i]);
            numberOfWay+=1;
        indexes[countJourney][countPath]=line;
        countPath+=1;
    elif (len(line)==2): # else if the string has short length and not empty (not ""), it will be the points. Add to points array.
        points.append((line[0], line[1])); #points will be an array and contain the points in tuple. For example: [(10, 10), (1, 3), (1, 2), (5, 2)]
        if(int(line[0])>max):
            max=int(line[0]);
        if(int(line[1])>max):
            max=int(line[1]);    
    elif (len(line)==0):
        indexes.append([]);        
        countJourney+=1;
        maxNumberPath=countPath;
        countPath=0;
        

#GRAPH
# colors = ['green', 'red', 'blue', 'cyan', 'yellow', 'black', 'magenta'];
def get_Data(indexNumber, pathNumber, wayNumber, maxWay):
    path = indexes[indexNumber][pathNumber];
    pathX=[];
    pathY=[];
    print("Index Order:", end=" ");
    print(path);
    for j in range(wayNumber+1):
        pathX.append(int(points[path.index(j)][0]));
        pathY.append(int(points[path.index(j)][1]));
        if(j==(maxWay-2)):
            pathX.append(int(points[path.index(0)][0]));
            pathY.append(int(points[path.index(0)][1]));
    print("--- X: ", end="");
    print(pathX)
    print("--- Y: ", end="");
    print(pathY, end="\n\n")
    return (pathX, pathY);

print("GRAPH")

countJourney=0;
countPath=0;
countWay=0;
fig = plt.figure("Ant Colony Optimization (ACO)", figsize=(10,7))
plt.xlim([0, max])
plt.ylim([0, max])
#creating a subplot 
ax1 = plt.subplot(1,2,1)
ax2 = plt.subplot(1,2,2)
ax1.title.set_text('Full Journey');
ax2.title.set_text('One by One Path');
ax1.set_xlim([0, max])
ax1.set_ylim([0, max])
ax2.set_xlim([0, max])
ax2.set_ylim([0, max])

graphX=[];
graphY=[];
graphXFull=[];
graphYFull=[];


def animate(i):
    global countPath;
    global countJourney;
    global countWay;
    global graphX;
    global graphY;
    global graphXFull;
    global graphYFull;
    ax1.clear();
    ax2.clear();
    ax1.title.set_text('Journey '+str(countJourney) + ', Path 0-' + str(countPath));
    ax2.title.set_text('Path '+str(countPath)+', Way 0-'+str(countWay));
    ax1.set_xlim([0, max])
    ax1.set_ylim([0, max])
    ax2.set_xlim([0, max])
    ax2.set_ylim([0, max])
    if (countPath == (maxNumberPath-1)):
        countPath = 0;
        countWay = 0;
        countJourney +=1;
        graphXFull=[];
        graphYFull=[];
    elif (countWay == len(points)):
        countPath+=1;
        countWay=0;
    print("Journey:", end=" ");
    print(countJourney); 
    print("Path: ", end="")  
    print(countPath);
    print("Way: 0-", end="")  
    print(countWay);
    print("Points:", end=" ");
    print(points); 
    
    for i in range (countWay):
        graphXFull.pop();
        graphYFull.pop();
    (graphX, graphY)=get_Data(countJourney, countPath, countWay, numberOfWay);
    (graphXFull, graphYFull)=(graphXFull+graphX, graphYFull+graphY);
    ax1.plot(graphXFull, graphYFull, label = "line 1", color= "blue", linestyle='dashed', linewidth = 1,
            marker='o', markerfacecolor='red', markersize=4.5) 
    ax2.plot(graphX, graphY, label = "line 2", color= "black", linestyle='dashed', linewidth = 1,
            marker='o', markerfacecolor='red', markersize=4.5) 
    countWay+=1;
    print("-------------------------------------------------------")
    

anim = animation.FuncAnimation(fig, animate, interval=0.1)    
# giving a title to my graph
plt.show(); # function to show the plot

# def get_FullPathData(indexNumber, pathNumber):
#     path = indexes[indexNumber][pathNumber];
#     pathX=[];
#     pathY=[];
#     print("Index Order:", end=" ");
#     print(path);
#     for j in range(len(points)):
#         pathX.append(int(points[path.index(j)][0]));
#         pathY.append(int(points[path.index(j)][1]));
#         if(j==(len(points)-1)):
#             pathX.append(int(points[path.index(0)][0]));
#             pathY.append(int(points[path.index(0)][1]));
#     print("--- X: ", end="");
#     print(pathX)
#     print("--- Y: ", end="");
#     print(pathY, end="\n\n");
#     return (pathX, pathY);
    

# def get_FullJourneyData(indexNumber):
#     pathX=[];
#     pathY=[];
#     print("Full Graph:")
#     for path in indexes[indexNumber]:
#         for j in range(len(points)):
#             pathX.append(int(points[path.index(j)][0]));
#             pathY.append(int(points[path.index(j)][1]));
#             if(j==(len(points)-1)):
#                 pathX.append(int(points[path.index(0)][0]));
#                 pathY.append(int(points[path.index(0)][1]));
#         return (pathX, pathY);
        
#     print("--- X: ", end="");
#     print(pathX)
#     print("--- Y: ", end="");
#     print(pathY, end="\n\n")