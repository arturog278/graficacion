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

int ancho=256,alto=256,px=0,py=0;
float ang=0;
double x1=0,y1=0;

unsigned char * datosBg;
unsigned char * datosPer;
unsigned char * datosAr;
unsigned char * datosIs;
unsigned char * datosFl;
unsigned char * datosTi;

void leerBackground(){
    FILE *imagen;
    imagen=fopen("/Users/arturo/Pictures/Proyecto/paisaje.data","r");
    if(imagen==NULL){printf("Error: No imagen");}
    else{printf("Imagen cargada correctamente");}
    
    datosBg=(unsigned char*)malloc(ancho*alto*3);
    fread(datosBg,ancho*alto*3,1,imagen);
    fclose(imagen);
}

void leerPersonaje(){
    FILE *imagen2;
    imagen2=fopen("/Users/arturo/Pictures/geometric2.data","r");
    if(imagen2==NULL){printf("Error: No imagen");}
    else{printf("Imagen cargada correctamente");}
    
    datosPer=(unsigned char*)malloc(ancho*alto*3);
    fread(datosPer,ancho*alto*3,1,imagen2);
    fclose(imagen2);
}

void leerArco(){
    FILE *imagen2;
    imagen2=fopen("/Users/arturo/Pictures/geometric2.data","r");
    if(imagen2==NULL){printf("Error: No imagen");}
    else{printf("Imagen cargada correctamente");}
    
    datosAr=(unsigned char*)malloc(ancho*alto*3);
    fread(datosAr,ancho*alto*3,1,imagen2);
    fclose(imagen2);
}

void leerIsla(){
    FILE *imagen2;
    imagen2=fopen("/Users/arturo/Pictures/Proyecto/isla.data","r");
    if(imagen2==NULL){printf("Error: No imagen");}
    else{printf("Imagen cargada correctamente");}
    
    datosIs=(unsigned char*)malloc(ancho*alto*3);
    fread(datosIs,ancho*alto*3,1,imagen2);
    fclose(imagen2);
}

void leerFlecha(){
    FILE *imagen2;
    imagen2=fopen("/Users/arturo/Pictures/geometric2.data","r");
    if(imagen2==NULL){printf("Error: No imagen");}
    else{printf("Imagen cargada correctamente");}
    
    datosFl=(unsigned char*)malloc(ancho*alto*3);
    fread(datosFl,ancho*alto*3,1,imagen2);
    fclose(imagen2);
}

void leerTierra(){
    FILE *imagen2;
    imagen2=fopen("/Users/arturo/Pictures/geometric2.data","r");
    if(imagen2==NULL){printf("Error: No imagen");}
    else{printf("Imagen cargada correctamente");}
    
    datosTi=(unsigned char*)malloc(ancho*alto*3);
    fread(datosTi,ancho*alto*3,1,imagen2);
    fclose(imagen2);
}

void usarBackground(){
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datosBg);
}

void usarPersonaje(){
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datosPer);
}

void usarArco(){
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datosAr);
}

void usarIsla(){
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datosIs);
}

void usarFlecha(){
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datosFl);
}

void usarTierra(){
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datosTi);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    usarBackground();
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);glVertex2f(0, 0);
    glTexCoord2f(0.0, 1.0);glVertex2f(600, 0 );
    glTexCoord2f(0.0, 0.0);glVertex2f(600, 600);
    glTexCoord2f(1.0, 0.0);glVertex2f(0, 600);
    glEnd();
    glPopMatrix();
    
    glFlush();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(10,10);
    glutCreateWindow ("Textura SintÈtica");
    leerBackground();
    leerIsla();
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0,0.0,0.0,0);
    gluOrtho2D(0,600,0,600);
    
    
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}

