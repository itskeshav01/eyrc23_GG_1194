//ESP32 Module programming

#define LEFT_SENSOR 19
#define CENTER_SENSOR 18
#define RIGHT_SENSOR 21
#define SIDE_LEFT 22
#define SIDE_RIGHT 5

#define LEFT_MOTOR_IN1 16
#define LEFT_MOTOR_IN2 4
#define RIGHT_MOTOR_IN3 15
#define RIGHT_MOTOR_IN4 2

enum Detected {
  centerOfLine,
  leftOfLine,
  rightOfLine,
  node,
  bothSideLine,
  sideRightLine,
  sideLeftLine,
  allThreeLine
};

// enum Motion {
//   forward,
//   left,
//   right,
//   stop  // You can add more directions as needed
// };

// int completePath [12]={}

// // Assuming myArray is a three-dimensional array
// Motion myArray[12][12][12];

// // Function to get the value from myArray based on three indexes
// Motion getMyArrayValue(int prevNode, int currentNode, int nextNode) {
//     return myArray[index1][index2][index3];
// }


// Function to determine detected position based on sensor readings
Detected determinePosition(bool sideLeftSensor, bool leftSensor, bool centerSensor, bool rightSensor, bool sideRightSensor) {
  Detected detected;

  if (!sideLeftSensor && !leftSensor && centerSensor && !rightSensor && !sideRightSensor) {
    // Node (center detected)
    detected = centerOfLine;

  } else if (!leftSensor && rightSensor) {
    // Right of the line
    detected = rightOfLine;

  } else if (leftSensor && !rightSensor) {
    // Left of the line
    detected = leftOfLine;

  } else if (!sideLeftSensor && leftSensor && centerSensor && rightSensor && !sideRightSensor) {
    // Left of the line
    detected = node;

  } else if (sideLeftSensor && !leftSensor && !centerSensor && !rightSensor && sideRightSensor) {
    // Both sides of the line
    detected = bothSideLine;

  } else if (!sideLeftSensor && !leftSensor && !rightSensor && sideRightSensor) {
    // Right side of the line
    detected = sideRightLine;

  } else if (sideLeftSensor && !leftSensor && !rightSensor && !sideRightSensor) {
    // Left side of the line
    detected = sideLeftLine;

  } else if (!sideLeftSensor && !leftSensor && !centerSensor && !rightSensor && !sideRightSensor) {
    // Right side of the line
    detected = allThreeLine;

  } else {
    // Default Case
     detected = detected;
  }

  return detected;
}




void setup() {
  Serial.begin(9600);

  pinMode(LEFT_SENSOR, INPUT);
  pinMode(CENTER_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);

  pinMode(LEFT_MOTOR_IN1, OUTPUT);
  pinMode(LEFT_MOTOR_IN2, OUTPUT);
  pinMode(RIGHT_MOTOR_IN3, OUTPUT);
  pinMode(RIGHT_MOTOR_IN4, OUTPUT);

  //Setting direction for bot

  
// myArray[0][1][2]='f';

// myArray[2][1][0]='f';

// myArray[1][2][3]='f';

// myArray[3][2][1]='f';

// myArray[2][3][4]='f';

// myArray[4][3][2]='f';

// myArray[0][1][8]='r';

// myArray[8][1][0]='l';

// myArray[1][2][7]='r';

// myArray[7][2][1]='l';

// myArray[2][3][6]='r';

// myArray[6][3][2]='l';

// myArray[3][4][5]='r';

// myArray[5][4][3]='l';

// myArray[4][5][6]='r';

// myArray[6][5][4]='l';

// myArray[9][5][6]='l';

// myArray[6][5][9]='r';

// myArray[3][6][7]='r';

// myArray[7][6][3]='l';

// myArray[5][6][7]='f';

// myArray[7][6][5]='f';

// myArray[3][6][5]='l';

// myArray[5][6][3]='r';

// myArray[10][6][7]='l';

// myArray[10][6][5]='r';

// myArray[7][6][10]='r';

// myArray[5][6][10]='l';

// myArray[3][6][10]='f';

// myArray[10][6][3]='f';

// myArray[3][4][9]='f';

// myArray[9][4][3]='f';

// myArray[2][7][8]='r'; myArray[11][7][8]='l'; myArray[2][7][11]='f'; myArray[6][7][8]='f'; myArray[11][7][6]='r'; myArray[2][7][6]='l';

// myArray[8][7][2]='l'; myArray[8][7][11]='r'; myArray[11][7][2]='f'; myArray[8][7][6]='f'; myArray[6][7][11]='l'; myArray[6][7][2]='r';

// myArray[1][8][7]='left'; myArray[7][8][1]='r'; myArray[11][8][7]='r'; myArray[7][8][11]='l'; myArray[1][8][11]='f'; myArray[11][8][1]='f'; 

// myArray[4][9][10]='f'; myArray[10][9][4]='f'; myArray[5][9][4]='l'; myArray[4][9][5]='r'; myArray[5][9][10]='r'; myArray[10][9][5]='l';

// myArray[9][10][11]='f'; myArray[9][10][6]='r'; myArray[6][10][11]='r'; myArray[11][10][9]='f'; myArray[6][10][9]='l'; myArray[11][10][6]='l';

// myArray[9][10][11]='f'; myArray[9][10][6]='r'; myArray[6][10][11]='r'; myArray[11][10][9]='f'; myArray[6][10][9]='l'; myArray[11][10][6]='l';

// myArray[7][11][8]='r'; myArray[8][11][7]='l'; myArray[10][11][8]='f'; myArray[8][11][10]='f'; myArray[10][11][7]='r'; myArray[7][11][10]='l';

// myArray[1][2][7]='r'; myArray[7][2][1]='l';

// myArray[6][3][4]='r'; myArray[4][3][6]='l';

}

void loop() {
  bool leftSensor = digitalRead(LEFT_SENSOR);
  bool centerSensor = digitalRead(CENTER_SENSOR);
  bool rightSensor = digitalRead(RIGHT_SENSOR);
  bool sideLeftSensor = digitalRead(SIDE_LEFT);
  bool sideRightSensor = digitalRead(SIDE_RIGHT);

  Detected detected = determinePosition(sideLeftSensor, leftSensor, centerSensor, rightSensor, sideRightSensor);
  Serial.println(detected);

  switch (detected) {
    case centerOfLine:
      // Perform forward motion action
      digitalWrite(LEFT_MOTOR_IN1, HIGH);
      digitalWrite(LEFT_MOTOR_IN2, LOW);
      digitalWrite(RIGHT_MOTOR_IN3, HIGH);
      digitalWrite(RIGHT_MOTOR_IN4, LOW);
      break;
    
    case bothSideLine:
      // Perform forward motion action
      digitalWrite(LEFT_MOTOR_IN1, HIGH);
      digitalWrite(LEFT_MOTOR_IN2, LOW);
      digitalWrite(RIGHT_MOTOR_IN3, HIGH);
      digitalWrite(RIGHT_MOTOR_IN4, LOW);
      break;
    
    case allThreeLine:
      // Perform forward motion action
      digitalWrite(LEFT_MOTOR_IN1, HIGH);
      digitalWrite(LEFT_MOTOR_IN2, LOW);
      digitalWrite(RIGHT_MOTOR_IN3, HIGH);
      digitalWrite(RIGHT_MOTOR_IN4, LOW);
      break;

    case leftOfLine:
      // Perform right motion action
      digitalWrite(LEFT_MOTOR_IN1, LOW);
      digitalWrite(LEFT_MOTOR_IN2, LOW);
      digitalWrite(RIGHT_MOTOR_IN3, HIGH);
      digitalWrite(RIGHT_MOTOR_IN4, LOW);
      break;

    case sideLeftLine:
      // Perform right motion action
      digitalWrite(LEFT_MOTOR_IN1, HIGH);
      digitalWrite(LEFT_MOTOR_IN2, LOW);
      digitalWrite(RIGHT_MOTOR_IN3, LOW);
      digitalWrite(RIGHT_MOTOR_IN4, LOW);
      break;

    case rightOfLine:
      // Perform right motion action
      digitalWrite(LEFT_MOTOR_IN1, HIGH);
      digitalWrite(LEFT_MOTOR_IN2, LOW);
      digitalWrite(RIGHT_MOTOR_IN3, LOW);
      digitalWrite(RIGHT_MOTOR_IN4, LOW);
      break;
    
    case sideRightLine:
      // Perform right motion action
      digitalWrite(LEFT_MOTOR_IN1, LOW);
      digitalWrite(LEFT_MOTOR_IN2, LOW);
      digitalWrite(RIGHT_MOTOR_IN3, HIGH);
      digitalWrite(RIGHT_MOTOR_IN4, LOW);
      break;

    case node:
      // Perform stop motion action
      digitalWrite(LEFT_MOTOR_IN1, LOW);
      digitalWrite(LEFT_MOTOR_IN2, LOW);
      digitalWrite(RIGHT_MOTOR_IN3, LOW);
      digitalWrite(RIGHT_MOTOR_IN4, LOW);
      break;
    // Add cases for other detected positions if needed
  }
}
