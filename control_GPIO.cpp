/** Simple On-board LED flashing program - written in C++ by Derek Molloy
*    simple functional struture for the Exploring BeagleBone book
*
*   This program takes three command line arguments: output GPIO number, output GPIO state, and input GPIO number
*	The program then turns on output GPIO or turns it off based on the state provided, either "hi" or "lo"
*	Lastly, the program reads out the value from given input GPIO number
* */

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

#define PATH "/sys/class/gpio/"

int write(string path, string fileName, string value){
   fstream fs;
   fs.open((path + fileName).c_str());
   if (!fs.is_open()){
	   perror("GPIO: write failed to open file ");
	   return -1;
   }
   fs << value;
   fs.close();
   return 0;
}

void setVal(string path, int value){
	write(path, "value", to_string(value));
}

string read(string path, string fileName){
   fstream fs;
   fs.open((path + fileName).c_str());
   if (!fs.is_open()){
	   perror("GPIO: read failed to open file ");
    }
   string input;
   getline(fs,input);
   fs.close();
   return input;
}

int getVal(string path){
	string out = read(path, "value");
	if(out == "0"){
		return 0;
	}
	else if(out == "1"){
		return 1;
	}
}

int main(int argc, char* argv[]){
   if(argc!=4){
	cout << "Usage is control_GPIO and output GPIO number, hi or low, and input GPIO number." << endl;
	cout << "e.g. control_GPIO 60 hi 46" << endl;
	cout << "this sends a high signal through GPIO 60 and reads from GPIO 46" << endl;
        return -1;
   }
   string outGPIO(argv[1]);
   string outState(argv[2]);
   string inGPIO(argv[3]);
   
   cout << "Starting the control_GPIO program" << endl;
	ostringstream outGstream;
	ostringstream inGstream;
	//concatenate through string stream
	outGstream<<"/sys/class/gpio/gpio"<<outGPIO<<"/";
	inGstream<<"/sys/class/gpio/gpio"<<inGPIO<<"/";
	//convert stream to string
	string outG = string(outGstream.str());
	string inG = string(inGstream.str());
	
	if(outState == "hi"){
		setVal(outG, 1);
	}
	else if(outState == "lo"){
		setVal(outG, 0);
	}
	else{
		cout<<"invalid state entered"<<endl;
		return -2;
	}
	
	cout<<"reading out GPIO"<<inGPIO<<": "<<getVal(inG)<<"\n"; 
   
   return 0;
}

