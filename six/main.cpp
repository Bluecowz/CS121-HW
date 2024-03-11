#include <fstream>
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

6. (20 Points)  Data by Location and Date

The program creates a new data file which contains data from all stations
within a specified rectangular area (North Latitude, South Latitude, West
Longitude, East Longitude) for a given date.

The user will enter the 4 coordinates and the data as:

NL, SL, WL, EL
MM DD YYYY

The program will locate all Stations within that area and on that date and
create a new data file with all the data from those stations.

The data file should have the same columns as the reduced column data file.
That is, use the reduced column data file for this program.

Upload the files created by these programs along with the code and screenshots
of the test cases. You should have three files. One for each test case.

TEST CASES

1. Madison County: 35.00,  34.55,  -86.79, -86.21  Date 12  2  2023
2. Northeast AL:      35.00, 33.50,   -86.79, -85.21    Date 12 14 2023
3. South AL:             32.34,  30.30,  -88.47,  -85.20  Date 12 31 2023
 */

int main() {

  std::string sNL;
  std::string sSL;
  std::string sWL;
  std::string sEL;
  std::string d;

  std::cout << "Enter NL: ";
  std::cin >> sNL;
  std::cout << "Enter SL: ";
  std::cin >> sSL;
  std::cout << "Enter WL: ";
  std::cin >> sWL;
  std::cout << "Enter EL ";
  std::cin >> sEL;
  std::cout << "Enter Day Date: ";
  std::cin >> d;

  if (d.size() == 1) {
    d = "0" + d;
  }

  const float NL = std::stof(sNL);
  const float SL = std::stof(sSL);
  const float EL = std::stof(sEL);
  const float WL = std::stof(sWL);

  std::ifstream reduced_file(REDUCED_FILE);
  std::ofstream location_file(AREA_FILE);

  unsigned long NAME = -1;
  unsigned long ELEVATION = -1;
  unsigned long LATITUDE = -1;
  unsigned long LONGITUDE = -1;
  unsigned long DATE = -1;
  unsigned long MDPR = -1;

  std::string derp;
  int counter = 1;

  if (location_file.is_open() && reduced_file.is_open()) {

    while (std::getline(reduced_file, derp)) {
      bool skip = true;
      if (counter == 1) {
        NAME = derp.find("STATION_NAME");
        ELEVATION = derp.find("ELEVATION");
        LATITUDE = derp.find("LATITUDE");
        LONGITUDE = derp.find("LONGITUDE");
        DATE = derp.find("DATE");
        MDPR = derp.find("MDPR");
        skip = false;

      } else if (counter > 2) {
        std::string name = trim(derp.substr(NAME, ELEVATION - NAME));
        std::string elevation =
            trim(derp.substr(ELEVATION, LATITUDE - ELEVATION));
        float lat =
            std::stof(trim(derp.substr(LATITUDE, LONGITUDE - LATITUDE)));
        float lon = std::stof(trim(derp.substr(LONGITUDE, DATE - LONGITUDE)));
        std::string date = trim(derp.substr(DATE, MDPR - DATE));

        std::string day = date.substr(3, 2);

        if (day == d && lat <= NL && lat >= SL && lon <= EL && lon >= WL) {
          skip = false;
        }
      }

      if (!skip) {
        location_file << derp << std::endl;
      }

      counter++;
    };
  } else {
    std::cout << "Files failed to open." << std::endl;
  }

  location_file.flush();
  reduced_file.close();
  location_file.close();

  return 0;
}
