#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cmath>


class CityTree {
private:
    static class Node {
    public:
        int population = 0;
        std::string cityNmae = "";
        std::shared_ptr<Node> leftNode = nullptr;
        std::shared_ptr<Node> rightNode = nullptr;
    };

    std::vector<std::shared_ptr<Node>> _nodeList;
public:
    // コンストラクタ―
    CityTree() {
    }

    void addNode(int population, std::string cityName) {
        auto node = std::make_shared<Node>(Node{population, cityName});    
        _nodeList.push_back(node);
        int n = node->population;
        searchNode(30);
    }
private:
    //指定した人口に近いノードを返します。
    //存在しない場合はnullptrを返す。
    std::shared_ptr<Node> searchNode(int population) {
        if (this->_nodeList.size() < 1) {
            return nullptr;
        }

        auto curNode = _nodeList.at(0);
        if (curNode->population < population) {
            // 大きい方を探す、右側を探す
            do {
                curNode = curNode->rightNode;
            } while (curNode->population < population);
        } else {
            // 小さい方を探す、左側を探す
        }
        
    }



};

int main() {
    CityTree* tree = new CityTree();
    tree->addNode(195 * std::pow(10, 4), "sapporo");
}

