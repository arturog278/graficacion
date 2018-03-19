//
//  main.cpp
//  Proyecto
//
//  Created by Arturo Garcia on 13/03/18.
//  Copyright © 2018 Arturo Garcia. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include <GLUT/GLUT.h>
#include <math.h>
#include <time.h>
#define PI 3.14159265

int ancho=256,alto=256,px=0,py=0;
int anchoB=1024,altoB=512;
int anchoArc=32,altoArc=32;
float tiempo=0;
float ang=0;
double x=0,y=0;
double posx=0,posy=0;
int turno=2;
int flecha=0;
int locked =0;
int potencia = 0;
int viento = 0;
char str[] = "";

unsigned char * datosBg;
unsigned char * datosPer;
unsigned char * datosAr;
unsigned char * datosIs;
unsigned char * datosFl;
unsigned char * datosTi;

void dibujaTexto(char * mensaje)
{
    while (*mensaje) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN,*mensaje++);
    }
}

void leerBackground(){
    FILE *imagen;
    imagen=fopen("/Users/arturo/Pictures/Proyecto/mapaf.data","r");
    if(imagen==NULL){printf("Error: No imagen");}
    else{printf("Imagen cargada correctamente");}

    datosBg=(unsigned char*)malloc(anchoB*altoB*3);
    fread(datosBg,anchoB*altoB*3,1,imagen);
    fclose(imagen);
}

void leerArco(){
    FILE *imagen2;
    imagen2=fopen("/Users/arturo/Pictures/Proyecto/arco3.data","r");
    if(imagen2==NULL){printf("Error: No imagen");}
    else{printf("Imagen cargada correctamente");}

    datosAr=(unsigned char*)malloc(anchoArc*altoArc*3);
    fread(datosAr,anchoArc*altoArc*3,1,imagen2);
    fclose(imagen2);
}

void usarBackground(){

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anchoB, altoB, 0, GL_RGB, GL_UNSIGNED_BYTE, datosBg);
}

void usarArco(){

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anchoArc, altoArc, 0, GL_RGB, GL_UNSIGNED_BYTE, datosAr);
}

void spkey(int key,int x, int y){
    if(locked==0){
    switch(key){
        case GLUT_KEY_UP:
            ang+=1;
            break;
        case GLUT_KEY_DOWN:
            ang-=1;
            break;
        case GLUT_KEY_RIGHT:
            if(potencia<10)
            potencia++;
            break;
        case GLUT_KEY_LEFT:
            if(potencia>0)
            potencia--;
            break;
    }
    }
    glutPostRedisplay();
}

void dibujarFlecha(){
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(0,2);
    glVertex2f(0,9);
    glVertex2f(1,9);
    glVertex2f(1,2);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(1,3);
    glVertex2f(1,8);
    glVertex2f(2,8);
    glVertex2f(2,3);
    glEnd();



    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(2,2);
    glVertex2f(19,2);
    glVertex2f(19,5);
    glVertex2f(2,5);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(19,4);
    glVertex2f(20,4);
    glVertex2f(20,5);
    glVertex2f(19,5);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(18,3);
    glVertex2f(19,3);
    glVertex2f(19,6);
    glVertex2f(18,6);
    glEnd();


}

void generarViento(){
    viento = rand() % 11;
    int dir = rand() % 2+1;
    if(viento!=0){
        if(dir==1){
            sprintf(str, "%d -->",viento);
            viento=viento*-1;
        }else{
            sprintf(str, "%d <--",viento);
        }
    }else{
        sprintf(str, "%d --",viento);
    }
}

int checarLimites(float x,float y){
    if ((x<566)&&(y<214)&&(x>390)&&(y>96)) {
        return 1;
    }else if(y<96){
        return 1;
    }else if(x<0){
        return 1;
    }else if(x>1024){
        return 1;
    }
    return 0;
}

void reiniciar(){
    x=0;
    y=0;
    tiempo=0;
    ang=0;
    posx= 0;
    posy=0;
    flecha=0;
    generarViento();
    glutPostRedisplay();
}

void temp(int value){
    switch (value) {
        case 1:
            locked=1;
            flecha=1;
            x = (50+potencia*10)*tiempo*cos(7*PI/36+ang/36)-(viento*pow(tiempo,2))/2;
            y = (50+potencia*10)*tiempo*sin(7*PI/36+ang/36)-(9.81*pow(tiempo, 2))/2;
            printf("(%f,%f)\n",x,y);
            tiempo+=0.05;
            glutPostRedisplay();
            if(checarLimites(posx, posy)!=1){
                glutTimerFunc(10, temp, 1);
            }else{
                locked =0;
            }
            break;
        case 2:
            locked=1;
            flecha=1;
            x = (50+potencia*10)*tiempo*cos(25*PI/36-ang/36)-(viento*pow(tiempo,2))/2;
            y = (50+potencia*10)*tiempo*sin(25*PI/36-ang/36)-(9.81*pow(tiempo, 2))/2;
            printf("(%f,%f)\n",x,y);
            tiempo+=0.05;
            glutPostRedisplay();
            if(checarLimites(posx, posy)!=1){
                glutTimerFunc(10, temp, 2);
            }else{
                locked =0;
            }
            break;
        default:
            break;
    }
}

void key(unsigned char c, int x, int y)
{
    if (c==27){exit(0);}
    if(locked==0){
    if (c=='f'){glutTimerFunc(10, temp, turno);}
    if (c=='r'){reiniciar();}
    }
    glutPostRedisplay();
}


void display(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 1, 1);
    glPushMatrix();
    usarBackground();
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);glVertex2f(1024, 0);
    glTexCoord2f(0.0, 1.0);glVertex2f(0, 0 );
    glTexCoord2f(0.0, 0.0);glVertex2f(0, 512);
    glTexCoord2f(1.0, 0.0);glVertex2f(1024, 512);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0,1);
    glTranslatef(36,450,0);
    glScalef(0.15, 0.15, 1);
    dibujaTexto(&str[0]);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0,1,0);
    glTranslatef(40,90,0);
    glScalef(vida1/2,1,0);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(10,0);
    glColor3f(1,0,0);
    glVertex2f(10,1);
    glVertex2f(10,1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0,1,0);
    glTranslatef(873,90,0);
    glScalef(vida2/2,1,0);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(10,0);
    glColor3f(0,1,0);
    glVertex2f(10,1);
    glVertex2f(10,1);
    glPopMatrix();

    switch(turno){
        case 1:
            glPushMatrix();
            glColor3f(1, 0, 0);

            glTranslatef(36, 166, 0);
            glScalef(potencia*10, 1, 0);
            glBegin(GL_QUADS);
            glVertex2f(0, 0);
            glVertex2f(1, 0);
            glVertex2f(1, 10);
            glVertex2f(0, 10);
            glEnd();
            glPopMatrix();

            glColor3f(1, 1, 1);
            glPushMatrix();
            usarArco();
            glTranslatef(78, 124, 0);
            glRotatef(ang, 0, 0, 1);
            glBegin(GL_QUADS);
            glTexCoord2f(1.0, 1.0);glVertex2f(32, 0);
            glTexCoord2f(0.0, 1.0);glVertex2f(0, 0 );
            glTexCoord2f(0.0, 0.0);glVertex2f(0, 32);
            glTexCoord2f(1.0, 0.0);glVertex2f(32, 32);
            glEnd();
            glPopMatrix();
            if(flecha==1){
                glPushMatrix();
                glTranslatef(110, 156, 0);
                glTranslatef(x, y, 0);
                dibujarFlecha();
                glPopMatrix();
            }
            posx = 110+x;
            posy = 156+y;
            break;
        case 2:
            glPushMatrix();
            glColor3f(1, 0, 0);

            glTranslatef(832, 166, 0);
            glScalef(potencia*10, 1, 0);
            glBegin(GL_QUADS);
            glVertex2f(0, 0);
            glVertex2f(1, 0);
            glVertex2f(1, 10);
            glVertex2f(0, 10);
            glEnd();
            glPopMatrix();

            glColor3f(1, 1, 1);
            glPushMatrix();
            usarArco();
            glTranslatef(846, 124, 0);
            glRotatef(-ang, 0, 0, 1);
            glScalef(-1, 1, 0);
            glBegin(GL_QUADS);
            glTexCoord2f(1.0, 1.0);glVertex2f(32, 0);
            glTexCoord2f(0.0, 1.0);glVertex2f(0, 0 );
            glTexCoord2f(0.0, 0.0);glVertex2f(0, 32);
            glTexCoord2f(1.0, 0.0);glVertex2f(32, 32);
            glEnd();
            glPopMatrix();

            if(flecha==1){
                glPushMatrix();
                glTranslatef(814, 156, 0);
                glTranslatef(x, y, 0);
                glScalef(-1, 1, 0);
                dibujarFlecha();
                glPopMatrix();
            }
            posx = 814+x;
            posy = 156+y;
            break;
    }



    glFlush();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitWindowSize(1024,512);
    glutInitWindowPosition(10,10);
    glutCreateWindow ("Proyecto");
    leerBackground();
    leerArco();
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0,0.0,0.0,0);
    gluOrtho2D(0,1024,0,512);
    srand (time(NULL));
    generarViento();
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(spkey);
    glutMainLoop();

    return 0;
}
