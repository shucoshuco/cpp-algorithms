#include <string>

int * init_vector(int size, int value);

int * copy_vector(int *v, int v_size, int new_size);

void change(int *list, int pos_a, int pos_b);

void c_quicksort(int *list, int size);

std::string print_array(int *list, int size);