/**
 * @file hw2.h
 * @brief Operations on tabular data for HW2
 *  
 * Use of various STL containers to manipulate and process tabular data.
 * This homework specifically focuses on the YYC Community Crime dataset
 * available at:
 * https://data.calgary.ca/Health-and-Safety/Community-Disorder-Statistics/h3h6-kgme/about_data
 * The data has already been downloaded to a CSV file that is distributed 
 * with the homework.
 */

#include <string>
#include <cstdint>
#include <vector>
#include <map>

/// @brief A struct representing a row of data already filtered by year.
struct Record {
    std::string community;
    std::string category;
    uint32_t count;
    uint32_t month;
};

/// Function to read dataset from a CSV file
/// into a vector of records.
///
/// @brief Reads tabular dataset from a CSV file
/// @param filename Name of CSV file
/// @param result A vector of records to hold the data
void read_csv( std::string filename, std::vector<Record>& result );


/// @brief An enum that will serve as a column selector
enum class Column { COMMUNITY, CATEGORY, MONTH };

/// Groups records based on a column and applies a sum 
/// aggregation to the crime counts. 
///
/// @brief Groupwise aggregation (sum) of crime counts.
/// @param table The input tabular dataset (vector of records) 
/// @param col Column to use for grouping
/// @param result STL map where result is to be written. 
///               The map associates groups (unique entries in selected column) 
///               with their aggregated crime counts. If the month column (Column::MONTH) is 
///               selected, the key is the month expressed as a two-digit string: 
///               "01", "02", ..., "12".    
void group_aggregate(
    const std::vector<Record>& table, 
    Column col, 
    std::map<std::string,uint32_t>& result);


/// @brief Number of numerical features for each community
const size_t N = 11U;

/// Given a dataset (represented as an STL vector of records), 
/// computes the average feature-vector for each community. 
/// A numerical feature-vector for a community is a 
/// N-dimensional
/// vector (in the mathematical sense) obtained by appropriately encoding the 
/// feature columns for each observation in the dataset. The average vector is 
/// then obtained by community-wise averaging of feature-vectors.   
///
/// @brief Computes the average numerical feature-vector for each community.
/// @param table Tabular crime dataset as a vector of records.
/// @param result STL map where result is to be written. The map associates
///               each community with its average N-dimensional
///               numerical feature-vector represented as 
///               an STL array of N doubles. 
void avg_feature_by_community(
    const std::vector<Record>& table, 
    std::map< std::string, std::array<double, N>>& result);

/// Given an STL map of community-wise feature-vectors, determines
/// the Euclidean distance between the feature-vector of a source community 
/// and all other communities in the STL map. The distance is a measure of
/// similarity between the crime profiles of communities, the lower the
/// distance, the higher the similarity. Distances are written in an STL vector
/// that is sorted in ascending order by distance. 
///
/// @brief Determine the distance between a given community and all other
///        communities.
/// @param source Community for which distances to all other communities are 
///               to be computed.
/// @param features STL map of feature vectors as computed by the
///                 avg_feature_by_community() function.
/// @param result An STL vector of pairs (community, distance) where
///               distances are to be written. The vector should be
///               sorted in ascending order by distance. 
void distance_from_community(
    const std::string source,
    const std::map< std::string, std::array<double, N>>& features, 
    std::vector<std::pair<std::string, double>>& result);
