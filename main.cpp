#include "functions.h"

int main() {
    string file;
    string second_file;

    name_a_file(file);
    open_a_file(file);
    input_to_file(file);
    show_content_of_file(file);
    define_biggest_faculty(file);
    name_a_file(second_file);
    rewrite_to_another_file(file, second_file);
    show_content_of_file(second_file);
    while (to_continue("Append file? (y/n): ")) {
        input_to_file(file);
        show_content_of_file(file);
        define_biggest_faculty(file);
        rewrite_to_another_file(file, second_file);
        show_content_of_file(second_file);
    }
    return 0;
}
