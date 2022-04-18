# importing the required module
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
def get_Data(indexNumber, pathNumber, wayNumber):
    path = indexes[indexNumber][pathNumber];
    pathX=[];
    pathY=[];
    print("Index Order:", end=" ");
    print(path);
    for j in range(wayNumber+1):
        pathX.append(int(points[path.index(j)][0]));
        pathY.append(int(points[path.index(j)][1]));
        if(j==3):
            pathX.append(int(points[path.index(0)][0]));
            pathY.append(int(points[path.index(0)][1]));
    print("--- X: ", end="");
    print(pathX)
    print("--- Y: ", end="");
    print(pathY, end="\n\n")
    return (pathX, pathY);

def get_FullPathData(indexNumber, pathNumber):
    path = indexes[indexNumber][pathNumber];
    pathX=[];
    pathY=[];
    print("Index Order:", end=" ");
    print(path);
    for j in range(len(points)):
        pathX.append(int(points[path.index(j)][0]));
        pathY.append(int(points[path.index(j)][1]));
        if(j==(len(points)-1)):
            pathX.append(int(points[path.index(0)][0]));
            pathY.append(int(points[path.index(0)][1]));
    print("--- X: ", end="");
    print(pathX)
    print("--- Y: ", end="");
    print(pathY, end="\n\n");
    return (pathX, pathY);
    

def get_FullJourneyData(indexNumber):
    pathX=[];
    pathY=[];
    print("Full Graph:")
    for path in indexes[indexNumber]:
        for j in range(len(points)):
            pathX.append(int(points[path.index(j)][0]));
            pathY.append(int(points[path.index(j)][1]));
            if(j==(len(points)-1)):
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
plt.xlim([0, 10])
plt.ylim([0, 10])
#creating a subplot 
ax1 = plt.subplot(2,2,1)
ax2 = plt.subplot(2,2,2)
ax3 = plt.subplot(2,2,3)
ax1.title.set_text('Full Journey');
ax2.title.set_text('Full Path');
ax3.title.set_text('One by One Path');
ax1.set_xlim([0, 10])
ax1.set_ylim([0, 10])
ax2.set_xlim([0, 10])
ax2.set_ylim([0, 10])
ax3.set_xlim([0, 10])
ax3.set_ylim([0, 10])
    
def animate(i):
    global countPath;
    global countJourney;
    global countWay;
    ax1.clear();
    ax2.clear();
    ax3.clear();
    ax1.title.set_text('Full Journey '+str(countJourney));
    ax2.title.set_text('Full Path '+str(countPath));
    ax3.title.set_text('One by One Path');
    ax1.set_xlim([0, 10])
    ax1.set_ylim([0, 10])
    ax2.set_xlim([0, 10])
    ax2.set_ylim([0, 10])
    ax3.set_xlim([0, 10])
    ax3.set_ylim([0, 10])
    if (countPath == len(points) and countWay == len(points)):
        countPath = 0;
        countWay = 0;
        countJourney +=1;
    elif (countWay == len(points)):
        countPath+=1;
        countWay=0;
    print("Journey:", end=" ");
    print(countJourney); 
    print("Points:", end=" ");
    print(points); 
    (graphXFull, graphYFull)=get_FullJourneyData(countJourney);
    print("Path: ", end="")  
    print(countPath);
    (graphXPath, graphYPath)=get_FullPathData(countJourney, countPath);
    
    print("Way: 0-", end="")  
    print(countWay);
    (graphX, graphY)=get_Data(countJourney, countPath, countWay);
    
    ax1.plot(graphXFull, graphYFull, label = "line 1", color= "blue", linestyle='dashed', linewidth = 2,
            marker='o', markerfacecolor='red', markersize=12) 
    ax2.plot(graphXPath, graphYPath, label = "line 2", color= "black", linestyle='dashed', linewidth = 2,
            marker='o', markerfacecolor='red', markersize=12) 
    ax3.plot(graphX, graphY, label = "line 3", color= "green", linestyle='dashed', linewidth = 2,
            marker='o', markerfacecolor='red', markersize=12) 
    countWay+=1;
    print("----------------------------------------------")
    

anim = animation.FuncAnimation(fig, animate, interval=500)    
# giving a title to my graph
plt.show(); # function to show the plot

