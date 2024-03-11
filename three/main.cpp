#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>


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


int main() {

  typedef struct {
    std::string Name;
    int max;
    int min;
  } Station;

  std::ifstream filtered_file(REDUCED_FILE);

  if (filtered_file.is_open()) {

    std::vector<Station> mins;
    std::vector<Station> maxs;

    unsigned long ELEVATION = -1;
    unsigned long NAME = -1;
    unsigned long TMAX = -1;
    unsigned long TMIN = -1;

    int c = 1;
    std::string derp;

    while (std::getline(filtered_file, derp)) {
      if (c == 1) {
        NAME = derp.find("STATION_NAME");
        ELEVATION = derp.find("ELEVATION");
        TMAX = derp.find("TMAX");
        TMIN = derp.find("TMIN");
      } else if (!derp.empty()) {
        std::string name = trim(derp.substr(NAME, ELEVATION - NAME));
        std::string max = trim(derp.substr(TMAX, 5));
        std::string min = trim(derp.substr(TMIN, 5));

        int fmax = std::stoi(max);
        int fmin = std::stoi(min);

        Station s;
        s.Name = name;
        s.max = fmax;
        s.min = fmin;

        // check maxs

        if (maxs.empty()) {
          maxs.push_back(s);
        } else {
          if (s.max > maxs.front().max) {
            maxs.clear();
            maxs.push_back(s);
          } else if (s.max == maxs.front().max) {
            maxs.push_back(s);
          }
        }

        if (mins.empty()) {
          mins.push_back(s);
        } else {
          if (s.min < mins.front().min) {
            mins.clear();
            mins.push_back(s);
          } else if (s.min == mins.front().min) {
            mins.push_back(s);
          }
        }
      }
      c++;
    }

    std::cout << "Maxs: " << std::endl;
    for (const Station &s : maxs) {
      std::cout << std::left << std::setw(60) << s.Name << std::setw(15)
                << s.max << std::setw(15) << s.min << std::endl;
    }

    std::cout << "Mins: " << std::endl;
    for (const Station &s : mins) {
      std::cout << std::left << std::setw(60) << s.Name << std::setw(15)
                << s.max << std::setw(15) << s.min << std::endl;
    }
  }

  filtered_file.close();
  return 0;
}