#include <fstream>
#include <iostream>
#include <ostream>
#include <string>


const std::string OG_FILE = "AL_Weather_Stations_Dec_23.txt";
const std::string FILTERED_FILE = "Filtered_AL_Weather_Station.txt";
const std::string REDUCED_FILE = "reduced_column.txt";
const std::string AREA_FILE = "area_data.txt";

std::string trim(const std::string& str,
                 const std::string& whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

/**
4.  (20 Points) Find the total precipitation from all stations in the state
for a single day.

The program calculates the total precipitation from all stations in inches for
a given date. The user needs only to enter the day (1-31) since year and month
do not change.)

TEST CASES:
December 10, 2023
December 25, 2023

*/

int main() {

    std::string tday;
    std::cout << "Input a day: ";
    std::cin >> tday;

    if(tday.size() < 2) {
        tday = "0" + tday;
    }

    float total = 0;

    std::ifstream filtered_file(REDUCED_FILE);

    if(filtered_file.is_open()) {

        unsigned long DATE = -1;
        unsigned long PRCP = -1;


        int c = 1;
        std::string derp;

        while(std::getline(filtered_file, derp)) {
            if(c == 1) {
                DATE = derp.find("DATE");
                PRCP = derp.find("PRCP");
            } else if(!derp.empty()) {
                std::string date = trim(derp.substr(DATE, PRCP - DATE));
                std::string prcp = trim(derp.substr(PRCP, 5));

                std::string day = date.substr(3, 2);

                if(tday == day) {
                    float p = std::stof(prcp);
                    total += p;
                }

            }
            c++;
        }

    }
    std::cout << "Total: " << total << std::endl;
    filtered_file.close();
}
