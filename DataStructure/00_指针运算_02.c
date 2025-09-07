#include <stdio.h>
typedef struct {
  int x, y;
} Point;

void movePointByPointer(Point *p) {
  p->x *= 10;
  p->y *= 10;
}

int main() {
  Point p1;
  p1.x = 10;
  p1.y = 20;
  movePointByPointer(&p1);
  printf("(%d,%d)", p1.x, p1.y);
  return 0;
}