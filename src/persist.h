#ifndef __PERSIST__
#define __PERSIST__

#include "rect.h"

enum PersistFlags {
        PERSIST_LEFT = 1,
        PERSIST_RIGHT,
        PERSIST_UP,
        PERSIST_DOWN
};

/* Atualiza as flags de persistência relativas à movimentação do disparo */
void update_persist(Rectangle *rect1, Rectangle *rect2, unsigned char *persist1, unsigned char *persist2);

#endif // __PERSIST__