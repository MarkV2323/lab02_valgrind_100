int main() {
    int *p = new int[10];
    p[9] = 1; // Corrected this to size properly.
    
    delete[] p; // Deallocates the memory from p.
    return 0;

    /*
     * If allocated with malloc, calloc, realloc, valloc, or memalign, you must deallocate with free*.
     * If allocated with new[], you must deallocate with delete[].
     * If allocated with new, you must deallocate with delete.
     *
    */
}
