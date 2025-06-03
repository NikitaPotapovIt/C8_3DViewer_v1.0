#include "../headers/parser.h"

// Смещение вершины по оси X.
// obj Struct, тип указателя obj_t
// значение Значение сдвига, тип float

void move_x(obj_t* obj, float value) {
  for (int i = 0; i < obj->vertex_count; i++) {
    obj->vertices[3 * i] += value;
  }
}

// Смещение вершины по оси Y.
// obj Struct, тип указателя obj_t
// значение Значение сдвига, тип float

void move_y(obj_t* obj, float value) {
  for (int i = 0; i < obj->vertex_count; i++) {
    obj->vertices[3 * i + 1] += value;
  }
}

// Смещение вершины по оси Z.
// obj Struct, тип указателя obj_t
// значение Значение сдвига, тип float

void move_z(obj_t* obj, float value) {
  for (int i = 0; i < obj->vertex_count; i++) {
    obj->vertices[3 * i + 2] += value;
  }
}

// Вращает вершину по оси x.
// Х = Х
// Y = Y*cos(a) + Z*sin(a)
// Z =-Y*sin(a) + Z*cos(a)
// obj Struct, тип указателя obj_t
// угол Коэффициент масштабирования, тип float

void rotate_x(obj_t* obj, float angle) {
  for (int i = 0; i < obj->vertex_count; i++) {
    double y = obj->vertices[3 * i + 1];
    double z = obj->vertices[3 * i + 2];
    obj->vertices[3 * i + 1] = y * cos(angle) - z * sin(angle);
    obj->vertices[3 * i + 2] = y * sin(angle) + z * cos(angle);
  }
}

// Вращает вершину по оси Y.
// X = X*cos(a) - Z*sin(a)
// Y = Y
// Z = X*sin(a) + Z*cos(a)
// obj Struct, тип указателя obj_t
// угол Коэффициент масштабирования, тип float

void rotate_y(obj_t* obj, float angle) {
  for (int i = 0; i < obj->vertex_count; i++) {
    double x = obj->vertices[3 * i];
    double z = obj->vertices[3 * i + 2];
    obj->vertices[3 * i] = x * cos(angle) + z * sin(angle);
    obj->vertices[3 * i + 2] = -x * sin(angle) + z * cos(angle);
  }
}

// Вращает вершину по оси Z.
// X = X*cos(a) + Y*sin(a)
// Y =-X*sin(a) + Y*cos(a)
// Z = Z
// obj Struct, тип указателя obj_t
// угол Коэффициент масштабирования, тип float

void rotate_z(obj_t* obj, float angle) {
  for (int i = 0; i < obj->vertex_count; i++) {
    double x = obj->vertices[3 * i];
    double y = obj->vertices[3 * i + 1];
    obj->vertices[3 * i] = x * cos(angle) - y * sin(angle);
    obj->vertices[3 * i + 1] = x * sin(angle) + y * cos(angle);
  }
}

// Масштабируем вершину по соотношению коэффициентов.
// obj Struct, тип указателя obj_t
// ratio Коэффициент масштабирования, тип float

void scale(obj_t* obj, float ratio) {
  if (ratio > 0) {
    for (int i = 0; i < (obj->vertex_count) * 3; i++) {
      obj->vertices[i] *= ratio;
    }
  }
}
