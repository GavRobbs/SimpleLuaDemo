#include <sol/sol.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

std::string read_script(std::string filename){
    //A utility function to get file contents fast
    std::ifstream file{filename};
    std::stringstream file_contents;
    file_contents << file.rdbuf();
    file.close();
    return file_contents.str();
}

struct Person{

    Person(std::string name, int age) : name(name), age(age){

    }

    std::string name;
    int age;

    void print_demographics(){
        std::cout << "I am " << name << " and I am " << age << " years old." << std::endl; 
    }

    void increase_age(){
        age += 1;
    }
};

struct vec2{

    float x;
    float y;
    
    vec2() : x(0.0f), y(0.0f){

    }

    vec2(float x, float y) : x(x), y(y){

    }

    vec2(const vec2 & other) : x(other.x), y(other.y){
        /* This is a bit interesting. Generally, you'd want to pass something like a vector by value, but
        lua forces all complex objects to be passed by reference. This is used to give my object a copy
        assignment operator.*/
    }

    vec2 operator+(const vec2 & other) const{
        return vec2(x + other.x, y + other.y);
    }

    vec2 operator-(const vec2 & other) const {
        return vec2(x - other.x, y - other.y);
    }

    vec2 operator*(const float & other) const{
        return vec2(x * other, y * other);
    }

    bool operator==(const vec2 & other) const {
        //Resist the urge to comment, I know, I just can't be arsed
        return x == other.x && y == other.y;
    }

    float magnitudeSquared() const{
        return x * x + y * y;
    }

    float magnitude() const{
        return std::sqrtf(magnitudeSquared());
    }

    float dot(const vec2 & other){
        return x * other.x + y * other.y;
    }

    void normalize(){
        float len = magnitude();
        x /= len;
        y /= len;
    }

    void display(){
        std::cout << "(" << x << " , " << y << ")" << std::endl;
    }    

};

void setup_person_struct(sol::state &lua){
    //This is actually pretty straightforward
    lua.new_usertype<Person>("Person",
        sol::constructors<Person(std::string, int)>(),
        "print_demographics",
        &Person::print_demographics,
        "increase_age",
        &Person::increase_age
    );
}

void setup_vector_extension(sol::state &lua){
    lua.new_usertype<vec2>("vec2",
        sol::constructors<vec2(), vec2(float, float), vec2(const vec2&)>(),
        "x", &vec2::x,
        "y", &vec2::y,
        sol::meta_function::addition, &vec2::operator+,
        sol::meta_function::subtraction, &vec2::operator-,
        sol::meta_function::multiplication, &vec2::operator*,
        sol::meta_function::equal_to, &vec2::operator==,
        "display", &vec2::display,
        "magnitudeSquared", &vec2::magnitudeSquared,
        "magnitude", &vec2::magnitude,
        "normalize", &vec2::normalize,
        "dot", &vec2::dot
    );
}

int main() {
    //Create our lua state
    sol::state lua{};

    //Include the lua standard library
    lua.open_libraries(sol::lib::base, sol::lib::math);

    int counter{0};

    std::cout << "Running hello world from file hello_world.lua" << std::endl;
    std::string hello_file = read_script("Scripts/hello_world.lua");
    lua.script(hello_file);

    std::cout << std::endl << "Calling a function created in C++ and exposed to lua" << std::endl;
    lua.set_function("count", [&counter] {
        ++counter;
        std::cout << "The counter is now " << counter << " thanks to the function called from lua" << std::endl;
    });
    lua.script("count()");

    std::cout << std::endl << "Exposing a complex object type to lua including functions and member data" << std::endl;
    setup_person_struct(lua);
    std::string obj_demo = read_script("Scripts/object_demo.lua");
    lua.script(obj_demo);

    std::cout << std::endl << "Another complex object, with operator overloading and copy semantics" << std::endl;
    setup_vector_extension(lua);
    std::string vec_demo = read_script("Scripts/vectors.lua");
    lua.script(vec_demo);

    std::cout << "Application finished" << std::endl;

    return 0;
}