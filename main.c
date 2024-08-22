#include <stdio.h>
#include "helper.h"

// Aquí incluirías las funciones previamente definidas.

int main() {
    // Crear tablas hash de estudiantes y cursos
    TablaHashE *tablaEstudiantes = newTablaHashE();
    TablaHashC *tablaCursos = newTablaHashC();

    // Agregar algunos estudiantes
    agregarEstudiante(tablaEstudiantes, "123", "Juan Perez");
    agregarEstudiante(tablaEstudiantes, "456", "Maria Garcia");
    agregarEstudiante(tablaEstudiantes, "789", "Luis Rodriguez");

    printf("Mostramos Estudiantes:\n");
    imprimirEstudiantes(tablaCursos, tablaEstudiantes);

    printf("Mostramos Cursos Nuevos:\n");
    agregarCurso(tablaCursos,"CUR101","Matematica");
    agregarCurso(tablaCursos,"CUR102","Fisica");
    imprimirCursos(tablaCursos, tablaEstudiantes);

    registrarCurso(tablaCursos, "CUR101", "123", tablaEstudiantes);
    registrarCurso(tablaCursos, "CUR102", "123", tablaEstudiantes);
    registrarCurso(tablaCursos, "CUR101", "456", tablaEstudiantes);
    registrarCurso(tablaCursos, "CUR102", "789", tablaEstudiantes);

    printf("Mostramos Cursos:\n");
    imprimirCursos(tablaCursos, tablaEstudiantes);


    // Eliminar un estudiante y sus referencias en los cursos
    eliminarEstudiante(tablaEstudiantes, tablaCursos, "123");

    // Imprimir todos los estudiantes y los cursos nuevamente, después de la eliminación
    printf("\nDespués de eliminar a Juan Perez:\n");
    imprimirEstudiantes(tablaCursos, tablaEstudiantes);


    return 0;
}
