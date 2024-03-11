#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>

const std::string OG_FILE = "AL_Weather_Stations_Dec_23.txt";
const std::string FILTERED_FILE = "Filtered_AL_Weather_Station.txt";
const std::string REDUCED_FILE = "reduced_column.txt";

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

http://uahcs.org/CS121/data/AL_Weather_Stations_Dec_23.txt

PART I. Data File Preparation

1. (10 Points) Using the original Weather Station Data file from December 2023
find all records that have a bad data flag (-9999) for either the PRCP, TMAX or
TMIN fields. Produce a new data file (call it Filtered_AL_Weather_Station.txt )
that omits those records with bad data flags. This new file will be used in
problem 2. NOTE: You will need to test the PRCP column for bad data records in
addition to TMAX and TMIN.

*/

void q_one() {

  std::ifstream my_file;
  std::ofstream filtered_file(FILTERED_FILE);

  int c = 1;
  unsigned long PRCP = -1;
  unsigned long TMAX = -1;
  unsigned long TMIN = -1;

  my_file.open(OG_FILE);

  if (my_file.is_open()) {
    std::string line;
    while (std::getline(my_file, line)) {
      bool skip = false;

      if (c == 1) {
        PRCP = line.find("PRCP");
        TMAX = line.find("TMAX");
        TMIN = line.find("TMIN");
      } else if (c > 2) {
        if (line.substr(PRCP, 5) == "-9999" ||
            line.substr(TMAX, 5) == "-9999" ||
            line.substr(TMIN, 5) == "-9999") {
          skip = true;
        }
      }
      c++;

      if (!skip) {
        filtered_file << line << std::endl;
      }
    }
  }

  filtered_file.flush();
  my_file.close();
  filtered_file.close();
}

/**
2. (10 Points) Using the filtered data file from problem 1, create another
file (reduced_column.txt) with only the following eight columns of
information:

STATION NAME          ELEVATION     LATITUDE     LONGITUDE     DATE     PRCP
TMAX     TMIN

This file should reformat the data as follows:

Left justify the STATION NAME eliminating the leading spaces.
Reorganize the DATE as MM DD YYYY
ELEVATION, PRCP, TMAX and TMIN should be float or double with precision(2)
LATITUDE and LONGITUDE should have precision(4)
Here is a sample of the reduced column data file:

image.png

IMPORTANT: You may need to use the string conversion functions to convert the
string type numbers to float or double. The functions are stof and stod. To
convert a string to float do this:

string s_tmax; // string type for TMAX
float tmax;      // float type for TMAX

// Convert string to float
tmax = stof(s_tmax);

*/

void q_two() {

  std::ifstream filtered_file(FILTERED_FILE);
  std::ofstream reduced_file(REDUCED_FILE);

  unsigned long NAME = -1;
  unsigned long ELEVATION = -1;
  unsigned long LATITUDE = -1;
  unsigned long LONGITUDE = -1;
  unsigned long DATE = -1;
  unsigned long PRCP = -1;
  unsigned long TMAX = -1;
  unsigned long TMIN = -1;
  unsigned long MDPR = -1;

  std::string derp;
  int counter = 1;

  if (filtered_file.is_open() && reduced_file.is_open()) {

    while (std::getline(filtered_file, derp)) {

      if (counter == 1) {
        NAME = derp.find("STATION_NAME");
        ELEVATION = derp.find("ELEVATION");
        LATITUDE = derp.find("LATITUDE");
        LONGITUDE = derp.find("LONGITUDE");
        DATE = derp.find("DATE");
        PRCP = derp.find("PRCP");
        TMAX = derp.find("TMAX");
        TMIN = derp.find("TMIN");
        MDPR = derp.find("MDPR");

        reduced_file << std::setw(60) << std::left << "STATION_NAME";
        reduced_file << std::setw(15) << std::left << "ELEVATION";
        reduced_file << std::setw(15) << std::left << "LATITUDE";
        reduced_file << std::setw(15) << std::left << "LONGITUDE";
        reduced_file << std::setw(15) << std::left << "DATE";
        reduced_file << std::setw(15) << std::left << "PRCP";
        reduced_file << std::setw(15) << std::left << "TMAX";
        reduced_file << std::setw(15) << std::left << "TMIN" << std::endl;

      } else if (counter > 2) {
        std::string name = trim(derp.substr(NAME, ELEVATION - NAME));
        std::string elevation =
            trim(derp.substr(ELEVATION, LATITUDE - ELEVATION));
        float lat =
            std::stof(trim(derp.substr(LATITUDE, LONGITUDE - LATITUDE)));
        float lon = std::stof(trim(derp.substr(LONGITUDE, DATE - LONGITUDE)));
        std::string date = trim(derp.substr(DATE, MDPR - DATE));
        std::string prcp = trim(derp.substr(PRCP, 5));
        std::string tmax = trim(derp.substr(TMAX, 5));
        std::string tmin = trim(derp.substr(TMIN, 5));

        std::string year = date.substr(0, 4);
        std::string month = date.substr(4, 2);
        std::string day = date.substr(6, 2);

        char buf[100];
        std::sprintf(buf, "%s %s %s", month.c_str(), day.c_str(), year.c_str());
        date = buf;

        reduced_file << std::setw(60) << std::left << name;
        reduced_file << std::setw(15) << std::left << elevation;
        reduced_file << std::setw(15) << std::left << std::setprecision(4)
                     << lat;
        reduced_file << std::setw(15) << std::left << std::setprecision(4)
                     << lon;
        reduced_file << std::setw(15) << std::left << date;
        reduced_file << std::setw(15) << std::left << prcp;
        reduced_file << std::setw(15) << std::left << tmax;
        reduced_file << std::setw(15) << std::left << tmin << std::endl;
      }

      counter++;
    };
  } else {
    std::cout << "Files failed to open." << std::endl;
  }

  reduced_file.flush();
  filtered_file.close();
  reduced_file.close();
}

int main() {
  q_one();
  q_two();
  return 0;
}