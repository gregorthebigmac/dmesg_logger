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

vector<string> terminal_feedback, error_list;

command cmd;

int main() {
	// This will run 300 times, with a 1 sec delay, for a grand total of 5 min
	// before quitting. This will result in 300 sequentially numbered text files.
	int log_num = 0;
	for (int i = 0; i < 300; i++) {
		terminal_feedback.clear();
		error_list.clear();
		string str_log_num = num_to_str(log_num);
		
		if (log_num < 10)
			str_log_num = "00" + str_log_num;
		else if (log_num < 100)
			str_log_num = "0" + str_log_num;
		
		string log_filename = "dmesg_log_" + str_log_num + ".txt";
		cmd.exec("dmesg", terminal_feedback, error_list);
		if (error_list.size > 0) {
			cout << "ERROR: " << endl;
			for (int j = 0; j < error_list.size(); j++) {
				cout << error_list[j];
			}
			return 1;
		}
		
		std::ofstream fout;
		log_filename = "data/" + log_filename;
		fout.open(log_filename.c_str());
		if (fout.is_open()) {
			for (int x = 0; x < terminal_feedback.size(); x++) {
				fout << terminal_feedback[x];
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