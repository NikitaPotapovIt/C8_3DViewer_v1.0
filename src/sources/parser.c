#include "../headers/parser.h"

// Открывает и читает файл .obj. Возвращает код ошибки 0, если имя файла
// правильно, иначе - 1.
// path Путь к файлу .obj, тип указателя const char
// obj Struct, тип указателя obj_t
// return OK/FILENAME_ERROR, тип int

int open_file(const char *path, obj_t *obj) {
  int error_code = OK;
  char file[LENGTH] = {0};
  snprintf(file, sizeof(file), "%s", path);
  FILE *fp = fopen(file, "rt");
  if (fp) {
    error_code = parse_obj(fp, obj);
    fclose(fp);
  } else {
    error_code = FILENAME_ERROR;
  }
  return error_code;
}

// Разбирает значения из файла .obj в структуру. Возвращает ошибку
// код 0, если значения в файле правильные, иначе - 2.
// тип указателя fp FILE
// obj Struct, тип указателя obj_t
// возвращаем OK/OBJ_VALUES_ERROR, тип int

int parse_obj(FILE *fp, obj_t *obj) {
  int error_code = OK;
  char line[LENGTH] = {0};
  while (fgets(line, LENGTH, fp) && error_code == OK) {
    if (*line == 'v' && *(line + 1) == ' ') {
      obj->vertex_count++;
    } else if (*line == 'f' && *(line + 1) == ' ') {
      obj->edge_count++;
    }
  }
  obj->vertices = (double *)realloc(obj->vertices,
                                    sizeof(double *) * obj->vertex_count * 3);
  obj->edges = (int *)realloc(obj->edges, sizeof(int *) * obj->edge_count * 6);
  if (obj->vertices && obj->edges) {
    fseek(fp, 0, SEEK_SET);
    int v_count = obj->vertex_count;
    int e_count = obj->edge_count;
    while (fgets(line, LENGTH, fp) && error_code == OK) {
      if (*line == 'v' && *(line + 1) == ' ') {
        error_code = parse_vertex(line, obj, v_count);
        v_count--;
      } else if (*line == 'f' && *(line + 1) == ' ') {
        error_code = parse_edge(line, obj, e_count);
        e_count--;
      }
    }
  }
  *line = '\0';
  return error_code;
}

// Разбирает значения вершины в структуру. Возвращает ошибку
// код 0, если значения вершины правильные, иначе - 2.
// ptr Указатель на строку в obj.file, тип указателя char
// obj Struct, тип указателя obj_t
// v_count Сдвиг индекса в массиве вершин, тип int
// возвращаем OK/OBJ_VALUES_ERROR, тип int

int parse_vertex(char *ptr, obj_t *obj, int v_count) {
  int error_code = OK;
  ptr += 2;
  obj->vertices[(obj->vertex_count - v_count) * 3] = strtod(ptr, &ptr);
  if ((*ptr) != ' ') error_code = OBJ_VALUES_ERROR;
  obj->vertices[(obj->vertex_count - v_count) * 3 + 1] = strtod(ptr, &ptr);
  if ((*ptr) != ' ') error_code = OBJ_VALUES_ERROR;
  obj->vertices[(obj->vertex_count - v_count) * 3 + 2] = strtod(ptr, &ptr);
  return error_code;
}

// Разбирает значения ребер в структуру. Возвращает ошибку
// код 0, если значения ребер правильные, иначе - 2.
// ptr Указатель на строку в obj.file, тип указателя char
// obj Struct, тип указателя obj_t
// e_count Сдвиг индекса в массиве ребер, тип int
// возвращаем OK/OBJ_VALUES_ERROR, тип int

int parse_edge(char *ptr, obj_t *obj, int e_count) {
  int error_code = OK;
  if (strchr(ptr, ' ') == NULL) error_code = OBJ_VALUES_ERROR;
  ptr = strchr(ptr, ' ');
  int first_index = (int)strtol(ptr, &ptr, 10) - 1;
  obj->edges[(obj->edge_count - e_count) * 6] = first_index;
  if (strchr(ptr, ' ') == NULL) error_code = OBJ_VALUES_ERROR;
  ptr = strchr(ptr, ' ');
  int second_index = (int)strtol(ptr, &ptr, 10) - 1;
  obj->edges[(obj->edge_count - e_count) * 6 + 1] = second_index;
  obj->edges[(obj->edge_count - e_count) * 6 + 2] = second_index;
  if (strchr(ptr, ' ') == NULL) error_code = OBJ_VALUES_ERROR;
  ptr = strchr(ptr, ' ');
  int third_index = (int)strtol(ptr, &ptr, 10) - 1;
  obj->edges[(obj->edge_count - e_count) * 6 + 3] = third_index;
  obj->edges[(obj->edge_count - e_count) * 6 + 4] = third_index;
  obj->edges[(obj->edge_count - e_count) * 6 + 5] = first_index;
  return error_code;
}

// Создает структуру obj_t.
// obj Struct, тип указателя obj_t
// vertex_count Количество вершин, тип int
// edge_count Количество ребер, тип int

void init_obj(obj_t *obj, int vertex_count, int edge_count) {
  obj->vertices = (double *)calloc(vertex_count, sizeof(double *));
  obj->edges = (int *)calloc(edge_count, sizeof(int *));
  obj->vertex_count = 0;
  obj->edge_count = 0;
}

// Удаляет структуру obj_t.
// obj Struct, тип указателя obj_t

void clean_obj(obj_t *obj) {
  if (obj) {
    if (obj->vertices) {
      free(obj->vertices);
    }
    if (obj->edges) {
      free(obj->edges);
    }
    obj = NULL;
  }
}
