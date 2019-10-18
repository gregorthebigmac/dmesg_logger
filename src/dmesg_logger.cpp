#include <sstream>	// for converting from int to string
#include <fstream>	// for file operations
#include <unistd.h>	// for sleep function

#include "../command/command.hpp"

template <typename T> std::string num_to_str ( T Number ) {
	std::ostringstream ss;
    ss << Number;
    return ss.str();
}

using std::cout;
using std::endl;
using std::string;
using std::vector;

vector<string> dmesg_1, dmesg_2, dmesg_out, error_list;

command cmd;

void diff_dmesg();

int main() {
	// This will run 300 times, with a 1 sec delay, for a grand total of 5 min
	// before quitting. This will result in 300 sequentially numbered text
	// files ranging from 001-300.
	for (int i = 1; i < 301; i++) {
		dmesg_1 = dmesg_2;
		dmesg_2.clear();
		error_list.clear();
		dmesg_out.clear();
		string log_num = num_to_str(i);
		
		if (i < 10)
			log_num = "00" + log_num;
		else if (i < 100)
			log_num = "0" + log_num;
		
		string log_filename = "dmesg_log_" + log_num + ".txt";
		cmd.exec("dmesg", dmesg_2, error_list);
		if (error_list.size() > 0) {
			cout << "ERROR: " << endl;
			for (int j = 0; j < error_list.size(); j++) {
				cout << error_list[j];
			}
			return 1;
		}
		
		diff_dmesg();
		
		std::ofstream fout;
		log_filename = "data/" + log_filename;
		fout.open(log_filename.c_str());
		if (fout.is_open()) {
			for (int x = 0; x < dmesg_out.size(); x++) {
				fout << dmesg_out[x];
			}
			fout.close();
		}
		else {
			cout << "ERROR: Failed to open " + log_filename + "!" << endl;
			return 2;
		}
		usleep(1000 * 1000);	// in microseconds. 1000 * 1000 = 1 second
	}
	return 0;
}

void diff_dmesg() {
	int loop_length = 0;
	cout << "loop_length = [" << loop_length << "]" << endl;
	cout << "dmesg_1.size() = [" << dmesg_1.size() << "]" << endl;
	cout << "dmesg_2.size() = [" << dmesg_2.size() << "]" << endl;
	if (dmesg_1.size() > dmesg_2.size()) {
		loop_length = dmesg_2.size();
		cout << "dmesg_2 is smaller, loop_length is now = dmesg_2.size()" << endl;
	}
	else {
		loop_length = dmesg_1.size();
		cout << "dmesg_1 is smaller, loop_length is now = dmesg_1.size()" << endl;
	}	
	for (int i = 0; i < loop_length; i++) {
		cout << "dmesg_1[" << i << "] = [" << dmesg_1[i] << "]" << endl;
		cout << "dmesg_2[" << i << "] = [" << dmesg_2[i] << "]" << endl;
		if (dmesg_1[i] != dmesg_2[i]) {
			dmesg_out.push_back(dmesg_2[i]);
			cout << "dmesg_1[" << i << "] != dmesg_2[" << i << "]" << endl;
			cout << "pushing dmesg_2[" << i << "] to dmesg_out" << endl;
		}
	}
	if (dmesg_2.size() > loop_length) {
		cout << "There are leftover lines in dmesg_2. Pushing them back to dmesg_out" << endl;
		for (int i = loop_length; i < dmesg_2.size(); i++) {
			dmesg_out.push_back(dmesg_2[i]);
		}
	}
}