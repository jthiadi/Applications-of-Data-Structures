#include "function.h"
#include <iostream>
#include <string>
#include <vector>
#include<list>
using namespace std;

void Commit::Clear(TrieNode* node) {
    if (!node) return;
    // apus semua child 
    for (int i = 0; i < 26; ++i) {
        if (node->children[i]) {
            Clear(node->children[i]);
        }
    }
    delete node;
}

int Commit::Insert(FileChange fileChange) {
    m_commits.push_back(move(fileChange));
    int idx = m_commits.size() - 1;

    TrieNode* p = m_root;
    // masukin nama file 
for (char c : m_commits[idx].fileName) {
    int ci = c - 'a';
    if (!p->children[ci]) {
        p->children[ci] = new TrieNode();
    }
    p = p->children[ci];
}
    p->idx = idx;
    return idx;
}

const Commit::FileChange* Commit::Search(const string& str) {
    TrieNode* p = m_root;
	//TrieNode p = m_root;

    // buat nyari file based on nama
	for (char c : str) {
		int ci = c - 'a';
		if (ci < 0 || ci >= 26 || !p->children[ci]) return nullptr; 
		p = p->children[ci];
	}
    if (p->idx != -1) return &m_commits[p->idx];
    else return NULL;
}

Git::Git() {
    Commit* rootCommit = new Commit();
    GitNode* rootNode = new GitNode(-1, 0, rootCommit);
    m_gitnodes.push_back(rootNode);
    m_current = 0;
}

Git::~Git() {
    for (GitNode* node : m_gitnodes) {
        delete node->commit;
        delete node;
    }
}

void Git::Switch(int index) {
	m_current = index;
    cout << "Switched to Branch " << index << endl;

    // cout << "current: " << m_current << endl;
}

void Git::CreateCommit(Commit* commit) {
    int parent = m_current;
    int lvl = m_gitnodes[parent]->level + 1;
    GitNode* node = new GitNode(parent, lvl, commit);
    m_gitnodes.push_back(node);

    int newIdx = m_gitnodes.size() - 1;
    m_gitnodes[parent]->children.push_back(newIdx);
    m_current = newIdx;

    // cout << "index: " << newIdx << endl;
}

vector<string> Git::Open(const string& filename) {
    vector<string> content;
    vector<int> path;

    // kmpulin smw node 
    for (int i = m_current; i != -1; i = m_gitnodes[i]->parent) {
        path.push_back(i);
    }

    // dari root ke current
    for (vector<int>::reverse_iterator i = path.rbegin(); i != path.rend(); i++) {
        const Commit::FileChange* fc = m_gitnodes[*i]->commit->Search(filename);
        if (!fc) continue;

        for (list<Commit::LineChange>::const_iterator j = fc->insertions.begin(); j != fc->insertions.end(); j++) {
            int pos = j->index;
            if (pos >= 0 && pos <= content.size()) {
                content.insert(content.begin() + pos, j->content);
                // cout << "masuk " << pos << ": " << j->content << endl;
            }
        }

        for (list<Commit::LineChange>::const_reverse_iterator k = fc->deletions.rbegin(); k != fc->deletions.rend(); k++) {
            int pos = k->index;
            if (pos >= 0 && pos < content.size()) {
                content.erase(content.begin() + pos);
                // cout << "apus " << pos << endl;
            }
        }
    }

    return content;
}