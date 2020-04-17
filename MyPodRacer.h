#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;


/**
 * This code automatically collects game data in an infinite loop.
 * It uses the standard input to place data into the game variables such as x and y.
 * YOU DO NOT NEED TO MODIFY THE INITIALIZATION OF THE GAME VARIABLES.
 **/


int main()
{
    bool hasBoost [2] = {true,true};
    
    int laps;
    int checkpointCount;
    int nextCheckpointX; // x position of the next check point
    int nextCheckpointY; // y position of the next check point
    
    cin >> laps;
    
    cin >> checkpointCount;
    
    int checkPointX [checkpointCount] = {};
    int checkPointY [checkpointCount] = {};
    
    
    for (int i = 0; i < checkpointCount; i++) {
         cin >> nextCheckpointX >> nextCheckpointY;
         checkPointX[i] = nextCheckpointX;
         checkPointY[i] = nextCheckpointY;
    }

    // game loop
    while (1) {
        
        for (int i = 0; i < 4; i++) {
            
        int thrust = 100;
         
        int x; // x position of your pod
        int y; // y position of your pod
        
        int vx;
        int vy;
        
        int angle;
        int nextCheckPointId;
        
        
        cin >> x >> y >> vx >> vy >> angle >> nextCheckPointId;
        
        if (i > 1) {
            continue;
        }
        
        int nextCheckpointX = checkPointX[nextCheckPointId];
        int nextCheckpointY = checkPointY[nextCheckPointId];
        
        int nextCheckpointDist = sqrt(pow(nextCheckpointY-y, 2) + pow(nextCheckpointX-x, 2));
        
        int dot = (vx)*(nextCheckpointX-x) + (vy)*(nextCheckpointY-y);
        int det = (vx)*(nextCheckpointY-y) - (vy)*(nextCheckpointX-x);
        float angleMistake = atan2(det, dot);
        
        float velocity = (sqrt(pow(vy, 2)+pow(vx,2)));
        
        if (abs(angleMistake) > 0.5 && abs(angleMistake) < 1.5 && velocity > 200 && nextCheckpointDist<6000){
            float cs = cos(angleMistake);
            float sn = sin(angleMistake);
            float px = (nextCheckpointX-x) * cs - (nextCheckpointY-y) * sn; 
            float py = (nextCheckpointX-x) * sn + (nextCheckpointY-y) * cs;
            nextCheckpointX = nextCheckpointX + (int)px; 
            nextCheckpointY = nextCheckpointY + (int)py; 
            
        }
    
        else if (abs(angleMistake) < 0.5 && velocity/nextCheckpointDist > 0.3 *abs(angleMistake) && velocity > 300 && nextCheckpointDist < 2000){
    
             nextCheckpointX = (nextCheckpointX + checkPointX[(nextCheckPointId+1)%(checkpointCount-1)])/2;
             nextCheckpointY = (nextCheckpointY + checkPointY[(nextCheckPointId+1)%(checkpointCount-1)])/2;
        }
        
        int nextCheckpointAngle;
        
        float absCheckPointAngle = atan2(nextCheckpointY-y, nextCheckpointX-x) * (180.0/3.14159);
        if (absCheckPointAngle <= 0) {
            nextCheckpointAngle = (int) abs((360+absCheckPointAngle)-angle);
        }
        else {
            nextCheckpointAngle = (int) abs(absCheckPointAngle-angle);
        }
        
        if (nextCheckpointDist > 3000 && abs(nextCheckpointAngle)<5 && hasBoost[i]){
            hasBoost[i] = false;
            cout << nextCheckpointX << " " << nextCheckpointY << " " << "BOOST" << endl;
        }
        else {
        cout << nextCheckpointX << " " << nextCheckpointY << " " << thrust << endl;
        }
        
        }
        
    }
}