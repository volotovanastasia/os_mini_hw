Эти программы используют функции POSIX для создания и отображения 
сегмента разделяемой памяти (shm_open, shm_unlink, mmap, munmap). 
Клиент генерирует случайные числа в диапазоне от 0 до 999 и 
записывает их в разделяемую память, а сервер ожидает числа и 
выводит их на консоль. Обе программы могут быть завершены, 
нажав Ctrl+C в соответствующем терминале. После завершения, 
сегмент разделяемой памяти будет удален.