## Pong

### How to run?
First, download the library:
[https://w3.cs.jmu.edu/bernstdh/web/common/help/cpp_mingw-glut-setup.php](https://w3.cs.jmu.edu/bernstdh/web/common/help/cpp_mingw-glut-setup.php)
``` g++ -o test -Wall main.cpp -mwindows glut32.lib -lopengl32 -lglu32 ```  

### Good to know?
Basic Keys: ESC to pause the game, press ESC again to resume  
Press F1 to restart the game when you lose the game  
Move mouse to move your horizontal bar  

### Preview
![Screenshot](ScreenShots/pong.png)
![Screenshot](ScreenShots/pong2.png)
![Screenshot](ScreenShots/pong3.png)

#### External resources
I used GL/glut.h library. It needs to be downloaded to run.   
It can be downloaded [here](https://w3.cs.jmu.edu/bernstdh/web/common/help/cpp_mingw-glut-setup.php)

Reference: [https://www3.ntu.edu.sg/home/ehchua/programming/opengl/cg_introduction.html](https://www3.ntu.edu.sg/home/ehchua/programming/opengl/cg_introduction.html)