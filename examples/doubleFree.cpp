int main() {
    int *p = new int(10);

    delete p;
    // Commenting this out to fix -> delete p;

    return 0;
}
