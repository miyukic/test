#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cmath>


class CityTree {
private:
    class Node {
    public:
        int population = 0;
        std::string cityNmae = "";
        std::shared_ptr<Node> leftNode = nullptr;
        std::shared_ptr<Node> rightNode = nullptr;
    };

    std::shared_ptr<Node> firstNode;
public:
    // コンストラクタ―
    CityTree() {
    }

    // <summary>
    //   ノードを受け取ってツリーに追加します。
    //   <param name="newNode">
    //     ノードを受け取ります。
    //   </pram>
    // </summary>
    void addNode(std::unique_ptr<Node> newNode) {
        int n = newNode->population;
        std::shared_ptr<Node> searchedNode = searchNode(n);
        if (searchedNode == nullptr) {
            this->firstNode = std::move(newNode);
            return;
        }
        if (searchedNode->population > n) {
            searchedNode->leftNode = std::move(newNode);
        } else if (searchedNode->population < n) {
            searchedNode->rightNode = std::move(newNode);
        }
    }

    void addNode(int population, std::string cityName) {
        auto newNode = std::make_unique<Node>(Node{population, cityName});    
        addNode(std::move(newNode));
    }

private:
    // <summary>
    //   指定した人口に近いノードを返します。
    //   存在しない場合はnullptrを返す。
    // </summary>
    // <param name="population">人口を受け取ります。</param>
    std::shared_ptr<Node> searchNode(int population) {
        if (firstNode == nullptr) return nullptr;
        std::shared_ptr<Node> curNode = this->firstNode;
        while(true) {
            if (curNode->population == population) {
                break;
            } else if(curNode->population > population) {
                if (curNode->leftNode == nullptr) break;
                curNode = curNode->leftNode;
            } else if(curNode->population < population) {
                if (curNode->rightNode == nullptr) break;
                curNode = curNode->rightNode;
            }
        }

        return curNode;
    }

};

int main() {
    std::unique_ptr<CityTree> tree = std::make_unique<CityTree>(CityTree());
    tree->addNode(195 * std::pow(10, 4), "sapporo");
    tree->addNode(196 * std::pow(10, 4), "oosaka");
    tree->addNode(197 * std::pow(10, 4), "nagoya");
    tree->addNode(198 * std::pow(10, 4), "hukuoka");
    tree->addNode(199 * std::pow(10, 4), "tokyo");
    tree->addNode(200 * std::pow(10, 4), "sendai");
}

