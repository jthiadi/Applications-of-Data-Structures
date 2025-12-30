#ifndef TARIFF_HPP
#define TARIFF_HPP

#include <vector>
#include <string>
#include <iostream>
#include <map>

class TariffPolicy {
public:
    struct RateChange {
        std::string rate;  // 稅率
    };

    struct CountryRate {
        std::string countryName;
        RateChange newRate;

        CountryRate(std::string name) : countryName(name) {}

        void setRate(const std::string& rate) {
            newRate.rate = rate;
        }
    };

public:
    // Trie 資料結構
    struct TrieNode {
        TrieNode* children[26];
        int idx;
        
        TrieNode() {
            idx = -1;
            for(int i = 0; i < 26; i++) children[i] = nullptr;
        }
    };
    
    TrieNode* m_root;
    // m_policies 存 country 跟 rate 資訊
    std::vector<TariffPolicy::CountryRate> m_policies;

public:
    // 建構函式
    TariffPolicy() {
        m_root = new TrieNode();
    }
    // 解構函式
    ~TariffPolicy() {
        Clear(m_root);
    }
    // 禁止複製
    TariffPolicy(const TariffPolicy&) = delete;
    TariffPolicy& operator=(const TariffPolicy&) = delete;

    void Clear(TrieNode* node);

    int Insert(CountryRate countryRate);

    const TariffPolicy::CountryRate* Search(const std::string& countryName);
};

class PolicyNode {
private:
    std::vector<int> children;  // 子政策
    int parent;                 // 父政策
    int level;                  // 政策等級
    std::string date;           // 政策日期
    TariffPolicy* policy;       // 政策內容
public:
    PolicyNode() : parent(-1), level(-1), date(""), policy(nullptr) {}
    PolicyNode(int p, int l, std::string d) : parent(p), level(l), date(d), policy(nullptr) {}
    PolicyNode(int p, int l, std::string d, TariffPolicy* p_policy) : parent(p), level(l), date(d), policy(p_policy) {}

    friend class TradePolicy;
};

class TradePolicy {
private:
    std::vector<PolicyNode*> m_policyNodes;  // 所有政策節點
    int m_current;                           // 當前政策索引
    std::map<std::string, int> m_date_index; // 日期到索引的映射

public:
    TradePolicy();

    TradePolicy(const TradePolicy&) = delete;
    TradePolicy& operator=(const TradePolicy&) = delete;
    
    ~TradePolicy();

    void Switch(const std::string& date);

    void Announce(TariffPolicy* policy, const std::string& date);

    std::vector<std::string> Check(const std::string& countryName, bool ascending = true);

    int FindPolicyByDate(const std::string& date);
};


#endif