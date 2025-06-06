#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    float grades[3], avg;
} Student;

Student s;
FILE *fp;

void computeavg(Student *s) {
    s->avg = (s->grades[0] + s->grades[1] + s->grades[2]) / 3;
}

void addstudent() {
    fp = fopen("data.txt", "a");
    printf("ID: "); scanf("%d", &s.id);
    printf("Name: "); getchar(); fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    for (int i = 0; i < 3; i++) {
        printf("Grade %d: ", i + 1);
        scanf("%f", &s.grades[i]);
    }
    computeavg(&s);
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}

void viewstudents() {
    fp = fopen("data.txt", "r");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\nID: %d\nName: %s\nAvg: %.2f\n", s.id, s.name, s.avg);
    }
    fclose(fp);
}

void deletestudent() {
    int delId;
    FILE *temp = fopen("temp.txt", "w");
    fp = fopen("data.txt", "r");
    printf("Enter ID to delete: "); scanf("%d", &delId);
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id != delId)
            fwrite(&s, sizeof(s), 1, temp);
    }
    fclose(fp); fclose(temp);
    remove("data.txt");
    rename("temp.txt", "data.txt");
}

void editstudent() {
    int editId, found = 0;
    FILE *temp = fopen("temp.txt", "w");
    fp = fopen("data.txt", "r");
    printf("Enter ID to edit: "); scanf("%d", &editId);
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == editId) {
            found = 1;
            printf("New Name: "); getchar(); fgets(s.name, 50, stdin);
            s.name[strcspn(s.name, "\n")] = 0;
            for (int i = 0; i < 3; i++) {
                printf("New Grade %d: ", i + 1);
                scanf("%f", &s.grades[i]);
            }
            computeavg(&s);
        }
        fwrite(&s, sizeof(s), 1, temp);
    }
    fclose(fp); fclose(temp);
    remove("data.txt");
    rename("temp.txt", "data.txt");
    if (found)
        printf("Student info updated.\n");
    else
        printf("Student ID not found.\n");
}

int main() {
    int ch;
    do {
        printf("\n1.Add \n2.View \n3.Delete \n4.Edit \n5.Exit\nChoice: ");
        scanf("%d", &ch);
        if (ch == 1) addstudent();
        else if (ch == 2) viewstudents();
        else if (ch == 3) deletestudent();
        else if (ch == 4) editstudent();
    } while (ch != 5);
    return 0;
}
    