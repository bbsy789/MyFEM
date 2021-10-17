#include "graphics.h"
 
int main(){
    initgraph(640,480);
    circle(200,200,100);
    getch();
    closegraph();
    return 0;
}