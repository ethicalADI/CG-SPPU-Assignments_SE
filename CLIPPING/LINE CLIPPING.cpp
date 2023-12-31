/*
BY:ADITYA KUMAR  
Topic:LINE CLIPPING
*/

#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std;

float xc,yc,xr,yr;

float xmin=-150,ymin=-150,xmax=150,ymax=150;


int code(float x,float y){
    int c1=0;
    if(y>ymax){
        c1=8;
    }
    else if(y<ymin){
        c1=4;
    }
    if(x>xmax){
        c1=c1|2;
    }
    if(x<xmin){
        c1=c1|1;
    }
    return c1;
}

vector<float> v(4);
void clip(float xc,float yc,float xr,float yr){
    int c1=0;
    int c2=0;
    c1 = code(xc,yc);
    c2 = code(xr,yr);
 
    float slope = (yr-yc)/(xr-xc);
    v[0]=xc;
    v[1]=yc;
    v[2]=xr;
    v[3]=yr;

    
    if((c1|c2)==0){
        v[0]=xc;
        v[1]=yc;
        v[2]=xr;
        v[3]=yr;
        
    }
    if((c1&c2)==0){
        if(c1&8){
            v[1]=ymax;
            v[0]=xc+(ymax-yc)/slope;
        }
        if(c1&4){
            v[1]=ymin;
            v[0]=xc+(ymin-yc)/slope;
        }
        if(c1&2){
            v[0]=xmax;
            v[1]=yc+(xmax-xc)*slope;
        }
        if(c1&1){
            v[0]=xmin;
            v[1]=yc+(xmin-xc)*slope;
        }
        if(c2&8){
            v[3]=ymax;
            v[2]=xr+(ymax-yr)/slope;
        }
        if(c2&4){
            v[3]=ymin;
            v[2]=xr+(ymin-yr)/slope;
        }
        if(c2&2){
            v[2]=xmax;
            v[3]=yr+(xmax-xr)*slope;
        }
        if(c2&1){
            v[2]=xmin;
            v[3]=yr+(xmin-xr)*slope;
        }
       
    }

    if(v[0]==0 && v[1]==0 && v[2]==0 && v[3]==0){
        cout<<"COMPLETELY OUTSIDE\n";
    }
    else{
        glPointSize(2.0);
        glColor3f(1.0,0.5,0.5);
        glBegin(GL_LINES);
            glVertex2f(v[0],v[1]);
            glVertex2f(v[2],v[3]);
        glEnd();
        glFlush();
    }
}



void display(){
    glPointSize(2.0);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_STRIP);
        glVertex2d(xmin,ymin);
        glVertex2d(xmax,ymin);
        glVertex2d(xmax,ymax);
        glVertex2d(xmin,ymax);
        glVertex2d(xmin,ymin);
    glEnd();
    glFlush();
}

void init(){
    glClearColor(1.0,1.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT );
    glLoadIdentity();
    gluOrtho2D(-300,300,-300,300);
}

void mouse(int button,int state,int x,int y){
    
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            xc=x-300;
            yc=300-y;
            glBegin(GL_POINTS);
                glVertex2f(xc,yc);
            glEnd();
            glFlush();
        }
        if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
            xr=x-300;
            yr=300-y;
            glBegin(GL_POINTS);
                glVertex2f(xr,yr);
            glEnd();
            glFlush();
        }
        if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
         {
            clip(xc,yc,xr,yr);
        }
    
}

int main(int argc, char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("CLIPPING");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
}
