#include "hw2.h"
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <map>
#include <array>
#include <algorithm>  // for sort

using namespace std;

// CSV file to read
const string filename { "Community_Crime_Statistics_Clean.csv" };



int main() {
    vector<Record> result;
    read_csv(filename, result );
    cout << "Read " << result.size() << " records" << endl;

    string d {"|"};
    auto print = [&d](Record& rec) {
        cout << rec.community << d << rec.category << d << rec.count << d << rec.month << "\n";
    };

    // display head and tail
    size_t N = 5;
    for(size_t i = 0; i < N; i++) {
        print( result[i]);
    }
    cout << "..." << endl;
    for(size_t i = result.size()-N; i < result.size(); i++) {
        print( result[i]);
    }


    // Unique values in Community, Category, and Month
    set<string> unique_categories, unique_communities;
    set<uint32_t> unique_months;

    for (const auto& rec : result) {
        unique_categories.insert(rec.category);
        unique_communities.insert(rec.community);
        unique_months.insert(rec.month);
    }

    cout << "\nUnique Categories (" << unique_categories.size() << "):\n";
    for (const auto& cat : unique_categories) {
        cout << cat << "\n";
    }

    cout << "\nUnique Communities (" << unique_communities.size() << "): " << unique_communities.size() << "\n";
    cout << "\nUnique Months (" << unique_months.size() << "): ";
    for (const auto& month : unique_months) {
        cout << month << " ";
    }
    cout << "\n";

    // Aggregate crime data by category, month, and community
    map<string, uint32_t> crime_by_category, crime_by_month, crime_by_community;

    group_aggregate(result, Column::CATEGORY, crime_by_category);
    group_aggregate(result, Column::MONTH, crime_by_month);
    group_aggregate(result, Column::COMMUNITY, crime_by_community);

    // Display aggregated crime count by category
    cout << "\nCrime Count by Category:\n";
    for (const auto& [category, count] : crime_by_category) {
        cout << category << ": " << count << "\n";
    }

    // Display aggregated crime count by month
    cout << "\nCrime Count by Month:\n";
    for (const auto& [month, count] : crime_by_month) {
        cout << month << ": " << count << "\n";
    }

    // Display top and bottom 5 communities by crime count
    vector<pair<string, uint32_t>> sorted_communities(crime_by_community.begin(), crime_by_community.end());
    sort(sorted_communities.begin(), sorted_communities.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    cout << "\nBottom 5 Communities by Crime Count:\n";
    for (size_t i = 0; i < 5 && i < sorted_communities.size(); ++i) {
        cout << sorted_communities[i].first << ": " << sorted_communities[i].second << "\n";
    }

    cout << "\nTop 5 Communities by Crime Count:\n";
    for (size_t i = sorted_communities.size() - 5; i < sorted_communities.size(); ++i) {
        cout << sorted_communities[i].first << ": " << sorted_communities[i].second << "\n";
    }

    // Compute average feature vectors for each community
    constexpr size_t M = 11U;
    map<string, array<double, M>> avg_features;
    avg_feature_by_community(result, avg_features);

    // Print one-hot encodings for the first 5 communities
    cout << "\nOne-Hot Encoded Features for First 5 Communities:\n";
    cout << "(Category One-Hot Encoding, Crime Count, Month)\n";
    int count = 0;
    for (const auto& [community, feature_vec] : avg_features) {
        cout << community << ": [ ";
        for (size_t i = 0; i < M; i++) {
            cout << fixed << setprecision(4) << feature_vec[i] << " ";
        }
        cout << "]\n";
        if (++count >= 5) break;
    }

    cout << "\nAverage Feature Vectors for 5 Random Communities:\n";
    count = 0;
    for (const auto& [community, feature_vec] : avg_features) {
        cout << community << ": [ ";
        for (double val : feature_vec) {
            cout << fixed << setprecision(4) << val << " ";
        }
        cout << "]\n";
        if (++count >= 5) break;
    }

    // Compute distances from selected communities
    vector<string> sample_communities = {"VARSITY", "BELTLINE", "PANORAMA HILLS"};
    for (const auto& source : sample_communities) {
        vector<pair<string, double>> distances;
        distance_from_community(source, avg_features, distances);

        cout << "\nTop 5 Closest Communities to " << source << ":\n";
        for (size_t i = 0; i < min(size_t(5), distances.size()); i++) {
            cout << distances[i].first << ": " << distances[i].second << "\n";
        }
    }
    
    return 0;
}
