//
//  main.cpp
//  Proyecto
//
//  Created by Arturo Garcia on 13/03/18.
//  Copyright © 2018 Arturo Garcia. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>
#define PI 3.14159265

int ancho=256,alto=256,px=0,py=0;
int anchoB=1024,altoB=512;
int anchoArc=32,altoArc=32;
float tiempo=0;
float ang=0;
float mensaje=0;
double x=0,y=0;
double posx=0,posy=0;
double centx=0,centy=0;
double dir = 0, dif = 0;
double xant=0,yant=0;
double pend;
int turno=1;
int flecha=0;
int locked =0;
int potencia = 0;
int viento = 0;
char str[] = "     ";
char str2[]= "Presione ENTER para continuar";
int hpP1 = 100;
int hpP2 = 100;


unsigned char * datosBg;
unsigned char * datosAr;

void dibujaTexto(char * mensaje)
{
    while (*mensaje) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN,*mensaje++);
    }
}

void leerBackground(){
    FILE *imagen;
    imagen=fopen("./mapaf.data","r");
    if(imagen==NULL){printf("Error: No imagen");}
    else{printf("Imagen cargada correctamente");}
    
    datosBg=(unsigned char*)malloc(anchoB*altoB*3);
    fread(datosBg,anchoB*altoB*3,1,imagen);
    fclose(imagen);
}

void leerArco(){
    FILE *imagen2;
    imagen2=fopen("./arco3.data","r");
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
            if(ang<65)
                ang+=1;
            break;
        case GLUT_KEY_DOWN:
            if(ang>-25)
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
            glutPostRedisplay();
    }
}

void dibujarFlecha(){
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(0,0);
    glVertex2f(0,2);
    glVertex2f(1,2);
    glVertex2f(1,0);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(1,1);
    glVertex2f(1,3);
    glVertex2f(2,3);
    glVertex2f(2,1);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(0,7);
    glVertex2f(0,5);
    glVertex2f(1,5);
    glVertex2f(1,7);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(1,6);
    glVertex2f(1,4);
    glVertex2f(2,4);
    glVertex2f(2,6);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(2,2);
    glVertex2f(2,5);
    glVertex2f(19,5);
    glVertex2f(19,2);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(19,3);
    glVertex2f(19,4);
    glVertex2f(20,4);
    glVertex2f(20,3);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(17,1);
    glVertex2f(18,1);
    glVertex2f(18,6);
    glVertex2f(17,6);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(16,0);
    glVertex2f(17,0);
    glVertex2f(17,7);
    glVertex2f(16,7);
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
/*
void dibujarPersonajes(){
    glPushMatrix();
    glBegin(GL_LINE_STRIP);
    glVertex2f(58, 120);
    glVertex2f(82, 120);
    glVertex2f(82, 148);
    glVertex2f(58, 148);
    glVertex2f(58, 120);
    glEnd();
    glPopMatrix();
  
    glPushMatrix();
    glBegin(GL_LINE_STRIP);
    glVertex2f(58, 83);
    glVertex2f(82, 83);
    glVertex2f(82, 120);
    glVertex2f(58, 120);
    glVertex2f(58, 83);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glBegin(GL_LINE_STRIP);
    glVertex2f(842, 120);
    glVertex2f(868, 120);
    glVertex2f(868, 148);
    glVertex2f(842, 148);
    glVertex2f(842, 120);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glBegin(GL_LINE_STRIP);
    glVertex2f(842, 83);
    glVertex2f(868, 83);
    glVertex2f(868, 120);
    glVertex2f(842, 120);
    glVertex2f(842, 83);
    glEnd();
    glPopMatrix();
   
}
*/
int checarLimites(float x,float y){
    if ((x<566)&&(y<214)&&(x>390)&&(y>96)) {
        return 1;
    }else if((x>58)&&(x<82)&&(y>120)&&(y<148)){
        return 2;
    }else if((x>58)&&(x<82)&&(y>83)&&(y<120)){
        return 3;
    }else if((x>842)&&(x<868)&&(y>120)&&(y<148)){
        return 4;
    }else if((x>842)&&(x<868)&&(y>83)&&(y<120)){
        return 5;
    }else if(y<84){
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
    xant = 0;
    yant = 0;
    centx = 0;
    centy = 0;
    pend = 0;
    dir = 0;
    dif = 0;
    tiempo=0;
    ang=0;
    posx= 0;
    posy=0;
    flecha=0;
    potencia = 0;
    glutPostRedisplay();
}

void temp(int value){
    switch (value) {
        case 1:
        {
            locked=2;
            flecha=1;
            x = (50+potencia*10)*tiempo*cos(5*PI/36+ang*PI/180)-(viento*pow(tiempo,2))/2;
            y = (50+potencia*10)*tiempo*sin(5*PI/36+ang*PI/180)-(9.81*pow(tiempo, 2))/2;
            tiempo+=0.05;
            glutPostRedisplay();
            int res = checarLimites(posx, posy);
            if(res==0){
                glutTimerFunc(10, temp, 1);
            }else if(res==2){
                hpP1-=35;
                if(hpP1<0)
                    hpP1=0;
                locked = 1;
            }else if(res==3){
                hpP1-=20;
                if(hpP1<0)
                    hpP1=0;
                locked = 1;

            }else if(res==4){
                hpP2-=35;
                if(hpP2<0)
                    hpP2=0;
                locked = 1;

            }else if(res==5){
                hpP2-=20;
                if(hpP2<0)
                    hpP2=0;
                locked = 1;

            }else{
                locked = 1;
            }
            
            break;
        }
        case 2:
        {
            locked=2;
            flecha=1;
            x = (50+potencia*10)*tiempo*cos(31*PI/36-ang*PI/180)-(viento*pow(tiempo,2))/2;
            y = (50+potencia*10)*tiempo*sin(31*PI/36-ang*PI/180)-(9.81*pow(tiempo, 2))/2;
            tiempo+=0.05;
            glutPostRedisplay();
            int res = checarLimites(posx, posy);
            if(res==0){
                glutTimerFunc(10, temp, 2);
            }else if(res==2){
                hpP1-=35;
                if(hpP1<0)
                    hpP1=0;
                locked = 1;
            }else if(res==3){
                hpP1-=20;
                if(hpP1<0)
                    hpP1=0;
                locked = 1;
            }else if(res==4){
                hpP2-=35;
                if(hpP2<0)
                    hpP2=0;
                locked = 1;
            }else if(res==5){
                hpP2-=20;
                if(hpP2<0)
                    hpP2=0;
                locked = 1;
            }else{
                locked = 1;
            }
            break;
        }
        default:
            break;
    }
    if(locked==1)
    {
        if(hpP1<=0){
            sprintf(str2,"Victoria del jugador 2");
            locked=3;
        }
        else if(hpP2<=0){
            sprintf(str2,"Victoria del jugador 1");
            locked=3;
        }
        else{
            sprintf(str2,"Presione ENTER para continuar");
        }
        mensaje=0.15;
    }
}

void key(unsigned char c, int x, int y)
{
    if (c==27){exit(0);}
    if (c==13){
        if(locked==1){
            locked=0;
            reiniciar();
            mensaje=0;
            if(turno==1)
                turno = 2;
            else{
                turno = 1;
                generarViento();
            }
                glutPostRedisplay();
        }
        else if(locked==3){
            locked=0;
            reiniciar();
            mensaje=0;
            turno=1;
            hpP2=100;
            hpP1=100;
                glutPostRedisplay();
        }
    }
    if(locked==0){
    if (c==32){glutTimerFunc(10, temp, turno);}
            glutPostRedisplay();
    }
}

void generarHPBar(int jugador){
    switch (jugador) {
        case 1:
            glBegin(GL_QUADS);
            glColor3f(1, 0, 0);
            glVertex2f(0, 0);
            glVertex2f(10, 0);
            glColor3f(1-hpP1/100.0, hpP1/100.0, 0);
            glVertex2f(10, 1);
            glVertex2f(0, 1);
            glEnd();
            break;
        case 2:
            glBegin(GL_QUADS);
            glColor3f(1, 0, 0);
            glVertex2f(0, 0);
            glVertex2f(10, 0);
            glColor3f(1-hpP2/100.0, hpP2/100.0, 0);
            glVertex2f(10, 1);
            glVertex2f(0, 1);
            glEnd();
            
        default:
            break;
    }
    
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
    glColor3f(0, 0, 1);
    glTranslatef(36,450,0);
    glScalef(0.15, 0.15, 1);
    dibujaTexto(&str[0]);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(358,284,0);
    glScalef(mensaje, mensaje, 1);
    dibujaTexto(&str2[0]);
    glPopMatrix();
    
    //dibujarPersonajes();

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
                glRotatef(pend, 0, 0, 1);
                dibujarFlecha();
                glPopMatrix();
            }
            xant = centx;
            yant = centy;
            centx = 110 + x;
            centy = 159 + y;
            dir = centx-xant;
            if(dir<0)
                dif = 180;
            else
                dif = 0;
            pend = atan((centy-yant)/(dir))*180/PI+dif;
            posx = 20*cos(pend*PI/180)+centx;
            posy = 20*sin(pend*PI/180)+centy;
            break;
        case 2:
            glPushMatrix();
            glColor3f(1, 0, 0);
            
            glTranslatef(750, 166, 0);
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
                glRotatef(-pend, 0, 0, 1);
                dibujarFlecha();
                glPopMatrix();
            }
            xant = centx;
            yant = centy;
            centx = 814+x;
            centy = 159+y;
            dir = centx-xant;
            if(dir>0)
                dif = 180;
            else
                dif = 0;
            pend = atan((centy-yant)/(dir))*180/PI+dif;
            posx = 20*cos(pend*PI/180+PI)+centx;
            posy = 20*sin(pend*PI/180+PI )+centy;
            break;
    }
    
    glPushMatrix();
    glTranslatef(20, 90, 0);
    glScalef(1, hpP1, 0);
    generarHPBar(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(880, 90, 0);
    glScalef(1, hpP2, 0);
    generarHPBar(2);
    glPopMatrix();
    
    
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

