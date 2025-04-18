#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;
// main program
//logic: define all variables, ask for all inputs
//then make a while loop and check for comma
//finally make a histogram
int main()
{
    // 4 string variables
    string title, column1, column2, datapoint;

      // Vectors to store author names and number of novels
    vector<string> name;
    vector<int> numberofnovel;

    // Enter a title, column 1, column 2, and header
    cout << "Enter a title for the data:" << endl;
    getline(cin, title);
    cout << "You entered: " << title << endl;

    cout << "Enter the column 1 header:" << endl;
    getline(cin, column1);
    cout << "You entered: " << column1 << endl;

    cout << "Enter the column 2 header:" << endl;
    getline(cin, column2);
    cout << "You entered: " << column2 << endl;

    // Need a loop for datapoint
    while (true) {
        // ask for data point
        cout << "Enter a data point (-1 to stop input):" << endl;

        getline(cin, datapoint);

        // break if user enters -1
        if (datapoint == "-1") {
            break;
        }

        // Find the first comma
        int comma = datapoint.find(','); //function for position
        //npo stands for no position

        if (comma == string::npos) {
            // no comma is found
            cout << "Error: No comma in string." << endl;
            continue;
        } else if (datapoint.find(',', comma + 1) != string::npos) {
            // more than 1 comma
            cout << "Error: Too many commas in input." << endl;
            continue;
        } else {
            // only 1 -- split in two parts: name & numbers
            string str = datapoint.substr(0, comma);
            string num = datapoint.substr(comma + 1);
            //try/catch
            try {
                // Handle exceptions:
                //converting the number part into an integer
                //push back:store/add elements to a vector(similar to list)
                //output datapoints also
                int intData = stoi(num);  // Convert number to integer
                name.push_back(str);  // Store name
                numberofnovel.push_back(intData);  // Store number of novels

                // Print confirmation of data input (Need this for case 3/4)
                 cout << "Data string: " << str << endl;
                 cout << "Data integer: " << intData << endl;
            } catch (invalid_argument&) {
                // expection:not an integer
                cout << "Error: Comma not followed by an integer." << endl;
            }
        }
    }

    // print the table with a setw() value of 33.
    cout << endl << setw(33) << right << title << endl;
    // column header: setw(20)
    cout << setw(20) << left << column1 << "|" << setw(23) << right << column2 << endl;
    // Need a separator line
    cout << "--------------------------------------------" << endl;

    // Loop through the vectors
    // print each datapoint
    for (int i = 0; i < name.size(); i++) {  // Loop through all the data
        cout << setw(20) << left << name[i] << "|" << setw(23) << right << numberofnovel[i] << endl;
    }

    //Histogram
    cout << endl;  // Empty line before the histogram

    // Loop through the vectors and print a histogram of stars
    for (int i = 0; i < name.size(); i++) {
        cout << setw(20) << name[i] << " ";  // Print  name
        for (int j = 0; j < numberofnovel[i]; j++) {  // Print stars!
            cout << "*";
        }
        cout << endl; //next line
    }

    return 0;
}
