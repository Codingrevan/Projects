#include "huffman.h"

int main(void){
    FILE* file = fopen("input.txt", "r");
    if(file == NULL){
        printf("Nie udało się otworzyć pliku!\n");
        exit(1);
    }
    int n = 0;
    bool flag = false;
    char character;
    leaf* tab = NULL;
    while((character = getc(file)) != EOF){
        flag = false;
        for(int i = 0; i < n; i++){
            if(tab[i].sign == character){
                tab[i].counter += 1;
                flag = true;
                break;
            }
        }
        if(flag == false){
            n++;
            tab = realloc(tab, n * sizeof(*tab));
            tab[n - 1] = (leaf){NULL, NULL, 1, character};
        }
    }
    fclose(file);
    heap* holder = create_heap(n, tab);
    printf("Na samym początku:\n\n");
    print_heap(holder);
    build_min_heap(holder);
    printf("Zbudowany kopiec:\n\n");
    print_heap(holder);
    leaf* x, *y, *z;
    x = y = z = NULL;
    for(int i = 1; i < n; i++){
        z = malloc(sizeof(*z));
        if(z == NULL){
            printf("Nie udało się zamallocować węzła przy wyborze zachłannym!\n");
            exit(3);
        }
        x = heap_extract_min(holder);
        y = heap_extract_min(holder);
        z -> left = x;
        z -> right = y;
        z -> counter = x -> counter + y -> counter;
        z -> sign = '.';
        min_heap_insert(holder, z);
        free(z);
    }
    z = heap_extract_min(holder);
    free_heap(&holder);
    char tabsign[n];
    char** tabcodes = malloc(n * sizeof(char*));
    for(int i = 0; i < n; i++)
        tabcodes[i] = malloc((n + 1) * sizeof(char));
    char buffer[n + 1];
    int idx = 0;
    treewalk(z, 0, buffer, tabsign, tabcodes, &idx);
    for(int i = 0; i < n; i++){
        if(tabsign[i] != '\n')
            printf("Litera: %c ", tabsign[i]);
        else
            printf("Litera: \\n ");
        printf("kod: %s\n", tabcodes[i]);
    }

    FILE* input = fopen("input.txt", "r");
    if(input == NULL){
        printf("Nie udało się otworzyć pliku tekstowego do kodowania!\n");
        exit(5);
    }
    FILE* output = fopen("output.bin", "wb");
    if(output == NULL){
        printf("Nie udało się otworzyć pliku binarnego do zapisu!\n");
        exit(6);
    }
    fseek(input, 0, SEEK_END);
    int input_length = ftell(input);
    rewind(input);
    fwrite(&input_length, sizeof(int), 1, output);
    int id;
    char* code = NULL;
    unsigned char buf = 0;
    int bit_count = 0;
    unsigned char bit;
    while((character = getc(input)) != EOF){
        id = -1;
        for(int k = 0; k < n; k++){
            if(tabsign[k] == character){ 
                id = k; 
                break; 
            }
        }
        code = tabcodes[id];
        for(int j = 0; code[j] != '\0'; j++){
            bit = code[j] - '0';
            write_bit(output, bit, &buf, &bit_count);
        }
    }
    if(bit_count > 0){
        buf <<= (8 - bit_count);
        fwrite(&buf, 1, 1, output);
    }
    fclose(input);
    fclose(output);
    decode(z, "output.bin", "decoded.txt");
    for(int i = 0; i < n; i++)
        free(tabcodes[i]);
    free(tabcodes);
    free_tree(z);
    return 0;
}



