#include "function.h"
#include <iostream>
#include <string>

// #define DEBUG 

#ifdef DEBUG
#include <chrono>
#include <cstdio>
#endif

int main() {
#ifdef DEBUG
    freopen("testcase/example.in", "r", stdin);
    freopen("testcase/example.out", "w+", stdout);
    auto start = std::chrono::high_resolution_clock::now();
#endif

    TradePolicy tradePolicy;

    // read testcasee
    int t;
    std::cin >> t;
    
    while(t--) {
        std::string cmd1, cmd2;
        std::cin >> cmd1 >> cmd2;
        
        if(cmd2 == "switch") {
            std::string date;
            std::cin >> date;
            tradePolicy.Switch(date);
        }
        else if(cmd2 == "announce") {
            int countryCount;
            std::string date;
            std::cin >> countryCount >> date;
            
            TariffPolicy* policy = new TariffPolicy();
            
            while(countryCount--) {
                std::string countryName, rate;
                std::cin >> countryName >> rate;
                
                TariffPolicy::CountryRate countryRate(countryName);
                countryRate.setRate(rate);
                policy->Insert(countryRate);
            }
            
            tradePolicy.Announce(policy, date);
        }
        
        else if(cmd2 == "check") {
            std::string countryName;
            std::string order;
            std::cin >> countryName >> order;
            
            // 根據 order 參數決定排序方向
            bool ascending = true;  // 默認為由早到晚
            if(order == "desc" || order == "descending") {
                ascending = false;  // 由晚到早
            }
            
            std::vector<std::string> rateHistory = tradePolicy.Check(countryName, ascending);
            if(rateHistory.empty()) {
                std::cout << "No tariff policy for " << countryName << std::endl;
            } else {
                std::cout << "Tariff history for " << countryName << ":" << std::endl;
                for(const auto& rate : rateHistory) {
                    std::cout << rate << std::endl;
                }
            }
        }
    }

#ifdef DEBUG
    auto end = std::chrono::high_resolution_clock::now();

    fclose(stdin);
    fclose(stdout);

    freopen("/dev/tty", "r", stdin);
    freopen("/dev/tty", "w", stdout);

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << duration.count() << " ms\n";
#endif

    return 0;
}