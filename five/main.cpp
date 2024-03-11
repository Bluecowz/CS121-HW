#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>

const std::string OG_FILE = "AL_Weather_Stations_Dec_23.txt";
const std::string FILTERED_FILE = "Filtered_AL_Weather_Station.txt";
const std::string REDUCED_FILE = "reduced_column.txt";
const std::string AREA_FILE = "area_data.txt";

std::string trim(const std::string &str,
                 const std::string &whitespace = " \t") {
  const auto strBegin = str.find_first_not_of(whitespace);
  if (strBegin == std::string::npos)
    return ""; // no content

  const auto strEnd = str.find_last_not_of(whitespace);
  const auto strRange = strEnd - strBegin + 1;

  return str.substr(strBegin, strRange);
}

/**

5. (20 Points) Data by Station and Date

The program finds and returns the maximum temp, minimum temp and precipitation
for a given station and date. The user enters the station name and day of the
month. e.g. BANKHEAD  25.

TEST CASES:
MOBILE DOWNTOWN AIRPORT AL US   December 2, 2323
HUNTSVILLE INTNL AIRPORT AL US         December 9, 2023

*/

int main() {
  std::string tday;
  std::cout << "Input a day: ";
  std::cin >> tday;

  if (tday.size() < 2) {
    tday = "0" + tday;
  }

  std::cin.ignore();
  std::string station;
  std::cout << "Input station: ";
  std::getline(std::cin, station);

  float total = 0;

  std::ifstream filtered_file(REDUCED_FILE);

  if (filtered_file.is_open()) {

    unsigned long NAME = -1;
    unsigned long ELEVATION = -1;
    unsigned long DATE = -1;
    unsigned long PRCP = -1;
    unsigned long TMAX = -1;
    unsigned long TMIN = -1;
    unsigned long MDPR = -1;

    int c = 1;
    std::string derp;

    while (std::getline(filtered_file, derp)) {
      if (c == 1) {
        NAME = derp.find("STATION_NAME");
        ELEVATION = derp.find("ELEVATION");
        DATE = derp.find("DATE");
        PRCP = derp.find("PRCP");
        TMAX = derp.find("TMAX");
        TMIN = derp.find("TMIN");
        MDPR = derp.find("MDPR");
      } else if (!derp.empty()) {
        std::string name = trim(derp.substr(NAME, ELEVATION - NAME));
        std::string date = trim(derp.substr(DATE, MDPR - DATE));
        std::string prcp = trim(derp.substr(PRCP, 5));
        std::string tmax = trim(derp.substr(TMAX, 5));
        std::string tmin = trim(derp.substr(TMIN, 5));

        std::string day = date.substr(3, 2);

        if (tday == day && station == name) {
          std::cout << std::left << std::setw(50) << name;
          std::cout << std::setw(8) << std::left << "Max:" << tmax;
          std::cout << std::setw(8) << std::left << "Min:" << tmin;
          std::cout << std::setw(8) << std::left << "Per:" << prcp;
          std::cout << std::endl;
        }
      }
      c++;
    }
  }

  filtered_file.close();
  return 0;
}
