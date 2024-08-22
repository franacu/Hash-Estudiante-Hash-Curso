//
// Created by Fran on 22/08/2024.
//

#ifndef UNTITLED19_HELPER_H
#define UNTITLED19_HELPER_H
#define TAM 100
typedef struct nodo
{
    struct nodo *sig;
    char id[12];
}Nodo;
typedef struct estudiante
{
    char id[12];
    char nombre[25];
    Nodo *curso;
}Estudiante;
typedef struct tablaHashE
{
    Estudiante *estudiante[TAM];
}TablaHashE;
typedef struct curso
{
    char id[12];
    char nombre[25];
    Nodo *estudiante;
}Curso;
typedef struct tablaHashC
{
    Curso *curso[TAM];
}TablaHashC;
Nodo *newNodo(char id[12]);
Estudiante *newEstudiante(char id[12],char nombre[25]);
TablaHashE *newTablaHashE();
Curso *newCurso(char id[12],char nombre[25]);
TablaHashC *newTablaHashC();

void agregarEstudiante(TablaHashE*estudiantes,char *id,char *nombre);
void eliminarEstudiante(TablaHashE*estudiantes,TablaHashC*cursos,char *id);
void registrarCurso(TablaHashC*cursos,char *idCurso,char *idEstudiante,TablaHashE*estudiantes);
void imprimirCurso(Curso * curso,TablaHashE *estudiantes);
void imprimirCursos(TablaHashC * cursos,TablaHashE*estudiantes);
void imprimirEstudiantes(TablaHashC * cursos,TablaHashE*estudiantes);
void agregarCurso(TablaHashC*cursos,char *idCurso,char *nombre);

#endif //UNTITLED19_HELPER_H
