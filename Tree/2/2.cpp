#include "function.h"
#include <algorithm>

using namespace std;

void TariffPolicy::Clear(TrieNode* node) {
    if (!node) return;
    for (auto* child:node->children) Clear(child);
}

int TariffPolicy::Insert(CountryRate countryRate) {
    TrieNode* current = m_root;
    for (auto c:countryRate.countryName) {
        auto index = c - 'a';
        if (!current->children[index]) current->children[index] = new TrieNode();
        current = current -> children[index];
    }

    current ->idx = m_policies.size();
    m_policies.push_back(countryRate);
    return current->idx;
}

const TariffPolicy::CountryRate* TariffPolicy::Search(const std::string& countryName) {
    TrieNode* current = m_root;
    for (auto c: countryName) {
        auto index = c - 'a';
        if (!current->children[index]) return nullptr;
        current = current -> children[index];
    }

    return (current->idx >= 0) ? &m_policies[current->idx] : nullptr;
}

TradePolicy::TradePolicy() {
    m_current = 0;
    m_policyNodes.push_back(new PolicyNode(-1, 0, ""));
}

TradePolicy::~TradePolicy() {

}

void TradePolicy::Switch(const std::string& date) {
    auto index = m_date_index.find(date);

    if (index == m_date_index.end()) cout << "No policy found on " << date << endl;
    else {
        m_current = index->second;
        cout << "Switched to Policy on " << date << endl;
    }
}

void TradePolicy::Announce(TariffPolicy* policy, const std::string& date) {
    auto level = m_policyNodes[m_current]->level + 1;
    auto index = m_policyNodes.size();

    PolicyNode* node = new PolicyNode(m_current, level, date, policy);
    m_policyNodes.push_back(node);
    m_date_index[date] = index;
    m_policyNodes[m_current]->children.push_back(index);
    m_current = index;

    cout << "New policy announced on " << date << endl;
}

std::vector<std::string> TradePolicy::Check(const std::string& countryName, bool ascending) {
    vector<string> history;

    for (auto i = m_current; i != -1; i = m_policyNodes[i]->parent) {
        if (auto* policy = m_policyNodes[i]->policy) {
            if (auto* rate = policy->Search(countryName)) history.push_back(rate->newRate.rate);
        }
    }

    if (ascending) reverse(history.begin(), history.end());
    return history;
}

int TradePolicy::FindPolicyByDate(const std::string& date) {
    auto index = m_date_index.find(date);
    return (index == m_date_index.end() ? -1 : index->second);
}