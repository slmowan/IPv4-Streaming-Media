// write array of structs to a text and to a binary file

#include <stdio.h>
#include <stdlib.h>

// define person struct
typedef struct {
    double age;
    int height;
    char intial;
}

// 此方法是对fwrite的封装
int write_people_to_text(char *file_name, person_t *people, int n_people) {
    FILE *fp = fopen(file_name, "w");

    if(fp==NULL) {
        perror("open()");
        exit(1);
    }
    for(int i=0; i<n_people; i++) {
        fprintf(fp, "%f, %d, %c\n", people[i].age, people[i].height, people[i].initial);
    }

    fclose(fp);
    exit(0);

}


// write to a binary file
int write_people_to_binary(char *file_name, person_t *people, int n_people) {

    FILE *fp = fopen(file_name, "w");
    if(fp==NULL) {
        perror("open()");
        exit(1);
    }

    for(int i=0; i<n_people; i++) {
        fwrite(&people[i], sizeof(people), 1, fp);
    }

}

int write_people_to_binary_ver2(char *file_name, person_t *people, int n_people) {

    FILE *fp = fopen(file_name, "w");
    if(fp==NULL) {
        perror("open()");
        exit(1);
    }

    fwrite(people, sizeof(person_t), n_people, fp); //这里和ver1不一样

}

int write_people_to_binary_ver3(char *file_name, person_t *people, int n_people) {

    FILE *fp = fopen(file_name, "w");
    if(fp==NULL) {
        perror("open()");
        exit(1);
    }

    // write field individually
    for(int i=0; i<n_people; i++) {
        fwrite(&people[i].height, sizeof(double), 1, fp);
        fwrite(&people[i].age, sizeof(int), 1, fp);
        fwrite(&people[i].initial, sizeof(char), 1, fp);
    }

    // if written in this way, the total size of binary file is smaller than of ver1 and ver2
    // because of structs padding


}