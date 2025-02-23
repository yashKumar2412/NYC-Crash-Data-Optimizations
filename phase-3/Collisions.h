#ifndef CRASH_H
#define CRASH_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std;

class Collisions {
    private:
        vector<string> collision_id;
        
        vector<int> crash_date;
        vector<int> crash_time;
        
        vector<int> borough;
        vector<int> zip_code;
        vector<float> latitude;
        vector<float> longitude;
        // vector<string> location;  // skipped because redundant (latitude, longitude)
        vector<string> on_street_name;
        vector<string> cross_street_name;
        vector<string> off_street_name;

        vector<int> num_of_persons_injured;
        vector<int> num_of_persons_killed;
        vector<int> num_of_pedestrians_injured;
        vector<int> num_of_pedestrians_killed;
        vector<int> num_of_cyclists_injured;
        vector<int> num_of_cyclists_killed;
        vector<int> num_of_motorists_injured;
        vector<int> num_of_motorists_killed;
        
        vector<string> contributing_factor_vehicle1;
        vector<string> contributing_factor_vehicle2;
        vector<string> contributing_factor_vehicle3;
        vector<string> contributing_factor_vehicle4;
        vector<string> contributing_factor_vehicle5;

        vector<string> vehicle_type_code1;
        vector<string> vehicle_type_code2;
        vector<string> vehicle_type_code3;
        vector<string> vehicle_type_code4;
        vector<string> vehicle_type_code5;

    public:
        int format_date(string date) {
            if (date.empty() || date.length() != 10)
                return 0;
            
            return stoi(date.substr(6, 4) + date.substr(0, 2) + date.substr(3, 2));
        }
        
        int format_time(string time) {
            if (time.empty() || time.length() != 5)
                return 0;
            
            return stoi(time.substr(0, 2) + time.substr(3, 2));
        }

        int string_to_int(string str) {
            if (str.empty() || !all_of(str.begin(), str.end(), ::isdigit))
                return 0;

            return stoi(str);
        }

        string trim_string(string str) {
            size_t first = str.find_first_not_of(" \t\n\r");
            size_t last = str.find_last_not_of(" \t\n\r");

            if (first == string::npos)
                return "N/A";
            
            return str.substr(first, (last - first + 1));
        }

        int get_size() {
            return collision_id.size();
        }

        void add_record(string id, string cd, string ct, string b, string zc, string l1, string l2, string on_sn, string cr_sn, string off_sn,
                            string prsn_inj, string prsn_kld, string pdstr_inj, string pdstr_kld, string cyc_inj, string cyc_kld, string mtr_inj, string mtr_kld,
                            string cfv1, string cfv2, string cfv3, string cfv4, string cfv5, string vtc1, string vtc2, string vtc3, string vtc4, string vtc5) {
            crash_date.emplace_back(format_date(cd));
            crash_time.emplace_back(format_time(ct));

            collision_id.emplace_back(trim_string(id));
            on_street_name.emplace_back(trim_string(on_sn));
            cross_street_name.emplace_back(trim_string(cr_sn));
            off_street_name.emplace_back(trim_string(off_sn));
            contributing_factor_vehicle1.emplace_back(trim_string(cfv1));
            contributing_factor_vehicle2.emplace_back(trim_string(cfv2));
            contributing_factor_vehicle3.emplace_back(trim_string(cfv3));
            contributing_factor_vehicle4.emplace_back(trim_string(cfv4));
            contributing_factor_vehicle5.emplace_back(trim_string(cfv5));
            vehicle_type_code1.emplace_back(trim_string(vtc1));
            vehicle_type_code2.emplace_back(trim_string(vtc2));
            vehicle_type_code3.emplace_back(trim_string(vtc3));
            vehicle_type_code4.emplace_back(trim_string(vtc4));
            vehicle_type_code5.emplace_back(trim_string(vtc5));

            zip_code.emplace_back(string_to_int(zc));
            borough.emplace_back(string_to_int(b));
            num_of_persons_injured.emplace_back(string_to_int(prsn_inj));
            num_of_persons_killed.emplace_back(string_to_int(prsn_kld));
            num_of_pedestrians_injured.emplace_back(string_to_int(pdstr_inj));
            num_of_pedestrians_killed.emplace_back(string_to_int(pdstr_kld));
            num_of_cyclists_injured.emplace_back(string_to_int(cyc_inj));
            num_of_cyclists_killed.emplace_back(string_to_int(cyc_kld));
            num_of_motorists_injured.emplace_back(string_to_int(mtr_inj));
            num_of_motorists_killed.emplace_back(string_to_int(mtr_kld));
            
            latitude.emplace_back(!l1.empty() ? stof(l1) : 0.0f);
            longitude.emplace_back(!l2.empty() ? stof(l2) : 0.0f); 
        }

        // AI-generated section start
        vector<string>& get_collision_id() { return collision_id; }
        vector<int>& get_crash_date() { return crash_date; }
        vector<int>& get_crash_time() { return crash_time; }
        vector<int>& get_borough() { return borough; }
        vector<int>& get_zip_code() { return zip_code; }
        vector<float>& get_latitude() { return latitude; }
        vector<float>& get_longitude() { return longitude; }
        vector<string>& get_on_street_name() { return on_street_name; }
        vector<string>& get_cross_street_name() { return cross_street_name; }
        vector<string>& get_off_street_name() { return off_street_name; }
        vector<int>& get_num_of_persons_injured() { return num_of_persons_injured; }
        vector<int>& get_num_of_persons_killed() { return num_of_persons_killed; }
        vector<int>& get_num_of_pedestrians_injured() { return num_of_pedestrians_injured; }
        vector<int>& get_num_of_pedestrians_killed() { return num_of_pedestrians_killed; }
        vector<int>& get_num_of_cyclists_injured() { return num_of_cyclists_injured; }
        vector<int>& get_num_of_cyclists_killed() { return num_of_cyclists_killed; }
        vector<int>& get_num_of_motorists_injured() { return num_of_motorists_injured; }
        vector<int>& get_num_of_motorists_killed() { return num_of_motorists_killed; }
        vector<string>& get_contributing_factor_vehicle1() { return contributing_factor_vehicle1; }
        vector<string>& get_contributing_factor_vehicle2() { return contributing_factor_vehicle2; }
        vector<string>& get_contributing_factor_vehicle3() { return contributing_factor_vehicle3; }
        vector<string>& get_contributing_factor_vehicle4() { return contributing_factor_vehicle4; }
        vector<string>& get_contributing_factor_vehicle5() { return contributing_factor_vehicle5; }
        vector<string>& get_vehicle_type_code1() { return vehicle_type_code1; }
        vector<string>& get_vehicle_type_code2() { return vehicle_type_code2; }
        vector<string>& get_vehicle_type_code3() { return vehicle_type_code3; }
        vector<string>& get_vehicle_type_code4() { return vehicle_type_code4; }
        vector<string>& get_vehicle_type_code5() { return vehicle_type_code5; }

        string get_collision_id(size_t idx) { return (idx < collision_id.size()) ? collision_id[idx] : "N/A"; }
        int get_crash_date(size_t idx) { return (idx < crash_date.size()) ? crash_date[idx] : 0; }
        int get_crash_time(size_t idx) { return (idx < crash_time.size()) ? crash_time[idx] : 0; }
        int get_borough(size_t idx) { return (idx < borough.size()) ? borough[idx] : borough.size(); }
        int get_zip_code(size_t idx) { return (idx < zip_code.size()) ? zip_code[idx] : 0; }
        float get_latitude(size_t idx) { return (idx < latitude.size()) ? latitude[idx] : 0.0f; }
        float get_longitude(size_t idx) { return (idx < longitude.size()) ? longitude[idx] : 0.0f; }
        string get_on_street_name(size_t idx) { return (idx < on_street_name.size()) ? on_street_name[idx] : "N/A"; }
        string get_cross_street_name(size_t idx) { return (idx < cross_street_name.size()) ? cross_street_name[idx] : "N/A"; }
        string get_off_street_name(size_t idx) { return (idx < off_street_name.size()) ? off_street_name[idx] : "N/A"; }
        int get_num_of_persons_injured(size_t idx) { return (idx < num_of_persons_injured.size()) ? num_of_persons_injured[idx] : 0; }
        int get_num_of_persons_killed(size_t idx) { return (idx < num_of_persons_killed.size()) ? num_of_persons_killed[idx] : 0; }
        int get_num_of_pedestrians_injured(size_t idx) { return (idx < num_of_pedestrians_injured.size()) ? num_of_pedestrians_injured[idx] : 0; }
        int get_num_of_pedestrians_killed(size_t idx) { return (idx < num_of_pedestrians_killed.size()) ? num_of_pedestrians_killed[idx] : 0; }
        int get_num_of_cyclists_injured(size_t idx) { return (idx < num_of_cyclists_injured.size()) ? num_of_cyclists_injured[idx] : 0; }
        int get_num_of_cyclists_killed(size_t idx) { return (idx < num_of_cyclists_killed.size()) ? num_of_cyclists_killed[idx] : 0; }
        int get_num_of_motorists_injured(size_t idx) { return (idx < num_of_motorists_injured.size()) ? num_of_motorists_injured[idx] : 0; }
        int get_num_of_motorists_killed(size_t idx) { return (idx < num_of_motorists_killed.size()) ? num_of_motorists_killed[idx] : 0; }
        string get_contributing_factor_vehicle1(size_t idx) { return (idx < contributing_factor_vehicle1.size()) ? contributing_factor_vehicle1[idx] : "N/A"; }
        string get_contributing_factor_vehicle2(size_t idx) { return (idx < contributing_factor_vehicle2.size()) ? contributing_factor_vehicle2[idx] : "N/A"; }
        string get_contributing_factor_vehicle3(size_t idx) { return (idx < contributing_factor_vehicle3.size()) ? contributing_factor_vehicle3[idx] : "N/A"; }
        string get_contributing_factor_vehicle4(size_t idx) { return (idx < contributing_factor_vehicle4.size()) ? contributing_factor_vehicle4[idx] : "N/A"; }
        string get_contributing_factor_vehicle5(size_t idx) { return (idx < contributing_factor_vehicle5.size()) ? contributing_factor_vehicle5[idx] : "N/A"; }
        string get_vehicle_type_code1(size_t idx) { return (idx < vehicle_type_code1.size()) ? vehicle_type_code1[idx] : "N/A"; }
        string get_vehicle_type_code2(size_t idx) { return (idx < vehicle_type_code2.size()) ? vehicle_type_code2[idx] : "N/A"; }
        string get_vehicle_type_code3(size_t idx) { return (idx < vehicle_type_code3.size()) ? vehicle_type_code3[idx] : "N/A"; }
        string get_vehicle_type_code4(size_t idx) { return (idx < vehicle_type_code4.size()) ? vehicle_type_code4[idx] : "N/A"; }
        string get_vehicle_type_code5(size_t idx) { return (idx < vehicle_type_code5.size()) ? vehicle_type_code5[idx] : "N/A"; }
        // AI-generated section end
};

#endif