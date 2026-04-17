#include "json.hpp"
using  json = nlohmann::json;

#include<iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;

string func1(){
    json js;
    js["xiaoxiao"] = {"nihao", "hello", "how are you"};
    js["dongdong"] = "baibai";
    js["jingjing"] = {1, 2, 3, 4, "5上山打老虎"};
    js["huahua"]["name"] = "张花";
    js["chacha"]["habbit"] = {{"eat", "drink"}, {"play", "happy"}};
    return js.dump();
}
string func2(){
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    map<int, string> m;
    m.insert({1, "我爱你"});
    m.insert({2, "中国"});
    m.insert({3, "亲爱的母亲"});
    json js1;
    js1["vec1"] = v;
    js1["map2"] = m;
    // cout<<js1<<endl;
    return js1.dump();
}

int main(int argc, char *argv[]){
    string recvbuf = func1();
    json jsbuf = json::parse(recvbuf);
    cout<<jsbuf["xiaoxiao"]<<endl;
    cout<<jsbuf["jingjing"]<<endl;
    cout<<jsbuf["dongdong"]<<endl;
    cout<<jsbuf["huahua"]<<endl;
    cout<<jsbuf["chacha"]<<endl;

    string recvbuf2 = func2();
    json jsbuf2 = json::parse(recvbuf2);
    vector<int> arr = jsbuf2["vec1"];
    auto mp = jsbuf2["map2"];
    cout<<jsbuf2<<endl;
    cout<<arr[2]<<endl;
    cout<<mp[1]<<endl;
    return 0;
}