#include "functions.h"

void Faculty::initialize_faculty() {

    char i_f_name[256];
    cout << "Faculty name: ";
    gets(i_f_name);
    strcpy(this->f_name,i_f_name);
    fflush(stdin);

    int f_quantity;
    cout << "Students: ";
    cin >> f_quantity;
    this->students = f_quantity;
    fflush(stdin);
}

void Faculty::show_structure() {
    cout << left << setw(12) << f_name << left << setw(12) << students << endl;
}

void University::initialize_array_of_faculties() {

    for(int i = 0; i < this->q_faculties; i++) {
        cout << "Faculty #" << i+1 << ": " << endl;
        this->un_faculties[i].initialize_faculty();
    }
}

void University::show_structure() {
    cout << left << setw(12) << name << left << setw(12) << city << left << setw(12) << level << left << setw(12) << q_faculties << endl;
    cout << left << setw(12) << "Faculty" << left << setw(12) << "Students" << endl;
    for(int i = 0; i < q_faculties; i++)
        un_faculties[i].show_structure();
}

void University::initialize_struct_university() {
    char u_name[256];
    char u_city[256];
    int u_level;
    int u_q_faculties;

    cout << "University name: ";
    gets(u_name);
    strcpy(this->name,u_name);
    fflush(stdin);

    cout << "City: ";
    gets(u_city);
    strcpy(this->city, u_city);
    fflush(stdin);

    cout << "Level: ";
    cin >> u_level;
    this->level = u_level;
    fflush(stdin);

    cout << "Quantity of faculties(max 10): ";
    cin >> u_q_faculties;
    this->q_faculties = u_q_faculties;
    fflush(stdin);

    this->initialize_array_of_faculties();
}

void name_a_file(string &file) {
    fflush(stdin);
    cout << "Name a file: ";
    getline(cin, file);
    fflush(stdin);
}

void open_a_file(const string &file) {
    ofstream out_file;
    out_file.open(file, ios::binary);
    out_file.close();
}

void input_to_file(const string &file) {
    ofstream out_file;
    University tmp_university;

    out_file.open(file, ios::binary | ios::app);
    cout << endl << "Input to file: " << endl;
    if (out_file.is_open()) {
        do {
            tmp_university.initialize_struct_university();
            out_file.write((char*)&tmp_university,sizeof(University));
        } while (to_continue("Create new note? (y/n): "));
    }
    else
        cout << "Cannot open your file\n";
    out_file.close();
}

bool to_continue(string sign) {
    bool result, flag;
    char ch;
    do {
        flag = true;
        cout << sign;
        cin >> ch;
        if (ch=='y' || ch=='Y') {
            fflush(stdin);
            result = true;
        } else if(ch=='n' || ch=='N') {
            fflush(stdin);
            result = false;
        } else {
            fflush(stdin);
            flag = false;
        }
    } while (!flag);

    return result;
}

void show_content_of_file(const string &file) {
    ifstream in_file;
    University tmp_university;

    in_file.open(file,ios::binary);
    cout << endl << "Content of " << file << endl;
    if(in_file.is_open()) {
        cout << left << setw(12) << "NAME" << left << setw(12) << "CITY" << left << setw(12) << "LEVEL" << left << setw(12) << "FACULTIES" << endl;
        cout << "---------------------------------------------------\n";
        while (in_file.read((char*)&tmp_university,sizeof(University))) {
            tmp_university.show_structure();
            cout << "---------------------------------------------------\n";
        }
        cout << endl;
    } else
        cout << "Cannot open your file\n";
    in_file.close();

}
void define_biggest_faculty(const string & file) {

    int define_array_size(const string & file, const char* city); //визначити розмір масиву університетів із вказаним містом
    University* fill_array_with_data(University* array, int size, const string & file, const char* city); //заповнити масив університетів із вказаним містом
    void show_array_of_universities(University* array, int size); //виведення масиву університетів
    void show_array_of_faculties(help_struct* array, int size); //виведення масиву факультетів із найбільшою кількістю студентів
    help_struct* define_biggest_faculties(University* array, int size); //визначити факультет із найбільшою кількістю студентів у кожному університеті
    void define_biggest_faculty_in_list(help_struct* array, int size); //визначити факультет із найбільшою кількістю студентів

    University* list_of_universities;
    help_struct* list_of_faculties;
    char city[256];
    int size = 0;

    cout << "Input city to define: ";
    gets(city);
    fflush(stdin);

    size = define_array_size(file, city);
    list_of_universities = fill_array_with_data(list_of_universities, size, file, city);
    list_of_faculties = define_biggest_faculties(list_of_universities, size);
    define_biggest_faculty_in_list(list_of_faculties,size);

    delete[] list_of_universities;
    delete[] list_of_faculties;

}

void help_struct::show_help_struct() {
    cout << left << setw(12) << university << left << setw(12) << faculty << left << setw(12) << students << endl;
}

void rewrite_to_another_file(const string & file, const string & other) {
    ifstream in_file;
    ofstream out_file;
    University tmp_university;

    in_file.open(file, ios::binary);
    out_file.open(other, ios::binary);

    if (in_file.is_open()&&out_file.is_open()) {
        while (in_file.read((char*)&tmp_university, sizeof(University))) {
            if (tmp_university.level==3||tmp_university.level==4) {
                out_file.write((char*)&tmp_university, sizeof(University));
            }
        }
    } else
        cout << "Cannot open your files\n";

    in_file.close();
    out_file.close();

}

int define_array_size(const string & file, const char* city) {
    ifstream in_file;
    University tmp_university;
    int counter = 0;

    in_file.open(file,ios::binary);

    while(in_file.read((char*)&tmp_university, sizeof(University)))
        if(strcmp(tmp_university.city, city)==0)
            counter++;

    in_file.close();

    return counter;

}

University* fill_array_with_data(University* array, int size, const string & file, const char* city) {
    ifstream in_file;
    University tmp_university;

    array = new University[size];

    in_file.open(file, ios::binary);

    int i = 0;
    while (in_file.read((char*)&tmp_university,sizeof(University))) {
        if (strcmp(tmp_university.city, city)==0) {
            array[i] = tmp_university;
            i++;
        }
    }

    in_file.close();

    return array;
}

help_struct* define_biggest_faculties(University* array, int size) {
    help_struct* list_of_faculties = new help_struct[size];
    for (int i = 0; i < size; i++) {

        Faculty faculty_result = array[i].un_faculties[0];

        for(int j = 1; j < array[i].q_faculties; j++) {
            if (array[i].un_faculties[j].students>faculty_result.students)
                faculty_result = array[i].un_faculties[j];
        }

        strcpy(list_of_faculties[i].faculty,faculty_result.f_name);
        strcpy(list_of_faculties[i].university,array[i].name);
        list_of_faculties[i].students = faculty_result.students;
    }

    return list_of_faculties;
}

void define_biggest_faculty_in_list(help_struct* array, int size) {
    help_struct result;
    result = array[0];
    for (int i = 1; i < size; i++)
        if (array[i].students > result.students)
            result = array[i];

    cout << "Faculty with the biggest amount of students:\n";
    cout << left << setw(12) << "Univer" << left << setw(12) << "Faculty" << left << setw(12) << "Students" << endl;
    result.show_help_struct();
}