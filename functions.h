#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
// Структура факультету
typedef struct Faculty{
    char f_name[256] = "";
    int students = 0;

    Faculty() = default;
    void initialize_faculty();
    void show_structure();
}Faculty;
// Структура університету
typedef struct University{
    char name[256];
    char city[256];
    int level;
    int q_faculties;
    Faculty un_faculties[10];

    void initialize_struct_university();
    void show_structure();
    void initialize_array_of_faculties();
}University;

typedef struct help_struct{
    char university[256];
    char faculty[256];
    int students;
    void show_help_struct();
}help_struct;

void name_a_file(string & file);
void open_a_file(const string & file);
void input_to_file(const string & file);
void show_content_of_file(const string & file);
void define_biggest_faculty(const string & file);
void rewrite_to_another_file(const string & file, const string & other);
bool to_continue(string sign);