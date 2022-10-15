#include <stdint.h>
#include <string>


class Character {
    std::string id;
    int16_t level;
    uint64_t exp;
    int32_t hp;     // HP
    int32_t cp;     //カリスマポイント
    struct Status {
        int32_t power;      //力
        int32_t knowledge;  //知識
        int32_t wisdom;     //知恵
        int32_t agility;    //敏捷
        int32_t charisma;   //カリスマ
        int32_t luck;       //運
        int32_t health;     //健康
    } status;
};
