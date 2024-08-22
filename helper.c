//
// Created by Fran on 22/08/2024.
//
#include<stdlib.h>
#include "helper.h"
#include "stdio.h"
#include "string.h"
Nodo *newNodo(char id[12])
{
    Nodo *aux= malloc(sizeof(Nodo));
    if(aux==NULL)
    {
        printf("Sin memoria suficiente\n");
        exit(-1);
    }
    strcpy(aux->id,id);
    aux->sig=NULL;
    return aux;
}
Estudiante *newEstudiante(char id[12],char nombre[25])
{
    Estudiante *aux= malloc(sizeof(Estudiante));
    if(aux==NULL)
    {
        printf("Sin memoria suficiente\n");
        exit(-1);
    }
    strcpy(aux->id,id);
    strcpy(aux->nombre,nombre);
    aux->curso=NULL;
    return aux;
}
TablaHashE *newTablaHashE()
{
    TablaHashE *aux= malloc(sizeof(TablaHashE));
    if(aux==NULL)
    {
        printf("Sin memoria suficiente\n");
        exit(-1);
    }
    for(int i=0;i<TAM;i++)
    {
        aux->estudiante[i]=NULL;
    }
    return aux;
}
Curso *newCurso(char id[12],char nombre[25])
{
    Curso *aux= malloc(sizeof(Curso));
    if(aux==NULL)
    {
        printf("Sin memoria suficiente\n");
        exit(-1);
    }
    strcpy(aux->id,id);
    strcpy(aux->nombre,nombre);
    aux->estudiante=NULL;
    return aux;
}
TablaHashC *newTablaHashC()
{
    TablaHashC *aux= malloc(sizeof(TablaHashC));
    if(aux==NULL)
    {
        printf("Sin memoria suficiente\n");
        exit(-1);
    }
    for(int i=0;i<TAM;i++)
    {
        aux->curso[i]=NULL;
    }
    return aux;
}
int hash(char *id)
{
    int suma=0;

    for(int i=0;i<TAM;i++)
    {
        suma=suma+id[i];
    }
    return suma % TAM;
}
void agregarEstudiante(TablaHashE *estudiantes,char *id,char *nombre)
{
    Estudiante *estudiante= newEstudiante(id,nombre);
    int pos=hash(id);
    while(estudiantes->estudiante[pos]!=NULL)
    {
        pos=(pos+1)%TAM;
    }
    estudiantes->estudiante[pos]=estudiante;
}
void eliminarEstudiante(TablaHashE*estudiantes,TablaHashC*cursos,char *id)
{
    int pos= hash(id);
    while (estudiantes->estudiante[pos]!=NULL && strcmp(estudiantes->estudiante[pos]->id,id)!=0)
    {
        pos=(pos+1) %TAM;
    }
    Estudiante *estudiante=estudiantes->estudiante[pos];
    if(estudiantes==NULL)
    {
        printf("Estudiante no encontrado\n");
        exit(-1);
    }
    Nodo *nodoCurso=estudiante->curso;
    while (nodoCurso!=NULL)
    {
        int posC= hash(nodoCurso->id);
        Curso *curso=cursos->curso[pos];
        while (cursos->curso[pos]!=NULL && strcmp(cursos->curso[pos]->id,id)!=0)
        {
            posC=(posC+1)%TAM;
            curso=cursos->curso[pos];
        }

        if(curso!=NULL)
        {
            Nodo *nodoEstudiante=curso->estudiante;
            Nodo *ant=NULL;
            while (nodoEstudiante!=NULL && strcmp(nodoEstudiante->id,id)!=0)
            {
                ant=nodoEstudiante;
                nodoEstudiante=nodoEstudiante->sig;
            }
            if(nodoEstudiante!=NULL)
            {
                if(ant==NULL)
                {
                    curso->estudiante=nodoEstudiante->sig;
                }else
                    {
                        ant->sig=nodoEstudiante->sig;
                    }
                free(nodoEstudiante);
                break;
            }
        }
        nodoCurso=nodoCurso->sig;
    }
    free(estudiantes->estudiante[pos]);
    estudiantes->estudiante[pos]=NULL;
}
Estudiante *buscarEstudiante(TablaHashE *estudiantes,char *idEstudiante)
{
    int posE= hash(idEstudiante);
    while (estudiantes->estudiante[posE]!=NULL )
    {
        if(strcmp(estudiantes->estudiante[posE]->id,idEstudiante)==0)
        {
            return estudiantes->estudiante[posE];
        }
        posE=(posE+1) % TAM;
    }
    return NULL;
}
Curso *buscarCurso(TablaHashC *cursos,char *idCurso)
{
    int posC= hash(idCurso);
    while (cursos->curso[posC]!=NULL )
    {
        if(strcmp(cursos->curso[posC]->id,idCurso)==0)
        {
            return cursos->curso[posC];
        }
        posC=(posC+1) % TAM;
    }
    return NULL;
}
void agregarCurso(TablaHashC*cursos,char *idCurso,char *nombre)
{
    int pos= hash(idCurso);
    Curso *nuevo= newCurso(idCurso,nombre);
    while (cursos->curso[pos]!=NULL)
    {
        pos=(pos+1)%TAM;
    }
    cursos->curso[pos]=nuevo;
}
void registrarCurso(TablaHashC*cursos,char *idCurso,char *idEstudiante,TablaHashE*estudiantes)
{
    Estudiante * estudiante = buscarEstudiante(estudiantes,idEstudiante);
    Curso * curso = buscarCurso(cursos,idCurso);
    if (estudiante == NULL) {
        printf("\nEstudiante no encontrado\n");
        return;
    }
    if (curso == NULL) {
        agregarCurso(cursos, idCurso, "Curso nuevo");
        curso = buscarCurso(cursos,idCurso);
    }
    Nodo * nuevo = newNodo(idCurso);
    if (estudiante->curso == NULL) {
        estudiante->curso = nuevo;
    } else
        {
        Nodo * aux = estudiante->curso;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
    Nodo * nuevo1 = newNodo(idEstudiante);
    if (curso->estudiante == NULL) {
        curso->estudiante = nuevo1;
    } else {
        Nodo * aux = curso->estudiante;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig =nuevo1;
    }
}
void imprimirCurso(Curso * curso,TablaHashE *estudiantes){
    if (curso == NULL) {
        printf("\nCurso no encontrado\n");
        return;
    }
    printf("\nID: %s\t", curso->id);
    printf("Nombre: %s\n", curso->nombre);
    Nodo * aux = curso->estudiante;
    while (aux!= NULL)
    {
        Estudiante *act=buscarEstudiante(estudiantes, aux->id);
        if(act!=NULL)
        {
            printf("Estudiante: %s\n", act->nombre);
        }
        aux = aux->sig;
    }
    printf("\n");
}
void imprimirCursos(TablaHashC * cursos,TablaHashE*estudiantes)
{
    for (int i = 0; i < TAM; i++)
    {
        if (cursos->curso[i]!= NULL)
        {
            imprimirCurso(cursos->curso[i], estudiantes);
        }
    }
}
void imprimirEstudiante(Estudiante *estudiante,TablaHashC *cursos){
    if (estudiante == NULL) {
        printf("\nCurso no encontrado\n");
        return;
    }
    printf("\nID: %s\t", estudiante->id);
    printf("Nombre: %s\n", estudiante->nombre);
    Nodo * aux = estudiante->curso;
    while (aux != NULL) {
        Curso *curso = buscarCurso(cursos, aux->id);
        if (curso != NULL)
        {
            printf("Curso: %s\t", curso->nombre);
        }
        aux = aux->sig;
    }
    printf("\n");
}
void imprimirEstudiantes(TablaHashC * cursos,TablaHashE*estudiantes) {
    for (int i = 0; i < TAM; i++) {
        if (estudiantes->estudiante[i] != NULL)
        {
            imprimirEstudiante(estudiantes->estudiante[i],cursos);
        }
    }
}