#include "Citygroup.hpp"
#include <eosiolib/asset.hpp>
#include <iostream>
#include <math.h>


namespace DotA {
    /*  中缀表达式转换成后缀表达式
    输入中缀表达式字符串infix，转化后返回后缀表达式字符串postfix
    输出串中，每一个数字后面放置一个#作为标识。因为数字使用char表达，234即三个char，“#”标识数字结束,
    做好数字完结标识后，即写入输出字符串中。
    遇到符号，左括号直接入栈；右括号时，将栈顶符号逐个取出写入输出字符串中，直到遇见左括号；
    运算符需循环与栈顶符号优先级进行比较：如果小于或者等于，取出栈顶符号写入输出字符串中，
    如果是左括号，直接入栈，如果优先级高于栈顶符号，入栈。
    */
    [[eosio::action]]
    void Citygroup::inftopos(string infix, string & result)//std:: std:://string InfixToPostfix
    {
        char current = 0;
        std::string postfix;//后缀表达式

        std::stack<char> mark;//符号栈

        std::map<char,int> priority;//符号优先级
        priority['+'] = 0;
        priority['-'] = 0;
        priority['*'] = 1;
        priority['/'] = 1;

        for(int i = 0;i < infix.size(); ++i)
        {
            current = infix[i];
            switch(current)
            {
                case '0':case '1':case '2':case '3':case '4':case '5':
                case '6':case '7':case '8':case '9':case '.':
                    postfix.push_back(current);//数字直接写入
                    break;
                case '+':case '-':case '*':case '/':
                    //如果运算符的前一项不是右括号即说明前一个数字输入完毕，用#标识
                    if(infix[i-1] != ')')
                        postfix.push_back('#');
                    //如果符号栈非空，即比较目前符号与栈顶符号优先级，低于等于出栈(并写入输出字符串)，
                    //直至符号全部出栈或者遇到了'('或者大于栈顶符号的优先级
                    if(!mark.empty())
                    {
                        char tempTop = mark.top();
                        while(tempTop != '(' && priority[current] <= priority[tempTop])
                        {
                            postfix.push_back(tempTop);
                            mark.pop();
                            if(mark.empty())
                                break;
                            tempTop = mark.top();
                        }
                    }
                    mark.push(current);//新符号入栈
                    break;
                case '(':
                    if(infix[i-1] >= '0' && infix[i-1] <= '9')// for expression 2-5*2(6/2)
                    {
                        postfix.push_back('#');
                        mark.push('*');
                    }
                    mark.push(current);
                    break;
                case ')':
                    if(infix[i-1] >= '0' && infix[i-1] <= '9')
                        postfix.push_back('#');//右括号说明前方数字输入完成，标识一下
                    while(mark.top() != '(')
                    {
                        postfix.push_back(mark.top());
                        mark.pop();
                    }
                    mark.pop();//左括号出栈
                    break;
                default:
                    break;//忽略其他字符
            }
        }
        if(infix[infix.size()-1] != ')')
            postfix.push_back('#');//中缀表达式最后一个是数字需要加上#。
        while(!mark.empty())//如果栈非空，全部出栈并写入输出字符串
        {
            postfix.push_back(mark.top());
            mark.pop();
        }
        // return postfix;
        result = postfix;
    }
    /*  计算后缀表达式结果
        输入为后缀表达式s，逐个读取字符，如果是数字即放入存放当前数字的字符串中，
        遇到“#”即将此字符串转换为float，
        使用atof()，参数接受const char*类型，字符串需使用.c_str()转化。
        完成数字识别转化后入栈，遇到符号即取出栈顶的两个数字计算，结果入栈。
        栈中最后的元素即为结果。
    */
    [[eosio::action]]
    void Citygroup::poxcpu(string s, float & result)//float std:://float posfixCompute
    {
        std::stack<float> tempResult;
        std::string strNum;//
        float currNum = 0;
        float tempNum = 0;
        print(" OK3.2 ");
        for(std::string::const_iterator i = s.begin(); i != s.end(); ++i)
        {   
            print("*i=",*i);
            switch(*i)
            {   
                case '0':case '1':case '2':case '3':case '4':case '5':
                case '6':case '7':case '8':case '9':case '.':
                    strNum.push_back(*i);
                    break;
                case '+':
                    tempNum = tempResult.top();print(" OK3.27 ");
                    tempResult.pop();print(" OK3.28 ");
                    tempNum += tempResult.top();print(" OK3.29 ");
                    tempResult.pop();print(" OK3.30 ");
                    tempResult.push(tempNum);print(" OK3.31 ");
                    break;
                case '-':
                    tempNum = tempResult.top();
                    tempResult.pop();
                    tempNum = tempResult.top() - tempNum;
                    tempResult.pop();
                    tempResult.push(tempNum);
                    break;
                case '*':
                    tempNum = tempResult.top();
                    tempResult.pop();
                    tempNum *= tempResult.top();
                    tempResult.pop();
                    tempResult.push(tempNum);
                    break;
                case '/':
                    tempNum = tempResult.top();
                    tempResult.pop();
                    tempNum = tempResult.top() / tempNum;
                    tempResult.pop();
                    tempResult.push(tempNum);
                    break;
                case '#':
                    print(" OK3.22 ");
                    currNum = std::stof(strNum);print(" OK3.25 ");//in c++11, use currNum = std::stof(strNum); atof(strNum.c_str())
                    strNum.clear();
                    tempResult.push(currNum);
                    break;
            }
            print(" OK3.35 ");
        }
        // return tempResult.top();
        print(" OK3.4 ");
        // auto r = tempResult.top();//where the problem at
        print(" OK3.6 ");
        float rr = tempResult.top();
        print(" OK3.8 ");
        result = rr;//tempResult.top();
    }

    [[eosio::action]]
    void Citygroup::expcal(string s, float & result)//std:://expressionCalculate
    {   
        string ss;
        string & infres = ss;
        print(" OK2 ");
        inftopos(s, infres);
        float lofloat = 0;
        float & poxres = lofloat;
        print("infre = ",infres, " ss = ",ss);
        print(" OK3 ");
        poxcpu(ss, poxres);
        print(" OK4 ");
        result = poxres;//posfixCompute(InfixToPostfix(s))   poxcpu(inftopos(s))
    }

// new city name can be xiangyang city/ winterfell / pingan / longlake

    [[eosio::action]]
    void Citygroup::cityinit(account_name account) {
        require_auth(account);
        // if(account != "dota") return;
        //productIndex products(_self, _self);
        cityIndex cities(_self, _self);

        auto iterator = cities.find(1);//newProduct.product_sid
        eosio_assert(iterator == cities.end(), "City for this ID already exists");
        cities.emplace(account, [&](auto& city) {
            city.city_id = 1;//
            city.city_name = "GoldCity";
            city.profit = 5*20/45;//5/person * 20 players / 45mins
            city.defense = 10;
            city.owner = 0;//??? god's account_name;
        });

        iterator = cities.find(2);//newProduct.product_id
        eosio_assert(iterator == cities.end(), "City for this ID already exists");
        cities.emplace(account, [&](auto& city) {
            city.city_id = 2;//
            city.city_name = "WoodCity";
            city.profit = 5*20/45;//5/person * 20 players / 45mins
            city.defense = 5;
            city.owner = 0;//??? god's account_name;
        });
    }
    

    [[eosio::action]]
    void Citygroup::getcitybyid(uint64_t cityId) {
        cityIndex cities(_self, _self);
        auto iterator = cities.find(cityId);
        eosio_assert(iterator != cities.end(), "City not found.");

        auto thecity = cities.get(cityId);
        print("|-| Id: ", thecity.city_id);
        print(" | CityName: ", thecity.city_name.c_str());
        print(" | Profit: ", thecity.profit);
        print(" | Defense: ", thecity.defense);
        print(" | Owner: ", thecity.owner);
    }


    [[eosio::action]]
    void Citygroup::getbattle(uint64_t battleId) {
        battleIndex battles(_self, _self);
        auto iterator = battles.find(battleId);
        eosio_assert(iterator != battles.end(), "Battle not found.");

        auto thisbattle = battles.get(battleId);
        print("  [ battle_id: ", thisbattle.battle_id);
        print(" | attacker: ", thisbattle.attacker);
        print(" | defender: ", thisbattle.defender);
        print(" | attacked_city_id: ", thisbattle.attacked_city_id);
        print(" | attacker_ts: ", thisbattle.attacker_ts);
        print(" | attacker_te: ", thisbattle.attacker_te);
        print(" | defender_ts: ", thisbattle.defender_ts);
        print(" | defender_te: ", thisbattle.defender_te);
        print(" | attacker_totalpoint: ", thisbattle.attacker_totalpoint);
        print(" | defender_totalpoint: ", thisbattle.defender_totalpoint);
        print(" | winner: ", thisbattle.winner);
        print("  ]  ");
    }


    [[eosio::action]]
    void Citygroup::citylistall(){
        cityIndex cities(_self, _self);
        auto iterator = cities.find(1);
        eosio_assert(iterator != cities.end(), "City not found.");
        auto thecity = cities.get(1);
        
        uint64_t cityId;
        for(cityId=1; cityId < thecity.city_name.size(); cityId++){
            auto iterator = cities.find(cityId);
            // eosio_assert(iterator != cities.end(), "City not found");
            if(!(iterator != cities.end()))break;
            auto thecity = cities.get(cityId);
            print("  [Id: ", thecity.city_id);
            print(" | Name: ", thecity.city_name.c_str());
            print(" | Profit: ", thecity.profit);
            print(" | Defense: ", thecity.defense);
            print(" | Owner: ", thecity.owner);
            print("]  ");
        }
    }


    [[eosio::action]]
    void Citygroup::updatecity(account_name account, uint64_t cityId, uint64_t newowner, uint64_t newprofit, int64_t __defense) {
        require_auth(account);
        // if(account != "dota") return;
        cityIndex cities(_self, _self);
        auto iterator = cities.find(cityId);
        eosio_assert(iterator != cities.end(), "City not found");

        cities.modify(iterator, account, [&](auto& city) {
            city.owner = newowner;
            city.profit = newprofit;
            city.defense += __defense;
        });
    }
    

    [[eosio::action]]
    void Citygroup::declarewar(account_name attacker, uint64_t cityId, uint64_t battleId){
        require_auth(attacker);
        cityIndex cities(_self, _self);
        auto iterator = cities.find(cityId);
        eosio_assert(iterator != cities.end(), "The city not found");
        auto thecity = cities.get(cityId);
        uint64_t defender = thecity.owner;
        eosio_assert(thecity.owner != attacker, "You can't declare war to a city you own.");
        
        uint64_t defenderPoints = thecity.defense;
        //Future : different city different problem
        print("Please solve the 24-Count problem of 3 3 2 8. Threshold: ",defenderPoints, " EOSC / 10 seconds");// (3/3+2)*8
        uint64_t t = current_time()/100000;//microseconds from 1970.
        print(", attacker_ts = ",t);//BUT Actual rRsolution is 0.5s ??!!

        battleIndex battles(_self, _self);
        auto itor = battles.find(battleId);
        eosio_assert(itor == battles.end(), "Battle for this ID already exists");
        battles.emplace(attacker, [&](auto& battle) {
            battle.battle_id = battleId;//
            battle.attacker = attacker;
            battle.defender = defender;
            battle.attacked_city_id = cityId;
            battle.attacker_ts = t;
        });
    }


    [[eosio::action]]//still have some problems
    void Citygroup::attack(account_name attacker, uint64_t battleId, uint64_t attack_value, string solution, uint64_t test){
        require_auth(attacker);
        battleIndex battles(_self, _self);
        auto iterator = battles.find(battleId);
        eosio_assert(iterator != battles.end(), "The battle not found");
        auto thisbattle = battles.get(battleId);

        uint64_t defender = thisbattle.defender;
        uint64_t cityId = thisbattle.attacked_city_id;
        cityIndex cities(_self, _self);
        auto itor = cities.find(cityId);
        eosio_assert(itor != cities.end(), "The city not found");
        auto thecity = cities.get(cityId);
        eosio_assert(defender != attacker, "You can't attack a city you own.");

        if( test==0 ){//not a test
            //Create asset
            //asset({amount}, string_to_symbol({precision}, {symbol}));
            asset attackPrice = asset(attack_value, string_to_symbol(4, "EOSC"));//thecity.defense
            
            // Do inline trasfer
            // action({permission_level}, {contract_deployer}, {contract_action}, {data_to_pass}).send();
            action(vector<permission_level>(), N(dota), N(transfer), make_tuple(attacker, _self, attackPrice, string(""))).send();
        }
        // if a test :
        uint64_t attackerPoints=attack_value*1000;
        uint64_t defenderPoints=thecity.defense*1000/10; // 10 seconds
        print("attackerPoints = ",attackerPoints, " ; defenderPoints = ",defenderPoints);

        float res = 0;
        float & result = res;
        print(" OK1 ");
        expcal(solution,result);//solution
        print(" OK5 ");
        uint64_t solution_result = uint64_t(result);//expressionCalculate(solution);
        print(" OKa.. ");

        if(solution_result==24){//Solved solution
            print(" Your solution is RIGHT! ");
            uint64_t t2 = current_time()/100000;
            uint64_t t1 = thisbattle.attacker_ts;
            uint64_t sovled_time = (t2-t1)/10 ;
            print(" Solved time : ", sovled_time);
            attackerPoints = attackerPoints/sovled_time;//****
            battles.modify(iterator, attacker, [&](auto& battle) {
                battle.attacker_totalpoint = attackerPoints;
                battle.defender_totalpoint = defenderPoints;
                // battle.defense += __defense;
            });
            // Execute action from another contract
            // action({permission_level}, {contract_deployer}, {contract_action}, {data_to_pass}).send();
            if( attackerPoints >= defenderPoints ){//If attacker succeed.
                print(" Battle winner:",attacker);
                // action(vector<permission_level>(), N(dota), N(addcity), make_tuple(attacker, 
                //     thecity.city_id,
                //     thecity.city_name,
                //     thecity.profit,
                //     thecity.defense,
                //     thecity.owner
                // )).send();

                battles.modify(iterator, attacker, [&](auto& battle) {
                    battle.winner = attacker;
                });
            }
            else{//If defender succeed.
                print(" Battle winner:",defender);
                battles.modify(iterator, attacker, [&](auto& battle) {
                    battle.winner = defender;
                });
            }
        }
        else{
            print(" Your solution is WRONG!");
        }
        
    }

}


