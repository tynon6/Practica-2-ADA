# Práctica 2 — Complejidad en ordenamiento

- **Materia:** [Analisis y Diseños de algoritmos]
- **Práctica:** [2 — Complejidad en ordenamiento]
- **Docente:** [Andres Garcia Floreano]
- **Estudiante(s):** [Iker Gael Cruz Vargas]
- **Grupo:** [3CV1]
- **Fecha de entrega:** 29/10/2026

## Objetivo

Implementar cinco algoritmos de ordenamiento en dos lenguajes, comparar sus tiempos y uso de memoria en arreglos de números reales y documentar las ejecuciones.

## Secciones por lenguaje

- [Java: código, resultados y evidencias](Java/README.md)
- [C++: código, resultados y evidencias](C++/README.md)

El código completo y su explicación están en este README para consulta rápida. Los CSV registran los resultados visibles en las capturas adjuntas: una ejecución por lenguaje con 100,000 elementos. Los datos no son promedios ni deben interpretarse como comparación controlada entre equipos.

## Algoritmos y complejidad teórica

| Algoritmo | Promedio | Peor caso | Espacio auxiliar |
|---|---:|---:|---:|
| Bubble Sort | O(n²) | O(n²) | O(1) |
| Merge Sort | O(n log n) | O(n log n) | O(n) |
| Tree Sort sin balance | O(n log n) | O(n²) | O(n) |
| Heap Sort | O(n log n) | O(n log n) | O(1) |
| Counting adaptado a reales | O(n log n) | O(n log n) | O(n) |

Counting Sort clásico requiere claves enteras en un rango acotado. Aquí se adapta a `double` ordenando las claves distintas y contando frecuencias, por lo que su complejidad incluye O(n log n). Un arreglo de mil millones de `double` ocupa aproximadamente 8 GB antes de sumar memoria auxiliar. Bubble Sort y Tree Sort degenerado pueden ser imprácticos en tamaños grandes. Los programas aceptan tamaños en la línea de comandos para permitir ejecutar pruebas graduales.

## Resultados registrados

| Lenguaje | Algoritmo | n | Tiempo (ms) | Memoria reportada (bytes) |
|---|---|---:|---:|---:|
| Java | Bubble | 100,000 | 35019.988 | 0 |
| Java | Merge | 100,000 | 40.241 | 834,520 |
| Java | Tree | 100,000 | 85.756 | 3,664,480 |
| Java | Heap | 100,000 | 24.942 | 0 |
| Java | Counting | 100,000 | 84.851 | 1,390,488 |
| C++ | Bubble | 100,000 | 64735.3 | 0 |
| C++ | Merge | 100,000 | 35.944 | 800,000 |
| C++ | Tree | 100,000 | 65.3732 | 2,400,000 |
| C++ | Heap | 100,000 | 45.6969 | 0 |
| C++ | Counting | 100,000 | 74.5786 | 1,200,000 |






