#ifndef COLLISIONDATASET_H
#define COLLISIONDATASET_H

#include <vector>
#include "Collisions.h"

using namespace std;

class CollisionDataset {
    private:
        Collisions collisions;
    
    public:
        void load_CSV(string filename);
        vector<int> search_by_zip_code(int zc);
        vector<int> search_by_injury_ranges(int inj_low, int inj_high);
        vector<int> search_by_latitude(float lat);
        vector<int> search_by_date_range(string start_date, string end_date);
        vector<int> search_by_borough(string b);

        Collisions get_collisions() {
            return collisions;
        }

        int format_date(string date) {
            if (collisions.get_size() == 0)
                return 0;
            
            return collisions.format_date(date);
        }

};

#endif