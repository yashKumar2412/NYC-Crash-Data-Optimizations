#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <omp.h>
#include <sys/stat.h>
#include "CollisionDataset.h"

using namespace std;

void CollisionDataset::load_CSV(string file_name) {
    struct stat stat_buf;
    
    if (stat(file_name.c_str(), &stat_buf) != 0) {
        cerr << "Error: Could not open file " << file_name << endl;
        return;
    }

    long file_size = stat_buf.st_size;
    int thread_count = omp_get_max_threads();
    long chunk_size = file_size / thread_count;

    vector<Collisions> thread_data(thread_count);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        long start = thread_id * chunk_size;
        long end = (thread_id == thread_count - 1) ? file_size : start + chunk_size;

        ifstream file(file_name);
        file.seekg(start);

        string dummy;
        getline(file, dummy);

        string collision_id, crash_date, crash_time, borough, zip_code, latitude, longitude, location, on_street_name, cross_street_name, off_street_name;
        string person_injured, person_killed, pedestrian_injured, pedestrian_killed, cyclist_injured, cyclist_killed, motorist_injured, motorist_killed;
        string contributing_factor_vehicle1, contributing_factor_vehicle2, contributing_factor_vehicle3, contributing_factor_vehicle4, contributing_factor_vehicle5;
        string vehicle_type_code1, vehicle_type_code2, vehicle_type_code3, vehicle_type_code4, vehicle_type_code5;
        string line;

        while (file.tellg() < end && getline(file, line)) {
            stringstream ss(line);
            
            // AI-generated section start
            getline(ss, crash_date, ',');
            getline(ss, crash_time, ',');

            getline(ss, borough, ',');
            getline(ss, zip_code, ',');
            getline(ss, latitude, ',');
            getline(ss, longitude, ',');

            getline(ss, location, ',');
            if (!location.empty())
                getline(ss, location, ','); // dummy double read to ignore location data when present

            getline(ss, on_street_name, ',');
            getline(ss, cross_street_name, ',');
            getline(ss, off_street_name, ',');
            
            getline(ss, person_injured, ',');
            getline(ss, person_killed, ',');
            getline(ss, pedestrian_injured, ',');
            getline(ss, pedestrian_killed, ',');
            getline(ss, cyclist_injured, ',');
            getline(ss, cyclist_killed, ',');
            getline(ss, motorist_injured, ',');
            getline(ss, motorist_killed, ',');

            getline(ss, contributing_factor_vehicle1, ',');
            getline(ss, contributing_factor_vehicle2, ',');
            getline(ss, contributing_factor_vehicle3, ',');
            getline(ss, contributing_factor_vehicle4, ',');
            getline(ss, contributing_factor_vehicle5, ',');

            getline(ss, collision_id, ',');

            getline(ss, vehicle_type_code1, ',');
            getline(ss, vehicle_type_code2, ',');
            getline(ss, vehicle_type_code3, ',');
            getline(ss, vehicle_type_code4, ',');
            getline(ss, vehicle_type_code5, ',');

            thread_data[thread_id].add_record(
                collision_id, crash_date, crash_time, borough, zip_code, latitude, longitude, on_street_name, cross_street_name, off_street_name,
                person_injured, person_killed, pedestrian_injured, pedestrian_killed, cyclist_injured, cyclist_killed, motorist_injured, motorist_killed,
                contributing_factor_vehicle1, contributing_factor_vehicle2, contributing_factor_vehicle3, contributing_factor_vehicle4, contributing_factor_vehicle5,
                vehicle_type_code1, vehicle_type_code2, vehicle_type_code3, vehicle_type_code4, vehicle_type_code5
            );
            // AI-generated section end
        }
    }

    for (auto& local_data : thread_data) {
        // AI-generated section start
        collisions.get_collision_id().insert(
            collisions.get_collision_id().end(),
            local_data.get_collision_id().begin(),
            local_data.get_collision_id().end()
        );
        
        collisions.get_crash_date().insert(
            collisions.get_crash_date().end(),
            local_data.get_crash_date().begin(),
            local_data.get_crash_date().end()
        );
        
        collisions.get_crash_time().insert(
            collisions.get_crash_time().end(),
            local_data.get_crash_time().begin(),
            local_data.get_crash_time().end()
        );
        
        collisions.get_borough().insert(
            collisions.get_borough().end(),
            local_data.get_borough().begin(),
            local_data.get_borough().end()
        );
        
        collisions.get_zip_code().insert(
            collisions.get_zip_code().end(),
            local_data.get_zip_code().begin(),
            local_data.get_zip_code().end()
        );
        
        collisions.get_latitude().insert(
            collisions.get_latitude().end(),
            local_data.get_latitude().begin(),
            local_data.get_latitude().end()
        );
        
        collisions.get_longitude().insert(
            collisions.get_longitude().end(),
            local_data.get_longitude().begin(),
            local_data.get_longitude().end()
        );
        
        collisions.get_on_street_name().insert(
            collisions.get_on_street_name().end(),
            local_data.get_on_street_name().begin(),
            local_data.get_on_street_name().end()
        );
        
        collisions.get_cross_street_name().insert(
            collisions.get_cross_street_name().end(),
            local_data.get_cross_street_name().begin(),
            local_data.get_cross_street_name().end()
        );
        
        collisions.get_off_street_name().insert(
            collisions.get_off_street_name().end(),
            local_data.get_off_street_name().begin(),
            local_data.get_off_street_name().end()
        );
        
        collisions.get_num_of_persons_injured().insert(
            collisions.get_num_of_persons_injured().end(),
            local_data.get_num_of_persons_injured().begin(),
            local_data.get_num_of_persons_injured().end()
        );
        
        collisions.get_num_of_persons_killed().insert(
            collisions.get_num_of_persons_killed().end(),
            local_data.get_num_of_persons_killed().begin(),
            local_data.get_num_of_persons_killed().end()
        );
        
        collisions.get_num_of_pedestrians_injured().insert(
            collisions.get_num_of_pedestrians_injured().end(),
            local_data.get_num_of_pedestrians_injured().begin(),
            local_data.get_num_of_pedestrians_injured().end()
        );
        
        collisions.get_num_of_pedestrians_killed().insert(
            collisions.get_num_of_pedestrians_killed().end(),
            local_data.get_num_of_pedestrians_killed().begin(),
            local_data.get_num_of_pedestrians_killed().end()
        );
        
        collisions.get_num_of_cyclists_injured().insert(
            collisions.get_num_of_cyclists_injured().end(),
            local_data.get_num_of_cyclists_injured().begin(),
            local_data.get_num_of_cyclists_injured().end()
        );
        
        collisions.get_num_of_cyclists_killed().insert(
            collisions.get_num_of_cyclists_killed().end(),
            local_data.get_num_of_cyclists_killed().begin(),
            local_data.get_num_of_cyclists_killed().end()
        );
        
        collisions.get_num_of_motorists_injured().insert(
            collisions.get_num_of_motorists_injured().end(),
            local_data.get_num_of_motorists_injured().begin(),
            local_data.get_num_of_motorists_injured().end()
        );
        
        collisions.get_num_of_motorists_killed().insert(
            collisions.get_num_of_motorists_killed().end(),
            local_data.get_num_of_motorists_killed().begin(),
            local_data.get_num_of_motorists_killed().end()
        );
        
        collisions.get_contributing_factor_vehicle1().insert(
            collisions.get_contributing_factor_vehicle1().end(),
            local_data.get_contributing_factor_vehicle1().begin(),
            local_data.get_contributing_factor_vehicle1().end()
        );
        
        collisions.get_contributing_factor_vehicle2().insert(
            collisions.get_contributing_factor_vehicle2().end(),
            local_data.get_contributing_factor_vehicle2().begin(),
            local_data.get_contributing_factor_vehicle2().end()
        );
        
        collisions.get_contributing_factor_vehicle3().insert(
            collisions.get_contributing_factor_vehicle3().end(),
            local_data.get_contributing_factor_vehicle3().begin(),
            local_data.get_contributing_factor_vehicle3().end()
        );
        
        collisions.get_contributing_factor_vehicle4().insert(
            collisions.get_contributing_factor_vehicle4().end(),
            local_data.get_contributing_factor_vehicle4().begin(),
            local_data.get_contributing_factor_vehicle4().end()
        );
        
        collisions.get_contributing_factor_vehicle5().insert(
            collisions.get_contributing_factor_vehicle5().end(),
            local_data.get_contributing_factor_vehicle5().begin(),
            local_data.get_contributing_factor_vehicle5().end()
        );
        
        collisions.get_vehicle_type_code1().insert(
            collisions.get_vehicle_type_code1().end(),
            local_data.get_vehicle_type_code1().begin(),
            local_data.get_vehicle_type_code1().end()
        );
        
        collisions.get_vehicle_type_code2().insert(
            collisions.get_vehicle_type_code2().end(),
            local_data.get_vehicle_type_code2().begin(),
            local_data.get_vehicle_type_code2().end()
        );
        
        collisions.get_vehicle_type_code3().insert(
            collisions.get_vehicle_type_code3().end(),
            local_data.get_vehicle_type_code3().begin(),
            local_data.get_vehicle_type_code3().end()
        );
        
        collisions.get_vehicle_type_code4().insert(
            collisions.get_vehicle_type_code4().end(),
            local_data.get_vehicle_type_code4().begin(),
            local_data.get_vehicle_type_code4().end()
        );
        
        collisions.get_vehicle_type_code5().insert(
            collisions.get_vehicle_type_code5().end(),
            local_data.get_vehicle_type_code5().begin(),
            local_data.get_vehicle_type_code5().end()
        );
        // AI-generated section end  
    }
}

vector<int> CollisionDataset::search_by_zip_code(int zc) {
    vector<int> query_result;

    #pragma omp parallel
    {
        vector<int> thread_results;

        #pragma omp for
        for (size_t i = 0; i < collisions.get_size(); i++) {
            if (collisions.get_zip_code(i) == zc) {
                thread_results.emplace_back(i);
            }
        }

        #pragma omp critical
        {
            query_result.insert(query_result.end(), thread_results.begin(), thread_results.end());
        }
    }    

    return query_result;
}

vector<int> CollisionDataset::search_by_injury_ranges(int inj_low, int inj_high) {
    vector<int> query_result;

    #pragma omp parallel
    {
        vector<int> thread_results;

        #pragma omp for
        for (size_t i = 0; i < collisions.get_size(); i++) {
            if (collisions.get_num_of_persons_injured(i) >= inj_low && collisions.get_num_of_persons_injured(i) <= inj_high) {
                thread_results.emplace_back(i);
            }
        }

        #pragma omp critical
        {
            query_result.insert(query_result.end(), thread_results.begin(), thread_results.end());
        }
    }

    return query_result;
}

vector<int> CollisionDataset::search_by_latitude(float lat) {
    vector<int> query_result;

    #pragma omp parallel
    {
        vector<int> thread_results;

        #pragma omp for
        for (size_t i = 0; i < collisions.get_size(); i++) {
            if (collisions.get_latitude(i) == lat) {
                thread_results.emplace_back(i);
            }
        }

        #pragma omp critical
        {
            query_result.insert(query_result.end(), thread_results.begin(), thread_results.end());
        }
    }

    return query_result;
}

vector<int> CollisionDataset::search_by_date_range(string sd, string ed) {
    vector<int> query_result;
    
    int start_date = format_date(sd);
    int end_date = format_date(ed);

    #pragma omp parallel
    {
        vector<int> thread_results;

        #pragma omp for
        for (size_t i = 0; i < collisions.get_size(); i++) {
            if (collisions.get_crash_date(i) >= start_date && collisions.get_crash_date(i) <= end_date) {
                thread_results.emplace_back(i);
            }
        }

        #pragma omp critical
        {
            query_result.insert(query_result.end(), thread_results.begin(), thread_results.end());
        }
    }

    return query_result;
}

vector<int> CollisionDataset::search_by_borough(string b) {
    vector<int> query_result;

    #pragma omp parallel
    {
        vector<int> thread_results;

        #pragma omp for
        for (size_t i = 0; i < collisions.get_size(); i++) {
            if (collisions.get_borough(i) == b) {
                thread_results.emplace_back(i);
            }
        }

        #pragma omp critical
        {
            query_result.insert(query_result.end(), thread_results.begin(), thread_results.end());
        }
    }

    return query_result;
}