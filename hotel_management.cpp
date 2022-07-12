#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

// creating a class
class Room{
    // creating private properties
    private:
        int number;
        string type;
        double rate;
        bool availability;
    // creating public methods
    public:
        // empty constructor
        Room() {}
        // constructor with 4 arguments
        Room(int number, string type, double rate, bool availability) {
            this->number = number;
            this->type = type;
            this->rate = rate;
            this->availability = availability;
        }
        // setter and getter methods
        void set_number(int number) {
            this->number = number;
        }
        int get_number() {
            return this->number;
        }
        void set_type(string type) {
            this->type = type;
        }
        string get_type() {
            return this->type;
        }
        void set_rate(double rate) {
            this->rate = rate;
        }
        double get_rate() {
            return this->rate;
        }
        void set_availability(bool availability) {
            this->availability = availability;
        }
        bool get_availability() {
            return this->availability;
        }
        // show method to show the room info
        void show() {
            cout << "Room No: " << this->number << "\t\t";
            cout << "Room Type: " << this->type << "\t\t";
            cout << "Room Rate: " << this->rate << "\t\t";
            cout << "Room Availability: " << this->availability << "\t\t";
        }
};

// creating a Date class
class Date{
    // creating private properties
    private:
        int day;
        int month;
        int year;
    // creating public methods
    public:
        // creating the setter function to set the date
        void set_all(int day, int month, int year){
            this->day = day;
            this->month = month;
            this->year = year;
        }
        // creating a show method to show the date
        void show() {
            cout << this->day << "-" << this->month << "-" << this->year;
        }
};

// creating a Reservation class
class Reservation {
    // create private properties
    private:
        int ID;
        string guest_name;
        Room room_info;
        Date check_in;
        int number_of_nights;
        string status;
    // creating public methods
    public:
        // creating setter and getters for all the private properties
        void set_ID(int ID) {
            this->ID = ID;
        }
        int get_ID() {
            return this->ID;
        }
        void set_guest_name(string guest_name) {
            this->guest_name = guest_name;
        }
        string get_guest_name() {
            return this->guest_name;
        }
        void set_room_info(Room room_info) {
            this->room_info = room_info;
        }
        Room get_room_info() {
            return this->room_info;
        }
        void set_check_in(Date check_in) {
            this->check_in = check_in;
        }
        Date get_check_in() {
            return this->check_in;
        }
        void set_number_of_nights(int number_of_nights) {
            this->number_of_nights = number_of_nights;
        }
        int get_number_of_nights() {
            return this->number_of_nights;
        }
        void set_status(string status) {
            this->status = status;
        }
        string get_status() {
            return this->status;
        }
        // creating a show method
        void show() {
            cout << "Guest ID: " << this->ID << endl;
            cout << "Guest Name: " << this->guest_name << endl;
            cout << "Room info: ";
            this->room_info.show();
            cout << "Checkin Date: ";
            check_in.show();
            cout << endl;
            cout << "Number of nights: " << this->number_of_nights << endl;
            cout << "Status: " << this->status << endl;
            
        }
};
// function to read the rooms data from a text file
void read_rooms();
// function to keep displaying the menu and get the input and call the apropriate function
void menu();
// function to reserve a room
void reserve_room();
// function to get the room index 
int get_room_index(int room_no);
// function to search the available rooms having the lowest price
void search_by_lowest_price();
// function to search the available rooms having a given type
void search_by_room_type();
// search room function to display to search options and search the room
void search_room();
// function to checkout
void checkout();
// function to get the reservation index by geust_id
int get_reservation_index(int guest_id);
// function to cancel a reservation
void cancel_reservation();
// function to display the bill
void display_bill();
// creating a Room array which can store 50 rooms data
Room rooms[50];
// creating a Reservation array which can store the reservation record for 100 reservations
Reservation reservations[100];
// creating a reservation_index variable to keep track the next empty index in reservation array
int reservation_index = 0;
// creating a total_rating variable to store the total ratings given by users
double total_rating = 0;
// creating a ratings variable to store the number of ratings we got
int ratings = 0;
// creating a main function to execute all the functions
int main() {
    // calling read rooms function to read the data from the text file and store in Room array
    read_rooms();
    // calling the menu function to keep displaying the menu and calling the apropriate functions
    menu();
    // returning 0
    return 0;
}
// function to display the bill
void display_bill() {
    // guest id variable to get the guest id from user
    int guest_id;
    cout << "Enter Your Guest ID: " ;
    cin >> guest_id;
    // getting the reservation index by passing the guest_id 
    int reserve_index = get_reservation_index(guest_id);
    // checking if the guest is available
    if(reserve_index == -1) {
        // if not available the printing a message
        cout << "Guest Not Found..." << endl;
    }
    // if available then 
    else{
        // checking the status
        if(reservations[reserve_index].get_status() == "left"){
            // if status if left then showing the reservation details
            reservations[reserve_index].show();
            // showing the price of stay
            cout << "Total Price: " << reservations[reserve_index].get_room_info().get_rate() * reservations[reserve_index].get_number_of_nights() << endl;
        }
    }
}
// function to cancel a reservation
void cancel_reservation() {
    // guest id variable to get the guest id from user
    int guest_id;
    cout << "Enter Your Guest ID: " ;
    cin >> guest_id;
    // getting the reservation index by passing the guest_id 
    int reserve_index = get_reservation_index(guest_id);
    // checking if the guest is available
    if(reserve_index == -1) {
        // if not available the printing a message
        cout << "Guest Not Found..." << endl;
    }
    // if available then 
    else{
        // getting the room index by passing room number
        int room_index = get_room_index(reservations[reserve_index].get_room_info().get_number());
        // setting the room availability true
        rooms[room_index].set_availability(true);
        // making reservation status cancelled
        reservations[reserve_index].set_status("cancelled");
        // showing the reservation details
        reservations[reserve_index].show();
    }
}
// function to checkout
void checkout() {
   // guest id variable to get the guest id from user
    int guest_id;
    cout << "Enter Your Guest ID: " ;
    cin >> guest_id;
    // getting the reservation index by passing the guest_id 
    int reserve_index = get_reservation_index(guest_id);
    // checking if the guest is available
    if(reserve_index == -1) {
        // if not available the printing a message
        cout << "Guest Not Found..." << endl;
    }
    // if available then 
    else{
        // getting the room index by passing the reservation room nuumber
        int room_index = get_room_index(reservations[reserve_index].get_room_info().get_number());
        // setting the room availabilty to true
        rooms[room_index].set_availability(true);
        // setting the status as left
        reservations[reserve_index].set_status("left");
        // showing the reservation details
        reservations[reserve_index].show();
        // creating a user_rating variable to get the rating from user
        double user_rating;    
        // runnig a while loop until user enter the rating between 1 - 5
        while(true) {
            cout << "Rate Your stay in the Hotel on a scale of 1-5: " ;
            cin >> user_rating;
            // checking if the ratings is in between 1 - 5  
            if(user_rating >= 1 && user_rating <= 5)
                break;
        }
        // adding the ratings in total_ratings
        total_rating += user_rating;
        // increasing the number of ratings
        ratings++;
        // showing the average rating to the user
        cout << "Our average rating is " << total_rating/ratings << " based on " << ratings << " ratings." << endl;
    }
}
// function for searching a room
void search_room() {
    // creating a choice variable to get the user choice
    int choice = 0;
    // running a while to until user choose either 1 or 2
    while(choice < 1 || choice > 2) {
        // showing the available options to the user
        cout << "1. Search Room By Room Type." << endl;
        cout << "2. Search Room Lowest Price." << endl;
        cout << "Select any of above option: " ;
        cin >> choice;
    }
    // checking the user choice and calling apropriate function
    switch(choice) {
        case 1 :
            search_by_room_type();
            break;
        case 2 :
            search_by_lowest_price();
            break;
    }
}
// function to search the room by it's type
void search_by_room_type() {
    // variable to store the type that user wants
    string type;
    cout << "Enter Room Type: ";
    cin >> type; // getting the  type of room from the user
    // running a for loop 
    for(int i=0; i<50; i++) {
        // checking the room type and availability
        if(rooms[i].get_type() == type && rooms[i].get_availability()){
            // if room is equal to the room that user want then printing the room details
            rooms[i].show();
            // adding a new line
            cout << endl;
        }
    }
}
// function to search the room by lowest price
void search_by_lowest_price(){
    // creating and initializing lowest price with the price of first room
    int lowest_price = rooms[0].get_rate();
    // runnig a for loop for all the rooms
    for(int i=0; i<50; i++) {
        // checking if any room has low price then lowest price_variable
        if(rooms[i].get_rate() < lowest_price && rooms[i].get_availability()) {
            // if yes then the lowest_price = the price of the room
            lowest_price = rooms[i].get_rate();
        }
    }
    // running a for loop
    for(int i=0; i<50; i++) {
        // checking the room which matches to the lowest_price
        if(rooms[i].get_rate() == lowest_price) {
            // if yes then showing room details
            rooms[i].show();
            // adding a new line
            cout << endl;
        }
    }
    
}
// function to reserve a room
void reserve_room() {
    int room_no;
    // running a while loop to get the room number from user
    while(true){
        cout << "Enter Room No: that you want to reserve: ";
        cin >> room_no;
        // checking the room if available
        int room_index = get_room_index(room_no);
        // if the room is not available
        if(room_index == -1){
            // then showing a message
            cout << "Room not exists..." << endl;
            // and continue the program to ask the room number again
            continue;
        }
        // if room exists
        else{
            // then checking the room availability
            if(rooms[room_index].get_availability()){
                // if available then creating variables to get user's data
                int guest_id , year , month , day , no_of_nights;
                // getting user data
                string guest_name;
                cout << "Enter Guest ID: " ;
                cin >> guest_id;
                cout << "Enter Guest Name: " ;
                cin >> guest_name;
                cout << "Enter Checkin date: " ;
                cin >> day;
                cin >> month;
                cin >> year;
                cout << "Enter number of nights: " ;
                cin >> no_of_nights;
                Date date; // creating a Date class object
                date.set_all(day , month , year); // setting the object date
                reservations[reservation_index].set_ID(guest_id); // setting the user ID
                reservations[reservation_index].set_guest_name(guest_name); // setting user name
                reservations[reservation_index].set_check_in(date); // setting the date
                reservations[reservation_index].set_number_of_nights(no_of_nights); // setting no of nights
                rooms[room_index].set_availability(false);// setting the room availability false
                reservations[reservation_index].set_room_info(rooms[room_index]); // setting room info
                reservations[reservation_index].set_status("confirmed");// setting status as confirmed
                cout << "Room Reserved Successfully..." << endl; // showing success message
                cout << "Reservation Details" << endl;
                reservations[reservation_index].show(); // showing reservations details
                reservation_index++; // increasing the reservation index
                break; // breaking the function
            }
            // if room not available
            else{
                // showing a message
                cout << "Room is not available..." << endl;
            }
        }
    }
    
}
// function to get the room index
int get_room_index(int room_no) {
    // running a for loop
    for(int i=0; i<50; i++) {
        // checking the given number with the room number
        if(rooms[i].get_number() == room_no){
            // if matches then returning the i
            return i;
        }
    }
    // if no room found return -1
    return -1;
}
// function to get the reservation index
int get_reservation_index(int guest_id) {
    // running a for loop
    for(int i=0; i<reservation_index; i++){
        // checking the given guest_id with the reservation guest_id
        if(reservations[i].get_ID() == guest_id) {
            // if matches then returning the i
            return i;
        }
    }
    // if no reservation found the return -1
    return -1;
}
// function to show the menu
void menu() {
    // running a while loop
    while(true){
        // showing the menu options
        cout << "1. Reserve a Room." << endl;
        cout << "2. Search for availabble rooms." << endl;
        cout << "3. Checkout." << endl;
        cout << "4. Cancel a reservation." << endl;
        cout << "5. Display information." << endl;
        cout << "6. Exit." << endl;
        cout << "Select any of above option: " ;
        int user_choice;
        cin >> user_choice; // getting user option/choice
        // checking if choice is not in between 1 - 6
        if(user_choice < 1 || user_choice > 6){
            // if yes then continue the function to get correct choice
            continue;
        }    
        // checking if choice is = 6
        if(user_choice == 6){
            // if yes then showing a message
            cout << "Goodbye..." << endl;
            // and breaking the while loop
            break;
        }
        // switch condition to call an apropriate function for user choice
        switch(user_choice){
            // if case 1
            case 1 :
                // call reserve_room
                reserve_room();
                break; 
            // if case 2
            case 2 :
                // call search_room
                search_room();
                break;
            // if case 3
            case 3 :
                // call checkout
                checkout();
                break;
            // if case 4
            case 4 :
                // call cancel_reservation
                cancel_reservation();
                break;
            // if case 5
            case 5 :
                // call display_bill
                display_bill();
                break;
        }
    }
    
}
// function to read the rooms data from a text file
void read_rooms() {
    // creating input stream object
    ifstream file;
    // opening the text file
    file.open("rooms.txt");
    // creating a string variable 
    string line;
    // creating a index variable
    int index = 0;
    // running a while loop until the end of file
    while(!file.eof()) {
        getline(file , line); // get the number
        stringstream convert_int;
        convert_int << line; // creating string stream object to convert string into int
        int number; // int variable to store the number
        convert_int >> number; // converting the string number into int and storing in number variable
        rooms[index].set_number(number);
        getline(file , line); // get the type
        rooms[index].set_type(line);
        getline(file , line); // get the rate
        stringstream convert_double;
        convert_double << line; // creating string stream object to convert string into double
        double rate;
        convert_double >> rate; // converting the string rate into double and storing in rate variable
        rooms[index].set_rate(rate);
        getline(file , line); // get the availability
        if(line == "true")
            rooms[index].set_availability(true);
        else
            rooms[index].set_availability(false);
        getline(file , line); // get the empty line
        index++;
    }
}