#include "hw2.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <array>

using namespace std;

// filter for year
const uint32_t YEAR = 2023u;

// Reading data
void read_csv(string filename, vector<Record> &result) {

  // open file for reading
  ifstream istrm(filename, ios::in);
  if (!istrm.is_open())
    cerr << "Failed to open " << filename << '\n';
  else {
    string line;
    stringstream ss;
    bool header = true;
    string field[5];
    if (header) {
      // skip header
      getline(istrm, line);
    }
    while (getline(istrm, line)) {
      ss.clear();
      ss.str("");
      ss << line;

      for (size_t i = 0; i < 5; i++) {
        getline(ss, field[i], ',');
      }

      string comm = field[0];
      string cat = field[1];
      uint32_t count = stoul(field[2]);
      uint32_t year = stoul(field[3]);
      uint32_t month = stoul(field[4]);

      if (year == YEAR) {
        Record rec{comm, cat, count, month};
        result.push_back(rec);
      }
    }
  }
}

// This groups crime records by community ,category, or month.
void group_aggregate(const vector<Record> &table, Column col,
                     map<string, uint32_t> &result) {

  // YOUR CODE BELOW

  // iterating through every record in the dataset
  for (const auto &record : table) {
    string key;

    // uses the column enum to group by specified parameter
    switch (col) {
        case Column::COMMUNITY:
            key = record.community;
            break;
        case Column::CATEGORY:
            key = record.category;
            break;
        case Column::MONTH:
            key = to_string(record.month);
            break;
    }

    // crime count of each grouping
    result[key] += record.count;
  }
}

// convert crime record into 11-dim feature vector and performs
// one-hot encoding for crime categories, and normalizes both
// crime counts and the month. Finally, computes the average feature
// vector for each community.
void avg_feature_by_community(const vector<Record> &table,
                              map<string, array<double, N>> &result) {

  // YOUR CODE BELOW

  // storage for feature sums and crime counts for every community
  map<string, pair<array<double, N>, uint32_t>> temp;

  // list of crime categories (same order as found in companion.ipynb)  
  vector<string> categories = {
      "Assault (Non-domestic)", "Break & Enter - Commercial", "Break & Enter - Dwelling",
      "Break & Enter - Other Premises", "Commercial Robbery", "Street Robbery",
      "Theft FROM Vehicle", "Theft OF Vehicle", "Violence 'Other' (Non-domestic)"
  };

  // maps categories to positions in the feature vector
  map<string, int> category_index;
  for (size_t i = 0; i < categories.size(); i++) {
      category_index[categories[i]] = i;
  }

  // find the maximum count
  double max_count = 0.0;
  for (const auto &record : table) {
      max_count = max(max_count, static_cast<double>(record.count));
  }

  // iterate though each record and convert to feature vector, storing values per community
  for (const auto &record : table) {
      array<double, N> features_array = {0};
      
      //one-hot encoding
      if (category_index.find(record.category) != category_index.end()) {
          features_array[category_index[record.category]] = 1.0;
      }
      
      // normalizing crime counts and months
      features_array[9] = record.count / max_count;
      features_array[10] = record.month / 12.0;
      
      // adds vector to a community's total
      auto &entry = temp[record.community];
      for (size_t i = 0; i < N; i++) {
          entry.first[i] += features_array[i];
      }
      entry.second++; // number of records per community
  }
  
  // compute the community feature vector
  for (const auto &pair : temp) {
      array<double, N> avg;
      for (size_t i = 0; i < N; i++) {
          avg[i] = pair.second.first[i] / pair.second.second; 
      }
      result[pair.first] = avg;
  }
}

// find euclidean distance between a community's feature vector and all others.
// results are then sorted.
void distance_from_community(const string source,
                             const map<string, array<double, N>> &features,
                             vector<pair<string, double>> &result) {

  // YOUR CODE BELOW

  // get feature vec of source
  auto it = features.find(source);
  const std::array<double, N>& source_vector = it->second;

  // Compute distances to every other community
  result.clear();
  for (const auto& [community, feature_vector] : features) {
      if (community == source) continue; // Skip if community is the source
      double sum = 0.0;

      // square-difference of each feature
      for (size_t i = 0; i < N; i++) {
          double diff = source_vector[i] - feature_vector[i];
          sum += diff * diff;
      }

      // final euclidean distance
      double distance = std::sqrt(sum);
      result.emplace_back(community, distance);
  }

  // Sort by ascending distance
  std::sort(result.begin(), result.end(), 
  [](const auto& a, const auto& b) { return a.second < b.second; });
}
