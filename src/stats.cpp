#include "stats.h"
#include <algorithm>
#include <numeric>
#include <cmath>

Stats::Stats(string name, const vector<int> &chain_lengths)
    : name(name), chain_lengths(chain_lengths){
    
    // ENTRIES
    entries = std::accumulate(chain_lengths.begin(), chain_lengths.end(), 0);
    
    // CHAINS
    chains = 0;
    for(int length:chain_lengths){ if(length>0) ++chains; }
    
    // LOAD FACTOR
    if(!chain_lengths.empty()){
        load_factor= static_cast<double>(entries) / chain_lengths.size(); }
    else{ load_factor=0; }

    // MIN MAX
    if(chain_lengths.empty()){ min=0, max=0; }
    else{
        min= *std::min_element(chain_lengths.begin(), chain_lengths.end());
        max= *std::max_element(chain_lengths.begin(), chain_lengths.end()); }

    // SPAN
    span = max - min;

    // MEAN
    if (!chain_lengths.empty()){
        double sum = std::accumulate(chain_lengths.begin(), chain_lengths.end(), 0.0);
        mean = sum/chain_lengths.size(); } 
    else {mean=0;}

    // STD
    if (!chain_lengths.empty()){
        double sum_squares = 0.0;
        for (int len : chain_lengths){
            double diff = len-mean;
            sum_squares += diff*diff; }
        stddev = std::sqrt(sum_squares / chain_lengths.size()); } 
    else{ stddev = 0; }
}