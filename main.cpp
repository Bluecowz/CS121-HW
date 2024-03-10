#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>

/**
CS 121 Homework Assignment
NOTE: I will be visiting my grandchildren during spring break and I don't expect
to be doing any grading then. Thus, there will be no late penalty on assignments
submitted by March 15.



In class we did two programs that read the weather station data file and created
a new data file that contained only the good data records for tmax and tmin. The
first used getline to read in a complete record and then the string processing
operations were used to process the data. The second program used the input
buffer operations.

In this programming assignment you will process a similar - but different - data
file from December 2023. Note that there are additional columns for location
(ELEVATION, LATITUDE, LONGITUDE) and there is an additional column for average
temperature (TAVG).

You may modify the programs we did in class (linked below) or you may choose a
different approach.

Filter AL Weather Station Data  Links to an external site.with getline
Filter AL Weather Station Data with Input Buffer Operations - Input Buffer
Operations Download the data file here.  Weather Station Data December 2023

Here is a sample of the data from December 2023.

image.png

COLUMN                     Description

STATION                      Code identifying the recording data station (18
chars) STATION_NAME        The full name of the station (50 chars) DATE Date of
data recording in YYYYMMDD format MDPR                          Multiday
precipitation total DAPR                           Number of days included in
the MDPR PRCP                            Daily Precipitation Amount (Inches)
SNWD                          Snow Depth
SNOW                          Snowfall
TMAX                          High Temperature in Degrees Fahrenheit
TMIN                           Low Temperature  in Degrees Fahrenheit
AWND                         Average Wind Speed

Link to full dataset documentation if you are interested.

Create one MS Word (or other text file) containing all the C++ code with screen
shots of the program results. Text files created by the programs should be
uploaded as separate .txt files.

Here are the solutions for parts 3 - 6 for you to test your results: Solutions
for Homework Test CasesDownload Solutions for Homework Test Cases

Below are six problems. You may combine problems 1 and 2 into a single C++
program if you like to create the filtered data file and the reduced column data
file. Problems 3-6 should be separate C++ programs.
*/

const std::string OG_FILE = "AL_Weather_Stations_Dec_23.txt";
const std::string FILTERED_FILE = "Filtered_AL_Weather_Station.txt";
const std::string REDUCED_FILE = "reduced_column.txt";

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

  std::fstream my_file(OG_FILE);
  std::fstream filtered_file(FILTERED_FILE);

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
        if (line.substr(PRCP, 5).compare("-9999") == 0 ||
            line.substr(TMAX, 5).compare("-9999") == 0 ||
            line.substr(TMIN, 5).compare("-9999") == 0) {
          skip = true;
        }
      }
      c++;

      if (!skip) {
        filtered_file << line;
      }
    }
  }

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

  std::fstream filtered_file(FILTERED_FILE);
  std::fstream reduced_file(REDUCED_FILE);

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

      if (counter == 2) {
        NAME = derp.find("STATION_NAME");
        ELEVATION = derp.find("ELEVATION");
        LATITUDE = derp.find("LATITUDE");
        LONGITUDE = derp.find("LONGITUDE");
        DATE = derp.find("DATE");
        PRCP = derp.find("PRCP");
        TMAX = derp.find("TMAX");
        TMIN = derp.find("TMIN");
        MDPR = derp.find("MDPR");

        reduced_file << std::setw(40) << std::left << std::setfill(' ')
                     << "STATION NAME";
        reduced_file << std::setw(15) << std::left << "ELEVATION";
        reduced_file << std::setw(15) << std::left << "LATITUDE";
        reduced_file << std::setw(15) << std::left << "LONGITUDE";
        reduced_file << std::setw(15) << std::left << "DATE";
        reduced_file << std::setw(15) << std::left << "PRCP";
        reduced_file << std::setw(15) << std::left << "TMAX";
        reduced_file << std::setw(15) << std::left << "TMIN" << std::endl;

      } else if (counter > 2) {
        std::string name = derp.substr(NAME, ELEVATION - NAME);
        std::string elevation = derp.substr(ELEVATION, LATITUDE - ELEVATION);
        std::string lat = derp.substr(LATITUDE, LONGITUDE - LATITUDE);
        std::string lon = derp.substr(LONGITUDE, DATE - LONGITUDE);
        std::string date = derp.substr(DATE, MDPR - DATE);
        std::string prcp = derp.substr(PRCP, 5);
        std::string tmax = derp.substr(TMAX, 5);
        std::string tmin = derp.substr(TMIN, 5);

        reduced_file << std::setw(40) << std::left << std::setfill(' ') << name;
        reduced_file << std::setw(15) << std::left << elevation;
        reduced_file << std::setw(15) << std::left << lat;
        reduced_file << std::setw(15) << std::left << lon;
        reduced_file << std::setw(15) << std::left << date;
        reduced_file << std::setw(15) << std::left << prcp;
        reduced_file << std::setw(15) << std::left << tmax;
        reduced_file << std::setw(15) << std::left << tmin << std::endl;
      }
    };
  } else {
    std::cout << "Files failed to open." << std::endl;
  }

  filtered_file.close();
  reduced_file.close();
}

/**

DATA ANALYSIS

Use the reduced-column data file from problem 2 in the following four
programs.

3.  (20 Points) High and Low Temperatures with Recording Stations

Determine the highest and lowest temperatures in the state for the entire
month of December 2023. Print out (to the screen) the station names with
highest and lowest temperatures along with the high and low values. (Multiple
stations may record the same values for high and low.)
4.  (20 Points) Find the total precipitation from all stations in the state
for a single day.

The program calculates the total precipitation from all stations in inches for
a given date. The user needs only to enter the day (1-31) since year and month
do not change.)

TEST CASES:
December 10, 2023
December 25, 2023

5. (20 Points) Data by Station and Date

The program finds and returns the maximum temp, minimum temp and precipitation
for a given station and date. The user enters the station name and day of the
month. e.g. BANKHEAD  25.

TEST CASES:
MOBILE DOWNTOWN AIRPORT AL US   December 2, 2323
HUNTSVILLE INTNL AIRPORT AL US         December 9, 2023

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
  std::cout << "Running Question 1... ";
  q_one();
  std::cout << "Done" << std::endl;

  std::cout << "Running Question 2... ";
  q_two();
  std::cout << "Done" << std::endl;
  return 0;
};
