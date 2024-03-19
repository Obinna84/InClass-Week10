#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

enum CarMakeType {Audi, Chrysler, Ford, Nissan, Mercedes, Honda, Volvo, Porsche, Lexus}; 

struct DateType{
  int day;
  int month;
  int year;
};
struct CarType{
  string fname;
  string lname;
  float cost;
  DateType date_delivery;
  CarMakeType car_make;
};

vector<CarType> allCars;

CarMakeType findCarType(string s){
  if(s == "A"){return Audi;} if(s == "N"){return Nissan;} if(s == "C"){return Chrysler;}
  if(s == "M"){return Mercedes;} if(s == "F"){return Ford;} if(s == "H"){return Honda;}
  if(s == "V"){return Volvo;} if(s == "P"){return Porsche;} if(s == "L"){return Lexus;}
  return Lexus;
}
string car_to_string(CarMakeType c){
  if(c == Audi){return "Audi";} if(c == Nissan){return "Nissan";} if(c == Chrysler){return "Chrysler";}
  if(c == Mercedes){return "Mercedes";} if(c == Ford){return "Ford";} if(c == Honda){return "Honda";}
  if(c == Volvo){return "Volvo";} if(c == Porsche){return "Porsche";} if(c == Lexus){return "Lexus";}
  return "";
}

vector<string> split(string s, char separator){
  vector<string> returned;
  returned.push_back("");
  int values_stored = 0;
  for(int i=0; i < s.length(); i++){
    if(returned.at(values_stored).length() < 1){
      if(s[i] != separator){
        returned.at(values_stored) += s[i];
      }
    }
    else{
      if(s[i] != separator){
        returned.at(values_stored) += s[i];
      }
      else{
        returned.push_back("");
        values_stored++;
      }
    }
  }
  return returned;
}

CarType get_car_data(string s){
  CarType current;
  vector<string> stored_info = split(s,' ');
  current.fname = stored_info[0];
  current.lname = stored_info[1];
  current.cost = stof(stored_info[2]);
  current.date_delivery.day = stoi(stored_info[3]);
  current.date_delivery.month = stoi(stored_info[4]);
  current.date_delivery.year = stoi(stored_info[5]);
  current.car_make = findCarType(stored_info[6]);
  return current;
}

void modify_car_data(vector<CarType> cars,int location, float discount){ 
  allCars[location].cost -= cars[location].cost * (discount * 0.01);
}

void output_car_data(ofstream& ofile, vector<CarType> cars){
  for(CarType i: cars){
    string car_str = i.fname + "\t" + i.lname + "\t" + to_string(i.cost) + "\t" + to_string(i.date_delivery.month) + "/" + to_string(i.date_delivery.day) + "/" + to_string(i.date_delivery.year) + "\t" + car_to_string(i.car_make);
    ofile << car_str << endl;
    cout << car_str << endl;
  }
}

void lookup_car_data(vector<CarType> cars, string carMake){
  float discount;
  string dis_str;
  bool found = false;
  for(int i = 0; i < cars.size(); i++){
    if(cars.at(i).car_make == findCarType(carMake) && !found && carMake != "stop"){
      cout << "You are Modifying: " << "\n" << "\tCustomer Name:\t" << cars[i].fname + " " << cars[i].lname <<  "\n" << "\tCar Price:\t" << to_string(cars[i].cost) + "\n" << "\tPurchase Date:\t" << to_string(cars[i].date_delivery.month) +"/" << to_string(cars[i].date_delivery.day)+"/" << to_string(cars[i].date_delivery.year) + "\n" << "\tCar Model:\t" + car_to_string(cars[i].car_make)<<endl;
      cout << "Enter the Discount ( ex: 10 = 10% ): ";
      cin >> dis_str;
      discount = stof(dis_str);
      cout << "\n" << "old cost is: $" << allCars[i].cost << endl;
      modify_car_data(cars,i,discount);
      cout << "new cost is: $" << allCars[i].cost << endl;
      cout << dis_str + "%" + " Discount is Being Applied" << "\n" <<endl;
      found = true;
    }
  }
}

int main(){
  string input_file_path = "inclass10.txt";
  string output_file_path = "output-inclass10.txt";
  ifstream input_file;
  ofstream output_file;
  output_file.open(output_file_path);
  input_file.open(input_file_path);
  string curr;
  while(getline(input_file,curr)){
    allCars.push_back(get_car_data(curr));
  }
  input_file.close();
  string userInput;
  CarType carToModify;
  string carManufacturers = "\t(F - Ford, L - Lexus, N - Nissan, M - Mercedes, H - Honda,\n\tA - Audi, C - Chrysler, V - Volvo, P - Porsche)";
  do{
    cout << "Choose from list of car manufacturers below. \n" << carManufacturers <<endl;
    cout << "Type 'stop' to exit prompt" << endl;
    cout << "Make of Car Whose Discount You Want To Modify: ";
    cin >> userInput;
    lookup_car_data(allCars,userInput);
  }
  while(userInput != "stop");
  cout << "\n" <<  "List of updated car prices and owners" << "\n" <<endl;
  output_car_data(output_file,allCars);
  return 0;
}
