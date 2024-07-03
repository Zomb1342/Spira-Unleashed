#ifndef MEMORY_TPP
#define MEMORY_TPP

template <class T>
T Memory::Read(long Address) {
    T buffer;
    bool success = Read(Address, &buffer, sizeof(T));
    if (!success) {
        PID = 0;
    }
    return buffer;
}

template <class T>
void Memory::Write(long Address, T Value) {
    bool success = Write(Address, &Value, sizeof(T));
    if (!success) {
        PID = 0;
    }
}

#endif // MEMORY_TPP

